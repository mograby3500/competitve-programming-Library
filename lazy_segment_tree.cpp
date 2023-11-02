#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node{
         int mx;
};

struct seg_tree{
         vector<node> tree;
         vector<int> lazy;
         int sz = 1;
         void init(int n){
                  while(sz < n) sz *= 2;
                  tree.resize(2 * sz, {0});
                  lazy.resize(2 * sz, 0);
         }
         node single(int v){
                  return {v};
         }
         node merge(node &a, node &b){
                  return {max(a.mx, b.mx)};
         }
         node neutral(){
                  return {0};
         }
         void propagate(int x, int lx, int rx){
                  if(!lazy[x]) return;
                  tree[x].mx += lazy[x];
                  if(lx + 1 != rx){
                           lazy[2 * x + 1] += lazy[x];
                           lazy[2 * x + 2] += lazy[x];
                  }
                  lazy[x]= 0;
         }

         int best(){
                  return tree[0].mx;
         }

         void update(int l, int r, int val, int x, int lx, int rx){
                  propagate(x, lx, rx);
                  if(l >= rx || lx >= r) return;
                  if(l <= lx && rx <= r){
                           lazy[x] += val;
                           propagate(x, lx, rx);
                           return;
                  }
                  int m = (lx + rx) >> 1;
                  update(l, r, val, 2 * x + 1, lx, m);
                  update(l, r, val, 2 * x + 2, m, rx);
                  tree[x]= merge(tree[2 * x + 1], tree[2 * x + 2]);
         }
         void update(int l, int r, int v){
                  update(l, r, v, 0, 0, sz);
         }
         node query(int l, int r, int x, int lx, int rx){
                  propagate(x, lx, rx);
                  if(l >= rx || lx >= r) return neutral();
                  if(lx >= l && rx <= r){
                           return tree[x];
                  }
                  int m = (lx + rx) >> 1;
                  node s1 = query(l, r, 2 * x + 1, lx, m);
                  node s2 = query(l, r, 2 * x + 2, m, rx);
                  return merge(s1, s2);
         }
         node query(int l, int r){
                  return query(l, r, 0, 0, sz);
         }
};


seg_tree st;
const int N = 2e5 + 10;
int n, d, alpha;
vector<pair<int, int>> vp;

void add(int idx){
         int ri = vp[idx].second;
         st.update(max(0LL, ri - d), ri + 1, 1);
}
void remove(int idx){
         int ri = vp[idx].second;
         st.update(max(0LL, ri - d), ri + 1, -1);
}
int32_t main() {
         cin.tie(0);
         cout.sync_with_stdio(0);

         long double alpha_d;
         cin>>n>>d>>alpha_d;
         alpha = round(100 * alpha_d);
         for(int i = 0; i < n; i++){
                  int ri;
                  long double a;
                  cin>>ri>>a;
                  vp.push_back({round(100 * a), ri});
         }
         sort(vp.begin(), vp.end());
         for(int i = 0; i < n; i++){
                  vp.push_back({vp[i].first + 36000, vp[i].second});
         }

         int ans=  0;
         st.init(N);
         int p = 0;
         for(int i = 0; i < n; i++){
                  while(p < vp.size() && vp[p].first - vp[i].first <= alpha){
                           add(p);
                           p++;
                  }
                  ans= max(ans, st.query(0, N).mx);
                  remove(i);
         }
         cout<<ans<<"\n";
}
