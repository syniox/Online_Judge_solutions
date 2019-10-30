#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,tot,ccnt,ncnt;
struct pnt{
	int x,y,c;
	friend bool operator < (const pnt &a,const pnt &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
	friend pnt operator - (const pnt &a,const pnt &b){
		return (pnt){a.x-b.x,a.y-b.y,-1};
	}
	friend lint crs(const pnt &a,const pnt &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
}pt[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int andrew(pnt *pt,const int n){
	static pnt stk[N];
	int t1=0,t2=0;
	for(int i=1; i<=n; ++i){
		while(t1>1&&crs(pt[i]-stk[t1],pt[i]-stk[t1-1])>=0){
			--t1;
		}
		stk[++t1]=pt[i];
	}
	t2=t1;
	for(int i=n-1; i>=1; --i){
		while(t2>t1&&crs(pt[i]-stk[t2],pt[i]-stk[t2-1])>=0){
			--t2;
		}
		stk[++t2]=pt[i];
	}
	if(n>1) --t2;
	memcpy(pt+1,stk+1,t2*sizeof(pt[1]));
	return t2;
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int get_ans(pnt *pt,const int n,const int *f,const int c0){
	int exist=0,lst=0,fir_c=0,cnt=0;
	for(int i=1; i<=n; ++i){
		if(pt[i].c){
			if(!fir_c) fir_c=pt[i].c;
			exist|=1<<(pt[i].c-1);
			if(lst&&lst!=pt[i].c&&++cnt>2) return 0;
			lst=pt[i].c;
		}
	}
	if(lst!=fir_c&&cnt>1) return 0;
	if(exist==0){
		return (((lint)(n-1)*n+2)%mod*fpow(2,c0)-(!f[0])-!(f[1]))%mod;
	}
	if(exist==(exist&-exist)){
		int st_p=1,ed_p=n,ans=0;
		while(!pt[st_p].c) ++st_p;
		while(!pt[ed_p].c) --ed_p;
		for(int st=st_p,i=st_p; i<=ed_p; ++i){
			if(pt[i].c) st=i+1;
			else if(pt[i+1].c){
				ans=(ans+(lint)(i-st+1)*(i-st+2)/2)%mod;
			}
		}
		int gap=(n-ed_p)+(st_p-1);
		ans=(ans+(lint)gap*(gap+1)/2)%mod;
		if(f[(pt[st_p].c-1)^1]){
			return (lint)(ans+1)*fpow(2,c0)%mod;
		}
		return c0?((lint)(ans+1)*fpow(2,c0)-1)%mod:ans;
	}
	else{
		int gp1=0,gp2=0;
		for(int lst=0,i=1; i<=n<<1; ++i){
			int c=pt[(i-1)%n+1].c;
			if(!c) continue;
			if(lst&&c!=pt[(lst-1)%n+1].c){
				if(!gp1) gp1=i-lst;
				else{
					gp2=i-lst;
					break;
				}
			}
			lst=i;
		}
		assert(gp1&&gp2);
		return (lint)gp1*gp2%mod*fpow(2,c0)%mod;
	}
}

int main(){
	n=nxi();
	int c[2]={0};
	for(int i=1; i<=n; ++i){
		pt[i].x=nxi(),pt[i].y=nxi(),pt[i].c=nxi();
		if(pt[i].c==0) ++ccnt;
		else ++c[pt[i].c-1];
	}
	std::sort(pt+1,pt+n+1);
	tot=andrew(pt,n);
	for(int i=1; i<=tot; ++i){
		if(pt[i].c==0) ++ncnt;
		else --c[pt[i].c-1];
	}
	printf("%d\n",get_ans(pt,tot,c,ccnt-ncnt));
	return 0;
}
