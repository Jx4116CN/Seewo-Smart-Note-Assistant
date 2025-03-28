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

bool JudgePoint(int left, int top, int right, int bottom)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	int x = cursorPos.x;
	int y = cursorPos.y;
	if (x >= left && x <= right && y >= top && y <= bottom) return true;
	else return false;
}

void SDL_MaxColorInSurface(SDL_Surface* surface, Uint8& R, Uint8& G, Uint8& B)
{
	// 锁定 Surface（确保像素数据可访问）
	SDL_LockSurface(surface);

	// 统计颜色出现次数
	std::unordered_map<QuantizedRGBColor, int> colorCount;
	int width = surface->w;
	int height = surface->h;
	int pitch = surface->pitch;
	SDL_PixelFormat* format = surface->format;

	// 遍历所有像素
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// 获取当前像素
			Uint32 pixel = *((Uint32*)((Uint8*)surface->pixels + y * pitch + x * format->BytesPerPixel));

			// 分解 RGBA
			Uint8 r, g, b;
			SDL_GetRGB(pixel, format, &r, &g, &b);
			QuantizedRGBColor color = { r, g, b };

			// 统计颜色
			colorCount[color]++;
		}
	}

	// 解锁 Surface
	SDL_UnlockSurface(surface);

	// 找到出现次数最多的颜色
	QuantizedRGBColor mostCommonColor = { 0, 0, 0 };
	int maxCount = 0;
	for (const auto& pair : colorCount) {
		if (pair.second > maxCount) {
			mostCommonColor = pair.first;
			maxCount = pair.second;
		}
	}

	R = mostCommonColor.r;
	G = mostCommonColor.g;
	B = mostCommonColor.b;
}

SDL_Surface* ResizeSurface(SDL_Surface* src, int newWidth, int newHeight)
{
	SDL_Surface* dst = SDL_CreateRGBSurfaceWithFormat(
		0, newWidth, newHeight, 32, SDL_PIXELFORMAT_RGBA8888
	);
	SDL_BlitScaled(src, NULL, dst, NULL);
	return dst;
}

SDL_Surface* convertToGrayscaleSurface(SDL_Surface* original)
{
	// 创建新 Surface（与原始图像相同格式和尺寸）
	SDL_Surface* graySurface = SDL_CreateRGBSurfaceWithFormat(
		0,                          // 标志位（0 表示默认）
		original->w, original->h,   // 宽度和高度
		32,                         // 32 位深度（ARGB8888）
		original->format->format    // 使用原始图像的像素格式
	);
	if (!graySurface) {
		printf("Failed to create gray surface: %s\n", SDL_GetError());
		return nullptr;
	}

	// 锁定 Surface 以直接访问像素
	SDL_LockSurface(original);
	SDL_LockSurface(graySurface);

	// 获取像素数据指针
	Uint8* originalPixels = (Uint8*)original->pixels;
	Uint8* grayPixels = (Uint8*)graySurface->pixels;

	// 遍历每个像素
	for (int y = 0; y < original->h; y++) {
		for (int x = 0; x < original->w; x++) {
			// 计算像素位置（考虑 pitch 对齐）
			Uint8* originalPixel = originalPixels + y * original->pitch + x * original->format->BytesPerPixel;
			Uint8* grayPixel = grayPixels + y * graySurface->pitch + x * graySurface->format->BytesPerPixel;

			// 获取原始 RGB 值
			Uint8 r, g, b;
			SDL_GetRGB(*(Uint32*)originalPixel, original->format, &r, &g, &b);

			// 计算灰度值（加权平均）
			Uint8 gray = (Uint8)(0.299 * r + 0.587 * g + 0.114 * b);

			// 写入灰度值到新 Surface
			*(Uint32*)grayPixel = SDL_MapRGB(graySurface->format, gray, gray, gray);
		}
	}

	// 解锁 Surface
	SDL_UnlockSurface(original);
	SDL_UnlockSurface(graySurface);

	return graySurface;
}