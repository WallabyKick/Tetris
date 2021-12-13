//
// Created by WallabyKick on 08.12.2021.
//

#include "Field.h"


Field::Field(Scene * scene, float posX, float posY){
    director = Director::getInstance();
    FieldScale = director->getVisibleSize().width/FIELDSIZE_X;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->scene = scene;
    tetramino.generate(FIELDSIZE_X/2, 0);
    this->posX = posX;
    this->posY = posY;
    for (int n = 0; n < 4; n++){
        tetramino.Blocks[n].sprite->setPosition(tetramino.Blocks[n].x*FieldScale+FieldScale/2+posX,(FIELDSIZE_Y-tetramino.Blocks[n].y)*FieldScale+FieldScale/2+posY);
        scene->addChild(tetramino.Blocks[n].sprite);
    }
    for (int i = 0; i < FIELDSIZE_X; i++){
        for (int j = 0; j < FIELDSIZE_Y; j++){
            BlockField[i][j].x = -1;
            BlockField[i][j].y = -1;
        }
    }
}

int Field::TickUpdate(){
    if (Instantly != -3){
        int buf = Instantly;
        Instantly = -3;
        return buf;
    }
    for (int n = 0; n <4; n++){
        if (((tetramino.Blocks[n].y+1 == BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y+1].y)&&(tetramino.Blocks[n].x == BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y+1].x))||(tetramino.Blocks[n].y+1 == FIELDSIZE_Y)){
            if (!GenerateNew())
                return -2;
            int LineCount = 0;
            int LineTake[4] = {-1, -1, -1, -1};
            for (int j = 0; j < FIELDSIZE_Y; j++){
                int BlockCount = 0;
                for (int i = 0; i < FIELDSIZE_X; i++){
                    if (BlockField[i][j].y > -1){
                        BlockCount++;
                        if (BlockCount == FIELDSIZE_X) {
                            LineTake[LineCount] = j;
                            LineCount++;
                        }
                    }
                }
            }
            CleanLine(LineTake);
            return LineCount;
        }
    }
    for (int n = 0; n <4; n++){
        ++tetramino.Blocks[n].y;
        tetramino.Blocks[n].sprite->setPositionY(tetramino.Blocks[n].sprite->getPositionY()-FieldScale);
    }
    return -1;
}

int Field::InstantDown(){
    while(1){
        int Stack;
        Stack = TickUpdate();
        if (Stack != -1) {
            Instantly = Stack;
            return Stack;
        }
    }
}

bool Field::CleanLine(int Line[4]){
    for (int j = 0; j < 4; j++) {
        if (Line[j] < 0)
            break;
        for (int i = 0; i < FIELDSIZE_X; i++) {
            BlockField[i][Line[j]].x = -1;
            BlockField[i][Line[j]].y = -1;
            scene->removeChild(BlockField[i][Line[j]].sprite, true);
        }
        MoveLines(Line[j]);
    }
    return true;
}

bool Field::MoveLines(int Line){
    for (int i = 0; i < FIELDSIZE_X; i++){
        for (int j = Line; j > 0; j--){
            BlockField[i][j] = BlockField[i][j-1];
            BlockField[i][j].sprite = BlockField[i][j - 1].sprite;
            if (BlockField[i][j-1].y > 0){
                BlockField[i][j].y++;
                BlockField[i][j].sprite->setPositionY(
                        BlockField[i][j].sprite->getPositionY() - FieldScale);
            }
        }
    }
    return true;
}

bool Field::MoveLeft(){
    for (int n = 0; n < 4; n++){
        if (((tetramino.Blocks[n].y == BlockField[tetramino.Blocks[n].x-1][tetramino.Blocks[n].y].y)&&
             (tetramino.Blocks[n].x-1 == BlockField[tetramino.Blocks[n].x-1][tetramino.Blocks[n].y].x))||
            (tetramino.Blocks[n].x-1 == -1))
            return false;
    }
    for (int n = 0; n <4; n++){
        --tetramino.Blocks[n].x;
        tetramino.Blocks[n].sprite->setPositionX(tetramino.Blocks[n].sprite->getPositionX()-FieldScale);
    }
    return true;
}

bool Field::MoveRight(){
    for (int n = 0; n < 4; n++){
        if (((tetramino.Blocks[n].y == BlockField[tetramino.Blocks[n].x+1][tetramino.Blocks[n].y].y)&&
             (tetramino.Blocks[n].x+1 == BlockField[tetramino.Blocks[n].x+1][tetramino.Blocks[n].y].x))||
            (tetramino.Blocks[n].x+1 == FIELDSIZE_X))
            return false;
    }
    for (int n = 0; n <4; n++){
        ++tetramino.Blocks[n].x;
        tetramino.Blocks[n].sprite->setPositionX(tetramino.Blocks[n].sprite->getPositionX()+FieldScale);
    }
    return true;
}


bool Field::Check(){
    for (int n = 0; n < 4; n++){
        if ((tetramino.Blocks[n].x >FIELDSIZE_X-1)||(tetramino.Blocks[n].x < 0)||(tetramino.Blocks[n].y > FIELDSIZE_Y-1)||(tetramino.Blocks[n].y < 0)||
            (tetramino.Blocks[n] == BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y])){
            return false;
        }
    }
    return true;
}

bool Field::Rotate(){
    Block save[4];
    Block p = tetramino.Blocks[1];
    for (int n = 0; n < 4; n++)
        save[n] = tetramino.Blocks[n];
    for (int n = 0; n < 4; n++)
    {
        int x = tetramino.Blocks[n].y - p.y;
        int y = tetramino.Blocks[n].x - p.x;
        tetramino.Blocks[n].x = p.x - x;
        tetramino.Blocks[n].y = p.y + y;
    }
    if (!Check()) {
        for (int n = 0; n < 4; n++) {
            tetramino.Blocks[n] = save[n];
        }
        return false;
    }
    for (int n = 0; n <4; n++){
        tetramino.Blocks[n].sprite->setPosition(tetramino.Blocks[n].x*FieldScale+FieldScale/2+posX,(FIELDSIZE_Y-tetramino.Blocks[n].y)*FieldScale+FieldScale/2+posY);
    }
    return true;
}


bool Field::GenerateNew() {
    for (int n = 0; n < 4; n++){
        BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y] = tetramino.Blocks[n];
        BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y].sprite = tetramino.Blocks[n].sprite;
    }
    tetramino.generate(FIELDSIZE_X / 2, 0);
    for (int n = 0; n <4; n++){
        if (tetramino.Blocks[n] == BlockField[tetramino.Blocks[n].x][tetramino.Blocks[n].y])
            return false;
    }
    for (int n = 0; n < 4; n++) {
        tetramino.Blocks[n].sprite->setPosition(
                tetramino.Blocks[n].x * FieldScale + FieldScale / 2 + posX,
                (FIELDSIZE_Y - tetramino.Blocks[n].y) * FieldScale + FieldScale / 2 + posY);
        scene->addChild(tetramino.Blocks[n].sprite);
    }
    return true;
}