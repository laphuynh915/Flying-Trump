#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "cocos2d.h"
USING_NS_CC;


class ObjectPIT{
public:
	ObjectPIT(Layer* layer);
	void Jump();
	void Update();

	void Fall();
	bool isFalling;
	bool done;
	Animation* animation;
	Animation *createAnimation(std::string preFixName, int pFrames, float Delay);
	Animate *animate;
	void batchNodeCreate();
	void spritePause();


	void setPos(float w, float h);
	int tag;

private:
    Size ofObject;
	float width;
	SpriteBatchNode* spritebatch;

	Sprite* object;
	Sprite* sprite1;
	PhysicsBody *objectBody;

	Size visibleSize;
	Vec2 origin;;


	float velocityY;
	float rotation;
};


#endif