#include "cocos2d.h"
#include "CardView.h"
#include "./models/Card.h"
#include "./configs/GlobalConfig.h"
USING_NS_CC;

CardView* CardView::create(Card* cardData)
{
    CardView* view = new (std::nothrow) CardView(cardData);
    if (view && view->init())
    {
        view->autorelease();
        return view;
    }
    delete view;
    return nullptr;
}

CardView::CardView(Card* cardData)
    : _cardData(cardData)
    , _faceSprite(nullptr)
    , _clickCallback(nullptr)
{
}

CardView::~CardView()
{
    _clickCallback = nullptr;
    _cardData = nullptr;
}

bool CardView::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    // 初始化点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    //回调绑定
    listener->onTouchBegan = CC_CALLBACK_2(CardView::touchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(CardView::touchEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // 加载图片
    loadCardPicture();
    return true;
}

void CardView::loadCardPicture()
{
    if (_cardData)
    {
        CardFaceType faceType = _cardData->getFace();//点数
        CardSuitType suitType = _cardData->getSuit();//花色
        auto face = Sprite::create();
        face->setContentSize(this->getContentSize());
        this->addChild(face);
        _faceSprite = face;
        auto cardBack = Sprite::create(GlobalConfig::kCardBack);//背景图
        if (cardBack)
        {
            cardBack->setPosition(face->getContentSize() / 2);
            face->addChild(cardBack);
        }
        std::string smallNumberPath = GlobalConfig::getNumberPath(faceType, false);//卡牌左上角小数字
        auto smallNumberSprite = Sprite::create(smallNumberPath);
        if (smallNumberSprite)
        {
            smallNumberSprite->setPosition(Vec2(30, face->getContentSize().height+90));
            face->addChild(smallNumberSprite);
        }
        std::string suitPath = GlobalConfig::getSuitPath(suitType);//卡牌右上角花色
        auto suitSprite = Sprite::create(suitPath);
        if (suitSprite)
        {
            suitSprite->setPosition(Vec2(face->getContentSize().width - 30, face->getContentSize().height +90));
            face->addChild(suitSprite);
        }
        std::string centerNumberPath = GlobalConfig::getNumberPath(faceType);//中央大数字
        auto centerNumber = Sprite::create(centerNumberPath);
        if (centerNumber)
        {
            centerNumber->setPosition(face->getContentSize() / 2);
            face->addChild(centerNumber);
        }
        _faceSprite->setVisible(true);//正面可见
    }
}


void CardView::setCardVisible(bool isVisible)
{
    this->setVisible(isVisible);
}

void CardView::updatePosition(const Vec2& targetPos, float duration)
{
    //创建移动动画
    auto moveAction = MoveTo::create(duration, targetPos);
    this->runAction(moveAction);
}

void CardView::setClickCallback(const std::function<void(CardView*)>& callback)
{
    _clickCallback = callback;
}

bool CardView::touchBegan(Touch* touch, Event* event)
{
    //检查点击是否在卡片范围内
    Vec2 touchLocation = this->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
    if (rect.containsPoint(touchLocation))
    {
        return true;
    }
    return false;
}

void CardView::touchEnd(Touch* touch, Event* event)
{
    
    // 检查点击是否在卡牌范围内
    Vec2 touchLocation = this->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
    if (rect.containsPoint(touchLocation) && _clickCallback)
    {
        //调用回调
        _clickCallback(this);
    }
}
