#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2;
int n,q;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int p,k,v,cnt,tick,rt[N];
	struct node{
		int l,r,sz;
		lint s;
	}tr[N*31];
	inline void upd(const int k){
		tr[k].s=tr[tr[k].l].s+tr[tr[k].r].s;
		tr[k].sz=tr[tr[k].l].sz+tr[tr[k].r].sz;
	}
	void mod(const int p,int &k,const int l,const int r){
		k=++cnt;
		memcpy(tr+k,tr+p,sizeof(node));
		if(l==r){
			++tr[k].sz;
			tr[k].s+=T::v;
			return;
		}
		const int mid=(l+r)>>1;
		if(v<=mid) mod(tr[p].l,tr[k].l,l,mid);
		else mod(tr[p].r,tr[k].r,mid+1,r);
		upd(k);
	}
	lint ask_v(const int p,const int k,const int l,const int r,const int v){
		if(r<=v) return tr[k].s-tr[p].s;
		const int mid=(l+r)>>1;
		int ans=ask_v(tr[p].l,tr[k].l,l,mid,v);
		if(v>mid) ans+=ask_v(tr[p].r,tr[k].r,mid+1,r,v);
		return ans;
	}
}

inline lint solve(const int x,const int y){
	lint lst,ans=0;
	do{
		lst=ans;
		ans=T::ask_v(T::rt[x-1],T::rt[y],1,1e9,ans+1);
	}while(lst!=ans);
	return ans+1;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		T::v=nxi();
		T::mod(T::rt[T::tick],T::rt[T::tick+1],1,1e9);
		++T::tick;
	}
	q=nxi();
	while(q--){
		const int x=nxi(),y=nxi();
		printf("%lld\n",solve(x,y));
	}
	return 0;
}
