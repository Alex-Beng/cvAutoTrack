#include "pch.h"
#include "Smooth.h"

Smooth::Smooth()
{
	type = FilterType::Smooth;
}

Smooth::~Smooth()
{
}

//��ƽ�������뵱ǰ�����Ȩ���ټ��ϲ���ƫ��������ֵȡ10��ƽ������
cv::Point2d Smooth::filterting(const cv::Point2d& pos)
{
	const cv::Point2d old_mean_pos = mean_pos;
	mean_pos = (pos * 0.1 + mean_pos * 0.9);		
	mean_pos += (mean_pos - old_mean_pos) * 9;
	return mean_pos;
}

cv::Point2d Smooth::re_init_filterting(const cv::Point2d& pos)
{
	mean_pos = pos;
	return filterting(pos);
}
