//
// Created by axelr on 13/10/2026.
//

#include<bits/stdc++.h>
using namespace::std;

template<typename data_type>
struct Heap {
    int _size;
    vector<data_type> a;

    Heap(int _size = 0) : _size(_size) {
        a = vector<data_type>();
    }

    Heap(vector<data_type> a, int &cont) : a(move(a)), _size(a.size()) {
        build_heap(cont);
    }

    int left(int p) {
        return (p << 1) | 1; // 2 * p + 1
    }

    int right(int p) {
        return (p << 1) + 2; // 2 * p + 2
    }

    int parent(int p) {
        return (p - 1) >> 1; // floor((p - 1) / 2)
    }

    void sift_down(int p, int &cont) {
        while (left(p) < _size) {
            int m = p;
            int l = left(p), r = right(p);
            if (a[l] < a[m]) {
                m = l;
            }
            if (r < _size and a[r] < a[m]) {
                m = r;
            }
            if (m == p) break;
            swap(a[p], a[m]);
            cont++;

            p = m;
        }
    }

    void sift_up(int u) {
        while (u > 0 and a[parent(u)] > a[u]) {
            swap(a[parent(u)], a[u]);
            u = parent(u);
        }
    }

    void build_heap(int &cont) {
        for (int i = parent(_size - 1); i >= 0; --i) {
            sift_down(i,cont);
        }
    }

    data_type top() const {
        return a[0];
    }

    void pop() {
        swap(a[0], a[_size - 1]);
        a.pop_back();
        --_size;
        sift_down(0);
    }

    data_type extract_min() {
        data_type min = a[0];
        pop();
        return min;
    }

    void insert(data_type value) {
        a.emplace_back(value);
        ++_size;
        sift_up(_size - 1);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        cin >> a[i];
    }
    int cont=0;
    Heap<int> heap(a,cont);

    cout<<cont<<"\n";
    for (auto &iter : heap.a) {
        cout<<iter<<" ";
    }

    return 0;
}