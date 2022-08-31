/*
* A little transparent rudementary analog clock made with olcPixelGameEngine
* Made it for own use, but feel free to use it if you find it useful
*
* PixelGameEngine  https://github.com/OneLoneCoder/olcPixelGameEngine
*
* Mouse Left klikk: toggle show numbers + digital clock
* Mouse right klikk, hold and drag for moving the clock
* 
* Written by Dragoneye, 2022/08/21
* 
*/

#include "PGE.h"

#include <chrono>
#include <ctime>
#include <string>
#include "Clock.h"
#include "pianoSample.h"


// transparancy in Windows only supported for now. ( need sleep xD )
#if defined(_WIN32) && !defined(__MINGW32__)
HWND SetTransparacy() {

	DWORD dwExStyle = WS_EX_LAYERED;
	DWORD dwStyle = WS_VISIBLE | WS_POPUP;

	// get the window handle 
	HWND hWnd = GetForegroundWindow();
	// HWND_TOPMOST
	// set the new extended style and style flags to the existing window
	SetWindowLongW(hWnd, GWL_EXSTYLE, dwExStyle);
	SetWindowLongW(hWnd, GWL_STYLE, dwStyle);

	// Use crKey as the transparency color. In our case it is black
	// BOOL SetLayeredWindowAttributes(HWND hwnd,COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0x0, LWA_COLORKEY);

	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	return hWnd;
	
}

HWND SetWindowTop(bool isTopMost) {
	// get the window handle 
	HWND hWnd = GetForegroundWindow();

	if ( isTopMost)
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return hWnd;
}
#endif


class App : public olc::PixelGameEngine
{

protected: // Sound Specific
	olc::sound::WaveEngine engine;
	olc::sound::Wave testSound2;


public:
	App()
	{
		sAppName = "A Clock";
	}

	Clock myClock{this};

	#if defined(_WIN32) && !defined(__MINGW32__)
		POINT mPoint;
		HWND hWnd;
	#endif

	// Play the sound once upon startup, false for not.
	bool playOnce{false};

	bool onTopToggle{ true};

public:

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		// TRANSPARANCY, yay!   (Windows only for now!)
		#if defined(_WIN32) && !defined(__MINGW32__)
			hWnd = SetTransparacy();
		#endif
	
		engine.InitialiseAudio(16000, 1);
		testSound2 = olc::sound::Wave(1, size_t(testSoundLen), 16000, testSoundLen);
		for (size_t i = 0; i < testSoundLen; i++) {
			testSound2.file.data()[i] = static_cast<float>(testSound[i]);
		}

		myClock.Init();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);

		if (playOnce || GetKey(olc::SPACE).bPressed) {
			engine.PlayWaveform(&testSound2);
			playOnce = false;
		}

		myClock.Draw({ ScreenWidth() / 2, (ScreenHeight() / 2) + 1 }, fElapsedTime);

		if (GetMouse(1).bHeld) {
			#if defined(_WIN32) && !defined(__MINGW32__)
				GetCursorPos(&mPoint);
				SetWindowPos( hWnd,	HWND_TOP, mPoint.x - ScreenWidth() / 2, mPoint.y - ScreenHeight() / 2, 0, 0, SWP_NOSIZE);
			#endif
		}
		
		if (GetMouse(0).bReleased) {
			bool isNobHovered = myClock.isNobHovered( GetMousePos());
			if (isNobHovered) {
				onTopToggle = !onTopToggle;
				(void) SetWindowTop(onTopToggle);
				std::cout << "Center nub overed and clicked\n";
			}
			else {
				myClock.ToggleDigitalClock();
				myClock.ToggleBigFour();
			}
		}

		if (GetKey(olc::ESCAPE).bPressed)
			return false;

		return true;
	}
};

int main()
{
	App aaaaClock;
	if (aaaaClock.Construct(256, 240, 1, 1, false, true))
		aaaaClock.Start();

	return 0;
}

// Right click on your project -> Configuration Properties -> Linker -> System -> SubSystem   set the Windows (/SUBSYSTEM:WINDOWS)   option to get rid of the console window if you insist.
#if defined(_WIN32) && !defined(__MINGW32__)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	return main();
}
#endif