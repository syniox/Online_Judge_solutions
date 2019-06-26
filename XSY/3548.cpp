#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
typedef long long lint;
const int N=505;
int n,m;
char mp[N][N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace L1{
	bool val[N];

	void oput(const int l,const int r){
		puts("+");
		for(int i=1; i<=n+m-1; ++i){
			putchar('0'+(i>=l&&i<=r));
			if(m==1) puts("");
		}
		if(n==1) puts("");
	}

	void solve(){
		if(n==1){
			for(int i=1; i<=m; ++i) val[i]=mp[1][i]=='1';
		}
		else{
			for(int i=1; i<=n; ++i) val[i]=mp[i][1]=='1';
		}
		const int len=n+m-1;
		int cnt=0;
		for(int i=1; i<=len; ++i){
			if(val[i]&&!val[i-1]) ++cnt;
		}
		printf("%d\n",cnt);
		for(int i=1,l=1; i<=len+1; ++i){
			if(val[i]&&!val[i-1]) l=i;
			if(val[i-1]&&!val[i]) oput(l,i-1);
		}
	}
}

namespace S12{
	int cnt,col[N][N];
	bool is_1[N*N];
	const int cx[]={1,0,-1,0},cy[]={0,1,0,-1};
	std::set <int> con[N*N];

	inline bool vld(const int x,const int y){
		return x>=1&&x<=n&&y>=1&&y<=m;
	}

	void paint(const int x,const int y,const int c){
		col[x][y]=c;
		for(int i=0; i<4; ++i){
			const int tx=x+cx[i],ty=y+cy[i];
			if(vld(tx,ty)&&!col[tx][ty]&&mp[tx][ty]==mp[x][y]) paint(tx,ty,c);
		}
	}

	bool solve(){
		int cnt_1=0;
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				if(col[i][j]) continue;
				cnt_1+=(is_1[++cnt]=mp[i][j]=='1');
				paint(i,j,cnt);
			}
		}
		if(cnt_1<=1){
			printf("%d\n",cnt_1);
			if(!cnt_1) return 1;
			puts("+");
			for(int i=1; i<=n; ++i){
				for(int j=1; j<=m; ++j){
					putchar(mp[i][j]);
				}
				puts("");
			}
			return 1;
		}
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				if(mp[i][j]=='1') continue;
				for(int k=0; k<4; ++k){
					int x=i+cx[k],y=j+cy[k];
					if(vld(x,y)&&mp[x][y]=='1'){
						con[col[i][j]].insert(col[x][y]);
					}
				}
			}
		}
		int spec=0;
		for(int i=1; !spec&&i<=cnt; ++i){
			if((int)con[i].size()==cnt_1) spec=i;
		}
		if(!spec) return 0;
		puts("2");
		puts("+");
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				putchar('0'+(mp[i][j]=='1'||col[i][j]==spec));
			}
			puts("");
		}
		puts("-");
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				putchar('0'+(col[i][j]==spec));
			}
			puts("");
		}
		return 1;
	}
}

void solve3_c(){
	puts("3");
	puts("+");
	for(int i=1; i<=m; ++i){
		putchar('1');
	}
	puts("");
	for(int i=2; i<n; ++i){
		for(int j=1; j<=m; ++j){
			putchar('0'+((j&1)==1||mp[i][j]=='1'));
		}
		puts("");
	}
	for(int i=1; i<=m; ++i){
		putchar('0');
	}
	puts("");
	puts("+");
	for(int i=1; i<=m; ++i){
		putchar('0');
	}
	puts("");
	for(int i=2; i<n; ++i){
		for(int j=1; j<=m; ++j){
			putchar('0'+((j&1)==0||mp[i][j]=='1'));
		}
		puts("");
	}
	for(int i=1; i<=m; ++i){
		putchar('1');
	}
	puts("");
	puts("-");
	for(int i=1; i<=m; ++i){
		putchar('0'+(mp[1][i]=='0'));
	}
	puts("");
	for(int i=2; i<n; ++i){
		for(int j=1; j<=m; ++j){
			putchar('1');
		}
		puts("");
	}
	for(int i=1; i<=m; ++i){
		putchar('0'+(mp[n][i]=='0'));
	}
	puts("");
}

void solve3_r(){
	puts("3");
	puts("+");
	for(int i=1; i<=n; ++i){
		putchar('1');
		for(int j=2; j<m; ++j){
			putchar('0'+((i&1)==1||mp[i][j]=='1'));
		}
		putchar('0');
		puts("");
	}
	puts("+");
	for(int i=1; i<=n; ++i){
		putchar('0');
		for(int j=2; j<m; ++j){
			putchar('0'+((i&1)==0||mp[i][j]=='1'));
		}
		putchar('1');
		puts("");
	}
	puts("-");
	for(int i=1; i<=n; ++i){
		putchar('0'+(mp[i][1]=='0'));
		for(int j=2; j<m; ++j){
			putchar('1');
		}
		putchar('0'+(mp[i][m]=='0'));
		puts("");
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",mp[i]+1);
	}
	if(n==1||m==1){
		L1::solve();
		return 0;
	}
	if(S12::solve()) return 0;
	if(m==2) solve3_c();
	else solve3_r();
	return 0;
}
