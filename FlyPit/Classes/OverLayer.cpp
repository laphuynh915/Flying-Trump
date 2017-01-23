#include "OverLayer.h"
#include "MenuScene.h"
#include "PlayScene.h"
USING_NS_CC;

Scene* Overlayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Overlayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Overlayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto overPanel = Sprite::create("Gameover.png");
	overPanel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(overPanel);

	//Score
	//Tạo LabelTTF
	scoreLabel = LabelTTF::create("0", "fonts/vgafix	.ttf", 120);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY());

	this->addChild(scoreLabel);

	//Button
	//Tương tự như Play Button, mình tạo 2 nút menu, replay và gắn nó vô menu thôi
	auto menuBtn = MenuItemImage::create("MenuBtn.png", "MenuBtn_Selected.png", CC_CALLBACK_0(Overlayer::gotoMenuScene, this));
	auto replayBtn = MenuItemImage::create("ReplayBtn.png", "ReplayBtn_Selected.png", CC_CALLBACK_0(Overlayer::gotoPlayScene, this));

	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	//Chỉnh align cho mấy cái nút, cách nhau 50
	menu->alignItemsHorizontallyWithPadding(50);

	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - 100);

	this->addChild(menu);
    
    return true;
}


void Overlayer::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
}

void Overlayer::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
void Overlayer::setScore(int _score)
{
	score = _score;
	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
}


void Overlayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
