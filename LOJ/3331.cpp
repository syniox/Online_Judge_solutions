#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int M=5e4+5,N=5e5+5;
int totn,m,q,cst,tot[M],req[M];
int *val[M],*cost[M];
struct st_s{
	int op,x1,y1,x2,y2,c;
}st[13];

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
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

int getidx(int x,int y){
	int id=0;
	for(int i=1; i<x; ++i) id+=tot[i];
	return id+y;
}

namespace S1{
	void main(){
		int ans=1e9;
		for(int i=1; i<1<<totn; ++i){
			int res=0,sum=0,vld=1;
			for(int s=0,j=1,p=1,r=1; vld&&j<=totn; ++j,++r){
				if(i>>(j-1)&1){
					assert(r<=tot[p]);
					res+=cost[p][r];
					s+=val[p][r];
				}
				if(r==tot[p]){
					if(s<req[p]) vld=0;
					sum+=s,s=0;
					++p,r=0;
				}
			}
			if(!vld||sum<q) continue;
			for(int j=1; j<=cst; ++j){
				int p1=getidx(st[j].x1,st[j].y1),p2=getidx(st[j].x2,st[j].y2);
				if(!(i>>(p1-1)&1)||!(i>>(p2-1))&1) continue;
				if(st[j].op==1) res-=st[j].c;
				else if(st[j].op==2) res+=st[j].c;
				else{
					res=1e9;
					break;
				}
			}
			apn(ans,res);
		}
		printf("%d\n",ans==1e9?-1:ans);
	}
}

namespace S3{
	void main(const int need){
		static int buk[N];
		int cnt=0,ans=0;
		for(int i=1; i<=m; ++i){
			if(tot[i]<req[i]){
				puts("-1");
				return;
			}
			sort(cost[i]+1,cost[i]+tot[i]+1);
			for(int j=1; j<=req[i]; ++j){
				ans+=cost[i][j];
			}
			for(int j=req[i]+1; j<=tot[i]; ++j){
				buk[++cnt]=cost[i][j];
			}
		}
		if(need>cnt){
			puts("-1");
			return;
		}
		sort(buk+1,buk+cnt);
		for(int i=1; i<=need; ++i){
			ans+=buk[i];
		}
		printf("%d\n",ans);
	}
}

int main(){
	m=ni,q=ni;
	bool v1=1;
	int creq=0;
	for(int i=1; i<=m; ++i){
		tot[i]=ni,req[i]=ni;
		creq+=req[i];
		val[i]=new int[tot[i]+1];
		cost[i]=new int[tot[i]+1];
		totn+=tot[i];
		for(int j=1; j<=tot[i]; ++j){
			val[i][j]=ni,cost[i][j]=ni;
			v1&=val[i][j]==1;
		}
	}
	cst=ni;
	for(int i=1; i<=cst; ++i){
		st[i]=(st_s){ni,ni,ni,ni,ni};
		if(st[i].op!=3) st[i].c=ni;
	}
	if(totn<=15) S1::main();
	//else if(totn<=1000&&cst==0) S2::main();
	else if(v1&&cst==0) S3::main(q-creq);
	//else if(creq==q&&cst==0) S4::main();
	return 0;
}
