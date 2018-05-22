#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

int mm[1000][1000];

int main(){
    FILE *fp = fopen("data/fakeroad.nedge", "r");
    int n, m;
    fscanf(fp, "%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mm[i][j] = i == j ? 0 : 1000000000;
    for (int i = 0; i < m; ++i){
        int x, y, w;
        fscanf(fp, "%d%d%d", &x, &y, &w);
        if (w < mm[x][y])
            mm[x][y] = mm[y][x] = w;
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i){
            if (k == i) continue;
            for (int j = 0; j < n; ++j){
                if (j == k || j == i) continue;
                mm[i][j] = min(mm[i][j], mm[i][k] + mm[k][j]);
            }
        }
    FILE *fp2 = fopen("data/fakecar.txt", "r");
    int idx, num;
    FILE *op = fopen("data/fakeprocess.ans", "w");
    while (fscanf(fp2, "%d%d", &idx, &num) != EOF){
        double x, y;
        int nid[5];
        for (int k = 0; k < num + 1; ++k)
            fscanf(fp2, "%lf,%lf,%d", &x, &y, &nid[k]);
        fprintf(op, "%d %d", idx, num);
        for (int k = 0; k < num + 1; ++k)
            fprintf(op, " %d", nid[k]);
        for (int k = 0; k < num + 1; ++k)
            for (int l = k + 1; l < num + 1; ++l)
                fprintf(op, " %d", mm[nid[k]][nid[l]]);
        fprintf(op, "\n");
    }
    fclose(op);
}
