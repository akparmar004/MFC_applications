
// SmartGymTrackerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SmartGymTracker.h"
#include "SmartGymTrackerDlg.h"
#include "afxdialogex.h"
#include "afxbutton.h"
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSmartGymTrackerDlg dialog



CSmartGymTrackerDlg::CSmartGymTrackerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SMARTGYMTRACKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	conn = nullptr;
}

void CSmartGymTrackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, btn_add);
	DDX_Control(pDX, IDC_BTN_LOAD,btn_load);
	DDX_Control(pDX, IDC_BTN_EDIT, btn_edit);
	DDX_Control(pDX, IDC_BTN_DELETE, btn_delete);
	DDX_Control(pDX, IDOK, btn_ok);
	DDX_Control(pDX, IDCANCEL, btn_cancel);
}

BEGIN_MESSAGE_MAP(CSmartGymTrackerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CSmartGymTrackerDlg::OnBnClickedAddMember)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CSmartGymTrackerDlg::OnBnClickedLoadMembers)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CSmartGymTrackerDlg::OnBnClickedDeleteMember)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CSmartGymTrackerDlg::OnBnClickedEditMember)
END_MESSAGE_MAP()


// CSmartGymTrackerDlg message handlers

BOOL CSmartGymTrackerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//connect to database
	connect();

	//set fonts of static texts
	setfont();

	//adding options to combo boxes
	addOptions();

	//init columns
	addColumns();

	// TODO: Add extra initialization here
	m_brush.CreateSolidBrush(RGB(255, 255, 255));
	blue.CreateSolidBrush(RGB(0,0,255));

	light_blue.CreateSolidBrush(RGB(173, 216, 230));

	styleButton();

	return TRUE;
}

void CSmartGymTrackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CSmartGymTrackerDlg::OnPaint()
{
	CPaintDC dc(this);
	if (IsIconic())
	{
		 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CSmartGymTrackerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSmartGymTrackerDlg::connect()
{
	
	conn = mysql_init(NULL);

	if (conn == NULL)
	{
		AfxMessageBox(_T("MySQL connectio failed!"));
		return;
	}

	conn = mysql_real_connect(conn, "localhost", "root", "akp000000", "gymdb", 3306, NULL, 0);
}

void CSmartGymTrackerDlg::setfont()
{
	//setting the fonts of static texts
	m_titleFont.CreatePointFont(220, _T("TIMES NEW ROMAN BOLD"));
	m_member_titleFont.CreatePointFont(160, _T("Arial Bold"));
	m_static.CreatePointFont(120, _T("Arial Bold"));

	//main title
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&m_titleFont);

	//form titles
	GetDlgItem(IDC_STATIC_MANAGEMENT)->SetFont(&m_member_titleFont);
	GetDlgItem(IDC_STATIC_LIST)->SetFont(&m_member_titleFont);

	GetDlgItem(IDC_STATIC1)->SetFont(&m_static);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_static);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_static);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_static);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_static);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_static);
}

void CSmartGymTrackerDlg::addOptions()
{
	CComboBox* gender = (CComboBox*)GetDlgItem(IDC_COMBO_GENDER);
	gender->AddString(_T("Male"));
	gender->AddString(_T("Female"));
	gender->AddString(_T("Other"));

	CComboBox* membership = (CComboBox*)GetDlgItem(IDC_COMBO_MEMBERSHIP);
	membership->AddString(_T("Basic"));
	membership->AddString(_T("Premium"));
	membership->AddString(_T("VIP"));
}

void CSmartGymTrackerDlg::addColumns()
{
	m_memberlist.SubclassDlgItem(IDC_LIST_MEMBERS, this);

	m_memberlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_memberlist.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_memberlist.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	m_memberlist.InsertColumn(2, _T("Age"), LVCFMT_LEFT, 50);
	m_memberlist.InsertColumn(3, _T("Phone"), LVCFMT_LEFT, 120);
	m_memberlist.InsertColumn(4, _T("Email"), LVCFMT_LEFT, 180);
	m_memberlist.InsertColumn(5, _T("Gender"), LVCFMT_LEFT, 80);
	m_memberlist.InsertColumn(6, _T("Membership Type"), LVCFMT_LEFT, 130);
}

void CSmartGymTrackerDlg::styleButton()
{
	CMFCButton* Buttons[] = { &btn_add, &btn_edit, &btn_delete, &btn_load };

	btn_font.CreatePointFont(140, _T("TIMES NEW ROMAN BOLD "));

	for (CMFCButton* btn : Buttons)
	{
		btn->SetFont(&btn_font);
		btn->SetFaceColor(RGB(0, 102, 204), true);
		btn->SetTextColor(RGB(255, 255, 255));
		btn->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	}
	

	CMFCButton* btn = &btn_ok;
	btn -> SetFont(&btn_font);
	btn->SetFaceColor(RGB(40, 40, 40));
	btn->SetTextColor(RGB(255, 255, 255));
	btn->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;	

	btn = &btn_cancel;
	btn->SetFont(&btn_font);
	btn->SetFaceColor(RGB(40, 40, 40));
	btn->SetTextColor(RGB(255, 255, 255));
	btn->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;	
}

void CSmartGymTrackerDlg::OnBnClickedAddMember()
{
	// Get values from input fields
	CString name, age, phone, email, gender, membership;
	GetDlgItemText(IDC_EDIT_NAME, name);
	GetDlgItemText(IDC_EDIT_AGE, age);
	GetDlgItemText(IDC_EDIT_PHONE, phone);
	GetDlgItemText(IDC_EDIT_EMAIL, email);
	GetDlgItemText(IDC_COMBO_GENDER, gender);  
	GetDlgItemText(IDC_COMBO_MEMBERSHIP, membership);

	// Prepare SQL Query
	CString query;
	query.Format(_T("INSERT INTO members (Name, Age, Gender, Phone, Email, MembershipType) VALUES ('%s', %s, '%s', '%s', '%s', '%s')"),
		(LPCTSTR)name, (LPCTSTR)age, (LPCTSTR)gender, (LPCTSTR)phone, (LPCTSTR)email, (LPCTSTR)membership);

	// Execute query
	if (mysql_query(conn, CStringA(query))) {
		MessageBox(_T("Failed to add member!"), _T("Error"), MB_ICONERROR);
	}
	else {
		MessageBox(_T("Member added successfully!"), _T("Success"), MB_ICONINFORMATION);
		OnBnClickedLoadMembers();
	}
}

void CSmartGymTrackerDlg::OnBnClickedLoadMembers()
{
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST_MEMBERS);
	list->DeleteAllItems();

	CString query = _T("SELECT MemberID, Name, Age, Phone, Email, Gender, MembershipType FROM members");

	// Run query and check for errors
	if (mysql_query(conn, CT2CA(query))) {
		CString error(mysql_error(conn)); // Get MySQL error message
		MessageBox(_T("Failed to load members! Error: ") + error, _T("Error"), MB_ICONERROR);
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	MYSQL_ROW row;
	int index = 0;

	while ((row = mysql_fetch_row(res)))
	{

		int rowIndex = list->InsertItem(index, CString(row[0]));
		list->SetItemText(rowIndex, 1, CString(row[1]));
		list->SetItemText(rowIndex, 2, CString(row[2]));
		list->SetItemText(rowIndex, 3, CString(row[3]));
		list->SetItemText(rowIndex, 4, CString(row[4]));
		list->SetItemText(rowIndex, 5, CString(row[5]));
		list->SetItemText(rowIndex, 6, CString(row[6]));

		index++;
	}

	mysql_free_result(res);
}

void CSmartGymTrackerDlg::OnBnClickedDeleteMember()
{
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST_MEMBERS);
	int selected = list->GetNextItem(-1, LVNI_SELECTED);

	if (selected == -1) {
		MessageBox(_T("Please select a member to delete!"), _T("Warning"), MB_ICONWARNING);
		return;
	}

	CString memberID = list->GetItemText(selected, 0);

	CString query;
	query.Format(_T("DELETE FROM Members WHERE MemberID = %s"), (LPCTSTR)memberID);

	if (mysql_query(conn, CStringA(query))) {
		MessageBox(_T("Failed to delete member!"), _T("Error"), MB_ICONERROR);
	}
	else {
		OnBnClickedLoadMembers();
		MessageBox(_T("Member deleted successfully!"), _T("Success"), MB_ICONINFORMATION);
	}
}

void CSmartGymTrackerDlg::OnBnClickedEditMember()
{
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST_MEMBERS);

	POSITION pos = list-> GetFirstSelectedItemPosition();
	int rowIndex = list->GetNextSelectedItem(pos);
	
	CString id = list->GetItemText(rowIndex, 0);

	CString name, age, phone, email, gender, membership;
	GetDlgItemText(IDC_EDIT_NAME, name);
	GetDlgItemText(IDC_EDIT_AGE, age);
	GetDlgItemText(IDC_EDIT_PHONE, phone);
	GetDlgItemText(IDC_EDIT_EMAIL, email);
	GetDlgItemText(IDC_COMBO_GENDER, gender); 
	GetDlgItemText(IDC_COMBO_MEMBERSHIP, membership);

	CString query;
	query.Format(_T("UPDATE members SET Name='%s', Age='%s', Phone='%s', Email='%s', Gender='%s', MembershipType='%s' WHERE MemberID='%s'"),
		(LPCWSTR)name, (LPCWSTR)age, (LPCWSTR)phone, (LPCWSTR)email, (LPCWSTR)gender, (LPCWSTR)membership, id);

	if (mysql_query(conn, CT2CA(query)))
	{
		MessageBox(_T("Failed to update member!"), _T("Error"), MB_ICONERROR);
		return;
	}

	MessageBox(_T("Member updated successfully!"), _T("Success"), MB_ICONINFORMATION);
	OnBnClickedLoadMembers();
}

HBRUSH CSmartGymTrackerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)  
	{
		pDC->SetTextColor(RGB(255, 255, 255));  
		pDC->SetBkColor(RGB(0, 0, 255));
		return blue;
	}
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MANAGEMENT || pWnd->GetDlgCtrlID() == IDC_STATIC_LIST)  
	{
		pDC->SetTextColor(RGB(255, 165, 0));
		pDC->SetBkColor(RGB(0, 0, 255));
		return blue;
	}

	if(nCtlColor == CTLCOLOR_DLG)
	{
		//return light_blue;
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(RGB(0, 0, 139));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	return hbr;
}
BOOL CSmartGymTrackerDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect); 

	
	TRIVERTEX vertex[2];
	vertex[0].x = rect.left;
	vertex[0].y = rect.top;
	vertex[0].Red = 0xA000;   
	vertex[0].Green = 0xD000;
	vertex[0].Blue = 0xF000;

	vertex[1].x = rect.right;
	vertex[1].y = rect.bottom;
	vertex[1].Red = 0x5000;   
	vertex[1].Green = 0xB000;
	vertex[1].Blue = 0xE000;

	// Define the gradient area
	GRADIENT_RECT gRect = { 0, 1 };

	// Apply gradient fill
	pDC->GradientFill(vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);

	return TRUE;  // Indicate that we've handled the background drawing
}