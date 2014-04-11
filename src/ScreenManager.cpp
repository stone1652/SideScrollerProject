#include "ScreenManager.h"
#include "TitleScreen.h"
#include "SplashScreen.h"

GameScreenInterface *currentScreen, *newScreen;

ScreenManager::ScreenManager()
{
}

ScreenManager::~ScreenManager()
{
}

ScreenManager::ScreenManager(const ScreenManager& screen)
{
}

ScreenManager &ScreenManager::operator=(const ScreenManager& newScreen)
{
}

ScreenManager &ScreenManager::GetInstance()
{
	static ScreenManager newInstance;
	return newInstance;
}

void ScreenManager::Initialize()
{
	currentScreen = new SplashScreen();
}

void ScreenManager::addScreen(GameScreenInterface *screen)
{
	transition.setAlpha(0);
	startOfTransition = true;
	newScreen = screen;
	transition.setIsActive(true);
}

void ScreenManager::loadContent()
{
	startOfTransition = false;
	currentScreen->loadContent();
	transitionImage = al_load_bitmap("./imgFiles/black-wallpapers.jpg");
	double position[] = {0,0};
	transition.loadContent(transitionImage, "", position);
}

void ScreenManager::unloadContent()
{
	al_destroy_bitmap(transitionImage);
	transition.unloadContent();
}

void ScreenManager::update(ALLEGRO_EVENT ev)
{
	if (!startOfTransition)
		currentScreen->updateContent(ev);
	else
		transitionHandler();
	
}

void ScreenManager::draw(ALLEGRO_DISPLAY *display)
{
	currentScreen->draw(display);
	
	if(startOfTransition)
		transition.draw(display);
}

void ScreenManager::transitionHandler()
{
	transition.update(currentScreen->getInput());
	if (transition.getAlpha() >= 255)
	{
		transition.setAlpha(255);
		currentScreen->unloadContent();
		delete currentScreen;
		currentScreen = newScreen;
		currentScreen->loadContent();
		al_rest(1.0);
	}
	else if (transition.getAlpha() <= 0)
	{
		startOfTransition = false;
		transition.setIsActive(false);
	}
}
