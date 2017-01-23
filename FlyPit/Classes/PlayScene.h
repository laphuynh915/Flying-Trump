#ifndef __PlayScene_SCENE_H__
#define __PlayScene_SCENE_H__

#include "cocos2d.h"
#include "Object.h"
#include "Obtacles.h"
#include "InfiniteParallaxNode.h"
#define SCROLLING_BACKGROUND_SPEED 0.01
USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
	InfiniteParallaxNode* _backgroundElements;
	float randomValueBetween(float low, float high);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void onMouseDown(Event* _event);
	void update(float dt);
	void onExit();
	bool onContactBegin(PhysicsContact &contact);
	void createOBC(float dt);
	//void onMouseDown(Event* _event);
	//void update(float dt);
	//void onExit();
	//bool onContactBegin(PhysicsContact &contact);
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);

private:
	Sprite *background1;
	Sprite *background2;


	Size visibleSize;
	Vec2 origin;
	void pixelFall(float dt);
	ObjectPIT* pixel;

	

	
	void OBCeMoveFinished();
	std::list<Obtacles*> listPipes;

	bool isDead = false;
	float vec = 400 ;
	LabelTTF* scoreLabel;
	float score;
	
};

#endif // __PlayScene_SCENE_H__








