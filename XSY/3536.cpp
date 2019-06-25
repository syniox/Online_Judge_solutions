#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <set>
typedef long long lint;
const int N=405;
int n,m;

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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

struct vec{
	int x,y;
	friend vec operator - (const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
	friend bool operator == (const vec &a,const vec &b){
		return a.x==b.x&&a.y==b.y;
	}
	friend lint crs(const vec &a,const vec &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	inline int quad() const{
		if(x>0&&y>=0) return 1;
		if(y>0&&x<=0) return 2;
		if(x<0&&y<=0) return 3;
		if(y<0&&x>=0) return 4;
		assert(!x&&!y);
		return 0;
	}
	friend bool operator < (const vec &a,const vec &b){
		int qa=a.quad(),qb=b.quad();
		if(qa!=qb) return qa<qb;
		lint res=crs(a,b);
		if(res) return res>0;
		return (a.x+a.y)<(b.x+b.y);
	}
}base,pw[N],pb[N];
std::set <vec> used;

inline bool cpb_quad(const vec &a,const vec &b){
	return a-base<b-base;
}

inline bool cpb_crs(const vec &a,const vec &b){
	return crs(a-base,b-base)>0;
}

template <class T>
void bswap(T *val,int mid,int len){
	static T tmp[N];
	for(int i=1; i<=mid; ++i){
		tmp[i]=val[i];
	}
	for(int i=1; i<=len; ++i){
		val[i]=val[i+mid];
	}
	for(int i=1; i<=mid; ++i){
		val[i+len-mid]=tmp[i];
	}
	/*
	const int l1=mid,l2=len-mid;
	memcpy(tmp+1,val+1,mid*sizeof(T));
	memcpy(val+mid+1,val+1,l2*sizeof(T));
	memcpy(val+l2+1,tmp+1,l1*sizeof(T));
	*/
}

int concave(){
	static vec buk[N];
	int ans=0;
	std::sort(pw+1,pw+n+1,cpb_quad);
	std::sort(pb+1,pb+m+1,cpb_quad);
	assert(pw[1]==base);
	for(int i=1; i<=m; ++i){
		int cnt=0;
		for(int j=2; j<=n; ++j){
			if(crs(base-pb[i],pw[j]-pb[i])>0){
				buk[++cnt]=pw[j];
			}
		}
		for(int j=1; j<cnt; ++j){
			if(!cpb_crs(buk[j],buk[j+1])){
				bswap(buk,j,cnt);
				break;
			}
		}
		//if(mrk) bswap(buk,mrk,cnt);
		//std::sort(buk+1,buk+cnt+1,cpb_crs);
		int ed=0;
		for(int j=i+1; j<=m; ++j){
			if(crs(base-pb[i],pb[j]-pb[i])>0) break;
			for(; ed<cnt; ++ed){
				if(crs(buk[ed+1]-pb[j],base-pb[j])<0) break;
			}
			ans+=ed;
		}
		for(int j=1; j<i; ++j){
			if(crs(base-pb[i],pb[j]-pb[i])>0) break;
			for(; ed<cnt; ++ed){
				if(crs(buk[ed+1]-pb[j],base-pb[j])<0) break;
			}
			ans+=ed;
		}
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		pw[i].x=nxi(),pw[i].y=nxi();
	}
	for(int i=1; i<=m; ++i){
		pb[i].x=nxi(),pb[i].y=nxi();
	}
	lint ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			int c1=0,c2=0;
			for(int k=1; k<=m; ++k){
				if(crs(pw[j]-pw[i],pb[k]-pw[i])<0) ++c1;
				else ++c2;
			}
			ans+=c1*c2;
		}
	}
	for(int i=1; i<=n; ++i){
		int t=1;
		while(used.find(pw[t])!=used.end()) ++t;
		used.insert(pw[t]);
		base=pw[t];
		ans-=concave();
	}
	printf("%lld\n",ans);
	return 0;
}
