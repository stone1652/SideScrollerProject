#include "CollisionDetection.h"
#include <iostream>

CollisionDetection::CollisionDetection()
{
}

CollisionDetection::~CollisionDetection()
{
}

bool CollisionDetection::checkForCollision(ObjectDimensions player, ObjectDimensions obj)
{
	// If player is technically "inside" object, return true, else, return false
	if(!(player.getMaxX() < obj.getMinX() || player.getMinX() > obj.getMaxX()))
		if(!(player.getMaxY() < obj.getMinY() || player.getMinY() > obj.getMaxY()))
			return true;
					
	return false;
}

bool CollisionDetection::checkForPlayerAtEdgeOfScreen(ObjectDimensions player)
{
	// Use default values for our program. May change to variable. Check
	// if it's within the parameters of the screen
	if (player.getMinX() < 0 || player.getMaxX() > 800 || player.getMinY() < 0 || player.getMaxY() > 600)
		return true;
		
	return false;
}

void CollisionDetection::fixCollision(ObjectDimensions& player, ObjectDimensions& obj)
{
	// Only called if there is a collision. Fix the collision on each
	// side
	fixCollisionLeftSide(player, obj);
	fixCollisionRightSide(player, obj);
	fixCollisionTopPlatform(player, obj);
	fixCollisionBottomPlatform(player, obj);
					
}

void CollisionDetection::fixCollisionAtEdgeOfScreen(ObjectDimensions& player)
{
	if (player.getMinX() < 0)
		player.setMinX(0 - player.getMinX());
	else if (player.getMaxX() > 800)
		player.setMinX(player.getMinX() - (player.getMaxX() - 800));
	else if (player.getMinY() < 0)
		player.setMinY(0 - player.getMinY());
	else if (player.getMaxY() > 600)
		player.setMinY(player.getMinY() - (600 - (player.getMaxY() - 600)));
}

void CollisionDetection::fixCollisionLeftSide(ObjectDimensions& player, ObjectDimensions& obj)
{
	if (player.getMaxX() >= obj.getMinX())
		if ((player.getMaxX() - obj.getMinX()) < (obj.getMaxX() - player.getMinX()))
			if ((player.getMaxX() - obj.getMinX()) < (obj.getMaxY() - player.getMinY()))
				if ((player.getMaxX() - obj.getMinX()) < (player.getMaxY() - obj.getMinY()))
					player.setMinX(player.getMinX() - (player.getMaxX() - obj.getMinX()));
}

void CollisionDetection::fixCollisionRightSide(ObjectDimensions& player, ObjectDimensions& obj)
{				
	if (player.getMinX() <= obj.getMaxX())
		if ((obj.getMaxX() - player.getMinX()) < (player.getMaxX() - obj.getMinX()))
			if ((obj.getMaxX() - player.getMinX()) < (obj.getMaxY() - player.getMinY()))
				if ((obj.getMaxX() - player.getMinX()) < (player.getMaxY() - player.getMinY()))
					player.setMinX(player.getMinX() + (obj.getMaxX() - player.getMinX()));
}

void CollisionDetection::fixCollisionTopPlatform(ObjectDimensions& player, ObjectDimensions& obj)
{
	if (player.getMaxY() >= obj.getMinY())
		if ((player.getMaxY() - obj.getMinY()) < (player.getMaxX() - obj.getMinX()))
			if ((player.getMaxY() - obj.getMinY()) < (obj.getMaxX() - player.getMinX()))
				if ((player.getMaxY() - obj.getMinY()) < (obj.getMaxY() - player.getMinY()))
					player.setMinY(player.getMinY() - (player.getMaxY() - obj.getMinY()));
}

void CollisionDetection::fixCollisionBottomPlatform(ObjectDimensions& player, ObjectDimensions& obj)
{
	if (player.getMinY() <= obj.getMaxY())
		if ((obj.getMaxY() - player.getMinY()) < (player.getMaxX() - obj.getMinX()))
			if ((obj.getMaxY() - player.getMinY()) < (obj.getMaxX() - player.getMinX()))
				if ((obj.getMaxY() - player.getMinY()) < (player.getMaxY() - obj.getMinY()))
					player.setMinY(player.getMinY() + (obj.getMaxY() - player.getMinY()));
}

bool CollisionDetection::isOnTopPlatform(ObjectDimensions& player, ObjectDimensions& obj)
{
	if (player.getMaxY() == obj.getMinY() +10)
		return true;
	return false;
}
