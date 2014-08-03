#include "intro.h"
#include "guide.h"
#include "realized.h"
#include "SimpleAudioEngine.h"
#define MUSIC_FILE "Images/Intro_temp.mp3"

USING_NS_CC;

Scene* mage::createScene()
{
    auto scene = Scene::create();

    auto layer = mage::create();

    scene->addChild(layer);

    return scene;
}

bool mage::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0, 0, 0)))
	{
		return false;
	}

	auto bg = Sprite::create("Images/Intro_temp.png");
	bg->setPosition(Point(400, 300));
	this->addChild(bg);

	auto startB = MenuItemImage::create(
		"Images/gamestart_temp.png",
		"Images/gamestart_selected_png.png",
		CC_CALLBACK_1(mage::doreplaceTran, this));

	auto ExitB = MenuItemImage::create(
		"Images/exit_temp.png",
		"Images/exit_selected_temp.png",
		CC_CALLBACK_1(mage::doExit, this));
	auto LoadB = MenuItemImage::create(
		"Images/load_temp.png",
		"Images/load_temp_selected.png",
		CC_CALLBACK_1(mage::doLoad, this));
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE,true);

	auto pMenu = Menu::create(startB,LoadB,ExitB, NULL);
	pMenu->setPosition(Point(652, 600-468));
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	


    return true;
}


void mage::doreplaceTran(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(MUSIC_FILE);

	auto pScene = guide::createScene();
	Director::getInstance()->replaceScene(createTransition(17, 1, pScene));
}

TransitionScene* mage::createTransition(int nIndex, float t, Scene* s)
{
	Director::getInstance()->setDepthTest(false);
	
	return TransitionFade::create(t, s);
}
void mage::doExit(Object* pSender)
{
	Director::getInstance()->end();
}
void mage::doLoad(Object* pSender)
{
}