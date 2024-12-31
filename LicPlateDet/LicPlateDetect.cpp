#include "LicPlateDetect.h"

void LicPlateDetect::lic_plate_detect()
{
	pre_process();
	segmentation();
	cut_black_border();
	char_recognition();
}

 //Ԥ����ʶ���Ʋ������������license_img_
void LicPlateDetect::pre_process()
{
	if (src_img_.empty())
	{
		cout << "The src_img is empty." << endl;
		abort();
	}
	double scale = (double)400 / src_img_.cols;
	resize(src_img_, src_img_, Size(0, 0), scale, scale);
	
	// ��˹�˲���ȥ��
	Mat gau_img;
	GaussianBlur(src_img_, gau_img, Size(5, 5), 0, 0);

	// ��ɫ����
	Mat hsv_img, bin_img, edge_img, close_img;
	cvtColor(gau_img, hsv_img, COLOR_BGR2HSV);
	inRange(hsv_img, Scalar(100, 80, 46), Scalar(124, 255, 255), bin_img);

	// ���ؼ�⣬��ȡ���ơ���������
	Canny(bin_img, edge_img, 30, 90, 3);//��ֵ����Ҫ

	// ʹ�ÿ�����ͱ�������ͼ���Ե��Ϊһ������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 3), Point(-1, -1));
	morphologyEx(edge_img, close_img, MORPH_CLOSE, kernel, Point(-1, -1), 2);

	// ����������ı�Դͼ����Ϣ����Ҫ����ͼ��
	Mat contour_img = close_img.clone();
	//Mat contour_img = bin_img.clone();
	vector<vector<Point>> contours;
	findContours(contour_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //ֻȡ�����������ֻ�����յ�����
	cvtColor(contour_img, contour_img, COLOR_GRAY2BGR);
	drawContours(contour_img, contours, -1, Scalar(0, 0, 255), 1);

	//����Ϊ���Σ�����λ����ȡ
	for (int i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		RotatedRect rotated_rect = minAreaRect(Mat(contours[i]));
		if ((float)rect.width / rect.height >= 2.5 && (float)rect.width / rect.height <= 3.6 && rect.height > 20 && rect.height < 200) //���еľŶ�ʽ���������ƹ���ߴ����ƺͺ�����440/140=3.14
		{
			rect = rect + Size(2, 0);
			rect = rect + Point(-1, 0);
			//cout << "rect.width = " << rect.width << ", rect.height = " << rect.height << endl;
			rectangle(contour_img, rect, Scalar(0, 255, 0), 1);
			license_img_ = src_img_(rect).clone();//���泵������

			////������С����İ�Χ����
			//Point2f vertex[4];
			//rotated_rect.points(vertex);
			//for (int i = 0; i < 4; i++)
			//	line(contour_img, vertex[i], vertex[(i + 1) % 4], Scalar(255, 0, 0), 2, LINE_AA);

		}
	}

	//namedWindow("src_img_", CV_WINDOW_NORMAL);
	//imshow("src_img_", src_img_);
	//namedWindow("bin_img", CV_WINDOW_NORMAL);
	//imshow("bin_img", bin_img);
	//namedWindow("close_img", CV_WINDOW_NORMAL);
	//imshow("close_img", close_img); 
	//namedWindow("edge_img", CV_WINDOW_NORMAL);
	//imshow("edge_img", edge_img);// ��ʾͼ��
	//namedWindow("contour_img", CV_WINDOW_NORMAL);
	//imshow("contour_img", contour_img);
	//namedWindow("license_img_", CV_WINDOW_NORMAL);
	//imshow("license_img_", license_img_);
	//waitKey(0);
}

//void LicPlateDetect::pre_process()
//{
//	if (src_img_.empty())
//	{
//		cout << "The src_img is empty." << endl;
//		abort();
//	}
//	double scale = (double)400 / src_img_.cols;
//	resize(src_img_, src_img_, Size(0, 0), scale, scale);
//
//	Mat gau_img;
//	GaussianBlur(src_img_, gau_img, Size(5, 5), 0, 0);
//
//	//��ɫ����
//	Mat gray_img, bin_img, edge_img, close_img;
//	//cvtColor(gau_img, hsv_img, COLOR_BGR2HSV);
//	cvtColor(gau_img, gray_img, COLOR_BGR2GRAY);
//
//	//��ֵ��
//	//inRange(hsv_img, Scalar(100, 80, 46), Scalar(124, 255, 255), bin_img);
//	adaptiveThreshold(gray_img, bin_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, -10);
//
//	Canny(bin_img, edge_img, 400, 1200, 3);//��ֵ����Ҫ
//
//	//��̬ѧ����
//			//��̬ѧ����
//	//ͼƬ���ʹ���
//	Mat dilate_image, erode_image;
//	//�Զ��� �˽��� x ��������͸�ʴ
//	Mat elementX = getStructuringElement(MORPH_RECT, Size(9, 3));
//	Mat elementY = getStructuringElement(MORPH_RECT, Size(3, 9));
//	Point point(-1, -1);
//	dilate(edge_img, dilate_image, elementX, point, 2);
//	erode(dilate_image, erode_image, elementX, point, 4);
//	dilate(erode_image, dilate_image, elementX, point, 2);
//
//	//�Զ��� �˽��� Y ��������͸�ʴ
//
//	erode(dilate_image, erode_image, elementY, point, 1);
//	dilate(erode_image, dilate_image, elementY, point, 2);
//
//	//imshow("test", dilate_image);
//	//waitKey(1000);
//	//imwrite("dilate_image.jpg", dilate_image);
//	//��������
////ƽ������ ��ֵ�˲�
//	//Mat blurr_image;
//	//medianBlur(dilate_image, blurr_image, 15);
//	//medianBlur(blurr_image, blurr_image, 15);
//	//imshow("test", blurr_image);
//
//	close_img = dilate_image;
//
//	//
//
//	//ʹ�ÿ�����ͱ�������ͼ���Ե��Ϊһ������
//	//Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 3), Point(-1, -1));
//	//morphologyEx(edge_img, close_img, MORPH_CLOSE, kernel, Point(-1, -1), 2);
//
//	//����������ı�Դͼ����Ϣ����Ҫ����ͼ��
//	Mat contour_img = close_img.clone();
//	vector<vector<Point>> contours;
//	findContours(contour_img, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); //ֻȡ�����������ֻ�����յ�����
//	cvtColor(contour_img, contour_img, COLOR_GRAY2BGR);
//	drawContours(contour_img, contours, -1, Scalar(0, 0, 255), 1);
//
//	//����Ϊ���Σ�����λ����ȡ
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Rect rect = boundingRect(Mat(contours[i]));
//		RotatedRect rotated_rect = minAreaRect(Mat(contours[i]));
//		if ((float)rect.width / rect.height >= 2.5 && (float)rect.width / rect.height <= 3.6 && rect.height > 20 && rect.height < 100) //���еľŶ�ʽ���������ƹ���ߴ����ƺͺ�����440/140=3.14
//		{
//			rect = rect + Size(2, 0);
//			rect = rect + Point(-1, 0);
//			//cout << "rect.width = " << rect.width << ", rect.height = " << rect.height << endl;
//			rectangle(contour_img, rect, Scalar(0, 255, 0), 1);
//			license_img_ = src_img_(rect).clone();
//
//		}
//	}
//
//	namedWindow("src_img_", CV_WINDOW_NORMAL);
//	imshow("src_img_", src_img_);
//	namedWindow("bin_img", CV_WINDOW_NORMAL);
//	imshow("bin_img", bin_img);
//	namedWindow("close_img", CV_WINDOW_NORMAL);
//	imshow("close_img", close_img); 
//	namedWindow("edge_img", CV_WINDOW_NORMAL);
//	imshow("edge_img", edge_img);// ��ʾͼ��
//	namedWindow("contour_img", CV_WINDOW_NORMAL);
//	imshow("contour_img", contour_img);
//	namedWindow("license_img_", CV_WINDOW_NORMAL);
//	//imshow("license_img_", license_img_);
//	waitKey(0);
//}

// �ָ�ƣ���ÿ���ַ��ָ�������õ�char_imgs_
void LicPlateDetect::segmentation()
{
	if (license_img_.empty())
	{
		cout << "The src_img is empty." << endl;
		abort();
	}
	Mat bin_img;
	license_img_src = license_img_.clone();
	GaussianBlur(license_img_, license_img_, Size(3, 3), 0, 0);
	cvtColor(license_img_, bin_img, COLOR_RGB2GRAY);

	// ����Ӧ��ֵ�����õ���ֵͼ��
	//adaptiveThreshold(bin_img, bin_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, -10);
	adaptiveThreshold(bin_img, bin_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, -5);

	get_vertical_img(bin_img);

	get_horizontal_img();

	//namedWindow("bin_img", CV_WINDOW_NORMAL);
	//imshow("bin_img", bin_img);
	////waitKey(1);
}

// ˮƽͶӰ��ֻ���������ֵĲ���
void LicPlateDetect::get_vertical_img(Mat &image)
{
	int height = image.rows, width = image.cols;//ͼ��ĸߺͿ�
	int tmp = 0;//���浱ǰ�е�255��Ŀ
	int *wp_num_arr = new int[height];//����ÿһ��255��Ŀ������
	int turn_num = 0;//���浱ǰ���ɺڱ�׵Ĵ���
	int *turn_num_arr = new int[height];//����ÿһ���ɺڱ�׵Ĵ���

	//ѭ������ͼ�����ݣ�����ÿһ�е�255�����Ŀ
	for (int i = 0; i < height; ++i)
	{
		tmp = 0; 
		turn_num = 0;
		for (int j = 0; j < width; ++j)
		{
			if (image.at<uchar>(i, j) == 255)
			{
				++tmp;
				if (j >= 1) { if (image.at<uchar>(i, j - 1) == 0) turn_num++; }
			}
		}
		wp_num_arr[i] = tmp;
		turn_num_arr[i] = turn_num;
	}

	// ȥ�룬���׵��ٵĵط��Ͽ�
	for (int i = 0; i < height; i++)
	{
		if (wp_num_arr[i] < 5) wp_num_arr[i] = 0;
		//if (turn_num_arr[i] < 5) wp_num_arr[i] = 0; //�仯����̫��
	}

	//���ݿ��ʶ����������
	vector<OneDimRegion> parts;
	int begin, end, current_length = 0;
	for (int i = 0; i < height; i++)
	{
		if (wp_num_arr[i] == 0 && current_length == 0) continue;
		else if (wp_num_arr[i] != 0 && current_length == 0)
		{
			begin = i;
			current_length++;
		}
		else if (wp_num_arr[i] != 0 && current_length != 0) current_length++;
		else if ((wp_num_arr[i] == 0 || i == height - 1) && current_length != 0) //�Ͽ����ߵ�ͷ��
		{
			end = i - 1;
			OneDimRegion current_region(begin, end);
			parts.push_back(current_region);
			current_length = 0;
			begin = 0;
			end = 0;
		}
	}
	int char_part = 0;
	for (int i = 0; i < parts.size(); i++)
	{
		if (parts[i].length > parts[char_part].length) char_part = i; // ����������������������
	}
	begin = parts[char_part].begin;
	end = parts[char_part].end;
	Rect rect(Point(0, begin), Point(width, end + 1));
	vertical_img_ = image(rect);
	
	//vertical_img_color_ = license_img_src(rect).clone();//ԭͼ�е�����
	//Mat mat1;
	////Canny(vertical_img_color_, mat1, 50, 150, 3);//��ֵ����Ҫ
	//cvtColor(vertical_img_color_, mat1, COLOR_RGB2GRAY);
	//threshold(mat1, mat1, 90, 255, THRESH_BINARY);

	//����������ˮƽͶӰͼ��
	Mat projImg(height, width, CV_8U, cv::Scalar(255));

	for (int i = 0; i < height; ++i)
	{
		cv::line(projImg, cv::Point(wp_num_arr[i], i), cv::Point(width - 1, i), cv::Scalar::all(0));
	}

	Mat projImg1(height, width, CV_8U, cv::Scalar(255));

	for (int i = 0; i < height; ++i)
	{
		cv::line(projImg1, cv::Point(turn_num_arr[i], i), cv::Point(width - 1, i), cv::Scalar::all(0));
	}

	//namedWindow("projImg", CV_WINDOW_NORMAL);
	//imshow("projImg", projImg);// ��ʾͼ��
	//namedWindow("projImg1", CV_WINDOW_NORMAL);
	//imshow("projImg1", projImg1);// ��ʾͼ��
	//namedWindow("vertical_img", CV_WINDOW_NORMAL);
	//imshow("vertical_img", vertical_img_);

	delete[] wp_num_arr;//ɾ��new����

}

// ��ֱͶӰ����ȡÿ������
void LicPlateDetect::get_horizontal_img()
{
	Mat show_img = vertical_img_.clone();
	cvtColor(show_img, show_img, COLOR_GRAY2BGR);//ת�ɲ�ɫͼ���ɻ���ɫ��
	int height = vertical_img_.rows, width = vertical_img_.cols;//ͼ��ĸߺͿ�
	int tmp = 0;//���浱ǰ�е�255��Ŀ
	int *wp_num_arr = new int[width];//����ÿһ��255��Ŀ������

	//ѭ������ͼ�����ݣ�����ÿһ�е�255�����Ŀ
	for (int i = 0; i < width; ++i)
	{
		tmp = 0;
		for (int j = 0; j < height; ++j)
		{
			if (vertical_img_.at<uchar>(j, i) == 255)
			{
				++tmp;
			}
		}
		wp_num_arr[i] = tmp;
	}

	//���ݿ��ʶ����������
	vector<OneDimRegion> parts;
	int begin, end, current_length = 0;
	for (int i = 0; i < width; i++)
	{
		if (wp_num_arr[i] == 0 && current_length == 0) continue;
		else if (wp_num_arr[i] != 0 && current_length == 0)
		{
			begin = i;
			current_length++;
		}
		else if (wp_num_arr[i] != 0 && current_length != 0) current_length++;
		if ((wp_num_arr[i] == 0 || i == width - 1) && current_length != 0) //�Ͽ����ߵ�ͷ��
		{
			end = (i == width - 1) ? i + 1 : i;
			OneDimRegion current_region(begin, end);
			parts.push_back(current_region);
			current_length = 0;
			begin = 0;
			end = 0;
		}
	}

	for (int i = 0; i < parts.size(); i++)
	{
		// ��������߿��Ϊ2��ȷ���ǲ������֣�������ɾ����ÿ��������һ������
		double scale = (double)height / parts[i].length;
		//cout << "parts[" << i << "] scale:" << scale << "; width:" << parts[i].length << endl;
		if (scale <= 1.6 || scale >= 2.5) // ����̫ϸ�������Ϊ��1���㡢����߿�
		{
			if (parts[i].center < 8 || width - parts[i].center < 8) //����߿�
			{
				parts.erase(parts.begin() + i);
				i--;
				continue;
			}

			int wp_ave_num = 0;
			for (int j = parts[i].begin; j <= parts[i].end; j++) wp_ave_num += wp_num_arr[j];
			wp_ave_num = wp_ave_num / parts[i].length;
			if (wp_ave_num < 10) // ��
			{
				parts.erase(parts.begin() + i);
				i--;
				continue;
			}

			//��1�����������Ӻڿ�
			int length = floor(height / 2);
			int half = floor((length - parts[i].length) / 2);
			parts[i].begin = parts[i].begin - half;
			parts[i].end = parts[i].end + half;
			parts[i].length = parts[i].length + half + half;
		}
		begin = parts[i].begin;
		end = parts[i].end;
		if (i == 0) { begin -= 1; end += 1; }
		Rect rect(Point(begin, 0), Point(end, height));
		Mat char_img = vertical_img_(rect);
		char_imgs_.push_back(char_img);

		rectangle(show_img, rect, Scalar(0, 255, 0), 1);
	}

	//���������ƴ�ֱͶӰͼ��
	Mat projImgV(height, width, CV_8U, cv::Scalar(255));

	for (int i = 0; i < width; ++i)
	{
		cv::line(projImgV, cv::Point(i, 0), cv::Point(i, height - wp_num_arr[i] - 1), cv::Scalar::all(0));
	}

	//namedWindow("projImgV", CV_WINDOW_NORMAL);
	//imshow("projImgV", projImgV);// ��ʾͼ��
	//namedWindow("show_img", CV_WINDOW_NORMAL);
	//imshow("show_img", show_img);
	//waitKey(1);

	delete[] wp_num_arr;//ɾ��new����
}

// �ü��ڱ�
void LicPlateDetect::cut_black_border()
{
	for (int index = 1; index < char_imgs_.size(); index++)
	{
		Mat char_img = char_imgs_[index];
		int height = char_img.rows, width = char_img.cols;//ͼ��ĸߺͿ�
		int tmp = 0;//���浱ǰ�е�255��Ŀ
		int *wp_num_arr = new int[height];//����ÿһ��255��Ŀ������

		//ѭ������ͼ�����ݣ�����ÿһ�е�255�����Ŀ
		for (int i = 0; i < height; ++i)
		{
			tmp = 0;
			for (int j = 0; j < width; ++j)
			{
				if (char_img.at<uchar>(i, j) == 255)
				{
					++tmp;
				}
			}
			wp_num_arr[i] = tmp;
		}

		int first = 0, last = height;
		for (int i = 0; i < height - 1; ++i)
		{
			if (wp_num_arr[0] != 0) break;
			if (wp_num_arr[i] == 0 && wp_num_arr[i + 1] != 0)
			{
				first = i + 1;
				break;
			}
		}
		for (int i = height - 1; i > 0; --i)
		{
			if (wp_num_arr[height - 1] != 0) break;
			if (wp_num_arr[i] == 0 && wp_num_arr[i - 1] != 0)
			{
				last = i - 1;
				break;
			}
		}

		Mat char_area = char_img(Rect(Point(0, first), Point(width, last))).clone();
		//namedWindow("src", CV_WINDOW_NORMAL);
		//imshow("src", char_img);
		//namedWindow("after_cut", CV_WINDOW_NORMAL);
		//imshow("after_cut", char_area);
		//waitKey(0);
		char_imgs_[index] = char_area;
	}
	
}

// char_imgs_�е��ַ�ʶ��ģ��ƥ�䷨
void LicPlateDetect::char_recognition()
{
	//��ȡģ��
	string c[34] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
					"A", "B", "C", "D", "E", "F", "G", "H", "J",
					"K", "L", "M", "N", "P", "Q", "R", "S", "T",
					"U", "V", "W", "X", "Y", "Z" };
	string cc[31] = { "��", "��", "��", "��", "��", "��", "��", "��", "��",
					"��", "��", "��", "��", "��", "��", "³", "��", "��",
					"��", "��", "��", "��", "��", "��", "��", "��", "��", 
					"ԥ", "��", "��", "��" };
	//string cc[10] = { "��", "��", "��", "³", "��", "��", "��", "��", "��", "��"};
	string prefix = "model/";
	string suffix = ".bmp";
	string filename;
	
	// ����ģ��ͼƬ
	vector<Mat> models;
	for (int i = 0; i < 34; i++)
	{
		filename = prefix + c[i] + suffix;
		Mat model = imread(filename, 0);    // ��ȡ��Ӧ·����ͼ��
		if (model.empty())
		{
			cout << "The image is not load." << endl;
			abort();
		}
		models.push_back(model);
	}
	vector<Mat> cmodels;
	for (int i = 0; i < 31; i++)
	{
		filename = prefix + cc[i] + suffix;
		Mat cmodel = imread(filename, 0);    // ��ȡ��Ӧ·����ͼ��
		if (cmodel.empty())
		{
			cout << "The image is not load." << endl;
			abort();
		}
		cmodels.push_back(cmodel);
	}

	// ʶ���ַ�
	for (int i = 0; i < char_imgs_.size(); i++)
	{
		Mat char_img = char_imgs_[i].clone();
		resize(char_img, char_img, Size(20, 40));
		//namedWindow("char_img", CV_WINDOW_NORMAL);
		//imshow("char_img", char_img);
		//waitKey(0);

		int index;
		double min_dist = 1.0e10;

		// ��һ���ַ�������,����ʶ���ʱȽϵ�
		if (i == 0)
		{
			for (int j = 0; j < 31; j++)
			{
				double dist = distance_c(char_img, cmodels[j]);
				if (dist <= min_dist)
				{
					min_dist = dist;
					index = j;
				}
			}
			char_res_.insert(char_res_.begin(), cc[index]);//������
			lic_str_ = cc[index];
			//cout << char_res_[0] ;
			continue;
		}
		// �ڶ����ַ�һ������ĸ
		else if (i == 1)
		{
			for (int j = 10; j < 34; j++)
			{
				double dist = distance(char_img, models[j]);
				if (dist <= min_dist)
				{
					min_dist = dist;
					index = j;
				}
			}
		}
		else if (i > 1)
		{
			for (int j = 0; j < 34; j++)
			{
				double dist = distance(char_img, models[j]);
				if (dist <= min_dist)
				{
					min_dist = dist;
					index = j;
				}
			}
		}

		char_res_.insert(char_res_.begin() + i, c[index]);//������
		lic_str_ += c[index];
		//cout << char_res_[i];
	}
	//cout << endl;
}


// ģ��ƥ�䷨��ͼ����롪��Ӣ���ַ�������
double LicPlateDetect::distance(Mat m1, Mat m2)
{
	if (m1.size() != m2.size())
	{
		cout << "The two mats for calculating distance is not the same size." << endl;
		abort();
	}
	double sum = 0;
	int width = m1.cols, height = m1.rows;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			double diff = m1.at<uchar>(i, j) - m2.at<uchar>(i, j);
			//sum += abs(diff);
			sum += pow(diff, 2);
		}

	return sum;
}

// ģ��ƥ�䷨��ͼ����롪������
double LicPlateDetect::distance_c(Mat m1, Mat m2)
{
	if (m1.size() != m2.size())
	{
		cout << "The two mats for calculating distance is not the same size." << endl;
		abort();
	}
	double sum = 0;
	int width = m1.cols, height = m1.rows;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if ((m1.at<uchar>(i, j) == 0 && m2.at<uchar>(i, j) != 0)
				|| (m1.at<uchar>(i, j) != 0 && m2.at<uchar>(i, j) == 0)) sum += 1;
		}
	return sum;
}

// �ж���Ƶ���Ƿ��г���
bool has_license(Mat &input_img)
{
	double scale = (double)400 / input_img.cols;
	resize(input_img, input_img, Size(0, 0), scale, scale);

	// ��˹�˲���ȥ��
	Mat gau_img;
	GaussianBlur(input_img, gau_img, Size(5, 5), 0, 0);

	// ��ɫ����
	Mat hsv_img, bin_img, edge_img, close_img;
	cvtColor(gau_img, hsv_img, COLOR_BGR2HSV);
	inRange(hsv_img, Scalar(100, 80, 46), Scalar(124, 255, 255), bin_img);

	// ���ؼ�⣬��ȡ���ơ���������
	Canny(bin_img, edge_img, 30, 90, 3);//��ֵ����Ҫ

	//ʹ�ÿ�����ͱ�������ͼ���Ե��Ϊһ������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 3), Point(-1, -1));
	morphologyEx(edge_img, close_img, MORPH_CLOSE, kernel, Point(-1, -1), 2);

	//����������ı�Դͼ����Ϣ����Ҫ����ͼ��
	Mat contour_img = close_img.clone();
	vector<vector<Point>> contours;
	findContours(contour_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //ֻȡ�����������ֻ�����յ�����
	cvtColor(contour_img, contour_img, COLOR_GRAY2BGR);
	drawContours(contour_img, contours, -1, Scalar(0, 0, 255), 1);

	//����Ϊ���Σ�����λ����ȡ
	for (int i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		RotatedRect rotated_rect = minAreaRect(Mat(contours[i]));
		if ((float)rect.width / rect.height >= 2.5 && (float)rect.width / rect.height <= 3.6 && rect.height > 20 && rect.height < 100) //���еľŶ�ʽ���������ƹ���ߴ����ƺͺ�����440/140=3.14
			return true;
	}

	return false;
}