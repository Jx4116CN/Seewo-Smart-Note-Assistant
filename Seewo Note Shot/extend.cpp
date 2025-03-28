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
	// ���� Surface��ȷ���������ݿɷ��ʣ�
	SDL_LockSurface(surface);

	// ͳ����ɫ���ִ���
	std::unordered_map<QuantizedRGBColor, int> colorCount;
	int width = surface->w;
	int height = surface->h;
	int pitch = surface->pitch;
	SDL_PixelFormat* format = surface->format;

	// ������������
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// ��ȡ��ǰ����
			Uint32 pixel = *((Uint32*)((Uint8*)surface->pixels + y * pitch + x * format->BytesPerPixel));

			// �ֽ� RGBA
			Uint8 r, g, b;
			SDL_GetRGB(pixel, format, &r, &g, &b);
			QuantizedRGBColor color = { r, g, b };

			// ͳ����ɫ
			colorCount[color]++;
		}
	}

	// ���� Surface
	SDL_UnlockSurface(surface);

	// �ҵ����ִ���������ɫ
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
	// ������ Surface����ԭʼͼ����ͬ��ʽ�ͳߴ磩
	SDL_Surface* graySurface = SDL_CreateRGBSurfaceWithFormat(
		0,                          // ��־λ��0 ��ʾĬ�ϣ�
		original->w, original->h,   // ��Ⱥ͸߶�
		32,                         // 32 λ��ȣ�ARGB8888��
		original->format->format    // ʹ��ԭʼͼ������ظ�ʽ
	);
	if (!graySurface) {
		printf("Failed to create gray surface: %s\n", SDL_GetError());
		return nullptr;
	}

	// ���� Surface ��ֱ�ӷ�������
	SDL_LockSurface(original);
	SDL_LockSurface(graySurface);

	// ��ȡ��������ָ��
	Uint8* originalPixels = (Uint8*)original->pixels;
	Uint8* grayPixels = (Uint8*)graySurface->pixels;

	// ����ÿ������
	for (int y = 0; y < original->h; y++) {
		for (int x = 0; x < original->w; x++) {
			// ��������λ�ã����� pitch ���룩
			Uint8* originalPixel = originalPixels + y * original->pitch + x * original->format->BytesPerPixel;
			Uint8* grayPixel = grayPixels + y * graySurface->pitch + x * graySurface->format->BytesPerPixel;

			// ��ȡԭʼ RGB ֵ
			Uint8 r, g, b;
			SDL_GetRGB(*(Uint32*)originalPixel, original->format, &r, &g, &b);

			// ����Ҷ�ֵ����Ȩƽ����
			Uint8 gray = (Uint8)(0.299 * r + 0.587 * g + 0.114 * b);

			// д��Ҷ�ֵ���� Surface
			*(Uint32*)grayPixel = SDL_MapRGB(graySurface->format, gray, gray, gray);
		}
	}

	// ���� Surface
	SDL_UnlockSurface(original);
	SDL_UnlockSurface(graySurface);

	return graySurface;
}