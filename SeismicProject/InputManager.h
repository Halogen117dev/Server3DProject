#pragma once
#include<wx/wx.h>
#include<wx/glcanvas.h>

#include<string>
#include<unordered_map>

class InputManager
{
public:
	InputManager(wxGLCanvas* parent);
	~InputManager();

private:
	wxGLCanvas* ParentWindow;

	struct Key
	{
		wxKeyCode Code;
		bool IsPressed;
		bool WasPressed;
	};

	struct MouseStruct
	{
		int x;
		int y;
		int LastX;
		int LastY;
		int dx;
		int dy;
		bool First;
	};

	std::unordered_map<std::string, Key> InputMap;

	bool MouseInClient = false;

	MouseStruct Mouse;
	void UpdateMouse();
public:
	void Update(wxIdleEvent& event);

	bool IsKeyPressed(const char* key);
	bool IsKeyJustPressed(const char* key);

	void SetMouseInClient(bool val);
	bool GetMouseInClient();

	wxPoint GetMousePos();
	wxPoint GetMouseDelta();
	wxPoint GetCapturedMouseDelta();
};

