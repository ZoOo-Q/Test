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
    record.extraData = currentCard->getPosition(); // ��¼ԭʼλ�ã����ڻ���
    Card* baseCard = GameData::getInstance()->getBaseCard();
    // ����Ƿ��ֵΪ1
    if (abs(GlobalConfig::getCardFaceValue(currentCard->getFace()) -GlobalConfig::getCardFaceValue(baseCard->getFace())) == 1) {
        cocos2d::Vec2 originalPos = currentCard->getPosition();//��¼ԭʼλ��
        Card* oldBaseCard = baseCard;//��¼�ɻ�������
        //��ȡ�ɻ������Ƶ���ͼ
        CardView* oldBaseCardView = nullptr;
        auto& cardViews = _gameView->GetCardView();
        for (auto view : cardViews) {
            if (view->getCardData() == oldBaseCard) {
                oldBaseCardView = view;
                break;
            }
        }
        //�ƶ���ǰ���Ƶ���������λ��
        MoveUtils::moveCardStraight(cardView, baseCard->getPosition(),
            GlobalConfig::kCardMoveTime, [=](CardView* view) {
                oldBaseCard->setisSeeable(false);
                if (oldBaseCardView) {oldBaseCardView->setCardVisible(false);}// ���ؾɻ���������ͼ
                // ���»�������
                GameData::getInstance()->setBaseCard(currentCard);
            });
        //��¼����
        record.operationType = OperationRecord::MATCH;
        record.cardA = currentCard;
        record.cardB = oldBaseCard;
        record.extraSData = baseCard->getPosition();
        GameData::getInstance()->pushOperation(record);  // ���ڻ���� _backSize
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
    //��ʼ����Ϸ
    GameService::getInstance()->initCards(GlobalConfig::kInitJson);
}




void GameController::onHandCardClick(CardView* cardView)
{
    if (!cardView) return;
    Card* currentCard = cardView->getCardData();
    Card* baseCard = GameData::getInstance()->getBaseCard();
    //���·����ƿɽ���
    if (!GameData::getInstance()->isLowerCard(currentCard) || !baseCard) { return;}
    //��¼����ǰ��λ��
    cocos2d::Vec2 basePos = baseCard->getPosition();
    cocos2d::Vec2 currentPos = currentCard->getPosition();
    //1. �ƶ���ǰ���Ƶ���������λ��
    MoveUtils::moveCardStraight(cardView, basePos,
        GlobalConfig::kCardMoveTime, nullptr);
    //2. �ƶ��������Ƶ���ǰ����λ�ã����ȡ�������Ƶ���ͼ��
    auto& cardViews = _gameView->GetCardView();
    for (auto view : cardViews) {
        if (view->getCardData() == baseCard) {
            MoveUtils::moveCardStraight(view, currentPos,
                GlobalConfig::kCardMoveTime, [=](CardView* view) {
                    // ������ɣ����»�������
                    GameData::getInstance()->setBaseCard(currentCard);
                });
            break;
        }
    }
    OperationRecord record;
    record.operationType = OperationRecord::SELECT; // ���Ϊ��������
    record.cardA = currentCard;       // �·�����
    record.cardB = baseCard;          // ԭ��������
    record.extraData = currentPos;    // �·�����ԭλ��
    record.extraSData = basePos;    // �·�����ԭλ��
    GameData::getInstance()->addLowerCard(baseCard);//��������
    GameData::getInstance()->deleteLowerCard(currentCard);//��������
    baseCard = currentCard;
    GameData::getInstance()->pushOperation(record);
}


