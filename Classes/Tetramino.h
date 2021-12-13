//
// Created by WallabyKick on 06.12.2021.
//

#ifndef PROJ_ANDROID_TETRAMINO_H
#define PROJ_ANDROID_TETRAMINO_H

#pragma once
#include "Block.h"
#include "Headers.h"
USING_NS_CC;

class Tetramino {
public:
    Block Blocks[4];
    Director * director;
    float FieldScale;
        Tetramino();
    void generate(int X, int Y);
};


#endif //PROJ_ANDROID_TETRAMINO_H
