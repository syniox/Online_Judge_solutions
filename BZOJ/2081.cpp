#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
typedef long long lint;
const int N=200005;
const int ha=19260817;
const int mod=1e9+7;
int n,ans,tl,tk,xl[N],vc[N],que[N];
lint hx[N],xh[N],qh[N];
map <int,int> mp;

inline int nxi(){
	int x(0);
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int zx(int x,int k){
	return ((hx[x+k-1]-hx[x-1]*qh[k])%mod+mod)%mod;
}

inline int fx(int x,int k){
	return ((xh[x]-xh[x+k]*qh[k])%mod+mod)%mod;
}

inline int cal(int k){
	int q=0;
	mp.erase(mp.begin(),mp.end());
	for(int i=1;i<=n-k+1;i+=k){
		int p=min(zx(i,k),fx(i,k));
		if(!mp[p]){
			mp[p]=1;
			++q;
		}
	}
	return q;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	qh[1]=ha;
	for(int i=2;i<N;++i) qh[i]=qh[i-1]*ha%mod;
	n=nxi();
	for(int i=1;i<=n;++i){
		xl[i]=nxi();
		hx[i]=(hx[i-1]*ha+xl[i])%mod;
	}
	for(int i=n;i;--i){
		xh[i]=(xh[i+1]*ha+xl[i])%mod;
	}
	for(int i=1;i<=n;++i){
		int k=cal(i);
		if(k==ans) vc[++tl]=i;
		if(k>ans){
			ans=k;
			vc[tl=1]=i;
		}
	}
	printf("%d %d\n",ans,tl);
	for(int i=1;i<=tl;++i){
		printf("%d ",vc[i]);
	}
	return 0;
}
