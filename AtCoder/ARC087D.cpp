#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=8005;
int cc[2][N],cnt[2];
char str[N];

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

bool vld(int *v,int n,int tgt){
	static bool vld[N];
	memset(vld,0,sizeof(vld));
	if(!n) return tgt==0;
	int tot=0;
	for(int i=1; i<=n; ++i){
		tot+=v[i];
	}
	{
		int tmp=std::max(tgt,-tgt);
		if(tot<tmp||(tot-tmp)&1) return 0;
		tot=(tot-tmp)>>1;
	}
	vld[0]=1;
	int s=0;
	for(int i=1; i<=n; ++i){
		s+=v[i];
		for(int j=s; j>=v[i]; --j){
			vld[j]|=vld[j-v[i]];
		}
	}
	return vld[tot];
}

int main(){
	scanf("%s",str+1);
	int n=strlen(str+1),p0=0,p1=0;
	for(int p=0,st=1,i=1; i<=n+1; ++i){
		if(i>n||str[i]=='T'){
			if(st<i){
				if(st==1) p0=-i+1;
				else cc[p][++cnt[p]]=i-st;
			}
			p^=1,st=i+1;
		}
	}
	p0+=nxi(),p1+=nxi();
	puts(vld(cc[0],cnt[0],p0)&&vld(cc[1],cnt[1],p1)?"Yes":"No");
	return 0;
}
