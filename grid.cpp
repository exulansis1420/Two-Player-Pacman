#include "grid.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include "cell.h"

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

void Grid::generateMaze() {
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
  addThickness();
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

void Grid::addThickness(){
    std::ofstream out;
    out.open("maze.txt");
    int arr[27][31];
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
    //print test
    for(int i=0; i<2*height+1; i++){
        for(int j=0; j<width*2+1; j++){
            /*if(i==1&&(j==1||j==width*2-1)){
                std::cout<<"G ";
            }
            else if(i==height*2-1&&(j==1||j==width*2-1)){
                std::cout<<"G ";
            }
            else if(i==(height+1-(height%2))&&(j==2*(width/3)+1||j==4*(width/3)+1)){
                std::cout<<"P ";
            }
            else*/
            if(arr[i][j]==0)
                out<<"  ";
            else out<<"O ";
        }
        out<<std::endl;
    }
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
