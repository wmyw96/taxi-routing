//
// Created by gyh15 on 2018/5/21.
//

#ifndef TAXI_ROUTING_GRAPH_H
#define TAXI_ROUTING_GRAPH_H


class graph{
private:
    // normal variables
    int n, m, nm, source, target;
    int* c;
    int* nxt;
    int* g;
    int* weight;
    int* s_dist;
    int* t_dist;
    int* visited;
    // cache
public:
    int nitems;
    int* ntargets;
    int** nid;
    int** pair_dist;
private:
    void dijkstra(int s, int* dist);
public:
    graph(int _n, int _m);
    void addedge(int x, int y, int w);
    void addbiedge(int x, int y, int w);
    int get_dist(int x, int y);
    int set_source_target(int x, int y);
    void load_cache(const char* file_path);
    int calc_min_dist(int source, int target, int taxi_id, int* routing);
};


#endif //TAXI_ROUTING_GRAPH_H
