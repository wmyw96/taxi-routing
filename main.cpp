//
// Created by gyh15 on 2018/5/21.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include "graph.h"

using namespace std;

#define LIMIT 100000
int main(int argc, char** argv){
    FILE *fp = fopen("data/road.nedge", "r");
    int n, m;
    fscanf(fp, "%d%d", &n, &m);
    graph* g = new graph(n, m);
    for (int i = 0; i < m; ++i){
        int x, y, w;
        fscanf(fp, "%d%d%d", &x, &y, &w);
        g->addbiedge(x, y, w);
    }
    cout << "Load Graph Finished" << endl;
    g->load_cache("data/process.out");
    cout << "Load Cache Finished" << endl;
    int s = atoi(argv[1]), t = atoi(argv[2]);
    g->set_source_target(s, t);
    int tot = 0;
    for (int i = 0; i < g->nitems; ++i) {
        int o_routing[6];
        int m_routing[6];
        if (g->get_dist(s, g->nid[i][0]) < LIMIT) {
            if (g->ntargets[i] == 4)
                continue;
            int d1 = g->calc_min_dist(-1, -1, i, o_routing);
            int d2 = g->get_dist(s, g->nid[i][0]);
            int d3 = g->calc_min_dist(s, t, i, m_routing);
            int d4 = g->get_dist(s, t);
            if (d2 + d3 - d1 < LIMIT && d3 - d4 < LIMIT){
                printf("Taxi %d, d1=%d, d2=%d, d3=%d, d4=%d: ", i, d1, d2, d3, d4);
                printf("cirvent %d (in), %d (wait)\n", d2 + d3 - d1, d3 - d4);
                ++tot;
            }
        }
    }
    printf("Totally %d candidate taxis\n", tot);
}