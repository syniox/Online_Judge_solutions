#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
int n,m;
lint ans[N];
struct data{
	int id,t,a,b;

	friend bool operator < (const data &a,const data &b){
		return a.t<b.t;
	}
}dt[N];

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}


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

void solve(){
	//apn!!!
	static std::vector <int> apply[N],token_des[N];
	std::vector <int> ::iterator it;
	static std::set <int> st_pos;
	std::set <int> ::iterator st;
	int solved=0;
	int lap=0,rap=0,lto=0,rto=0;
	for(lint i=0,j=0,pos=1; solved<n; ){
		for(; j<n&&dt[j+1].t<=i; ++j){
			if(dt[j+1].a==dt[j+1].b){
				++solved;
				continue;
			}
			if(dt[j+1].a==pos){
				token_des[dt[j+1].b].push_back(j+1);
				st_pos.insert(dt[j+1].b);
				if(dt[j+1].b<pos) ++lap;
				if(dt[j+1].b>pos) ++rap;
			}
			else{
				apply[dt[j+1].a].push_back(j+1);
				st_pos.insert(dt[j+1].a);
				if(dt[j+1].a<pos) ++lap;
				if(dt[j+1].a>pos) ++rap;
			}
		}
		if(solved==j){
			i=dt[j+1].t;
			continue;
		}
		int lsum=lap+lto,rsum=rap+rto;
		bool type=rsum>=lsum;//1: 向右
		st=st_pos.upper_bound(pos);
		if(type){
			int des=m;
			if(st!=st_pos.end()) apn(des,*st);
			int step=des-pos;
			if(j<n) apn(step,dt[j+1].t-(int)i);
			pos+=step,i+=step;
		}
		else{
			int des=1;
			if(st!=st_pos.begin()) apx(des,*--st);
			int step=pos-des;
			if(j<n) apn(step,dt[j+1].t-(int)i);
			pos-=step,i+=step;
		}
		if(type){
			rto-=token_des[pos].size();
			rap-=apply[pos].size();
		}
		else{
			lto-=token_des[pos].size();
			lap-=apply[pos].size();
		}
		if(!apply[pos].empty()||!token_des[pos].empty()){
			st_pos.erase(pos);
		}
		for(it=apply[pos].begin(); it!=apply[pos].end(); ++it){
			token_des[dt[*it].b].push_back(*it);
			st_pos.insert(dt[*it].b);
			if(dt[*it].b<pos) ++lto;
			if(dt[*it].b>pos) ++rto;
		}
		apply[pos].clear();
		for(it=token_des[pos].begin(); it!=token_des[pos].end(); ++it){
			++solved;
			apn(ans[dt[*it].id],i);
		}
		token_des[pos].clear();
	}
}

int main(){
	n=nxi(),m=nxi();
	memset(ans+1,10,n*sizeof(lint));
	for(int i=1; i<=n; ++i){
		dt[i].t=nxi(),dt[i].a=nxi(),dt[i].b=nxi(),dt[i].id=i;
		if(dt[i].a==dt[i].b) ans[i]=dt[i].t;
	}
	std::sort(dt+1,dt+n+1);
	solve();
	for(int i=1; i<=n; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
