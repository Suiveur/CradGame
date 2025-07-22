
#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include <cstdio>
#include <fstream>
using namespace rapidjson;

LevelConfig LevelConfigLoader::loadFromFile(const std::string& filename) {
    LevelConfig config;
    
    // 获取文件路径
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename);

    // 打开文件
    FILE* fp = fopen(fullPath.c_str(), "rb");
    if (!fp) {
        cocos2d::log("[LevelConfigLoader] Error opening file: %s", fullPath.c_str());
        return config;
    }

    // 读取文件内容
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // 解析JSON
    Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if (doc.HasParseError()) {
        cocos2d::log("[LevelConfigLoader] JSON parse error: %s (offset: %u)",
            GetParseError_En(doc.GetParseError()), doc.GetErrorOffset());
        return config;
    }

    // 解析主牌区
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const Value& playfieldArray = doc["Playfield"];
        for (SizeType i = 0; i < playfieldArray.Size(); i++) {
            config.playfield.push_back(parseCardConfig(playfieldArray[i]));
        }
    }

    // 解析备用牌堆
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const Value& stackArray = doc["Stack"];
        for (SizeType i = 0; i < stackArray.Size(); i++) {
            config.stack.push_back(parseCardConfig(stackArray[i]));
        }
    }

    cocos2d::log("[LevelConfigLoader] Loaded config: %zu playfield cards, %zu stack cards",
        config.playfield.size(), config.stack.size());

    return config;
}

CardConfig LevelConfigLoader::parseCardConfig(const rapidjson::Value& cardObj) {
    CardConfig config;

    if (cardObj.HasMember("CardFace") && cardObj["CardFace"].IsInt()) {
        config.face = parseCardFace(cardObj["CardFace"].GetInt());
    }
    else {
        config.face = CardFaceType::CFT_NONE;
    }

    if (cardObj.HasMember("CardSuit") && cardObj["CardSuit"].IsInt()) {
        config.suit = parseCardSuit(cardObj["CardSuit"].GetInt());
    }
    else {
        config.suit = CardSuitType::CST_NONE;
    }

    if (cardObj.HasMember("Position") && cardObj["Position"].IsObject()) {
        config.position = parsePosition(cardObj["Position"]);
    }
    else {
        config.position = cocos2d::Vec2::ZERO;
    }

    return config;
}

cocos2d::Vec2 LevelConfigLoader::parsePosition(const rapidjson::Value& posObj) {
    float x = 0, y = 0;

    if (posObj.HasMember("x") && posObj["x"].IsNumber()) {
        x = posObj["x"].GetFloat();
    }

    if (posObj.HasMember("y") && posObj["y"].IsNumber()) {
        y = posObj["y"].GetFloat();
    }

    return cocos2d::Vec2(x, y);
}

CardFaceType LevelConfigLoader::parseCardFace(int value) {
    // 映射枚举值，确保在有效范围内
    if (value >= static_cast<int>(CardFaceType::CFT_ACE) &&
        value <= static_cast<int>(CardFaceType::CFT_KING)) {
        return static_cast<CardFaceType>(value);
    }
    return CardFaceType::CFT_NONE;
}

CardSuitType LevelConfigLoader::parseCardSuit(int value) {
    // 映射枚举值，确保在有效范围内
    if (value >= static_cast<int>(CardSuitType::CST_CLUBS) &&
        value <= static_cast<int>(CardSuitType::CST_SPADES)) {
        return static_cast<CardSuitType>(value);
    }
    return CardSuitType::CST_NONE;
}