#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Card.h"
#include <vector>
#include <stack>
#include <memory>

// ������¼
struct OperationRecord
{
    enum Type { MATCH, SELECT } operationType;  //�������ͣ�ƥ��/ѡ��
    //ƥ������ļ�¼
    Card* cardA = nullptr;
    Card* cardB = nullptr;
    cocos2d::Vec2 extraData; //ԭλ��
    cocos2d::Vec2 extraSData;//��ƥ��Ŀ���λ��
};

class GameData
{
public:
    static GameData* getInstance();

    void initCards(const std::string& json);

    //��ȡ���п���
    std::vector<Card*> getAllCards() const { return _allCards; }

    //���ӿ���
    void addCard(Card* card);

    //�Ƴ�����
    void removeCard(Card* card);

    // ��ȡ������
    Card* getTopHandCard();


    //ƥ�俨��
    bool matchCards(Card* card1, Card* card2);  

    // ���ز���
    bool undoLastOperation();  // ������һ������
    int getbackSize() const { return _backSize.size(); }  // ��ȡ��ǰ�ɳ��ز���

    void pushOperation(const OperationRecord& record);

    // ���û������ƣ����½ǣ�
    void setBaseCard(Card* card) { _baseCard = card; }
    Card* getBaseCard() { return _baseCard; }

    // ����Ϸ�/�·�����
    void addUpperCard(Card* card) { _upperCards.push_back(card); }
    void addLowerCard(Card* card) { _lowerCards.push_back(card); }

    void deleteLowerCard(Card* card) {
        if(std::find(_lowerCards.begin(), _lowerCards.end(), card)!=_lowerCards.end())
        {
            _lowerCards.erase(std::find(_lowerCards.begin(), _lowerCards.end(), card));
        }
    }

    //�ж��Ƿ�Ϊ�Ϸ���ƥ�俨��
    bool isUpperCard(Card* card) {
        return std::find(_upperCards.begin(), _upperCards.end(), card) != _upperCards.end();
    }

    //�ж��Ƿ�Ϊ�·���������
    bool isLowerCard(Card* card) {
        return std::find(_lowerCards.begin(), _lowerCards.end(), card) != _lowerCards.end();
    }

    //��ȡ��ʷ����ջ
    std::stack<OperationRecord>& getBackStack() { return _backSize; }

   
   
private:
    GameData(); 
    ~GameData();

    // �洢���п���
    std::vector<Card*> _allCards;

    // ��ƥ��Ŀ��ƶ�
    std::vector<std::pair<Card*, Card*>> _matchedCard;

    // ��ʷջ
    std::stack<OperationRecord> _backSize;

    // ʵ��
    static GameData* _instance;

    //����������
    std::vector<Card*> _handCards; 
    // ��ǰ������
    Card* _topHandCard = nullptr; 


    Card* _baseCard = nullptr;      // ���½�
    std::vector<Card*> _upperCards; // �Ϸ���ƥ�俨��
    std::vector<Card*> _lowerCards; // ���·���������

};



#endif // GAME_DATA_H