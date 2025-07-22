#pragma once
#pragma once
#include "configs/LevelConfig.h"
#include "models/GameModel.h"

class GameModelGenerator {
public:
    static GameModel generateFromConfig(const LevelConfig& config);
};