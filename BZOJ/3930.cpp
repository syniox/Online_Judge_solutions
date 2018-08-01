#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<cstring>
typedef long long lint;
const int N=1e6+7;
const int mod=1e9+7;


struct Mu{
	std::map <int,int> mp;
	int a[N];
	inline int adj(int x){
		return x;
	}
	inline int dirch(int x){
		return 1;
	}
	inline int operator () (int x){
		if(x<N) return a[x];
		if(mp.count(x)) return mp[x];
		int ans=dirch(x);
		for(int i=2,j=x/i;i<=x;i=x/j+1,j=x/i){
			ans=(ans-(adj(x/j)-adj(i-1))*(*this)(j))%mod;
		}
		return mp[x]=ans;
	}
}mu;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t){
	lint ans(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void init(){
	static int cnp,prm[N];
	static bool npr[N];
	mu.a[1]=1;
	for(int i=2;i<N;++i){
		if(!npr[i]){
			mu.a[i]=-1;
			prm[++cnp]=i;
		}
		for(int j=1;j<=cnp&&i*prm[j]<N;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
			mu.a[i*prm[j]]=-mu.a[i];
		}
		mu.a[i]+=mu.a[i-1];
	}
}

int main(){
	init();
	int p=nxi(),k=nxi(),l=nxi(),r=nxi();
	lint ans=0;
	l=(l-1)/k,r/=k;
	for(int i=1,j;i<=r;i=j+1){
		int pl=l/i,pr=r/i;
		if(i<=l) j=std::min(l/pl,r/pr);
		else j=r/pr;
		ans=(ans+(mu(j)-mu(i-1))*qpow(pr-pl,p))%mod;
	}
	if(ans<0) ans+=mod;
	printf("%lld\n",ans);
	return 0;
}
