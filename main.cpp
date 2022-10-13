// BlueWhiteProject.cpp : Defines the entry point for the application.
//
#include "windows.h"

#include <iostream>
#include "ImplementModule.h"
#include "UdpImplement.h"
#include "Rs422Implement.h"

using namespace std;

volatile bool running = true;

int main()
{
	ImplementModule impModule;
	impModule.registerImpelement(enumImplement::DIG_IMPELEMENT_E, new UdpImplement(7777));
	impModule.registerImpelement(enumImplement::PLOW_IMPELEMENT_E, new UdpImplement(7778));
	impModule.registerImpelement(enumImplement::SOW_IMPELEMENT_E, new Rs422Implement());

	while (running)
	{
		impModule.doCycle();

		Sleep(100);
	}

	return 0;
}
