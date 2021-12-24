//
// Created by WallabyKick on 08.12.2021.
//

#ifndef PROJ_ANDROID_FIELD_H
#define PROJ_ANDROID_FIELD_H

#include "Headers.h"
#include "Block.h"


class Manager {
public:

    Manager(Scene * scene, float posX, float posY, int & score);

    bool TickUpdate();

    void InstantDown();

    bool MoveLeft();

    bool MoveRight();

    bool Rotate();

private:
    int * score;
    std::vector<Block> Tetramino;
    std::vector<Block> TetraminoNext;
    std::vector<Block> Field;
    Vec2 origin;
    Scene * scene;
    Director * director;
    float FieldScale;
    float posX, posY;

    bool GenerateNew();

    bool CheckCollisson();
    bool CheckBorder();
    void CheckLine();
    //return can move down
    bool MoveDown();
    bool MoveLines(int Line);
};


#endif //PROJ_ANDROID_FIELD_H
