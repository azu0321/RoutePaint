//
//  main.cpp
//  RouteSearch
//
//  Created by mitukuni on 2014/11/19.
//  Copyright (c) 2014年 mitukuni. All rights reserved.
//

#include <iostream>
#include "boostGraph.h"
#include "Types.h"
#include "File.h"
//#include "Paint.h"

//乱数を生成する関数
namespace {
    float frand(float from, float to){
        
        return from + ((float)rand()*(to-from)/(RAND_MAX));
    }
    
    float frand(float f){
        return frand(0,f);
    }
}


//ノードの座標を格納するクラス
class Node{
public:
    Node(){}
    Node(float x, float y):position_(x,y){}
    rge::float2 getPosition(){
        return position_;
    }
    float length(){return sqrt(position_.x*position_.x+position_.y*position_.y);}
    
private:
    rge::float2 position_;
};

//ノード同士の結合とその重みを格納するクラス
class Edge{
public:
    Edge(){}
    Edge(int first,int second): edge_(first,second){}
    
    void setWeight(double w){ weight_ = w; }
    pair<int, int> getEdge(){return edge_;}
    double getWeight(){return weight_;}
    
private:
    pair<int, int> edge_;
    double weight_;
};

typedef vector<Node> Nodes;
typedef vector<Edge> Edges;

//簡単なグラフをつくるクラス
class SimpleGraph{
public:
    SimpleGraph(){}
    
    //num_node分のノードをランダムに生成し、順番に繋いだだけのグラフを作る
    void makeRandomGraph(int num_node){
        nodes_.resize(num_node);
        for(auto &n : nodes_){
            n=Node(frand(50),frand(50));
        }
        for(int i=1; i<num_node;i++){
            edges_.push_back(Edge(i,i-1));
            edges_.back().setWeight((nodes_[i].getPosition()-nodes_[i-1].getPosition()).length());
        }
    }
    
    // fileからデータを取得してグラフを作る。
    void makeDataGraph(string filename){
        

        File f;
        vector<data3> xy = f.file_read(filename);
        
        for(int y = 0; y < MAP_Y; y++){
            for(int x = 0; x < MAP_X; x++){
                int point = y*MAP_X + x;
                
                float wight;
                // 自分の右側と接続
                if(point+1 < (y+1)*MAP_X){
                    wight=abs(xy[point].data-xy[point+1].data)+1;
                    edges_.push_back(Edge(point,point+1));
                    edges_.back().setWeight(wight);
                    
                }
                
                // 自分の下と接続
                if(point+MAP_X < MAP_X*MAP_Y){
                    wight=abs(xy[point].data-xy[point+MAP_X].data)+1;
                    edges_.push_back(Edge(point,point+MAP_X));
                    edges_.back().setWeight(wight);
                }
                
                
                // 自分左下と接続
                if(point < (y+1)*MAP_X-1 && point-MAP_X+1 > 0){
                    wight=1.6*(abs(xy[point].data - xy[point-MAP_X+1].data)+1);
                    edges_.push_back(Edge(point,point-MAP_X+1));
                    edges_.back().setWeight(wight);
                }
                
                // 自分の左上と接続
                if(point-MAP_X-1 >= 0 && point != y*MAP_X){
                    wight=1.6*(abs(xy[point].data-xy[point-MAP_X-1].data)+1);
                    edges_.push_back(Edge(point,point-MAP_X-1));
                    edges_.back().setWeight(wight);
                }
            }
        }

     }
    
    
    //Edge classのままでは RouteSearcherに入れられないので、vector<pair<int,int>>に変換して返す。
    vector<pair<int, int>> getEdges(){
        vector<pair<int, int>> vp_edges;
        for (auto &e: edges_) {
            vp_edges.push_back(e.getEdge());
        }
        return vp_edges;
    }
    
    //上と同様にvector<double>にして返す
    vector<double> getWeight(){
        rge::doubles weights;
        for (auto &e: edges_) {
            weights.push_back(e.getWeight());
        }
        return weights;
    }
    
    //指定した番号のNodeを返す
    Node getNode(int i){
        return nodes_[i];
    }
    
private:
    Nodes nodes_;
    Edges edges_;
    
};

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
    std::string Datafile3 = "/Users/e125733/Desktop/IV/sampledata4.txt";
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
    cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
    //pt.paint_map3(img,a,color,point);
    pt.move(img,a,color,point);
    cv::imshow("drawing", img);
    cv::waitKey(0);
    
    return 0;
    
}
