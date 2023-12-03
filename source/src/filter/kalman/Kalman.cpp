#include "pch.h"
#include "Kalman.h"

Kalman::Kalman()
{
	type = FilterType::Kalman;
	
	KF = cv::KalmanFilter(stateNum, measureNum, controlNum);
	state = cv::Mat(stateNum, 1, CV_32F); 
	processNoise = cv::Mat(stateNum, 1, CV_32F);
	measurement = cv::Mat::zeros(measureNum, 1, CV_32F);	//measurement(x,y)

	randn(state, cv::Scalar::all(0), cv::Scalar::all(0.1)); //随机生成一个矩阵，期望是0，标准差为0.1;
	// set A
	KF.transitionMatrix = (cv::Mat_<float>(2, 2) <<
		1, 0,
		0, 1);
	// set B
	KF.controlMatrix = (cv::Mat_<float>(2, 2) <<
		1, 0,
		0, 1);
	// set Q
	setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));
	// set H
	KF.measurementMatrix = (cv::Mat_<float>(2, 2) <<
		1, 0,
		0, 1);
	// set R
	setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-5));

	randn(KF.statePost, cv::Scalar::all(0), cv::Scalar::all(0.1));
}

Kalman::~Kalman()
{
}

cv::Point2d Kalman::filterting(const cv::Point2d& pos, const cv::Point2f& u_k)
{
	// use u_k to predict
	// make u_k to cv::Mat
	cv::Mat u_k_mat = cv::Mat::zeros(2, 1, CV_32F);
	u_k_mat.at<float>(0, 0) = u_k.x;
	u_k_mat.at<float>(1, 0) = u_k.y;
	cv::Mat prediction = KF.predict(u_k_mat);
	cv::Point2d predictPt = cv::Point2d(prediction.at<float>(0), prediction.at<float>(1));

	//3.update measurement
	measurement.at<float>(0, 0) = static_cast<float>(pos.x);
	measurement.at<float>(1, 0) = static_cast<float>(pos.y);

	//4.update
	KF.correct(measurement);

	cv::Point2d resP = cv::Point2d(KF.statePost.at<float>(0), KF.statePost.at<float>(1));
	return resP;
}

cv::Point2d Kalman::re_init_filterting(const cv::Point2d& pos)
{
	KF.init(stateNum, measureNum, controlNum);

	state = cv::Mat(stateNum, 1, CV_32F); //state(x,y,detaX,detaY)
	processNoise = cv::Mat(stateNum, 1, CV_32F);
	measurement = cv::Mat::zeros(measureNum, 1, CV_32F);	//measurement(x,y)

	randn(state, cv::Scalar::all(0), cv::Scalar::all(0.1)); //随机生成一个矩阵，期望是0，标准差为0.1;
	// set A
	KF.transitionMatrix = (cv::Mat_<float>(2, 2) <<
		1, 0,
		0, 1);
	// set B
	KF.controlMatrix = (cv::Mat_<float>(2, 2) <<
		1, 0,
		0, 1);
	// set Q
	//!< process noise covariance matrix (Q)
	// wk 是过程噪声，并假定其符合均值为零，协方差矩阵为Qk(Q)的多元正态分布;
	setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));

	//!< measurement noise covariance matrix (R)
	//vk 是观测噪声，其均值为零，协方差矩阵为Rk,且服从正态分布;
	setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-1));

	//!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/  A代表F: transitionMatrix
	//预测估计协方差矩阵;
	// 这啥啊，这不计算中的误差协方差
	// 绑架问题不收敛的罪魁祸首，这个协方差会影响K的计算，从而影响后续的预测和更新
	// setIdentity(KF.errorCovPost, cv::Scalar::all(1));

	//!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
	//initialize post state of kalman filter at random 
	randn(KF.statePost, cv::Scalar::all(0), cv::Scalar::all(0.1));

	KF.statePost.at<float>(0) = static_cast<float>(pos.x);
	KF.statePost.at<float>(1) = static_cast<float>(pos.y);

	cv::Mat prediction = KF.predict();
	cv::Point2d predictPt = cv::Point2d(prediction.at<float>(0), prediction.at<float>(1));

	//3.update measurement
	measurement.at<float>(0, 0) = static_cast<float>(pos.x);
	measurement.at<float>(1, 0) = static_cast<float>(pos.y);

	//4.update
	KF.correct(measurement);

	cv::Point2d resP = cv::Point2d(KF.statePost.at<float>(0), KF.statePost.at<float>(1));
	
	return resP;
}
