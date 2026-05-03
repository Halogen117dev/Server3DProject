#include"App.h"
#include"MainFrame.h"
#include"OGLCanvas.h"

//#include<wx/wx.h>
//#include<wx/wx.h>
//#include<glad/glad.h> //must be included before glCanvas.h
//#include<wx/glcanvas.h>
//#include<math.h>

wxIMPLEMENT_APP(App);


bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MyFrame = new MainFrame("Server 3D");
    MyFrame->Show(true);

    return true;
}
int App::OnExit()
{
    return 1;
}