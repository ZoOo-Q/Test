#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include "cocos2d.h"
#include "CardDefine.h" 

namespace GlobalConfig
{
    //��Ʒֱ��ʣ�1080*2080�����ڴ�С 1080*2080
    const cocos2d::Size kScreenSize = cocos2d::Size(1080, 2080);

    //���ƻ�������
    const cocos2d::Size kCardSize = cocos2d::Size(160, 240); // ���ƵĿ�͸�
    const float kCardMoveTime = 0.4f; // �����ƶ���ʱ��

    //���Ƶ�������
    inline int getCardFaceValue(CardFaceType cardFaceType)
    {
        switch (cardFaceType)
        {
        case CFT_ACE: return 1;
        case CFT_TWO: return 2;
        case CFT_THREE: return 3;
        case CFT_FOUR: return 4;
        case CFT_FIVE: return 5;
        case CFT_SIX: return 6;
        case CFT_SEVEN: return 7;
        case CFT_EIGHT: return 8;
        case CFT_NINE: return 9;
        case CFT_TEN: return 10;
        case CFT_JACK: return 11;
        case CFT_QUEEN: return 12;
        case CFT_KING: return 13;
        default: return 0;
        }
    }

    // �������Ϳ��ѳߴ�
    //1.������
    const cocos2d::Size kMainSize = cocos2d::Size(1080 , 1500); //��͸�
    const cocos2d::Vec2 kMainPos = cocos2d::Vec2  //�޸ı���������׼ȷ��ӳ��λ�ö��ǳߴ�
    (
        kScreenSize.width / 2,
        kScreenSize.height - kMainSize.height / 2  //��������
    );

    //2.������
    const cocos2d::Size kCardAreaSize = cocos2d::Size(1080 , 1500 ); //��͸ߣ��޸����Ʊ����뿨�ƴ�С��ͻ
    const cocos2d::Vec2 kCardAreaPos = cocos2d::Vec2  //�޸ı���������׼ȷ��ӳ��λ�ö��ǳߴ�
    (
        kMainPos.x,
        kMainPos.y  //��������һ��
    );

    //3.������
    const cocos2d::Size kStackSize = cocos2d::Size(1080, 580); //��͸�
    const cocos2d::Vec2 kStackPos = cocos2d::Vec2(  //�޸ı���������׼ȷ��ӳ��λ�ö��ǳߴ�
        kScreenSize.width / 2,
        kStackSize.height / 2  //�ײ�����
    );

    //4.����������
    const cocos2d::Vec2 STACK_TOP_POS = cocos2d::Vec2
    (
        kStackPos.x,
        kStackPos.y + kStackSize.height / 2 - kCardSize.height / 2
    );

    //5.������
    const cocos2d::Vec2 kBackPos = cocos2d::Vec2
    (
        kStackPos.x + kStackSize.width / 6 -150,
        kStackPos.y + kStackSize.height / 5-200 
    );

    //����·��
    const std::string kNumberPath = "number/";
    const std::string kSuitPath = "suits/";  
    inline std::string getNumber(CardFaceType cardFaceType)
    {
        switch (cardFaceType) {
        case CFT_ACE: return "A";
        case CFT_TWO: return "2";
        case CFT_THREE: return "3";
        case CFT_FOUR: return "4";
        case CFT_FIVE: return "5";
        case CFT_SIX: return "6";
        case CFT_SEVEN: return "7";
        case CFT_EIGHT: return "8";
        case CFT_NINE: return "9";
        case CFT_TEN: return "10";
        case CFT_JACK: return "J";
        case CFT_QUEEN: return "Q";
        case CFT_KING: return "K";
        default: return "";
        }
    }
    inline std::string getSuit(CardSuitType cardSuitType)
    {
        switch (cardSuitType) {
        case CST_CLUBS: return "club.png";      // ÷��
        case CST_DIAMONDS: return "diamond.png";// ����
        case CST_HEARTS: return "heart.png";    // ����
        case CST_SPADES: return "spade.png";    // ����
        default: return "";
        }
    }
    //ƴ��
    inline std::string getNumberPath(CardFaceType face, bool isBig = true, bool isBlack = true)
    {
        std::string sizePrefix = isBig ? "big_" : "small_";
        std::string colorPrefix = isBlack ? "black_" : "red_";
        return kNumberPath + sizePrefix + colorPrefix + getNumber(face) + ".png";
    }
    inline std::string getSuitPath(CardSuitType suit)
    {
        return kSuitPath + getSuit(suit); 
    }

    //uiͼƬ·��
    const std::string kCardBack = "res/card_general.png";   // ���˰�ť
    const std::string kBackButton = "background/backbutton.png";   // ���˰�ť
    const std::string kBackGround = "background/background.png"; // ��Ϸ����ͼ

    //�����ļ�·��
    const std::string kInitJson = "InitCards.json";    // ��ʼ��������

    //ͼ��ĸ��ǹ�ϵ
    const int kBack = 0;    // ������
    const int kCard = 10;        // ���Ʋ�
    const int kButton = 20;           // ���˲�
}

#endif