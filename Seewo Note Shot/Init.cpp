#include "Init.h"

inline void OutLog(std::string str)
{
	OutDate();
	std::cout << str << "\n";
	OutDateToFile(logfilename.c_str());
	OutToFile(str + "\n", logfilename.c_str());
}

void Init_Console()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	logfilename = "logs";
	CreateDirectory(logfilename.c_str(), NULL);
	logfilename += "\\" + std::to_string(st.wYear) + "-" + std::to_string(st.wMonth) + "-" + std::to_string(st.wDay);
	CreateDirectory(logfilename.c_str(), NULL);
	logfilename += "\\" + std::to_string(st.wYear) + "-" + std::to_string(st.wMonth) + "-" + std::to_string(st.wDay) + "-" + std::to_string(st.wHour) + "-" + std::to_string(st.wMinute) + "-" + std::to_string(st.wSecond) + "-" + std::to_string(st.wMilliseconds) + ".log";

	if (!console) return;

init:
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		OutLog("控制台已创建！");
	}
	else
	{
		if (IDRETRY == MessageBox(NULL, "无法创建控制台！", "错误", MB_ICONERROR | MB_RETRYCANCEL))
			goto init;
		else
			exit(0);
	}
}
void Quit_Console()
{
	if (console)
		FreeConsole();
}

void Init_SDL()
{
initSDL:
	if (NULL != SDL_Init(SDL_INIT_VIDEO))
	{
		if (IDRETRY == SDL_ErrorMessageBox(MB_RETRYCANCEL | MB_ICONERROR))
			goto initSDL;
		else
			exit(0);
	}
	OutLog("已初始化SDL");

initIMG:
	if (NULL == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_AVIF | IMG_INIT_JXL))
	{
		if (IDRETRY == IMG_ErrorMessageBox(MB_RETRYCANCEL | MB_ICONERROR))
			goto initIMG;
		else
			exit(0);
	}
	OutLog("已初始化SDL_IMG");
}
void Quit_SDL()
{
	IMG_Quit();
	SDL_Quit();
}

void Init_Data()
{
	char AppDataPath[MAX_PATH];
	SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, AppDataPath);
	std::string Path_AppData = AppDataPath;

init_Console:
	std::ifstream file(Path_AppData + Path_Console, std::ios::binary);
	if (file.is_open())
	{
		bool data;
		file.read((char*)&data, sizeof(data));
		console = data;
	}
	else
	{
		if (IDRETRY == MessageBox(NULL, ("Failed to open the file - " + Path_AppData + Path_Console).c_str(), "Seewo Note Shot - 提示", MB_RETRYCANCEL | MB_ICONERROR))
			goto init_Console;
		else
			exit(0);
	}
	Init_Console();

init_SaveWay:
	std::ifstream file2(Path_AppData + Path_SaveWay);
	if (file2.is_open())
	{
		int data;
		file2.read((char*)&data, sizeof(data));
		switch (data)
		{
		case 0:
			SaveWay = PNG;
			break;
		case 1:
			SaveWay = JPEG;
			break;
		case 2:
			SaveWay = BMP;
			break;
		case 3:
			SaveWay = TIFF;
			break;
		case 4:
			SaveWay = WEBP;
			break;
		case 5:
			SaveWay = AVIF;
			break;
		case 6:
			SaveWay = JXL;
			break;
		default:
			SaveWay = PNG;
			break;
		}
		file2.close();
	}
	else
	{
		if (IDRETRY == MessageBox(NULL, ("Failed to open the file - " + Path_AppData + Path_SaveWay).c_str(), "Seewo Note Shot - 提示", MB_RETRYCANCEL | MB_ICONERROR))
			goto init_SaveWay;
		else
			exit(0);
	}
	OutLog("已打开文件 - " + Path_AppData + Path_SaveWay + "\nvalue:" + std::to_string((int)SaveWay));

init_SavePath:
	std::ifstream file3(Path_AppData + Path_SavePath);
	if (file3.is_open())
	{
		std::getline(file3, SavePath);
	}
	else
	{
		if (IDRETRY == MessageBox(NULL, ("Failed to open the file - " + Path_AppData + Path_SaveWay).c_str(), "Seewo Note Shot - 提示", MB_RETRYCANCEL | MB_ICONERROR))
			goto init_SavePath;
		else
			exit(0);
	}
	OutLog("已打开文件 - " + Path_AppData + Path_SavePath + "\nvalue:" + SavePath);
	SavePath += '\\';
}

void Init_Size()
{
	HDC hdc = ::GetDC(nullptr);
	int cxLogical = GetDeviceCaps(hdc, HORZRES);        // 逻辑分辨率宽度
	int cxPhysical = GetDeviceCaps(hdc, DESKTOPHORZRES); // 物理分辨率宽度
	::ReleaseDC(nullptr, hdc);

	scaleFactor = static_cast<double>(cxPhysical) / cxLogical;
	OutLog("Scale Factor: " + std::to_string(scaleFactor));

	screenw = GetSystemMetrics(SM_CXSCREEN);
	screenh = GetSystemMetrics(SM_CYSCREEN);
	OutLog("Screen width: " + std::to_string(screenw) + " Screen height: " + std::to_string(screenh));

	int spacing = scaleFactor / 480 * 1920;
	int width = scaleFactor / 29 * 1920;
	int height = scaleFactor / 19 * 1080;
	right2 = screenw - spacing;
	right1 = right2 - width * 2;
	bottom2 = screenh - spacing;
	bottom1 = bottom2;
	left2 = right2 - width;
	left1 = right1 - width;
	top2 = bottom2 - height;
	top1 = bottom1 - height;
}

void init()
{
	Init_Data();

	Init_Size();

	Init_SDL();
}
void quit()
{
	Quit_SDL();
	Quit_Console();
}