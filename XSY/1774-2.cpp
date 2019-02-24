#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1.1e6+5;
const int P=31;
const int mod=1e9+7;
int n,q;
unsigned hash[N],fpow[N];
bool type;
char ch[N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void init(){
	fpow[0]=1;
	for(int i=1; i<N; ++i){
		fpow[i]=fpow[i-1]*P;
	}
}

inline unsigned get_hash(unsigned l,unsigned r){
	return hash[r]-hash[l-1]*fpow[r-l+1];
}

inline int solve(const int x,const int y){
	if(x==y) return x;
	int mid,l=1,r=std::min(x,y)+1;
	while(l!=r){
		mid=(l+r)>>1;
		if(get_hash(x-mid+1,x)==get_hash(y-mid+1,y)) l=mid+1;
		else r=mid;
	}
	if(l>x||l>y) return l-1;
	return ch[x-l+1]<ch[y-l+1]?x:y;
}

int main(){
	init();
	scanf("%s",ch+1);
	n=strlen(ch+1);
	std::reverse(ch+1,ch+n+1);
	for(int i=1; i<=n; ++i){
		hash[i]=hash[i-1]*P+ch[i]-'a'+1;
	}
	q=nxi(),type=nxi();
	int ans=0;
	for(int res=0; q; --q){
		char c;
		while((c=get_c())!='Q'&&c!='I');
		if(c=='Q'){
			int x=nxi(),y=nxi();
			if(type){
				x=(x^res)%n+1,y=(y^res)%n+1;
			}
			//printf("res: %d\n",solve(x,y));
			ans=((lint)ans*23+(res=solve(x,y)))%mod;
		}
		else{
			while((c=get_c())<'a'||c>'z');
			ch[++n]=c;
			hash[n]=hash[n-1]*P+(unsigned)(c-'a'+1u);
		}
	}
	printf("%d\n",ans);
	return 0;
}
