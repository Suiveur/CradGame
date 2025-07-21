// services/GameModelGenerator.cpp
#include "GameModelGenerator.h"
#include <ctime>
#include <cstdlib>

GameModel GameModelGenerator::generateFromConfig(const LevelConfig& config) {
    GameModel gameModel;
    int id = 0;
    // 处理主牌区卡牌
    for (const auto& cardConfig : config.playfield) {
        CardModel card(
            id,
            cardConfig.face,
            cardConfig.suit,
            cardConfig.position
        );
        id++;
        gameModel.playfieldCards.push_back(card);
    }

    // 处理备用牌堆卡牌
    for (const auto& cardConfig : config.stack) {
        CardModel card(
            id,
            cardConfig.face,
            cardConfig.suit,
            cardConfig.position
        );
        id++;
        gameModel.stackCards.push_back(card);
    }

    // 设置初始底牌
    if (!gameModel.stackCards.empty()) {
        CardModel tc = gameModel.stackCards.back();
        gameModel.trayCard = tc;
    }
    return gameModel;
}