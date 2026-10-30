//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;

    vector<string> mat(n);

    for (int i=0;i<n;i++) {
        cin>>mat[i];
    }

    int sum_deg=0;
    int aislados=0;
    int callejon=0;
    int vertices=0;
    vector<int> dx={0,0,1,-1};
    vector<int> dy={1,-1,0,0};
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            int deg=0;
            if (mat[i][j]!='#') {
                vertices++;
                for (int k=0;k<4;k++) {
                    int x=i+dx[k];
                    int y=j+dy[k];
                    if (x<0 || x>n-1 || y<0 || y>m-1) continue;
                    if (mat[x][y]!='#')
                        deg++;
                }
                sum_deg+=deg;
                if (deg==1) callejon++;
                else if (deg==0) aislados++;
            }
        }
    }
    int aristas=sum_deg/2;
    cout<<vertices<<" "<<aristas<<" "<<aislados<<" "<<callejon<<'\n';

    return 0;
}
