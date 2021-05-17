#ifndef GRID_H
#define GRID_H

#include <stack>
#include <vector>
#include "cell.h"

class Grid {
 private:
  int width;
  int height;

  std::vector<Cell> cells;
  std::stack<Cell *> backtrace;
  Cell *current;

  void createCells();
  int calculateIndex(int i, int j);
  std::vector<Cell *> getAvailableNeighbors();
  std::vector<Cell *> getClosedNeighbors();
  Cell *findNextCell();
  Cell *findCandidate();
  bool areClosed(Cell *a, Cell *b);
  void removeDeadEnds();
  std::vector<int> addThickness();

 public:
  Grid();
  std::vector<int> generateMaze();
};

#endif
