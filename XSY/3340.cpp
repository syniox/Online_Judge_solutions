#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long lint;
const int N=2e5+5;
int n,lenu,lend;
class pnt{
	public:
		lint x,y;
		pnt operator - (const pnt &b) const {
			return (pnt){x-b.x,y-b.y};
		}
		lint hx(const int a){
			return x*a+y;
		}
}pdn[N],pup[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline lint crs(const pnt &a,const pnt &b){
	return a.x*b.y-a.y*b.x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline double turn_x(const pnt &a,const pnt &b){
	return (double)(b.y-a.y)/(a.x-b.x);
}

inline void andrew(pnt pt[],bool f,int &top){
	top=2;
	for(int i=3; i<=n; ++i){
		for(; top>1; --top){
			lint res=crs(pt[top]-pt[top-1],pt[i]-pt[top]);
			if(res&&(res>0)==f) break;
		}
		pt[++top]=pt[i];
	}
	for(int i=1; i<=top; ++i) pt[i].x=-pt[i].x;
}

inline lint solve(){
	lint ans=0;
	for(lint x=-1e15,i=1,j=1; i<=lenu&&j<=lend;){
		lint limit_up=i<lenu?turn_x(pup[i],pup[i+1]):1e15;
		lint limit_dn=j<lend?turn_x(pdn[j],pdn[j+1]):1e15;
		lint nx_x=std::min(limit_up,limit_dn);
		if(pup[i].x>pdn[j].x){
			apx(x,(lint)ceil(turn_x(pup[i],pdn[j])));
		}
		else if(pup[i].x<pdn[j].x){
			apn(nx_x,(lint)floor(turn_x(pup[i],pdn[j])));
		}
		ans+=((pup[i].hx(x)-pdn[j].hx(x)+1)+(pup[i].hx(nx_x)-pdn[j].hx(nx_x))+1)*(nx_x-x+1)>>1;
		nx_x=std::min(limit_up,limit_dn);
		x=nx_x+1;
		i+=nx_x==limit_up;
		j+=nx_x==limit_dn;
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		int l=nxi(),r=nxi();
		pdn[i]=(pnt){i,l};
		pup[i]=(pnt){i,r};
	}
	andrew(pdn,0,lend);
	andrew(pup,1,lenu);
	std::reverse(pdn+1,pdn+lend+1);
	printf("%lld\n",solve());
	return 0;
}
