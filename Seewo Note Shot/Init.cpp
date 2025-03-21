#include "Init.h"

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
		OutDate();
		std::cout << "控制台已创建！\n";
		OutDateToFile(logfilename.c_str());
		OutToFile("控制台已创建！\n", logfilename.c_str());
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
	OutDate();
	std::cout << "已初始化SDL\n";
	OutDateToFile(logfilename.c_str());
	OutToFile("已初始化SDL\n", logfilename.c_str());

initIMG:
	if (NULL == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_AVIF | IMG_INIT_JXL))
	{
		if (IDRETRY == IMG_ErrorMessageBox(MB_RETRYCANCEL | MB_ICONERROR))
			goto initIMG;
		else
			exit(0);
	}
	OutDate();
	std::cout << "已初始化SDL_IMG\n";
	OutDateToFile(logfilename.c_str());
	OutToFile("已初始化SDL_IMG\n", logfilename.c_str());
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
	file.open(Path_AppData + Path_SaveWay, std::ios::binary);
	if (file.is_open())
	{
		int data;
		file.read((char*)&data, sizeof(data));
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
		file.close();
	}
	else
	{
		if (IDRETRY == MessageBox(NULL, ("Failed to open the file - " + Path_AppData + Path_SaveWay).c_str(), "Seewo Note Shot - 提示", MB_RETRYCANCEL | MB_ICONERROR))
			goto init_SaveWay;
		else
			exit(0);
	}
	OutDate();
	std::cout << "已打开文件 - " << Path_AppData + Path_SaveWay << "\nvalue:" << (int)SaveWay << "\n";
	OutDateToFile(logfilename.c_str());
	OutToFile("已打开文件 - " + Path_AppData + Path_SaveWay + "\nvalue:" + std::to_string((int)SaveWay) + "\n", logfilename.c_str());
}

void init()
{
	Init_Data();

	Init_SDL();
}
void quit()
{
	Quit_SDL();
	Quit_Console();
}