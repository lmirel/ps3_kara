#include <cell/dbgfont.h>

CellDbgFontConsoleId mDbgFontID[2];

//-----------------------------------------------------------------------------
//E  Description: Debug font initialization function
//-----------------------------------------------------------------------------
void dbgFontInit(int w, int h)
{
	//E  initialize debug font library, then open console.
	int ret;
	CellDbgFontConfig cfg;
	memset(&cfg, 0, sizeof(CellDbgFontConfig));
	cfg.bufSize      = 512;
	cfg.screenWidth  = w;
	cfg.screenHeight = h;
	ret = cellDbgFontInit(&cfg);
	if (ret != CELL_OK) {
		Nprintf("cellDbgFontInit() failed %x\n", ret);
		return;
	}
#if 0
	CellDbgFontConsoleConfig ccfg[2];
	memset(ccfg, 0, sizeof(ccfg));
	ccfg[0].posLeft     = 0.1f;
	ccfg[0].posTop      = 0.8f;
	ccfg[0].cnsWidth    = 32;
	ccfg[0].cnsHeight   = 4;
	ccfg[0].scale       = 1.0f;
	//E  ABGR -> orange
	ccfg[0].color       = 0xff0080ff;
	mDbgFontID[0] = cellDbgFontConsoleOpen(&ccfg[0]);
	if (mDbgFontID[0] < 0) {
		Nprintf("cellDbgFontConsoleOpen() failed %x\n", mDbgFontID[0]);
		return;
	}

	ccfg[1].posLeft     = 0.65f;
	ccfg[1].posTop      = 0.6f;
	ccfg[1].cnsWidth    = 32;
	ccfg[1].cnsHeight   = 16;
	ccfg[1].scale       = 0.6f;
	//E  ABGR -> pale blue
	ccfg[1].color       = 0xffff8080;
	mDbgFontID[1] = cellDbgFontConsoleOpen(&ccfg[1]);
	if (mDbgFontID[1] < 0) {
		Nprintf("cellDbgFontConsoleOpen() failed %x\n", mDbgFontID[1]);
		return;
	}
	#endif
}

//-----------------------------------------------------------------------------
//E  Description: Debug font put function
//-----------------------------------------------------------------------------
void dbgFontPut(void)
{
	#if 0
	static const int CONS0_PUTS_INTERVAL    = 60;
	static const int CONS0_NUM_STRINGS      = 6;
	static const int CONS1_PUTC_INTERVAL    = 4;
	static const int CONS1_AUTOEOL_INTERVAL = 200;
	
	char testchar[CONS0_NUM_STRINGS][256] = {
		"This is a debug font sample that",
		"shows co-working with FW and ",
		"User drawing.",
		"Connect USB-PAD and try to press",
		"[Circle] and [Cross] buttons.",
		"------------------------------\n",
	};
	
	static char letter = 'a';
	int mFrame = 0;
		//E  put string to console 0 or stdout
	if (mFrame % CONS0_PUTS_INTERVAL == 0){
		cellDbgFontConsolePuts((mIsStdout ? CELL_DBGFONT_STDOUT_ID : mDbgFontID[0]), 
							   testchar[(mFrame / CONS0_PUTS_INTERVAL) % CONS0_NUM_STRINGS]);
	}

	//E  put chars to console 1
	if (mFrame % CONS1_PUTC_INTERVAL == 0) {
		cellDbgFontConsolePrintf(mDbgFontID[1], "%c", letter);
		//E  increment the letter and clip it upto 'z'
		if(++letter == 'z' + 1)
			letter = 'a';
	}
	if (mFrame % CONS1_AUTOEOL_INTERVAL == 0 ) {
		cellDbgFontConsolePrintf(mDbgFontID[1], "%s", "[EOL]\n");
	}
	#endif
	//E  Label mode printing (all white)
	cellDbgFontPuts(0.1f, 0.12f, 0.8f, 0xffffffff, "Press [Circle] : Insert carriage return to right console");
	cellDbgFontPuts(0.1f, 0.15f, 0.8f, 0xffffffff, "Press [Cross]  : Toggle output console");
	
	cellDbgFontPuts(0.1f, 0.7f, 0.3f, 0xffffffff, "Now printing out to left console..");
}

//-----------------------------------------------------------------------------
//E  Description: Debug font draw function
//-----------------------------------------------------------------------------
void dbgFontDraw(void)
{
	cellDbgFontDraw();
}

//-----------------------------------------------------------------------------
//E  Description: Debug font exit function
//-----------------------------------------------------------------------------
void dbgFontExit(void)
{
	#if 0
	cellDbgFontConsoleClose(mDbgFontID[0]);
	cellDbgFontConsoleClose(mDbgFontID[1]);
	#endif
	cellDbgFontExit();
}


//color is AABBGGRR
void dbgFontPrintStroke (float x, float y, float size, unsigned int color, const char *str)
{
	#if 0 //can't write this too many times since the dbgFont lib is limited to 256 chars per frame
  cellDbgFontPrintf (x - .001f, y + .001f, size, 0xff000000, str);
  cellDbgFontPrintf (x - .001f, y - .001f, size, 0xff000000, str);

  cellDbgFontPrintf (x + .001f, y + .001f, size, 0xff000000, str);
  cellDbgFontPrintf (x + .001f, y - .001f, size, 0xff000000, str);
	#endif
  cellDbgFontPrintf (x + .002f, y + .002f, size, 0xff000000, str);

  cellDbgFontPrintf (x, y, size, color, str);
}

void dbgFontPrint (float x, float y, float size, unsigned int color, const char *str)
{
  cellDbgFontPrintf (x, y, size, color, str);
}
