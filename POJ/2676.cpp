#include <iostream>
#include <cstdio>
#include <cstring>
const int N=9;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int cbit(int x){
	x=(x&0x5555)+((x&0xaaaa)>>1);
	x=(x&0x3333)+((x&0xcccc)>>2);
	x=(x&0x0f0f)+((x&0xf0f0)>>4);
	x=(x&0x00ff)+((x&0xff00)>>8);
	return x;
}

namespace G{
	int mp[N][N];
	int vld_row[N],vld_col[N],vld_sqr[N];
	//actually used

	inline void init(){
		memset(mp,0,sizeof(mp));
		memset(vld_row,0,sizeof(vld_row));
		memset(vld_col,0,sizeof(vld_col));
		memset(vld_sqr,0,sizeof(vld_sqr));
	}

	inline int get_sqr(int x,int y){
		return x/3*3+y/3;
	}

	inline int get_vld(const int x,const int y){
		return vld_row[x]|vld_col[y]|vld_sqr[get_sqr(x,y)];
	}

	inline void fill(int x,int y,int v){
		if(v==0) return;
		mp[x][y]^=v;
		vld_row[x]^=1<<(v-1);
		vld_col[y]^=1<<(v-1);
		vld_sqr[get_sqr(x,y)]^=1<<(v-1);
	}

	bool dfs(){
		int bx=0,by=0,st=0;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				if(mp[i][j]) continue;
				int tmp=get_vld(i,j);
				if(cbit(st)<cbit(tmp)){
					bx=i,by=j,st=tmp;
				}
			}
		}
		if(mp[bx][by]){
			for(int i=0; i<N; ++i){
				for(int j=0; j<N; ++j){
					printf("%d",mp[i][j]);
				}
				puts("");
			}
			return 1;
		}
		for(int i=1; i<=9; ++i){
			if(!((st>>(i-1))&1)){
				fill(bx,by,i);
				if(dfs()) return 1;
				fill(bx,by,i);
			}
		}
		return 0;
	}
}

int main(){
	static char ch[N];
	for(int T=nxi(); T; --T){
		G::init();
		for(int i=0; i<N; ++i){
			using namespace G;
			scanf("%s",ch);
			for(int j=0; j<N; ++j){
				if(ch[j]-'0') fill(i,j,ch[j]-'0');
			}
		}
		G::dfs();
	}
	return 0;
}
