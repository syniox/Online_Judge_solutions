#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;
const int N=1e5+5;

namespace S{
	int cnt,lst;
	lint ans;
	struct node{
		int lk,len;
		lint cnt;
		std::map<int,int> c;
	}tr[N*2];
	struct _init{
		_init(){tr[0].lk=-1,tr[0].cnt=1;}
	}__init;

	void insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
			tr[k].cnt+=tr[p].cnt;
		}
		ans+=tr[k].cnt;
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			lint tmp=0;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
				tmp+=tr[p].cnt;
			}
			tr[k].lk=tr[q].lk=cnt;
			tr[q].cnt-=tmp;
			tr[cnt].cnt=tmp;
		}
	}
}

int main(){
	int n=ni;
	for(int i=1; i<=n; ++i){
		S::insert(ni);
		printf("%lld\n",S::ans);
	}
	return 0;
}
