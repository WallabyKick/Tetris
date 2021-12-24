//
// Created by WallabyKick on 04.12.2021.
//

#ifndef PROJ_ANDROID_STARTMENU_H
#define PROJ_ANDROID_STARTMENU_H

#include "Headers.h"

class StartMenu : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    void StartGame(cocos2d::Ref* pSender);
    void ViewControl(cocos2d::Ref* pSender);

private:
    cocos2d::MenuItemImage* closeItem;
    CREATE_FUNC(StartMenu);

};


#endif //PROJ_ANDROID_STARTMENU_H
