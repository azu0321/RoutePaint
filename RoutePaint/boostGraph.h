//
//  boostGraph.h
//  clustering_sample
//
//  Created by akaminelab on 2013/12/18.
//  Copyright (c) 2013年 赤嶺 研究室. All rights reserved.
//

#ifndef __clustering_sample__boostGraph__
#define __clustering_sample__boostGraph__

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
//#include <boost/graph/astar_search.hpp>



using namespace std;
using namespace boost;

class RouteSearcher{
    typedef vector<int> ints;
    typedef pair<int, int> Edge;
    typedef vector<Edge> Edges;
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, double> > BoostGraph;
    typedef graph_traits<BoostGraph>::vertex_descriptor Vertex;
    typedef vector<Vertex> Vertices;
    typedef vector<double> Distances;
    typedef vector<int> Route;
public:
    RouteSearcher():origin_(-1){}
    ~RouteSearcher(){}
    
    void makeGraph(vector< pair<int, int> > edges, Distances ds, size_t node_num){
        graph_ = BoostGraph(edges.begin(),edges.end(), ds.begin(), node_num);
    }
    
    void setOrigin(int o){
        origin_ = o;
    }
    
    void setDistances(Distances &ds){
        distances_ = ds;
    }
    
    void shortestPath(int origin, vector<Vertex> &parents, vector<double> &edge_weights){
        if(origin_ == origin){
            return;
        }
        
        parents.resize(num_vertices(graph_));
        edge_weights.resize(num_vertices(graph_));
        
        Vertex s = vertex(origin, graph_);
        typename property_map<BoostGraph, edge_weight_t>::type weightmap = get(edge_weight, graph_);
        typename property_map<BoostGraph, vertex_index_t>::type indexmap = get(vertex_index,graph_);
        
        try{
            dijkstra_shortest_paths(graph_, s, &parents[0], &edge_weights[0], weightmap, indexmap,
                                    std::less<double>(), closed_plus<double>(),
                                    std::numeric_limits<double>::max(), 0,
                                    default_dijkstra_visitor());
        } catch (negative_edge& e) {
            printf("Negative edge in dijkstra shortest path\n");
            parents.clear();
            return;
        }
        
        origin_ = origin;
        
    }
    
    void shortestPath(int origin){
        shortestPath(origin, parents_, distances_);
    }
    
    void getRouteTo(int to, const Vertices& parentsToSrc, Route *r){
        int cur_node = to;
        r->clear();
        
        while(cur_node != (int)parentsToSrc[cur_node]){
            r->push_back(cur_node);
            cur_node = (id_t)parentsToSrc[cur_node];
        }
    }
    
    void getRouteTo(int to, Route *r){
        
        if(origin_ == to) r->push_back(to);
        
        if(isReachable(to) && origin_ != to){
            getRouteTo(to,parents_, r);
            r->push_back(origin_);
            if(r->size() > 0){
                reverse(r->begin(),r->end());
            }
        }
    }
    
    double getDistanceTo(int to){
        return distances_[to];
    }
    
    vector<double> getDistances(){
        return distances_;
    }
    
    
    bool isReachable(int to){ return distances_[to] != numeric_limits<double>::max(); }
private:
    int origin_;
    BoostGraph graph_;
    
    
    Vertices parents_;
    Distances distances_;
};

#endif /* defined(__clustering_sample__boostGraph__) */
