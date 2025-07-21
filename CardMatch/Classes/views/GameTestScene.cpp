#include "GameTestScene.h"
#include "ui/CocosGUI.h"
#include <math.h>
USING_NS_CC;

Scene* GameTestScene::createScene()
{
    return GameTestScene::create();
}

// on "init" you need to initialize your instance
bool GameTestScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    tag = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    initBackGround();

    initUndo();

    _gameController.startGame(1);
    auto playfieldCards = _gameController.getGameModel().playfieldCards;
    auto stackCrads = _gameController.getGameModel().stackCards;

    // 加载卡片
    for (auto card : playfieldCards) 
    {
        loadCard(card);
    }
    for (auto card : stackCrads)
    {
        loadCard(card);
    }
    _trcy.set(_allCard.back()->getPosition());
    updateCanTouch();
    _trcyCount = 0;// 一张底牌

    return true; 
}

void GameTestScene::initUndo()
{
    ui::Button* undoBtn = ui::Button::create("./res/undo.png");
    undoBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    undoBtn->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 20, 400));
    undoBtn->setScale(2.f);
    this->addChild(undoBtn);
    int undoTag;
    undoBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        Vec2 pos;
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            undoTag = _gameController.undoOnce(pos);
            undoView(undoTag,pos);
            CCLOG("Button undo clicked");
            break;
        default:
            break;
        }
        });
}

void GameTestScene::loadCard(CardModel& card)
{
    auto cardSpr = Sprite::create("./res/card_general.png");

    cardSpr->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    cardSpr->setPosition(card.getPosition().x, card.getPosition().y + 400);

    Sprite* suit = loadSuit(card.getSuit());            // 加载花色
    suit->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    suit->setPosition(cardSpr->getContentSize().width - 20, cardSpr->getContentSize().height - 20);
    cardSpr->addChild(suit);

    std::string color = getCardColor(card.getSuit());   // 颜色
    std::string number = getCardNumber(card.getFace()); // 大小

    std::string smallFaceFileName = cocos2d::StringUtils::format(
        "./res/number/small_%s_%s.png", color.c_str(), number.c_str());
    Sprite* smallFace = Sprite::create(smallFaceFileName);
    smallFace->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    smallFace->setPosition(20, cardSpr->getContentSize().height - 20);
    cardSpr->addChild(smallFace);

    std::string bigFaceFileName = cocos2d::StringUtils::format(
        "./res/number/big_%s_%s.png", color.c_str(), number.c_str());
    Sprite* bigFace = Sprite::create(bigFaceFileName);
    bigFace->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bigFace->setPosition(cardSpr->getContentSize() / 2);
    cardSpr->addChild(bigFace);
    setupSpriteTouch(cardSpr);
    cardSpr->setTag(tag);
    tag++;
    this->addChild(cardSpr);

    // updateCanTouch(cardSpr);
    _allCard.push_back(cardSpr);

}

void GameTestScene::updateCanTouch()
{
    for (auto cardSpr : _allCard)
    {
        // 更新可被触摸的卡片
        std::vector<Sprite*> removeV;
        for (auto s : _canTouchSprite)
        {
            float dx = fabs(s->getPosition().x - cardSpr->getPosition().x);
            float dy = fabs(s->getPosition().y - cardSpr->getPosition().y);
            // 遮盖
            if (dx < cardSpr->getContentSize().width && dy < cardSpr->getContentSize().height)
            {
                removeV.push_back(s);
            }
        }
        for (auto r : removeV)
        {
            _canTouchSprite.remove(r);
        }
        _canTouchSprite.push_back(cardSpr);
    }

}

Sprite* GameTestScene::loadSuit(CardSuitType cardSuit)
{
    if (cardSuit == CST_CLUBS)
    {
        return Sprite::create("./res/suits/club.png");
    }
    else if (cardSuit == CST_SPADES)
    {
        return Sprite::create("./res/suits/spade.png");
    }
    else if (cardSuit == CST_DIAMONDS)
    {
        return Sprite::create("./res/suits/diamond.png");
    }
    else if (cardSuit == CST_HEARTS)
    {
        return Sprite::create("./res/suits/heart.png");
    }
    return Sprite::create();
}

std::string GameTestScene::getCardColor(CardSuitType suit)
{
    std::string color;
    if (suit == CST_CLUBS)
    {
        color = "black";
    }
    else if (suit == CST_SPADES)
    {
        color = "black";
    }
    else if (suit == CST_DIAMONDS)
    {
        color = "red";
    }
    else if (suit == CST_HEARTS)
    {
        color = "red";
    }
    else 
    {
        color = "?";
    }
    return color;
}

std::string GameTestScene::getCardNumber(CardFaceType cardFace)
{
    std::string number;
    if (cardFace >= 1 && cardFace <= 9)
    {
        number = std::to_string(cardFace + 1);
    }
    else
    {
        switch (cardFace)
        {
        case CFT_ACE:
            number = "A";
            break;
        case CFT_JACK:
            number = "J";
            break;
        case CFT_QUEEN:
            number = "Q";
            break;
        case CFT_KING:
            number = "K";
            break;
        default:
            number = "?";
        }
    }
    return number;
}

void GameTestScene::initBackGround()
{
    auto backgroundUp = cocos2d::LayerColor::create(Color4B(170, 121, 66, 255));
    auto backgroundDn = cocos2d::LayerColor::create(Color4B(148, 33, 146, 255));

    backgroundUp->setContentSize(Size(this->getContentSize()));
    backgroundUp->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    backgroundUp->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(backgroundUp, -1);// zOrder设为-1确保在底层

    // 设置背景尺寸为整个游戏区域
    backgroundDn->setContentSize(Size(this->getContentSize().width, this->getContentSize().height - 1400));
    backgroundDn->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    backgroundDn->setPosition(cocos2d::Vec2::ZERO);
    // 添加到游戏视图的最底层
    this->addChild(backgroundDn, -1); 
}

void GameTestScene::setupSpriteTouch(cocos2d::Sprite* sprite)
{
    auto listener = EventListenerTouchOneByOne::create();
    // 设置触摸吞噬，防止事件穿透
    listener->setSwallowTouches(true);

    // 触摸开始事件
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // 先刷新,避免Bug
        this->updateCanTouch();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        // 获取精灵在节点坐标系中的位置和尺寸
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

        // 转换触摸点到精灵的本地坐标系
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

        // 检查触摸点是否在精灵范围内
        if (rect.containsPoint(locationInNode)) {
            

            for (auto sprite : this->getCanTouchSprite()) 
            {
                if (target == sprite) 
                {
                    // 触摸点在精灵内部
                    target->setOpacity(180); // 半透明效果
                    return true; // 表示处理这个触摸事件
                }
            }
            return false;
        }
        return false; // 不在精灵范围内，不处理
    };

    // 触摸移动事件
    listener->onTouchMoved = [](Touch* touch, Event* event) {};

    // 触摸结束事件
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        if (_gameController.acceptCard(target->getTag()))
        {
            //接受
            this->addTrcyCount();
            target->setLocalZOrder(this->getTrcyCount());
            target->runAction(CCMoveTo::create(0.5, ccp(this->getTrcy().x, this->getTrcy().y)));
        }
        target->setOpacity(255); // 恢复不透明
        if (_gameController.isWin())
        {
            auto labelWin = Label::createWithTTF("YOU WIN", "fonts/Marker Felt.ttf", 36);
            labelWin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            labelWin->setPosition((Director::getInstance()->getVisibleSize() / 2));
        }
    };

    // 触摸取消事件
    listener->onTouchCancelled = [](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255); // 恢复不透明
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
}

void GameTestScene::undoView(int undoTag,Vec2 pos)
{
    if (undoTag == -1)
    {
        return;
    }
    Sprite* undoCard;

    for (auto card : _allCard)
    {
        if (card->getTag() == undoTag)
        {
            undoCard = card;
            break;
        }
    }
    
    this->subTrcyCount();
    undoCard->setLocalZOrder(0);
    undoCard->runAction(CCMoveTo::create(0.5, ccp(pos.x, pos.y + 400)));
}

std::list<cocos2d::Sprite*> GameTestScene::getCanTouchSprite()
{
    return _canTouchSprite;
}

cocos2d::Vec2 GameTestScene::getTrcy()
{
    return _trcy;
}

int GameTestScene::getTrcyCount()
{
    return _trcyCount;
}

void GameTestScene::addTrcyCount()
{
    _trcyCount++;
}

void GameTestScene::subTrcyCount()
{
    _trcyCount--;
}


