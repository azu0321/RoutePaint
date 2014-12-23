//
//  File.cpp
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/02.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#include "File.h"

vector<data3> File::file_read(string fileName){
    
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

void File::file_write(string fileName, data3 *data){
    
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

