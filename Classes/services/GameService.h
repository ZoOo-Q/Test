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

    // ��ʼ����Ƭ����
    void initCards(const std::string& jsonPath);

    // ����������
    bool handleUndo(std::vector<CardView*>& cardViews);

    // ��ȡ���п�Ƭ��ͼ����
    std::vector<Card*> getAllCards() const;

private:
    GameService() = default;
    ~GameService() = default;

    static GameService* _instance;
    GameData* _gameData; // �������ݲ�����
};

#endif // GAME_SERVICE_H