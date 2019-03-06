#include <iostream>
#include <Windows.h>
#include "Framework.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	Framework frmwrk(800, 800, "Tic Tac Toe, x64");

	if (!frmwrk.Run())
	{
		std::cerr << "Runtime Error." << std::endl;
		return 1;
	}

	
	return 0;
}