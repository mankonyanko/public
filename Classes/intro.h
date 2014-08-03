#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class mage : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(mage);

	void mage::doreplaceTran(Object* pSender);
	void mage::doExit(Object* pSender);
	void mage::doLoad(Object* pSender);
	cocos2d::TransitionScene* createTransition(int nIdex, float t, cocos2d::Scene* s);



};

#endif // __HELLOWORLD_SCENE_H__
