#include "cell.h"

#include <random>
#include <iostream>

cell::cell(int size_x, int size_y)
{
    map=nullptr;
    setSize(size_x,size_y);
    setMap();
}

cell::~cell()
{
    if(map != nullptr) free(map);
}

void cell::setSize(int size_x, int size_y)
{
    this->sizeX = size_x;
    this->sizeY = size_y;
    this->indexLimit = size_x * size_y;
    if(map != nullptr)  free(map);
    setMap();
}

void cell::setMap()
{
    if(map!= nullptr)
        free( map);
    int *tmp = static_cast<int *>(calloc(sizeof(int),indexLimit));
    this->map = tmp;
    std::random_device rd;
    std::mt19937 mt(rd());                                  //梅森旋转，均匀分布
    for(int i=0;i<indexLimit;i++)
    {
        tmp[i] = mt()%2;
    }
    //paintMap();
}

void cell::updateCell(const int posX, const int posY)
{
    int index = posX+posY*sizeY;
    int status = map[index];

    int count=0;
    for(int i=-1;i<2;++i)
        for(int j=-1;j<2;j++)
        {
            int index_tmp =index+i*sizeY+j;
            if(checkLimit(posX,posY,i,j))
            {
                if(index_tmp < index && map[index_tmp] & 2)
                    ++count;
                else if(index_tmp > index && map[index_tmp] & 1)
                    ++count;
            }

        }
    switch (count) {
    case 2:     //保持
        if(status == this->stillDead || status == this->toDead)
        {
            status = stillDead;
            break;
        }
        if(status == this->stillAlive || status == this->toAlive)
        {
            status = stillAlive;
            break;
        }
    case 3:     //存活
        if(status == this->stillDead || status == this->toDead)
        {
            status = toAlive;
            break;
        }
        if(status == this->stillAlive || status == this->toAlive)
        {
            status = stillAlive;
            break;
        }
        break;
    default:
        if(status == this->stillDead || status == this->toDead)
        {
            status = stillDead;
            break;
        }
        if(status == this->stillAlive || status == this->toAlive)
        {
            status = toDead;
            break;
        }
    };
    map[index] = status;
}

void cell::updateCells()
{
    for(int i=0; i<indexLimit; ++i){
        int x = i%sizeX;
        int y = i/sizeY;
        updateCell(x,y);
    }
    //paintMap();
}

bool cell::checkLimit(int posX,int posY,int offsetX,int offsetY)
{
    if((posX+offsetX < sizeX && posX+offsetX >=0) && (posY+offsetY < sizeY && posY+offsetY >=0))
        return true;
    else
        return false;
}

std::pair<int, int> cell::getSize()
{
    return std::pair<int,int> (sizeX,sizeY);
}

void cell::paintMap()
{
    for(int i=0; i<indexLimit; ++i){
        if(i % sizeX == 0)
            std::cout<<std::endl;
        std::cout<<map[i]<<" ";
    }
    std::cout<<std::endl;
}

int cell::getIndexLimit()
{
    return indexLimit;
}
