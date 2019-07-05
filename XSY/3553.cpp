#include <iostream>
#include <string>
#include <bitset>
#include <cassert>
#include <vector>
#include "game.h"

static const int N=5300;
static int n,dep,cnt1,lenq[12];
static std::vector <std::bitset <N> > qry[12];
static std::string ans;

static int calc1(std::bitset <N> &bs){
	//1表示选中而不是询问字符串包含1
	static std::string str;
	str.resize(n);
	int tot=0;
	for(int i=0; i<n; ++i){
		str[i]='0'+(bs[i]^1);
		tot+=bs[i];
	}
	int res=guess(str);
	assert(((tot+cnt1-res)&1)==0);
	return (tot+cnt1-res)>>1;
}

template <class T>//std::vector <std::bitset <N> >
static void merge(const T &s1,T &s2,const int len){
	static std::bitset <N> t1,t2,t3;
	const int n=s1.size();
	t1.reset(),t2.reset(),t3.reset();
	for(int i=0; i<len; ++i){
		t1.set(i);
		t2.set(i+len);
	}
	for(int i=0; i<n-1; ++i){
		s2.push_back(s1[i]|s1[i]<<len);
		t3.set(i+(len<<1),1);
		s2.push_back((s1[i]^t1)|s1[i]<<len|t3);
		t3.set(i+(len<<1),0);
	}
	for(int i=0; i<n; ++i){
		t3.set(i+(len<<1));
	}
	s2.push_back(t1);
	s2.push_back(t1|t2|t3);
}

static void get_qry(){
	std::bitset <N> tmp;
	tmp.set(0);
	qry[0].push_back(tmp);
	lenq[0]=1;
	while(lenq[dep]<n){
		merge(qry[dep],qry[dep+1],lenq[dep]);
		lenq[dep+1]=lenq[dep]*2+(1<<dep)-1;
		++dep;
	}
}

static void solve(const int l,const int r,const int d,std::vector <int> &res){
	if(l==r){
		ans[l]=res[0]+'0';
		return;
	}
	std::vector <int> res1,res2;
	assert((int)res.size()==1<<d);
	const int len=lenq[d-1];
	int sz_l=res[res.size()-2],sz=res[res.size()-1],sz_c=0;
	for(int i=0; i<(int)res.size()-2; i+=2){
		int a1=res[i],a2=res[i+1],res_c=(a1+a2-sz_l)&1;
		sz_c+=res_c;
		ans[l+len*2+(i>>1)]=res_c+'0';
		res1.push_back(a1-((a1+a2-sz_l)>>1));
		res2.push_back((a1+a2-sz_l)>>1);
	}
	std::vector <int> ().swap(res);
	res1.push_back(sz_l);
	res2.push_back(sz-sz_l-sz_c);
	solve(l,l+len-1,d-1,res1);
	solve(l+len,l+len*2-1,d-1,res2);
}

std::string game(const int n,const int useless1){
	::n=n;
	cnt1=guess(std::string(n,'1'));
	ans.resize(n);
	get_qry();
	std::vector <int> res;
	for(int i=0; i<(int)qry[dep].size(); ++i){
		res.push_back(calc1(qry[dep][i]));
	}
	solve(0,n-1,dep,res);
	return ans;
}
