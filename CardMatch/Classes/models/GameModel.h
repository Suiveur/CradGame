#pragma once
#include "CardModel.h"
#include <vector>
#include <stack>
class GameModel {
public:
    GameModel();
    GameModel(std::vector<CardModel> &pfc, std::vector<CardModel> &sc, CardModel &tc, std::stack<CardModel>&dc);
    
    std::vector<CardModel> playfieldCards; // ������
    std::vector<CardModel> stackCards;     // �����ƶ�
    CardModel trayCard;                    // ���ƣ���ǰ�����ƣ�
    std::stack<CardModel> doneCards;       // ��¼�Ѿ������Ķ���
    int noMatchCount;
    // ��Ϸ״̬����
};
