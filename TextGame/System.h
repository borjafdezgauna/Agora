#pragma once

enum ConsoleColor {White, Blue, Red, Green, Yellow, Black};

class System
{
public:
	System();
	virtual ~System();

	static void Cls();
	static void HideCursor();
	static void SetCursorPos(int x, int y);
	static void SetTextColor(ConsoleColor foregroundColor
		, ConsoleColor backgroundColor= Black);
};

