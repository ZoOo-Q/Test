#ifndef GAME_RULE_H
#define GAME_RULE_H

#include "cocos2d.h"
#include "CardDefine.h"
#include "GlobalConfig.h"
#include <vector>

class Card;

namespace GameRule 
{
    // 判断卡牌是否可以匹配
    bool canMatch(const Card* card1, const Card* card2);

    // 判断是否可以进行撤销回操作
    bool canUndo(int backStep);
} 
#endif // GAME_RULE_H
