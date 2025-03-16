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
void OutDateToFile(const char* path)
{
	std::ofstream file(path, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		file << "["
			<< st.wYear << "-"
			<< st.wMonth << "-"
			<< st.wDay << " "
			<< st.wHour << ":"
			<< st.wMinute << ":"
			<< st.wSecond << "."
			<< st.wMilliseconds
			<< "]";
	}
}

int OutToFile(std::string strout, const char* path)
{
	std::ofstream file(path, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		file << strout;
		file.close();
		return 0;
	}
	else return GetLastError();
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