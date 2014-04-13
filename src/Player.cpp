#include "Player.h"

Player::Player()
{
	playerDimensions.setMinX(10);
	playerDimensions.setMinY(388);
}
 
Player::~Player()
{
}

void Player::setXStatic()
{
	playerDimensions.setMinX(lastXPosition);
}



void Player::movePlayer(ALLEGRO_EVENT e)
{
	switch(e.keyboard.keycode)
	{
		case ALLEGRO_KEY_S:
			playerAnimation.getIsActive() = true;
			direction = Direction::DOWN;
			break;
		case ALLEGRO_KEY_W:
			playerAnimation.getIsActive() = true;
			direction = Direction::UP;
			break;
		case ALLEGRO_KEY_D:
			playerAnimation.getIsActive() = true;
			direction = Direction::RIGHT;
			playerDimensions.setMinX(playerDimensions.getMinX() + moveSpeed);
			break;
		case ALLEGRO_KEY_SPACE:
			playerAnimation.getIsActive() = true;
			if(floor > 0 && playerDimensions.getMinY() == floor)
			{
				setY(0-moveSpeed);
				jumpCounter = 5;
				jump = true;
			}
			if(playerDimensions.getMinY() == stageFloor)
			{
				setY(0-moveSpeed);
				jumpCounter = 5;
				jump = true;
			}
			break;
		case ALLEGRO_KEY_A:
			playerAnimation.getIsActive() = true;
			direction = Direction::LEFT;
			playerDimensions.setMinX(playerDimensions.getMinX() - moveSpeed);
			break;
		default:
			//playerAnimation.getIsActive() = false;
			break;
	}
}


void Player::setFloor(double fl)
{	
	floor = fl;
}

int Player::getLastXPosition()
{
	return lastXPosition;
}

void Player::gravityTick()
{
	setY(10);
}

void Player::jumpTick()
{
	if(jump)
	{
		jCount++;
		setY(-40);
		if(jCount > 5)
		{
			jump = false;
			jCount = 0;
		}
	}
}

void Player::setY(double speed)
{

	if(floor > 0)
	{
		if(playerDimensions.getMinY() <= floor && speed < 0)
			playerDimensions.setMinY(playerDimensions.getMinY() + speed);
		else if(speed > 0 && playerDimensions.getMinY() < floor)
			playerDimensions.setMinY(playerDimensions.getMinY() + speed);
		else if (playerDimensions.getMinY() > floor)
			playerDimensions.setMinY(floor);
	}
	else
	{
		if(playerDimensions.getMinY() <= stageFloor && speed < 0)
			playerDimensions.setMinY(playerDimensions.getMinY() + speed);
		else if(speed > 0 && playerDimensions.getMinY() < stageFloor)
			playerDimensions.setMinY(playerDimensions.getMinY() + speed);
		else if (playerDimensions.getMinY() > stageFloor)
			playerDimensions.setMinY(stageFloor);
	}
}
 
void Player::loadPlayer()
{
	playerBitmap = al_load_bitmap("./imgFiles/image.png");
	playerDimensions.setImgWidth(al_get_bitmap_width(playerBitmap) / 3);
	playerDimensions.setImgHeight(al_get_bitmap_height(playerBitmap) / 4);
	playerDimensions.updateValues();
	
	double position[] = {playerDimensions.getMinX(), playerDimensions.getMinY()};
	playerAnimation.loadContent(playerBitmap, "", position);
	
	playerAnimation.getIsActive() = true;
	direction = Direction::DOWN;
}


void Player::unloadPlayer()
{
	al_destroy_bitmap(playerBitmap);
	playerAnimation.unloadContent();
}

void Player::update(ALLEGRO_EVENT ev, InputManagement input)
{
	input.update();
		
	movePlayer(ev);
	jumpTick();
	gravityTick();
	
	playerAnimation.modifiableCurrentFrame().second = direction;
	ssAnimation.update(playerAnimation);
}

void Player::draw(ALLEGRO_DISPLAY *display)
{
	playerAnimation.draw(display, playerDimensions.getMinX(),
						 playerDimensions.getMinY());
}

ObjectDimensions Player::getCurrentDimensions()
{
	return playerDimensions;
}
