//
// Created by axelr on 18/09/2026.
//


#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) {
        chains.resize(m);
    }

private:
    // Centraliza la búsqueda en el bucket para no duplicar código
    int _find_index(int chain_pos, const key_type &key) const {
        for (int i = 0; i < (int)chains[chain_pos].size(); ++i) {
            if (chains[chain_pos][i].first == key) {
                return i;
            }
        }
        return -1;
    }

public:
    value_type& operator[](const key_type &key) {
        int chain_pos = _hash(key);
        int at = _find_index(chain_pos, key);

        if (at == -1) {
            chains[chain_pos].emplace_back(key, value_type());
            ++_size;
            return chains[chain_pos].back().second;
        }
        return chains[chain_pos][at].second;
    }

    void erase(const key_type &key) {
        int chain_pos = _hash(key);
        int at = _find_index(chain_pos, key);

        if (at != -1) {
            // Swap & Pop directo en O(1)
            swap(chains[chain_pos][at], chains[chain_pos].back());
            chains[chain_pos].pop_back();
            --_size;
        }
    }

    bool has_key(const key_type &key) const {
        int chain_pos = _hash(key);
        return _find_index(chain_pos, key) != -1;
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void print() const {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ":\n";
            for (const auto &e : chains[i]) {
                cout << "  " << e.first << " --> " << e.second << "\n";
            }
            cout << "End bucket\n";
        }
    }

    value_type get(const key_type &key) const {
        int chain_pos = _hash(key);
        int at = _find_index(chain_pos, key);
        if (at != -1) {
            return chains[chain_pos][at].second;
        }
        return value_type(); // Retorna 0 por defecto
    }

    int _hash(key_type key) const {
        unsigned long long x = key;
        x ^= (x >> 30);
        x *= 0xbf58476d1ce4e5b9ULL;
        x ^= (x >> 27);
        x *= 0x94d049bb133111ebULL;
        x ^= (x >> 31);
        return x % m;
    }

};

int main () {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin>>n;
    my_map<int,int> map(2*n+7);
    vector<int> v;
    for (int i=0;i<n;i++) {
        int x;
        cin>>x;
        map[x]++;
        v.push_back(x);
    }

    for (auto& iter: v) {
        if (map.get(iter)==1) {
            cout<<iter<<"\n";
            return 0;
        }
    }

    cout<<-1;



    return 0;
}


