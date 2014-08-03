#include "realized.h"
#include "intro.h"
#include "magecreate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* game::createScene()
{
	auto scene = Scene::create();
	auto layer = game::create();
	scene->addChild(layer);
	return scene;
}

bool game::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 0, 255)))
	{
		return false;
	}

	maze* Maze = new maze(100);
	Maze->mazecreate();
	Maze->mazechange();
	


	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("Images/test0725.tmx");
	floor = tmap->getLayer("Floor");
	wall = tmap->getLayer("Wall");
	this->addChild(tmap, 0, 11);

	int gid = this->wall->getTileGIDAt(Point(0,0));

	Value& properties = tmap->getPropertiesForGID(gid);
	Point Vec2;
	for (int i = 0; i <= 200; i++)
	{
		for (int k = 0; k <= 200; k++)
		{
			Vec2.setPoint(i, k);
			if (Maze->maze_map[i][k] == 0)
			{
				this->wall->removeTileAt(Vec2);
			}
		}
	}


	TMXObjectGroup* objects = tmap->getObjectGroup("Point");
	ValueMap& spawnPoint = objects->getObject("Spawn");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	playerPosition = Point(x, y);

	this->createPlayer();
	this->setViewpointCenter(player->getPosition());


	return true;
}

void game::onEnter()
{
	Layer::onEnter();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(game::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(game::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}

void game::onExit()
{
	_eventDispatcher->removeEventListeners(EventListener::Type::KEYBOARD);

	Layer::onExit();
}

void game::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
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
		log("pressed %d", keyCode);
		this->startMovingPlayer();
	}



	this->setViewpointCenter(player->getPosition());
}

void game::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		isUpPressed = false;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		isDownPressed = false;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isRightPressed = false;

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		isLeftPressed = false;

	}

	if (isLeftPressed == false && isRightPressed == false && isUpPressed == false && isDownPressed == false)
	{
		log("released %d", keyCode);
		this->stopMovingPlayer();
	}
}

void game::startMovingPlayer()
{
	//if ((isLeftPressed == true && isRightPressed == true) || (isUpPressed == true && isDownPressed == true))
	//	return;

	this->schedule(schedule_selector(game::movePlayer));
}

void game::stopMovingPlayer()
{

	this->unschedule(schedule_selector(game::movePlayer));
}

void game::movePlayer(float t)
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

void game::createPlayer()
{
	///////

	///////

	player = Sprite::create("Images/block.png");
	player->setPosition(playerPosition);
	this->addChild(player);

}


void game::setViewpointCenter(Point position)
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


Point game::tileCoordForPosition(Point position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y)
		/ tmap->getTileSize().height;
	return Point(x, y);
}

