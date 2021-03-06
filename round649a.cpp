#include<iostream>
#include<vector>
#include<numeric>
#include<map>


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

vector<int> arr;

bool check_div(int a, int x){
	return a%x != 0;
}

int maxsubarrlen(vector<int> a, int n, int x, int sum){
	if(sum%x!=0) return n;
	int s = 0, sol = -1;
	for(int i=1;i<=n;i++) {
		s = (s+a[i])%x;
		if(s) {
			sol = max(sol, i); // Take the prefix
			sol = max(sol, n-i); // Dont take the prefix
		}
	}
	return sol;
}

void testcase() {
	int n, x;
	scanf("%d %d", &n, &x);
	arr.clear();
	arr.resize(n+1);
	for(int i=1;i <= n;i++) {
		scanf("%d", &arr[i]);
	}
	int cnt = maxsubarrlen(arr, n, x, accumulate(arr.begin()+1, arr.end(), 0));
	printf("%d\n", cnt);
}


int main() {
	int test;
	scanf("%d", &test);
	for(int i = 0;i < test;i++) {
		testcase();
	}
	return 0;
}
