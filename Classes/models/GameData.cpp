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
    // 清空
    for (Card* card : _allCards)
    {
        delete card;
    }
    _allCards.clear();
    _matchedCard.clear();

    // 读取JSON文件内容
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

    // 解析JSON
    rapidjson::Document doc;
    doc.Parse(jsonContent.c_str());
    if (doc.HasParseError() || !doc.IsObject())
    {
        return; 
    }

    // 解析Playfield中的卡牌
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfield = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfield.Size(); ++i)
        {
            const rapidjson::Value& cardData = playfield[i];
            if (!cardData.IsObject()) continue;

            // 提取卡牌属性
            int face = cardData["CardFace"].GetInt();
            int suit = cardData["CardSuit"].GetInt();

            // 提取位置信息
            float x = cardData["Position"]["x"].GetFloat();
            float y = cardData["Position"]["y"].GetFloat() ;

            // 创建卡牌并设置属性
            Card* card = Card::create((CardSuitType)suit, (CardFaceType)face);
            if (card)
            {
                card->setPosition(cocos2d::Vec2(x, y));
                addCard(card);
            }
        }
    }

    // 解析Stack中的卡牌
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stack = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stack.Size(); ++i)
        {
            const rapidjson::Value& cardData = stack[i];
            if (!cardData.IsObject()) continue;

            // 提取卡牌属性
            int face = cardData["CardFace"].GetInt();
            int suit = cardData["CardSuit"].GetInt();

            // 提取位置信息
            float x = cardData["Position"]["x"].GetFloat();
            float y = cardData["Position"]["y"].GetFloat();

            // 创建卡牌并设置属性
            Card* card = Card::create((CardSuitType)suit, (CardFaceType)face);
            if (card)
            {
                card->setPosition(cocos2d::Vec2(x, y));
                addCard(card);
            }
        }
    }
    if (!_allCards.empty()) {
        setBaseCard(_allCards.back()); // 假设最后一张为右下角卡牌
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
    // 移除
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
    // 判空
    if (card1 == nullptr || card2 == nullptr || card1 == card2)
        return false;

    // 检查是否已匹配
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
            auto& backStack = gameData->getBackStack();  // 需要在 GameData 中提供获取 _backSize 的方法

            if (!backStack.empty()) {
                lastRecord = backStack.top();
            }
            backStack.pop();
            auto& cardViews = _gameView->GetCardView();
             for (auto view : cardViews)
             {
                    Card* card = view->getCardData();
                   
                    // 恢复位置（已有的位置恢复逻辑保留）
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


