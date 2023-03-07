#pragma once
#include "utils/Utils.h"

bool save_map_keypoint_cache(std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors, double hessian_threshold = 1, int octaves = 1, int octave_layers = 1, bool extended = false, bool upright = false);
bool load_map_keypoint_cache(std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors, double hessian_threshold = 1, int octaves = 1, int octave_layers = 1, bool extended = false, bool upright = false);
bool get_map_keypoint(std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors, double hessian_threshold = 1, int octaves = 1, int octave_layers = 1, bool extended = false, bool upright = false);

bool judgesIsOnCity(std::vector<TianLi::Utils::MatchKeyPoint> goodMatches, double minimap_scale);

// ������ȷ����Сƥ������������ڸ�ֵ��Ϊ������
constexpr int NOT_ON_CITY__MIN_GOODMATCHS = 20;
// �����Ⳣ��ʹ�ó��������ż������Сƥ���������С�ڸ�ֵ��ƥ��ʧ��
constexpr int NOT_ON_CITY__ON_CITY_MIN_GOODMATCHS = 8;
// ������ȷ����Сƥ������������ڸ�ֵ��Ϊ������
constexpr int ON_CITY__MIN_GOODMATCHS = 20;
// ȫͼƥ��ʱ����������ƥ��㷽����ֵ����Χ�ڼ�Ϊ������
constexpr double ALL_MAP__ON_CITY__STDEV_THRESH = 50;
// ȫͼƥ��ʱ������������ƥ��㷽����ֵ����Χ�ڼ�Ϊ������
constexpr double ALL_MAP__NOT_ON_CITY__STDEV_THRESH = 500;

// ������ƥ����޳����ӣ�Խ��Խ�ϸ�
constexpr double SURF_MATCH_RATIO_THRESH = 0.66;
// ��ͼ��С��ͼҰ������ű����������ͼ / С��ͼҰ�⣩�õ���ע�������С��ͼ��Ұ��������������ǳ����ڱ�����1.3/2
constexpr double MAP_BOTH_SCALE_RATE = 1.3;
// ��ͼ��ȡС��������İ뾶��ĿǰΪС��ͼ��׼�뾶
constexpr int DEFAULT_SOME_MAP_SIZE_R = 106;

class Match
{
public:
	struct KeyMatPoint
	{
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		bool empty() { return keypoints.size() == 0; }
		auto size() { return keypoints.size(); }
	};
public:
	Match(double hessian_threshold = 1, int octaves = 4, int octave_layers = 3, bool extended = false, bool upright = false);
	~Match() = default;
public:
	cv::Ptr<cv::xfeatures2d::SURF> detector;
	cv::Ptr<cv::DescriptorMatcher> matcher;
	KeyMatPoint query;
	KeyMatPoint train;
public:
	std::vector<std::vector<cv::DMatch>> match(cv::Mat& query_descriptors, cv::Mat& train_descriptors);
	std::vector<std::vector<cv::DMatch>> match(KeyMatPoint& query_key_mat_point, KeyMatPoint& train_key_mat_point);
	bool detect_and_compute(cv::Mat img, std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors);
	bool detect_and_compute(cv::Mat img, KeyMatPoint& key_mat_point);
};


class SurfMatch
{
	cv::Mat _mapMat;
	cv::Mat _miniMapMat;
	cv::Mat _miniMapLastMat;


	cv::Point2d pos;
	cv::Rect rect_continuity_map;
public:
	SurfMatch() = default;
	~SurfMatch() = default;

public:
	Match matcher;
	
	Match::KeyMatPoint map, some_map, mini_map;

	bool isInit = false;
	bool isContinuity = false;
	bool isCoveying = false;
	bool isOnCity = false;

	int max_continuity_retry = 3;
	
	bool is_success_match = false;

	void setMap(cv::Mat gi_map);
	void setMiniMap(cv::Mat miniMapMat);

	void Init();
	void Init(std::vector<cv::KeyPoint>& gi_map_keypoints, cv::Mat& gi_map_descriptors);
	void UnInit();
	void match();

	cv::Point2d match_continuity(bool& calc_continuity_is_faile);
	cv::Point2d match_continuity_on_city(bool& calc_continuity_is_faile);
	cv::Point2d match_continuity_not_on_city(bool& calc_continuity_is_faile);

	cv::Point2d match_no_continuity(bool& calc_is_faile);
	cv::Point2d match_no_continuity_1st(bool& calc_is_faile);

	//ȫͼƥ��
	cv::Point2d match_all_map(bool& calc_is_faile,double& stdev, double minimap_scale_param = 1.0);

	cv::Point2d getLocalPos();
	bool getIsContinuity();
private:

	cv::Mat crop_border(cv::Mat& mat, double border)
	{
		int crop_size = static_cast<int>((mat.rows + mat.cols) * 0.5 * border);
		return mat(cv::Rect(crop_size, crop_size, mat.cols - crop_size * 2, mat.rows - crop_size * 2));
	}
};

