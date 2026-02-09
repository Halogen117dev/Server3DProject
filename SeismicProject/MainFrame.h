#pragma once
#include<wx/wx.h>

class MainFrame: public wxFrame
{
public:
	MainFrame(const wxString& title);
	void CreateControls();
	void SetupSizers();

private:
	wxPanel* MainPanel;
	wxPanel* InformationPanel;
	wxPanel* GraphicsPanel;
	wxPanel* LogPanel;
};

