#include <iostream>
#include <cstdio>
#include <cstring>
const int N=50005;
int n,hx1[N],hx2[N],fd[N],invd[N];
bool vis[N<<1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,v;
	struct node{
		int s,f;
		inline void chn(const int v){
			s+=v,f+=v;
		}
	}tr[N<<2];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].s=std::min(tr[idx(l,mid)].s,tr[idx(mid+1,r)].s);
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(tr[k].f&&l!=r){
			tr[idx(l,mid)].chn(tr[k].f);
			tr[idx(mid+1,r)].chn(tr[k].f);
			tr[k].f=0;
		}
	}

	void mod_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].chn(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	inline void mod(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n<<1);
	}
}

inline int solve(){
	memset(T::tr,0,sizeof(T::tr));
	int ans=invd[1];
	for(int i=1;i<=n;++i){
		T::mod(hx1[i],n<<1,1);
		T::mod(hx2[i],n<<1,-1);
		apn(ans,-T::tr[T::idx(1,n<<1)].s+invd[i+1]);
	}
	return n-ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		vis[hx1[i]=nxi()]=1;
	}
	for(int i=1,j=n;i<=n<<1;++i){
		if(!vis[i]) hx2[j--]=i;
	}
	for(int i=n;i;--i){
		T::mod(hx1[i],n<<1,-1);
		T::mod(hx2[i],n<<1,1);
		invd[i]=-T::tr[T::idx(1,n<<1)].s;
	}
	printf("%d\n",solve());
	return 0;
}
