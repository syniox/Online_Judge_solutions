#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e4+5;
const int M=60;
const double eps=1e-7;
int n,m;
struct edge{
	int x,y,dis,val;
	friend bool operator < (const edge &a,const edge &b){
		return a.dis<b.dis;
	}
}eg[(int)2e5+5];

namespace IO{
	char *pt;
	struct _Initializer{
		_Initializer(){
			pt=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
		}
	}_initializer;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*pt++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*pt++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

class Mtrx{
	public:
		int sz;
		double **n;
		Mtrx(int len=0){
			sz=len;
			n=new double*[len];
			for(int i=0; i<len; ++i){
				n[i]=new double[len];
			}
		}
		Mtrx(const Mtrx &x){
			sz=x.sz;
			n=new double*[sz];
			for(int i=0; i<sz; ++i){
				n[i]=new double[sz];
				memcpy(n[i],x.n[i],sz*sizeof(double));
			}
		}
		inline void clear(){
			for(int i=0; i<sz; ++i){
				memset(n[i],0,sz*sizeof(double));
			}
		}
		~Mtrx(){
			delete[] n;
		}
		inline void add(const int x,const int y){
			if(x<sz) ++n[x][x];
			if(y<sz) ++n[y][y];
			if(x<sz&&y<sz) --n[x][y],--n[y][x];
		}
		inline void del(const int x,const int y){
			if(x<sz) --n[x][x];
			if(y<sz) --n[y][y];
			if(x<sz&&y<sz) ++n[x][y],++n[y][x];
		}
};

class UFS{
	public:
		int fa[N];
		inline int find_rt(const int x){
			return fa[x]?fa[x]=find_rt(fa[x]):x;
		}
}U[2];

inline long double get_dat(Mtrx a){
	for(int i=0; i<a.sz; ++i){
		int j=i;
		while(j<a.sz&&fabs(a.n[j][i])<eps) ++j;
		if(j==a.sz) return 0;
		if(i!=j){
			for(int k=0; k<a.sz; ++k){
				std::swap(a.n[j][k],a.n[i][k]);
			}
		}
		for(int j=i+1; j<a.sz; ++j){
			if(fabs(a.n[j][i])<eps) continue;
			double wgt=a.n[j][i]/a.n[i][i];
			for(int k=i; k<a.sz; ++k){
				a.n[j][k]-=a.n[i][k]*wgt;
			}
		}
	}
	long double res=1;
	for(int i=0; i<a.sz; ++i) res*=a.n[i][i];
	return res;
}

namespace S{
	std::vector <int> list[N];

	inline double solve(const int pos){
		static std::map <int,int> mp;
		static std::map <int,int> ::iterator mt;
		static std::vector <int> ::iterator it;
		int cnd=0;
		mp.clear();
		for(it=list[pos].begin(); it!=list[pos].end(); ++it){
			int x=U[0].find_rt(eg[*it].x),y=U[0].find_rt(eg[*it].y);
			if(x==y) continue;
			mt=mp.find(x);
			if(mt==mp.end()) x=mp[x]=cnd++;
			else x=mt->second;
			mt=mp.find(y);
			if(mt==mp.end()) y=mp[y]=cnd++;
			else y=mt->second;
		}
		if(!cnd) return 0;
		Mtrx mtx(cnd-1);
		mtx.clear();
		for(it=list[pos].begin(); it!=list[pos].end(); ++it){
			int x=U[0].find_rt(eg[*it].x),y=U[0].find_rt(eg[*it].y);
			if(x==y) continue;
			x=mp.find(x)->second;
			y=mp.find(y)->second;
			mtx.add(x,y);
		}
		long double tot_dat=get_dat(mtx);
		long double csum=0;
		for(it=list[pos].begin(); it!=list[pos].end(); ++it){
			int x=mp[U[0].find_rt(eg[*it].x)],y=mp[U[0].find_rt(eg[*it].y)];
			mtx.del(x,y);
			long double cur_dat=get_dat(mtx);
			csum+=(tot_dat-cur_dat)*eg[*it].val;
			mtx.add(x,y);
		}
		return csum/tot_dat;
	}

	inline long double calc(const int l,const int r){
		long double sum=0;
		for(int i=l; i<=r; ++i){
			int x=U[1].find_rt(eg[i].x),y=U[1].find_rt(eg[i].y);
			if(x!=y) U[1].fa[x]=y;
		}
		for(int i=l; i<=r; ++i){
			int x=U[1].find_rt(eg[i].x),y=U[1].find_rt(eg[i].y);
			assert(x==y);
			list[x].push_back(i);
		}
		for(int i=l; i<=r; ++i){
			int pos=U[1].find_rt(eg[i].x);
			if(list[pos].empty()) continue;
			sum+=solve(pos);
			list[pos].clear();
		}
		for(int i=l; i<=r; ++i){
			int x=U[0].find_rt(eg[i].x),y=U[0].find_rt(eg[i].y);
			if(x!=y) U[0].fa[x]=y;
		}
		return sum;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi();
		eg[i].dis=nxi(),eg[i].val=nxi();
		if(eg[i].x==eg[i].y) --i,--m;
	}
	std::sort(eg+1,eg+m+1);
	long double sum=0;
	for(int i=1,j=1; i<=m; i=j+1){
		for(j=i; j<m&&eg[j+1].dis==eg[i].dis;){
			++j;
		}
		sum+=S::calc(i,j);
	}
	printf("%.5Lf\n",sum);
	return 0;
}
