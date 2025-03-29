#pragma once

#include "extend.h"
#include <shlobj.h>
#include <thread>

__declspec(selectany) std::string logfilename;

__declspec(selectany) std::string Path_Console = "\\Seewo Note Shot\\Settings\\console.bool";
__declspec(selectany) bool console = false;

__declspec(selectany) std::string Path_SaveWay = "\\Seewo Note Shot\\Settings\\SaveWay.int";
enum SAVEWAY
{
	PNG = 0x00000000,
	JPEG = 0x00000001,
	BMP = 0x00000002,
	TIFF = 0x00000003,
	WEBP = 0x00000004,
	AVIF = 0x00000005,
	JXL = 0x00000006
};
__declspec(selectany) SAVEWAY SaveWay;

__declspec(selectany) std::string Path_SavePath = "\\Seewo Note Shot\\Settings\\SavePath.string";
__declspec(selectany) std::string SavePath;

__declspec(selectany) int screenw;
__declspec(selectany) int screenh;
__declspec(selectany) float scaleFactor;
__declspec(selectany) int left1, top1, right1, bottom1;
__declspec(selectany) int left2, top2, right2, bottom2;

inline void OutLog(std::string str);

void init();
void quit();

void Shot();