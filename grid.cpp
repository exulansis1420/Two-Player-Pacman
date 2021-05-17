#include "grid.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "cell.h"

std::vector<int> populate(std::vector<int> maze, int rows, int cols, int p, int g)
{
    int pr = p/cols, pc = p%cols, gr = g/cols, gc = g%cols;
    std::vector<int> maze2;
    //all 0 cells need to be given value 6 - small coin or 7 - large coin, except near pens, range of 2
    //Exactly 8 big coins need to be there
    int numLC = 0;
    int cr,cc;
    for(int i=0; i< rows*cols; i++)
    {
        cr = i/cols;
        cc = i%cols;
        if (maze[i]!=0)
            maze2.push_back(maze[i]);
        if (maze[i]==0){
            maze2.push_back(6);
            if ((double) rand()/RAND_MAX < 0.02 && numLC < 8){
                    maze2[i]=7;
                    numLC++;
            }
            if ((((pc-cc)*(pc-cc)<9)&&(pr-cr)*(pr-cr)<16)||(((gc-cc)*(gc-cc)<9)&&(gr-cr)*(gr-cr)<16))
                maze2[i]=0;
        }
    }
    return maze2;
}

int chooseRandom(int dir)
{
    std::vector<int> directions;
    int i=1;
    while(dir>0){
        //std::cout<<dir<<std::endl;
        if (dir%2==1)
        {
            directions.push_back(i);
        }
        i*=2;
        dir/=2;
    }
    return directions.at(rand() % directions.size());
}

std::vector<int> reRemoveDeadEnds(std::vector<int> maze, int rows, int cols, int p, int g)
{
    int num_on,dir,cr,cc;
    for(int i=0; i< rows*cols; i++)
    {
        cc = i%cols;
        cr = i/cols;
        num_on=0;
        dir=0;
        if (maze[i]==0&&cc%2==1&&cr%2==1&&i!=p-cols&&i!=p+cols&&i!=g-cols&&i!=g+cols&&i!=p-2*cols&&i!=p+2*cols&&i!=g-2*cols&&i!=g+2*cols){
            dir+=(maze[i-1]==0)?0:1;
            dir+=(maze[i+1]==0)?0:4;
            dir+=(maze[i-cols]==0)?0:2;
            dir+=(maze[i+cols]==0)?0:8;
            num_on+=(maze[i-1]==0)?1:0;
            num_on+=(maze[i+1]==0)?1:0;
            num_on+=(maze[i-cols]==0)?1:0;
            num_on+=(maze[i+cols]==0)?1:0;
            if(num_on<2)
            {
                dir = chooseRandom(dir);
                //std::cout<<"Choosing: "<<dir<<std::endl;
                switch(dir){
                case 1: maze[i-1]=0;
                        //std::cout<<maze[i-1]<<std::endl;
                        break;
                case 2: maze[i-cols]=0;
                        //std::cout<<maze[i-cols]<<std::endl;
                        break;
                case 4: maze[i+1]=0;
                        //std::cout<<maze[i+1]<<std::endl;
                        break;
                case 8: maze[i+cols]=0;
                        //std::cout<<maze[i+cols]<<std::endl;
                        break;
            }
            }
        }
    }
    return maze;
}

Grid::Grid() {
  this->width = 15;
  this->height = 13;
  createCells();
  current = &cells[0];
}

void Grid::createCells() {
  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      cells.push_back(Cell(row, column));
    }
  }
}

std::vector<int> Grid::generateMaze() {
  while (true) {
    current->setVisited(true);
    Cell *next = findNextCell();

    if (next != NULL) {
      next->setVisited(true);
      backtrace.push(current);
      current->removeWalls(*next);
      current = next;
    } else if (backtrace.size() > 0) {
      current = backtrace.top();
      backtrace.pop();
    } else if (backtrace.size() == 0) {
      break;
    }
  }
  removeDeadEnds();
  std::vector<int> maze = addThickness();

  int p, g;
  std::vector<int>::iterator it;
  it = std::find (maze.begin(), maze.end(), 4);
  p = it - maze.begin();
  it = std::find (maze.begin(), maze.end(), 5);
  g = it - maze.begin();

  maze = reRemoveDeadEnds(maze,2*height+2,2*width+3,p,g);
  maze = populate(maze, 2*height+2, 2*width+3,p,g);
  return maze;
}

Cell *Grid::findNextCell() {
  std::vector<Cell *> availableNeighbors = getAvailableNeighbors();
  if (availableNeighbors.size() > 0) {
    return availableNeighbors.at(rand() % availableNeighbors.size());
  }

  return NULL;
}

bool Grid::areClosed(Cell *a, Cell *b) {
    int r1, r2, c1, c2, w1, w2;
    r1 = a->getRow();
    r2 = b->getRow();
    c1 = a->getColumn();
    c2 = b->getColumn();
    w1 = a->getWalls();
    w2 = b->getWalls();

    if(r1-r2 == 1)
    {
        return (w1%2==1);
    }
    else if(r2-r1 == 1)
    {
        return (w2%2==1);
    }
    else if(c1-c2 == 1)
    {
        return (w2>=8);
    }
    else if (c2-c1 == 1)
    {
        return (w1>=8);
    }
    else
        return false;
}

std::vector<Cell *> Grid::getAvailableNeighbors() {
  std::vector<Cell *> neighbors;

  int currentRow = current->getRow();
  int currentColumn = current->getColumn();

  int neighborIndexes[4] = {
      calculateIndex(currentRow - 1, currentColumn),
      calculateIndex(currentRow, currentColumn + 1),
      calculateIndex(currentRow + 1, currentColumn),
      calculateIndex(currentRow, currentColumn - 1),
  };

  for (int i : neighborIndexes) {
    if (i != -1 && !cells[i].isVisited()) {
      neighbors.push_back(&cells[i]);
    }
  }

  return neighbors;
}

int Grid::calculateIndex(int row, int column) {
  if (row < 0 || column < 0 || column > width - 1 || row > height - 1)
    return -1;
  else
    return column + row * width;
}

std::vector<int> Grid::addThickness(){
    std::ofstream out;
    out.open("maze.txt");
    //I want to repeat 2 random cols and 1 random row
    int arr[28][33];
    for(int i=0; i<2*height+1; i++){
        for(int j=0; j<2*width+1; j++){
            arr[i][j] = 1;
        }
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            arr[2*i+1][2*j+1] = 0;
            int wall = (&cells[width*i+j])->getWalls();
            if (wall <8)
                arr[2*i+1][2*j+2] = 0;
            if ((wall != 12) && ((wall<4)||(wall>7)))
                arr[2*i+2][2*j+1] = 0;
        }
    }
    int er, oddr, ec, oc;
    while(true)
    {
        for (int i = 0; i<10; i++)
        {
            er = 2*(rand()%height);
            oddr = 2*(rand()%height)+1;
            ec = 2*(rand()%width);
            oc = 2*(rand()%width)+1;
            arr[er][oc] = 0;
            arr[oddr][ec] = 0;
        }
        int sum=0;
        for(int i=0; i<2*height+1; i++){
            for(int j=0; j<2*width+1; j++){
                sum+=arr[i][j];
            }
        }
        if((double)sum/(double)((2*width+1)*(2*height+1)) <0.42)
            break;
    }
    //rejoin borders
    for(int i=0; i<width*2+1; i++)
        arr[0][i]=1;
    for(int i=0; i<2*height+1; i++)
        arr[i][0]=1;
    //add the two tunnels
    arr[2*(height/3)+1][0] = 0;
    arr[4*(height/3)+1][0] = 0;
    arr[2*(height/3)+1][2*width] = 0;
    arr[4*(height/3)+1][2*width] = 0;
    //Pen generation
    {
        int sr = height-2, sc1 = 2*width/3 - 2, sc2 = 4*width/3;
        arr[sr][sc1] = 1; arr[sr][sc2] = 1;
        arr[sr][sc1+1] = 1; arr[sr][sc2+1] = 1;
        arr[sr][sc1+2] = 1; arr[sr][sc2+2] = 1;
        arr[sr+1][sc1] = 1; arr[sr+1][sc2] = 1;
        arr[sr+1][sc1+1] = 0; arr[sr+1][sc2+1] = 0;
        arr[sr+1][sc1+2] = 1; arr[sr+1][sc2+2] = 1;
        arr[sr+2][sc1] = 2; arr[sr+2][sc2] = 1;
        arr[sr+2][sc1+1] = 4; arr[sr+2][sc2+1] = 5;
        arr[sr+2][sc1+2] = 1; arr[sr+2][sc2+2] = 3;
        arr[sr+3][sc1] = 1; arr[sr+3][sc2] = 1;
        arr[sr+3][sc1+1] = 0; arr[sr+3][sc2+1] = 0;
        arr[sr+3][sc1+2] = 1; arr[sr+3][sc2+2] = 1;
        arr[sr+4][sc1] = 1; arr[sr+4][sc2] = 1;
        arr[sr+4][sc1+1] = 1; arr[sr+4][sc2+1] = 1;
        arr[sr+4][sc1+2] = 1; arr[sr+4][sc2+2] = 1;
    }
    //I want to repeat 2 random cols and 1 random row
    //should be of type even,even
    int r,c1,c2;
    r = 2*(rand()%height-2)+2;
    c1 = 2*(rand()%height-2)+2;
    c2 = 2*(rand()%height-2)+2;
    for(int i = 0; i<2*width+1; i++)
    {
        arr[2*height+1][i] = arr[r][i];
        if (arr[2*height+1][i]>1)
            arr[2*height+1][i]=0;
    }
    //bubble up
    for(int i = 2*height+1; i>r;i--)
    {
        for(int j = 0; j<2*width+1; j++)
        {
            std::swap(arr[i][j],arr[i-1][j]) ;
        }
    }
    //create columns
    for(int i = 0; i<2*height+2; i++)
    {
        arr[i][2*width+1] = arr[i][c1];
        arr[i][2*width+2] = arr[i][c2];
        if (arr[i][2*width+1]>1)
            arr[i][2*width+1]=0;
        if (arr[i][2*width+2]>1)
            arr[i][2*width+2]=0;
    }
    if(c2<c1)
    {
        for(int i = 0; i<2*height+2; i++)
        {
            std::swap(arr[i][2*width+1],arr[i][2*width+2]) ;
        }
        std::swap(c2,c1);
    }
    //bubble left
    for(int i = 2*width+1; i>c1;i--)
    {
        for(int j = 0; j<2*height+2; j++)
        {
            std::swap(arr[j][i],arr[j][i-1]) ;
        }
    }
    c2++;
    for(int i = 2*width+2; i>c2;i--)
    {
        for(int j = 0; j<2*height+2; j++)
        {
            std::swap(arr[j][i],arr[j][i-1]) ;
        }
    }
    //print test
    for(int i=0; i<2*height+2; i++){
        for(int j=0; j<width*2+3; j++){
            out<<arr[i][j];
        }
        out<<std::endl;
    }
    std::vector<int> result;
    for(int i=0; i<2*height+2; i++){
        for(int j=0; j<width*2+3; j++){
            result.push_back(arr[i][j]);
        }
    }
    return result;
}


void Grid::removeDeadEnds(){
    for(int i=0; i<width*height; i++)
    {
        current = &cells[i];
        if(current->isDeadEnd()){
            Cell *candidate = findCandidate();
            current->removeWalls(*candidate);
        }
    }
}

Cell *Grid::findCandidate() {
  std::vector<Cell *> closedNeighbors = getClosedNeighbors();
  if (closedNeighbors.size() > 0) {
    return closedNeighbors.at(rand() % closedNeighbors.size());
  }

  return NULL;
}

std::vector<Cell *> Grid::getClosedNeighbors() {
  std::vector<Cell *> neighbors;

  int currentRow = current->getRow();
  int currentColumn = current->getColumn();

  int neighborIndexes[4] = {
      calculateIndex(currentRow - 1, currentColumn),
      calculateIndex(currentRow, currentColumn + 1),
      calculateIndex(currentRow + 1, currentColumn),
      calculateIndex(currentRow, currentColumn - 1),
  };

  for (int i : neighborIndexes) {
    if (i != -1 && areClosed(current, &cells[i])) {
      neighbors.push_back(&cells[i]);
    }
  }

  return neighbors;
}
