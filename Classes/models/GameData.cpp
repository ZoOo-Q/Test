#include "GameData.h"
#include "./configs/GameRule.h"
#include "./configs/GlobalConfig.h"
#include "./controllers/GameController.h"
#include "cocos2d.h"
#include "./cocos2d/external/rapidjson/include/rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "./utils/MoveUtils.h"
GameData* GameData::_instance = nullptr;

GameData* GameData::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new GameData();
    }
    return _instance;
}

void GameData::pushOperation(const OperationRecord& record)
{
    _backSize.push(record);
}

GameData::GameData()
{
    
}

GameData::~GameData()
{
    for (auto * card : _allCards)
    {
        delete card;
    }
    _allCards.clear();
    _matchedCard.clear();
}

void GameData::initCards(const std::string& json)
{
    // ���
    for (Card* card : _allCards)
    {
        delete card;
    }
    _allCards.clear();
    _matchedCard.clear();

    // ��ȡJSON�ļ�����
    std::string jsonContent;
    std::ifstream file(json);
   
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        jsonContent = buffer.str();
        file.close();
    }
    else
    {
        return; 
    }

    // ����JSON
    rapidjson::Document doc;
    doc.Parse(jsonContent.c_str());
    if (doc.HasParseError() || !doc.IsObject())
    {
        return; 
    }

    // ����Playfield�еĿ���
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfield = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfield.Size(); ++i)
        {
            const rapidjson::Value& cardData = playfield[i];
            if (!cardData.IsObject()) continue;

            // ��ȡ��������
            int face = cardData["CardFace"].GetInt();
            int suit = cardData["CardSuit"].GetInt();

            // ��ȡλ����Ϣ
            float x = cardData["Position"]["x"].GetFloat();
            float y = cardData["Position"]["y"].GetFloat() ;

            // �������Ʋ���������
            Card* card = Card::create((CardSuitType)suit, (CardFaceType)face);
            if (card)
            {
                card->setPosition(cocos2d::Vec2(x, y));
                addCard(card);
            }
        }
    }

    // ����Stack�еĿ���
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stack = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stack.Size(); ++i)
        {
            const rapidjson::Value& cardData = stack[i];
            if (!cardData.IsObject()) continue;

            // ��ȡ��������
            int face = cardData["CardFace"].GetInt();
            int suit = cardData["CardSuit"].GetInt();

            // ��ȡλ����Ϣ
            float x = cardData["Position"]["x"].GetFloat();
            float y = cardData["Position"]["y"].GetFloat();

            // �������Ʋ���������
            Card* card = Card::create((CardSuitType)suit, (CardFaceType)face);
            if (card)
            {
                card->setPosition(cocos2d::Vec2(x, y));
                addCard(card);
            }
        }
    }
    if (!_allCards.empty()) {
        setBaseCard(_allCards.back()); // �������һ��Ϊ���½ǿ���
    }

    int i = 0;
    int size = _allCards.size();
    for (auto card : _allCards) {
        if (card->getPosition().y > 1000) {
            addUpperCard(card);
        }
        if (card->getPosition().y < 600)
        { 
            addLowerCard(card);
        }
    }
    
}



void GameData::addCard(Card* card)
{
    if (card == nullptr) return;
    auto it = std::find(_allCards.begin(), _allCards.end(), card);
    if (it == _allCards.end())
    {
        _allCards.push_back(card);
    }
    else
    {
        return;
    }
}

void GameData::removeCard(Card* card)
{
    if (card == nullptr) return;
    // �Ƴ�
    auto it = std::find(_allCards.begin(), _allCards.end(), card);
    if (it != _allCards.end())
    {
        _allCards.erase(it);
    }
    delete card;
}


Card* GameData::getTopHandCard()
{
    return _topHandCard;
}




bool GameData::matchCards(Card* card1, Card* card2)
{
    // �п�
    if (card1 == nullptr || card2 == nullptr || card1 == card2)
        return false;

    // ����Ƿ���ƥ��
    for (const auto& pair : _matchedCard)
    {
        if ((pair.first == card1 && pair.second == card2) ||
            (pair.first == card2 && pair.second == card1))
        {
            return false; 
        }
    }
    if (GameRule::canMatch(card1, card2))
    {
        _matchedCard.emplace_back(card1, card2);
        return true;
    }
    return false;
}

bool GameData::undoLastOperation()
{
    auto _gameView = GameController::getInstance()->getGameView();
    if (!GameData::getInstance()->getBackStack().empty())
    {
        if (GameRule::canUndo(1))
        {

            auto gameData = GameData::getInstance();
            OperationRecord lastRecord;
            auto& backStack = gameData->getBackStack();  // ��Ҫ�� GameData ���ṩ��ȡ _backSize �ķ���

            if (!backStack.empty()) {
                lastRecord = backStack.top();
            }
            backStack.pop();
            auto& cardViews = _gameView->GetCardView();
             for (auto view : cardViews)
             {
                    Card* card = view->getCardData();
                   
                    // �ָ�λ�ã����е�λ�ûָ��߼�������
                    if (lastRecord.operationType == OperationRecord::MATCH)
                    {

                        
                        if (card == lastRecord.cardA)
                        {
                            view->setVisible(true);
                            view->setCardVisible(true);
                            MoveUtils::moveCardStraight(view, lastRecord.extraData);

                        }
                        else if (card == lastRecord.cardB)
                        {
                            view->setVisible(true);
                            view->setCardVisible(true);
                            _baseCard = card;

                        }
                    }
                    else
                    {

                        if (card == lastRecord.cardA)
                        {
                            view->setVisible(true);
                            view->setCardVisible(true);

                            MoveUtils::moveCardStraight(view, lastRecord.extraData);
                            GameData::getInstance()->addLowerCard(card);

                        }
                        else if (card == lastRecord.cardB)
                        {
                            view->setVisible(true);
                            view->setCardVisible(true);

                            MoveUtils::moveCardStraight(view, lastRecord.extraSData);
                            _baseCard = card;
                            GameData::getInstance()->deleteLowerCard(card);

                        }
                    }
            }
        }
    }
    return true;
}


