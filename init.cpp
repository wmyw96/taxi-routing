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

class graph{
private:
    int n, m, nm, source;
    int* c;
    int* nxt;
    int* g;
    int* weight;
    int* dist;
    int* visited;
    void dijkstra(int s){
        if (s == source)
            return;
        source = s;
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
public:
    graph(int _n, int _m){
        n = _n;
        m = _m;
        c = new int[n];
        g = new int[m * 2];
        nxt = new int[m * 2];
        weight = new int[m * 2];
        visited = new int[n];
        nm = 0;
        dist = new int[n];
        source = -1;
        memset(c, -1, n * sizeof(int));
        memset(dist, -1, n * sizeof(int));
    }
    void addedge(int x, int y, int w){
        g[nm] = y;
        nxt[nm] = c[x];
        weight[nm] = w;
        c[x] = nm;
        nm++;
    }
    void addbiedge(int x, int y, int w){
        addedge(x, y, w);
        addedge(y, x, w);
    }
    int get_dist(int x, int y){
        if (x == source)
            return dist[y];
        if (y == source)
            return dist[x];
        dijkstra(x);
        return dist[y];
    }
};

#define MAXN 1000000
int nid[MAXN][5], ntot[MAXN];
int dist_cache[MAXN][5][5];
vector<int> inv_q[MAXN];

int main(){
    FILE *fp = fopen("data/fakeroad.nedge", "r");
    int n, m;
    fscanf(fp, "%d%d", &n, &m);
    graph* g = new graph(n, m);
    for (int i = 0; i < m; ++i){
        int x, y, w;
        fscanf(fp, "%d%d%d", &x, &y, &w);
        g->addbiedge(x, y, w);
    }
    FILE *fp2 = fopen("data/fakecar.txt", "r");
    int idx, num;
    FILE *op = fopen("data/fakeprocess.out", "w");
    int num_query = 0;
    while (fscanf(fp2, "%d%d", &idx, &num) != EOF){
        double x, y;
        ntot[idx] = num + 1;
        for (int k = 0; k < num + 1; ++k){
            fscanf(fp2, "%lf,%lf,%d", &x, &y, &nid[idx][k]);
            inv_q[nid[idx][k]].push_back(idx * 8 + k);
        }
        num_query = idx + 1;
    }
    for (int i = 0; i < n; ++i){
        for (int k = 0; k < inv_q[i].size(); ++k){
            int idx = inv_q[i][k] / 8;
            int inv_ord = inv_q[i][k] % 8;
            for (int j = inv_ord + 1; j < ntot[idx]; ++j)
                dist_cache[idx][inv_ord][j] = g->get_dist(i, nid[idx][j]);
        }
        if ((i + 1) % 100 == 0){
            printf("have done %d nodes\n", i + 1);
        }
    }
    for (int i = 0; i < num_query; ++i){
        num = ntot[i] - 1;
        fprintf(op, "%d %d", i, num);
        for (int k = 0; k < num + 1; ++k)
            fprintf(op, " %d", nid[i][k]);
        for (int k = 0; k < num + 1; ++k)
            for (int l = k + 1; l < num + 1; ++l)
                fprintf(op, " %d", dist_cache[i][k][l]);
        fprintf(op, "\n");
    }
    fclose(op);
}