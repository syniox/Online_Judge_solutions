#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
const int N=1e6+2;
int n,ql,qr,cf[N],dp[N],pt[N<<1],buk[N<<1];
std::vector <int> vt[N<<1];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace T{
	int x,v,tr[N<<2];
	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]+tr[idx(mid+1,r)];
	}
	void mod(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k]+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod(l,mid);
		else mod(mid+1,r);
		upd(l,r);
	}
	int ask(const int l,const int r){
		if(l==r) return l;
		const int mid=(l+r)>>1;
		if(tr[idx(mid+1,r)]) return ask(mid+1,r);
		return ask(l,mid);
	}
	inline void mod_t(const int x,const int v){
		T::x=x,T::v=v;
		mod(0,(N-1)<<1);
	}
}

inline void pop(const int pos){
	const int val=dp[pos]+N;
	if(val<-2e6) return;
	if(vt[val][pt[val]+1]==pos) ++pt[val],--buk[val];
	if(!buk[val]) T::mod_t(val,-1);
}

inline void add(const int pos){
	const int val=dp[pos]+N;
	if(val<-2e6) return;
	if(!buk[val]) T::mod_t(val,1);
	while(buk[val]&&cf[vt[val].back()]>cf[pos]){
		--buk[val];
		vt[val].pop_back();
	}
	++buk[val];
	vt[val].push_back(pos);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	memset(dp,-4,sizeof(dp));
	memset(pt,-1,sizeof(pt));
	n=nxi(),ql=nxi(),qr=nxi();
	for(int i=1;i<=n;++i){
		cf[i]=cf[i-1]+nxi();
	}
	dp[0]=0;
	for(int i=1;i<=n;++i){
		if(i-qr>0) pop(i-qr-1);
		if(i-ql>=0) add(i-ql);
		const int val=T::ask(0,(N-1)<<1);
		if(!val&&!buk[val]) continue;
		const int f1=vt[val][pt[val]+1];
		dp[i]=dp[f1]+(cf[f1]<cf[i])-(cf[f1]>cf[i]);
		if(buk[val-1]){
			const int f2=vt[val-1][pt[val-1]+1];
			apx(dp[i],dp[f2]+(cf[f2]<cf[i])-(cf[f2]>cf[i]));
		}
	}
//	printf("cf:");
//	for(int i=1;i<=n;++i){
//		printf("%d ",cf[i]);
//	}
//	puts("");
//	printf("dp:");
//	for(int i=1;i<=n;++i){
//		printf("%d ",dp[i]);
//	}
//	puts("");
	if(dp[n]<-2e6) puts("Impossible");
	else printf("%d\n",dp[n]);
	return 0;
}
