//
//  File.cpp
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/02.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#include "File.h"
void File::file_read(string fileName, double data[MAP_X][MAP_Y]){
    
    ifstream dataFile(fileName);
    
    for (int row = 0; row < MAP_Y; row++)
        
    {
        
        for(int col = 0; col < MAP_X;col++){
            dataFile >> data[col][row];
            
        }
    }
    
    dataFile.close();
}

void File::file_write(string fileName, double data[MAP_X][MAP_Y]){
    
    ofstream dataFile;
    dataFile.open(fileName);
    
    
    for (int row = 0; row < MAP_Y; row++)
    {
        for(int col = 0; col < MAP_X;col++){
            dataFile << data[col][row] << " ";
            
        }
        dataFile << "\n";
    }
     dataFile.close();
}
