#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
typedef long long lint;
const int N=205;
int n,m,qs,qt;
std::vector <std::pair <double,double> >cvx;

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

namespace G{
	int cnt,fir[N],pre_p[N],pre_e[N];
	double w1,w2,dis[N];
	struct edge{
		int to,v1,v2,nx;
	}eg[N<<2];
	struct data{
		int x;
		double dis;
		friend bool operator < (const data &a,const data &b){
			return a.dis>b.dis;
		}
	};

	inline void add(const int a,const int b,const int v1,const int v2){
		eg[++cnt]=(edge){b,v1,v2,fir[a]};
		fir[a]=cnt;
	}

	inline double real_d(const edge &e){
		return e.v1*w1+e.v2*w2;
	}

	void dij(){
		static bool vis[N];
		std::priority_queue <data> pq;
		memset(vis+1,0,n*sizeof(bool));
		for(int i=1; i<=n; ++i){
			dis[i]=1e18;
		}
		dis[qs]=0;
		pq.push((data){qs,0});
		while(!pq.empty()){
			const int x=pq.top().x;
			pq.pop();
			if(vis[x]) continue;
			if(x==qt) break;
			vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const double v=dis[x]+real_d(eg[i]);
				if(dis[y]>v){
					pre_p[y]=x;
					pre_e[y]=i;
					dis[y]=v;
					pq.push((data){y,v});
				}
			}
		}
	}

	std::pair <double,double> get_pr(const double w1,const double w2){
		G::w1=w1,G::w2=w2;
		dij();
		std::pair <double,double> res(0,0);
		for(int i=qt; i!=qs; i=pre_p[i]){
			const int e=pre_e[i];
			res.first+=eg[e].v1;
			res.second+=eg[e].v2;
		}
		return res;
	}
}

template <class T>
void get_cvx(const T &x,const T y){
	assert(y.first>=x.first);
	T mid=G::get_pr(x.second-y.second,y.first-x.first);
	if(mid==x||mid==y) return;
	get_cvx(x,mid);
	cvx.push_back(mid);
	get_cvx(mid,y);
}

double get_ans(){
	std::reverse(cvx.begin(),cvx.end());
	const int sz=cvx.size();
	double ans=0,lst=0;
	for(int i=0; i<sz; ++i){
		double end=1;
		if(i<sz-1){
			double ax=cvx[i].first,ay=cvx[i].second;
			double bx=cvx[i+1].first,by=cvx[i+1].second;
			assert(bx-by-ax+ay);
			end=(ay-by)/(bx-by-ax+ay);
		}
		assert(lst<=end);
		double mid=(lst+end)/2;
		ans+=(cvx[i].first*mid+cvx[i].second*(1-mid))*(end-lst);
		lst=end;
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi(),qs=nxi(),qt=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v1=nxi(),v2=nxi();
		G::add(a,b,v1,v2);
		G::add(b,a,v1,v2);
	}
	std::pair <double,double> x=G::get_pr(1,0);
	std::pair <double,double> y=G::get_pr(0,1);
	cvx.push_back(x);
	if(x!=y){
		get_cvx(x,y);
		cvx.push_back(y);
	}
	printf("%lf\n",get_ans());
	return 0;
}
