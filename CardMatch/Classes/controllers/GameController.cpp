
#include "GameController.h"
#include "services/GameModelGenerator.h"
#include <memory>

void GameController::startGame(int levelId) {
    // 1. 构建配置文件路径
    std::string configPath = cocos2d::StringUtils::format("../../Classes/configs/level_%d.json", levelId);

    // 2. 加载关卡配置
    LevelConfig levelConfig = LevelConfigLoader::loadFromFile(configPath);

    // 3. 生成游戏模型
    _gameModel = GameModelGenerator::generateFromConfig(levelConfig);
    
    cocos2d::log("[GameController] Game started with level: %d", levelId);
    CCLOG("%d,%d", _gameModel.trayCard.getFace(), _gameModel.trayCard.getSuit());
}

GameModel GameController::getGameModel()
{
    return _gameModel;
}

bool GameController::acceptCard(int tag)
{
    bool res;
    if (tag >= _gameModel.playfieldCards.size())
    {
        //在备用牌区
        res = true;/*abs(static_cast<int>(_gameModel.stackCards[tag - _gameModel.playfieldCards.size()].getFace()) -
            static_cast<int>(_gameModel.trayCard.getFace())) == 1;*/

        _gameModel.doneCards.push(_gameModel.stackCards[tag - _gameModel.playfieldCards.size()]);
        _gameModel.trayCard = _gameModel.stackCards[tag - _gameModel.playfieldCards.size()];

    }
    else {
        res = abs(static_cast<int>(_gameModel.playfieldCards[tag].getFace()) -
            static_cast<int>(_gameModel.trayCard.getFace())) == 1;
        if (res)
        {
            _gameModel.noMatchCount++;
            _gameModel.doneCards.push(_gameModel.playfieldCards[tag]);
            _gameModel.trayCard = _gameModel.playfieldCards[tag];
        }
    }
    return res;
}

int GameController::undoOnce(cocos2d::Vec2& pos)
{
    if (_gameModel.doneCards.empty())
    {
        _gameModel.trayCard = _gameModel.stackCards.back();
        return -1;
    }
    CardModel cm = _gameModel.doneCards.top();
    _gameModel.doneCards.pop();
    pos = cm.getPosition();
    if (!_gameModel.doneCards.empty())
    {
        _gameModel.trayCard = _gameModel.doneCards.top();
    }
    else
    {
        _gameModel.trayCard = _gameModel.stackCards.back();
    }

    if (cm.getId() < _gameModel.playfieldCards.size())
    {
        _gameModel.noMatchCount--;
    }

    return cm.getId();
}

bool GameController::isWin()
{
    return _gameModel.noMatchCount == _gameModel.playfieldCards.size();
}






