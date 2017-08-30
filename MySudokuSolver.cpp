#include "MySudokuSolver.h"
#include <set>
int MySudokuSolver::Init()
{
    fillNumber=-1;
    if(filledGrid)
        delete filledGrid;
    if(Grid)
        delete Grid;
    Grid=new int[81];
    for(int i=0;i<81;i++)
        Grid[i]=0;
    for(int i=0;i<9;i++)
    {
        RecordArray[i]=9;
        RecordRow[i]=9;
        RecordBox[i]=9;
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            numRecordArray[i][j]=9;
            numRecordBox[i][j]=9;
            numRecordRow[i][j]=9;
        }
}
int MySudokuSolver::importGrid(int* Grid_)
{
    Init();
    for(short y=0;y<9;y++)
        for(short x=0;x<9;x++)
        {
            short index=x+y*9;
            if(Grid_[index]>0)
                SetGrid(x+1,y+1,Grid_[index]);
        }
#ifdef My_Debug
    std::cout<<"--MySudokuSolver:Import puzzle:"<<std::endl;
    Output();
#endif
}
int  MySudokuSolver::isSafe(int x,int y,int v)
{
#ifndef NewApproach
    if(!isRowSafe(x,y,v))
        return 1;
    else if(!isArraySafe(x,y,v))
        return 2;
    else if(!isBoxSafe(x,y,v))
        return 3;
    else
        return 0;
#else
    if(Grid[x-1+(y-1)*9]>0)//该点需要无数字
        return 5;
    if(numRecordArray[v-1][x-1]<=0)//该列需要无同数字
        return 4;
    if(numRecordRow[v-1][y-1]<=0)//该行需要无同数字
        return 4;
    if(numRecordBox[v-1][(x-1)/3+(y-1)/3*3]<=0)//该box无同数字
        return 4;
    if(RecordArray[x-1]>0<=0)//该列可以放
        return 3;
    if(RecordBox[(x-1)/3+(y-1)/3*3]<=0)//该box可以放
        return 3;
    if(RecordRow[y-1]<=0)//该行可以放
        return 3;
    return 0;
#endif
}
int MySudokuSolver::Output(int *Grid_)
{
    if(Grid_==NULL)
        Grid_=Grid;
    int n=ClueNumber(Grid_);
    if(n>0)
        std::cout<<"Clue = "<<n<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
        {
            std::cout<<" "<<Grid_[x*9+y]<<" ";
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
int MySudokuSolver::OutputFillGrid()
{
    if(filledGrid==NULL)
        return 1;
    int n=ClueNumber(filledGrid);
    if(n>0)
        std::cout<<"Clue = "<<n<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
        {
            std::cout<<" "<<filledGrid[x*9+y]<<" ";
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
//设置需要做的numRecord
//同num:行列设置为0
//      交叉行列（如果交叉点原来是安全的则减少1）
//异num:同行同列，该位置原来是safe则减少1
int MySudokuSolver::SetGrid(int x,int y,int v)
{
    if(fillNumber>0)
        fillNumber-=1;
    ChangeFlag=true;
#ifdef MyStepShow
    std::cout<<"("<<x<<","<<y<<")--"<<v<<std::endl;
#endif
    v-=1;
    int Box_index=(x-1)/3+(y-1)/3*3;

    for(int j=0;j<9;j++)//同一位置别的数字
    {
        if(j!=v&&isSafe(x,y,j+1)==0)
        {
            numRecordRow[j][y-1]-=1;//颜色j的第y行
            numRecordArray[j][x-1]-=1;
            numRecordBox[j][Box_index]-=1;
        }
    }
    for(int i=0;i<9;i++)//交叉行列中让同数字的取消可能性
    {

        //(i,y)交叉点在同一行
        if((i+1!=x)&&isSafe(i+1,y,v+1)==0)
            numRecordArray[v][i]-=1;
        //(x,i)交叉点在同一列
        if((i+1!=y)&&isSafe(x,i+1,v+1)==0)
            numRecordRow[v][i]-=1;
    }
    for(int px=0;px<3;px++)//同一box中交叉行列的
        for(int py=0;py<3;py++)
        {
            int temx=Box_index%3*3+px;
            int temy=Box_index/3*3+py;
            if(temx==x-1||temy==y-1)
                continue;
            else
            {
                if(isSafe(temx+1,temy+1,v+1)==0)
                {
                    numRecordRow[v][temy]-=1;
                    numRecordArray[v][temx]-=1;
                }
            }
        }
    for(int i=0;i<9;i++)//交叉行列的box
    {
        //列穿过的box
        if(i/3!=(y-1)/3)
            if(isSafe(x,i+1,v+1)==0)
                numRecordBox[v][i/3*3+(x-1)/3]-=1;
        //行穿过的box
        if(i/3!=(x-1)/3)
            if(isSafe(i+1,y,v+1)==0)
                numRecordBox[v][(y-1)/3*3+i/3]-=1;
    }
    RecordArray[x-1]-=1;
    RecordRow[y-1]-=1;
    RecordBox[Box_index]-=1;
    numRecordArray[v][x-1]=0;//同列置0
    numRecordRow[v][y-1]=0;//同行置0
    numRecordBox[v][Box_index]=0;//同盒子置0
    Grid[x+y*9-10]=v+1;
}
int MySudokuSolver::SearchRows()
{
    for(int i=0;i<9;i++)
    {
        if(RecordRow[i]==1)
        {
            if(SearchRow(i,-1))
                return 1;
        }
        for(int v=0;v<9;v++)
        {
            if(numRecordRow[v][i]==1)
            {
                if(SearchRow(i,v+1))
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
                index=i;
        }
#ifdef My_Debug
        if(s.size()!=1)
        {
            return 1;
        }
#endif
        SetGrid(index+1,r+1,*(s.begin()));
    }
    else
    {
        bool count=true;
        for(short i=0;i<9;i++)
            if(isSafe(i+1,r+1,v)==0)
                if(count)
                {
                    SetGrid(i+1,r+1,v);
                    count=false;
                }
                else
                {
#ifdef My_Debug
                    return 2;
#endif
                }
    }
    return 0;
}
int MySudokuSolver::SearchArrays(){
    for(int i=0;i<9;i++)
    {
        if(RecordArray[i]==1)
        {
            if(SearchArray(i,-1))
                return 1;
        }
        for(int v=0;v<9;v++)
            if(numRecordArray[v][i]==1)
            {
                if(SearchArray(i,v+1))
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
                index=i;
        }
#ifdef My_Debug
        if(s.size()!=1)
        {
            return 1;
        }
#endif
        SetGrid(a+1,index+1,*(s.begin()));
    }
    else
    {
        bool count=true;
        for(short i=0;i<9;i++)
            if(isSafe(a+1,i+1,v)==0)
            {
                if(count)
                {
                    count=false;
                    SetGrid(a+1,i+1,v);
                }
                else
                {
#ifdef My_Debug
                    return 2;
#endif
                }
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
#ifdef My_Debug
        if(s.size()!=1)
        {
            return 1;
        }
#endif
        SetGrid(index%9+1,index/9+1,*(s.begin()));
    }
    else
    {
        int temx=(b-1)%3*3;
        int temy=(b-1)/3*3;
        bool count=true;
        for(int x=0;x<3;x++)
        {
            temx+=1;
            for(int y=0;y<3;y++)
            {
                temy+=1;
                if(isSafe(temx,temy,v)==0)
                    if(count)
                    {
                        count=false;
                        SetGrid(temx,temy,v);
                    }
                    else
                    {
    #ifdef My_Debug
                        return 2;
    #endif
                    }

            }
            temy-=3;
        }
    }
    return 0;
}
int MySudokuSolver::Search()
{
    ChangeFlag=true;
    while(ChangeFlag==true)
    {
        ChangeFlag=false;
        if(SearchRows())
            return 1;

#ifdef MyStepShow
        Output();
        system("pause");
#endif
        if(SearchBoxes())
            return 2;

#ifdef MyStepShow
        Output();
        system("pause");
#endif
        if(SearchArrays())
            return 3;

#ifdef MyStepShow
        Output();
        system("pause");
#endif
    }
    return 0;
}
int MySudokuSolver::GuessWithSearch(int xStart,int yStart)
{
    if(xStart==10)
    {
        xStart=1;
        yStart++;
    }
    if(yStart==10)
    {
        int* tem=new int[81];
        memcpy(tem,Grid,sizeof(int)*81);
        FinalGrids.push_back(tem);
    }

    else if(Grid[xStart-1+(yStart-1)*9]>0)
    {
        GuessWithSearch(xStart+1,yStart);
    }
    else
        for(int i=1;i<10;i++)
        {
            if(isSafe(xStart,yStart,i)==0)
            {
                //保存
                int newGrid[81];
                short temRecordABR[27];
                short temnumRecordABR[81*3];
                memcpy(newGrid,Grid,sizeof(int)*81);
                memcpy(&(temRecordABR[0]),RecordArray,sizeof(short)*9);
                memcpy(&(temRecordABR[9]),RecordBox,sizeof(short)*9);
                memcpy(&(temRecordABR[18]),RecordRow,sizeof(short)*9);
                memcpy(&(temnumRecordABR[0]),numRecordArray,sizeof(short)*81);
                memcpy(&(temnumRecordABR[9]),numRecordBox,sizeof(short)*81);
                memcpy(&(temnumRecordABR[18]),numRecordRow,sizeof(short)*81);

                SetGrid(xStart,yStart,i);
                if(Search()==0);
                {
                    GuessWithSearch(xStart+1,yStart);
                }
                //恢复
                memcpy(Grid,newGrid,sizeof(int)*81);
                memcpy(RecordArray,&(temRecordABR[0]),sizeof(short)*9);
                memcpy(RecordBox,&(temRecordABR[9]),sizeof(short)*9);
                memcpy(RecordRow,&(temRecordABR[18]),sizeof(short)*9);
                memcpy(numRecordArray,&(temnumRecordABR[0]),sizeof(short)*81);
                memcpy(numRecordBox,&(temnumRecordABR[9]),sizeof(short)*81);
                memcpy(numRecordRow,&(temnumRecordABR[18]),sizeof(short)*81);
            }
            else
                continue;
        }
    return 0;
}
int MySudokuSolver::setClue(int number)
{
    if(Grid==NULL)
        return 1;
    int currentclue=ClueNumber(Grid);
    fillNumber=number-currentclue;
    if(fillNumber<0)
        fillNumber=0;
    return 0;
}
int MySudokuSolver::SolveWithSearch()
{
    if(GuessWithSearch(1,1)==1)
    {
#ifdef My_Debug
        std::cout<<"set done"<<std::endl;
        OutputFillGrid();
#endif
    }
    else if(FinalGrids.size()==0)
    {
#ifdef My_Debug
        std::cout<<"no Solution"<<std::endl;
        Output();
#endif
    }
    else if(FinalGrids.size()>0)
    {
#ifdef My_Debug
        std::cout<<"Solution ="<<FinalGrids.size()<<std::endl;
        for(auto iter:FinalGrids)
        {
            Output(&(*(iter)));
        }
#endif
    }
}
int MySudokuSolver::ClueNumber(int *Grid)
{
    if(Grid)
    {
        int count=0;
        for(int i=0;i<81;i++)
            if(Grid[i]!=0)
                count+=1;
        return count;
    }
    return -1;
}
