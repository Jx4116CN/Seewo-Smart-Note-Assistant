#pragma once

#include "extend.h"
#include <fstream>
#include <shlobj.h>

//using namespace std;

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

void init();