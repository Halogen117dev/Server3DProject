#include"App.h"
#include"MainFrame.h"
#include"OGLCanvas.h"

//#include<wx/wx.h>
//#include<wx/wx.h>
//#include<glad/glad.h> //must be included before glCanvas.h
//#include<wx/glcanvas.h>
//#include<math.h>

wxIMPLEMENT_APP(App);

MainFrame* frame;

bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    frame = new MainFrame("Hello OpenGL");
    frame->Show(true);

    return true;
}
int App::OnExit()
{
    return 1;
}