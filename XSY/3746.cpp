#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5,M=2e5+5;
const int S=760;
int n,m,val[N];
lint abuk[M];
vector<int> pset[N],sset[N],tset[N];//sset: 挂着的附属小集合,tset: 小集合加入的时间
struct qry_s{
	int l,r,q,id;
	friend bool operator<(const qry_s &a,const qry_s &b);
};
vector<qry_s> qbuk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool operator<(const qry_s &a,const qry_s &b){
	int p=a.l/S,q=b.l/S;
	return p==q?(p&1?a.r>b.r:a.r<b.r):p<q;
}

void merge_to(vector<int> &a,vector<int> &b){
	vector<int> c;
	c.reserve(a.size()+b.size());
	merge(a.begin(),a.end(),b.begin(),b.end(),back_inserter(c));
	a.clear();
	swap(b,c);
}
void concat_to(vector<int> &a,vector<int> &b){
	b.reserve(a.size()+b.size());
	for(vector<int>::iterator it=a.begin(); it!=a.end(); ++it){
		b.push_back(*it);
	}
	a.clear();
}

namespace MD{
	int times[M],cbuk[N],nx[N],pre[N];
	//times[i]: 有多少个元素的值为i
	//cbuk[i]: 出现次数为i的值有多少个

	void ins(const int p,const int x){
		nx[x]=nx[p],pre[nx[p]]=x;
		nx[p]=x,pre[x]=p;
	}
	void del(const int x){//重新进入链表时会重设
		nx[pre[x]]=nx[x];
		pre[nx[x]]=pre[x];
		cbuk[x]=0;
	}
	void reset_nx(){
		for(int i=nx[0]; i; i=nx[i]) del(i);
		pre[0]=nx[0]=0;
	}

	void pls1(const int v){
		if(!cbuk[times[v]+1]++) ins(times[v],times[v]+1);
		if(!--cbuk[times[v]++]) del(times[v]-1);
	}
	void mns1(const int v){
		if(!cbuk[times[v]-1]++) ins(pre[times[v]],times[v]-1);
		if(!--cbuk[times[v]--]) del(times[v]+1);
	}

	lint qans(const int q){
		static int que[N];
		int cnt=0;
		for(int i=nx[0]; i; i=nx[i]){
			assert(i>0&&i!=nx[i]);
			que[++cnt]=i;
		}
		lint ans=0;
		for(int i=cnt,j=1,s=0; i; --i){
			for(; j<=cnt&&que[j]+que[i]<=q; ++j){
				s+=que[j]*cbuk[que[j]];
			}
			ans+=(lint)que[i]*cbuk[que[i]]*s;
		}
		return ans;
	}

	void aqry(const int x){
		if(qbuk[x].empty()) return;
		int pl=0,pr=-1,sz=pset[x].size();
		sort(qbuk[x].begin(),qbuk[x].end());
		cbuk[0]=N;
		for(vector<qry_s>::iterator it=qbuk[x].begin(); it!=qbuk[x].end(); ++it){
			while(pr<sz-1&&pset[x][pr+1]<=it->r) pls1(val[pset[x][++pr]]);
			while(pl>0&&pset[x][pl-1]>=it->l) pls1(val[pset[x][--pl]]);
			while(pr>=0&&pset[x][pr]>it->r) mns1(val[pset[x][pr--]]);
			while(pl<sz&&pset[x][pl]<it->l) mns1(val[pset[x][pl++]]);
			assert(sset[x].size()==tset[x].size());
			for(int i=0; i<(int)sset[x].size(); ++i){
				int p=sset[x][i];
				if(tset[x][i]>it->id||p<it->l||p>it->r) continue;
				pls1(val[p]);
			}
			abuk[it->id]=qans(it->q);
			for(int i=0; i<(int)sset[x].size(); ++i){
				int p=sset[x][i];
				if(tset[x][i]>it->id||p<it->l||p>it->r) continue;
				mns1(val[p]);
			}
		}
		reset_nx();
		memset(times,0,(m+1)*sizeof(int));
		qbuk[x].clear();
	}

	int bf_qry(const int x,const int l,const int r,const int q){//一定在int内？
		assert(sset[x].empty());
		cbuk[0]=N;
		for(vector<int>::iterator it=pset[x].begin(); it!=pset[x].end(); ++it){
			if(*it>=l&&*it<=r) pls1(val[*it]);
		}
		int ans=qans(q);
		reset_nx();
		for(vector<int>::iterator it=pset[x].begin(); it!=pset[x].end(); ++it){
			times[val[*it]]=0;
		}
		return ans;
	}
}

void fold_ss(const int x){
	MD::aqry(x);
	if(!sset[x].size()) return;
	sort(sset[x].begin(),sset[x].end());
	merge_to(sset[x],pset[x]);
	tset[x].clear();
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	memset(abuk,-1,sizeof(abuk));
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pset[i].push_back(i);
	}
	for(int i=1; i<=m; ++i){
		if(nxi()==1){
			int x=nxi(),y=nxi();
			if((int)pset[x].size()<S&&(int)pset[y].size()<S){
				merge_to(pset[y],pset[x]);
			}else if((int)pset[x].size()<S||(int)pset[y].size()<S){
				if(pset[x].size()<pset[y].size()){
					swap(pset[x],pset[y]),swap(qbuk[x],qbuk[y]);
					swap(sset[x],sset[y]),swap(tset[x],tset[y]);
				}
				int sz_y=pset[y].size();
				concat_to(pset[y],sset[x]);
				tset[x].reserve(tset[x].size()+sz_y);
				for(int j=0; j<sz_y; ++j){
					tset[x].push_back(i);
				}
				if(sset[x].size()>=S){
					fold_ss(x);
				}
			}else{
				fold_ss(x),fold_ss(y);
				merge_to(pset[y],pset[x]);
			}
		}else{
			const int x=nxi(),l=nxi(),r=nxi(),q=nxi();
			if(pset[x].size()<S){
				abuk[i]=MD::bf_qry(x,l,r,q);
			}else{
				qbuk[x].push_back((qry_s){l,r,q,i});
			}
		}
	}
	for(int i=1; i<=n; ++i){
		MD::aqry(i);
	}
	for(int i=1; i<=m; ++i){
		if(~abuk[i]) printf("%lld\n",abuk[i]);
	}
	return 0;
}
