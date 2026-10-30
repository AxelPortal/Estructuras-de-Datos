//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int BFS01(vector<string> &G, int n, int m, int sx, int sy, int ex,int ey) {
    vector<vector<int>> dist(n,vector<int> (m,-1));
    dist[sx][sy]=0;
    queue<pair<int,int>> Q;
    Q.push(make_pair(sx,sy));

    vector<int> dx={0,0,1,-1};
    vector<int> dy={1,-1,0,0};

    while (not Q.empty()) {
        int ux, uy;
        tie(ux,uy)=Q.front();
        Q.pop();

        for (int k=0; k<4; k++) {

            int vx=ux+dx[k];
            int vy=uy+dy[k];
            if (vx<0 or vy<0 or vx>=n or vy >= m) continue;
            int weight;
            if (G[vx][vy]=='#') weight = 1;
            else weight = 0;
            if (dist[vx][vy]>dist[ux][uy]+weight or dist[vx][vy]==-1) {
                dist[vx][vy]=dist[ux][uy]+weight;
                Q.push(make_pair(vx,vy));
            }

        }

    }

    return dist[ex][ey];


}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<string> grid(n);
    for (int i=0; i<n; i++) {
        cin>>grid[i];
    }

    cout<<BFS01(grid,n,m,0,0,n-1,m-1)<<"\n";

    return 0;
}