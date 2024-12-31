
// LicPlateDetDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LicPlateDet.h"
#include "LicPlateDetDlg.h"
#include "afxdialogex.h"
#include <opencv2/highgui/highgui_c.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLicPlateDetDlg 对话框



CLicPlateDetDlg::CLicPlateDetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LICPLATEDET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLicPlateDetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_VID, IDC_VID);
	DDX_Control(pDX, IDC_FRAME, frame);
	DDX_Control(pDX, IDC_LIC, lic);
	DDX_Control(pDX, IDC_CHAR0, char0_box);
	DDX_Control(pDX, IDC_CHAR1, char1_box);
	DDX_Control(pDX, IDC_CHAR2, char2_box);
	DDX_Control(pDX, IDC_CHAR3, char3_box);
	DDX_Control(pDX, IDC_CHAR4, char4_box);
	DDX_Control(pDX, IDC_CHAR5, char5_box);
	DDX_Control(pDX, IDC_CHAR6, char6_box);
	DDX_Control(pDX, IDC_VIDEO, video_box);
	DDX_Control(pDX, IDC_STR, str_box);
}

BEGIN_MESSAGE_MAP(CLicPlateDetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CLicPlateDetDlg::OnBnClickedBtnOpen)
	//ON_STN_CLICKED(IDC_VID, &CLicPlateDetDlg::OnStnClickedVid)
	ON_BN_CLICKED(IDC_BTN_DETECT, &CLicPlateDetDlg::OnBnClickedBtnDetect)
END_MESSAGE_MAP()


// CLicPlateDetDlg 消息处理程序

BOOL CLicPlateDetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//----------------------------【自定义代码处】--------------------------------------
	CWnd  *pWnd1 = GetDlgItem(IDC_VIDEO);//CWnd是MFC窗口类的基类,提供了微软基础类库中所有窗口类的基本功能。
	pWnd1->GetClientRect(&rect_vid);//GetClientRect为获得控件相自身的坐标大小
	namedWindow("idc_vid", WINDOW_AUTOSIZE);//设置窗口名
	HWND hWndl1 = (HWND)cvGetWindowHandle("idc_vid");//hWnd 表示窗口句柄,获取窗口句柄
	HWND hParent1 = ::GetParent(hWndl1);//GetParent函数一个指定子窗口的父窗口句柄
	::SetParent(hWndl1, GetDlgItem(IDC_VIDEO)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);
	//Mat srcImg = imread("License8.jpg");
	//resize(srcImg, srcImg, Size(rect_vid.Width(), rect_vid.Height()));
	//imshow("idc_vid", srcImg);

	CWnd  *pWnd2 = GetDlgItem(IDC_FRAME);
	pWnd2->GetClientRect(&rect_frame);
	namedWindow("idc_frame", WINDOW_AUTOSIZE);
	HWND hWndl2 = (HWND)cvGetWindowHandle("idc_frame");
	HWND hParent2 = ::GetParent(hWndl2);
	::SetParent(hWndl2, GetDlgItem(IDC_FRAME)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);
	//Mat srcImg2 = imread("License8.jpg");
	//resize(srcImg2, srcImg2, Size(rect2.Width(), rect2.Height()));
	//imshow("idc_frame", srcImg2);

	CWnd  *pWnd3 = GetDlgItem(IDC_LIC);
	pWnd3->GetClientRect(&rect_lic);
	namedWindow("idc_lic", WINDOW_AUTOSIZE);
	HWND hWndl3 = (HWND)cvGetWindowHandle("idc_lic");
	HWND hParent3 = ::GetParent(hWndl3);
	::SetParent(hWndl3, GetDlgItem(IDC_LIC)->m_hWnd);
	::ShowWindow(hParent3, SW_HIDE);
	//Mat srcImg3 = imread("License8.jpg");
	//resize(srcImg3, srcImg3, Size(rect3.Width(), rect3.Height()));
	//imshow("idc_lic", srcImg3);

	CWnd  *pWnd4 = GetDlgItem(IDC_CHAR0);
	pWnd4->GetClientRect(&rect_char0);
	namedWindow("idc_char0", WINDOW_AUTOSIZE);
	HWND hWndl4 = (HWND)cvGetWindowHandle("idc_char0");
	HWND hParent4 = ::GetParent(hWndl4);
	::SetParent(hWndl4, GetDlgItem(IDC_CHAR0)->m_hWnd);
	::ShowWindow(hParent4, SW_HIDE);

	CWnd  *pWnd5 = GetDlgItem(IDC_CHAR1);
	pWnd5->GetClientRect(&rect_char[1]);
	namedWindow("idc_char1", WINDOW_AUTOSIZE);
	HWND hWndl5 = (HWND)cvGetWindowHandle("idc_char1");
	HWND hParent5 = ::GetParent(hWndl5);
	::SetParent(hWndl5, GetDlgItem(IDC_CHAR1)->m_hWnd);
	::ShowWindow(hParent5, SW_HIDE);

	CWnd  *pWnd6 = GetDlgItem(IDC_CHAR2);
	pWnd6->GetClientRect(&rect_char[2]);
	namedWindow("idc_char2", WINDOW_AUTOSIZE);
	HWND hWndl6 = (HWND)cvGetWindowHandle("idc_char2");
	HWND hParent6 = ::GetParent(hWndl6);
	::SetParent(hWndl6, GetDlgItem(IDC_CHAR2)->m_hWnd);
	::ShowWindow(hParent6, SW_HIDE);

	CWnd  *pWnd7 = GetDlgItem(IDC_CHAR3);
	pWnd7->GetClientRect(&rect_char[3]);
	namedWindow("idc_char3", WINDOW_AUTOSIZE);
	HWND hWndl7 = (HWND)cvGetWindowHandle("idc_char3");
	HWND hParent7 = ::GetParent(hWndl7);
	::SetParent(hWndl7, GetDlgItem(IDC_CHAR3)->m_hWnd);
	::ShowWindow(hParent7, SW_HIDE);

	CWnd  *pWnd8 = GetDlgItem(IDC_CHAR4);
	pWnd8->GetClientRect(&rect_char[4]);
	namedWindow("idc_char4", WINDOW_AUTOSIZE);
	HWND hWndl8 = (HWND)cvGetWindowHandle("idc_char4");
	HWND hParent8 = ::GetParent(hWndl8);
	::SetParent(hWndl8, GetDlgItem(IDC_CHAR4)->m_hWnd);
	::ShowWindow(hParent8, SW_HIDE);

	CWnd  *pWnd9 = GetDlgItem(IDC_CHAR5);
	pWnd9->GetClientRect(&rect_char[5]);
	namedWindow("idc_char5", WINDOW_AUTOSIZE);
	HWND hWndl9 = (HWND)cvGetWindowHandle("idc_char5");
	HWND hParent9 = ::GetParent(hWndl9);
	::SetParent(hWndl9, GetDlgItem(IDC_CHAR5)->m_hWnd);
	::ShowWindow(hParent9, SW_HIDE);

	CWnd  *pWnd10 = GetDlgItem(IDC_CHAR6);
	pWnd10->GetClientRect(&rect_char[6]);
	namedWindow("idc_char6", WINDOW_AUTOSIZE);
	HWND hWndl10 = (HWND)cvGetWindowHandle("idc_char6");
	HWND hParent10 = ::GetParent(hWndl10);
	::SetParent(hWndl10, GetDlgItem(IDC_CHAR6)->m_hWnd);
	::ShowWindow(hParent10, SW_HIDE);
	//----------------------------【自定义代码处】--------------------------------------


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLicPlateDetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLicPlateDetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLicPlateDetDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//TCHAR szFilter[] = _T("图片文件 (*.jpg)|*.jpg|All Files (*.*)|*.*||");
	TCHAR szFilter[] = _T("视频文件 (*.avi)|*.avi|All Files (*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		USES_CONVERSION;
		filepath = T2A(strFilePath);
		cap.open(filepath);
		Mat cover_img;
		cap >> cover_img;
		resize(cover_img, cover_img, Size(rect_vid.Width(), rect_vid.Height()));
		imshow("idc_vid", cover_img);
	}
}

void CLicPlateDetDlg::OnBnClickedBtnDetect()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat frame;
	Mat roi_img;
	int count = 0;
	bool flag = false;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		//roi_img = frame(Range(680, 1480), Range(1020, 2220)); // 截取1200*800的窗口（原视频为3840*2160）
		roi_img = frame(Range(300, 700), Range(400, 800));//400*400

		//判断是否有车牌，若有则检测车牌
		if (has_license(roi_img))
		{
			count++;
			if (count < 20) continue;

			//检测车牌
			detector.set_image(roi_img);
			detector.lic_plate_detect();
			frame_img = detector.src_img_;
			lic_img = detector.license_img_;
			char_imgs = detector.char_imgs_;
			lic_str = detector.lic_str_.data();
			show_pic();

			flag = true;
		}

		resize(roi_img, roi_img, Size(rect_vid.Width(), rect_vid.Height()));
		imshow("idc_vid", roi_img);
		//resize(frame, frame, Size(rect_vid.Width(), rect_vid.Height()));
		//imshow("idc_vid", frame);
		waitKey(20);

		if (flag) break;//已找到车牌
	}
}


void CLicPlateDetDlg::show_pic()
{
	resize(frame_img, frame_img, Size(rect_frame.Width(), rect_frame.Height()));
	imshow("idc_frame", frame_img);

	resize(lic_img, lic_img, Size(rect_lic.Width(), rect_lic.Height()));
	imshow("idc_lic", lic_img);

	string img_name[7] = { "idc_char0", "idc_char1", "idc_char2", "idc_char3", "idc_char4",
		"idc_char5", "idc_char6" };
	for (int i = 0; i < 7; i++)
	{
		//resize(char_imgs[i], char_imgs[i], Size(rect_char[i].Width(), rect_char[i].Height()));
		imshow(img_name[i], char_imgs[i]);
	}

	str_box.SetWindowTextW(lic_str);
	
}

