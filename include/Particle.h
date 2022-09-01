#pragma once

#include <vector>
#include "PGE.h"



class Particle {
public:
	Particle() {}
	Particle(olc::vi2d mP, int mT, olc::Pixel mC, float mV, olc::vf2d mD, bool fttl) : mPos{ mP }, mTTL{ mT }, mColor{ mC }, mVelocity{ mV }, mDirection{ mD }, mFadeOutToTTL{ fttl } {}
	void setPos(olc::vi2d p) {
		mPos = p;
	}
	void setTTL(int t) {
		mTTL = t;
	}
	void setColor(olc::Pixel c) {
		mColor = c;
	}
	void setVelocity(float v) {
		mVelocity = v;
	}
	void setDirection(olc::vf2d dir) {
		mDirection = dir;
	}
	void updatePhysics( olc::vf2d gravity, float drag) {

	}

	void setFadeOut(bool fttl) {
		mFadeOutToTTL = fttl;
	}

private:
	olc::vi2d mPos{ 0, 0};
	int mTTL{ 1000 };	// 1s
	olc::Pixel mColor{olc::RED};
	float mVelocity{100.0f};
	olc::vf2d mDirection{0.5f, 0.5f};
	bool mFadeOutToTTL{ true };
};




class Particles {
public:
	void Init(olc::PixelGameEngine* pge) {
		pgePtr = pge;
	}

	void addParticles(int number, olc::vi2d pos, olc::Pixel color, int ttl) {
		Particle P;
		for (; number; number--) {
			P.setPos(pos);
			// random time to live 
			P.setTTL(500);
			// mix of colors
			P.setColor(olc::BLUE);
			// random velocity
			P.setVelocity(100.0f);
			// spred them out randomly
			P.setDirection({ 0.4f, -0.3f});
			mParticles.emplace_back(P);
		}
	}

	void updatePhysics() {
		for (auto& i : mParticles) {

		}
	}

	void Draw() {
		for (auto &i : mParticles) {

		}
	}

	void setGravity(float g) {
		mGravity = g;
	}

	void setDrag(float d) {
		mDrag = d;
	}

private:
	std::vector<Particle> mParticles;
	olc::PixelGameEngine* pgePtr{nullptr};

	float mGravity{ 9.8f };
	float mDrag{ 0.001f };
};
