#include "Class_Console.h"

Console::Console()
{
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		Alloc = true;
	}
	else
		Alloc = false;

	outDate = true;
}

Console::~Console()
{
	FreeConsole();
}

void Console::OutDate()
{
	std::time_t now = std::time(nullptr);

	std::tm* localTime = std::localtime(&now);

	std::cout << "["
		<< localTime->tm_year + 1900 << "-"
		<< localTime->tm_mon + 1 << "-"
		<< localTime->tm_mday << " "
		<< localTime->tm_hour << ":"
		<< localTime->tm_min << ":"
		<< localTime->tm_sec << "]";
}