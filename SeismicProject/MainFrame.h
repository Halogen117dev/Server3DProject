#pragma once
#include<wx/wx.h>

#include<wx/glcanvas.h>

class GraphicsCanvas;

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

	wxString     m_OGLString;
	GraphicsCanvas* MyGraphicsCanvas;
};

class GraphicsCanvas : public wxGLCanvas
{
public:
	GraphicsCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs);
	//~GraphicsCanvas();

	//Init the OpenGL stuff
	bool oglInit();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnMouse(wxMouseEvent& event);

private:
	// Members
	MainFrame* parentFrame;
	wxGLContext* oglContext;
	//myOGLManager* m_oglManager;
	int           m_winHeight; // We use this var to know if we have been sized
};


