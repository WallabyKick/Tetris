//
// Created by WallabyKick on 08.12.2021.
//

#ifndef PROJ_ANDROID_FIELD_H
#define PROJ_ANDROID_FIELD_H

#include "Headers.h"
#include "cocos2d.h"
#include "Block.h"
#include "Tetramino.h"


USING_NS_CC;

class Field {
public:

    Field(Scene * scene, float posX, float posY);

    int TickUpdate();

    int InstantDown();

    bool MoveLeft();

    bool MoveRight();

    bool Rotate();

private:
    Block BlockField[FIELDSIZE_X][FIELDSIZE_Y];
    Scene * scene;
    Tetramino tetramino;
    Director * director;
    float FieldScale;
    float posX, posY;
    int Instantly = -3;
    bool GenerateNew();
    bool Check();
    bool CleanLine(int Line[4]);
    bool MoveLines(int Line);
};


#endif //PROJ_ANDROID_FIELD_H
