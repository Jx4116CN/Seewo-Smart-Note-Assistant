#include "Init.h"

HWND hWnd = NULL;
int page_all = 1, page_this = 1;
bool click_last = false, click_next = false;

void GetShot()
{
again:
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

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
	dePath = SavePath + std::to_string(time.wYear) + "-" + std::to_string(time.wMonth) + "-" + std::to_string(time.wDay) + "\\";
	CreateDirectory(dePath.c_str(), NULL);
	std::string name = dePath + std::to_string(time.wYear) + "-" + std::to_string(time.wMonth) + "-" + std::to_string(time.wDay) + "-" + std::to_string(time.wHour) + "-" + std::to_string(time.wMinute) + "-" + std::to_string(time.wSecond) + "-" + std::to_string(time.wMilliseconds);
	name += ".png";

	// 保存为PNG
	if (IMG_SavePNG(surface, name.c_str()) != 0)
	{
		SDL_Log("保存PNG失败: %s", SDL_GetError());
		SDL_FreeSurface(surface);
	}
	Sleep(1000);
	goto again;
}

void shot()
{
	std::thread thread_GetShot(GetShot);

	SDL_Rect Rect1;
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
	SDL_SetRenderDrawColor(rdr2, 0, 0, 0, 255);

	SDL_Event Event;
	while (true)
	{
		SDL_RenderFillRect(rdr1, NULL);
		SDL_RenderFillRect(rdr2, NULL);
		SDL_RenderPresent(rdr1);
		SDL_RenderPresent(rdr2);

		if (SDL_PollEvent(&Event))
		{
			hWnd = FindWindow(0, "希沃白板");
			if (hWnd != NULL)
			{
				if (Event.type == SDL_MOUSEBUTTONDOWN && Event.button.button == SDL_BUTTON_LEFT)
				{
					if (JudgePoint(&Event, left1, top1, right1, bottom1))
						click_last = true;
					else if (JudgePoint(&Event, left2, top2, right2, bottom2))
						click_next = true;
				}
				else if (Event.type == SDL_MOUSEBUTTONUP && Event.button.button == SDL_BUTTON_LEFT)
				{
					if (JudgePoint(&Event, left1, top1, right1, bottom1))
					{
						if (click_last)
						{
							page_this--;
							if (page_this <= 0) page_this = 1;
						}
					}
					else if (JudgePoint(&Event, left2, top2, right2, bottom2))
					{
						if (click_next)
						{
							page_this++;
							if (page_this > page_all)
								page_all++;
						}
					}
					click_last = false;
					click_next = false;
				}
			}
		}
		else
			Sleep(10);
	}
}