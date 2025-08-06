#ifndef UIBACK_H
#define UIBACK_H

#include "cocos2d.h"
#include "./configs/GlobalConfig.h"

namespace cocos2d {
    namespace ui {
        class Button;
    }

    class UiBack : public Layer
    {
    public:
        UiBack();
        virtual ~UiBack() override;

        virtual bool init() override;

        //创建实例
        static UiBack* create();

        //回退按钮点击回调
        std::function<void()> onBackClicked;

        //回退按钮
        ui::Button* backButton;

        //初始化按钮
        void initBackButton();

        //按钮点击处理
        void backButtonClicked();
    };
}

#endif // UIBACK_H