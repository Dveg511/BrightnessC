#pragma comment(lib, "Dxva2.lib")
#pragma comment(lib , "User32.lib")
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <string>
#include <ctime>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <fstream>
using std::string;
using std::cout;

void brightnessset(bool* exit)
{
	*exit = false;
	DWORD Bright;
	cout << "write ur brightness : ";
	std::cin >> Bright;
	HWND hwnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

	DWORD MonitorCount = NULL;
	GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &MonitorCount);
	// monitor count check
	if (MonitorCount == 0)
	{
		std::cout << "no monitor found";
		system("exit");

	}

	DWORD CurrentBrightness, MinBrightness, MaxBrightness;

	PHYSICAL_MONITOR* PhysicalMonitor = new PHYSICAL_MONITOR[MonitorCount];

	GetPhysicalMonitorsFromHMONITOR(hMonitor, MonitorCount, PhysicalMonitor);

	GetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness);
	// brightness check
	if (!SetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, Bright)) {
		if (Bright < 0) {
			cout << "\nur " << Bright << " invalid , min is "<<MinBrightness<<"\n";
			Bright = MinBrightness+1;
		}
		if (Bright > MaxBrightness) {
			cout << "\nur " << Bright << " invalid , max is "<<MaxBrightness<<"\n";
			Bright = MaxBrightness-1;
		}
		if (Bright == MaxBrightness) {
			Bright = MaxBrightness-1;
		}
		if (Bright == 0) {
			Bright = MinBrightness;
		}
		for (int i = 0; i < size_t(PhysicalMonitor);i++)
		{
			SetMonitorBrightness(PhysicalMonitor[i].hPhysicalMonitor, Bright);
		}
	}
	delete[] PhysicalMonitor;
}


void menu(bool* exit) 
{
	HWND hwnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

	DWORD MonitorCount = NULL;
	GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &MonitorCount);
	// monitor count check
	if (MonitorCount == 0)
	{
		std::cout << "no monitor found";
		system("exit");

	}

	DWORD CurrentBrightness, MinBrightness, MaxBrightness;

	PHYSICAL_MONITOR* PhysicalMonitor = new PHYSICAL_MONITOR[MonitorCount];

	GetPhysicalMonitorsFromHMONITOR(hMonitor, MonitorCount, PhysicalMonitor);

	GetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness);
	delete[] PhysicalMonitor;
	string first = "1.CHANGE BRIGHTNESS";
	string second = "2.EXIT";
	while (*exit == 1)
	{
		if (GetKeyState(0x31) & 0x8000)
		{
			brightnessset(exit);
		}
		if (GetKeyState(0x32) & 0x8000)
		{
			*exit = false;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			first = "1.CHANGE BRIGHTNESS";
			second = "2.EXIT <";
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			second ="2.EXIT";
			first = "1.CHANGE BRIGHTNESS <";
		}
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			if (first == "1.CHANGE BRIGHTNESS <")
			{
				brightnessset(exit);
			}
			if (second == "2.EXIT <")
			{
				*exit = false;
			}
		}
		std::cout << "\n" << first;
		std::cout << "\n" << second;
		std::cout << "\n\n\nMaxBrightness : " << MaxBrightness;
		std::cout << "\nMinBrightness : " << MinBrightness;
		std::cout << "\nCurrentBrightness : " << CurrentBrightness;

		Sleep(50);
		system("CLS");
	}
	








}
int main()
{
	bool exit = 1;
	menu(&exit);
	return 1;
}	

