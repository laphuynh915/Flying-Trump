#include "Object.h"
#include "Definition.h"

USING_NS_CC;


ObjectPIT::ObjectPIT(Layer* layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	this->setPos(0, 0);
	this->batchNodeCreate();
	
	//Tạo sprite cho Pixel, và set vị trí cho nó
	
/*  object = Sprite::create("khunglong.png");
	object->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); */

	//Tạo PhysicsBody cho pixelTexture
	
	//objectBody = PhysicsBody::createBox(object->getContentSize(), PhysicsMaterial(0, 0, 0));
	objectBody = PhysicsBody::createBox(spritebatch->getContentSize(), PhysicsMaterial(0, 0, 0));
	
	
	//Gán giá trị để xét va chạm cho body, mình sẽ giải thích thêm ở dưới
	//Gán Category Bitmask cho body
	//Có thể hiểu là "Tao là PIXEL nè!"
	
	objectBody->setCategoryBitmask(eObjectBitmask::OBJ);
	
	//Gán CollisionBitmask cho body
	//Hiểu đơn giản là "Tao có thể chạm với PIPE"
	objectBody->setCollisionBitmask(eObjectBitmask::OBJ);
	//Gán ContactTestBitmask cho body, tương tự Collision mà nó sẽ gọi các hàm onContact...
	//Hiểu đơn giản là "Tao sẽ gọi cho onContact... khi chạm với PIPE hoặc LINE"
	
	
	objectBody->setContactTestBitmask(eObjectBitmask::OBC);

	//Cuối cùng là gán body cho Sprite thôi :p
	
	//object->setPhysicsBody(objectBody);
	sprite1->setPhysicsBody(objectBody);
	//layer->addChild(object, 100);
	layer->addChild(spritebatch,100);
	//spritebatch->setScale(0.25);
	//spritebatch->setAnchorPoint(Vec2(0, 0));
	//spritebatch->setPosition(origin.x , origin.y);
	//Các giá trị mặc định cho các biến
	velocityY = 0.0f;
	rotation = 0.0f;

}

void ObjectPIT::Update()
{

	if (isFalling)
	{
		if (sprite1->getPositionY() > ofObject.height)
		{
			velocityY = -2;
		}
		else
		{
			velocityY = 0;
		}
	}
	else
	{
		if (sprite1->getPositionY() < (Director::getInstance()->getVisibleSize().height - sprite1->getContentSize().height/8))
			velocityY = 6;
		else
			velocityY = 0;
	}

	
	//Nếu mà nó đang rơi

	sprite1->setPosition(Vec2(sprite1->getPositionX(), sprite1->getPositionY() + velocityY));
}

void ObjectPIT::Jump()
{
	//Bay
	isFalling = false;
}

void ObjectPIT::Fall()
{
	//Rơi
	isFalling = true;
}


void ObjectPIT::batchNodeCreate()
{
	spritebatch = SpriteBatchNode::create("trump.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("trump.plist");
    sprite1 = Sprite::createWithSpriteFrameName("trump1.png");
	sprite1->setAnchorPoint(Vec2(0, 0));
	sprite1->setScale(0.25);
	
	spritebatch->addChild(sprite1);
	sprite1->setPosition(100,200);
	animate = Animate::create(ObjectPIT::createAnimation("trump", 8, 0.1));
	animate->retain();
	sprite1->runAction(RepeatForever::create(animate));
	
}

Animation* ObjectPIT::createAnimation(std::string preFixName, int pFrames, float Delay){

	Vector<SpriteFrame*> animFrames;

	
	for (int i = 1; i <= pFrames; i++)
	{
		char btr[20] = { 0 };
		sprintf(btr, "%d.png", i);
		std::string str = preFixName + btr;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	 animation = Animation::createWithSpriteFrames(animFrames, Delay);
	return animation;

}


void ObjectPIT::spritePause()
{
	sprite1->pause();
	spritebatch->pause();
}

void ObjectPIT::setPos(float w , float h)
{
	ofObject.height = h;
	ofObject.width = w;
}