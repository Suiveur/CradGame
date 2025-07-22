#pragma once
#include "configs/LevelConfigLoader.h"
#include "models/GameModel.h"
#include <memory>
class GameController
{
public:
	void startGame(int levelId);

	GameModel getGameModel();

	bool acceptCard(int tag);

	int undoOnce(cocos2d::Vec2& pos);

	bool isWin();
private:
	GameModel _gameModel;
};

