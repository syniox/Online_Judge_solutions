#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=14;
int mx[N];
lint t[N];
bool vis[N][10];
struct data{
	lint a[10];
	data operator + (const data b) const {
		data c;
		for(int i=0;i<10;++i){
			c.a[i]=a[i]+b.a[i];
		}
		return c;
	}
}dp[N][10];

inline lint nxi(){
	lint x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	t[0]=1;
	for(int i=1;i<N;++i){
		t[i]=t[i-1]*10;
	}
}

//y: 1 exist? l->limit
data dfs(int w,int x,bool y,bool l){
	if(vis[w][x]&&y&&!l) return dp[w][x];
	data ans;
	for(int i=0;i<10;++i) ans.a[i]=0;
	if(w==1) return ans;
	int top=l?mx[w-1]:9;
	for(int i=0;i<=top;++i){
		ans=ans+dfs(w-1,i,i||y,l&&i==top);
	}
	for(int i=1-y;i<top;++i){
		ans.a[i]+=t[w-2];
	}
	if(!l) ans.a[top]+=t[w-2];
	else {
		lint tp=0;
		for(int i=w-2;i;--i){
			tp=tp*10+mx[i];
		}
		ans.a[top]+=tp+(y||top);//Be careful with zero
	}
	if(y&&!l) dp[w][x]=ans,vis[w][x]=1;
	return ans;
}

inline data cal(lint x){
	int cnt=0;
	while(x){
		mx[++cnt]=x%10;
		x/=10;
	}
	return dfs(cnt+1,0,0,1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	init();
	lint a=nxi(),b=nxi();
	if(a>b) swap(a,b);
	data x=cal(a-1),y=cal(b);
	for(int i=0;i<10;++i){
		printf("%lld ",y.a[i]-x.a[i]);
	}
	putchar('\n');
	return 0;
}
