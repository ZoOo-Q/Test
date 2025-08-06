#include "GameRule.h"
#include "models/Card.h"  
// �ж����ſ����Ƿ����ƥ��
bool GameRule::canMatch(const Card* card1, const Card* card2) 
{
    if (!card1 || !card2)
    {
        return false;
    }
    // ��ȡ����
    int value1 = GlobalConfig::getCardFaceValue(card1->getFace());
    int value2 = GlobalConfig::getCardFaceValue(card2->getFace());
    return abs(value1 - value2) == 1;
}

// �ж��Ƿ���Խ��л��˲���
bool GameRule::canUndo(int backStep)
{
    if (backStep >= 1)
    {

        return true;
    }
    return false;
}

