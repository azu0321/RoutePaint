//
//  main.cpp
//  RouteSearch
//
//  Created by / on 2014/11/19.
//  Copyright (c) 2014年 mitukuni. All rights reserved.
//

#include <iostream>

#include "boostGraph.h"
#include "Types.h"
#include "File.h"
#include "glPaint.h"
#include "Map.h"
//#include "Paint.h"
typedef rge::ints Route; // rge::ints = vector<int> = Route

int main(int argc, const char * argv[]) {
    
   
    //Types.hをincludeすることでrge::とついているクラスを利用できます
    //float2などの~2は xとyの2つの値を持っている構造体 座標などに利用しましょう。(~3だとzも入ってきます)
    //講義中にも言っていた+、-も使えるようにオーバーロードされています。
    //intsなどの複数形になっているものはvectorのようにtypedefされています。
    
    std::string Datafile = "/Users/e125733/Desktop/IV/sampledata.txt";
    SimpleGraph sg;
    sg.makeDataGraph(Datafile);
    
    RouteSearcher rs;//ダイクストラで経路探索を行なうクラス
    rs.makeGraph(sg.getEdges(), sg.getWeight(), MAP_X*MAP_Y);
    
    Route route; //最短経路を入れるためのベクター
    int from=0;
    int to=MAP_X*MAP_Y-1;
    

    vector<data3> point;
    
    rs.shortestPath(from); //現在地を引数にわたし、ダイクストラを実行
    rs.getRouteTo(to,&route); //routeに結果が返る
    
    File fi2;
    std::string Datafile3 = "/Users/e125733/Desktop/IV/sampledata6.txt";
    vector<data3> color = fi2.file_read(Datafile3);
     //結果の表示
     
    
    cout<<"Route is ";
    for(auto &r : route){ //routeの配列を先頭から順番にrという変数にいれてループする
        
        int y = (int)r/MAP_X;
        int x = (int)r%MAP_X;
        
        
        for(auto n:color){
            if(n.x == x && n.y == y){
                point.push_back(data3(x,y,n.data));
                break;
            }
        }
        
        
        cout<< r << ", p[" << x <<"][" << y << "] " <<"->";
        
    }
    
    //目的地までのコスト
    double distance = rs.getDistanceTo(to);
    cout<<"\nRoute cost is "<<distance<<endl;
   

    std::string Datafile2 = "/Users/e125733/Desktop/IV/sampledata.txt";
    File fi;
    vector<data3> a = fi.file_read(Datafile2);

    Paint pt;
    cv::Mat img = cv::Mat::zeros(640, 640, CV_8UC3);
    //pt.paint_map(img,a,color,point);
    pt.move(img,a,color,point);
    cv::imshow("drawing", img);
    cv::waitKey(0);
    
    glPaint gl;
    void (*pFunc)() = &glPaint::display;
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc,const_cast<char**>(argv));

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("paint");
    
    // ここの時間を求める。
    glutDisplayFunc(pFunc);
    gl.Init();
    
    glutMainLoop();

    
    
    return 0;
}
