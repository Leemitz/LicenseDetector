#ifndef LICPLATEDETCT_H_
#define LICPLATEDETCT_H_

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

struct OneDimRegion
{
	int begin;
	int end;
	int length, center;
	OneDimRegion(int begin_, int end_) : begin(begin_), end(end_)
	{
		length = end - begin + 1;
		center = (begin_ + end_) / 2;
	}
};

class LicPlateDetect
{
public:
	LicPlateDetect() = default;
	LicPlateDetect(Mat &src_img) { src_img_ = src_img.clone(); };
	void set_image(Mat &src_img) { src_img_ = src_img.clone(); }
	void lic_plate_detect();//检测接口函数
	void pre_process();
	void segmentation();
	void get_vertical_img(Mat &image);
	void get_horizontal_img();
	void cut_black_border();
	void char_recognition();
	double distance(Mat m1, Mat m2);
	double distance_c(Mat m1, Mat m2);

	Mat src_img_;//原图->resize()
	Mat license_img_;//车牌区域,被平滑滤波
	Mat license_img_src;
	Mat vertical_img_; //竖直方向经过裁剪后的车牌
	Mat vertical_img_color_;
	vector<Mat> char_imgs_;//水平方向经过裁剪后的车牌文字区域
	vector<string> char_res_;//字符识别结果
	string lic_str_;

};

bool has_license(Mat &input_img);

#endif