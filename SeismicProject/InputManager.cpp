#include"OGLCanvas.h"
#include<memory>

InputManager::InputManager(wxGLCanvas* parent)
{
	ParentWindow = parent;

	Mouse = { 0, 0, 0, 0, true };

	InputMap["A"] = Key((wxKeyCode)'A', false, false);
	InputMap["B"] = Key((wxKeyCode)'B', false, false);
	InputMap["C"] = Key((wxKeyCode)'C', false, false);
	InputMap["D"] = Key((wxKeyCode)'D', false, false);
	InputMap["E"] = Key((wxKeyCode)'E', false, false);
	InputMap["F"] = Key((wxKeyCode)'F', false, false);
	InputMap["G"] = Key((wxKeyCode)'G', false, false);
	InputMap["H"] = Key((wxKeyCode)'H', false, false);
	InputMap["I"] = Key((wxKeyCode)'I', false, false);
	InputMap["J"] = Key((wxKeyCode)'J', false, false);
	InputMap["K"] = Key((wxKeyCode)'K', false, false);
	InputMap["L"] = Key((wxKeyCode)'L', false, false);
	InputMap["M"] = Key((wxKeyCode)'M', false, false);
	InputMap["N"] = Key((wxKeyCode)'N', false, false);
	InputMap["O"] = Key((wxKeyCode)'O', false, false);
	InputMap["P"] = Key((wxKeyCode)'P', false, false);
	InputMap["Q"] = Key((wxKeyCode)'Q', false, false);
	InputMap["R"] = Key((wxKeyCode)'R', false, false);
	InputMap["S"] = Key((wxKeyCode)'S', false, false);
	InputMap["T"] = Key((wxKeyCode)'T', false, false);
	InputMap["U"] = Key((wxKeyCode)'U', false, false);
	InputMap["V"] = Key((wxKeyCode)'V', false, false);
	InputMap["W"] = Key((wxKeyCode)'W', false, false);
	InputMap["X"] = Key((wxKeyCode)'X', false, false);
	InputMap["Y"] = Key((wxKeyCode)'Y', false, false);
	InputMap["Z"] = Key((wxKeyCode)'Z', false, false);

	InputMap["UP"] = Key(WXK_UP, false, false);
	InputMap["DOWN"] = Key(WXK_DOWN, false, false);

	InputMap["RMB"] = Key(WXK_RBUTTON, false, false);
	InputMap["LMB"] = Key(WXK_LBUTTON, false, false);
	InputMap["MMB"] = Key(WXK_LBUTTON, false, false);


}

InputManager::~InputManager()
{
}

void InputManager::UpdateMouse()
{
	wxPoint mousePos = wxGetMousePosition();
	if (Mouse.First)
	{
		Mouse.LastX = mousePos.x;
		Mouse.LastY = mousePos.y;
		Mouse.First = false;
	}

	//Calculate delta
	Mouse.x = mousePos.x;
	Mouse.y = mousePos.y;
	Mouse.dx = Mouse.x - Mouse.LastX;
	Mouse.dy = Mouse.y - Mouse.LastY;

	//Set last pos
	Mouse.LastX = Mouse.x;
	Mouse.LastY = Mouse.y;
}

void InputManager::Update(wxIdleEvent& event)
{
	UpdateMouse();

	for (auto i = InputMap.begin(); i != InputMap.end(); i++)
	{
		Key key = i->second;
		if (wxGetKeyState(key.Code))
		{
			if (!key.IsPressed)
				InputMap.at(i->first).IsPressed = true;
			else
				InputMap.at(i->first).WasPressed = true;
		}
		else
		{
			if (key.IsPressed)
				InputMap.at(i->first).IsPressed = false;
			else
				InputMap.at(i->first).WasPressed = false;
		}
	}

	if (wxGetMouseState().LeftIsDown())
	{
		Key key = InputMap.at("LMB");
		if (!key.IsPressed)
			InputMap.at("LMB").IsPressed = true;
		else
			InputMap.at("LMB").WasPressed = true;
	}
	else
	{
		Key key = InputMap.at("LMB");
		if (key.IsPressed)
			InputMap.at("LMB").IsPressed = false;
		else
			InputMap.at("LMB").WasPressed = false;
	}

	if (wxGetMouseState().RightIsDown())
	{
		Key key = InputMap.at("RMB");
		if (!key.IsPressed)
			InputMap.at("RMB").IsPressed = true;
		else
			InputMap.at("RMB").WasPressed = true;
	}
	else
	{
		Key key = InputMap.at("RMB");
		if (key.IsPressed)
			InputMap.at("RMB").IsPressed = false;
		else
			InputMap.at("RMB").WasPressed = false;
	}

	if (wxGetMouseState().MiddleIsDown())
	{
		Key key = InputMap.at("MMB");
		if (!key.IsPressed)
			InputMap.at("MMB").IsPressed = true;
		else
			InputMap.at("MMB").WasPressed = true;
	}
	else
	{
		Key key = InputMap.at("MMB");
		if (key.IsPressed)
			InputMap.at("MMB").IsPressed = false;
		else
			InputMap.at("MMB").WasPressed = false;
	}
}

bool InputManager::IsKeyPressed(const char* key)
{
	if (!MouseInClient)
		return false;

	return InputMap.at(std::string(key)).IsPressed;
}

bool InputManager::IsKeyJustPressed(const char* key)
{
	if (!MouseInClient)
		return false;

	Key inputKey = InputMap.at(std::string(key));
	
	if (!inputKey.WasPressed && inputKey.IsPressed)
		return true;
	
	return false;
}

void InputManager::SetMouseInClient(bool val)
{
	MouseInClient = val;
}

bool InputManager::GetMouseInClient()
{
	return MouseInClient;
}

wxPoint InputManager::GetMousePos()
{
	return wxPoint(Mouse.x, Mouse.y);
}

wxPoint InputManager::GetMouseDelta()
{
	if (MouseInClient)
		return wxPoint(Mouse.dx, -Mouse.dy);
	else
		return wxPoint(0, 0);
}

wxPoint InputManager::GetCapturedMouseDelta()
{
	OGLCanvas* canvas = static_cast<OGLCanvas*>(ParentWindow);
	//UpdateMouse();
	//canvas->WarpPointer(Mouse.LastX, Mouse.LastY);

	if (MouseInClient)
		return wxPoint(Mouse.dx, -Mouse.dy);
	else
		return wxPoint(0, 0);
}
