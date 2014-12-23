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
    
    //            cv::circle(img, cv::Point(25+50*i, 25+50*j), 20, cv::Scalar(0,0,200), 3, 4);
    //            sleep(0.5);
    //            cv::imshow("drawing", img);
    //        }
    //    }

}

void Paint::move(cv::Mat img,vector<data3> xy,vector<data3> color,vector<data3> p){
    bool flag=true;
    for (auto n: p) {
        img = cv::Mat::zeros(500, 500, CV_8UC3);
        paint_map(img,xy,color,p);
        
        cv::circle(img, cv::Point(25+50*n.x, 25+50*n.y), 20, cv::Scalar(0,0,200), 3, 4);
        Event e;
        if(e.event(n.data)){
            flag = true;
            std::cout<< "WALK!!!!!\n";
        } else {
            flag = false;
            break;
        }
        sleep(1);
        cv::imshow("drawing", img);
    }
    
    if(flag){
        std::cout<< "CLEAR!!!!!\n";
    } else {
        std::cout<< "GAME OVER!!!!!\n";
    }
    
}

