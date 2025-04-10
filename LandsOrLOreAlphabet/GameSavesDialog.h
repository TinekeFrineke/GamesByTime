#pragma once


// GameSavesDialog dialog

class GameSavesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(GameSavesDialog)

public:
	GameSavesDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GameSavesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LANDSORLOREALPHABET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
