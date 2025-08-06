// GameService.cpp
#include "GameService.h"
#include "configs/GlobalConfig.h"
#include <iostream>
GameService* GameService::_instance = nullptr;

GameService* GameService::getInstance() {
    if (!_instance) {
        _instance = new GameService();
        _instance->_gameData = GameData::getInstance();
    }
    return _instance;
}

void GameService::initCards(const std::string& jsonPath) {
    _gameData->initCards(jsonPath);
}

std::vector<Card*> GameService::getAllCards() const {
    return _gameData->getAllCards();
}