#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=1e5+5;
int n;
lint ans=2e18;
struct vec{
	int x,y;
	friend bool operator < (const vec &a,const vec &b){
		return a.x<b.x;
	}
}pnt[N];

template <class T> inline T sqr(const T a){
	return a*a;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

void solve(const int l,const int r){
	static vec buk[N],ls[N];
	const int mid=(l+r)>>1,len=r-l+1;
	if(l<mid) solve(l,mid);
	if(r>mid+1) solve(mid+1,r);
	int top=0,lim=sqrt(ans)+1;
	for(int i=l,j=mid+1; i<=mid||j<=r; ){
		if(i>mid) buk[++top]=pnt[j++];
		else if(j>r) buk[++top]=pnt[i++];
		else buk[++top]=pnt[pnt[i].y<pnt[j].y?i++:j++];
	}
	assert(top==r-l+1);
	top=0;
	for(int i=1; i<=len; ++i){
		if(abs(buk[i].x-mid)<=lim) ls[++top]=buk[i];
	}
	for(int i=1; i<=top; ++i){
		for(int j=i+1; j<=top; ++j){
			if(ls[j].y-ls[i].y>lim) break;
			apn(ans,sqr<lint>(ls[j].y-ls[i].y)+sqr<lint>(ls[j].x-ls[i].x));
		}
	}
	memcpy(pnt+l,buk+1,len*sizeof(vec));
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=i,pnt[i].y=pnt[i-1].y+nxi();
	}
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
