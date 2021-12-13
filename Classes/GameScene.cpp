//
// Created by WallabyKick on 06.12.2021.
//

#include "GameScene.h"


#define MARKER_FELT_TTF "fonts/Marker Felt.ttf"


USING_NS_CC;

Scene* GameScene::createScene(){
    return GameScene::create();
}

void GameScene::initPause(){
    Vector<MenuItem*> MenuItems;
    auto ExitLabel = MenuItemLabel::create(Label::createWithTTF("To Start menu", MARKER_FELT_TTF, 16), ([&](Ref* sender) { Director::getInstance()->popScene();}));
    ExitLabel->setPosition(Director::getInstance()->getVisibleSize().width/2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height/10*7 + Director::getInstance()->getVisibleOrigin().y);
    MenuItems.pushBack(ExitLabel);
    auto UnPauseLabel = MenuItemLabel::create(Label::createWithTTF("Unpause", MARKER_FELT_TTF, 16),CC_CALLBACK_1(GameScene::UnPause, this));
    UnPauseLabel->setPosition(Director::getInstance()->getVisibleSize().width/2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height/10*5 + Director::getInstance()->getVisibleOrigin().y);
    MenuItems.pushBack(UnPauseLabel);
    MenuPause = Menu::createWithArray(MenuItems);
    MenuPause->setPosition(Vec2::ZERO);
    this->addChild(MenuPause, 1);
    MenuPause->setVisible(false);
    MenuPause->setEnabled(false);
}

bool GameScene::init(){

    if (!Scene::init()) {
        return false;
    }
    initPause();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<MenuItem*> MenuItems;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite.plist", "Sprite.png");

    auto PauseItem = MenuItemLabel::create(Label::createWithTTF("Back/Pause", MARKER_FELT_TTF, 12),
                                           CC_CALLBACK_1(GameScene::Pause, this));
    MenuItems.pushBack(PauseItem);
    PauseItem->setPosition(visibleSize.width - PauseItem->getContentSize().width/2 + origin.x, visibleSize.height - PauseItem->getContentSize().height + origin.y);

    ScoreLabel = Label::createWithTTF("Score: ", MARKER_FELT_TTF, 12);
    addChild(ScoreLabel);
    ScoreLabel->setPosition(ScoreLabel->getContentSize().width/2 + origin.x, ScoreLabel->getContentSize().height + origin.y);
    field = new Field(this, ScoreLabel->getPositionX()-ScoreLabel->getContentSize().width/2,ScoreLabel->getPositionY()-ScoreLabel->getContentSize().height/2);


    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    this->scheduleUpdate();
    return true;
}

void GameScene::Pause(cocos2d::Ref* pSender)
{
    MenuPause->setVisible(true);
    MenuPause->setEnabled(true);
    pause = true;
}

void GameScene::UnPause(cocos2d::Ref* pSender)
{
    MenuPause->setVisible(false);
    MenuPause->setEnabled(false);
    pause = false;
}

void GameScene::update(float delta){
    if (!pause){
        Time += delta;
        if (Time > GameTick) {
            int Case = field->TickUpdate();
            switch (Case) {
                case -2:
                    Director::getInstance()->popScene();
                    break;
                case -1:
                    break;
                case 0:
                    GameTick *= ScaleTime;
                    break;
                case 4:
                    GameTick *= ScaleTime;
                    Score +=100;
                    break;
                default:
                    GameTick *= ScaleTime;
                    Score += Case*10;
                    break;
            }
            ScoreLabel->setString("Score: " + std::to_string(Score));
            ScoreLabel->setPosition(ScoreLabel->getContentSize().width/2 + Director::getInstance()->getVisibleOrigin().x, ScoreLabel->getContentSize().height + Director::getInstance()->getVisibleOrigin().y);
            Time = 0;
        }
    }
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    if (!pause) {
        if (touch->getLocation().x - Director::getInstance()->getVisibleOrigin().x <
            Director::getInstance()->getVisibleSize().width / 2) {
            if (touch->getLocation().y - Director::getInstance()->getVisibleOrigin().y >
                Director::getInstance()->getVisibleSize().height / 2)
                field->MoveLeft();
            else
                field->InstantDown();
        } else {
            if (touch->getLocation().y - Director::getInstance()->getVisibleOrigin().y <
                Director::getInstance()->getVisibleSize().height / 2)
                field->Rotate();
            else
                field->MoveRight();
        }
    }
    return true;
}