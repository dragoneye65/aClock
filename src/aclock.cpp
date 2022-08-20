#include "PGE.h"

#include <chrono>
#include <ctime>
#include <string>
#include "Clock.h"


/*
#include <GL/gl.h>
#include <GL/GLU.h>
#include "glcorearb.h"

typedef char GLchar;
#define GL_MAX_DEBUG_MESSAGE_LENGTH 256

void GetFirstNMessages(GLuint numMsgs)
{
	GLint maxMsgLen = 0;
	glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);

	std::vector<GLchar> msgData(numMsgs * maxMsgLen);
	std::vector<GLenum> sources(numMsgs);
	std::vector<GLenum> types(numMsgs);
	std::vector<GLenum> severities(numMsgs);
	std::vector<GLuint> ids(numMsgs);
	std::vector<GLsizei> lengths(numMsgs);

	GLuint numFound = glGetDebugMessageLog(numMsgs, msgs.size(), 
			&sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);

	sources.resize(numFound);
	types.resize(numFound);
	severities.resize(numFound);
	ids.resize(numFound);
	lengths.resize(numFound);

	std::vector<std::string> messages;
	messages.reserve(numFound);

	std::vector<GLchar>::iterator currPos = msgData.begin();
	for (size_t msg = 0; msg < lengths.size(); ++msg)
	{
		messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
		currPos = currPos + lengths[msg];
	}
}
*/



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


		// glEnable(GL_DEBUG_OUTPUT);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		// SetPixelMode(olc::Pixel::MASK);
		Clear(olc::DARK_BLUE);
		// Clear(olc::BLANK);

		myClock.setRadius(90.0f);
		myClock.Draw({ ScreenWidth()/2, (ScreenHeight()/2)+1 });

		if (GetMouse(0).bReleased) {
			myClock.toggleDigitalClock();
		}

		if (GetMouse(1).bReleased) {
			myClock.toggleBigFour();
		}

		return true;
	}
};

int main()
{
	App demo;
	if (demo.Construct(256, 240, 1, 1, false, true))
		demo.Start();

	return 0;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	return main();
}
