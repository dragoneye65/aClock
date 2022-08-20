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

	// strTime = std::to_string(now.tm_hour) + ":" + std::to_string(now.tm_min) + ":" + std::to_string(now.tm_sec);
	strTime = strHour + ":" + strMin + ":" + strSec;



	// digital clock
	if (showDigital) {
		olc::vi2d digiClockPos = {
			int((origo.x) - int(strTime.size() * 8 / 2)),
			int(origo.y) + 50
		};
		pge->DrawString(digiClockPos, strTime, olc::VERY_DARK_MAGENTA);
	}

	int secDeg = int((secRes * now.tm_sec)) % 360;
	int minDeg = int((minRes * now.tm_min)) % 360;
	int hourDeg = int((hourRes * now.tm_hour)) % 360;

	float secRad = secDeg * M_PI / 180.0f;
	float minRad = minDeg * M_PI / 180.0f;
	float hourRad = hourDeg * M_PI / 180.0f;

	olc::vf2d secEndpoint;
	olc::vf2d minEndpoint;
	olc::vf2d hourEndpoint;

	// subtract 90 degrees so we get 0 at north, or 12 o'clock if you will
	secEndpoint.x = origo.x + (clockRadius-10) * cos(secRad - M_PI / 2);
	secEndpoint.y = origo.y + (clockRadius - 10) * sin(secRad - M_PI / 2);
	minEndpoint.x = origo.x + (clockRadius - 10) * cos(minRad - M_PI / 2);
	minEndpoint.y = origo.y + (clockRadius - 10) * sin(minRad - M_PI / 2);
	hourEndpoint.x = origo.x + (clockRadius - 20) * cos(hourRad - M_PI / 2);
	hourEndpoint.y = origo.y + (clockRadius - 20) * sin(hourRad - M_PI / 2);

	pge->DrawLine(origo, hourEndpoint, olc::YELLOW);
	pge->DrawLine(origo, minEndpoint, olc::GREEN);
	pge->DrawLine(origo, secEndpoint, olc::RED);

	// strTime = std::to_string(origo.x) + "," + std::to_string(origo.y);
	// pge->DrawString({ 50, 160 }, strTime);

	// draw the clock circle
	olc::vf2d clockOuterMarker;
	olc::vf2d startDrawOffset;
	float markerDrawOffset = (clockRadius-5) * scale;
	int i{ 0 };

	for (i = 0; i < 360; i++) {
		// if ( secRes % 12)
		startDrawOffset.x = origo.x + (markerDrawOffset + 6) * cos(i * M_PI / 180 - M_PI / 2);
		startDrawOffset.y = origo.y + (markerDrawOffset + 6) * sin(i * M_PI / 180 - M_PI / 2);

		clockOuterMarker.x = origo.x + clockRadius * cos(i * M_PI / 180 - M_PI / 2);
		clockOuterMarker.y = origo.y + clockRadius * sin(i * M_PI / 180 - M_PI / 2);


		// draw second markers
		if (!(i % int(secRes))) {
			// DrawLine(startDrawOffset, clockOuterMarker);
			pge->Draw({ int64_t(clockOuterMarker.x), int64_t(clockOuterMarker.y) });
		}

		// Draw hour markers
		if (!(i % int(360 / 12))) {
			startDrawOffset.x = origo.x + (markerDrawOffset)*cos(i * M_PI / 180 - M_PI / 2);
			startDrawOffset.y = origo.y + (markerDrawOffset)*sin(i * M_PI / 180 - M_PI / 2);
			pge->DrawLine(startDrawOffset, clockOuterMarker, olc::YELLOW);
		}

		// Draw the big 4 markers
		if (i == 0 || i == 90 || i == 180 || i == 270) {
			startDrawOffset.x = origo.x + (markerDrawOffset - 4) * cos(i * M_PI / 180 - M_PI / 2);
			startDrawOffset.y = origo.y + (markerDrawOffset - 4) * sin(i * M_PI / 180 - M_PI / 2);

			pge->DrawLine(startDrawOffset, clockOuterMarker, olc::MAGENTA);

			startDrawOffset.x = origo.x + (markerDrawOffset + 20) * cos(i * M_PI / 180 - M_PI / 2);
			startDrawOffset.y = origo.y + (markerDrawOffset + 20) * sin(i * M_PI / 180 - M_PI / 2);
			int kl{ 0 };
			switch (i)
			{
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

				pge->DrawString({ int64_t(startDrawOffset.x - (strTmp.size() * 8 / 2)), int64_t(startDrawOffset.y - 8 / 2) }, strTmp);
			}
		}
	}

}