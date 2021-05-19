#ifndef DOTS_H
#define DOTS_H


#include <iostream>
#include <stdlib.h>
#include <vector>


std::vector<int> populate(std::vector<int> maze, int rows, int cols);
int eatDot(std::vector<int> &dots, int row, int col);

#endif
