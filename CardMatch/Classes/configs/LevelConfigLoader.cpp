
#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include <cstdio>
#include <fstream>
using namespace rapidjson;

LevelConfig LevelConfigLoader::loadFromFile(const std::string& filename) {
    LevelConfig config;
    
    // ��ȡ�ļ�·��
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename);

    // ���ļ�
    FILE* fp = fopen(fullPath.c_str(), "rb");
    if (!fp) {
        cocos2d::log("[LevelConfigLoader] Error opening file: %s", fullPath.c_str());
        return config;
    }

    // ��ȡ�ļ�����
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // ����JSON
    Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if (doc.HasParseError()) {
        cocos2d::log("[LevelConfigLoader] JSON parse error: %s (offset: %u)",
            GetParseError_En(doc.GetParseError()), doc.GetErrorOffset());
        return config;
    }

    // ����������
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const Value& playfieldArray = doc["Playfield"];
        for (SizeType i = 0; i < playfieldArray.Size(); i++) {
            config.playfield.push_back(parseCardConfig(playfieldArray[i]));
        }
    }

    // ���������ƶ�
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
    // ӳ��ö��ֵ��ȷ������Ч��Χ��
    if (value >= static_cast<int>(CardFaceType::CFT_ACE) &&
        value <= static_cast<int>(CardFaceType::CFT_KING)) {
        return static_cast<CardFaceType>(value);
    }
    return CardFaceType::CFT_NONE;
}

CardSuitType LevelConfigLoader::parseCardSuit(int value) {
    // ӳ��ö��ֵ��ȷ������Ч��Χ��
    if (value >= static_cast<int>(CardSuitType::CST_CLUBS) &&
        value <= static_cast<int>(CardSuitType::CST_SPADES)) {
        return static_cast<CardSuitType>(value);
    }
    return CardSuitType::CST_NONE;
}