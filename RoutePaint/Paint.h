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


//#define MAP_X 10
//#define MAP_Y 10
#define MAP_X 16
#define MAP_Y 16

#define SIZE 40
#define COLOR 80

#define MAX_POINT 16*16
struct data3{
    data3(float x_,float y_,float data_):x(x_),y(y_),data(data_){}
    float x;
    float y;
    float data;
};

using namespace std;

class Paint{
    
public:
    
    static void paint_map(cv::Mat img,vector<data3> xy,vector<data3> color,vector<data3> p);
    static void move(cv::Mat img,vector<data3> xy,vector<data3> color,vector<data3> p);
};


#endif
