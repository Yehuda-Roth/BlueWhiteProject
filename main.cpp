// BlueWhiteProject.cpp : Defines the entry point for the application.
//
#include "windows.h"

#include <iostream>
#include "ImplementModule.h"

using namespace std;

volatile bool running = true;

int main()
{
	ImplementModule impModule;
	impModule.registerImpelement(enumImplement::XXX_IMPELEMENT_E, new UdpImplement());

	while (running)
	{
		impModule.doCycle();

		Sleep(100);
	}

	return 0;
}
