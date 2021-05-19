#ifndef CELL_H
#define CELL_H


class Cell {
 private:
  int row, column;
  int walls;
  bool visited;

 public:
  Cell(int i, int j);
  int getWalls();
  Cell *checkNeighbors();
  void print();
  void removeWalls(Cell &);

  void setVisited(bool);
  bool isVisited();

  bool isDeadEnd();

  int getRow();
  int getColumn();
};

#endif


