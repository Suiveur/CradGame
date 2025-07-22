#include "MainScene.h"
#include "GameTestScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初始化背景和按键
    initBackGround();

    return true;
}

void MainScene::initBackGround()
{
    // 创建白色背景层
    auto background = cocos2d::LayerColor::create(Color4B(240, 240, 240, 255));

    // 设置背景尺寸为整个游戏区域
    background->setContentSize(this->getContentSize());
    background->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    background->setPosition(cocos2d::Vec2::ZERO);

    // 添加到游戏视图的最底层
    this->addChild(background, -1); // zOrder设为-1确保在底层

    Size visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("%f,%f", visibleSize.width, visibleSize.height);
    auto button = ui::Button::create("./res/play_normal.png", "./res/play_selected.png","./res/play_disable.png");

    button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    button->setPosition(Vec2(visibleSize / 2));
    button->setTitleText("Start");
    button->setScale(1.5f, 1.5f);

    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(GameTestScene::createScene());
            CCLOG("Button start clicked");
            break;
        default:
            break;
        }
        });
    this->addChild(button);
    
}

