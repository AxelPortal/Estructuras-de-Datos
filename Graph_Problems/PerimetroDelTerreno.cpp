//
// Created by axelr on 20/10/2026.
//

#include "iostream"
#include "vector"


using namespace std;



int main() {
    int n,m;
    cin>>n>>m;
    vector<string> mat(n);
    for(int i=0;i<n;i++) {
        cin>>mat[i];
    }

    vector<int> grados(5,0);

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if (mat[i][j]=='#') {
                int up=i-1;
                int down=i+1;
                int left=j-1;
                int right=j+1;

                int total=0;

                if (up!=-1) {
                    if (mat[up][j]=='#') {
                        total++;
                    }
                }
                if (down!=n) {
                    if (mat[down][j]=='#') {
                        total++;
                    }
                }
                if (left!=-1) {
                    if (mat[i][left]=='#') {
                        total++;
                    }
                }

                if (right!=m) {
                    if (mat[i][right]=='#') {
                        total++;
                    }
                }
                grados[total]++;
            }
        }
    }

    int p=0;
    for(int i=0;i<grados.size();i++) {
        p=p+(4-i)*grados[i];

    }

    cout<<p<<" ";
    for(int i=0;i<grados.size();i++) {
        cout<<grados[i]<<" ";
    }

    return 0;
}