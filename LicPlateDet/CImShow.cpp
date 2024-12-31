// CImShow.cpp: 实现文件
//

#include "stdafx.h"
#include "LicPlateDet.h"
#include "CImShow.h"
#include "afxdialogex.h"


// CImShow 对话框

IMPLEMENT_DYNAMIC(CImShow, CDialogEx)

CImShow::CImShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LICPLATEDET_DIALOG, pParent)
{

}

CImShow::~CImShow()
{
}

void CImShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImShow, CDialogEx)
END_MESSAGE_MAP()


// CImShow 消息处理程序
