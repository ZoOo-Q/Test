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

    // ��ʼ����ϷԪ��
    void initGameElements();
    // ��ʼ��������ͼ
    void initCardViews();
    // ��ʼ�����ذ�ť
    void initBackButton();
    // �����Ƶ��
    void onCardClicked(CardView* cardView);
    // ����������
    void handleUndo();

    std::vector<CardView*> GetCardView();

    // ʵ��CREATE_FUNC��
    CREATE_FUNC(GameView);

    bool isPointInHandCardArea(const cocos2d::Vec2& pos);

private:
    std::vector<CardView*> _cardViews; // ������ͼ
    CardView* _selectedCard = nullptr; // ��ǰѡ�еĿ���
};

#endif // GAME_VIEW_H