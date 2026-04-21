#pragma once
#include<wx/wx.h>

#include<string>
#include<unordered_map>

class Input
{
public:
	Input();
	~Input();

private:
	struct Key
	{
		wxKeyCode Code;
		bool IsPressed;
		bool WasPressed;
	};

	std::unordered_map<std::string, Key> InputMap;


public:
	void Update(wxIdleEvent& event);

	bool IsKeyPressed(const char* key);
	bool IsKeyJustPressed(const char* key);
};

