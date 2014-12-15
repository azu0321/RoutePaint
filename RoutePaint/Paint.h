//
//  Paint.h
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/02.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#ifndef RoutePaint_Paint_h
#define RoutePaint_Paint_h
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define MAP_X 10
#define MAP_Y 10
#define SIZE 50
#define COLOR 80

#define MAX_POINT 100
using namespace std;
class Paint{
    
public:
    static void paint_map(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y]);
    static void paint_map2(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y],double color[MAP_X][MAP_Y],int x[MAX_POINT], int y[MAX_POINT], int num);
};


#endif
