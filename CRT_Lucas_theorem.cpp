#include <bits/stdc++.h>
using  namespace  std;
typedef  long long ll;


const ll N = 1e6 + 10;
ll a, b, n;
ll mod = 1e9 + 7;
ll p[2] = {2, 500000003};
ll dp[N][2], fac[N][2];
ll factorial(ll n, ll idx){
    return fac[n][idx];
}
ll power(ll a, ll b, ll modd){
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % modd;
        a = a * a % modd;
        b >>= 1;
    }

    return res;
}
ll gcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return  a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
ll mod_inv(ll a, ll modd){
    return power(a, modd - 2, modd);
}
ll nck(ll n, ll k, ll idx){
    if(k > n) return 0;
    if(k == 0) return 1;
    ll top = factorial(n, idx);
    ll bot = 1ll * factorial(k, idx) * factorial(n - k, idx) % p[idx];
    return 1ll * top * mod_inv(bot, p[idx]) % p[idx];
}
ll nckLucas(ll n, ll k, ll idx){
    ll res = 1;
    while(n || k){
        ll ni = n % p[idx];
        ll ki = k % p[idx];

        res = 1ll * res * nck(ni, ki, idx) % p[idx];

        n /= p[idx];
        k /= p[idx];
    }
    return res;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    memset(dp, -1, sizeof dp);


    for(int i = 0; i <= 1; i++){
        fac[0][i] = 1;
        for(int j = 1; j < N; j++)
            fac[j][i] = 1ll * fac[j - 1][i] * j % p[i];
    }
    ll T; cin>>T;
    while(T--){
        cin>>a>>b>>n;
        ll r[2];
        ll mods[2] = {2, 500000003};
        for(ll i = 0; i <= 1; i++){
            r[i] = nckLucas(2 * n, n, i);
            r[i] = power(r[i], b, p[i]);
        }
        if(!b) r[0] = r[1] = 1;

        ll M = mods[0];
        ll R = r[0];
        for(ll i = 1; i <= 1; i++){
            ll a = M, b = mods[i], c = r[i] - R;
            ll q1, q2, d = gcd(a, b, q1, q2);

            assert(c % d == 0);

            q1 *= c / d;
            R += q1 * M;
            M  = (M / __gcd(M, mods[i]) * mods[i];
            R = (R % M + M) % M;
        }
        bool ok = 1;
        for(ll i = 0; i < 2; i++)
            ok &= R % mods[i] == r[i];

        assert(ok);
        cout<<power(a, R, mod)<<"\n";
    }
}
/*
 * Think twice, code once
 * Think of different approaches to tackle a problem: write them down.
 * Think of different views of the problem. don't look from only one side.
 * don't get stuck in one approach.
 * common mistakes: over_flow
 *                  - out_of_bound index
 *                  -infinite loop
 *                  -corner cases
 *                  -duplication counting.
 */
