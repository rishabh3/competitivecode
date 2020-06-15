#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {

/*sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);*/

template < class c > struct rge { c b, e; };
template < class c > rge<c> range(c i, c j) { return rge<c>{i, j}; }
template < class c > auto dud(c* x) -> decltype(cerr << *x, 0);
template < class c > char dud(...);

struct debug {
	~debug() { cerr << endl; }

	//eni(!=) cerr << boolalpha << i; ris; }        Part 1

	template < class c > typename \
	enable_if<sizeof dud<c>(0) != 1, debug&>::type operator<<(c i) {
		cerr << boolalpha << i;
		return * this;
	}

	//eni(==) ris << range(begin(i), end(i)); }     Part 2

	template < class c > typename \
	enable_if<sizeof dud<c>(0) == 1, debug&>::type operator<<(c i) {
		return * this << range(begin(i), end(i));
	}

	/*sim, class b dor(pair < b, c > d) {           Part 3
		ris << "(" << d.first << ", " << d.second << ")";
	}*/

	template < class c, class b > debug & operator << (pair < b, c > d) {
		return * this << "(" << d.first << ", " << d.second << ")";
	}

	/*sim dor(rge<c> d) {                           Part 4
		*this << "[";
		for (auto it = d.b; it != d.e; ++it)
			*this << ", " + 2 * (it == d.b) << *it;
		ris << "]";
	}*/

	template < class c > debug & operator <<(rge<c> d) {
		*this << "[";
		for (auto it = d.b; it != d.e; ++it)
			*this << ", " + 2 * (it == d.b) << *it;
		return * this << "]";
	}

};

#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define MAX 1e+9

void print_answer(vector<vector<int>> mem) {
	int min_val = MAX;
	for(auto it=mem.begin();it!=mem.end();it++) {
		vector<int> temp = *it;
		if(temp.size() < min_val) min_val = temp.size();
	}
	cout << min_val << endl;
	if(min_val != 0) {
		for(int i=0;i<min_val;i++) {
			cout << mem[0][i] << " " << mem[1][i] << " " << mem[2][i] << endl;
		}
	}
}

void testcase() {
	int n;
	scanf("%d", &n);
	vector<int> t(n);
	for(int i = 0;i < n;i++) {
		scanf("%d", &t[i]);
	}
	vector<vector<int>> mem = {{}, {}, {}};
	for(int i=0;i < n;i++) {
		mem[t[i]-1].push_back(i+1);
	}
	//~ debug() << imie(mem);
	print_answer(mem);
}


int main() {
	testcase();
	return 0;
}
