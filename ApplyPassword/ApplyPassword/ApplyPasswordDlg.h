// ApplyPasswordDlg.h : header file
//

#pragma once


// CApplyPasswordDlg dialog
class CApplyPasswordDlg : public CDialog
{
// Construction
public:
	CApplyPasswordDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_APPLYPASSWORD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnBrowse();
};
