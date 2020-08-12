#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5,Q=1e6+5;
const long double eps=1e-6;
int n,q;
lint ans[Q];
struct vec_s{
	lint x,y;
	vec_s operator-()const;
	friend vec_s operator+(const vec_s &a,const vec_s &b);
	friend vec_s operator-(const vec_s &a,const vec_s &b);
	friend bool operator<(const vec_s &a,const vec_s &b);
	friend long double crs(const vec_s &a,const vec_s &b);
	friend lint pts(const vec_s &a,const vec_s &b);
}pnt[N],spt[N],qry[Q];
vector<vec_s> cbuk;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

vec_s vec_s::operator-()const{
	return (vec_s){-x,-y};
}
vec_s operator+(const vec_s &a,const vec_s &b){
	return (vec_s){a.x+b.x,a.y+b.y};
}
vec_s operator-(const vec_s &a,const vec_s &b){
	return (vec_s){a.x-b.x,a.y-b.y};
}
bool operator<(const vec_s &a,const vec_s &b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
long double crs(const vec_s &a,const vec_s &b){
	return (long double)a.x*b.y-(long double)a.y*b.x;
}
lint pts(const vec_s &a,const vec_s &b){
	return a.x*b.x+a.y*b.y;
}

void flip_y(vec_s v[],int len){
	for(int i=0,j; i<len; i=j){
		for(j=i+1; j<len&&v[j].x==v[i].x; ++j);
		reverse(v+i,v+j);
	}
}

int sancvh(vec_s v[],int len){
	if(len<=2) return len;
	int cnt=2;
	for(int i=2; i<len; ++i){
		assert(v[i-1].x<=v[i].x);
		for(; cnt>1&&crs(v[cnt-1]-v[cnt-2],v[i]-v[cnt-2])>=0; --cnt);
		v[cnt++]=v[i];
	}
	return cnt;
}

void getcvh(vec_s v1[],const int c1,vec_s v2[],const int c2){
	int p1=0,p2=0;
	do{
		vec_s lst=v1[p1]+v2[p2];
		cbuk.push_back(lst);
		if(p1==c1-1) ++p2;
		else if(p2==c2-1) ++p1;
		else{
			vec_s t1=v1[p1+1]+v2[p2],t2=v1[p1]+v2[p2+1];
			if(crs(t1-lst,t2-lst)<0) ++p1;
			else ++p2;
		}
	}while(p1<=c1-1&&p2<=c2-1);
}

void build_cbuk(const int l,const int r){//左端点在(l,mid]，右端点在(mid,r]的区间
	static vec_s cv1[N],cv2[N];
	if(l==r){
		cbuk.push_back(spt[l]);
		return;
	}
	const int mid=(l+r)>>1;
	build_cbuk(l,mid);
	build_cbuk(mid+1,r);
	flip_y(spt+l,mid-l+1);
	int c1=0,c2=0;
	for(int i=mid; i>=l; --i) cv1[c1++]=-spt[i];
	for(int i=mid+1; i<=r; ++i) cv2[c2++]=spt[i];
	c1=sancvh(cv1,c1);
	c2=sancvh(cv2,c2);
	getcvh(cv1,c1,cv2,c2);
	flip_y(spt+l,mid-l+1);
	inplace_merge(spt+l,spt+mid+1,spt+r+1);
}

lint qans(const vec_s &q){
	int l=0,r=cbuk.size()-1,mid;
	vec_s t=(vec_s){-q.y,q.x};
	while(r-l>2){//反向时位置？
		mid=(l+r)>>1;
		if(pts(t,cbuk[mid+1]-cbuk[mid])<0) r=mid+1;
		else l=mid;
	}
	lint res=-1e18;
	for(int i=l; i<=r; ++i)
		apx(res,(lint)crs(q,cbuk[i]));
	return res;
}

void gao(){//上凸包
	cbuk.clear();
	cbuk.reserve(n*10);
	build_cbuk(1,n);
	sort(cbuk.begin(),cbuk.end());
	cbuk.resize(sancvh(cbuk.data(),cbuk.size()));
	for(int i=1; i<=q; ++i){
		apx(ans[i],qans(qry[i]));
	}
}

int main(){
	n=ni,q=ni;
	memset(ans+1,-10,q*sizeof(ans[0]));
	for(int i=1; i<=n; ++i){
		pnt[i]=(vec_s){ni,ni};
		spt[i]=spt[i-1]+pnt[i];
	}
	for(int i=1; i<=q; ++i){
		qry[i]=(vec_s){ni,ni};
	}
	gao();
	for(int i=1; i<=n; ++i){
		pnt[i]=-pnt[i];
		spt[i]=spt[i-1]+pnt[i];
	}
	for(int i=1; i<=q; ++i){
		qry[i]=-qry[i];
	}
	gao();
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
