
// LicPlateDetDlg.h: 头文件
//
#include "CImShow.h"
#include "LicPlateDetect.h"
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;

#pragma once


// CLicPlateDetDlg 对话框
class CLicPlateDetDlg : public CDialogEx
{
// 构造
public:
	CLicPlateDetDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LICPLATEDET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnDetect();
	void show_pic();

	char* filepath;
	CRect rect_vid, rect_frame, rect_lic, rect_char0, rect_char1, rect_char2,
		rect_char3, rect_char4, rect_char5, rect_char6;
	CRect rect_char[7];
	//CStatic IDC_VID;
	CImShow video_box;
	CImShow frame;
	CImShow lic;
	CImShow char0_box;
	CImShow char1_box;
	CImShow char2_box;
	CImShow char3_box;
	CImShow char4_box;
	CImShow char5_box;
	CImShow char6_box;
	CStatic str_box;

	LicPlateDetect detector;
	VideoCapture cap;
	Mat frame_img, lic_img;
	vector<Mat> char_imgs;
	CString lic_str;

};
