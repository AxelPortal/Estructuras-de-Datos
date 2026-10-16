//
// Created by axelr on 13/10/2026.
//

#include <iostream>

using namespace std;

void hanoi(int n, int origen, int destino, int apoyo) {
    if (n==1) {
        cout<<n<<" "<<origen<<" "<<destino<<endl;
        return;
    }

    hanoi(n-1, origen, apoyo, destino);
    cout<<n<<" "<<origen<<" "<<destino<<endl;
    hanoi(n-1, apoyo, destino, origen);



}

int main () {
    int x;
    cin>>x;
    hanoi(x, 1, 3, 2);


    return 0;
}