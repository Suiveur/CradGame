// configs/models/LevelConfig.h
#pragma once
#include "cocos2d.h"
#include "models/CardEnum.h"// 包含 CardFaceType 和 CardSuitType 枚举

struct CardConfig {
    CardFaceType face;
    CardSuitType suit;
    cocos2d::Vec2 position;
};

struct LevelConfig {
    std::vector<CardConfig> playfield; // 主牌区
    std::vector<CardConfig> stack;     // 备用牌堆
};
