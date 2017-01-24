
// PixelgrafikenDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Pixelgrafiken.h"
#include "PixelgrafikenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPixelgrafikenDlg-Dialogfeld



CPixelgrafikenDlg::CPixelgrafikenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PIXELGRAFIKEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelgrafikenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelgrafikenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_MENUSELECT()

	ON_BN_CLICKED(IDC_BUTTON1, &CPixelgrafikenDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPixelgrafikenDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPixelgrafikenDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPixelgrafikenDlg-Meldungshandler

BOOL CPixelgrafikenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol f�r dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

									// TODO: Hier zus�tzliche Initialisierung einf�gen

	return TRUE;  // TRUE zur�ckgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgef�hrt.

void CPixelgrafikenDlg::OnPaint()
{
	CPaintDC dc(this); // Ger�tekontext zum Zeichnen

	CRect rect;
	GetClientRect(&rect);
	m_dib.Draw(&dc, 0, 0, rect.Width(), rect.Height());

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, w�hrend der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CPixelgrafikenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPixelgrafikenDlg::OnBnClickedButton1()
{
	if (!m_dib.Load("bild.bmp")) {
		AfxMessageBox(L"Keine bmp-Datei");
		OnCancel();
	}
	RedrawWindow();
}


void CPixelgrafikenDlg::OnSize(UINT nType, int cx, int cy)
{
	RedrawWindow();
	CDialogEx::OnSize(nType, cx, cy);
}


void CPixelgrafikenDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	VERIFY(menu.CreatePopupMenu());
	menu.AppendMenu(MF_STRING, 1, L"Laden ...");
	menu.AppendMenu(MF_STRING, 2, L"Speichern ...");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 3, L"Aufhellen");
	menu.AppendMenu(MF_STRING, 4, L"Abdunkeln");
	menu.AppendMenu(MF_STRING, 5, L"Graustufen");
	menu.AppendMenu(MF_STRING, 6, L"Negativ");
	menu.AppendMenu(MF_STRING, 7, L"mehr Kontrast");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 8, L"Rotebene");
	menu.AppendMenu(MF_STRING, 9, L"Gr�nebene");
	menu.AppendMenu(MF_STRING, 10, L"Blauebene");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 11, L"Histogramm");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 12, L"Sch�rfen");
	menu.AppendMenu(MF_STRING, 13, L"Unsch�rfe");
	menu.AppendMenu(MF_STRING, 14, L"Emboss");
	menu.AppendMenu(MF_STRING, 15, L"Kantenerkennung");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 16, L"Flip horizontal");
	menu.AppendMenu(MF_STRING, 17, L"Flip vertikal");
	menu.AppendMenu(MF_STRING, 18, L"Schmelzen");
	menu.AppendMenu(MF_STRING, 19, L"�lgem�lde");
	menu.AppendMenu(MF_STRING, 20, L"Mosaik");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 21, L"(inverse) FFT");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
}


void CPixelgrafikenDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CDialogEx::OnMenuSelect(nItemID, nFlags, hSysMenu);
}


void CPixelgrafikenDlg::OnBnClickedButton2()
{
	int edge_matrix[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	m_dib.matrix(edge_matrix, 1, 1);
	RedrawWindow();
}


void CPixelgrafikenDlg::OnBnClickedButton3()
{
	float h[256] = { 0.f }; int x = 10, y = 105;
	CClientDC dc(this);
	m_dib.histogramm(h, 20.f);
	dc.MoveTo(x, y); dc.LineTo(x + 255 + 2, y); // Rahmen zeichnen
	dc.LineTo(x + 255 + 2, y - 101); dc.LineTo(x, y - 101); dc.LineTo(x, y);
	CPen p(PS_SOLID, 1, RGB(255, 255, 0)); dc.SelectObject(&p);
	for (int i = 0; i < 255; i++) { // Histogramm zeichnen
		dc.MoveTo(x + i + 1, y - 1);
		dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}

BOOL CPixelgrafikenDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{


	switch (wParam)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		break;
	case 21:
		break;
	default: // Do nothing
		break;
	}
	return CDialog::OnCommand(wParam, lParam);
}