#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "cocos2d.h"
#include "./models/GameData.h"
#include "./views/GameView.h"
#include "./views/CardView.h"
#include <functional>

class GameController
{
public:
    static GameController* getInstance();

    //初始化控制器
    //参数:游戏实例
    //返回值:
    void init(GameView* view);

    //处理手牌区翻牌
    //参数:卡牌图形实例
    void onHandCardClick(CardView* cardView);

    //增加操作记录
    //参数:一次操作记录
    void pushOperation(const OperationRecord& record);

    //匹配卡牌
    //参数:匹配卡牌实例对象
    void onDesktopCardClick(CardView* cardView);

    GameView* getGameView()
    {
        return _gameView;
    }
private:
    GameController();
    ~GameController();

    static GameController* _instance;//游戏控制实例
    GameView* _gameView;          // gameview
    CardView* _selectedCardView; // 当前选中的卡片
};

#endif // GAME_CONTROLLER_H