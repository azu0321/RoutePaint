//
//  File.h
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/02.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#ifndef RoutePaint_File_h
#define RoutePaint_File_h
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Paint.h"

using namespace std;
class File{
    
public:
    
    static void file_read(string fileName, double data[MAP_X][MAP_Y]);
    static void file_write(string fileName, double data[MAP_X][MAP_Y]);
    
    
    static vector<data3> file_read2(string fileName);
    static void file_write2(string fileName, data3 *data);
};

#endif
