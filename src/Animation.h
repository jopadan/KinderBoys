#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL_rect.h"

#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

	// Allows the animation to keep going back and forth
	bool pingpong = false;

private:
	float currentFrame = 0.0f;
	int totalFrames = 0;
	int loopCount = 0;
	int pingpongDirection = 1;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Empty()
	{
		totalFrames = 0;
	}

	void Reset()
	{
		currentFrame = 0;
	}
	
	bool HasFinished()
	{
		return !loop && !pingpong && loopCount > 0;
	}

	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop || pingpong) ? 0.0f : totalFrames - 1;
			++loopCount;

			if (pingpong) pingpongDirection = -pingpongDirection;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1) actualFrame = totalFrames - currentFrame;

		return frames[actualFrame];
	}
};

#endif	// __ANIMATION_H__
