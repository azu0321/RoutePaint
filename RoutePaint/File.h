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
    
    static vector<data3> file_read(string fileName);
    static void file_write(string fileName, data3 *data);
};

#endif
