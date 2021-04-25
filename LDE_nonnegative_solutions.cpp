#include <bits/stdc++.h>
using  namespace  std;
typedef  long long ll;

ll gcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return  a;
    }
    ll x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    ll n;
    while(cin>>n && n){
        ll c1, n1, c2, n2;
        cin>>c1>>n1;
        cin>>c2>>n2;
        ll x, y;
        ll d = gcd(n1, n2, x, y);
        if(n % d != 0){
            cout<<"failed\n";
            continue;
        }
        x *= n / d;
        y *= n / d;
        bool swapd = 0;
        if(x > y && n1 != n2){
            swapd = 1;
            swap(x, y);
            swap(n1, n2);
            swap(c1, c2);
        }
        ll mn = -1;
        ll mx = -1;
        ll L = 0, R = LLONG_MAX / (n2 / d);
        while(L <= R){
            ll mid = (L + R) / 2;
            if(x + mid * (n2 / d) >= 0){
                mn = mid;
                R = mid - 1;
            }else
                L = mid + 1;
        }
        L = 0, R = LLONG_MAX / (n1 / d);
        while(L <= R){
            ll mid = (L + R) / 2;
            if(y >= mid * (n1 / d)){
                mx = mid;
                L = mid + 1;
            }else
                R = mid - 1;
        }
        if(mx < mn){
            cout<<"failed\n";
            continue;
        }
        ll cost_ans = LLONG_MAX;
        ll x_ans, y_ans;
        vector<ll> v = {mn, mx};
        for(ll k : v){
            ll x1 = x + k * (n2 / d);
            ll y1 = y - k * (n1 / d);
            ll cost = x1 * c1 + y1 * c2;

            assert(cost > 0);
            if(cost < cost_ans){
                x_ans = x1;
                y_ans = y1;
                cost_ans = cost;
            }
        }
        if(swapd) swap(x_ans, y_ans);
        cout<<x_ans<<" "<<y_ans<<"\n";
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
