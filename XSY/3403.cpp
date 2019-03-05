/**************************************************************
    Problem: 3403
    User: sy01
****************************************************************/
 
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e4+5;
const int mod=1e9+7;
int n;
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
    return x;
}
 
template <class T> inline void apx(T &x,const T y){
    if(x<y) x=y;
}
 
template <class T> inline int fpow(int x,T t){
    int ans=1;
    for(; t; x=(lint)x*x%mod,t>>=1){
        if(t&1) ans=(lint)ans*x%mod;
    }
    return ans;
}
 
#include <vector>
#define cout std::cerr
template<class T>inline void apadd(int &a,const T &b){
    a=(a+b)%mod;
}
inline std::vector<int>bm_sk(std::vector<int>a){
    using std::max;
    typedef std::vector<int>vi;
    vi c,b;
    int bpos,bval;
    c.push_back(1);
    const int &O=mod;
    for(int i=0;i<(int)a.size();++i){
        int sum=0;
        for(int j=0;j<(int)c.size();++j){
            sum=(sum+(lint)a[i-j]*c[j])%mod;
        }
        if(sum==0)continue;
        if(b.empty()){
            b=c,bpos=i,bval=sum;
            c.resize(i+2);
        }else{
            const int r=(lint)fpow(bval,O-2)*(O-sum)%O;
            vi tmpc=c;
            c.resize(max(c.size(),i-bpos+b.size()));
            for(int j=0;j<(int)b.size();j++){
                apadd(c[i-bpos+j],(lint)r*b[j]);
            }
            using namespace std;
            //if(i-tmpc.size()>bpos-b.size()){
            if(i-(int)tmpc.size()>bpos-(int)b.size()){
                b=tmpc,bpos=i,bval=sum;
            }
        }
    }
    return c;
}
 
inline int bm(int *tgt,int *src,int src_len){
    static int lst_len,lst[N];
    static int tgt_len;
    static int buk_len,buk[N];
    tgt[0]=lst[0]=lst_len=tgt_len=1;
    for(int i=0,lst_pos=-1,lst_val=0; i<src_len; ++i){
        int sum=0;
        for(int j=0; j<tgt_len; ++j){
            sum=(sum+(lint)tgt[j]*src[i-j])%mod;
        }
        if(sum==0) continue;
        if(lst_pos==-1){
            lst_pos=i;
            lst_val=sum;
            tgt_len=i+2;
        }
        else{
            memcpy(buk,tgt,tgt_len*sizeof(int));
            buk_len=tgt_len;
            for(int j=tgt_len; j<i-lst_pos+lst_len; ++j){
                assert(tgt[j]==0);
            }
            apx(tgt_len,i-lst_pos+lst_len);
            int tmp=(lint)(mod-sum)*fpow(lst_val,mod-2)%mod;
            for(int j=0; j<lst_len; ++j){
                tgt[j+i-lst_pos]=(tgt[j+i-lst_pos]+(lint)tmp*lst[j])%mod;
            }
            if(i-buk_len>lst_pos-lst_len){
                lst_pos=i,lst_len=buk_len;
                lst_val=sum;
                memcpy(lst,buk,buk_len*sizeof(int));
            }
        }
    }
    return tgt_len;
}
 
int main(){
    std::vector <int> vt;
    static int a[N],b[N];
    n=nxi();
    for(int i=0; i<n; ++i){
        a[i]=nxi();
        //vt.push_back(a[i]);
    }
    //std::vector <int> c=bm_sk(vt);
    int len=bm(b,a,n);
    printf("%d\n",len-1);
    for(int i=0; i<len; ++i){
        printf("%d ",b[i]);
    }
    puts("");
    return 0;
}
