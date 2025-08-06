#include "Card.h"

Card::Card(CardSuitType suit, CardFaceType face)
    : _suit(suit)
    , _face(face)
    , _position(cocos2d::Vec2::ZERO)  // 原点
    , _isSeeable(true)                // 默认是可见
{
}

Card::~Card()
{
}

Card* Card::create(CardSuitType suit, CardFaceType face)
{
    Card* card = new Card(suit, face);
    if (card && card->init())
    {
        return card;  // 初始化成功
    }
    delete card;
    return nullptr;
}

bool Card::init()
{
    return true;
}