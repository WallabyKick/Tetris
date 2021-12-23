//
// Created by WallabyKick on 06.12.2021.
//

#ifndef PROJ_ANDROID_BLOCK_H
#define PROJ_ANDROID_BLOCK_H

#include "Headers.h"
#include "cocos2d.h"



struct Block {
public:
    int x,y;
    cocos2d::Sprite * sprite;
    Block(){
    }
    Block(int x, int y, cocos2d::Sprite * spire){
        this->y = y;
        this->x = x;
        this->sprite = spire;
    }

    void operator=(const Block& block){
        this->x = block.x;
        this->y = block.y;
        this->sprite = block.sprite;
    }

    bool operator==(const Block& block) const
    {
        return (this->x == block.x && this->y == block.y);
    }
};


#endif //PROJ_ANDROID_BLOCK_H
