#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=30005;
int n,m,idx_a[N],idx_b[N];

template <class T> inline void apx(T &x,const T y);

struct node{
	int v,pos;
	friend bool cmp_v(const node &a,const node &b){
		return a.v<b.v;
	}
}val_a[N],val_b[N];

struct mtrx{
	//00 01 01 10 10 11
	//00 01 10 01 10 11
	lint v[6][6];
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		memset(c.v,-2,sizeof(c.v));
		for(int i=0; i<6; ++i){
			for(int j=0; j<6; ++j){
				for(int k=0; k<6; ++k){
					apx(c.v[i][j],a.v[i][k]+b.v[k][j]);
				}
			}
		}
		return c;
	}
	inline void print(){
		for(int i=0; i<6; ++i){
			for(int j=0; j<6; ++j){
				if(v[i][j]>=0) printf("%d -> %d: %lld\n",i,j,v[i][j]);
			}
		}
	}
}dp_mtx[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}
bool cmp_v(const node &a,const node &b);

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void make_mtrx(int x){
	// 0  1  2  3  4  5
	//00 01 01 10 10 11
	//00 01 10 01 10 11
	//2 1 0
	mtrx ans;
	memset(ans.v,-2,sizeof(ans.v));
	lint aval[3],bval[3];
	int apos[3],bpos[3];
	for(int i=0; i<3; ++i){
		apos[i]=x-i>0?val_a[x-i].pos:bpos[0];
		bpos[i]=x-i>0?val_b[x-i].pos:apos[0];
		aval[i]=x-i>0?val_a[x-i].v:-1e9+5;
		bval[i]=x-i>0?val_b[x-i].v:-1e9+5;
	}
	if(apos[0]!=bpos[2]&&apos[2]!=bpos[0]){
		lint tp=aval[0]*bval[2]+aval[2]*bval[0];
		ans.v[0][1]=tp;
		ans.v[1][5]=tp;
	}
	if(apos[2]!=bpos[0]){
		ans.v[2][3]=aval[2]*bval[0];
	}
	if(apos[2]!=bpos[0]&&apos[0]!=bpos[1]){
		ans.v[2][5]=aval[2]*bval[0]+aval[0]*bval[1];
	}
	if(apos[0]!=bpos[2]){
		ans.v[3][2]=aval[0]*bval[2];
	}
	if(apos[0]!=bpos[2]&&apos[1]!=bpos[0]){
		ans.v[3][5]=aval[0]*bval[2]+aval[1]*bval[0];
	}
	ans.v[4][0]=0;
	if(apos[0]!=bpos[0]){
		ans.v[4][1]=aval[0]*bval[0];
	}
	if(apos[0]!=bpos[1]){
		ans.v[4][2]=aval[0]*bval[1];
	}
	if(apos[1]!=bpos[0]){
		ans.v[4][3]=aval[1]*bval[0];
	}
	if(apos[0]!=bpos[1]&&apos[1]!=bpos[0]){
		ans.v[4][5]=aval[0]*bval[1]+aval[1]*bval[0];
	}
	ans.v[5][4]=0;
	if(apos[0]!=bpos[0]){
		ans.v[5][5]=aval[0]*bval[0];
	}
	dp_mtx[x]=ans;
}

namespace T{
	mtrx tr[N<<1];
	int x;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]*tr[idx(mid+1,r)];
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=dp_mtx[l];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void renew_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=dp_mtx[l];
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) renew_t(l,mid);
		else renew_t(mid+1,r);
		upd(l,r);
	}

	inline void renew(const int x){
		T::x=x;
		renew_t(1,n);
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i) val_a[i]=(node){nxi(),i};
	for(int i=1; i<=n; ++i) val_b[i]=(node){nxi(),i};
	std::sort(val_a+1,val_a+n+1,cmp_v);
	std::sort(val_b+1,val_b+n+1,cmp_v);
	for(int i=1; i<=n; ++i){
		idx_b[val_b[i].pos]=i;
	}
	for(int i=1; i<=n; ++i){
		make_mtrx(i);
	}
	T::build(1,n);
	for(int x,y; m; --m){
		x=nxi(),y=nxi();
		std::swap(val_b[idx_b[x]].pos,val_b[idx_b[y]].pos);
		for(int i=idx_b[x]; i<=n&&i<=idx_b[x]+2; ++i){
			make_mtrx(i);
			T::renew(i);
		}
		for(int i=idx_b[y]; i<=n&&i<=idx_b[y]+2; ++i){
			make_mtrx(i);
			T::renew(i);
		}
		std::swap(idx_b[x],idx_b[y]);
		printf("%lld\n",T::tr[T::idx(1,n)].v[5][5]);
	}
	return 0;
}
