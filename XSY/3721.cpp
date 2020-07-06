#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,q;
string ans;
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace SA{
	int n,sa[N],rk[N];
	char *str;
	inline int qrk(const int x){
		return x>n?-1:rk[x];
	}
	inline void fsort(int *sa,const int *rk,const int *idx){
		static int buk[N];
		const int lim=std::max(n,26);
		memset(buk,0,(lim+1)*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rk[i]];
		}
		for(int i=1; i<=lim; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rk[idx[i]]]--]=idx[i];
		}
	}
	void build(char *str,const int n){
		static int tmp[N];
		SA::str=str,SA::n=n;
		for(int i=1; i<=n; ++i){
			rk[i]=str[i]-'a';
			tmp[i]=i;
		}
		fsort(sa,rk,tmp);
		for(int w=1,crk=1; w<n&&crk<n; crk=w<<=1){
			for(int i=1; i<=w; ++i){
				tmp[i]=n-w+i;
			}
			for(int i=1; i<=n; ++i){
				if(sa[i]>w) tmp[++crk]=sa[i]-w;
			}
			fsort(sa,rk,tmp);
			crk=0;
			for(int i=1; i<=n; ++i){
				if(i==1||rk[sa[i]]!=rk[sa[i-1]]||qrk(sa[i]+w)!=qrk(sa[i-1]+w)){
					++crk;
				}
				tmp[sa[i]]=crk;
			}
			memcpy(rk+1,tmp+1,n*sizeof(int));
		}
	}
}

int main(){
	q=nxi();
	scanf("%s",str+1);
	n=strlen(str+1);
	SA::build(str,n);
	for(int lst=0,i=25; ~i; --i){
		using SA::sa;
		using SA::rk;
		std::priority_queue <int> pq;
		int cnt=0,psum=0,xr=0;
		for(int pl=lst+1; pl<=n; ++pl){
			if(str[pl]!='a'+i) continue;
			int pr=pl;
			for(; str[pr+1]=='a'+i; ++pr);
			++cnt,psum+=pr-pl+1;
			xr=pl=pr;
		}
		if(!cnt) continue;
		cnt-=str[lst+1]=='a'+i;
		if(cnt<q){
			for(int j=1; j<=psum; ++j)
				ans+=(char)('a'+i);
			q-=cnt;
			lst=xr;
		}else{
			cnt=0,psum=0;
			int mx=0,mxrk=0,offs=0;
			for(int pl=lst+1; pl<=n; ++pl){
				if(str[pl]!='a'+i) continue;
				int pr=pl;
				for(; str[pr+1]=='a'+i; ++pr);
				if(pl==lst+1){
					offs=pr-pl+1,pl=pr;
					continue;
				}
				int curc=psum+pr-pl+1;
				if(mx<curc) mx=curc,mxrk=0;
				if(mx==curc) apx(mxrk,rk[pr+1]);
				psum+=pr-pl+1;
				pq.push(-(pr-pl+1));
				if((int)pq.size()==q){
					psum+=pq.top();
					pq.pop();
				}
				pl=pr;
			}
			for(int j=1; j<=mx+offs; ++j){
				ans+=(char)('a'+i);
			}
			if(mxrk) ans+=str+sa[mxrk];
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}
