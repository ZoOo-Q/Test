#include "GameRule.h"
#include "models/Card.h"  
// 判断两张卡牌是否可以匹配
bool GameRule::canMatch(const Card* card1, const Card* card2) 
{
    if (!card1 || !card2)
    {
        return false;
    }
    // 获取点数
    int value1 = GlobalConfig::getCardFaceValue(card1->getFace());
    int value2 = GlobalConfig::getCardFaceValue(card2->getFace());
    return abs(value1 - value2) == 1;
}

// 判断是否可以进行回退操作
bool GameRule::canUndo(int backStep)
{
    if (backStep >= 1)
    {

        return true;
    }
    return false;
}

