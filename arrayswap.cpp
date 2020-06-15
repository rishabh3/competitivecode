#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>


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


void testcase() {
	int n, k;
	scanf("%d %d", &n, &k);
	vector<int> a(n), b(n);
	int suma=0, sumb=0;
	for(int i=0;i<n;i++) {
		scanf("%d", &a[i]);
		suma += a[i];
	}
	for(int i=0;i<n;i++) {
		scanf("%d", &b[i]);
		sumb += b[i];
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end(), greater<int>());
	//~ debug() << imie(a) << imie(b);
	for(int i=0;i<k;i++) {
		if(a[i] < b[i]) { // Dont do blind swap first check
			int temp = a[i];
			a[i] = b[i];
			b[i] = temp;
		}
	}
	//~ debug() << imie(a) << imie(b);
	int sum_after_swaps = accumulate(a.begin(), a.end(), 0);
	int res = suma > sum_after_swaps ? suma : sum_after_swaps; // We check new sum is greater than earlier sum before swaps
	cout << res << endl;
}


int main() {
	int test;
	scanf("%d", &test);
	while(test--) testcase();
	return 0;
}
