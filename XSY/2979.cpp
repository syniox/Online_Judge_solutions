#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace BIT{
	lint tr1[N],tr2[N];
	inline void mod_t(int x,const int v){
		const lint tp=(lint)x*v;
		for(;x<=n;x+=x&-x) tr1[x]+=v,tr2[x]+=tp;
	}
	inline lint ask_t(const int x){
		lint ans1=0,ans2=0;
		for(int t=x;t;t-=t&-t){
			ans1+=tr1[t],ans2+=tr2[t];
		}
		return ans1*(x+1)-ans2;
	}
	inline void mod(const int x,const int y,const int v){
		mod_t(x,v),mod_t(y+1,-v);
	}
	inline lint ask(int x,int y){
		return ask_t(y)-ask_t(x-1);
	}
}

namespace SEG{
	int x,y,cnt,rt[N];
	struct node{
		int l,r;//f+=1
		bool s;
	}tr[N*36];

	inline void upd(const int k){
		tr[k].s=tr[tr[k].l].s&tr[tr[k].r].s;
	}
	
	void rm_t(const int k,const int l,const int r){
		if(tr[k].s){
			BIT::mod(std::max(x,l),std::min(r,y),-1);
			return;
		}
		const int mid=(l+r)>>1;
		if(tr[k].l&&x<=mid) rm_t(tr[k].l,l,mid);
		if(tr[k].r&&y>mid) rm_t(tr[k].r,mid+1,r);
	}

	void mod_t(int &k,const int l,const int r){
		if(tr[k].s) return;
		if(!k) k=++cnt;
		if(l>=x&&r<=y){
			rm_t(k,l,r);
			BIT::mod(l,r,1);
			tr[k].s=1;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[k].l,l,mid);
		if(y>mid) mod_t(tr[k].r,mid+1,r);
		upd(k);
	}

	inline void mod(const int l,const int r,const int v){
		x=l,y=r;
		mod_t(rt[v],1,n);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int q=nxi();q;--q){
		const int op=nxi(),a=nxi(),b=nxi();
		if(op==0) SEG::mod(a,b,nxi());
		else printf("%lld\n",BIT::ask(a,b));
	}
	return 0;
}
