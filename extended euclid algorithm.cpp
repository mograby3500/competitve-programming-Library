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
ll mod_inv(ll a, ll mod){
    int b = mod;
    int c = 1;
    ll x0, y0, d = gcd(a, b, x0, y0);
    if(d != 1) return -1;
    x0 %= mod;
    while(x0 < 0) x0 += mod;
    cout<<x0<<" ";
    return x0;
}
