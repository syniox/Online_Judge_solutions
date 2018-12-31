#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1005;
int n;
lint cnt_all;
struct vec{
	lint x,y;

	friend vec operator - (const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
	friend long double crs(const vec &a,const vec &b){
		return (long double)a.x*b.y-(long double)b.x*a.y;
	}
	const int quad() const {
		if(x>0&&y>=0) return 1;
		if(x<=0&&y>0) return 2;
		if(x<0&&y<=0) return 3;
		if(x>=0&&y<0) return 4;
		return 0;
	}
	friend bool operator < (const vec &a,const vec &b){
		int qa=a.quad(),qb=b.quad();
		if(qa!=qb) return qa<qb;
		return crs(a,b)>0;
	}
	inline friend std::ostream & operator << (std::ostream & out,const vec &b){
		out<<"("<<b.x<<","<<b.y<<")";
		return out;
	}
}pnt[N];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace G{
	vec base;
	vec buk[N];

	bool cmp_base(const vec &a,const vec &b){
		return a-base<b-base;
	}

	inline lint calc(){
		memcpy(buk,pnt,(n+1)*sizeof(vec));
		lint res=0;
		for(int i=1; i<=n; ++i){
			base=pnt[i];
			std::sort(buk+1,buk+n+1,cmp_base);
			//n>2
			for(int j=2,k=3; j<=n; ++j){
				while(k!=j&&crs(buk[j]-pnt[i],buk[k]-pnt[i])>=0){
					if(++k>n) k=2;
				}
				int side=j<k?k-j-1:(k+n-1)-j-1;
				res+=(lint)side*(side-1)>>1;
				res+=(lint)(n-2-side)*(n-2-side-1)>>1;
			}
		}
		return res>>1;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
	}
	cnt_all=(lint)n*(n-1)*(n-2)*(n-3)/(2*3*4);
	lint cnt_cal=G::calc();
	cnt_cal-=cnt_all*3;
	printf("%lld\n",cnt_cal*8+(lint)n*(n-1)*(n-2)*4);
	return 0;
}
