#include "deprecatedMainFrame.h"
#include<wx/wx.h>


deprecatedMainFrame::deprecatedMainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	SetupSizers();

	MyGraphicsCanvas = nullptr;
	wxGLAttributes vAttrs;
	vAttrs.PlatformDefaults().Defaults().EndList();

	bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);
	if (accepted)
	{
		wxMessageDialog dialog(this, "Successfully initializing OpenGL", "All is well", wxOK);
		dialog.ShowModal();
	}
	else
	{
		wxMessageDialog dialog(this, "WE'RE COOKED BRO", "Bad", wxOK);
		dialog.ShowModal();
	}

	MyGraphicsCanvas = new GraphicsCanvas(this, vAttrs);
	
}

void deprecatedMainFrame::CreateControls()
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

void deprecatedMainFrame::SetupSizers()
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


GraphicsCanvas::GraphicsCanvas(deprecatedMainFrame* parent, const wxGLAttributes& canvasAttrs)
	:wxGLCanvas(parent, canvasAttrs)
{
	parentFrame = parent;
	oglContext = nullptr;
	m_winHeight = 0; // We have not been sized yet

	wxGLContextAttrs contextAttribs;

	contextAttribs.PlatformDefaults().OGLVersion(4, 6).EndList();
	oglContext = new wxGLContext(this, nullptr, &contextAttribs);

	if (oglContext->IsOK())
	{
		wxMessageDialog dialog(parentFrame, "Bro this OGL context is working as intended!", "All is well", wxOK);
		dialog.ShowModal();
	}
	else
	{
		wxMessageDialog dialog(parentFrame, "Bro this OGL context is ASS LOL", "All is well", wxOK);
		dialog.ShowModal();
	}
}
