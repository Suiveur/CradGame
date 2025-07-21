// CardModel.cpp
#include "CardModel.h"
#include <sstream>

CardModel::CardModel(int id,CardFaceType face, CardSuitType suit,
    const cocos2d::Vec2& position)
     :_id(id),_face(face), _suit(suit), _position(position), _canTouch(true) {}

CardModel::CardModel(CardFaceType face, CardSuitType suit,
    const cocos2d::Vec2& position)
    : _face(face), _suit(suit), _position(position), _canTouch(true) {}

CardModel::CardModel()
{
}

std::string CardModel::serialize() const 
{
    std::ostringstream oss;
    oss << static_cast<int>(_face) << ","
        << static_cast<int>(_suit) << ","
        << _position.x << "," << _position.y;
    return oss.str();
}

CardModel CardModel::deserialize(const std::string& data) 
{
    std::istringstream iss(data);
    char delimiter;         // ·Ö½ç·û
    int face, suit;
    float x, y;
    iss >> face >> delimiter
        >> suit >> delimiter
        >> x >> delimiter >> y;

    return CardModel(
        static_cast<CardFaceType>(face),
        static_cast<CardSuitType>(suit),
        cocos2d::Vec2(x, y)
    );
}


int CardModel::getId() const
{
    return _id;
}

CardFaceType CardModel::getFace() const
{
    return _face;
}

CardSuitType CardModel::getSuit() const
{
    return _suit;
}

cocos2d::Vec2 CardModel::getPosition() const
{
    return _position;
}

bool CardModel::getCanTOuch() const
{
    return _canTouch;
}


void CardModel::setPosition(const cocos2d::Vec2& position)
{
    _position = position; 
}

void CardModel::setCanTouch(bool canTouch)
{
    _canTouch = canTouch;
}


void CardModel::setId(int id)
{
    _id = id;
}

void CardModel::setFace(CardFaceType face)
{
    _face = face;
}

void CardModel::setSuit(CardSuitType suit)
{
    _suit = suit;
}
