#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=1005;
int n,m,k,ans,cnt(1),dep[N],que[N],fir[N],cur[N];
int dis[N],pre[N];
bool vis[N];
struct edge{
    int fr,to,wi,cs,nx;
}eg[10005];
struct node{
    int x,dis;
    bool operator < ( const node b) const {
        return dis> b.dis;
    }
};
priority_queue<node> Q;
inline void add(int a,int b,int c,int w){
    eg[++cnt]=(edge){a,b,c,w,fir[a]};
    fir[a]=cnt;
    eg[++cnt]=(edge){b,a,0,w,fir[b]};
    fir[b]=cnt;
}
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    for(;c>='0'&&c<='9';c=getchar()) x=x*10-48+c;
    return x;
}
bool bfs(){
    memset(dep,0,sizeof(dep));
    dep[1]=1;
    que[0]=1;
    int hd=0,tl=1;
    while(hd!=tl){
        int x=que[hd++];
        for(int i=cur[x]=fir[x];i;i=eg[i].nx){
            int y=eg[i].to;
            if(!dep[y]&&eg[i].wi){
                dep[y]=dep[x]+1;
                que[tl++]=y;
            }
        }
    }
    return dep[n];
}
int dfs(int x,int t){
    if(x==n) return t;
    int tp,tt(t);
    for(int &i=cur[x];i;i=eg[i].nx){
        int y=eg[i].to,&v=eg[i].wi;
        if(tt&&v&&dep[y]==dep[x]+1&&(tp=dfs(y,min(v,tt)))){
            v-=tp;
            eg[i^1].wi+=tp;
            tt-=tp;
        }
    }
    return t-tt;
}
inline void spfa(){
    memset(dis,31,sizeof(dis));
    int hd=0,tl=1;
    que[0]=1;
    dis[1]=0;
    while(hd!=tl){
        int x=que[hd++];
        if(hd==N) hd=0;
        vis[x]=0;
        for(int i=fir[x];i;i=eg[i].nx){
            int y=eg[i].to,v=eg[i].wi?0:eg[i].cs;
            if(dis[y]>dis[x]+v&&(!v||(i&1)==0)){//& ==
                dis[y]=dis[x]+v;
                pre[y]=i;
                if(!vis[y]){
                    vis[y]=1;
                    que[tl++]=y;
                }
            }
        }
    }
}
void dij(){
    memset(dis,31,sizeof(dis));
    memset(vis,0,sizeof(vis));
    while(!Q.empty()) Q.pop();
    dis[1]=0;
    Q.push((node){1,0});
    while(!Q.empty()){
        node x=Q.top();
        Q.pop();
        if(vis[x.x]) continue;
        if(x.x==n) return;
        vis[x.x]=1;
        for(int i=fir[x.x];i;i=eg[i].nx){
            int y=eg[i].to,v=eg[i].wi?0:eg[i].cs;
            if(dis[y]>dis[x.x]+v&&(!v||(i&1)==0)){
                pre[y]=i;
                dis[y]=dis[x.x]+v;
                Q.push((node){y,dis[x.x]+v});
            }
        }
    }
}
inline int cal(){
    int ans=0;
    for(int i=1;i<=k;++i){
        dij();
        for(int x=n,i=pre[x];x!=1;x=eg[i].fr,i=pre[x]){
            if(!eg[i].wi) ans+=eg[i].cs;
            else {
                --eg[i].wi;
                ++eg[i^1].wi;
            }
        }
    }
    return ans;
}
int main(){
    n=nxi(),m=nxi(),k=nxi();
    for(int a,b,c,w,i=1;i<=m;++i){
        a=nxi(),b=nxi(),c=nxi(),w=nxi();
        add(a,b,c,w);
    }
    while(bfs()) ans+=dfs(1,1e9);
    printf("%d %d\n",ans,cal());
    return 0;
}
