#pragma once
#include<wx/wx.h>

class App : public wxApp
{
public:
	App() {};

	bool OnInit() override;
	int OnExit() override;
};

