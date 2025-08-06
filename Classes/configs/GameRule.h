#ifndef GAME_RULE_H
#define GAME_RULE_H

#include "cocos2d.h"
#include "CardDefine.h"
#include "GlobalConfig.h"
#include <vector>

class Card;

namespace GameRule 
{
    // �жϿ����Ƿ����ƥ��
    bool canMatch(const Card* card1, const Card* card2);

    // �ж��Ƿ���Խ��г����ز���
    bool canUndo(int backStep);
} 
#endif // GAME_RULE_H
