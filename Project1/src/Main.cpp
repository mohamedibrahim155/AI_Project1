#include "ApplicationRenderer.h"
#include <Windows.h>

int main()
{

	ApplicationRenderer application;
	application.WindowInitialize(2560, 1440);
	application.Render();
	return 0;
}