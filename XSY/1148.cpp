#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
const int N=4e4+5;
const double eps=1e-4,P=acos(-1);
int n,m,jmp[16][N];
double ndis;
struct pnt{
	int x,y;
	double p;
	bool operator < (const pnt &b) const {
		return p<b.p;
	}
}pt[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline double crs(const double x1,const double y1,const double x2,const double y2){
	return (x1*y2)-(x2*y1);
}

inline double get_tan(const double x,const double y){
	const double ans=abs(y)<eps?P/2:atan(x/y);
	return ans+(y>0||(y==0&&x>0)?0:P);
}

inline double get_cos(const double x,const double y){
	return acos(x/y)+(y>0||(y==0&&x>0)?0:P);
}

inline bool jdg(const double aim){
	for(int i=1;i<=n;++i){
		const int x=pt[i].x,y=pt[i].y;
		pt[i].p=get_tan(y,x)+get_cos(aim,sqrt(x*x+y*y));
		if(pt[i].p>P*2) pt[i].p-=P*2;
	}
	std::sort(pt+1,pt+n+1);
	for(int i=1,j=i;i<=n;++i){
		const double x=pt[i].x,y=pt[i].y;
		const double vx=aim*cos(pt[i].p)-x;
		const double vy=aim*sin(pt[i].p)-y;
		while(crs(vx,vy,pt[j+1].x-x,pt[j+1].y-y)<0){
			if(++j>n) j-=n;
			if(j==i) return 1;
		}
		jmp[0][i]=(j>=i?j:j+n)-i+1;
		if(j==i) ++j;
	}
	for(int i=1;i<16;++i){
		for(int j=1;j<=n;++j){
			int f=(jmp[i-1][j]+j-1)%n+1;
			jmp[i][j]=jmp[i-1][f]+jmp[i-1][j];
		}
	}
	for(int i=1;i<=n;++i){
		int p=i,ans=0;
		for(int j=15;j>=0;--j){
			if(m&(1<<j)){
				ans+=jmp[j][p];
				if(ans>=n) break;
				p+=jmp[j][p]+1;
				if(p>n) p-=n;
			}
		}
		if(ans>=n) return 1;
	}
	return 0;
}

inline double solve(){
	double l=0,r=ndis,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(jdg(mid)) l=mid;
		else r=mid;
	}
	return l;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	ndis=1e7;
	for(int i=1;i<=n;++i){
		pt[i].x=nxi(),pt[i].y=nxi();
		apn(ndis,sqrt(pt[i].x*pt[i].x+pt[i].y*pt[i].y));
		if(!(pt[i].x||pt[i].y)){
			puts("0.00");
			return 0;
		}
	}
	printf("%.2lf\n",solve());
	return 0;
}
