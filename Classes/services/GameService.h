// GameService.h
#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "models/GameData.h"
#include "views/CardView.h"
#include "configs/GameRule.h"
#include <vector>

class GameService {
public:
    static GameService* getInstance();

    // 初始化卡片数据
    void initCards(const std::string& jsonPath);

    // 处理撤销操作
    bool handleUndo(std::vector<CardView*>& cardViews);

    // 获取所有卡片视图数据
    std::vector<Card*> getAllCards() const;

private:
    GameService() = default;
    ~GameService() = default;

    static GameService* _instance;
    GameData* _gameData; // 持有数据层引用
};

#endif // GAME_SERVICE_H