#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include "cocos2d.h"
#include <functional>

class Card;

class CardView : public cocos2d::Sprite
{
public:
    
   
    //������CardViewʵ��
    //����:����ʵ��
    //����ֵ:����ͼ��ʵ��
    static CardView* create(Card* cardData);

    //���캯��
    //������cardData ��������ָ��
    explicit CardView(Card* cardData);

    ~CardView() override;

    //���ÿ��ƿɼ���
    //������isVisible �Ƿ�ɼ�
    void setCardVisible(bool isVisible);

    
    //���¿���λ�ã���������
    //������targetPos Ŀ��λ��  duration ����ʱ��
    void updatePosition(const cocos2d::Vec2& targetPos, float duration);

    
    //�ص�����
    //������callback �ص�����
    void setClickCallback(const std::function<void(CardView*)>& callback);

   
    //��ȡ�����Ŀ�������
    //����ֵ����������ָ��
    Card* getCardData() const { return _cardData; }

    
    // ��ʼ������
    bool init() override;

    //���ؿ���ͼƬ
    void loadCardPicture();

    //�����ʼ�¼�����
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    //��������¼�����
    void touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);

  

private:
    Card* _cardData;                 // ��������
    cocos2d::Sprite* _faceSprite;    // ��������
    std::function<void(CardView*)> _clickCallback;  // ����ص�
};

#endif // CARD_VIEW_H
