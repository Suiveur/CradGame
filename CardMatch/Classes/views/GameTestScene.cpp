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

    // ���ؿ�Ƭ
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
    _trcyCount = 0;// һ�ŵ���

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

    Sprite* suit = loadSuit(card.getSuit());            // ���ػ�ɫ
    suit->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    suit->setPosition(cardSpr->getContentSize().width - 20, cardSpr->getContentSize().height - 20);
    cardSpr->addChild(suit);

    std::string color = getCardColor(card.getSuit());   // ��ɫ
    std::string number = getCardNumber(card.getFace()); // ��С

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
        // ���¿ɱ������Ŀ�Ƭ
        std::vector<Sprite*> removeV;
        for (auto s : _canTouchSprite)
        {
            float dx = fabs(s->getPosition().x - cardSpr->getPosition().x);
            float dy = fabs(s->getPosition().y - cardSpr->getPosition().y);
            // �ڸ�
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
    this->addChild(backgroundUp, -1);// zOrder��Ϊ-1ȷ���ڵײ�

    // ���ñ����ߴ�Ϊ������Ϸ����
    backgroundDn->setContentSize(Size(this->getContentSize().width, this->getContentSize().height - 1400));
    backgroundDn->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    backgroundDn->setPosition(cocos2d::Vec2::ZERO);
    // ��ӵ���Ϸ��ͼ����ײ�
    this->addChild(backgroundDn, -1); 
}

void GameTestScene::setupSpriteTouch(cocos2d::Sprite* sprite)
{
    auto listener = EventListenerTouchOneByOne::create();
    // ���ô������ɣ���ֹ�¼���͸
    listener->setSwallowTouches(true);

    // ������ʼ�¼�
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // ��ˢ��,����Bug
        this->updateCanTouch();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        // ��ȡ�����ڽڵ�����ϵ�е�λ�úͳߴ�
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

        // ת�������㵽����ı�������ϵ
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

        // ��鴥�����Ƿ��ھ��鷶Χ��
        if (rect.containsPoint(locationInNode)) {
            

            for (auto sprite : this->getCanTouchSprite()) 
            {
                if (target == sprite) 
                {
                    // �������ھ����ڲ�
                    target->setOpacity(180); // ��͸��Ч��
                    return true; // ��ʾ������������¼�
                }
            }
            return false;
        }
        return false; // ���ھ��鷶Χ�ڣ�������
    };

    // �����ƶ��¼�
    listener->onTouchMoved = [](Touch* touch, Event* event) {};

    // ���������¼�
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        if (_gameController.acceptCard(target->getTag()))
        {
            //����
            this->addTrcyCount();
            target->setLocalZOrder(this->getTrcyCount());
            target->runAction(CCMoveTo::create(0.5, ccp(this->getTrcy().x, this->getTrcy().y)));
        }
        target->setOpacity(255); // �ָ���͸��
        if (_gameController.isWin())
        {
            auto labelWin = Label::createWithTTF("YOU WIN", "fonts/Marker Felt.ttf", 36);
            labelWin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            labelWin->setPosition((Director::getInstance()->getVisibleSize() / 2));
        }
    };

    // ����ȡ���¼�
    listener->onTouchCancelled = [](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255); // �ָ���͸��
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


