#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long lint;
using namespace std;
const int N=1e5+5,M=1e6+5;
int n,m,cfa[M];
struct pep{
	int fr,to,id;
	const bool direct() const;
};
struct op_s{
	bool type;
	int x,y;
};
vector<pep> pbuk[M];

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
			const bool f=(c=='-')&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

const bool pep::direct() const{
	return fr<to;
}

lint cans(){
	lint ans=0;
	for(int scc=0,i=1; i<m; ++i){
		scc+=cfa[i];
		ans+=cabs(scc);
	}
	return ans;
}

queue<pep> que;
vector<op_s> frt,bck;

bool getpep(const int i,pep &p){
	for(; !que.empty()&&(p=que.front(),max(p.fr,p.to)<=i); que.pop()){
		bck.push_back((op_s){0,p.id,p.to});
	}
	return !que.empty();
}

void oput_ans(){
	frt.clear(),bck.clear();
	for(int i=1; i<=m; ++i){
		pep x;
		for(vector<pep>::iterator it=pbuk[i].begin(); it!=pbuk[i].end(); ++it){
			if(!getpep(i,x)||x.direct()==it->direct()){
				que.push(*it);
			}else{
				que.pop();
				pep y=*it;
				if(!x.direct()) swap(x,y);
				if(x.fr!=i){
					frt.push_back((op_s){0,x.id,i});
				}
				if(y.to!=i){
					bck.push_back((op_s){0,y.id,y.to});
				}
				const int cl=i,cr=min(x.to,y.fr);
				if(y.fr<=x.to){//交错
					frt.push_back((op_s){0,y.id,cl});
					frt.push_back((op_s){1,x.id,y.id});
					frt.push_back((op_s){0,x.id,cr});
					if(y.fr!=x.to){
						pbuk[y.fr].push_back((pep){y.fr,x.to,x.id});
					}
				}else{
					bck.push_back((op_s){0,x.id,cr});
					bck.push_back((op_s){1,x.id,y.id});
					bck.push_back((op_s){0,y.id,cl});
					pbuk[x.to].push_back((pep){y.fr,x.to,y.id});
				}
			}
		}
	}
	pep fff;
	assert(!getpep(m,fff));
	printf("%d\n",int(frt.size()+bck.size()));
	for(vector<op_s>::iterator it=frt.begin(); it!=frt.end(); ++it){
		printf("%d %d %d\n",it->type,it->x,it->y);
	}
	for(vector<op_s>::reverse_iterator it=bck.rbegin(); it!=bck.rend(); ++it){
		printf("%d %d %d\n",it->type,it->x,it->y);
	}
}

int main(){
	for(int T=ni; T--; ){
		n=ni,m=ni;
		memset(cfa+1,0,m*sizeof(cfa[0]));
		for(int i=1; i<=m; ++i){
			pbuk[i].clear();
		}
		for(int i=1; i<=n; ++i){
			pep tmp=(pep){ni,ni,i};
			pbuk[min(tmp.fr,tmp.to)].push_back(tmp);
			++cfa[tmp.fr];
			--cfa[tmp.to];
		}
		printf("%lld ",cans());
		oput_ans();
	}
	return 0;
}
