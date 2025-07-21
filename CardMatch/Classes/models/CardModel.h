#pragma once
#include "cocos2d.h"
#include "CardEnum.h"
class CardModel {
public:
    
    CardModel(int id,CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position);
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position);
    CardModel();
    // ���л�����
    std::string serialize() const;
    // �����л�����
    static CardModel deserialize(const std::string& data);

    // Getters
    int getId() const;
    CardFaceType getFace() const;
    CardSuitType getSuit() const;
    cocos2d::Vec2 getPosition() const;
    bool getCanTOuch() const;

    // Setters    
    void setId(int id);
    void setFace(CardFaceType face);
    void setSuit(CardSuitType suit);
    void setPosition(const cocos2d::Vec2& position);
    void setCanTouch(bool canTouch);

private:
    int _id;
    CardFaceType _face;     // ����ֵ
    CardSuitType _suit;     // ��ɫ
    cocos2d::Vec2 _position; // λ������
    bool _canTouch;
};