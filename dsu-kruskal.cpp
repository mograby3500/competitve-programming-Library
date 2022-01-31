struct UnionFind{
     vector<int> sz, parent;
     int forests;
     
     UnionFind(int n){
          sz = vector<int> (n);
          parent = vector<int> (n);
          forests = n;
          
          for(int i = 0; i < n; i++){
               sz[i] = 1, parent[i] = i;
          }
     }
     int find_set(int x){
          if(x == parent[x]) return x;
          return parent[x] = find_set(parent[x]);
     }
     void link(int x, int y){
          if(sz[x] > sz[y]) swap(x, y);
          
          parent[x] = y;
          sz[y] += sz[x];
     }
     bool union_sets(int x, int y){
          x = find_set(x);
          y = find_set(y);
          
          if(x != y){
               link(x, y);
               forests--;
          }
          return x != y;
     }
};
struct edge{
    int from, to, w;
    edge(int from, int to, int w):from(from), to(to), w(w){}

    bool operator < (const edge & e) const {
        return w > e.w;
    }
};

ll kruskal(vector<edge> edgeList, int n){
    UnionFind uf(n);
    vector<edge> edges;
    ll mstCost = 0;
    priority_queue<edge> pq;
    for(int i = 0; i < edgeList.size(); i++)
        pq.push(edgeList[i]);
    while(!pq.empty()){
        edge e = pq.top();
        pq.pop();
        if(uf.union_sets(e.from, e.to)){
            mstCost += e.w;
            edges.push_back(e);
        }
    }
    return mstCost;
}
