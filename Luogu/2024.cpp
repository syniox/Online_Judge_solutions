#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n,ans;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N*3];//i 吃i的 i吃的
	inline int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
	inline int same(const int x,const int y){
		return find_rt(x)==find_rt(y);
	}
	inline void link(int x,int y){
		x=find_rt(x),y=find_rt(y);
		if(x!=y) fa[x]=y;
	}
}

int main(){
	n=nxi();
	for(int q=nxi(); q; --q){
		const int op=nxi(),x=nxi(),y=nxi();
		if(x>n||y>n||(op==2&&x==y)) ++ans;
		else if(op==1){
			if(U::same(x,y+n)||U::same(x,y+(n<<1))){
				++ans;
			}
			else{
				U::link(x,y);
				U::link(x+n,y+n);
				U::link(x+(n<<1),y+(n<<1));
			}
		}
		else{
			if(U::same(x,y)||U::same(x+n,y)){
				++ans;
			}
			else{
				U::link(y+n,x);
				U::link(y,x+(n<<1));
				U::link(y+(n<<1),x+n);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
