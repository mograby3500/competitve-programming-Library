#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

struct SuffixAutomaton{
         vector<map<int, int>> to;
         vector<int> link, len;
         int last, sz;
         SuffixAutomaton(int n){
                  to.resize(2 * n + 10);
                  link.resize(2 * n + 10);
                  len.resize(2 * n + 10);
                  last= 0, sz= 1;
         }
         void extend(int c)
         {
                  int p = last;
                  last = sz++;
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
};
const int N= 4e6 + 10;
int32_t  main() {
         cin.tie(0);
         cin.sync_with_stdio(0);

}
