// ApplyPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ApplyPassword.h"
#include "ApplyPasswordDlg.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApplyPasswordDlg dialog




CApplyPasswordDlg::CApplyPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApplyPasswordDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApplyPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CApplyPasswordDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_EXIT, &CApplyPasswordDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CApplyPasswordDlg::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CApplyPasswordDlg::OnBnClickedBtnBrowse)
END_MESSAGE_MAP()


// CApplyPasswordDlg message handlers

BOOL CApplyPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// default path
	GetDlgItem(IDC_TXT_PATH)->SetWindowTextA("C:\\Program Files (x86)\\GiD\\GiD 8.0.2\\gid.exe");

	ShowWindow(SW_SHOW);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CApplyPasswordDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CApplyPasswordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CApplyPasswordDlg::OnBnClickedBtnExit()
{
	exit(0);
}

void CApplyPasswordDlg::OnBnClickedBtnBrowse()
{
	CFileDialog FileDialog(TRUE, "*.*", NULL, OFN_HIDEREADONLY, "Exe Files:|gid.exe");
	if (FileDialog.DoModal() == IDOK) {
		CString fileName = FileDialog.GetPathName();
		const size_t fnSize = fileName.GetLength() + 1;
		char* fName = new char[fnSize];
		//MessageBox(fileName, "Path", MB_OK);
		GetDlgItem(IDC_TXT_PATH)->SetWindowTextA(fileName);
	}
}

void CApplyPasswordDlg::OnBnClickedBtnApply()
{
	// get hostname
	char hostName[128] = "";
	char host[150] = "";
	DWORD dwSize = sizeof(hostName);
	int cnf = 0;
	//char hexString[20] = "";
	if (GetComputerNameExA((COMPUTER_NAME_FORMAT)cnf, hostName, &dwSize)) {
		for(int i = 0; i < sizeof(hostName); i++) {
			hostName[i] = tolower(hostName[i]);
		}
		//sprintf_s(host, sizeof(host), "Host: %s", hostName);
		//MessageBox(host, "OK", MB_OK);
		
		char fileName[256] = "";
		GetDlgItem(IDC_TXT_PATH)->GetWindowTextA(fileName, sizeof(fileName));

		int hasExisted = checkFileExists(fileName);
		if (hasExisted) {
			//MessageBox("Exe file exists", "Check File", MB_OK);
			int isOk = patchExeFile(fileName, hostName, getLen(hostName));
			if (isOk) {
				MessageBox("Successfully!", "Apply Password", MB_OK);
				//MessageBox(hexString, "Apply Password", MB_OK);
			} else {
				MessageBox("Please Run as administrator!", "Apply Password", MB_ICONERROR | MB_OK);
			}
		} else {
			MessageBox("File gid.exe does not exist\nPlease use Browse button!", "Check File", MB_ICONERROR | MB_OK);
		}
	}
}