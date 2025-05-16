#include <bits/stdc++.h>
using namespace std;

class HashFunction
{
public:
    unsigned int sdbmHash(const char *p,int num_bucket)
    {
        unsigned int hash = 0;
        auto *str = (unsigned char *)p;
        int c{};
        while ((c = *str++))
        {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash%num_bucket;
    }

    // cp-algorithms
    // https://cp-algorithms.com/string/string-hashing.html
    unsigned int count_unique_substrings(string str, unsigned int num_buckets)
    {
        int n = str.size();

        const int p = 31;
        const int m = 1e9 + 9;
        vector<long long> p_pow(n);
        p_pow[0] = 1;
        for (int i = 1; i < n; i++)
            p_pow[i] = (p_pow[i - 1] * p) % m;

        vector<long long> h(n + 1, 0);
        for (int i = 0; i < n; i++)
            h[i + 1] = (h[i] + (str[i] - 'a' + 1) * p_pow[i]) % m;

        int cnt = 0;
        for (int l = 1; l <= n; l++)
        {
            unordered_set<long long> hs;
            for (int i = 0; i <= n - l; i++)
            {
                long long cur_h = (h[i + l] + m - h[i]) % m;
                cur_h = (cur_h * p_pow[n - i - 1]) % m;
                hs.insert(cur_h);
            }
            cnt += hs.size();
        }
        return cnt % num_buckets;
    }

    // https://github.com/alessandromrc/JOAAT/blob/main/src/JOAAT.h
    unsigned int joaat(string str, unsigned int num_buckets)
    {
        unsigned int hash = 0;
        for (char c : str)
        {
            hash += static_cast<unsigned char>(c);
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash % num_buckets;
    }

    // https://theartincode.stanis.me/008-djb2/
    unsigned int djb2(string str, unsigned int num_buckets)
    {

        unsigned int hash = 5381;
        int c;
        for (char c : str)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % num_buckets;
    }
};