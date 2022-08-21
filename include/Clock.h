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



#pragma once
#include <chrono>
#include <ctime>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#include "PGE.h"

class Clock {
public:
	Clock(olc::PixelGameEngine* engine) {
		pge = engine;
	}

	void Draw(olc::vi2d pos);
	void SetRadius(float r) {
		clockRadius = r;
	}

	void ToggleDigitalClock() {
		showDigital = !showDigital;
	}

	void ToggleBigFour() {
		showBigFourNumbers = !showBigFourNumbers;
	}

private:
	std::time_t currentTime;
	std::tm now;
	std::string strTime;
	float secRes{ 360.0f / 60.0f };
	float minRes{ 360.0f / 60.0f };
	float hourRes{ 360.0f / 12.0f };
	float secRadius{ 70.0f };
	float minRadius{ 70.0f };
	float hourRadius{ 45.0f };
	float clockRadius{ 90.0f };
	olc::vi2d origo;
	float scale{ 1.0f };
	olc::PixelGameEngine* pge;
	bool showDigital{ true };
	bool showBigFourNumbers{ true };

};
