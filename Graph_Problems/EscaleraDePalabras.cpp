//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>

using namespace std;

bool verificar(string &s1, string &s2, int L) {
    int dif=0;
    for (int i=0; i<L; i++) {
        if (s1[i] != s2[i]) {
            dif++;
            if (dif>1) return false;
        }
    }
    return dif==1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,L;
    cin>>n>>L;
    vector<string> palabras(n);
    for (int i=0; i<n; i++) {
        cin>>palabras[i];
    }

    vector<int> grados(n,0);
    for (int i=0; i<n; i++) {
        for (int j=i+1;j<n;j++) {
            if (verificar(palabras[i], palabras[j], L)) {
                grados[i]++;
                grados[j]++;
            }
        }
    }

    int mayor=grados[0];
    int aislados=0;
    int aristas=0;

    for (auto &it: grados) {
        aristas+=it;
        mayor=max(it,mayor);
        if (it==0) aislados++;
    }

    cout<<aristas/2<<" "<<mayor<<" "<<aislados<<"\n";


    return 0;
}