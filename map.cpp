#include "map.hpp"
#include "grid.h"
#include "cell.h"
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
 
    // 0 - EMPTY
    // 1 - WALL
    // 2 - PACMAN
    // 3 - GHOST
    // 4 - D0T
    // 5 - POWER DOT
    
    for(int i=0; i<21; i++){
        for(int j=0; j<19; j++){
            maze[i][j] = m[19*i+j];

            if(maze[i][j]==6) {
                dot++;
            }
            else if(maze[i][j]==7) {
                powerdot++;
            }
            else if(maze[i][j]==2) {
                PMspawn.first = i;
                //std::cout<<i<<" ";
                PMspawn.second = j;
               // std::cout<<j<<" ";
                PMpos = PMspawn;
            }
            else if(maze[i][j]==3) {
                Gspawn.first = i;
                Gspawn.second = j;
            }
           
        }
    }
    
//    // Create a text string, which is used to output the text file
//    string myText;
//
//    // Read from the text file
//    std::ifstream MyReadFile("/Users/tanishq/Downloads/maze.txt");
//
//    // Use a while loop together with the getline() function to read the file line by line
//    int j=0;
//    while (getline (MyReadFile, myText)) {
//      // Output the text from the file
//        for(int i=0;i<19;i++) {
//            maze[j][i] = myText[i]-'0';
//            cout<<maze[j][i];
//                        if(maze[j][i]==6) {
//                            dot++;
//                        }
//                        else if(maze[j][i]==7) {
//                            powerdot++;
//                        }
//                        else if(maze[j][i]==2) {
//                            PMspawn.first = j;
//                            //std::cout<<i<<" ";
//                            PMspawn.second = i;
//                            //std::cout<<j<<" ";
//                            PMpos = PMspawn;
//                        }
//                        else if(maze[j][i]==3) {
//                            Gspawn.first = j;
//                            Gspawn.second = i;
//                        }
//
//        }
//        cout<<endl;
//        j++;
//
//    }
//
//    MyReadFile.close();
   
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

