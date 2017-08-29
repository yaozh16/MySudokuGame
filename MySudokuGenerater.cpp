#include "MySudokuGenerater.h"
int MySudokuGenerater::Init()
{
    Grid=new int[81];
    for(int i=0;i<81;i++)
        Grid[i]=0;

    Grid[0*9+3]=8;
    Grid[0*9+5]=1;
    Grid[1*9+7]=4;
    Grid[1*9+8]=3;
    Grid[2*9+0]=5;
    Grid[3*9+4]=7;
    Grid[3*9+6]=8;
    Grid[4*9+6]=1;
    Grid[5*9+1]=2;
    Grid[5*9+4]=3;
    Grid[6*9+0]=6;
    Grid[6*9+7]=7;
    Grid[6*9+8]=5;
    Grid[7*9+2]=3;
    Grid[7*9+3]=4;
    Grid[8*9+3]=2;
    Grid[8*9+6]=6;
    srand(time(NULL));
    //SeedGrid();
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
    int i=rand()%9;
    int j=i;
    while(j==i){j=rand()%9;}
    for(int y=0;y<9;y++)
        swap(Grid[i+9*y],Grid[j+9*y]);
    return 0;
}
int MySudokuGenerater::rowSwap()
{
    int i=rand()%9;
    int j=i;
    while(j==i){j=rand()%9;}
    for(int y=0;y<9;y++)
        swap(Grid[y+9*i],Grid[y+9*j]);
    return 0;
}
int MySudokuGenerater::NumberReplace()
{
    int count=rand()%10+10;
    int a[10];
    for(int i=0;i<10;i++)
        a[i]=i;
    for(int i=0;i<count;i++)
    {
        int x=rand()%9+1;
        int y=rand()%9+1;
        while(y==x){y=rand()%9+1;}
        swap(a[x],a[y]);
    }
    int *newGrid=new int[81];
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
            if(Grid[x+9*y]==0)
                newGrid[x+9*y]=0;
            else
                newGrid[x+9*y]=a[Grid[x+9*y]];
    delete Grid;
    Grid=newGrid;
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
    //NumberReplace();
    return 0;
}
int MySudokuGenerater::swap(int& i,int& j)
{
    int p=i;
    i=j;
    j=p;
    return 0;
}
int* MySudokuGenerater::getGrid()
{
    return Grid;
}
int MySudokuGenerater::Print()
{
#ifdef My_Debug
    std::cout<<"------------------------------"<<std::endl;
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
        {
            std::cout<<" "<<Grid[x*9+y]<<" ";
            if(y%3==2)
                std::cout<<"|";
            if(y==8)
            {
                std::cout<<std::endl;
                if(x%3==2)
                   std::cout<<"------------------------------"<<std::endl;
            }
        }
#endif
    return 0;
}
int MySudokuGenerater::SeedGrid()
{
    int newGrid[81]={1,2,7,4,9,3,0,0,5,
                     0,0,0,0,1,0,0,0,0,
                     0,0,0,0,8,6,3,0,0,
                     6,5,3,7,0,0,0,9,8,
                     2,0,0,0,0,0,5,0,0,
                     0,7,0,0,4,5,1,2,6,
                     3,6,2,8,0,0,7,1,9,
                     4,8,9,1,7,2,6,0,3,
                     0,1,5,0,3,9,0,8,4};
    for(int i=0;i<81;i++)
        Grid[i]=newGrid[i];
    return 0;
}
