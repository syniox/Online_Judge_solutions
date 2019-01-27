#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=50005;
int n;
lint ans;

struct node{
	int v[4];
}nd[N],nd_cp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int cmp_util;

	bool cmp_v(const node &a,const node &b){
		return a.v[cmp_util]<b.v[cmp_util];
	}

	inline void solve(node *a,int len_a,node *b,int len_b,int dep){
		//a smaller than b
		static node buk[N];
		if(!len_a||!len_b) return;
		if(dep==4){
			ans+=(lint)len_a*len_b;
			return;
		}
		if(dep!=1){
			cmp_util=dep;
			std::sort(b+1,b+len_b+1,cmp_v);
		}
		memcpy(buk+1,a+1,len_a*sizeof(node));
		const int mid=(len_b+1)>>1;
		int pt_l=0,pt_r=len_a+1;
		for(int i=1; i<=len_a; ++i){
			if(buk[i].v[dep]<b[mid].v[dep]) a[++pt_l]=buk[i];
			else a[--pt_r]=buk[i];
		}
		node *a_copy=new node[len_a+1];
		node *b_copy=new node[len_b+1];
		std::memcpy(a_copy+1,a+1,len_a*sizeof(node));
		std::memcpy(b_copy+1,b+1,len_b*sizeof(node));

		//goto itself?
		solve(a,pt_l,b,mid,dep);
		solve(a+pt_l,pt_l,b_copy,mid,dep);
		solve(a_copy,len_a-pt_l,b+mid,len_b-mid,dep+1);
		solve(a_copy+pt_l,len_a-pt_l,b_copy+mid,len_b-mid,dep);

		delete[] a_copy;
		delete[] b_copy;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i) nd[i].v[0]=i;
	for(int i=1; i<=n; ++i) nd[i].v[1]=nxi();
	for(int i=1; i<=n; ++i) nd[i].v[2]=nxi();
	for(int i=1; i<=n; ++i) nd[i].v[3]=nxi();
	memcpy(nd_cp+1,nd+1,n*sizeof(node));
	S::solve(nd,n,nd_cp,n,1);
	printf("%lld\n",ans);
	return 0;
}
