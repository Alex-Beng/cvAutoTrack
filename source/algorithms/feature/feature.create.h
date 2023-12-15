#pragma once
#include "../algorithms.feature.h"
#include <execution>

namespace tianli::algorithms::feature::create
{
    // NEED_TEST: 构造均匀分布的特征点，基于网格划分，在每个网格内至少采样到目标密度的特征点
    static features from_image(const cv::Mat &image, const int target_density = 100, const int grid_radius = 512, const cv::Mat &mask = cv::Mat())
    {
        const float target_density_rate = 1.0 / (grid_radius * grid_radius) * target_density;
        // 将图像根据尺寸划分为网格，均匀划分，尽可能以给的半径划分
        // 网格行数和列数
        const size_t grids_row_count = std::ceil(1.0 * image.rows / grid_radius);
        const size_t grids_col_count = std::ceil(1.0 * image.cols / grid_radius);
        // 网格行和列的半径
        const size_t grid_row_radius = std::ceil(1.0 * image.rows / grids_row_count);
        const size_t grid_col_radius = std::ceil(1.0 * image.cols / grids_col_count);
        const size_t grid_size = grids_row_count * grids_col_count;

        std::vector<std::pair<cv::Rect, features>> grid_features(grid_size);
        //  结果特征点
        features result_features;
        for (int grid_row_index = 0; grid_row_index < grids_row_count; grid_row_index++)
        {
            for (int grid_col_index = 0; grid_col_index < grids_col_count; grid_col_index++)
            {
                // 计算网格范围
                const size_t grid_x = grid_col_index * grid_col_radius;
                const size_t grid_y = grid_row_index * grid_row_radius;
                // 如果为最后一个格子，由于可能的舍入精度，可能会遗漏最后一个像素，所以改为直接计算最后一个格子的大小
                const size_t grid_width = grid_col_index == grids_col_count - 1 ? image.cols - grid_x : grid_row_radius;
                const size_t grid_height = grid_row_index == grids_row_count - 1 ? image.rows - grid_y : grid_col_radius;
                // 计算网格索引
                const size_t grid_index = grid_row_index * grids_col_count + grid_col_index;
                const cv::Rect grid_rect = cv::Rect(grid_x, grid_y, grid_width, grid_height);
                grid_features[grid_index].first = grid_rect;
            }
        }

        std::for_each(std::execution::par_unseq, grid_features.begin(), grid_features.end(), [&](std::pair<cv::Rect, features> &grid_feature)
                      {
                const int fixed_target_density = std::ceil(target_density_rate * grid_feature.first.area());
                const auto &detector = cv::xfeatures2d::SURF::create(100, 1, 3, true, false);
                float threshold = 100.0;
                features feature;
                for (int i = 0; i < 10; i++)
                {
                    if (threshold < 1 || feature.keypoints.size() > fixed_target_density)
                        break;
                    detector->setHessianThreshold(threshold);
                    feature = feature::from_image(detector, image, grid_feature.first, mask);
                    threshold /= 2.0;
                }
                grid_feature.second = feature; });

        for (int i = 0; i < grid_size; i++)
            result_features = merge(result_features, grid_features[i].second, cv::Point2d(grid_features[i].first.x, grid_features[i].first.y));
        return result_features;
    }
}