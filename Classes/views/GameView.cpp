#include "GameView.h"
#include "./configs/GlobalConfig.h"
#include "./configs/GameRule.h"
#include "./services/GameService.h"
#include "./controllers/GameController.h"
using namespace cocos2d;
Scene* GameView::createScene()
{
    return GameView::create();
}

bool GameView::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 初始化游戏控制器
    GameController::getInstance()->init(this);

    // 初始化游戏元素
    initGameElements();

    return true;
}

void GameView::initGameElements()
{
    //设置背景
    auto background = Sprite::create(GlobalConfig::kBackGround);
    if (background)
    {
        background->setPosition(GlobalConfig::kScreenSize / 2);
        background->setContentSize(GlobalConfig::kScreenSize);
        this->addChild(background, GlobalConfig::kBack);
    }
    //初始化卡牌视图
    initCardViews();
    //初始化回退按钮
    initBackButton();
}

void GameView::initCardViews()
{
    auto allCards = GameService::getInstance()->getAllCards();
    for (auto card : allCards)
    {
        CardView* cardView = CardView::create(card);
        if (cardView)
        {
            // 设置卡牌大小和初始位置
            cardView->setContentSize(GlobalConfig::kCardSize);
            cardView->setPosition(card->getPosition());
            // 设置点击回调
            cardView->setClickCallback(std::bind(&GameView::onCardClicked, this, std::placeholders::_1));
            this->addChild(cardView, GlobalConfig::kCard);
            _cardViews.push_back(cardView);
        }
    }
}

void GameView::initBackButton()
{
    UiBack* backLayer = UiBack::create();
    if (backLayer)
    {
        backLayer->setContentSize(Size(50, 50));
        backLayer->setScale(0.5f);
        backLayer->onBackClicked = std::bind(&GameView::handleUndo, this);
        this->addChild(backLayer);
        backLayer->setPosition(GlobalConfig::kBackPos); // 示例位置
    }
}

bool GameView::isPointInHandCardArea(const cocos2d::Vec2& pos)
{
    return pos.y >= GlobalConfig::kStackPos.y - GlobalConfig::kStackSize.height / 2 &&
        pos.y <= GlobalConfig::kStackPos.y + GlobalConfig::kStackSize.height / 2;
}

void GameView::onCardClicked(CardView* cardView)
{
    if (!cardView) return;
    Card* currentCard = cardView->getCardData();
    if (!currentCard) return;
    // 判断是否是手牌
    bool isHandCard = isPointInHandCardArea(currentCard->getPosition());
    if (isHandCard) 
    {
        GameController::getInstance()->onHandCardClick(cardView);
    }
    else {
        GameController::getInstance()->onDesktopCardClick(cardView);
    }
}

void GameView::handleUndo()
{
    if (GameRule::canUndo(GameData::getInstance()->getbackSize()))
    {
        GameData::getInstance()->undoLastOperation();
    }
}

std::vector<CardView*> GameView::GetCardView()
{
    return this->_cardViews;
}
