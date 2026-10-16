//
// Created by axelr on 13/10/2026.
//

#include<bits/stdc++.h>
using namespace::std;

bool esHeapValido(vector<int> &a) {
    int n=a.size();
    for (int i=0;i<=(n-2)/2;i++) {
        int izq=2*i+1;
        int der=2*i+2;
        if (izq<n&&a[i]>a[izq]) {
            return false;
        }
        if (der<n&&a[i]>a[der]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0;i<n;i++) {
            cin >> a[i];
        }

        if (esHeapValido(a))
            cout<<"SI"<<endl;
        else
            cout<<"NO"<<endl;

    }

    return 0;
}