//
// Created by WallabyKick on 08.12.2021.
//

#include "Manager.h"


Manager::Manager(Scene * scene, float posX, float posY, int & score){
    director = Director::getInstance();
    FieldScale = director->getVisibleSize().width/FIELDSIZE_X;
    origin = Director::getInstance()->getVisibleOrigin();
    this->scene = scene;
    this->posX = posX;
    this->posY = posY;
    this->score = &score;
    GenerateNew();
}

bool Manager::TickUpdate(){
    if (!MoveDown()) {
        if (!GenerateNew()) {
            return false;
        } else {
            CheckLine();
        }
    }
    return true;
}

bool Manager::MoveDown(){

    std::vector<Block> Buff;
    Buff.insert(Buff.end(),Tetramino.begin(),Tetramino.end());

    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.y++;
    });

    if (!CheckCollisson() || !CheckBorder()){
        Tetramino.clear();
        Tetramino.insert(Tetramino.end(),Buff.begin(),Buff.end());
        return false;
    }
    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.sprite->setPositionY(item.sprite->getPositionY() - item.sprite->getContentSize().height);
    });

    return true;
}

bool Manager::MoveLeft(){

    std::vector<Block> Buff;
    Buff.insert(Buff.end(),Tetramino.begin(),Tetramino.end());

    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.x--;
    });


    if (!CheckCollisson() || !CheckBorder()){
        Tetramino.clear();
        Tetramino.insert(Tetramino.end(),Buff.begin(),Buff.end());
        return false;
    }
    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.sprite->setPositionX(item.sprite->getPositionX() - item.sprite->getContentSize().height);
    });
    return true;
}

bool Manager::MoveRight(){
    std::vector<Block> Buff;
    Buff.insert(Buff.end(),Tetramino.begin(),Tetramino.end());

    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.x++;
    });

    if (!CheckCollisson() || !CheckBorder()){
        Tetramino.clear();
        Tetramino.insert(Tetramino.end(),Buff.begin(),Buff.end());
        return false;
    }
    for_each(begin(Tetramino),end(Tetramino),[](Block & item){
        item.sprite->setPositionX(item.sprite->getPositionX() + item.sprite->getContentSize().height);
    });
    return true;
}

bool Manager::Rotate(){
    Block save[4];
    Block p = Tetramino[1];
    for (int n = 0; n < 4; n++)
        save[n] = Tetramino[n];
    for (int n = 0; n < 4; n++)
    {
        int x = Tetramino[n].y - p.y;
        int y = Tetramino[n].x - p.x;
        Tetramino[n].x = p.x - x;
        Tetramino[n].y = p.y + y;
    }
    if (!CheckCollisson()||!CheckBorder()) {
        for (int n = 0; n < 4; n++) {
            Tetramino[n] = save[n];
        }
        return false;
    }
    for (int n = 0; n <4; n++){
        Tetramino[n].sprite->setPosition(Tetramino[n].x*FieldScale+FieldScale/2+posX,(FIELDSIZE_Y-Tetramino[n].y)*FieldScale+FieldScale/2+posY);
    }
    return true;
}

void Manager::InstantDown(){
    while(MoveDown());
}

bool Manager::CheckCollisson(){
    for (int i = 0; i < Field.size(); i++){
        for(int j = 0; j < Tetramino.size();j++){
            if (Field[i] == Tetramino[j])
                return false;
        }
    }
    return true;
}

bool Manager::CheckBorder(){
    for (int i = 0; i < Tetramino.size(); i++){
        if ((Tetramino[i].x > FIELDSIZE_X-1)||(Tetramino[i].x < 0)||
                (Tetramino[i].y > FIELDSIZE_Y-1)||(Tetramino[i].y < 0))
            return false;
    }
    return true;
}

void Manager::CheckLine(){
    std::vector<int> numberLines;
    int counter = 0;
    sort(Field.begin(),
         Field.end(),
         [](const Block& lhs, const Block& rhs)
         {
             return lhs.y < rhs.y;
         });
    for (int i = 0; i < Field.size(); i++){
        if (Field[i].y == Field[i+1].y) {
            counter++;
            if (counter == FIELDSIZE_X-1)
                numberLines.push_back(Field[i].y);
        }
        else
            counter = 0;
    }
    for (int i = 0; i < numberLines.size(); i++){
        MoveLines(numberLines[i]);
    }
    *score += numberLines.size() == 4 ? 100 : numberLines.size()*10;
}

bool Manager::MoveLines(int Line){
    for (int i = 0; i < Field.size(); i++){
        if (Field[i].y == Line) {
            scene->removeChild(Field[i].sprite);
            Field.erase(Field.begin()+i);
            i--;
        }
        else
            if (Field[i].y < Line) {
                Field[i].y++;
                Field[i].sprite->setPositionY(Field[i].sprite->getPositionY() - Field[i].sprite->getContentSize().height);
            }
    }
    return true;
}

bool Manager::GenerateNew() {
    int NextScale = 3;
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
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> TypeFigure(0,6);
    std::uniform_int_distribution<std::mt19937::result_type> ColorFigure(1,5);

    Field.insert(Field.end(),Tetramino.begin(),Tetramino.end());


    int n = TypeFigure(rng);
    int nBuf = TypeFigure(rng);
    int color = ColorFigure(rng);
    int colorBUF = ColorFigure(rng);
    if (Tetramino.empty()){
        for (int i = 0; i < 4; i++)
        {
            Tetramino.push_back({figures[n][i] % 2 + FIELDSIZE_X/2,figures[n][i] / 2,Sprite::createWithSpriteFrameName(std::to_string(color))});
            Tetramino[i].sprite->setContentSize(Size(FieldScale,FieldScale));
            Tetramino[i].sprite->setPosition(Tetramino[i].x*FieldScale+FieldScale/2+posX,
                                             (FIELDSIZE_Y-Tetramino[i].y)*FieldScale+FieldScale/2+posY);
            scene->addChild(Tetramino[i].sprite);

            TetraminoNext.push_back({figures[nBuf][i] % 2 + FIELDSIZE_X/2,figures[nBuf][i] / 2,Sprite::createWithSpriteFrameName(std::to_string(colorBUF))});
            TetraminoNext[i].sprite->setContentSize(Size(FieldScale/NextScale,FieldScale/NextScale));
            TetraminoNext[i].sprite->setPosition((TetraminoNext[i].x-FIELDSIZE_X/2)*FieldScale/NextScale+FieldScale/2/NextScale+origin.x + director->getVisibleSize().width/4,
                                                 director->getVisibleSize().height -(TetraminoNext[i].y+1)*FieldScale/NextScale+FieldScale/2/NextScale+origin.y);
            scene->addChild(TetraminoNext[i].sprite);
        }
    }
    else{
        Tetramino.clear();
        Tetramino.insert(Tetramino.end(), TetraminoNext.begin(),TetraminoNext.end());
        TetraminoNext.clear();
        for (int i = 0; i < Tetramino.size(); i++){
            for (int j = 0; j < Field.size();j++){
                if (Tetramino[i] == Field[j]) {
                    return false;
                }
            }
            Tetramino[i].sprite->setContentSize(Size(FieldScale,FieldScale));
            Tetramino[i].sprite->setPosition(Tetramino[i].x*FieldScale+FieldScale/2+posX,
                                             (FIELDSIZE_Y-Tetramino[i].y)*FieldScale+FieldScale/2+posY);

            TetraminoNext.push_back({figures[nBuf][i] % 2 + FIELDSIZE_X/2,figures[nBuf][i] / 2,Sprite::createWithSpriteFrameName(std::to_string(colorBUF))});
            TetraminoNext[i].sprite->setContentSize(Size(FieldScale/NextScale,FieldScale/NextScale));
            TetraminoNext[i].sprite->setPosition((TetraminoNext[i].x-FIELDSIZE_X/2)*FieldScale/NextScale+FieldScale/2/NextScale+origin.x + director->getVisibleSize().width/4 ,
                                                 director->getVisibleSize().height -(TetraminoNext[i].y+1)*FieldScale/NextScale+FieldScale/2/NextScale+origin.y);
            scene->addChild(TetraminoNext[i].sprite);
        }
    }
    return true;
}

