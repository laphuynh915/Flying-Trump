#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void gotoPlayScene();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);


};

#endif // __MenuScene_SCENE_H__
