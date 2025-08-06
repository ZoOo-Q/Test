#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "cocos2d.h"
#include "CardView.h"
#include "./models/GameData.h"
#include "UiBack.h"
#include <vector>

class GameView : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    // 初始化游戏元素
    void initGameElements();
    // 初始化卡牌视图
    void initCardViews();
    // 初始化返回按钮
    void initBackButton();
    // 处理卡牌点击
    void onCardClicked(CardView* cardView);
    // 处理撤销操作
    void handleUndo();

    std::vector<CardView*> GetCardView();

    // 实现CREATE_FUNC宏
    CREATE_FUNC(GameView);

    bool isPointInHandCardArea(const cocos2d::Vec2& pos);

private:
    std::vector<CardView*> _cardViews; // 卡牌视图
    CardView* _selectedCard = nullptr; // 当前选中的卡牌
};

#endif // GAME_VIEW_H