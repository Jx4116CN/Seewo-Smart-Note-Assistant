#include "Init.h"

HWND hWnd = NULL;
int page_all = 1, page_this = 1, page_shot = 1;
bool click_last = false, click_next = false;

int times_open = 1;
bool is_open = false;

bool shot = false;
void GetShot()
{
again:
	if (!shot)
	{
		Sleep(1);
		goto again;
	}
	else shot = false;

	int width = GetSystemMetrics(SM_CXSCREEN) * scaleFactor;
	int height = GetSystemMetrics(SM_CYSCREEN) * scaleFactor;

	// 获取设备上下文
	HDC hdcScreen = GetDC(nullptr);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);

	// 创建兼容的位图
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
	SelectObject(hdcMem, hBitmap);

	// 将屏幕内容复制到位图
	BitBlt(hdcMem, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

	// 将位图保存为文件
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height; // 负值表示从上到下的位图
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;

	// 创建SDL Surface
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
		0, width, height, 32, SDL_PIXELFORMAT_ARGB8888
	);

	// 将位图数据复制到SDL Surface
	GetDIBits(hdcMem, hBitmap, 0, height, surface->pixels, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	std::string dePath;
	SYSTEMTIME time;
	GetLocalTime(&time);
	CreateDirectory(SavePath.c_str(), NULL);
	dePath = SavePath + std::to_string(time.wYear) + "-" + std::to_string(time.wMonth) + "-" + std::to_string(time.wDay) + "-" + std::to_string(times_open) + "\\";
	CreateDirectory(dePath.c_str(), NULL);
	std::string name2 = dePath + std::to_string(time.wYear) + "-" + std::to_string(time.wMonth) + "-" + std::to_string(time.wDay) + "-" + std::to_string(time.wHour) + "-" + std::to_string(page_shot);
	dePath += "History\\";
	CreateDirectory(dePath.c_str(), NULL);
	dePath += "Page_" + std::to_string(page_shot) + "\\";
	CreateDirectory(dePath.c_str(), NULL);
	std::string name = dePath + std::to_string(time.wYear) + "-" + std::to_string(time.wMonth) + "-" + std::to_string(time.wDay) + "-" + std::to_string(time.wHour) + "-" + std::to_string(time.wMinute) + "-" + std::to_string(time.wSecond) + "-" + std::to_string(time.wMilliseconds);

	switch (SaveWay)
	{
	case PNG:
		name += ".png";
		name2 += ".png";
		if (NULL == IMG_SavePNG(surface, name.c_str()) && NULL == IMG_SavePNG(surface, name2.c_str())) OutLog("Succeeded to save - " + name);
		else OutLog("Failed to save - " + name);
		break;
	case JPEG:
		name += ".jpeg";
		name2 += ".jpeg";
		if (NULL == IMG_SaveJPG(surface, name.c_str(), 50) && IMG_SaveJPG(surface, name2.c_str(), 50)) OutLog("Succeeded to save - " + name);
		else OutLog("Failed to save - " + name);
		break;
	case BMP:
		name += ".bmp";
		name2 += ".bmp";
		if (NULL == SDL_SaveBMP(surface, name.c_str()) && SDL_SaveBMP(surface, name2.c_str())) OutLog("Succeeded to save - " + name);
		else OutLog("Failed to save - " + name);
		break;
	default:
		name += ".png";
		name2 += ".png";
		if (NULL == IMG_SavePNG(surface, name.c_str()) && IMG_SavePNG(surface, name2.c_str())) OutLog("Succeeded to save - " + name);
		else OutLog("Failed to save - " + name);
		break;
	}

	SDL_FreeSurface(surface);

	goto again;
}

#define KEY_DOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000) ? 1:0)
void Shot()
{
	std::thread thread_GetShot(GetShot);

	/*SDL_Rect Rect1;
	Rect1.x = left1;
	Rect1.y = top1;
	Rect1.w = right1 - left1;
	Rect1.h = bottom1 - top1;
	SDL_Window* win1 = SDL_CreateWindow("null1", Rect1.x, Rect1.y, Rect1.w, Rect1.h, NULL);
	SDL_Renderer* rdr1 = SDL_CreateRenderer(win1, -1, 0);
	SDL_SetRenderDrawColor(rdr1, 0, 0, 0, 255);
	SDL_Rect Rect2;
	Rect2.x = left2;
	Rect2.y = top2;
	Rect2.w = right2 - left2;
	Rect2.h = bottom2 - top2;
	SDL_Window* win2 = SDL_CreateWindow("null2", Rect2.x, Rect2.y, Rect2.w, Rect2.h, NULL);
	SDL_Renderer* rdr2 = SDL_CreateRenderer(win2, -1, 0);
	SDL_SetRenderDrawColor(rdr2, 0, 0, 0, 255);*/

	while (true)
	{
		/*SDL_RenderFillRect(rdr1, NULL);
		SDL_RenderFillRect(rdr2, NULL);
		SDL_RenderPresent(rdr1);
		SDL_RenderPresent(rdr2);*/

		hWnd = FindWindow(0, "希沃白板");
		if (hWnd != NULL)
		{
			is_open = true;
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (JudgePoint(left1, top1, right1, bottom1))
					click_last = true;
				else if (JudgePoint(left2, top2, right2, bottom2))
					click_next = true;
			}
			else if (click_last || click_next)
			{
				if (JudgePoint(left1, top1, right1, bottom1))
				{
					if (click_last)
					{
						page_this--;
						if (page_this <= 0) page_this = 1;
					}
				}
				else if (JudgePoint(left2, top2, right2, bottom2))
				{
					if (click_next)
					{
						shot = true;
						page_shot = page_this;
						page_this++;
						if (page_this > page_all)
							page_all++;
					}
				}
				click_last = false;
				click_next = false;
			}
		}
		else
		{
			if (is_open)
			{
				is_open = false;
				times_open++;
				page_all = 1, page_this = 1, page_shot = 1;
				click_last = false, click_next = false;
			}
		}
		Sleep(1);
	}
}