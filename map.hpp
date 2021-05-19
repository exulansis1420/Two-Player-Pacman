#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "mazeimage.h"

class Map{
private:
    int xTiles;
    int yTiles;
    int cellDim;
    std::pair<int,int> PMspawn;
    std::pair<int,int> Gspawn;
    std::pair<int,int> PMpos;
    std::pair<int,int> Gpos;
    std::pair<int,int> Pgatepos;
    std::pair<int,int> Ggatepos;
    int dot;
    int powerdot;
    
    
public:
    Map();
    std::vector<int> dots;
    int maze[25][25];
    int dotmaze[25][25];
    std::vector<int> mvector;
    std::pair<int,int> getPMspawn() ;
    std::pair<int,int> getGspawn() ;
    std::pair<int,int> getPMpos() ;
    std::pair<int,int> getGpos() ;
    void updatePMpos(std::pair<int,int> p);
    void updateGpos(std::pair<int,int> p);
    void init();
    void kill();
};
