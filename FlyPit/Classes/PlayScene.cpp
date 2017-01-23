#include "PlayScene.h"
#include "OverLayer.h"
#include  <SimpleAudioEngine.h>

auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{

	



	// sound effect.
	audio->preloadEffect("Make america greate again.wav");
	audio->preloadEffect("buble.wav");
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto ground = Sprite::create("full-background.png");
	ground->setAnchorPoint(Point(0, 0));
	ground->setPosition(Point::ZERO);
	addChild(ground, 1);


	background1 = Sprite::create("hehe1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(origin.x, origin.y));

	background2 = Sprite::create("hehe1.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(origin.x + background1->getContentSize().width, origin.y));

	// add the sprite as a child to this layer
	this->addChild(background1, 2);
	this->addChild(background2, 2);


	pixel = new ObjectPIT(this);
	pixel->setPos(background1->getContentSize().width/12,background1->getContentSize().height/8);
	audio->playEffect("Make america greate again.wav", false, 1.0f, 1.0f, 1.0f);
	
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PlayScene::onMouseDown, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//this->scheduleUpdate();
	this->schedule(schedule_selector(PlayScene::createOBC), 0.5f);
	//Mình bỏ 1 pipe mới vào listPipes
	listPipes.push_back(new Obtacles(this,400));

	score = 0;
	
	scoreLabel = LabelTTF::create("0", "fonts/vgafix.ttf", 100);
	scoreLabel->setScale(0.4);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);

	this->addChild(scoreLabel, 50);
	

    return true;
}

void PlayScene::update(float dt)
{
	background1->setPositionX(background1->getPositionX() - (SCROLLING_BACKGROUND_SPEED * 200));
	background2->setPositionX(background2->getPositionX() - (SCROLLING_BACKGROUND_SPEED * 200));

	if (background1->getPositionX() <= -background1->getContentSize().width)
	{
		background1->setPositionX(background2->getPositionX() + background2->getContentSize().width);
	}

	if (background2->getPositionX() <= -background2->getContentSize().width)
	{
		background2->setPositionX(background1->getPositionY() + background1->getContentSize().width);
	}
	//Mình sẽ duyệt từng Pipe, nếu đã kết thúc mình sẽ xóa nó đi
	for (std::list<Obtacles*>::iterator pipe = listPipes.begin(); pipe != listPipes.end(); pipe++)
	{
		if ((*pipe)->isMoveFinished)
		{
			CC_SAFE_DELETE((*pipe));
			listPipes.remove(*pipe);
			break;
		}
	}
	//Gọi hàm Update của Pixel
	pixel->Update();
	score+= 0.02;
	scoreLabel->setScale(0.4);
	scoreLabel->setString(String::createWithFormat("%d", int(score))->getCString());
	//Nếu mà mình chết
	if (isDead)
	{
		//Thì sẽ xóa Label đi
		//this->removeChild(scoreLabel);
		//Pause game lại không cho update nữa.
		this->pause();

		//Vì pause() ở trên mới có ở layer hiện tại, mình cần pause tất cả các con của nó bên trong
		Vector <cocos2d::Node*> childs = this->getChildren();
		for (int i = 0; i < childs.size(); i++)
		{
			childs.at(i)->pause();
		}


		Overlayer* overlayer = Overlayer::create();
	

		overlayer->setScore(score);

		overlayer->setPosition(origin.x, origin.y);
		this->addChild(overlayer, 110);
	}

}
void PlayScene::createOBC(float dt)
{
	 vec += 20;
	//Đẩy một cái pipe mới vào thôi
	auto A = new Obtacles(this,400);

	listPipes.push_back(A);
}

void PlayScene::onMouseDown(Event* _event)
{
	//Mình sẽ lấy sự kiện Chuột trái click
	EventMouse* mouse = (EventMouse*)_event;
	audio->playEffect("buble.wav", false, 1.0f, 1.0f, 1.0f);
	if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
	
		//Nếu mà nó click, pixel sẽ bay lên
		
			pixel->Jump();
			//Và sau 0.2s lại rớt xuống, gọi hàm pixelFall
			this->scheduleOnce(schedule_selector(PlayScene::pixelFall), 0.2);

	}
}

void PlayScene::onExit()
{
	//Phải gọi hàm onExit của Layer để nó làm mấy việc của Layer khi thoát ra
	Layer::onExit();

	//Xóa pixel đi
	CC_SAFE_DELETE(pixel);

	//Xóa listPipes đi
	while (!listPipes.empty())
	{
		CC_SAFE_DELETE(listPipes.front());
		listPipes.pop_front();
	}
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	//Mình lấy 2 cái đối tượng mà nó va chạm với nhau ra
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();
	auto target = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tag1 = target->getTag();
	target = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag2 = target->getTag();
	//Nếu A và B là PIPE và PIXEL thì mình chết
	if (tag1 == 5 || tag2 == 5)
	{
	}
	else
	{
		if ((shapeA->getCategoryBitmask() == eObjectBitmask::OBC && shapeB->getCategoryBitmask() == eObjectBitmask::OBJ) ||
			(shapeB->getCategoryBitmask() == eObjectBitmask::OBC && shapeA->getCategoryBitmask() == eObjectBitmask::OBJ))
		{
			//Teo...
			isDead = true;
		}
	}

	return true;
}

float PlayScene::randomValueBetween(float low, float high)
{
	return (((float)rand() / RAND_MAX) * (high - low)) + low;
}

void PlayScene::pixelFall(float dt)
{
	pixel->Fall();
}
void PlayScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
