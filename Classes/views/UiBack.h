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

        //����ʵ��
        static UiBack* create();

        //���˰�ť����ص�
        std::function<void()> onBackClicked;

        //���˰�ť
        ui::Button* backButton;

        //��ʼ����ť
        void initBackButton();

        //��ť�������
        void backButtonClicked();
    };
}

#endif // UIBACK_H