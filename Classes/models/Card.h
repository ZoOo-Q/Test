#ifndef CARD_H
#define CARD_H

#include "cocos2d.h"
#include "./configs/CardDefine.h"


class Card
{
public:
    // ��������
    static Card* create(CardSuitType suit, CardFaceType face);
    
    ~Card();

    // ��ȡ��������
    CardSuitType getSuit() const { return _suit; }//��ɫ
    CardFaceType getFace() const { return _face; }//����
    cocos2d::Vec2 getPosition() const { return _position; }//λ��
    bool isSeeable() const { return _isSeeable; }//�Ƿ�ɼ�

    // ���ÿ�������
    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }
    void setisSeeable(bool seeable) { _isSeeable = seeable; }

private:
    Card(CardSuitType suit, CardFaceType face);

    bool init();

    CardSuitType _suit;           // ��ɫ
    CardFaceType _face;           // ����
    cocos2d::Vec2 _position;      // λ��
    bool _isSeeable;              // �Ƿ�ɼ�
};

#endif // CARD_H