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
// #include <filesystem>
#include "PGE.h"

class Clock {
public:
	Clock(olc::PixelGameEngine* engine) {
		pge = engine;
	}

	void Init();
	void ResizeWindow( olc::vi2d wSize);
	void Draw(olc::vi2d pos, float fElapsedTime);
	void SetRadius(float r) {
		clockRadius = r;
	}

	void ToggleDigitalClock() {
		showDigital = !showDigital;
	}

	void ToggleBigFour() {
		showBigFourNumbers = !showBigFourNumbers;
	}

	void CenterPinRot(float rotDir, float fElapsedTime) {
		centerPinAngle -= 0.5f * fElapsedTime;
		if (centerPinAngle < 0.0f)
			centerPinAngle = (3.14159265f * 2) - 0.01f;
		if (centerPinAngle > 3.14159265f * 2)
			centerPinAngle = 0.01f;
	}

	bool isNobHovered( olc::vi2d mPos) {
		int clickedRadius = 5;
		int yPlusWhyyyyy = 40;
		if (mPos.x > centerPinPos.x - clickedRadius && mPos.x < centerPinPos.x + clickedRadius) {
			if (mPos.y > centerPinPos.y + yPlusWhyyyyy - clickedRadius && mPos.y < centerPinPos.y + yPlusWhyyyyy + clickedRadius) {
				return true;
			}
		}

		return false;
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
	float centerPinAngle{ 3.1415f * 2.0f };
	olc::vi2d centerPinPos{ 0, 0};
	olc::Renderable clockDisk, hourHandle, centerPin;
};
