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

void brightness(string function, bool* exit)
{
	*exit = false;
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

	PHYSICAL_MONITOR* PhysicalMonitor = new PHYSICAL_MONITOR[MonitorCount];
	DWORD CurrentBrightness, MinBrightness, MaxBrightness;
	GetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness);
	// brightness check

	GetPhysicalMonitorsFromHMONITOR(hMonitor, MonitorCount, PhysicalMonitor);

	if (function == "brightnessset")
	{
		DWORD Bright;
		cout << "Write ur brightness : ";
		std::cin >> Bright;
		if (Bright < 0) {
			cout << "\nur " << Bright << " invalid , min is " << MinBrightness << "\n";
			Bright = MinBrightness + 1;
		}
		if (Bright > MaxBrightness) {
			cout << "\nur " << Bright << " invalid , max is " << MaxBrightness << "\n";
			Bright = MaxBrightness - 1;
		}
		if (Bright == MaxBrightness) {
			Bright = MaxBrightness - 1;
		}
		if (Bright == 0) {
			Bright = MinBrightness;
		}
		if (!SetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, Bright))
		{
			SetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, Bright);
		}
	}
	if (function == "TemperatureSet")
	{
		
		cout << "\n\n\n\t\t\t\t\t\033[31m in future, wait for 0.3\033[0m\n\n\n\n";
	}


	delete[] PhysicalMonitor;
}


void menu(bool* exit) 
{
	HWND hwnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
	const int functioncount = 4;
	int functionselected = 0 ;
	DWORD MonitorCount = NULL;
	DWORD CurrentBrightness, MinBrightness, MaxBrightness;


	GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &MonitorCount);

	// monitor count check
	if (MonitorCount == 0)
	{
		std::cout << "no monitor found";
		system("exit");

	}
	PHYSICAL_MONITOR* PhysicalMonitor = new PHYSICAL_MONITOR[MonitorCount];

	GetPhysicalMonitorsFromHMONITOR(hMonitor, MonitorCount, PhysicalMonitor);


	GetMonitorBrightness(PhysicalMonitor[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness);

	string functionlist[functioncount]{ " 1.CHANGE BRIGHTNESS" , " 2.ColorTemepatureChange" , " 3.EXIT"};

	string selectedfunctionlist[functioncount]{ "\033[33m 1. CHANGE BRIGHTNESS <\033[0m" , "\033[33m 2. ColorTemepatureChange <\033[0m" , "\033[33m 3.EXIT <\033[0m" };

	string showfunctionlist[functioncount]{ " 1.CHANGE BRIGHTNESS" , " 2.ColorTemepatureChange" , " 3.EXIT" };
	while (*exit == 1)
	{
		for (int i = 0; i < functioncount; i++)
		{
			cout << showfunctionlist[i] << "\n";
		}
		if (GetKeyState(0x31) & 0x8000)
		{
			brightness("brightnessset", exit);
		}
		if (GetKeyState(0x32) & 0x8000)
		{
			brightness("TemperatureSet", exit);
		}
		if (GetKeyState(0x33) & 0x8000)
		{
			*exit = false;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			Sleep(100);
			if (functionselected > 0 )
			{
				functionselected -= 1;
				showfunctionlist[functionselected] = selectedfunctionlist[functionselected];
				showfunctionlist[functionselected+1] = functionlist[functionselected+1];
			}
			else functionselected = 1  ;

		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			Sleep(100);
			if (functionselected < 3)
			{
				functionselected += 1;
				showfunctionlist[functionselected] = selectedfunctionlist[functionselected];
				showfunctionlist[functionselected - 1] = functionlist[functionselected - 1];
			}
			else functionselected = 2  ;
		}
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			system("CLS");
			switch (functionselected)
			{
			case 0:
			
				brightness("brightnessset", exit);
			case 1:
				brightness("TemperatureSet", exit);
			case 2:
				*exit = false;
			case 3:
				continue;

			}
		}
		std::cout << "\n\n\nMaxBrightness : " << MaxBrightness;
		std::cout << "\nMinBrightness : " << MinBrightness;
		std::cout << "\nCurrentBrightness : " << CurrentBrightness;


		Sleep(50);
		system("CLS");
	}
	DestroyPhysicalMonitors(MonitorCount, PhysicalMonitor);
	delete[] PhysicalMonitor;








}
int main()
{
	bool exit = 1;
	menu(&exit);
	return 1;
}	

