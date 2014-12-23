//
//  Paint.cpp
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/02.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#include "Paint.h"
#include "Event.h"
#include <unistd.h>

using namespace std;


void Paint::paint_map(cv::Mat img,vector<data3> xy,vector<data3> color,vector<data3> p){
    
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    
    
    // 描画
    for(int y = 0; y < MAP_Y; y++){
        for(int x = 0; x < MAP_X; x++){
            
            
            int point = y*MAP_X+x;
            // 地点
            int point_x = SIZE*(xy[point].x);
            int point_y = SIZE*xy[point].y;
            
            
            int red = 1;
            int green = 1;
            int blue = 1;
            
            switch ((int)color[point].data) {
                case 0 :
                    // 緑
                    green= 0;
                    break;
                case 1 :
                    // 青
                    blue = 0;
                    break;
                case 2 :
                    // 赤
                    red = 0;
                    break;
                case 3 :
                    // 紫
                    red = blue = 0.5;
                    break;
                default: red = green = blue = 0;
                    
                    
            }
            
            
            // マップの表示
            cv::rectangle(img, cv::Point(point_x+1,point_y+1), cv::Point(SIZE-1 + point_x, SIZE-1+point_y),
                          cv::Scalar(300-(xy[point].data*COLOR*red),300-(xy[point].data*COLOR*green),(300-xy[point].data*COLOR*blue)), -1, CV_AA);
            
            
            
        }
    }
    
    // 通った地点の表示
    for (auto n: p) {
        cv::circle(img,cv::Point(25+(n.x*SIZE) , 25+(n.y*SIZE)), 5, cv::Scalar(200,0,0), -1, CV_AA);
    }
    
}

void Paint::move(cv::Mat img,vector<data3> xy,vector<data3> color,vector<data3> p){
    bool flag=true;
    
    double pre_x = 0;
    double pre_y = 0;
    
    for (auto n: p) {
        
        if(n.x == 0 && n.y == 0){
            pre_x = n.x;
            pre_y = n.y;
            
        } else {
            
            for(int i = 0; i < 50; i++){
                int x = i*(n.x - pre_x);
                int y = i*(n.y - pre_y);
                img = cv::Mat::zeros(500, 500, CV_8UC3);
                paint_map(img,xy,color,p);
                cv::circle(img, cv::Point(25+50*pre_x+x, 25+50*pre_y+y), 20, cv::Scalar(0,0,200), 3, 4);
                cv::imshow("drawing", img);
                sleep(0.1);
            }
            
            Event e;
            if(e.event(n.data)){
                flag = true;
                std::cout<< "WALK!!!!!\n";
            } else {
                flag = false;
                break;
            }
            

            
            pre_x = n.x;
            pre_y = n.y;
        }
    }
    
    if(flag){
        std::cout<< "CLEAR!!!!!\n";
    } else {
        std::cout<< "GAME OVER!!!!!\n";
    }
    
}

