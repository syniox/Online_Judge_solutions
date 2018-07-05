#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=200005;
const int ha=19260817;
const int mod=1e9+7;
int n,ans,tl,tk,xl[N],vc[N],zk[N],fk[N],que[N];
lint hx[N],xh[N],qh[N];

inline int nxi(){
	int x(0);
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

lint qmi(int x,int t){
	if(!t) return 1;
	lint q=qmi(x,t>>1);
	q=q*q%mod;
	if(t&1) q=q*x%mod;
	return q;
}

inline int zx(int x,int k){
	return ((hx[x+k-1]-hx[x-1]*qh[k])%mod+mod)%mod;
}

inline int fx(int x,int k){
	return ((xh[x]-xh[x+k]*qh[k])%mod+mod)%mod;
}

bool eql(int a,int b,int k){
	return (zk[a]==zk[b]&&fk[a]==fk[b])||(zk[a]==fk[b]&&zk[b]==fk[a]);
}

bool jdg(int i,int k){
	for(int j=1;j<=tk;++j){
		if(eql(i,que[j],k)) return 0;
	}
	return 1;
}

inline int cal(int k){
	int q=tk=0;
	for(int i=1;i<=n-k+1;i+=k){
		zk[i]=zx(i,k),fk[i]=fx(i,k);
		if(jdg(i,k)){
			que[++tk]=i;
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
