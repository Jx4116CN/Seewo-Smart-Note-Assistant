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

bool JudgePoint(int left, int top, int right, int bottom);

#include <unordered_map>
struct QuantizedRGBColor
{
	Uint8 r, g, b;
	QuantizedRGBColor(Uint8 r, Uint8 g, Uint8 b) : r(r & 0xE0), g(g & 0xE0), b(b & 0xE0) {}
	bool operator==(const QuantizedRGBColor& other) const {
		return r == other.r && g == other.g && b == other.b;
	}
};
// ¹þÏ£º¯Êý
namespace std
{
	template<>
	struct hash<QuantizedRGBColor> {
		size_t operator()(const QuantizedRGBColor& color) const {
			return ((size_t)color.r << 16) | ((size_t)color.g << 8) | color.b;
		}
	};
}
void SDL_MaxColorInSurface(SDL_Surface* surface, Uint8& R, Uint8& G, Uint8& B);

SDL_Surface* ResizeSurface(SDL_Surface* src, int newWidth, int newHeight);

SDL_Surface* convertToGrayscaleSurface(SDL_Surface* original);