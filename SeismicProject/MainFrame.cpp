#include "MainFrame.h"
#include<wx/wx.h>
#include<wx/spinctrl.h>

#include<glad/glad.h>
#include<wx/glcanvas.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	SetupSizers();
}

void MainFrame::CreateControls()
{
	MainPanel			= new wxPanel(this, wxID_ANY);
	MainPanel->SetBackgroundColour(wxString("AQUAMARINE"));

	InformationPanel	= new wxPanel(MainPanel, wxID_ANY, wxDefaultPosition, wxSize(300, -1));
	InformationPanel->SetBackgroundColour(wxString("GOLD"));

	GraphicsPanel		= new wxPanel(MainPanel, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	GraphicsPanel->SetBackgroundColour(wxString("DARK ORCHID"));

	LogPanel			= new wxPanel(MainPanel, wxID_ANY);
	LogPanel->SetBackgroundColour(wxString("WHEAT"));
}

void MainFrame::SetupSizers()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* graphicsAndLogSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->Add(graphicsAndLogSizer, wxSizerFlags().Proportion(2).Expand());

	graphicsAndLogSizer->Add(GraphicsPanel, wxSizerFlags().Proportion(2).Expand());
	graphicsAndLogSizer->Add(LogPanel, wxSizerFlags().Proportion(1).Expand());

	mainSizer->Add(InformationPanel, wxSizerFlags().Proportion(1).Expand());
	
	MainPanel->SetSizer(mainSizer);
	mainSizer->SetSizeHints(this);
}
