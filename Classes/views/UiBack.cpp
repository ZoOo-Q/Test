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
    // 初始化回退按钮
    initBackButton();
    return true;
}

void UiBack::initBackButton()
{
    backButton = Button::create(
        GlobalConfig::kBackButton    // 正常
    );

    if (backButton) {
        // 设置按钮位置
        backButton->setPosition(GlobalConfig::kBackPos);
        // 设置按钮层级
        backButton->setLocalZOrder(GlobalConfig::kButton);
        // 绑定点击事件
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