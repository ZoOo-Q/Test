#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include "cocos2d.h"
#include "CardDefine.h" 

namespace GlobalConfig
{
    //设计分辨率：1080*2080；窗口大小 1080*2080
    const cocos2d::Size kScreenSize = cocos2d::Size(1080, 2080);

    //卡牌基础属性
    const cocos2d::Size kCardSize = cocos2d::Size(160, 240); // 卡牌的宽和高
    const float kCardMoveTime = 0.4f; // 卡牌移动的时长

    //卡牌点数返回
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

    // 主牌区和卡堆尺寸
    //1.主牌区
    const cocos2d::Size kMainSize = cocos2d::Size(1080 , 1500); //宽和高
    const cocos2d::Vec2 kMainPos = cocos2d::Vec2  //修改变量名，更准确反映是位置而非尺寸
    (
        kScreenSize.width / 2,
        kScreenSize.height - kMainSize.height / 2  //顶部居中
    );

    //2.卡牌区
    const cocos2d::Size kCardAreaSize = cocos2d::Size(1080 , 1500 ); //宽和高，修改名称避免与卡牌大小冲突
    const cocos2d::Vec2 kCardAreaPos = cocos2d::Vec2  //修改变量名，更准确反映是位置而非尺寸
    (
        kMainPos.x,
        kMainPos.y  //与主牌区一致
    );

    //3.手牌区
    const cocos2d::Size kStackSize = cocos2d::Size(1080, 580); //宽和高
    const cocos2d::Vec2 kStackPos = cocos2d::Vec2(  //修改变量名，更准确反映是位置而非尺寸
        kScreenSize.width / 2,
        kStackSize.height / 2  //底部居中
    );

    //4.单张手牌区
    const cocos2d::Vec2 STACK_TOP_POS = cocos2d::Vec2
    (
        kStackPos.x,
        kStackPos.y + kStackSize.height / 2 - kCardSize.height / 2
    );

    //5.回退区
    const cocos2d::Vec2 kBackPos = cocos2d::Vec2
    (
        kStackPos.x + kStackSize.width / 6 -150,
        kStackPos.y + kStackSize.height / 5-200 
    );

    //卡牌路径
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
        case CST_CLUBS: return "club.png";      // 梅花
        case CST_DIAMONDS: return "diamond.png";// 方块
        case CST_HEARTS: return "heart.png";    // 红桃
        case CST_SPADES: return "spade.png";    // 黑桃
        default: return "";
        }
    }
    //拼接
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

    //ui图片路径
    const std::string kCardBack = "res/card_general.png";   // 回退按钮
    const std::string kBackButton = "background/backbutton.png";   // 回退按钮
    const std::string kBackGround = "background/background.png"; // 游戏背景图

    //配置文件路径
    const std::string kInitJson = "InitCards.json";    // 初始卡牌配置

    //图层的覆盖关系
    const int kBack = 0;    // 背景层
    const int kCard = 10;        // 卡牌层
    const int kButton = 20;           // 回退层
}

#endif