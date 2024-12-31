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
	void lic_plate_detect();//���ӿں���
	void pre_process();
	void segmentation();
	void get_vertical_img(Mat &image);
	void get_horizontal_img();
	void cut_black_border();
	void char_recognition();
	double distance(Mat m1, Mat m2);
	double distance_c(Mat m1, Mat m2);

	Mat src_img_;//ԭͼ->resize()
	Mat license_img_;//��������,��ƽ���˲�
	Mat license_img_src;
	Mat vertical_img_; //��ֱ���򾭹��ü���ĳ���
	Mat vertical_img_color_;
	vector<Mat> char_imgs_;//ˮƽ���򾭹��ü���ĳ�����������
	vector<string> char_res_;//�ַ�ʶ����
	string lic_str_;

};

bool has_license(Mat &input_img);

#endif