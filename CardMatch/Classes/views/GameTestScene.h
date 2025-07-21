#pragma once
#include "cocos2d.h"
#include "controllers/GameController.h"

class GameTestScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initUndo();

    void loadCard(CardModel& card);

    void updateCanTouch();

    cocos2d::Sprite* loadSuit(CardSuitType cardSuit);

    std::string getCardColor(CardSuitType suit);

    std::string getCardNumber(CardFaceType face);

    void initBackGround();

    void setupSpriteTouch(cocos2d::Sprite* sprite);

    CREATE_FUNC(GameTestScene);

    GameController _gameController;
    void undoView(int undoTag,cocos2d::Vec2 pos);
    std::list<cocos2d::Sprite*> getCanTouchSprite();
    cocos2d::Vec2 getTrcy();
    int getTrcyCount();
    void addTrcyCount();
    void subTrcyCount();
    
private:
    int tag;
    std::list<cocos2d::Sprite*> _canTouchSprite; //可以被触摸的精灵
    std::list<cocos2d::Sprite*> _allCard; //可以被触摸的精灵
    cocos2d::Vec2 _trcy;
    int _trcyCount;                     // 底牌数目
};