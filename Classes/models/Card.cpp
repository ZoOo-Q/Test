#include "Card.h"

Card::Card(CardSuitType suit, CardFaceType face)
    : _suit(suit)
    , _face(face)
    , _position(cocos2d::Vec2::ZERO)  // ԭ��
    , _isSeeable(true)                // Ĭ���ǿɼ�
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
        return card;  // ��ʼ���ɹ�
    }
    delete card;
    return nullptr;
}

bool Card::init()
{
    return true;
}