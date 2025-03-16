#include "extend.h"

void OutDate()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	std::cout << "["
		<< st.wYear << "-"
		<< st.wMonth << "-"
		<< st.wDay << " "
		<< st.wHour << ":"
		<< st.wMinute << ":"
		<< st.wSecond << "."
		<< st.wMilliseconds
		<< "]";
}

int SDL_ErrorMessageBox(_In_ Uint32 uType)
{
	std::string tip = SDL_GetError();
	tip += "\nError code: " + std::to_string(GetLastError());
	return MessageBox(
		NULL,
		tip.c_str(),
		"Error",
		uType);
}
int IMG_ErrorMessageBox(_In_ Uint32 uType)
{
	std::string tip = IMG_GetError();
	tip += "\nError code: " + std::to_string(GetLastError());
	return MessageBox(
		NULL,
		tip.c_str(),
		"Error",
		uType);
}