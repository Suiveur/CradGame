#pragma once
#include "cocos2d.h"
#include "controllers/GameController.h"
#include "ui/CocosGUI.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initBackGround();
    

    CREATE_FUNC(MainScene);
private:
    GameController _gameController;
};