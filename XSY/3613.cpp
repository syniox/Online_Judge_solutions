#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
typedef long long lint;
const int N=1e5+5;
int n,m,l,mcnt[N];
struct data{
	int m,p,x,y;
	friend bool cmp_x(const data &a,const data &b){
		return a.x<b.x;
	}
	friend bool cmp_y(const data &a,const data &b){
		return a.y<b.y;
	}
}dt[N],*dbuk[N];

//return 0时a在b前
struct cpq_x{
	bool operator () (const data &a,const data &b){
		return a.x<b.x;
	}
};

//return 0时a在b前
struct cpq_y{
	bool operator () (const data &a,const data &b){
		return a.y>b.y;
	}
};

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

bool cmp_x(const data &a,const data &b);
bool cmp_y(const data &a,const data &b);

namespace D{
	int v[N*4],cnt;
	inline void clear(){
		cnt=0;
	}
	inline void insert(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+cnt+1,x)-v;
	}
}

bool get_dbuk(){
	for(int i=1; i<=n; ++i){
		dt[i].m=D::ask(dt[i].m);
		++mcnt[dt[i].m];
	}
	for(int i=1; i<=m; ++i){
		dbuk[i]=new data[mcnt[i]+1];
		memset(dbuk[i],0,mcnt[i]+1*sizeof(data));
	}
	memset(mcnt+1,0,m*sizeof(int));
	for(int i=1; i<=n; ++i){
		dbuk[dt[i].m][++mcnt[dt[i].m]]=dt[i];
	}
	for(int i=1; i<=m; ++i){
		static data tmp[N];
		std::priority_queue <data,std::vector <data>,cpq_x> pq;
		std::sort(dbuk[i]+1,dbuk[i]+mcnt[i]+1,cmp_y);
		int cnt=0;
		for(int j=dbuk[i][mcnt[i]].y,k=mcnt[i]; k||!pq.empty(); --j){
			for(; k&&dbuk[i][k].y>=j; --k){
				pq.push(dbuk[i][k]);
			}
			if(pq.empty()){
				j=dbuk[i][k].y+1;
				continue;
			}
			data t=pq.top();
			pq.pop();
			if(t.x>j) return 0;
			++cnt;
			tmp[cnt]=(data){t.m,cnt,t.x,j};
		}
		assert(cnt==mcnt[i]);
		memcpy(dbuk[i]+1,tmp+1,cnt*sizeof(data));
	}
	return 1;
}

void disc_dbuk(){
	D::clear();
	for(int i=1; i<=m; ++i){
		for(int j=1; j<=mcnt[i]; ++j){
			D::insert(dbuk[i][j].x-1);
			D::insert(dbuk[i][j].y);
		}
	}
	D::build();
	l=D::cnt;
	for(int i=1; i<=m; ++i){
		for(int j=1; j<=mcnt[i]; ++j){
			dbuk[i][j].x=D::ask(dbuk[i][j].x-1)+1;
			dbuk[i][j].y=D::ask(dbuk[i][j].y);
		}
	}
}

int get_ans(){
	static std::priority_queue <data,std::vector <data>,cpq_y> pq,mq[N];
	static bool *used[N];
	static int cnt_q[N];
	static std::vector <data> ibuk[N];
	std::set <int> inq;
	for(int i=1; i<=m; ++i){
		std::sort(dbuk[i]+1,dbuk[i]+mcnt[i]+1,cmp_x);
		used[i]=new bool[mcnt[i]+1];
		memset(used[i]+1,0,mcnt[i]);
		for(int j=1; j<=mcnt[i]; ++j){
			ibuk[dbuk[i][j].x].push_back(dbuk[i][j]);
		}
	}
	int ans=0;
	for(int i=1; i<=l; ++i){
		for(std::vector <data> ::iterator it=ibuk[i].begin(); it!=ibuk[i].end(); ++it){
			if(!cnt_q[it->m]++) inq.insert(it->m);
			pq.push(*it);
			mq[it->m].push(*it);
		}
		while(!pq.empty()&&used[pq.top().m][pq.top().p]){
			pq.pop();
		}
		if(!pq.empty()) assert(pq.top().y>=i);
		if(pq.empty()||pq.top().y>i) continue;
		++ans;
		for(std::set <int> ::iterator it=inq.begin(); it!=inq.end();){
			data t=mq[*it].top();
			mq[*it].pop();
			used[t.m][t.p]=1;
			if(!--cnt_q[*it]) inq.erase(it++);
			else ++it;
		}
	}
	return ans;
}

int main(){
	n=nxi(),nxi();
	for(int i=1; i<=n; ++i){
		dt[i].x=nxi(),dt[i].y=nxi(),dt[i].m=nxi();
		D::insert(dt[i].m);
	}
	D::build();
	m=D::cnt;
	if(!get_dbuk()){
		puts("GG");
		return 0;
	}
	disc_dbuk();
	printf("%d\n",get_ans());
	return 0;
}
