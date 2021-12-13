//
// Created by WallabyKick on 06.12.2021.
//

#ifndef PROJ_ANDROID_BLOCK_H
#define PROJ_ANDROID_BLOCK_H

#pragma once
#include "Headers.h"
#include "cocos2d.h"

class Block {
public:
    int x,y;
    cocos2d::Sprite * sprite;
    Block(){
        sprite->create();
    }

    void operator=(const Block& block){
        this->x = block.x;
        this->y = block.y;
    }

    bool operator==(const Block& block) const
    {
        return (this->x == block.x && this->y == block.y);
    }
};


#endif //PROJ_ANDROID_BLOCK_H
