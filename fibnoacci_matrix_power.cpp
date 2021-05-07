ll mod = 1e9 + 7;
auto multiply(auto a, auto b){
    vector<vector<ll>> prod(2, vector<ll> (2, 0));
    for(int i = 0; i < 2; i++)
        for(int k = 0; k < 2; k++)
            for(int j = 0; j < 2; j++)
            {
                prod[i][k] += a[i][j] * b[j][k];
                prod[i][k] %= mod;
            }
    return prod;
}
vector<vector<ll>> a;
auto solve(ll n){
    vector<vector<ll>> res(2, vector<ll> (2, 0));
    res[0][0] = 1;
    res[1][1] = 1;
    while(n){
        if(n & 1) res = multiply(res, a);
        a = multiply(a, a);
        n /= 2;
    }
    return res;
}
ll fib(ll x, ll y, ll n){
    a = vector<vector<ll>> (2, vector<ll> (2));
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 1;
    a[1][1] = 0;
    a = solve(n - 1);
    vector<vector<ll>> b = vector<vector<ll>>(2, vector<ll>(1));
    b[0][0] = y;
    b[1][0] = x;
    b = multiply(a, b);
    return b[1][0];
}
