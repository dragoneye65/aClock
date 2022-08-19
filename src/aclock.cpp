#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <chrono>
#include <ctime>
#include <string>



// #define _USE_MATH_DEFINES
// #include <cmath>
// or simply define it
constexpr auto M_PI = 3.14159265358979323846;



class App : public olc::PixelGameEngine
{
public:
	App()
	{
		sAppName = "A Clock";
	}

	std::time_t currentTime;
	std::tm now;
	std::string strTime;
	float secRes{ 360.0f / 60.0f };
	float minRes{ 360.0f / 60.0f };
	float hourRes{ 360.0f / 12.0f };
	float secRadius{ 70.0f };
	float minRadius { 70.0f };
	float hourRadius { 45.0f };
	float clockRadius{ 90.0f };

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


//		for (int x = 0; x < ScreenWidth(); x++)
//			for (int y = 0; y < ScreenHeight(); y++)
//				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));

		currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&now,&currentTime);

		strTime = std::to_string(now.tm_hour) + ":" + std::to_string(now.tm_min) + ":" + std::to_string(now.tm_sec);

		// digital clock
		olc::vi2d digiClockPos = { 
			int((ScreenWidth() / 2) - int(strTime.size() * 8 / 2)),
			int(ScreenHeight() / 2) + 50 
		};
		DrawString( digiClockPos, strTime, olc::VERY_DARK_MAGENTA);

		int secDeg = int((secRes * now.tm_sec)) % 360;
		int minDeg = int((minRes * now.tm_min)) % 360;
		int hourDeg = int((hourRes * now.tm_hour)) % 360;
		// strTime = std::to_string( secDeg );
		// DrawString({ 50, 150 }, strTime);

		float secRad = secDeg * M_PI / 180.0f;
		float minRad = minDeg * M_PI / 180.0f;
		float hourRad = hourDeg * M_PI / 180.0f;
		// strTime = std::to_string(hourRad) + " " + std::to_string(hourDeg);
		// DrawString({ 50, 160 }, strTime);

		// polar coordinate trickery
		olc::vi2d origo{ ScreenWidth() / 2, ScreenHeight() / 2 };

		olc::vf2d secEndpoint;
		olc::vf2d minEndpoint;
		olc::vf2d hourEndpoint;
		secEndpoint.x = origo.x + secRadius * cos(secRad - M_PI / 2);
		secEndpoint.y = origo.y + secRadius * sin(secRad - M_PI / 2);
		minEndpoint.x = origo.x + minRadius * cos(minRad - M_PI / 2);
		minEndpoint.y = origo.y + minRadius * sin(minRad - M_PI / 2);
		hourEndpoint.x = origo.x + hourRadius * cos(hourRad - M_PI / 2);
		hourEndpoint.y = origo.y + hourRadius * sin(hourRad - M_PI / 2);
		DrawLine(origo, secEndpoint, olc::RED);
		DrawLine(origo, hourEndpoint, olc::YELLOW);
		DrawLine(origo, minEndpoint, olc::GREEN);


		// draw the clock circle
		olc::vf2d clockOuterMarker;
		olc::vf2d startDrawOffset;
		float markerDrawOffset = 85.0f;
		int i{ 0 };
		
		for ( i = 0; i < 360; i++) {
			// if ( secRes % 12)
			startDrawOffset.x = origo.x + (markerDrawOffset+6) * cos( i * M_PI / 180 - M_PI / 2);
			startDrawOffset.y = origo.y + (markerDrawOffset+6) * sin( i * M_PI / 180 - M_PI / 2);

			clockOuterMarker.x = origo.x + clockRadius * cos( i * M_PI / 180 - M_PI / 2);
			clockOuterMarker.y = origo.y + clockRadius * sin( i * M_PI / 180 - M_PI / 2);
			
			
			// if (!(int(i*360/180) % 22)) {
			if ( !(i % int(secRes))) {
				// DrawLine(startDrawOffset, clockOuterMarker);
				Draw({ int64_t(clockOuterMarker.x), int64_t(clockOuterMarker.y) });
			}

			if ( !(i % int(360/12))) {
				startDrawOffset.x = origo.x + (markerDrawOffset) * cos(i * M_PI / 180 - M_PI / 2);
				startDrawOffset.y = origo.y + (markerDrawOffset) * sin(i * M_PI / 180 - M_PI / 2);
				DrawLine(startDrawOffset, clockOuterMarker, olc::YELLOW);
			}

			// Draw the big 4
			if ( i == 0 || i == 90 || i == 180 || i == 270) {
				startDrawOffset.x = origo.x + (markerDrawOffset-4) * cos( i * M_PI / 180- M_PI / 2);
				startDrawOffset.y = origo.y + (markerDrawOffset-4) * sin( i * M_PI / 180 - M_PI / 2);

				DrawLine(startDrawOffset, clockOuterMarker, olc::MAGENTA);

				startDrawOffset.x = origo.x + (markerDrawOffset + 20) * cos( i * M_PI / 180 - M_PI / 2);
				startDrawOffset.y = origo.y + (markerDrawOffset + 20) * sin( i * M_PI / 180 - M_PI / 2);
				int kl{0};
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
				std::string strTmp = std::to_string(kl);
				
				DrawString({ int64_t(startDrawOffset.x-(strTmp.size()*8/2)), int64_t(startDrawOffset.y-8/2) }, strTmp);
			}
		}

		return true;
	}
};


int main()
{
	App demo;
	if (demo.Construct(256*2, 240*2, 2, 2, false, true))
		demo.Start();

	return 0;
}
