//
// Created by axelr on 3/11/2026.
//

#include <iostream>
#include <vector>

using namespace std;

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

int DFS (int x,int y, vector<string> &G, vector<vector<bool>> &visitados) {
    visitados[x][y]=true;
    int res=1;
    for (int i=0;i<4;i++) {
        int nx=x+dx[i];
        int ny=y+dy[i];
        if (nx<0 || nx>=G.size() || ny<0 || ny>=G[0].size()) continue;
        if (visitados[nx][ny]) continue;
        if (G[nx][ny]=='.') continue;
        res=res+DFS(nx,ny,G, visitados);
    }

    return res;

}



int main () {
    cin.tie(0)->sync_with_stdio(false);

    int n,m;
    cin>>n>>m;

    vector<string> G(n);

    for (int i=0;i<n;i++) {
        cin>>G[i];
    }

    vector<vector<bool>> visited(n,vector<bool> (m,false));

    int mayor=0;
    int cnt=0;

    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (G[i][j]=='.') continue;
            if (visited[i][j]) continue;
            cnt++;
            int tam=DFS(i,j,G,visited);
            mayor=max(mayor,tam);
        }
    }

    cout<<cnt<<" "<<mayor;




    return 0;

}