//based heavily on https://github.com/devkitPro/3ds-examples/tree/master/graphics/printing/hello-world for now

#include <3ds.h>
#include <stdio.h>
#include <cstring>
#include <string>


bool doQuit = false;

int coolInt = 0;

void pr(std::string t, int x, int y)
{
	std::string printstr = "\x1b[" + std::to_string(y + 1) + ";" + std::to_string(x).c_str() + "H" + t;
	printf(printstr.c_str() );
	
}

void update()
{
	hidScanInput();

	u32 kDown = hidKeysDown();
	
	if (kDown & KEY_LEFT)
	{
		coolInt -= 1;
	}
	if (kDown & KEY_RIGHT)
	{
		coolInt += 1;
	}
	
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
		doQuit = true;
	}
}


void draw()
{
	consoleClear();
	pr("LaunchParty!",0,1);
	pr("Press START to launch RHMM",0,3);
	pr("Press SELECT to quit",0,4);
	
	pr(std::to_string(coolInt),1,6);
	
	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();
}


int main(int argc, char **argv)
{
	gfxInitDefault();
	//use console for now, eventually probably use citro2d?
	consoleInit(GFX_TOP, NULL);
	
	
	
	while (aptMainLoop())
	{
		update();
		
		draw();
		
		if(doQuit)
		{
			break;
		}
		
	}
	
	
	gfxExit();
	return 0;
	
}