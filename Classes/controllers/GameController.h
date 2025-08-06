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

    //��ʼ��������
    //����:��Ϸʵ��
    //����ֵ:
    void init(GameView* view);

    //��������������
    //����:����ͼ��ʵ��
    void onHandCardClick(CardView* cardView);

    //���Ӳ�����¼
    //����:һ�β�����¼
    void pushOperation(const OperationRecord& record);

    //ƥ�俨��
    //����:ƥ�俨��ʵ������
    void onDesktopCardClick(CardView* cardView);

    GameView* getGameView()
    {
        return _gameView;
    }
private:
    GameController();
    ~GameController();

    static GameController* _instance;//��Ϸ����ʵ��
    GameView* _gameView;          // gameview
    CardView* _selectedCardView; // ��ǰѡ�еĿ�Ƭ
};

#endif // GAME_CONTROLLER_H