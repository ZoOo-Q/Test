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
    // 记录起始位置并更新卡牌数据位置
    Vec2 startPos = cardView->getPosition();
    Card* cardData = cardView->getCardData();
    if (cardData)
    {
        cardData->setPosition(targetPos); // 同步模型位置
    }
    // 创建直线移动动作
    auto moveAction = MoveTo::create(duration, targetPos);
    // 组合动作（移动+回调）
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