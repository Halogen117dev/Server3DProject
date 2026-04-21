#include "Input.h"

Input::Input()
{
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

}

Input::~Input()
{
}

void Input::Update(wxIdleEvent& event)
{
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if (wxGetKeyState((wxKeyCode)i))
		{
			if (!InputMap.at(std::string({i})).IsPressed)
			{
				InputMap.at(std::string({ i })).IsPressed = true;
			}
			else
			{
				InputMap.at(std::string({ i })).WasPressed = true;
			}

		}
		else
		{
			if (InputMap.at(std::string({ i })).IsPressed)
			{
				InputMap.at(std::string({ i })).IsPressed = false;
			}
			else
			{
				InputMap.at(std::string({ i })).WasPressed = false;
			}
		}
	}


}

bool Input::IsKeyPressed(const char* key)
{
	return InputMap.at(std::string(key)).IsPressed;
}

bool Input::IsKeyJustPressed(const char* key)
{
	Key inputKey = InputMap.at(std::string(key));
	
	if (!inputKey.WasPressed && inputKey.IsPressed)
		return true;
	
	return false;
}
