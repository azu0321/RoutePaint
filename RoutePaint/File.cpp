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

vector<data3> File::file_read2(string fileName){
    
    ifstream dataFile(fileName);
    int a;
    //vector<data3> world_data;
    vector<data3> data;
    for (int row = 0; row < MAP_Y; row++)
        
    {
        
        for(int col = 0; col < MAP_X;col++){
            dataFile >> a;
            data.push_back(data3(col,row,a));
            
            
        }
    }
    
    dataFile.close();
    
    return data;
}

void File::file_write2(string fileName, data3 *data){
    
    ofstream dataFile;
    dataFile.open(fileName);
    
    
    for (int row = 0; row < MAP_Y; row++)
    {
        for(int col = 0; col < MAP_X;col++){
            dataFile << &data[MAP_X*row+col] << " ";
            
        }
        dataFile << "\n";
    }
    dataFile.close();
}

