#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
typedef long long lint;
const int N=1e5+2;
int qk,n,buk1[N<<1];
struct data{
	int l,r;
	bool operator < (const data &b) const {
		return l+r<b.l+b.r;
	}
}dt[N];

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
	int x,y,cnr,cnt,rt[N<<1];
	struct node{
		int l,r,sz;
		lint s;
	}tr[N*62];
	void mod(int &k,const int p,const int l,const int r){
		k=++cnt;
		tr[k]=tr[p];
		++tr[k].sz;
		tr[k].s+=x;
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(x<=mid) mod(tr[k].l,tr[p].l,l,mid);
		else mod(tr[k].r,tr[p].r,mid+1,r);
	}
	int ask_idx(const int k,const int p,const int l,const int r,const int s){
		if(l==r) return l;
		const int l_sz=tr[tr[k].l].sz-tr[tr[p].l].sz;
		const int mid=(l+r)>>1;
		if(l_sz>=s) return ask_idx(tr[k].l,tr[p].l,l,mid,s);
		return ask_idx(tr[k].r,tr[p].r,mid+1,r,s-l_sz);
	}
	int ask_sz(const int k,const int p,const int l,const int r){
		if(l>=x&&r<=y) return tr[k].sz-tr[p].sz;
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans+=ask_sz(tr[k].l,tr[p].l,l,mid);
		if(y>mid) ans+=ask_sz(tr[k].r,tr[p].r,mid+1,r);
		return ans;
	}
	lint ask_s(const int k,const int p,const int l,const int r){
		if(l>=x&&r<=y) return tr[k].s-tr[p].s;
		const int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=ask_s(tr[k].l,tr[p].l,l,mid);
		if(y>mid) ans+=ask_s(tr[k].r,tr[p].r,mid+1,r);
		return ans;
	}
	inline void mod_t(const int x){
		++cnr;
		T::x=x;
		mod(rt[cnr],rt[cnr-1],0,1e9);
	}
	inline int ask_sz_t(const int p,const int k,const int x,const int y){
		if(x>y) return 0;
		T::x=x,T::y=y;
		return ask_sz(rt[k],rt[p-1],0,1e9);
	}
	inline lint ask_s_t(const int p,const int k,const int x,const int y){
		if(x>y) return 0;
		T::x=x,T::y=y;
		return ask_s(rt[k],rt[p-1],0,1e9);
	}
}

inline lint calc(const int l,const int r,const int idx){
	const lint s_left=T::ask_s_t(l,r,0,idx-1),s_right=T::ask_s_t(l,r,idx+1,1e9);
	const lint sz_left=T::ask_sz_t(l,r,0,idx-1),sz_right=T::ask_sz_t(l,r,idx+1,1e9);
	return (sz_left*idx-s_left)+(s_right-idx*sz_right);
}

inline lint get_ans(){
	lint ans=1e14;
	for(int i=1;i<n;++i){
		const int idx1=T::ask_idx(T::rt[i<<1],T::rt[0],0,1e9,i);
		const int idx2=T::ask_idx(T::rt[n<<1],T::rt[i<<1|1],0,1e9,n-i);
//		const int s_left=dt[i].l+dt[i].r;
//		const int s_right=dt[i+1].l+dt[i+1].r;
//		if(abs(s_left-(idx1<<1))>abs(s_left-(idx2<<1))) continue;
//		if(abs(s_right-(idx2<<1))>abs(s_right-(idx1<<1))) continue;
		apn(ans,calc(1,i<<1,idx1)+calc(i<<1|1,n<<1,idx2));
	}
	return ans==1e14?0:ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	qk=nxi(),n=nxi();
	lint base=0;
	for(int i=1;i<=n;++i){
		char p,q;
		while((p=getchar())!='A'&&p!='B');
		int c1=nxi();
		while((q=getchar())!='A'&&q!='B');
		int c2=nxi();
		if(p==q){
			base+=abs(c1-c2);
			--i,--n;
		}
		else{
			++base;
			if(c1>c2) std::swap(c1,c2);
			dt[i]=(data){c1,c2};
		}
	}
	if(qk==1){
		for(int i=1;i<=n;++i){
			buk1[(i<<1)-1]=dt[i].l;
			buk1[i<<1]=dt[i].r;
		}
		std::sort(buk1+1,buk1+(n<<1)+1);
		const int mid=buk1[n];
		for(int i=1;i<=n<<1;++i){
			base+=abs(buk1[i]-mid);
		}
		printf("%lld\n",base);
	}
	else{
		std::sort(dt+1,dt+n+1);
		for(int i=1;i<=n;++i){
			T::mod_t(dt[i].l);
			T::mod_t(dt[i].r);
		}
		printf("%lld\n",base+get_ans());
	}
	return 0;
}
