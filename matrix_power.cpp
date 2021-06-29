#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 1e9 + 7;
struct Matrix{
    ll a[3][3];
    int n;
    Matrix(int nn) : n(nn){};
    Matrix operator *(Matrix other){
        Matrix prod(n);
        memset(prod.a, 0, sizeof prod.a);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                {
                    prod.a[i][k] += (a[i][j] * other.a[j][k]) % mod;
                    prod.a[i][k] %= mod;
                }

        return prod;
    }
};
Matrix unity(int n){
    Matrix a(n);
    memset(a.a, 0, sizeof a.a);

    for(int i = 0; i < n; i++)
        a.a[i][i] = 1;

    return a;
}
Matrix power(Matrix a, ll n, int sz){
    Matrix res = unity(sz);
    while(n){
        if(n & 1) res = res * a;
        a = a * a;
        n /= 2;
    }

    return res;
}
ll power(ll a, ll b){
    if(b < 0) return 1;
    ll res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int w, h;
    cin>>w>>h;

    ll a = 1, b = 11, c = 29;

    Matrix co(3);
    co.a[0][0] = 0;
    co.a[0][1] = 0;
    co.a[0][2] = 8;

    co.a[1][0] = 1;
    co.a[1][1] = 0;
    co.a[1][2] = 10;

    co.a[2][0] = 0;
    co.a[2][1] = 1;
    co.a[2][2] = 1;


    Matrix base(3);
    base.a[0][0] = 1;
    base.a[0][1] = 11;
    base.a[0][2] = 29;
    Matrix p = power(co, w - 3, 3);
    Matrix f = base * p;
    ll ans;
    if(w == 1)
        ans = a;
    else if(w == 2)
        ans = b;
    else
        ans = f.a[0][2];

    cout<<power(ans, h);
}
