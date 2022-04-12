struct node{
     int cnt[41];
     node(){
          memset(cnt, 0, sizeof(cnt));
     }
};
 
struct seg_tree{
    vector<node> values;
    int sz = 1;
    void init(int n){
        while(sz < n) sz *= 2;
        values.resize(2 * sz);
    }
    node single(int v){
         node x;
         x.cnt[v] = 1;
         return x;
    }
    node merge(node &a, node &b){
         node x;
         for(int i = 1; i <= 40; i++)
              x.cnt[i] = a.cnt[i] + b.cnt[i];
         
         return x;
    }
    node neutral(){
         return node();
    }
    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int) a.size()){
                values[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    void build(vector<int> &a) {
         build(a, 0, 0, sz);
    }
    void set(int i, int v, int x, int lx, int rx){
         if(rx - lx == 1){
              values[x] = single(v);
              return;
         }
         int m = (lx + rx) >> 1;
         if(i < m)
              set(i, v, 2 * x + 1, lx, m);
         else
              set(i, v, 2 * x + 2, m, rx);
         
         values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    void set(int i, int v){
         set(i, v, 0, 0, sz);
    }
    node calc(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return neutral();
        if(lx >= l && rx <= r){
            return values[x];
        }
        int m = (lx + rx) >> 1;
        node s1 = calc(l, r, 2 * x + 1, lx, m);
        node s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    node calc(int l, int r){
        return calc(l, r, 0, 0, sz);
    }
};
