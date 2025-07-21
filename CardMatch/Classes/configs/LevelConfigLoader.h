#pragma once
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/filereadstream.h"
#include "json/error/en.h"
#include "configs/LevelConfig.h"


class LevelConfigLoader {
public:
    static LevelConfig loadFromFile(const std::string& filename);

private:
    static CardFaceType parseCardFace(int value);
    static CardSuitType parseCardSuit(int value);
    static cocos2d::Vec2 parsePosition(const rapidjson::Value& posObj);
    static CardConfig parseCardConfig(const rapidjson::Value& cardObj);
};