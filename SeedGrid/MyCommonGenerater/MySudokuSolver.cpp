#include "MySudokuSolver.h"
#include <set>
#include <fstream>
int MySudokuSolver::Init()
{
    clueNumber=0;
    filledGrid.clear();
    Grid.clear();
    for(int i=0;i<81;i++)
        Grid.push_back(0);
    RecordArray.clear();
    RecordRow.clear();
    RecordBox.clear();
    numGrid.clear();
    numRecordRow.clear();
    numRecordArray.clear();
    numRecordBox.clear();
    for(int i=0;i<9;i++)
    {
        RecordArray.push_back(9);
        RecordRow.push_back(9);
        RecordBox.push_back(9);
        std::vector<bool> tnum;
        for(int j=0;j<81;j++)
            tnum.push_back(false);
        numGrid.push_back(tnum);
    }
    std::vector<int> t;
    for(int j=0;j<9;j++)
        t.push_back(9);
    for(int i=0;i<9;i++)
    {

        numRecordRow.push_back(t);
        numRecordArray.push_back(t);
        numRecordBox.push_back(t);
    }
}
int MySudokuSolver::importGrid(std::vector<int> Grid_)
{
    Init();
    for(int y=0;y<9;y++)
        for(int x=0;x<9;x++)
        {
            int index=x+y*9;
            if(Grid_[index]>0)
                SetGrid(x+1,y+1,Grid_[index]);
        }
    return 0;
}
int  MySudokuSolver::isSafe(int x,int y,int v)
{
    if(numGrid[v-1][x+y*9-10])//该位置是否可以放东西
    {
        return 6;
    }
    return 0;
}

int MySudokuSolver::SetGrid(int x,int y,int v)
{
    clueNumber+=1;
    if(fillNumber>0)
        fillNumber-=1;
    ChangeFlag=true;
    v-=1;

    int Box_index=GetBoxIndex(x,y);

    for(int j=0;j<9;j++)//同一位置别的数字(行、列、box)
    {
        if(j!=v)
        {
            if(isSafe(x,y,j+1)==0)
            {

                numRecordRow[j][y-1]-=1;//颜色j的第y行
                numRecordArray[j][x-1]-=1;
                numRecordBox[j][Box_index]-=1;
            }
            numGrid[j][x+y*9-10]=true;
        }
    }
    for(int i=0;i<9;i++)//同行中让同数字的取消可能性
    {
        if(isSafe(i+1,y,v+1)==0)
        {

            numRecordArray[v][i]-=1;
            numRecordRow[v][y-1]-=1;
            numRecordBox[v][GetBoxIndex(i+1,y)]-=1;
        }
        numGrid[v][i+y*9-9]=true;
    }
    for(int i=0;i<9;i++)//同列不同行中让同数字的取消可能性
    {
        if(i+1!=y)
        {
            if(isSafe(x,i+1,v+1)==0)
            {

                numRecordRow[v][i]-=1;
                numRecordArray[v][x-1]-=1;
                numRecordBox[v][GetBoxIndex(x,i+1)]-=1;
            }
            numGrid[v][x-1+i*9]=true;
        }
    }
    int temx,temy;
    GetBoxOffset(temx,temy,Box_index);
    temx-=2;
    temy-=2;
    for(int px=0;px<3;px++)//同一box中不同行列的同数字
    {
        temy+=1;
        for(int py=0;py<3;py++)
        {
            temx+=1;
            if(temx+1!=x&&temy+1!=y)
            {
                if(isSafe(temx+1,temy+1,v+1)==0)
                {
                    numRecordRow[v][temy]-=1;
                    numRecordArray[v][temx]-=1;
                    numRecordBox[v][Box_index]-=1;
                }
                numGrid[v][temx+temy*9]=true;
            }
        }
        temx-=3;
    }
    RecordArray[x-1]-=1;
    RecordRow[y-1]-=1;
    RecordBox[Box_index]-=1;
    Grid[x+y*9-10]=v+1;
    numGrid[v][x+y*9-10]=true;

}
int MySudokuSolver::SearchRows()
{
    for(int i=0;i<9;i++)
    {
        if(RecordRow[i]==1)
        {
            if(SearchRow(i,-1)!=0)
                return 1;
        }
        for(int v=0;v<9;v++)
        {
            if(numRecordRow[v][i]==1)
            {
                if(SearchRow(i,v+1)!=0)
                    return 2;
            }
        }
    }
    return 0;
}
int MySudokuSolver::SearchRow(int r,int v)
{
    if(v<0)
    {
        short index=0;
        std::set<int> s;
        for(int i=1;i<10;i++)
            s.insert(i);
        for(int i=0;i<9;i++)
        {
            if(Grid[r*9+i]>0)
                s.erase(Grid[r*9+i]);
            else
                index=i+1;
        }
        if(s.size()!=1)
        {
            return 1;
        }
        if (isSafe(index,r+1,*(s.begin()))==0)
            SetGrid(index,r+1,*(s.begin()));
        else
            return 1;
    }
    else
    {
        int count=0;
        int index;
        for(short i=0;i<9;i++)
            if(isSafe(i+1,r+1,v)==0)
            {
                index=i+1;
                count+=1;
            }
        if(count!=1)
        {
            return 2;
        }
        SetGrid(index,r+1,v);
    }
    return 0;
}
int MySudokuSolver::SearchArrays(){
    for(int i=0;i<9;i++)
    {
        if(RecordArray[i]==1)
        {
            if(SearchArray(i,-1)!=0)
                return 1;
        }
        for(int v=0;v<9;v++)
            if(numRecordArray[v][i]==1)
            {
                if(SearchArray(i,v+1)!=0)
                    return 2;
            }
    }
    return 0;
}
int MySudokuSolver::SearchArray(int a,int v)
{
    if(v<0)
    {
        short index=0;
        std::set<int> s;
        for(short i=1;i<10;i++)
            s.insert(i);
        for(short i=0;i<9;i++)
        {
            if(Grid[a+i*9]>0)
                s.erase(Grid[a+i*9]);
            else
                index=i+1;
        }
        if(s.size()!=1)
        {
            return 1;
        }
        if(isSafe(a+1,index,*(s.begin()))==0)
            SetGrid(a+1,index,*(s.begin()));
        else
            return 1;
    }
    else
    {
        int  count=0;
        int index;
        for(short i=0;i<9;i++)
            if(isSafe(a+1,i+1,v)==0)
            {
                count+=1;
                index=i+1;
            }
        if(count==1)
            SetGrid(a+1,index,v);
        else
        {
            return 2;
        }
    }
    return 0;
}
int MySudokuSolver::SearchBoxes()
{
    for(int i=0;i<9;i++)
    {
        if(RecordBox[i]==1)
        {
            if(SearchBox(i,-1))
                return 1;
        }
        for(int v=0;v<9;v++)
            if(numRecordBox[v][i]==1)
            {
                if(SearchBox(i+1,v+1))
                    return 2;
            }
    }
    return 0;
}
int MySudokuSolver::SearchBox(int b,int v)
{
    if(v<0)
    {
        short index=0;
        std::set<int> s;
        //例如第(3)4号3x3格子，起始点为(1,4)，实际下标为(0,3)=27
        //例如第(6)7号3x3格子，起始点为(1,7)，实际下标为(0,6)=54
        //例如第(7)8号3x3格子，起始点为(4,7)，实际下标为(3,6)=57
        int BoxOffsetIndex=b/3*3*9+b%3*3;
        for(short i=1;i<10;i++)
            s.insert(i);
        for(short i=0;i<9;i++)
        {
            int temIndex=BoxOffsetIndex+i/3*9+i%3;
            if(Grid[temIndex]>0)
                s.erase(Grid[temIndex]);
            else
                index=temIndex;
        }
        if(isSafe(index%9+1,index/9+1,*(s.begin()))==0)
            SetGrid(index%9+1,index/9+1,*(s.begin()));
        else
            return 1;
    }
    else
    {
        int temx=(b-1)%3*3;
        int temy=(b-1)/3*3;
        int indexX,indexY;
        int count=0;
        for(int x=0;x<3;x++)
        {
            temx+=1;
            for(int y=0;y<3;y++)
            {
                temy+=1;
                if(isSafe(temx,temy,v)==0)
                    {
                        count+=1;
                        indexX=temx;
                        indexY=temy;
                    }

            }
            temy-=3;
        }
        if(count==1)
            SetGrid(indexX,indexY,v);
        else
        {
#ifdef My_Debug
            return 2;
#endif
        }
    }
    return 0;
}
int MySudokuSolver::Search()
{
    //发生setGrid的时候就会为true
    ChangeFlag=true;
    while(ChangeFlag==true)
    {
        ChangeFlag=false;
        if(SearchRows())
            return 1;
        if(SearchBoxes())
            return 2;
        if(SearchArrays())
            return 3;
    }
    return 0;
}
int MySudokuSolver::GuessWithSearch(int xStart,int yStart)
{
    //边界判断
    if(xStart==10)
    {
        xStart=1;
        yStart++;
    }
    if(yStart==10)
    {
        if(Check(Grid)==0)
        {
            FinalGrids.push_back(Grid);
            FinalGuessCounts.push_back(GuessCount);
        }
    }
    //填充判断
    else if(Grid[xStart-1+(yStart-1)*9]>0)
    {
        GuessWithSearch(xStart+1,yStart);
    }
    else
    {
        GuessCount+=1;
        for(int i=1;i<10;i++)
        {
            //尝试--安全
            if(isSafe(xStart,yStart,i)==0)
            {
                //保存
                ParaState state;
                state.Save(this);
                //设置
                SetGrid(xStart,yStart,i);
                //逻辑计算完善地图
                int ret=Search();
                if (ret==0);
                    GuessWithSearch(xStart+1,yStart);
                //退回该步时恢复
                state.Load(this);
            }
        }
        GuessCount-=1;
    }
    return 0;
}
//在已经Import之后才能调用
std::vector<int> MySudokuSolver::setClue(int number)
{
    filledGrid.clear();

    if(Grid.size()!=81)
    {
        for(int i=0;i<81;i++)
            filledGrid.push_back(0);
        return filledGrid;
    }


    //计算
    SolveWithSearch();
    if(FinalGrids.size()<1)
    {
        for(int i=0;i<81;i++)
            filledGrid.push_back(0);
        return filledGrid;
    }
    filledGrid=Grid;
    number-=ClueNumber(Grid);
    if(number<0)
        return filledGrid;

    std::vector<int> pFinal=*(FinalGrids.begin());
    while (number>0)
    {
        int x=rand()%9;
        int y=rand()%9;
        if(filledGrid[x+y*9]==0)
        {
            filledGrid[x+y*9]=pFinal[x+y*9];
            number-=1;
        }
    }
    return filledGrid;
}

int MySudokuSolver::SolveWithSearch()
{
    FinalGrids.clear();
    FinalGuessCounts.clear();
    GuessCount=0;
    GuessWithSearch(1,1);
    return FinalGrids.size();
}
int MySudokuSolver::ClueNumber(std::vector<int> Grid)
{
    if(Grid.size()==81)
    {
        int count=0;
        for(int i=0;i<81;i++)
                if(Grid[i]>0)
                    count++;
        return count;
    }
    return -1;
}
int MySudokuSolver::GetBoxIndex(int stdx,int stdy)
{
    //(3,4)-4-3
    //(9,2)-3-2
    //(7,8)-9-8
    return (stdx-1)/3+(stdy-1)/3*3;
}
int MySudokuSolver::GetBoxOffset(int &stdx,int &stdy,int index)
{
    //0-(1,1)
    //2-(7,1)
    //7-(4,7)
    stdx=index%3*3+1;
    stdy=index/3*3+1;
}
int MySudokuSolver::Check(std::vector<int> Grid)
{

    for(int i=0;i<9;i++)
    {
        std::set<int> s;
        for(int i=1;i<10;i++)
            s.insert(i);
        for(int j=0;j<9;j++)
            s.erase(Grid[i*9+j]);
        if(s.size()>0)
            return 1;
    }
    for(int i=0;i<9;i++)
    {
        std::set<int> s;
        for(int i=1;i<10;i++)
            s.insert(i);
        for(int j=0;j<9;j++)
            s.erase(Grid[i+j*9]);
        if(s.size()>0)
            return 2;
    }
    for(int i=0;i<9;i++)
    {
        std::set<int> s;
        for(int i=1;i<10;i++)
            s.insert(i);
        int x,y;
        GetBoxOffset(x,y,i);
        for(int j=0;j<3;j++)
            for(int k=0;k<9;k++)
            s.erase(Grid[x+k-1+(j+y-1)*9]);
        if(s.size()>0)
            return 3;
    }
    return 0;
}
