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
struct data3{
    data3(float x_,float y_,float data_):x(x_),y(y_),data(data_){}
    float x;
    float y;
    float data;
};

using namespace std;
class Paint{
    
public:
    static void paint_map(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y]);
    static void paint_map2(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y],double color[MAP_X][MAP_Y],int x[MAX_POINT], int y[MAX_POINT], int num);
    
    static void paint_map3(vector<data3> xy,vector<data3> p);
    static void move(vector<data3> xy,vector<data3> p);
};


#endif
