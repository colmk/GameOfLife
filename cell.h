#ifndef PROCESS_H
#define PROCESS_H

#include<utility>

class cell
{
public:
    //cell();
    cell(int sizeX, int sizeY);
    ~cell();
    void setSize(const int sizeX, const int sizeY);
    void setMap();
    void updateCell(const int posX,const int posY);               //更新细胞状态
    void updateCells();
    int fresh(const int posX,const int posY);                     //刷新细胞状态
    bool checkLimit(int posX, int posY,int offsetX,int offsetY);
    std::pair<int,int> getSize();
    void paintMap();
    int getIndexLimit();

    int *map;
private:
    int sizeX;
    int sizeY;
    int indexLimit;
    enum status{stillDead=0,toAlive,toDead,stillAlive};    //细胞状态集
};

#endif // PROCESS_H
