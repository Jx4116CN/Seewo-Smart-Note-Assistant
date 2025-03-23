#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

void OutDate();
void OutDateToFile(const char* path);

int OutToFile(std::string strout, const char* path);

int SDL_ErrorMessageBox(_In_ Uint32 uType);
int IMG_ErrorMessageBox(_In_ Uint32 uType);

bool JudgePoint(SDL_Event* Event, int left, int top, int right, int bottom);