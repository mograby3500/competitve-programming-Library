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
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    ll a, b, c, x1, x2, y1, y2;
    cin>>a>>b>>c>>x1>>x2>>y1>>y2;
    if(x1 > x2 || y1 > y2) return cout<<"0", 0;
    c=-c;
    if(c < 0){
        c *= -1; a *= -1; b *= -1;
    }
    if(a < 0){
        a *= -1; x1 *= -1; x2 *= -1; swap(x1, x2);
    }
    if(b < 0){
        b *= -1; y1 *= -1; y2 *= -1; swap(y1, y2);
    }
    if(x1 > x2 || y1 > y2) return cout<<"0", 0;
    ll len1 = x2 - x1 + 1;
    ll len2 = y2 - y1 + 1;
    if(!a && !b && !c){
        cout<<len2 * len1;
        return 0;
    }
    if(!a && !b){
        cout<<"0";
        return 0;
    }
    if(!a && b){
        if(c % b != 0) return cout<<"0", 0;
        int sol = -c / b;
        if(sol < y1 || sol > y2) return cout<<"0", 0;
        cout<<len1;
        return 0;
    }
    if(a && !b){
        if(c % a != 0) return cout<<"0", 0;
        int sol = -c / a;
        if(sol < x1 || sol > x2) cout<<"0", 0;
        cout<<len2;
        return 0;
    }
    ll x0, y0, d = gcd(abs(a), abs(b), x0, y0);
    if(c % d != 0) return cout<<"0", 0;
    x0 *= c/d;
    y0 *= c/d;

    ll L1 = ceil((x1 - x0) * 1.0 * d / b);
    ll R1 = floor((x2 - x0) * 1.0 * d / b);

    ll L2 = ceil((y2 - y0) * 1.0 * - d / a);
    ll R2 = floor((y1 - y0) * 1.0 * -d / a);

    ll L = max(L1, L2);
    ll R = min(R1, R2);

    if(L > R) cout<<"0";
    else
        cout<<R - L + 1;

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
