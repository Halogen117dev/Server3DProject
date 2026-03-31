#pragma once
#include<wx/wx.h>

class MainFrame;

class App : public wxApp
{
public:
	App() {};

	bool OnInit() override;
	int OnExit() override;

private:
	MainFrame* MyFrame = nullptr;
};

