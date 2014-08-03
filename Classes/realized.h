#ifndef __game_hajimaruyo_H__
#define __game_hajimaruyo_H__

#include "cocos2d.h"

class game : public cocos2d::LayerColor
{
public:
	
	static cocos2d::Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(game);

	cocos2d::Size winSize;
	cocos2d::Point playerPosition;
	cocos2d::Sprite* player;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* floor;
	cocos2d::TMXLayer* wall;

	bool isLeftPressed;
	bool isRightPressed;
	bool isUpPressed;
	bool isDownPressed;
	int speed;

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onEnter();
	void onExit();
	void createSpriteParallax();

	void createPlayer();
	void setViewpointCenter(cocos2d::Point position);
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);
	//void setPlayerPosition(cocos2d::Point position);
	void startMovingPlayer();
	void stopMovingPlayer();
	void movePlayer(float t);

};

#endif 
