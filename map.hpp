#pragma once
#include <iostream>
#include <string>

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
    int maze[28][33];
    std::pair<int,int> getPMspawn() ;
    std::pair<int,int> getGspawn() ;
    std::pair<int,int> getPMpos() ;
    std::pair<int,int> getGpos() ;
    std::pair<int,int> getPgatepos();
    std::pair<int,int> getGgatepos() ;
    void updatePMpos(std::pair<int,int> p);
    void init();
    void kill();
};
