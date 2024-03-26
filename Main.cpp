#include "Main.h"
#include "auth.hpp"
#include "indicator.h"
#include <filesystem>
#include "xors.h"
#include "Protection.h"
#include "Print.h"
#include "Xor.hpp"


//#define _DEBUG 1

uint64_t add[16];

bool k_f5 = 0;
bool k_f6 = 0;
bool k_f7 = 0;
bool k_f8 = 0;


bool IsKeyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}
int aim_key = VK_RBUTTON;


std::string RandomString(const size_t length)
{
	std::string r;
	static const char bet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYabcdefghijklmnopqrstuvwxyzZ1234567890" };
	srand((unsigned)time(NULL) * 5);
	for (int i = 0; i < length; ++i)
		r += bet[rand() % (sizeof(bet) - 1)];
	return r;
}




HWND g_Hwnd = NULL;

bool ExGetProcessId(_Out_ LPDWORD lpdwProcessId, HWND* Hwnd)
{
	HWND GameHwnd = FindWindowW(L"UnrealWindow"), NULL);
	if (GameHwnd != NULL)
	{
		GetWindowThreadProcessId(GameHwnd, lpdwProcessId);
		*Hwnd = GameHwnd;
		return true;
	}
	return false;
}



bool IsProcessRunning(const std::wstring& processName)
{
	HANDLE hSnapshot = LI_FN(CreateToolhelp32Snapshot)(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &processEntry))
	{
		do
		{
			if (processName == processEntry.szExeFile)
			{
				LI_FN(CloseHandle)(hSnapshot);
				return true;
			}
		} while (Process32Next(hSnapshot, &processEntry));
	}

	LI_FN(CloseHandle)(hSnapshot);
	return false;
}

DWORD GetProcessByName(const wchar_t* Name) {
	typedef NTSTATUS(WINAPI* t_NtQuerySystemInformation)(int, PVOID, ULONG, PULONG);
	static t_NtQuerySystemInformation f_NtQuerySystemInformation = (t_NtQuerySystemInformation)GetProcAddress(GetModuleHandleA(xor ("ntdll.dll")), xor ("NtQuerySystemInformation"));
	ULONG buflen = 0;
	BYTE* buffer = NULL;

	// première appel pour récupérer la taille du tampon nécessaire pour les informations
	NTSTATUS lResult = f_NtQuerySystemInformation(5, NULL, 0, &buflen);
	buffer = new BYTE[buflen];

	// maintenant appel avec l'intention de collecter les informations
	lResult = f_NtQuerySystemInformation(5, buffer, buflen, &buflen);
	if (lResult) {
		delete[] buffer;
		Sleep(1);
		return GetProcessByName(Name);
	}

	// itérer à travers les processus
	SYSTEM_PROCESS_INFORMATION* info = (SYSTEM_PROCESS_INFORMATION*)buffer;
	while (info) {
		if (info->ImageName.Buffer != NULL && info->ImageName.Length != 0) {
			if (_wcsicmp(info->ImageName.Buffer, Name) == 0) {
				DWORD PID = (DWORD)info->UniqueProcessId;
				delete[] buffer;
				return PID;
			}
		}
		if (info->NextEntryOffset == 0)
			break;
		info = (SYSTEM_PROCESS_INFORMATION*)((BYTE*)info + info->NextEntryOffset);
	}

	delete[] buffer;
	return 0;
}

const wchar_t* dwProcessNames = L"SCUM.exe";

std::string path()
{
	char shitter[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
	return std::string(shitter); //returning the path
}




int main()
{
	
    HWND Hwnd = 0;
    DWORD ProcId = 0;
	bool hwnd = 0;

	while (hwnd == NULL)
	{
		PrintSpace::print("\nPlease open your games");
		Sleep(50);
		system("cls");
		auto wind = ("SCUM  ");
		hwnd = FindWindowA(0, wind);
		Sleep(100);
	}

	SetupWindow();
	Beep(500, 400);
	DirectXInit(MyWnd);

	while (false == (ExGetProcessId(&ProcId, &Hwnd)))
	{
		Sleep(500);
	}

	if (driver->Init(FALSE)) {
		driver->Attach(ProcId);

		ProcessBase = driver->GetModuleBase(dwProcessNames);
	}

	if (!ProcessBase) 
		li(MessageBoxA)(0, CRY_XORSTR_LIGHT("Try run .reg file."), CRY_XORSTR_LIGHT("CONTACT SUPPORT"), MB_OK);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf(XorChar("Do not close loader !\n"));
	printf(XorChar("END KEY for Unload.\n"));

	Beep(500, 400);

	HWND console = GetConsoleWindow();
	//ShowWindow(console, SW_HIDE);

	BaseAddressTemp = ProcessBase;
	//printf("1");
	//ReadSettings();
	Sleep(3000);
	//printf("8");
	HANDLE hdl = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cache), nullptr, NULL, NULL);
	CloseHandle(hdl);

	while (TRUE) {
		MainLoop();
	}
}



