#include "GameScreen.h"
#include "Platform.h"

GameScreen::GameScreen()
{
	userPlayer = new Player();
	userPlatform = new Platform();
	cd.setPlayer(userPlayer);
}

GameScreen::~GameScreen()
{
	delete userPlayer;
	delete userPlatform;
}
 
void GameScreen::loadContent()
{
	bitmap = al_load_bitmap("./imgFiles/backdrop.bmp");
	userPlayer->loadPlayer();
	userPlatform ->loadPlatform();
}

void GameScreen::unloadContent()
{
	userPlayer->unloadPlayer();
	userPlatform ->unloadPlatform();
}

void GameScreen::updateContent(ALLEGRO_EVENT ev)
{
	cd.calculateFloor();
	userPlayer->update(ev);
}

void GameScreen::draw(ALLEGRO_DISPLAY *display)
{
	al_draw_bitmap(bitmap, 0, 0, 0);
	userPlayer->draw(display);
	userPlatform ->draw();
}
