#pragma once
#include "CardModel.h"
#include <vector>
#include <stack>
class GameModel {
public:
    GameModel();
    GameModel(std::vector<CardModel> &pfc, std::vector<CardModel> &sc, CardModel &tc, std::stack<CardModel>&dc);
    
    std::vector<CardModel> playfieldCards; // 主牌区
    std::vector<CardModel> stackCards;     // 备用牌堆
    CardModel trayCard;                    // 底牌（当前顶部牌）
    std::stack<CardModel> doneCards;       // 记录已经操作的动作
    int noMatchCount;
    // 游戏状态数据
};
