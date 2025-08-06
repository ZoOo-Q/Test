#ifndef CARD_H
#define CARD_H

#include "cocos2d.h"
#include "./configs/CardDefine.h"


class Card
{
public:
    // 创建卡牌
    static Card* create(CardSuitType suit, CardFaceType face);
    
    ~Card();

    // 获取卡牌属性
    CardSuitType getSuit() const { return _suit; }//花色
    CardFaceType getFace() const { return _face; }//点数
    cocos2d::Vec2 getPosition() const { return _position; }//位置
    bool isSeeable() const { return _isSeeable; }//是否可见

    // 设置卡牌属性
    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }
    void setisSeeable(bool seeable) { _isSeeable = seeable; }

private:
    Card(CardSuitType suit, CardFaceType face);

    bool init();

    CardSuitType _suit;           // 花色
    CardFaceType _face;           // 点数
    cocos2d::Vec2 _position;      // 位置
    bool _isSeeable;              // 是否可见
};

#endif // CARD_H