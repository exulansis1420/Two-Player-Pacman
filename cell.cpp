#include "cell.h"
#include <stdlib.h>
#include <iostream>

const int UP = 1, LEFT = 2, DOWN = 4, RIGHT = 8;

Cell::Cell(int row , int column ) {
  this->row = row;
  this->column = column;
  visited = false;
  walls = 15;
}

void Cell::setVisited(bool b) { visited = b; }
bool Cell::isVisited() { return visited; }
bool Cell::isDeadEnd() { return (walls == 7)||(walls == 11)||(walls==13)||(walls==14); }

int Cell::getRow() { return row; }
int Cell::getColumn() { return column; }
int Cell::getWalls() {return walls;}

void Cell::removeWalls(Cell &next) {
  int x = column - next.column;
  int y = row - next.row;

  if (x == 1) {
    walls -= LEFT;
    next.walls -= RIGHT;
  } else if (x == -1) {
    walls -= RIGHT;
    next.walls -= LEFT;
  } else if (y == 1) {
    walls -= UP;
    next.walls -= DOWN;
  } else if (y == -1) {
    walls -= DOWN;
    next.walls -= UP;
  }
}

void Cell::print() {
  switch(walls){
    case 0: std::cout<<"   ";
            break;
    case 1: std::cout<<"   ";
            break;
    case 2: std::cout<<"|  ";
            break;
    case 3: std::cout<<"|  ";
            break;
    case 4: std::cout<<" _ ";
            break;
    case 5: std::cout<<" _ ";
            break;
    case 6: std::cout<<"|_ ";
            break;
    case 7: std::cout<<"|_ ";
            break;
    case 8: std::cout<<"  |";
            break;
    case 9: std::cout<<"  |";
            break;
    case 10: std::cout<<"| |";
            break;
    case 11: std::cout<<"| |";
            break;
    case 12: std::cout<<" _|";
            break;
    case 13: std::cout<<" _|";
            break;
    case 14: std::cout<<"|_|";
            break;
    case 15: std::cout<<"|_|";
            break;
  }
}



