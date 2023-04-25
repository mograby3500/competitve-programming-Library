struct SuffixAutomaton{
         vector<map<char, int>> to;
         vector<int> link, len, cnt;
         int last, sz;
         priority_queue<pair<int,int>> pq;
         SuffixAutomaton(int n){
                  to.resize(2 * n + 10);
                  link.resize(2 * n + 10);
                  len.resize(2 * n + 10);
                  cnt.resize(2 * n + 10);
                  last= 0, sz= 1;
         }
         void calcCounts()
         {
                  vector<pair<int,int>> vp;
                  for(int i = 1; i < sz; i++)
                  {
                           vp.push_back({-len[i], i});
                  }
                  sort(vp.begin(), vp.end());
                  for(auto [L, v] : vp)
                  {
                           cnt[link[v]] += cnt[v];
                  }
         }
         void print()
         {
                  for(int state= 0; state < sz; state++)
                  {
                           cout<<link[state]<<"\n";
                           for(auto [c, t] : to[state])
                           {
                                    cout<<state<<" "<<t<<" "<<c<<"\n";
                           }
                  }
         }
         void extend(char c, int u)
         {
                  int p = last;
                  last = sz++;
                  cnt[last]= u;
                  len[last] = len[p] + 1;
                  for (; to[p][c] == 0; p = link[p])
                           to[p][c] = last;
                  if (to[p][c] == last) {
                           link[last] = 0;
                           return;
                  }
                  int q = to[p][c];
                  if (len[q] == len[p] + 1) {
                           link[last] = q;
                           return;
                  }
                  int cl = sz++;
                  to[cl] = to[q];
                  link[cl] = link[q];
                  len[cl] = len[p] + 1;
                  link[last] = link[q] = cl;
                  for (; to[p][c] == q; p = link[p])
                           to[p][c] = cl;
         }
         int nxt(int state, char c){
                  return to[state][c];
         }
};
