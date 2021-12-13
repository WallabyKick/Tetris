//
// Created by WallabyKick on 04.12.2021.
//

#include "StartMenu.h"
#include "GameScene.h"
#define MARKER_FELT_TTF "fonts/Marker Felt.ttf"
USING_NS_CC;

Scene* StartMenu::createScene(){
    return StartMenu::create();
}

bool StartMenu::init() {

    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<MenuItem*> MenuItems;

    closeItem = MenuItemImage::create(
            "Control.png",
            "Control.png",
            CC_CALLBACK_1(StartMenu::ViewControl, this));
    closeItem->setPosition(origin.x+ visibleSize.width/2,origin.y+visibleSize.height/2);
    closeItem->setVisible(false);
    closeItem->setEnabled(false);



    auto PrimaryItem = MenuItemLabel::create(Label::createWithTTF("First Place", MARKER_FELT_TTF, 24));
    MenuItems.pushBack(PrimaryItem);
    PrimaryItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/10*9 + origin.y);

    auto StartGameItem = MenuItemLabel::create(Label::createWithTTF("Start", MARKER_FELT_TTF, 18),
                                               CC_CALLBACK_1(StartMenu::StartGame, this));
    MenuItems.pushBack(StartGameItem);
    StartGameItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/10*7 + origin.y);

    auto ControlViewItem = MenuItemLabel::create(Label::createWithTTF("Control", MARKER_FELT_TTF, 18),
                                                 ([&](Ref* sender) { closeItem->setVisible(true);
                                                     closeItem->setEnabled(true); }));
    MenuItems.pushBack(ControlViewItem);
    ControlViewItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/10*5 + origin.y);

    auto CloseItem =  MenuItemLabel::create(Label::createWithTTF("Close", MARKER_FELT_TTF, 18),
                                            ([&](Ref* sender) { Director::getInstance()->end(); }));
    MenuItems.pushBack(CloseItem);
    CloseItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/10*2 + origin.y);

    auto menu = Menu::createWithArray(MenuItems);
    menu->addChild(closeItem, 10);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void StartMenu::StartGame(cocos2d::Ref* pSender)
{
    auto TheGameScene = GameScene::createScene();
    Director::getInstance()->pushScene(TheGameScene);

}


void StartMenu::ViewControl(cocos2d::Ref* pSender)
{
    closeItem->setVisible(false);
    closeItem->setEnabled(false);
}