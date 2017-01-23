#include "Obtacles.h"

Obtacles::Obtacles(Layer* layer, float vec)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	//Gán vận tốc X cho Obtacles
	velocityX = 200;

	//Tạo Obtacles phía dưới
	int i = random(0, 5);

	switch (i)
	{
		
		case 0:
			bottomTexture = Sprite::create("clinton2.png");
			bottomTexture->setTag(i);
			break;
		case 1:
			bottomTexture = Sprite::create("1.png");
			bottomTexture->setTag(i);
			break;
		case 2:
			bottomTexture = Sprite::create("2.png");
			bottomTexture->setTag(i);
			break;
		case 3:
			bottomTexture = Sprite::create("3.png");
			bottomTexture->setTag(i);
			break;
		case 4:
			bottomTexture = Sprite::create("4.png");
			bottomTexture->setTag(i);
			break;
		case 5:
			bottomTexture = Sprite::create("superman.png");
			bottomTexture->setTag(i);
			break;
	}
	//Mình sẽ random tọa độ Y cho cái Obtacles, nó sẽ trong khoảng trừ 1/4 chiều cao hình đến 1/3 chiều cao hình
	float randomY = RandomHelper::random_int((int)visibleSize.height/4, (int)visibleSize.height - (int)bottomTexture->getContentSize().height);

	//Và gán vị trí cho nó
	bottomTexture->setAnchorPoint(Vec2(0,0));
	bottomTexture->setPosition(origin.x + visibleSize.width, 0);

	//Tạo PhysicsBody cho Obtacles bên dưới
	bottomBody = PhysicsBody::createBox(bottomTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	//Body mặc định là dynamic, có nghĩa là "động" kiểu như nó sẽ di chuyển nếu bị tác động vật lý
	//nếu setDynamic(false) nó sẽ không di chuyển
	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::OBC);
	//Mình có thể đặt giá trị 0 để không va chạm với body nào hết
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::OBJ);

	//Gán body cho Sprite
	bottomTexture->setPhysicsBody(bottomBody);

	//Gán Sprite này vào layer hiện tại
	layer->addChild(bottomTexture,100);

	//Tương tự mình tạo Obtacles bên trên
	
	//Score Line
	//Là đối tượng để mình tính điểm nếu Pixel đi qua nó

	//Và mình sẽ di chuyển cái Obtacles này
	endPositionX = origin.x - bottomTexture->getContentSize().width / 2;
	isMoveFinished = false;

	//Thời gian di chuyển = quảng đường / vận tốc
	//vậy thời gian = visibleSize.width / velocityX
	//Khi di chuyển đến endPositionX mình sẽ gọi hàm moveFinished
	bottomTexture->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.width / velocityX, Point(endPositionX, bottomTexture->getPositionY())), CallFunc::create(CC_CALLBACK_0(Obtacles::moveFinished, this))));
	
}

void Obtacles::addVec(float dt)
{
	velocityX += dt;
}
void Obtacles::moveFinished()
{
	//Khi mà di chuyển kết thúc, mình sẽ remove nó ra khỏi layer hiện tại
	bottomTexture->removeFromParent();

	isMoveFinished = true;
}

