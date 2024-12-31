#pragma once


// CImShow 对话框

class CImShow : public CDialogEx
{
	DECLARE_DYNAMIC(CImShow)

public:
	CImShow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImShow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LICPLATEDET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
