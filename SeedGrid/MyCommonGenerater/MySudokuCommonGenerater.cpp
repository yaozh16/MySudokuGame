#include "MySudokuCommonGenerater.h"
#include <fstream>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
int MySudokuGenerater::Init()
{
    Grid.clear();
    for(int i=0;i<81;i++)
        Grid.push_back(0);

    srand(time(NULL));
    return 0;
}
int MySudokuGenerater::towerSwap()
{
    int i=rand()%3;
    int j=i;
    while(j==i){j=rand()%3;}

    for(int y=0;y<3;y++)
        for(int x=0;x<9;x++)
            swap(Grid[x+(i*3+y)*9],Grid[x+(j*3+y)*9]);
    return 0;
}
int MySudokuGenerater::floorSwap()
{
    int i=rand()%3;
    int j=i;
    while(j==i){j=rand()%3;}

    for(int x=0;x<3;x++)
        for(int y=0;y<9;y++)
            swap(Grid[i*3+x+y*9],Grid[j*3+x+y*9]);
    return 0;
}
int MySudokuGenerater::arraySwap()
{
    int tower=rand()%3;
    int i=rand()%3;
    int j=i;
    while(j==i){j=rand()%3;}
    for(int y=0;y<9;y++)
        swap(Grid[i+3*tower+9*y],Grid[j+3*tower+9*y]);
    return 0;
}
int MySudokuGenerater::rowSwap()
{
    int floor=rand()%3;
    int i=rand()%3;
    int j=i;
    while(j==i){j=rand()%3;}
    for(int t=0;t<9;t++)
        swap(Grid[t+9*(i+3*floor)],Grid[t+9*(j+3*floor)]);
    return 0;
}
int MySudokuGenerater::NumberReplace()
{

    std::vector<int> a;
    for(int i=0;i<10;i++)
        a.push_back(i);
    int count=rand()%10+10;
    for(int i=0;i<count;i++)
    {
        int x=rand()%9+1;
        int y=rand()%9+1;
        while(y==x){y=rand()%9+1;}
        swap(a[x],a[y]);
    }
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
            if(Grid[x+9*y]!=0)
                Grid[x+9*y]=a[Grid[x+9*y]];
    return 0;
}
int MySudokuGenerater::Generate()
{
    int ChangeCount=rand()%20+20;
    for(int i=0;i<ChangeCount;i++)
    {
        switch(rand()%4)
        {
        case 0:
            towerSwap();
            break;
        case 1:
            floorSwap();
            break;
        case 2:
            arraySwap();
            break;
        case 3:
            rowSwap();
            break;
        }
    }
    NumberReplace();
    return 0;
}
void MySudokuGenerater::swap(int& i,int& j)
{
    int p=i;
    i=j;
    j=p;
}
std::vector<int> MySudokuGenerater::getGrid()
{
    return Grid;
}
int MySudokuGenerater::Print(std::vector<int> grid)
{
    std::cout<<"------------------------------"<<std::endl;
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
        {
            std::cout<<" "<<grid[x*9+y]<<" ";
            if(y%3==2)
                std::cout<<"|";
            if(y==8)
            {
                std::cout<<std::endl;
                if(x%3==2)
                   std::cout<<"------------------------------"<<std::endl;
            }
        }
    return 0;
}
int MySudokuGenerater::SeedGrid()
{
    std::string tem;
    std::ifstream fin;
    int count=1466;
    fin.open("Seed1.txt");
    for(int i=0;i<count;i++)
        std::getline(fin,tem);
    std::cout<<"count="<<count<<std::endl;
    for(int i=0;i<81;i++)
        if(tem[i]!='.')
            Grid[i]=int(tem[i]-'0');
        else
            Grid[i]=0;
    fin.close();
    return 0;
}
void MySudokuGenerater::Import(std::vector<int> newGrid)
{
    if(newGrid.size()==81)
    {
        Grid.clear();
        for(int i=0;i<81;i++)
            Grid.push_back(newGrid[i]);
    }
}
void MySudokuGenerater::SaveSeed(int i)
{
    std::fstream f;
    f.open(std::to_string(i)+".dat",std::ios_base::app);
    for(int i=0;i<81;i++)
        f<<Grid[i]<<" ";
    f.close();
}
