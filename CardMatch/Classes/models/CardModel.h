#pragma once
#include "cocos2d.h"
#include "CardEnum.h"
class CardModel {
public:
    
    CardModel(int id,CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position);
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position);
    CardModel();
    // 序列化方法
    std::string serialize() const;
    // 反序列化方法
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
    CardFaceType _face;     // 牌面值
    CardSuitType _suit;     // 花色
    cocos2d::Vec2 _position; // 位置坐标
    bool _canTouch;
};