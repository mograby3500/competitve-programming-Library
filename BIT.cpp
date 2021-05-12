const int N = 2e5 + 10;
int BIT[N];
void update(int x,int val) {
    while(x<=N)
    {
        BIT[x]+=val;
        x+=(x&-x);
    }
}
int query(int x) {
    int res=0;
    while(x>0)
    {
        res+=BIT[x];
        x-=(x&-x);
    }
    return res;
}
