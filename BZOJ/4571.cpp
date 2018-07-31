#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e5+2;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,cnt,rt[N];
	struct node{
		int l,r,sz;
	}tr[(int)4e6];
	void mod(int pk,int &nk,int l,int r,int v){
		tr[nk=++cnt]=tr[pk];
		++tr[nk].sz;
		if(l==v&&r==v) return;
		int mid=(l+r)>>1;
		if(v>mid) mod(tr[pk].r,tr[nk].r,mid+1,r,v);
		else mod(tr[pk].l,tr[nk].l,l,mid,v);
	}
	bool ask(int lk,int rk,int l,int r){
		if(tr[rk].sz-tr[lk].sz==0) return 0;
		if(l>=x&&r<=y) return 1;
		int ans=0,mid=(l+r)>>1;
		if(x<=mid) ans|=ask(tr[lk].l,tr[rk].l,l,mid);
		if(!ans&&y>mid) ans|=ask(tr[lk].r,tr[rk].r,mid+1,r);
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	n=nxi(),m=nxi();
	T::rt[0]=1;
	for(int i=1;i<=n;++i){
		using namespace T;
		mod(rt[i-1],rt[i],0,99999,nxi());
	}
	while(m--){
		int b=nxi(),x=nxi(),l=nxi(),r=nxi(),s=0;
		for(int i=17;i>=0;--i){
			if(b&(1<<i)){
				T::x=s -x,T::y=(s|(1<<i))-1 -x;
				if(!T::ask(T::rt[l-1],T::rt[r],0,99999)) s|=1<<i;
			}
			else{
				T::x=(s|(1<<i)) -x,T::y=(s|((1<<(i+1))-1)) -x;
				if(T::ask(T::rt[l-1],T::rt[r],0,99999)) s|=1<<i;
			}
		}
		printf("%d\n",s^b);
	}
	return 0;
}
