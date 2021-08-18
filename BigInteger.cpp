const int bignumlen=3000;
const int Blen=8;
const ll base=100000000;
struct bignum{
        
        int len;
        ll data[bignumlen];
        ll &operator [](int x){ return(data[x]);}
        const ll &operator [](int x)const { return(data[x]);}
        bignum (){
                memset(data,0,sizeof(data));
                len=0;
        }
        void clear(){
                for(int i=len;i>=1;--i)data[i]=0;
                len=0;
        }
        int check (const bignum &a,const bignum &b){
                if(a.len>b.len)return(0);
                if(b.len>a.len)return(1);
                for(int i=a.len;i>=1;--i){
                        if(a.data[i]<b.data[i])return(1);
                        if(b.data[i]<a.data[i])return(0);
                }
                return 2;
        }
        bignum operator=(const bignum &x){
                for(int i=x.len+1;i<=len;++i)data[i]=0;
                for(int i=1;i<=x.len;++i)data[i]=x.data[i];
                len=x.len;
                return *this;
        }
        bignum operator=(ll x){
                for(int i=len;i>=0;--i)data[i]=0;
                len=0;
                while(x){
                        data[++len]=x%base;
                        x/=base;
                }
                return *this;
        }
        bignum(ll x){
                memset(data,0,sizeof(data));
                len=0;
                (*this)=x;
        }
        bignum operator *(const bignum &b){
                int i,j;
                bignum tmp;
                for(i=1;i<=len;++i)if(data[i]!=0)
                                for(j=1;j<=b.len;++j)if(b.data[j]!=0){
                                                tmp.data[i+j-1]+=data[i]*b.data[j];
                                                tmp.data[i+j]+=tmp.data[i+j-1]/base;
                                                tmp.data[i+j-1]%=base;
                                        }
                tmp.len=len+b.len-1;
                while(tmp.data[tmp.len+1])tmp.len++;
                return tmp;
        }
        
        bignum operator +(const bignum &b){
                bignum tmp;
                int i,l=max(len,b.len);
                for(i=1;i<=l;++i)tmp[i]=data[i]+b[i];
                for(i=1;i<=l;++i)tmp[i+1]+=tmp[i]/base,tmp[i]%=base;
                tmp.len=l;
                if(tmp[tmp.len+1])tmp.len++;
                return tmp;
        }
        
        bignum operator +=(const bignum &b){return *this=(*this+b);}
        bignum operator *=(const bignum &b){return *this=(*this*b);}
        bignum operator *=(ll x) {return( *this=(*this *x));}
        bignum operator +=(ll x) {return( *this=(*this +x));}
        
        void write(){
                printf("%I64d",data[len]);
                for(int i=len-1;i>=1;--i)printf("%0*I64d",Blen,data[i]);
        }
        
};
