//
//  Event.h
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/15.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#ifndef RoutePaint_Event_h
#define RoutePaint_Event_h
#include "Paint.h"
#include "File.h"
using namespace std;
class Event{

    
public:
//    static void
    static void nomal_road();
    static void fire_road();
    static void water_road();
    static void mushroom_road();
    static bool event(int color);
};



#endif
