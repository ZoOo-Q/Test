#include "MoveUtils.h"
#include "cocos2d.h"
#include "models/Card.h"

using namespace cocos2d;

void MoveUtils::moveCardStraight(CardView* cardView,
    const Vec2& targetPos,
    float duration,
    MoveCompleteCallback callback)
{
    if (!cardView) return;
    // ��¼��ʼλ�ò����¿�������λ��
    Vec2 startPos = cardView->getPosition();
    Card* cardData = cardView->getCardData();
    if (cardData)
    {
        cardData->setPosition(targetPos); // ͬ��ģ��λ��
    }
    // ����ֱ���ƶ�����
    auto moveAction = MoveTo::create(duration, targetPos);
    // ��϶������ƶ�+�ص���
    Sequence* sequence = nullptr;
    if (callback)
    {
        sequence = Sequence::create(
            moveAction,
            CallFunc::create([cardView, callback]() {
                callback(cardView);
                }),
            nullptr
        );
    }
    else
    {
        sequence = Sequence::create(moveAction, nullptr);
    }

    cardView->runAction(sequence);
}