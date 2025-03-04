
// SmartGymTrackerDlg.h : header file
//
#pragma once

#include <mysql.h>

#pragma comment(lib, "libmysql.lib")



// CSmartGymTrackerDlg dialog
class CSmartGymTrackerDlg : public CDialogEx
{
// Construction
public:
	MYSQL* conn;
	CSmartGymTrackerDlg(CWnd* pParent = nullptr);	// standard constructor
	CFont m_titleFont, m_member_titleFont, m_static, btn_font;
	CListCtrl m_memberlist;
	CBrush m_brush, blue, light_blue;
	CMFCButton btn_add, btn_edit, btn_delete, btn_load, btn_ok, btn_cancel;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMARTGYMTRACKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void connect();
	void setfont();
	void addOptions();
	void addColumns();
	void styleButton();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedAddMember();
	afx_msg void OnBnClickedLoadMembers();
	afx_msg void OnBnClickedDeleteMember();
	afx_msg void OnBnClickedEditMember();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};
