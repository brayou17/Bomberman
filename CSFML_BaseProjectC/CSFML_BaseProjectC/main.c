#include <windows.h>
#include "tools.h"
#include "windowManager.h"


int main(int argc, char** argv)
{
#ifndef _DEBUG
	FreeConsole();
#endif // !DEBUG

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-debug") == 0)
		{
			printf("Debug Mode activated !\n");
			isDebugMode = sfTrue;
		}
		else
			isDebugMode = sfFalse;
	}

	

	sfVector2i defaultVideoMode = { 1920,1080 };
	Window* mainWindow = windowSetup("BomberMan", defaultVideoMode);
	initTools();

	while (!IsDone(mainWindow))
	{
		windowInit(mainWindow);
		windowUpdate(mainWindow);

		BeginDraw(mainWindow);
		windowDraw(mainWindow);
		EndDraw(mainWindow);
	}
	return 0;
}