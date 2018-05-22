//
// Created by gyh15 on 2018/5/21.
//

#include "graph.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

namespace dijkstra_pq{
    priority_queue<pair<int, int> > q;
}

void graph::dijkstra(int s, int* dist){
    memset(dist, -1, n * sizeof(int));
    dist[s] = 0;
    using namespace dijkstra_pq;
    while (!q.empty())
        q.pop();
    q.push(make_pair(0, s));
    memset(visited, 0, n * sizeof(int));
    for (int i = 0; i < n; ++i){
        pair<int, int> current = q.top();
        q.pop();
        int x = current.second;
        if (visited[x]){
            --i;
            continue;
        }
        visited[x] = 1;
        for (int k = c[x]; ~k; k = nxt[k]){
            int y = g[k];
            int w = weight[k];
            if (dist[x] + w < dist[y] || dist[y] == -1){
                dist[y] = dist[x] + w;
                q.push(make_pair(-dist[y], y));
            }
        }
    }
    while (!q.empty()) q.pop();
}

graph::graph(int _n, int _m){
    n = _n;
    m = _m;
    c = new int[n];
    g = new int[m * 2];
    nxt = new int[m * 2];
    weight = new int[m * 2];
    visited = new int[n];
    nm = 0;
    s_dist = new int[n];
    t_dist = new int[n];
    source = -1;
    memset(c, -1, n * sizeof(int));
    memset(s_dist, -1, n * sizeof(int));
    memset(t_dist, -1, n * sizeof(int));
}

void graph::addedge(int x, int y, int w){
    g[nm] = y;
    nxt[nm] = c[x];
    weight[nm] = w;
    c[x] = nm;
    nm++;
}

void graph::addbiedge(int x, int y, int w){
    addedge(x, y, w);
    addedge(y, x, w);
}

int graph::get_dist(int x, int y){
    if (x == source)
        return s_dist[y];
    if (y == source)
        return s_dist[x];
    if (x == target)
        return t_dist[y];
    if (y == target)
        return t_dist[x];
    printf("Error: need to be source %d or target %d, get (%d, %d)",
           source, target, x, y);
    return -1;
}

int graph::set_source_target(int x, int y){
    source = x;
    target = y;
    dijkstra(source, s_dist);
    dijkstra(target, t_dist);
    return 0;
}

void graph::load_cache(const char* file_path){
    FILE *fp = fopen(file_path, "r");

    fscanf(fp, "%d", &nitems);
    nid = new int*[nitems];
    pair_dist = new int*[nitems];
    ntargets = new int[nitems];
    int idx, num;
    while (fscanf(fp, "%d%d", &idx, &num) != EOF){
        double x, y;
        nid[idx] = new int[5];
        ntargets[idx] = num + 1;
        pair_dist[idx] = new int[10];
        for (int k = 0; k < num + 1; ++k)
            fscanf(fp, "%d", &nid[idx][k]);
        for (int k = 0; k < (num + 1) * num / 2; ++k)
            fscanf(fp, "%d", &pair_dist[idx][k]);
    }
    fclose(fp);
}

void search(int cost, int* a, int level, int n, int g[6][6],
            int* vis, int* mapping, int *routing, int &ans){
    if (level == n){
        if (cost < ans){
            ans = cost;
            for (int i = 0; i < n; ++i)
                routing[i] = mapping[a[i]];
        }
    }
    else{
        for (int i = 0; i < n; ++i)
            if (!vis[i]){
                a[level] = i;
                vis[i] = 1;
                search(cost + g[a[level - 1]][i], a, level + 1,
                       n, g, vis, mapping, routing, ans);
                vis[i] = 0;
            }
    }
}

int graph::calc_min_dist(int _source, int _target, int taxi_id, int* routing){
    if (_source == -1 && _target == -1){
        int a[6];
        int mm[6][6];
        int vis[6];
        memset(vis, 0, sizeof vis);
        vis[0] = 1;
        memset(a, 0, sizeof a);
        memset(mm, 0, sizeof mm);
        for (int i = 0, nm = 0; i < ntargets[taxi_id]; ++i)
            for (int j = i + 1; j < ntargets[taxi_id]; ++j)
                mm[i][j] = mm[j][i] = pair_dist[taxi_id][nm++];
        int ans = 1000000000;
        search(0, a, 1, ntargets[taxi_id], mm, vis, nid[taxi_id], routing, ans);
        return ans;
    }
    else
    if (source == _source && target == _target){
        int a[6];
        int mm[6][6];
        int vis[6];
        memset(vis, 0, sizeof vis);
        vis[0] = 1;
        memset(a, 0, sizeof a);
        memset(mm, 0, sizeof mm);
        for (int i = 0, nm = 0; i < ntargets[taxi_id]; ++i)
            for (int j = i + 1; j < ntargets[taxi_id]; ++j)
                mm[i][j] = mm[j][i] = pair_dist[taxi_id][nm++];
        int nts = ntargets[taxi_id];
        for (int j = 1; j < nts; ++j)
            mm[0][j] = mm[j][0] = get_dist(source, nid[taxi_id][j]);
        for (int i = 1; i < nts; ++i)
            mm[i][nts] = mm[nts][i] = get_dist(nid[taxi_id][i], target);
        mm[0][nts] = mm[nts][0] = get_dist(source, target);
        int mapping[6];
        for (int i = 1; i < nts; ++i)
            mapping[i] = nid[taxi_id][i];
        mapping[0] = source;
        mapping[nts] = target;
        nts += 1;
        int ans = 1000000000;
        search(0, a, 1, nts, mm, vis, mapping, routing, ans);
        return ans;
    }
    else printf("Invalid query");
    return -1;
}