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

void Paint::paint_map(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y]){
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);

    for(int j = 0; j < MAP_Y; j++){
    for(int i = 0; i < MAP_X; i++){
        
        img = cv::Mat::zeros(500, 500, CV_8UC3);

        // 描画
        for(int y = 0; y < MAP_Y; y++){
            for(int x = 0; x < MAP_X; x++){
                // 地点
                int point_x = SIZE*x;
                int point_y = SIZE*y;
            
                // マップの表示
                cv::rectangle(img, cv::Point(point_x+1,point_y+1), cv::Point(SIZE-1 + point_x, SIZE-1+point_y),
                cv::Scalar(300-(xy[x][y]*COLOR),300-(xy[x][y]*COLOR),300-(xy[x][y]*COLOR)), -1, CV_AA);
            
                // 通った地点の表示
                if(p[x][y] == 1){
                    cv::circle(img,cv::Point(25+point_x , 25+point_y), 5, cv::Scalar(200,0,0), -1, CV_AA);
                }
            
            }
        }
     
        cv::circle(img, cv::Point(25+50*i, 25+50*j), 20, cv::Scalar(0,0,200), 3, 4);
        sleep(1);
        cv::imshow("drawing", img);
        }
    }
    cv::imshow("drawing", img);
    cv::waitKey(0);
}

void Paint::paint_map2(double xy[MAP_X][MAP_Y],double p[MAP_X][MAP_Y],double color[MAP_X][MAP_Y],int x[MAX_POINT], int y[MAX_POINT], int num){
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
    
 
        for(int i = 0; i < num; i++){
            
            img = cv::Mat::zeros(500, 500, CV_8UC3);
            
            // 描画
            for(int y = 0; y < MAP_Y; y++){
                for(int x = 0; x < MAP_X; x++){
                    // 地点
                    int point_x = SIZE*x;
                    int point_y = SIZE*y;
                    
                    int red = 1;
                    int green = 1;
                    int blue = 1;
                    
                    switch ((int)color[x][y]) {
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
                                  cv::Scalar(300-((xy[x][y]+1)*COLOR*red),300-((xy[x][y]+1)*COLOR*green),300-((xy[x][y]+1)*COLOR)*blue), -1, CV_AA);
                    
                    // 通った地点の表示
                    if(p[x][y] == 1){
                        cv::circle(img,cv::Point(25+point_x , 25+point_y), 5, cv::Scalar(200,0,0), -1, CV_AA);
                    }
                    
                    
                    
                }
            }
            
            sleep(1);
            cv::circle(img, cv::Point(25+50*x[i], 25+50*y[i]), 20, cv::Scalar(0,0,200), 3, 4);
            Event e;
            if(e.event((int)color[x[i]][y[i]])){
                std::cout<< "WALK!!!!!\n";
            } else {
                std::cout<< "GAME OVER!!!!!\n";
                break;
            }
            

            cv::imshow("drawing", img);
       }
    std::cout<< "CREAR!!!!!\n";
    cv::imshow("drawing", img);
    cv::waitKey(0);
}

