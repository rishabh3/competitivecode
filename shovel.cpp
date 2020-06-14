#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<iterator>

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

map<int, vector<int>> mem;

void testcase() {
	int n, r;
	scanf("%d %d", &n, &r);
	int count = 0;
	if(n%10 == 0) {
		count = 1;
	}
	else {
		int rem = n%10;
		auto it = find(mem[rem].begin(), mem[rem].end(), r);
		if(it == mem[rem].end()) {
			it = find(mem[rem].begin(), mem[rem].end(), 0);
			int pos = distance(mem[rem].begin(), it);
			count+=(pos+1);
		}
		else {
			int pos = distance(mem[rem].begin(), it);
			count += (pos+1);
		}
	}
	cout << count << endl;
}


int main() {
	mem[1] = {1,2,3,4,5,6,7,8,9,0};
	mem[2] = {2,4,6,8,0};
	mem[3] = {3,6,9,2,5,8,1,4,7,0};
	mem[4] = {4,8,2,6,0};
	mem[5] = {5,0};
	mem[6] = {6,2,8,4,0};
	mem[7] = {7,4,1,8,5,2,9,6,3,0};
	mem[8] = {8,6,4,2,0};
	mem[9] = {9,8,7,6,5,4,3,2,1,0};
	testcase();
	return 0;
}
