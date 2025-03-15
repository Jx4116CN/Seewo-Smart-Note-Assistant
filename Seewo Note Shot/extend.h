#pragma once
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>

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