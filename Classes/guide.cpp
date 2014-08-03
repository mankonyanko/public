#include "guide.h"
#include "intro.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* guide::createScene()
{
	auto scene = Scene::create();
	auto layer = guide::create();
	scene->addChild(layer);
	return scene;
}

bool guide::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 0, 255)))
	{
		return false;
	}


	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("Images/start_map.tmx");
	floor = tmap->getLayer("Floor");
	wall = tmap->getLayer("Wall");
	this->addChild(tmap, 0, 11);

	TMXObjectGroup* objects = tmap->getObjectGroup("Point");
	ValueMap& spawnPoint = objects->getObject("Spawn");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	playerPosition = Point(x, y);

	this->createPlayer();
	this->setViewpointCenter(player->getPosition());


	return true;
}

void guide::onEnter()
{
	Layer::onEnter();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(guide::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(guide::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}

void guide::onExit()
{
	_eventDispatcher->removeEventListeners(EventListener::Type::KEYBOARD);

	Layer::onExit();
}

void guide::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	isLeftPressed = false;
	isRightPressed = false;
	isUpPressed = false;
	isDownPressed = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		isUpPressed = true;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		isDownPressed = true;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isRightPressed = true;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		isLeftPressed = true;
	}

	if (isLeftPressed == true || isRightPressed == true || isUpPressed == true || isDownPressed == true)
	{
		this->startMovingPlayer();
	}



	this->setViewpointCenter(player->getPosition());
}

void guide::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		isUpPressed = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		isDownPressed = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		isRightPressed = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		isLeftPressed = false;
	
	if (isLeftPressed == false && isRightPressed == false && isUpPressed == false && isDownPressed == false)
	{
		log("released %d", keyCode);
		this->stopMovingPlayer();
	}
}

void guide::startMovingPlayer()
{
	//if ((isLeftPressed == true && isRightPressed == true) || (isUpPressed == true && isDownPressed == true))
	//	return;

	this->schedule(schedule_selector(guide::movePlayer));
}

void guide::stopMovingPlayer()
{

	this->unschedule(schedule_selector(guide::movePlayer));
}

void guide::movePlayer(float t)
{
	speed = 3;
	auto moveStepV = speed;
	auto moveStepH = speed;
	if (isLeftPressed && player->getPositionX() > 0) {
		moveStepV = -speed;
	}
	else if (isRightPressed && player->getPositionX() < (tmap->getMapSize().width * tmap->getTileSize().width)){
		moveStepV = speed;
	}
	else
	{
		moveStepV = 0;
	}
	if (isDownPressed && player->getPositionY() > 0){
		moveStepH = -speed;
	}
	else if (isUpPressed && player->getPositionY() < (tmap->getMapSize().height * tmap->getTileSize().height)){
		moveStepH = speed;
	}
	else{
		moveStepH = 0;
	}

	auto newPos = Point(player->getPosition().x + moveStepV, player->getPosition().y + moveStepH);

//	auto crashPosLD = newPos - Point(50, 50);
//	auto crashPosRU = newPos + Point(50, 50);

	Point tileCoord = this->tileCoordForPosition(newPos);
	int tileGid = this->wall->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		Value& properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull())
		{
			std::string wall = properties.asValueMap()["Wall"].asString();

			if (wall == "YES"){
				log("fuck");
				return;
			}

		}
	}
	player->setPosition(newPos);
	this->setViewpointCenter(player->getPosition());

}

void guide::createPlayer()
{
	///////

	///////

	player = Sprite::create("Images/block.png");
	player->setPosition(playerPosition);
	this->addChild(player);

}


void guide::setViewpointCenter(Point position)
{
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Point actualPosition = Point(x, y);
	Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}


Point guide::tileCoordForPosition(Point position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y)
		/ tmap->getTileSize().height;
	return Point(x, y);
}

