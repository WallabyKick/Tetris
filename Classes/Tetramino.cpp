//
// Created by WallabyKick on 06.12.2021.
//

#include "Tetramino.h"



Tetramino::Tetramino(){
    director = Director::getInstance();
    FieldScale = director->getVisibleSize().width/FIELDSIZE_X;
}

void Tetramino::generate(int X, int Y) {
    int figures[7][4]=
            {
                    1,3,5,7, // I
                    2,4,5,7, // Z
                    3,5,4,6, // S
                    3,5,4,7, // T
                    2,3,5,7, // L
                    3,5,7,6, // J
                    2,3,4,5, // O
            };
    int n = rand()%7;
    int color = rand()%5+1;
    for (int i = 0; i < 4; i++)
    {
        Blocks[i].x = figures[n][i] % 2 + X;
        Blocks[i].y = figures[n][i] / 2 + Y;
        Blocks[i].sprite = Sprite::createWithSpriteFrameName(std::to_string(color));
        Blocks[i].sprite->setContentSize(Size(FieldScale,FieldScale));
    }
}