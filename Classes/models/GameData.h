#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Card.h"
#include <vector>
#include <stack>
#include <memory>

// 操作记录
struct OperationRecord
{
    enum Type { MATCH, SELECT } operationType;  //操作类型：匹配/选中
    //匹配操作的记录
    Card* cardA = nullptr;
    Card* cardB = nullptr;
    cocos2d::Vec2 extraData; //原位置
    cocos2d::Vec2 extraSData;//被匹配的卡牌位置
};

class GameData
{
public:
    static GameData* getInstance();

    void initCards(const std::string& json);

    //获取所有卡牌
    std::vector<Card*> getAllCards() const { return _allCards; }

    //增加卡牌
    void addCard(Card* card);

    //移除卡牌
    void removeCard(Card* card);

    // 获取顶部牌
    Card* getTopHandCard();


    //匹配卡牌
    bool matchCards(Card* card1, Card* card2);  

    // 撤回操作
    bool undoLastOperation();  // 撤回上一步操作
    int getbackSize() const { return _backSize.size(); }  // 获取当前可撤回步数

    void pushOperation(const OperationRecord& record);

    // 设置基础卡牌（右下角）
    void setBaseCard(Card* card) { _baseCard = card; }
    Card* getBaseCard() { return _baseCard; }

    // 添加上方/下方卡牌
    void addUpperCard(Card* card) { _upperCards.push_back(card); }
    void addLowerCard(Card* card) { _lowerCards.push_back(card); }

    void deleteLowerCard(Card* card) {
        if(std::find(_lowerCards.begin(), _lowerCards.end(), card)!=_lowerCards.end())
        {
            _lowerCards.erase(std::find(_lowerCards.begin(), _lowerCards.end(), card));
        }
    }

    //判断是否为上方可匹配卡牌
    bool isUpperCard(Card* card) {
        return std::find(_upperCards.begin(), _upperCards.end(), card) != _upperCards.end();
    }

    //判断是否为下方交换卡牌
    bool isLowerCard(Card* card) {
        return std::find(_lowerCards.begin(), _lowerCards.end(), card) != _lowerCards.end();
    }

    //获取历史操作栈
    std::stack<OperationRecord>& getBackStack() { return _backSize; }

   
   
private:
    GameData(); 
    ~GameData();

    // 存储所有卡牌
    std::vector<Card*> _allCards;

    // 已匹配的卡牌对
    std::vector<std::pair<Card*, Card*>> _matchedCard;

    // 历史栈
    std::stack<OperationRecord> _backSize;

    // 实例
    static GameData* _instance;

    //手牌区卡牌
    std::vector<Card*> _handCards; 
    // 当前顶部牌
    Card* _topHandCard = nullptr; 


    Card* _baseCard = nullptr;      // 右下角
    std::vector<Card*> _upperCards; // 上方可匹配卡牌
    std::vector<Card*> _lowerCards; // 左下方交换卡牌

};



#endif // GAME_DATA_H