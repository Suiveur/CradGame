#include "GameModel.h"

GameModel::GameModel()
{
	noMatchCount = 0;
}

GameModel::GameModel(std::vector<CardModel> &pfc, std::vector<CardModel> &sc, CardModel &tc, std::stack<CardModel> &dc)
	:playfieldCards(pfc)
	,stackCards(sc)
	,trayCard(tc)
	,doneCards(dc)
{
	noMatchCount = 0;
}
