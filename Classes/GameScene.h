//
// Created by WallabyKick on 06.12.2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include "Manager.h"

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float);
    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);


    Manager * manager;
private:
    float ScaleTime = 0.97;
    cocos2d::Label * ScoreLabel;
    int Score = 0;
    float Time = 0;
    float GameTick = 0.5;

    void initPause();
    void Pause(cocos2d::Ref* pSender);
    void UnPause(cocos2d::Ref* pSender);
    bool pause = false;
    cocos2d::Menu* MenuPause;
    CREATE_FUNC(GameScene);
};


#endif //PROJ_ANDROID_GAMESCENE_H
