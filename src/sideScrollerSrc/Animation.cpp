#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::loadContent(ALLEGRO_BITMAP* givenImage, double givenPosition[2])
{
	// Assign givenVariables to class variables
	image = givenImage;
	position[0] = givenPosition[0];
	position[1] = givenPosition[1];
	
	// Create defaults of class
	alpha = 255;
	sourceRectangle = givenImage;
	isActive = false;
	frameCount = std::pair<int, int>(3,4);
	currentFrame = std::pair<int, int>(1, 0);
}

void Animation::unloadContent()
{
	// Destroy bitmap
	al_destroy_bitmap(sourceRectangle);
}

void Animation::update(Animation& currentAnimation)
{
}

void Animation::draw(ALLEGRO_DISPLAY *display, double x, double y)
{
	// Given x and y values, draw the bitmap to the screen
	position[0] = x;
	position[1] = y;
	if (sourceRectangle != 0)
		al_draw_tinted_bitmap(sourceRectangle, al_map_rgba(255, 255, 255, alpha), 
			position[0], position[1], 0);
}

double &Animation::getAlpha()
{
	return alpha;
}

bool &Animation::getIsActive()
{
	return isActive;
}

std::pair<int, int> &Animation::modifiableFrameCount()
{
	return frameCount;
}

std::pair<int, int> &Animation::modifiableCurrentFrame()
{
	return currentFrame;
}

std::pair<int, int> &Animation::getFrameDimensions()
{
	// Now that image is assigned, we can assign the frame dimensions
	// and return them
	std::pair<int, int> frameDimensions(al_get_bitmap_width(image) / frameCount.first,
		al_get_bitmap_height(image) / frameCount.second);
		
	return frameDimensions;
}

ALLEGRO_BITMAP* Animation::Image()
{
	return image;
}

ALLEGRO_BITMAP*& Animation::returnSourceRectangle()
{
	return sourceRectangle;
}
