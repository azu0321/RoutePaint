//
//  glPaint.h
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2015/01/13.
//  Copyright (c) 2015年 Azusa SHIMABUKURO. All rights reserved.
//

#ifndef __RoutePaint__glPaint__
#define __RoutePaint__glPaint__

#include <stdio.h>
#include <GLUT/glut.h>
#include "File.h"
class glPaint{
#define WIDTH 400
#define HEIGHT 400
    
    public :

    void DrawQuadrangle(int x,int y, int color){
        double r = 0, g = 0, b = 0;
        
        switch (color) {
            case 0 :
                // 緑
                g = 1;
                break;
            case 1 :
                // 青
                b  = 1;
                break;
            case 2 :
                // 赤
                r = 1;
                break;
            case 3 :
                // 紫
                r = 0.8;
                b = 1.0;
                break;
            default: r = g = b = 0;
                
        }
        
        glBegin(GL_QUADS);
        glColor4f(r, g, b, 1.0f);
        glVertex3f(x , y, 0); // 左上
        glColor4f(r, g, b, 1.0f);
        glVertex3f(x+25 , y, 0); // 右上
        glColor4f(r, g, b, 1.0f);
        glVertex3f(x+25 , y+25, 0);// 右下
        glColor4f(r, g, b, 1.0f);
        glVertex3f(x , y+25, 0); // 左下
        glEnd();
    }
    static void Init(){
        glClearColor(0.3, 0.3, 0.3, 1.0);
        glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    }
    
    static void display(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);
        
        std::string Datafile = "/Users/e125733/Desktop/IV/sampledata5.txt";
        File fi;
        vector<data3> color = fi.file_read(Datafile);
        
        glPaint g;
        for (auto n: color) {
            g.DrawQuadrangle((int)n.x*25,(int)n.y*25,(int)n.data);
        }
        glutSwapBuffers();
    }

};

#endif /* defined(__RoutePaint__glPaint__) */
