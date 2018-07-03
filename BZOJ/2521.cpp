#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=502;
int n,m,lb,fr,to,fw,cnt,fi[N],fir[N],cur[N],que[N],dep[N],map[N][N];
 
struct edge{
    int to,wi,nx;
}eg[1600],gg[1605];
 
inline void add(int a,int b,int v){
    eg[++cnt]=(edge){b,v,fir[a]};
    fir[a]=cnt;
    eg[++cnt]=(edge){a,v,fir[b]};
    fir[b]=cnt;
}
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
    return x;
}
 
inline bool bfs(){
    memset(dep,0,sizeof(dep));
    dep[fr]=1;
    int hd=0,tl=1;
    que[0]=fr;
    while(hd!=tl){
        int x=que[hd++];
        for(int i=cur[x]=fir[x];i;i=eg[i].nx){
            int y=eg[i].to;
            if(!dep[y]&&eg[i].wi){
                que[tl++]=y;
                dep[y]=dep[x]+1;
            }
        }
    }
    return dep[to];
}
 
int dfs(int x,int t){
    if(x==to) return t;
    int tp,tt=t;
    for(int &i=cur[x];i;i=eg[i].nx){
        int y=eg[i].to,&v=eg[i].wi;
        if(v&&t&&dep[y]==dep[x]+1&&(tp=dfs(y,min(v,t)))){
            v-=tp;
            eg[i^1].wi+=tp;
            t-=tp;
            if(!t) break;
        }
    }
    return tt-t;
}
 
int main(){
    cnt=0;
    memset(map,31,sizeof(map));
    n=nxi(),m=nxi(),lb=nxi();
    for(int a,b,c,i=1;i<=m;++i){
        a=nxi(),b=nxi(),c=nxi();
        gg[++cnt]=(edge){b,c,fi[a]};
        fi[a]=cnt;
        if(i==lb) fr=a,to=b,fw=c;
    }
    if(fr>to) swap(fr,to);
    cnt=1;
    for(int x=1;x<=n;++x){
        for(int i=fi[x];i;i=gg[i].nx){
            if(gg[i].wi<=fw&&i!=lb) add(x,gg[i].to,fw-gg[i].wi+1);
        }
    }
    int ans(0);
    while(bfs()) ans+=dfs(fr,1e9);
    printf("%d\n",ans);
    return 0;
}
