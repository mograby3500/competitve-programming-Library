#include<bits/stdc++.h>
using namespace std;

#define N 409 //max number of vertices in one part
#define INF 100000000 //just infinity
int cost[N][N]; //cost matrix
int n, max_match; //n workers and n jobs
int lx[N], ly[N]; //labels of X and Y parts
int xy[N]; //xy[x] - vertex that is matched with x,
int yx[N]; //yx[y] - vertex that is matched with y
bool S[N], T[N]; //sets S and T in algorithm
int slack[N]; //as in the algorithm description
int slackx[N], prv[N];

void init_labels(){
     memset(lx, 0, sizeof(lx));
     memset(ly, 0, sizeof(ly));
     for (int x = 0; x < n; x++)
          for (int y = 0; y < n; y++)
               lx[x] = max(lx[x], cost[x][y]);
}
void add_to_tree(int x, int prevx){
     S[x] = true; //add x to S
     prv[x] = prevx; //we need this when augmenting
     for (int y = 0; y < n; y++) //update slacks, because we add new vertex to S
          if (lx[x] + ly[y] - cost[x][y] < slack[y])
          {
               slack[y] = lx[x] + ly[y] - cost[x][y];
               slackx[y] = x;
          }
}
void update_labels()
{
     int x, y, delta = INF; //init delta as infinity
     for (y = 0; y < n; y++) //calculate delta using slack
          if (!T[y])
               delta = min(delta, slack[y]);
     for (x = 0; x < n; x++) //update X labels
          if (S[x]) lx[x] -= delta;
     for (y = 0; y < n; y++) //update Y labels
          if (T[y]) ly[y] += delta;
     for (y = 0; y < n; y++) //update slack array
          if (!T[y])
               slack[y] -= delta;
}
void augment(){
     if (max_match == n) return; //check wether matching is already perfect
     int x, y, root; //just counters and root vertex
     int q[N], wr = 0, rd = 0; //q - queue for bfs, wr,rd - write and read pos in queue
     memset(S, false, sizeof(S)); //init set S
     memset(T, false, sizeof(T)); //init set T
     memset(prv, -1, sizeof prv);
     
     for (x = 0; x < n; x++) //finding root of the tree
          if (xy[x] == -1)
          {
               q[wr++] = root = x;
               prv[x] = -2;
               S[x] = true;
               break;
          }
     for (y = 0; y < n; y++) //initializing slack array
     {
          slack[y] = lx[root] + ly[y] - cost[root][y];
          slackx[y] = root;
     }
     //second part of augment() function
     while (true) //main cycle
     {
          while (rd < wr) //building tree with bfs cycle
          {
               x = q[rd++]; //current vertex from X part
               for (y = 0; y < n; y++) //iterate through all edges in equality graph
                    if (cost[x][y] == lx[x] + ly[y] && !T[y])
                    {
                         if (yx[y] == -1) break; //an exposed vertex in Y found, so
//augmenting path exists!
                         T[y] = true; //else just add y to T,
                         q[wr++] = yx[y]; //add vertex yx[y], which is matched
//with y, to the queue
                         add_to_tree(yx[y], x); //add edges (x,y) and (y,yx[y]) to the tree
                    }
               if (y < n) break; //augmenting path found!
          }
          if (y < n) break; //augmenting path found!
          update_labels(); //augmenting path not found, so improve labeling
          wr = rd = 0;
          for (y = 0; y < n; y++)
               if (!T[y] && slack[y] == 0)
               {
                    if (yx[y] == -1) //exposed vertex in Y found - augmenting path exists!
                    {
                         x = slackx[y];
                         break;
                    }
                    else
                    {
                         T[y] = true; //else just add y to T,
                         if (!S[yx[y]])
                         {
                              q[wr++] = yx[y];
                              add_to_tree(yx[y], slackx[y]);
                         }
                    }
               }
          if (y < n) break; //augmenting path found!
     }
     if (y < n) //we found augmenting path!
     {
          max_match++;
          for (int cx = x, cy = y, ty; cx != -2; cx = prv[cx], cy = ty)
          {
               ty = xy[cx];
               yx[cy] = cx;
               xy[cx] = cy;
          }
          augment();
     }
}
int hungarian(){
     int ret = 0; //weight of the optimal matching
     max_match = 0; //number of vertices in current matching
     memset(xy, -1, sizeof(xy));
     memset(yx, -1, sizeof(yx));
     init_labels(); //step 0
     augment(); //steps 1-3
     for (int x = 0; x < n; x++) //forming answer there
          ret += cost[x][xy[x]];
     return ret;
}
void get_ac(){
     cin>>n;
     vector<long long> a(n), b(n), c(n);
     vector<int> p(n);
     for(int i= 0; i < n; i++)
          cin>>a[i];
     for(int i = 0; i < n; i++)
          cin>>p[i];
     for(int i = 0; i < n; i++)
          cin>>b[i];
     for(int i = 0; i < n; i++)
          cin>>c[i];
     
     
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
               for(int k = 0; k < n; k++){
                    if(b[i] + c[j] > a[k])
                         cost[i][j] += p[k];
               }
          }
     }
     cout<<hungarian()<<"\n";
}
int main() {
     cin.tie(0);
     cin.sync_with_stdio(0);
     
     int T; T = 1;
     while(T--){
          get_ac();
     }
}
