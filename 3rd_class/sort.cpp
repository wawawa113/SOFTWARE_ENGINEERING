#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <thread>
#include <map>
#include <random>
#include <string>
#include <queue>
#include <iostream>
#include <atomic>
#include <mutex>
#include <algorithm>

using namespace std;
using ll = long long;
int main()
{
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<> dis(0, 100000ll);
    vector<ll> v1, v2,v3;
    
    //make test_case
    for (ll i = 0; i < 10; i++)
    {
        ll n = dis(engine);
        v1.push_back(n);
        n = dis(engine);
        v2.push_back(n);
        n=dis(engine);
        v3.push_back(n);
    }

    auto InsertionSort = [](vector<ll> &v)
    {
        for (ll j = 1; j < v.size(); j++)
        {
            ll key = v[j];
            ll i = j - 1;
            for (; i > -1 && v[i] > key; i--)
            {
                v[i + 1] = v[i];
            }
            v[i + 1] = key;
        }
    };
    auto test = v1;
    InsertionSort(v1);
    sort(test.begin(), test.end());
    assert(v1 == test);

    auto Partition_ = [&](vector<ll> &v, ll p, ll r)
    {
        ll x = v[r];
        ll i = p - 1;
        for (ll j = p; j <= r - 1; j++)
        {
            if (v[j] <= x)
            {
                i++;
                swap(v[i], v[j]);
            }
        }
        swap(v[i + 1], v[r]);
        // iから左がx以下で整列されてる。
        return i + 1;
    };

    function<void(vector<ll> &, ll, ll)> QuickSort = [&](vector<ll> &v, ll p, ll r)
    {
        if (p < r)
        {
            ll q = Partition_(v, p, r); // qで分割
            //さいきてきに。
            QuickSort(v, p, q - 1);
            QuickSort(v, q + 1, r);
        }
    };
    test=v2;
    QuickSort(v2,0,v2.size()-1);
    sort(test.begin(),test.end());
    assert(test==v2);

    auto CountSort=[&](vector<ll> &A,vector<ll> &B,ll k){
        vector<ll> C(k);
        for(auto j:A)C[j]++;
        for(int i=1;i<C.size();i++)C[i]+=C[i-1];
        // for(auto i:C)cout<<i<<" ";cout<<endl;
        for(int j=A.size()-1;j>=0;j--){
            B[C[A[j]]-1]=A[j];
            C[A[j]]--;
        }
    };
    test=v3;
    sort(test.begin(),test.end());
    vector<ll> res(v3.size());
    CountSort(v3,res,100000ll);
    v3=res;
    assert(v3==test);
}