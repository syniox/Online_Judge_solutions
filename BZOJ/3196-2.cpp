#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=5e4+5;
const int S=640;
int n,q,val[N];
int bel[N],blen[N/S+5],bidx[N/S+5][S],bque[N/S+5][S];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool cmp_val(const int a,const int b){
	return val[a]<val[b];
}

void build(const int p){
	int *idx=bidx[p],*que=bque[p];
	int cnt=0;
	for(int i=(p-1)*S+1; i<=std::min(p*S,n); ++i){
		idx[++cnt]=i;
	}
	blen[p]=cnt;
	std::sort(idx+1,idx+cnt+1,cmp_val);
	for(int i=1; i<=cnt; ++i){
		que[i]=val[idx[i]];
	}
}

int bget_rnk(const int p,const int v){
	int *q=bque[p];
	return std::lower_bound(q+1,q+blen[p]+1,v)-q-1;
}

int get_rnk(const int l,const int r,const int v){
	int res=1;
	if(bel[l]==bel[r]){
		for(int i=l; i<=r; ++i){
			res+=val[i]<v;
		}
		return res;
	}
	for(int i=bel[l]+1; i<bel[r]; ++i){
		res+=bget_rnk(i,v);
	}
	for(int i=l; bel[i]==bel[l]; ++i){
		res+=val[i]<v;
	}
	for(int i=r; bel[i]==bel[r]; --i){
		res+=val[i]<v;
	}
	return res;
}

int get_val(const int x,const int y,const int v){
	int l=-1e9,r=1e9,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(get_rnk(x,y,mid)>v) r=mid-1;
		else l=mid;
	}
	return l;
}

void chn_val(const int x,const int v){
	const int p=bel[x];
	int *bi=bidx[p],*bq=bque[p];
	int lpos=1;
	while(lpos<=blen[p]&&bi[lpos]!=x) ++lpos;
	assert(lpos<=blen[p]);
	for(int i=lpos; i<blen[p]; ++i){
		bi[i]=bi[i+1];
		bq[i]=bq[i+1];
	}
	int cpos=1;
	val[x]=v;
	while(cpos<blen[p]&&bq[cpos]<v) ++cpos;
	for(int i=blen[p]; i>cpos; --i){
		bi[i]=bi[i-1];
		bq[i]=bq[i-1];
	}
	bi[cpos]=x;
	bq[cpos]=v;
}

int bget_pre(const int p,const int v){
	int *q=bque[p],*pos=std::lower_bound(q+1,q+blen[p]+1,v);
	return pos==q+1?-1e9:*--pos;
}

int bget_nxt(const int p,const int v){
	int *q=bque[p],*pos=std::upper_bound(q+1,q+blen[p]+1,v);
	return pos==q+blen[p]+1?1e9:*pos;
}

int get_pre(const int l,const int r,const int v){
	int res=-1e9;
	if(bel[l]==bel[r]){
		for(int i=l; i<=r; ++i){
			if(val[i]<v) apx(res,val[i]);
		}
		return res;
	}
	for(int i=bel[l]+1; i<bel[r]; ++i){
		apx(res,bget_pre(i,v));
	}
	for(int i=l; bel[i]==bel[l]; ++i){
		if(val[i]<v) apx(res,val[i]);
	}
	for(int i=r; bel[i]==bel[r]; --i){
		if(val[i]<v) apx(res,val[i]);
	}
	return res;
}

int get_nxt(const int l,const int r,const int v){
	int res=1e9;
	if(bel[l]==bel[r]){
		for(int i=l; i<=r; ++i){
			if(val[i]>v) apn(res,val[i]);
		}
		return res;
	}
	for(int i=bel[l]+1; i<bel[r]; ++i){
		apn(res,bget_nxt(i,v));
	}
	for(int i=l; bel[i]==bel[l]; ++i){
		if(val[i]>v) apn(res,val[i]);
	}
	for(int i=r; bel[i]==bel[r]; --i){
		if(val[i]>v) apn(res,val[i]);
	}
	return res;
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		bel[i]=(i-1)/S+1;
	}
	for(int i=1; i<=bel[n]; ++i){
		build(i);
	}
	for(int a,b,i=1; i<=q; ++i){
		const int op=nxi();
		a=nxi(),b=nxi();
		switch(op){
			case 1:
				printf("%d\n",get_rnk(a,b,nxi()));
				break;
			case 2:
				printf("%d\n",get_val(a,b,nxi()));
				break;
			case 3:
				chn_val(a,b);
				break;
			case 4:
				printf("%d\n",get_pre(a,b,nxi()));
				break;
			case 5:
				printf("%d\n",get_nxt(a,b,nxi()));
				break;
			default:
				assert(0);
		}
	}
	return 0;
}
