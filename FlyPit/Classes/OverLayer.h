#ifndef __Overlayer_SCENE_H__
#define __Overlayer_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class Overlayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setScore(int _score);
    // implement the "static create()" method manually
    CREATE_FUNC(Overlayer);
private:

	void gotoMenuScene();
	void gotoPlayScene();
	int score;
	LabelTTF* scoreLabel;
};

#endif // __Overlayer_SCENE_H__
