#include "map.hpp"
#include "grid.h"
#include "cell.h"

using namespace std;

Map::Map() {
    xTiles=28;
    yTiles=33;
    cellDim=20;
    dot=0;
    powerdot=0;
}

void Map::init() {
    
    srand( static_cast<unsigned int>(time(nullptr)));

    std::vector<int> v;
    Grid g = Grid();
    std::vector<int> m = g.generateMaze();
 
    // 0 - EMPTY
    // 1 - WALL
    // 2 - PACMAN GATE
    // 3 - GHOST GATE
    // 4 - PACMAN
    // 5 - GHOST
    // 6 - D0T
    // 7 - POWER DOT
    
    for(int i=0; i<28; i++){
        for(int j=0; j<33; j++){
            maze[i][j] = m[33*i+j];
            
            if(maze[i][j]==6) {
                dot++;
            }
            else if(maze[i][j]==7) {
                powerdot++;
            }
            else if(maze[i][j]==4) {
                PMspawn.first = i;
                //std::cout<<i<<" ";
                PMspawn.second = j;
               // std::cout<<j<<" ";
                PMpos = PMspawn;
            }
            else if(maze[i][j]==5) {
                Gspawn.first = i;
                Gspawn.second = j;
            }
            else if(maze[i][j]==2) {
                Pgatepos.first = i;
                Pgatepos.second = j;
            }
            else if(maze[i][j]==3) {
                Ggatepos.first = i;
                Ggatepos.second = j;
            }
        }
    }
    
    
}

std::pair<int,int> Map::getPMspawn() {
    return PMspawn;
}
std::pair<int,int> Map::getGspawn() {
    return Gspawn;
}
std::pair<int,int> Map::getPMpos() {
    return PMpos;
}
std::pair<int,int> Map::getGpos() {
    return Gpos;
}
std::pair<int,int> Map::getPgatepos() {
    return Pgatepos;
}
std::pair<int,int> Map::getGgatepos() {
    return Ggatepos;
}

void Map::updatePMpos(std::pair<int,int> p) {
    PMpos.first = p.first;
    PMpos.second = p.second;
}

