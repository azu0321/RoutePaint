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
                          cv::Scalar(300-((xy[point].data+1)*COLOR*red),300-((xy[point].data+1)*COLOR*green),300-((xy[point].data+1)*COLOR*blue)), -1, CV_AA);
            
            
            
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
    int angle = 0;
    for (auto n: p) {
        
        if(n.x == 0 && n.y == 0){
            pre_x = n.x;
            pre_y = n.y;
            
        } else {

            for(int i = 0; i < 50; i++){
                int x =(n.x - pre_x);
                int y =(n.y - pre_y);
                img = cv::Mat::zeros(500, 500, CV_8UC3);
                paint_map(img,xy,color,p);

                if(x == 0){
                    if(y == 0){
                        angle = angle;
                    } else if(y < 0){
                        angle = 270;
                    } else{
                        angle = 90;
                        
                    }
                    
                } else if (x < 0) {
                    if(y == 0){
                        angle = 180;
                    } else if(y < 0){
                        angle = 225;
                    } else{
                        angle = 135;
                    }
                } else {
                    if(y == 0){
                        angle = 0;
                    } else if(y < 0){
                        angle = 315;
                    } else{
                        angle = 45;
                        
                    }

                    
                }
                cv::ellipse(img, cv::Point(25+50*pre_x+x*i, 25+50*pre_y+y*i), cv::Size(20, 20), angle, 15, 345, cv::Scalar(0,0,200), -1, CV_AA);
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

