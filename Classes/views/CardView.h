#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include "cocos2d.h"
#include <functional>

class Card;

class CardView : public cocos2d::Sprite
{
public:
    
   
    //创建的CardView实例
    //参数:卡牌实例
    //返回值:卡牌图像实例
    static CardView* create(Card* cardData);

    //构造函数
    //参数：cardData 卡牌数据指针
    explicit CardView(Card* cardData);

    ~CardView() override;

    //设置卡牌可见性
    //参数：isVisible 是否可见
    void setCardVisible(bool isVisible);

    
    //更新卡牌位置（带动画）
    //参数：targetPos 目标位置  duration 动画时间
    void updatePosition(const cocos2d::Vec2& targetPos, float duration);

    
    //回调函数
    //参数：callback 回调函数
    void setClickCallback(const std::function<void(CardView*)>& callback);

   
    //获取关联的卡牌数据
    //返回值：卡牌数据指针
    Card* getCardData() const { return _cardData; }

    
    // 初始化函数
    bool init() override;

    //加载卡牌图片
    void loadCardPicture();

    //点击开始事件处理
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    //点击结束事件处理
    void touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);

  

private:
    Card* _cardData;                 // 卡牌数据
    cocos2d::Sprite* _faceSprite;    // 卡牌正面
    std::function<void(CardView*)> _clickCallback;  // 点击回调
};

#endif // CARD_VIEW_H
