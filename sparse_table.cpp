#include <bits/stdc++.h>
using  namespace  std;
typedef  long long ll;
using cd = complex<double>;
const double PI = acos(-1);
#define all(x) x.begin(), x.end()

//you should really read the stuff at the bottom
const int N = 4e5 + 10;
int lg[N];
ll sparse[40][N];
ll query(int l, int r){
     int len = r - l + 1;
     int k = lg[len];
     ll ans = __gcd(sparse[k][l], sparse[k][r - (1 << k) + 1]);
     return ans;
}
void solve(){
     int n; cin>>n;
     ll a[n];
     for(int i = 0; i < n; i++)
          cin>>a[i];
     
     int sz = 1;
     while(sz < n - 1)
          sz *= 2;
     
     vector<ll> v(sz, 0);
     for(int i = 0; i + 1 < n; i++)
          v[i] = (llabs(a[i] - a[i + 1]));
     
     n--;
     for(int i = 0; i < n; i++)
          sparse[0][i] = v[i];
     
     for(int i = 1; i <= lg[sz]; i++){
          for(int j = 0; j + (1 << i) - 1 < n; j++)
               sparse[i][j] = __gcd(sparse[i - 1][j],
                                    sparse[i - 1][j + (1 << (i - 1))]);
     }
     int ans = 0;
     for(int i = 0; i < n; i++){
          int L = i, R = n - 1;
          int pos = -1;
          while(L <= R){
               int mid = (L + R) >> 1;
               if(query(i, mid) > 1)
                    pos = mid, L = mid + 1;
               else
                    R = mid - 1;
          }
          ans= max(ans, pos - i + 1);
     }
     cout<<ans + 1<<"\n";
}
int main(){
     cin.tie(0);
     cin.sync_with_stdio(0);
     //freopen("zeros.in", "r", stdin);
     
     for(int i = 2; i < N; i++)
          lg[i] = lg[i / 2] + 1;
     
     int t; cin>>t;
     while(t--)
          solve();
}
/*
 * don't be lazy in thinking ya 3l2
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
