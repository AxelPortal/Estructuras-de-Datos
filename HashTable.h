//
// Created by axelr on 13/09/2026.
//

#ifndef ESTRUCTURAS_HASHTABLE_H
#define ESTRUCTURAS_HASHTABLE_H

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

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

    int _hash(key_type key) const {
        const int B = 311;
        const int MOD = 1e9 + 7;
        int hash_value = 0;
        while (key > 0) {
            int d = key % 10;
            hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
            key /= 10;
        }
        return hash_value % m;
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
};

#endif //ESTRUCTURAS_HASHTABLE_H