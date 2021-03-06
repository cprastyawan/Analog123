
// Analog123Dlg.h : header file
//

#pragma once


// CAnalog123Dlg dialog
class CAnalog123Dlg : public CDialog
{
// Construction
public:
	CAnalog123Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANALOG123_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
private:
public:
	bool default_jam=TRUE;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void setJam(int jam, int detik, int menit);
	void gambarJam();
	int jarumJam, jarumMenit, jarumDetik;
	int timer1;
	afx_msg void OnBnClickedOk();
	afx_msg
		void InitializeFont();
	void OnBnClickedButtonTest();
	int edit_Jam;
	int edit_Menit;
	int edit_Detik;
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool UpdateJam = TRUE;
	CEdit jam_Ctrl;
	CFont font;
	CEdit menit_Ctrl;
	CEdit detik_Ctrl;
	afx_msg void OnBnClickedBtnCurtime();
	CString teksMenit;
	CString teksJam;
};
