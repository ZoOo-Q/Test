#include "UiBack.h"
#include "ui/CocosGUI.h"  

using namespace cocos2d::ui;
using namespace cocos2d;

UiBack::UiBack()
    : backButton(nullptr)
    , onBackClicked(nullptr)
{
}

UiBack::~UiBack()
{
}

UiBack* UiBack::create()
{
    UiBack* ret = new (std::nothrow) UiBack();
    if (ret && ret->init()) 
    {
        return ret;
    }
    delete ret; 
    return nullptr;
}

bool UiBack::init()
{
    if (!Layer::init()) {
        return false;
    }
    // ��ʼ�����˰�ť
    initBackButton();
    return true;
}

void UiBack::initBackButton()
{
    backButton = Button::create(
        GlobalConfig::kBackButton    // ����
    );

    if (backButton) {
        // ���ð�ťλ��
        backButton->setPosition(GlobalConfig::kBackPos);
        // ���ð�ť�㼶
        backButton->setLocalZOrder(GlobalConfig::kButton);
        // �󶨵���¼�
        backButton->addClickEventListener([this](Ref*) {
            this->backButtonClicked();
            });
        this->addChild(backButton);
    }
}

void UiBack::backButtonClicked()
{
    if (onBackClicked) 
    {
        onBackClicked();
    }
}