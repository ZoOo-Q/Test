#include "GameController.h"
#include "./configs/GameRule.h"
#include "./configs/GlobalConfig.h"
#include "./services/GameService.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "./utils/MoveUtils.h"

GameController* GameController::_instance = nullptr;

GameController* GameController::getInstance()
{
    if (!_instance)
    {
        _instance = new (std::nothrow) GameController();
    }
    return _instance;
}

void GameController::onDesktopCardClick(CardView* cardView)
{
    if (!cardView) return;
    OperationRecord record;
    Card* currentCard = cardView->getCardData();
    record.extraData = currentCard->getPosition(); // 记录原始位置，用于回退
    Card* baseCard = GameData::getInstance()->getBaseCard();
    // 检查是否差值为1
    if (abs(GlobalConfig::getCardFaceValue(currentCard->getFace()) -GlobalConfig::getCardFaceValue(baseCard->getFace())) == 1) {
        cocos2d::Vec2 originalPos = currentCard->getPosition();//记录原始位置
        Card* oldBaseCard = baseCard;//记录旧基础卡牌
        //获取旧基础卡牌的视图
        CardView* oldBaseCardView = nullptr;
        auto& cardViews = _gameView->GetCardView();
        for (auto view : cardViews) {
            if (view->getCardData() == oldBaseCard) {
                oldBaseCardView = view;
                break;
            }
        }
        //移动当前卡牌到基础卡牌位置
        MoveUtils::moveCardStraight(cardView, baseCard->getPosition(),
            GlobalConfig::kCardMoveTime, [=](CardView* view) {
                oldBaseCard->setisSeeable(false);
                if (oldBaseCardView) {oldBaseCardView->setCardVisible(false);}// 隐藏旧基础卡牌视图
                // 更新基础卡牌
                GameData::getInstance()->setBaseCard(currentCard);
            });
        //记录操作
        record.operationType = OperationRecord::MATCH;
        record.cardA = currentCard;
        record.cardB = oldBaseCard;
        record.extraSData = baseCard->getPosition();
        GameData::getInstance()->pushOperation(record);  // 现在会存入 _backSize
    }
}

GameController::GameController()
    : _gameView(nullptr)
    , _selectedCardView(nullptr)
{
}

GameController::~GameController()
{
    _gameView = nullptr;
    _selectedCardView = nullptr;
}

void GameController::init(GameView* view)
{
    _gameView = view;
    if (!_gameView)
    {
        return;
    }
    //初始化游戏
    GameService::getInstance()->initCards(GlobalConfig::kInitJson);
}




void GameController::onHandCardClick(CardView* cardView)
{
    if (!cardView) return;
    Card* currentCard = cardView->getCardData();
    Card* baseCard = GameData::getInstance()->getBaseCard();
    //仅下方卡牌可交换
    if (!GameData::getInstance()->isLowerCard(currentCard) || !baseCard) { return;}
    //记录交换前的位置
    cocos2d::Vec2 basePos = baseCard->getPosition();
    cocos2d::Vec2 currentPos = currentCard->getPosition();
    //1. 移动当前卡牌到基础卡牌位置
    MoveUtils::moveCardStraight(cardView, basePos,
        GlobalConfig::kCardMoveTime, nullptr);
    //2. 移动基础卡牌到当前卡牌位置（需获取基础卡牌的视图）
    auto& cardViews = _gameView->GetCardView();
    for (auto view : cardViews) {
        if (view->getCardData() == baseCard) {
            MoveUtils::moveCardStraight(view, currentPos,
                GlobalConfig::kCardMoveTime, [=](CardView* view) {
                    // 交换完成，更新基础卡牌
                    GameData::getInstance()->setBaseCard(currentCard);
                });
            break;
        }
    }
    OperationRecord record;
    record.operationType = OperationRecord::SELECT; // 标记为交换操作
    record.cardA = currentCard;       // 下方卡牌
    record.cardB = baseCard;          // 原基础卡牌
    record.extraData = currentPos;    // 下方卡牌原位置
    record.extraSData = basePos;    // 下方卡牌原位置
    GameData::getInstance()->addLowerCard(baseCard);//更新手牌
    GameData::getInstance()->deleteLowerCard(currentCard);//更新手牌
    baseCard = currentCard;
    GameData::getInstance()->pushOperation(record);
}


