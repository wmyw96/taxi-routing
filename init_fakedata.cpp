#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

#define EDGE_RANGE 100

int main(int argc, char** argv){
    freopen("data/fakeroad.nedge", "w", stdout);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    printf("%d %d\n", n, m);
    for (int i = 1; i < n; ++i)
        printf("%d %d %d\n", rand() % i, i, rand() % EDGE_RANGE);
    for (int i = 0; i < m - (n - 1); ++i)
        printf("%d %d %d\n", rand() % n, rand() % n, rand() % EDGE_RANGE);
    freopen("data/fakecar.txt", "w", stdout);
    for (int i = 0; i < k; ++i){
        int v = rand() % 4;
        printf("%d %d", i, v);
        for (int i = 0; i < v + 1; ++i)
            printf(" 0,0,%d", rand() % n);
        printf("\n");
    }
}
