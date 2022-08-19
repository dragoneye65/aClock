#include "PGE.h"

#include <chrono>
#include <ctime>
#include <string>
#include "Clock.h"


class App : public olc::PixelGameEngine
{
public:
	App()
	{
		sAppName = "A Clock";
	}

	Clock myClock{this};

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		SetPixelMode(olc::Pixel::MASK);
		// Clear(olc::DARK_BLUE);
		Clear(olc::BLANK);

		myClock.setRadius(45.0f);
		myClock.Draw({ ScreenWidth()/2, (ScreenHeight()/2)+1 });

		return true;
	}
};


int main()
{
	App demo;
	if (demo.Construct(256/2, 240/2, 1, 1, false, true))
		demo.Start();

	return 0;
}
