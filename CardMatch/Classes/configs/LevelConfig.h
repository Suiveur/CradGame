// configs/models/LevelConfig.h
#pragma once
#include "cocos2d.h"
#include "models/CardEnum.h"// ���� CardFaceType �� CardSuitType ö��

struct CardConfig {
    CardFaceType face;
    CardSuitType suit;
    cocos2d::Vec2 position;
};

struct LevelConfig {
    std::vector<CardConfig> playfield; // ������
    std::vector<CardConfig> stack;     // �����ƶ�
};
