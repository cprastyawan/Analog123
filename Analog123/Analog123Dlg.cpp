
// Analog123Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Analog123.h"
#include "Analog123Dlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAnalog123Dlg dialog

CAnalog123Dlg::CAnalog123Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ANALOG123_DIALOG, pParent)
	, timer1(0)
	, edit_Jam(0)
	, edit_Menit(0)
	, edit_Detik(0)
	, teksMenit(_T(""))
	, teksJam(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnalog123Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JAM, edit_Jam);
	DDV_MinMaxInt(pDX, edit_Jam, 0, 12);
	DDX_Text(pDX, IDC_EDIT_MENIT, edit_Menit);
	DDV_MinMaxInt(pDX, edit_Menit, 0, 60);
	DDX_Text(pDX, IDC_EDIT_DETIK, edit_Detik);
	DDV_MinMaxInt(pDX, edit_Detik, 0, 60);
	DDX_Control(pDX, IDC_EDIT_JAM, jam_Ctrl);
	DDX_Control(pDX, IDC_EDIT_MENIT, menit_Ctrl);
	DDX_Control(pDX, IDC_EDIT_DETIK, detik_Ctrl);
}

BEGIN_MESSAGE_MAP(CAnalog123Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CAnalog123Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CAnalog123Dlg::OnBnClickedButtonTest)
//	ON_WM_ERASEBKGND()
ON_BN_CLICKED(ID_BTN_CURTIME, &CAnalog123Dlg::OnBnClickedBtnCurtime)
END_MESSAGE_MAP()


// CAnalog123Dlg message handlers

BOOL CAnalog123Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnalog123Dlg::OnPaint()
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
		this->ValidateRect(&rect);
		
	}
	else
	{
		InitializeFont();
		SetTimer(0, 1000, NULL);
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAnalog123Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAnalog123Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);
	CTime CurrentTime = CTime::GetCurrentTime();
	if (default_jam) {
		if (UpdateJam) {
			jarumDetik = CurrentTime.GetSecond();
			jarumMenit = CurrentTime.GetMinute() * 60 + CurrentTime.GetSecond();
			jarumJam = CurrentTime.GetHour() * 60 + CurrentTime.GetMinute();
		}
	}
	CClientDC dc(this);
	UpdateJam = FALSE;
	CBrush brush;
	CRect tempatDigitalRect;
	CWnd *tempatDigitalWnd = GetDlgItem(ID_JAM_DIGITAL);
	tempatDigitalWnd->GetWindowRect(&tempatDigitalRect);
	ScreenToClient(&tempatDigitalRect);

	dc.SetBkColor(RGB(240, 240, 240));
	CString digitalDetik;
	if (jarumDetik >= 10) digitalDetik.Format(_T("%d"), jarumDetik); 
	else digitalDetik.Format(_T("0%d"), jarumDetik);
	CString digitalMenit;
	if (jarumMenit >= 10*60) digitalMenit.Format(_T("%d"), jarumMenit / 60); 
	else digitalMenit.Format(_T("0%d"), jarumMenit / 60);
	CString digitalJam;
	if (jarumJam >= 10*60) digitalJam.Format(_T("%d"), jarumJam / 60);
	else digitalJam.Format(_T("0%d"), jarumJam / 60 );
	CFont* def_font = dc.SelectObject(&font);
	CString jamDigital;
	jamDigital.Format(_T(" %s:%s:%s "), digitalJam, digitalMenit, digitalDetik);
	dc.TextOutW(tempatDigitalRect.CenterPoint().x-100, tempatDigitalRect.CenterPoint().y-25, jamDigital, 10);
	dc.SelectObject(def_font);

	CRect tempatjamRect;
	CWnd *tempatjamWnd = GetDlgItem(ID_TEMPAT_JAM);
	tempatjamWnd->GetWindowRect(&tempatjamRect);
	ScreenToClient(&tempatjamRect);
	int centerx = tempatjamRect.CenterPoint().x;
	int centery = tempatjamRect.CenterPoint().y;
	int lengthdetik = 80;
	int lengthmenit = 70;
	int lengthjam = 50;
	Ellipse(dc,centerx - 5, centery - 5, centerx + 5, centery + 5);
	CBrush mybrush(RGB(240, 240, 240));
	SelectObject(dc, mybrush);
	Ellipse(dc,tempatjamRect.left + 30, tempatjamRect.top + 30, tempatjamRect.right - 30, tempatjamRect.bottom - 30);
	Ellipse(dc,tempatjamRect.left + 31, tempatjamRect.top + 31, tempatjamRect.right - 31, tempatjamRect.bottom - 31);
	Ellipse(dc,tempatjamRect.left + 32, tempatjamRect.top + 32, tempatjamRect.right - 32, tempatjamRect.bottom - 32);
	Ellipse(dc, tempatjamRect.left + 33, tempatjamRect.top + 33, tempatjamRect.right - 33, tempatjamRect.bottom - 33);
	dc.TextOutW(centerx - 10, tempatjamRect.top + 36, L"12");
	dc.TextOutW(tempatjamRect.left + 36, centery - 10, L"9");
	dc.TextOutW(centerx - 5, tempatjamRect.bottom - 50, L"6");
	dc.TextOutW(tempatjamRect.right - 45, centery - 5, L"3");

	CPen pDetik;
	CPen pMenit;
	CPen pJam;
	pDetik.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	pMenit.CreatePen(PS_SOLID, 3, RGB(24, 171, 92));
	pJam.CreatePen(PS_SOLID, 3, RGB(21, 52, 174));
	dc.FillSolidRect(centerx - 5, centery - 5, 10, 10, RGB(0, 0, 0));

	CPen* pOldPen = dc.SelectObject(&pDetik);
	
	dc.MoveTo(centerx, centery);
	LineTo(dc, centerx + (lengthdetik * cos((double)(jarumDetik * 6 - 135) / 57.3) - lengthdetik * sin((double)(jarumDetik * 6 - 135) / 57.3)), centery + (lengthdetik * sin((double)(jarumDetik * 6 - 135) / 57.3) + lengthdetik * cos((double)(jarumDetik * 6 - 135) / 57.3)));
	SelectObject(dc,pOldPen);

	//Menit
	pOldPen = dc.SelectObject(&pMenit);
	dc.MoveTo(centerx, centery);
	LineTo(dc,centerx + (lengthmenit * cos((double)(jarumMenit * 0.1 - 135) / 57.3) - lengthmenit * sin((double)(jarumMenit * 0.1 - 135) / 57.3)), centery + (lengthmenit * sin((double)(jarumMenit * 0.1 - 135) / 57.3) + lengthmenit * cos((double)(jarumMenit * 0.1 - 135) / 57.3)));
	SelectObject(dc,pOldPen);

	//JAM
	pOldPen = dc.SelectObject(&pJam);
	dc.MoveTo(centerx, centery);
	LineTo(dc,centerx + (lengthjam * cos((double)(jarumJam * 0.5 - 135) / 57.3) - lengthjam * sin((double)(jarumJam * 0.5 - 135) / 57.3)), centery + (lengthjam * sin((double)(jarumJam * 0.5 - 135) / 57.3) + lengthjam * cos((double)(jarumJam * 0.5 - 135) / 57.3)));
	SelectObject(dc,pOldPen);
	jarumDetik++;
	jarumMenit++;
	
	if (jarumDetik > 59) {
		jarumDetik = 0;
		jarumJam++;
	}
	if (jarumMenit >= 60 * 60) {
		jarumMenit = 0;
	}
	if (jarumJam >= 60 * 24) jarumJam = 0;
	//if (jarumJam > 59) jarumJam = 0;
}

void CAnalog123Dlg::setJam(int jam, int detik, int menit) {
	SetTimer(0, 1000, NULL);
}

void CAnalog123Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CAnalog123Dlg::InitializeFont() {
	VERIFY(font.CreateFontW(60,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_HEAVY,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		PROOF_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Kaufmann BT")));                 // lpszFacename))
}
void CAnalog123Dlg::OnBnClickedButtonTest()
{
	default_jam = FALSE;
	CString teksJam=_T("");
	CString teksMenit = _T("");
	CString teksDetik = _T("");
	jam_Ctrl.GetWindowTextW(teksJam);
	menit_Ctrl.GetWindowTextW(teksMenit);
	detik_Ctrl.GetWindowTextW(teksDetik);
	int detik = _ttoi(teksDetik);
	int menit = _ttoi(teksMenit);
	int jam = _ttoi(teksJam);
	if (!teksJam.IsEmpty() && !teksMenit.IsEmpty() && !teksDetik.IsEmpty()) {
		if ((detik < 60 && detik >= 0) && (menit < 60 && menit >= 0) && (jam < 24 && jam >= 0)) {
			jarumDetik = detik;
			jarumMenit = menit * 60 + detik;
			jarumJam = jam * 60 + menit;
		}
		else MessageBox(_T("Cek Teks Boks!"), _T("ERROR!"), MB_OK);
	}
	else MessageBox(_T("Tidak Boleh Kosong!"), _T("ERROR!"), MB_OK);
	// TODO: Add your control notification handler code here
}

void CAnalog123Dlg::OnBnClickedBtnCurtime()
{
	default_jam = TRUE;
	UpdateJam = TRUE;
	// TODO: Add your control notification handler code here
}
