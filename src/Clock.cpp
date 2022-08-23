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

#include "Clock.h"

void Clock::Draw(olc::vi2d pos) {
	origo = pos;

	currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&now, &currentTime);

	auto strtmp = std::to_string(now.tm_hour);
	auto strHour = std::string(2 - std::min(2, int(strtmp.length())), '0') + strtmp;

	strtmp = std::to_string(now.tm_min);
	auto strMin = std::string(2 - std::min(2, int(strtmp.length())), '0') + strtmp;

	strtmp = std::to_string(now.tm_sec);
	auto strSec = std::string(2 - std::min(2, int(strtmp.length())), '0') + strtmp;

	strTime = strHour + ":" + strMin + ":" + strSec;

	// draw the disk
	pge->FillCircle({ pge->ScreenWidth() / 2, pge->ScreenHeight() / 2 }, 92, olc::VERY_DARK_BLUE);
	pge->DrawCircle({ pge->ScreenWidth() / 2, pge->ScreenHeight() / 2 }, 92, olc::RED);

	// digital clock
	if (showDigital) {
		olc::vi2d digiClockPos = {
			int((origo.x) - int(strTime.size() * 8 / 2)),
			int(origo.y) + 50
		};
		pge->DrawString(digiClockPos, strTime, olc::DARK_MAGENTA);
	}

	int secDeg = int((secRes * now.tm_sec)) % 360;
	int minDeg = int((minRes * now.tm_min)) % 360;
	int hourDeg = int((hourRes * now.tm_hour)) % 360;

	float secRad = float(secDeg * M_PI / 180.0f);
	float minRad = float(minDeg * M_PI / 180.0f);
	float hourRad = float(hourDeg * M_PI / 180.0f);

	olc::vf2d secEndpoint;
	olc::vf2d minEndpoint;
	olc::vf2d hourEndpoint;

	// subtract 90 degrees so we get 0 at north, or 12 o'clock if you will
	secEndpoint.x = float(origo.x + (clockRadius - 10) * cos(secRad - M_PI / 2));
	secEndpoint.y = float(origo.y + (clockRadius - 10) * sin(secRad - M_PI / 2));
	minEndpoint.x = float(origo.x + (clockRadius - 20) * cos(minRad - M_PI / 2));
	minEndpoint.y = float(origo.y + (clockRadius - 20) * sin(minRad - M_PI / 2));
	hourEndpoint.x = float(origo.x + (clockRadius - 45) * cos(hourRad - M_PI / 2));
	hourEndpoint.y = float(origo.y + (clockRadius - 45) * sin(hourRad - M_PI / 2));

	pge->DrawLine(origo, hourEndpoint, olc::YELLOW);
	pge->DrawLine(origo, minEndpoint, olc::GREEN);
	pge->DrawLine(origo, secEndpoint, olc::RED);

	// draw the clock circle
	olc::vf2d clockOuterMarker;
	olc::vf2d startDrawOffset;
	float markerDrawOffset = (clockRadius-5) * scale;
	int i{ 0 };

	// loop through the 360 degree circle
	for (i = 0; i < 360; i++) {
		startDrawOffset.x = float(origo.x + (markerDrawOffset + 6) * cos(i * M_PI / 180 - M_PI / 2));
		startDrawOffset.y = float(origo.y + (markerDrawOffset + 6) * sin(i * M_PI / 180 - M_PI / 2));

		clockOuterMarker.x = float(origo.x + clockRadius * cos(i * M_PI / 180 - M_PI / 2));
		clockOuterMarker.y = float(origo.y + clockRadius * sin(i * M_PI / 180 - M_PI / 2));

		// draw second markers
		if (!(i % int(secRes))) {
			// DrawLine(startDrawOffset, clockOuterMarker);
			pge->Draw({ int64_t(clockOuterMarker.x), int64_t(clockOuterMarker.y) });
		}

		// Draw hour markers
		if (!(i % int(360 / 12))) {
			startDrawOffset.x = float(origo.x + (markerDrawOffset)*cos(i * M_PI / 180 - M_PI / 2));
			startDrawOffset.y = float(origo.y + (markerDrawOffset)*sin(i * M_PI / 180 - M_PI / 2));
			pge->DrawLine(startDrawOffset, clockOuterMarker, olc::YELLOW);
		}

		// Draw the big 4 markers
		if (i == 0 || i == 90 || i == 180 || i == 270) {
			startDrawOffset.x = float(origo.x + (markerDrawOffset - 4) * cos(i * M_PI / 180 - M_PI / 2));
			startDrawOffset.y = float(origo.y + (markerDrawOffset - 4) * sin(i * M_PI / 180 - M_PI / 2));

			pge->DrawLine(startDrawOffset, clockOuterMarker, olc::MAGENTA);

			startDrawOffset.x = float(origo.x + (markerDrawOffset + 20) * cos(i * M_PI / 180 - M_PI / 2));
			startDrawOffset.y = float(origo.y + (markerDrawOffset + 20) * sin(i * M_PI / 180 - M_PI / 2));
			int kl{ 0 };
			switch (i) {
			case 0:
				kl = 12;
				break;
			case 90:
				kl = 3;
				break;
			case 180:
				kl = 6;
				break;
			case 270:
				kl = 9;
				break;
			default:
				break;
			}

			if (showBigFourNumbers) {
				std::string strTmp = std::to_string(kl);
				startDrawOffset.x = float(origo.x + (markerDrawOffset - 12) * cos(i * M_PI / 180 - M_PI / 2));
				startDrawOffset.y = float(origo.y + (markerDrawOffset - 12) * sin(i * M_PI / 180 - M_PI / 2));

				pge->DrawString( { int64_t(startDrawOffset.x - (strTmp.size() * 8 / 2)), int64_t(startDrawOffset.y - 8 / 2) }, strTmp);
			}
		}
	}
}
