#include "map.hpp"
#include "grid.h"
#include "cell.h"
#include "dots.h"
#include<fstream>

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
    mvector = m;
    saveMap(mvector);

    dots = populate(m,21,19);
 
    // 0 - EMPTY
    // 1 - WALL
    // 2 - PACMAN
    // 3 - GHOST
    // 4 - D0T
    // 5 - POWER DOT
    
    for(int i=0; i<21; i++){
        for(int j=0; j<19; j++){
            maze[i][j] = m[19*i+j];
 
        if(maze[i][j]==2) {
                PMspawn.first = i;
                //std::cout<<i<<" ";
                PMspawn.second = j;
               // std::cout<<j<<" ";
                PMpos = PMspawn;
            }
            else if(maze[i][j]==3) {
                Gspawn.first = i;
                Gspawn.second = j;
                Gpos = Gspawn;
            }
           
        }
    }
    
    for(int i=0; i<21; i++){
        for(int j=0; j<19; j++){
            dotmaze[i][j] = dots[19*i+j];
 
            if(dotmaze[i][j]==1) {
                dot++;
            }
            else if(maze[i][j]==2) {
                powerdot++;
            }
            
            cout<<dotmaze[i][j];
           
        }
        
        cout<<endl;
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

void Map::updatePMpos(std::pair<int,int> p) {
    PMpos.first = p.first;
    PMpos.second = p.second;
}

void Map::updateGpos(std::pair<int,int> p) {
    Gpos.first = p.first;
    Gpos.second = p.second;
}
