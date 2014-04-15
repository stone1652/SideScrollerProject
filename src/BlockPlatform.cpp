#include "BlockPlatform.h"
 
BlockPlatform::BlockPlatform()
{
	scrollerObstacleDimension.setMinX(800);
	scrollerObstacleDimension.setMinY(200 + rand() % 188);
	isDeadly = false;
	isBeingDrawn = false;
}
 
BlockPlatform::~BlockPlatform()
{
}
 
void BlockPlatform::loadScrollerObstacle()
{
	scrollerObstacleBitmap = al_load_bitmap("./assets/imgFiles/basicPlatform1.png");
	scrollerObstacleDimension.setImgWidth(al_get_bitmap_width(scrollerObstacleBitmap));
	scrollerObstacleDimension.setImgHeight(al_get_bitmap_height(scrollerObstacleBitmap));
	
	scrollerObstacleDimension.updateValues();
}
