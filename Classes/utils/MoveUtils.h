#ifndef MOVE_UTILS_H
#define MOVE_UTILS_H

#include "cocos2d.h"
#include "views/CardView.h"
#include "configs/GlobalConfig.h"

class MoveUtils
{
public:
    // 移动完成回调
    using MoveCompleteCallback = std::function<void(CardView*)>;

    static void moveCardStraight(CardView* cardView,
        const cocos2d::Vec2& targetPos,
        float duration = GlobalConfig::kCardMoveTime,
        MoveCompleteCallback callback = nullptr);

private:
    MoveUtils() = default;
};

#endif // MOVE_UTILS_H