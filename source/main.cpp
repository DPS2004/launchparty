//based heavily on https://github.com/devkitPro/3ds-examples/tree/master/graphics/printing/hello-world for now

#include <3ds.h>
#include <stdio.h>
#include <cstring>


int main(int argc, char **argv)
{
	gfxInitDefault();
	//use console for now, eventually probably use citro2d?
	consoleInit(GFX_TOP, NULL);
	
	printf("\x1b[2;0HLaunchParty!");
	printf("\x1b[4;0HPress START to launch RHMM");
	printf("\x1b[5;0HPress SELECT to quit");
	
	while (aptMainLoop())
	{
		
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		
		if (kDown & KEY_START)
		{	
			//based on ModMoon implementation
			u8 param[0x300];
			u8 hmac[0x20];
			u64 mm_id = 0x000400000018A400;
			
			memset(param, 0, sizeof(param));
			memset(hmac, 0, sizeof(hmac));
			
			APT_PrepareToDoApplicationJump(0, mm_id, 1); //assumes USA copy stored on SD
			APT_DoApplicationJump(param, sizeof(param), hmac);
		}
		
		if (kDown & KEY_SELECT)
		{
			break; // break in order to return to hbmenu
		}
		
		
		
		
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	
	
	gfxExit();
	return 0;
	
}