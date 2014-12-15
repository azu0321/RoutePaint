//
//  Event.cpp
//  RoutePaint
//
//  Created by Azusa SHIMABUKURO on 2014/12/15.
//  Copyright (c) 2014年 Azusa SHIMABUKURO. All rights reserved.
//

#include "Event.h"

bool Event::event(int color){
    switch (color){
        case 0 :
            nomal_road();
            return(true);

        case 1 :
            fire_road();
            return(false);

        case 2 :
            water_road();
            return(false);

        case 3 :
            mushroom_road();
            return(false);

        default: return(false);
            

    }
    
}

void Event::nomal_road(){

    std::cout<< "nomal_road\n";
}

void Event::fire_road(){
    std::cout<< "fire_road\n";
    
}

void Event::water_road(){
    std::cout<< "water_road\n";
    
}

void Event::mushroom_road(){
    std::cout<< "mushroom_road\n";
}




