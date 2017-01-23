#ifndef __OBC_H__
#define __OBC_H__

#include "cocos2d.h"
#include "Definition.h"

USING_NS_CC;

class Obtacles
{
public:
	Obtacles(Layer* layer, float vec);

	void addVec(float dt);
	void moveFinished();
	bool isMoveFinished;
	void setPos(float w, float h);
	void OBCsetPositionAndAction(float w, float h, Layer* layer);

private:
	Size ofObject;
	Sprite  *bottomTexture;
	PhysicsBody  *bottomBody;

	Size visibleSize;
	Vec2 origin;

	float velocityX;
	float endPositionX;

};

#endif //__PIPE_H__