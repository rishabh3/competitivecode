#include<iostream>
#include<vector>
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
#define ll long long int

void testcase() {
	//~ a+b=x
	//~ b+c=y
	//~ c-a=y-x
	//~ a+c = z
	//~ c = (y-x+z)/2
	//~ a = (2z - (y-x+z))/2 => (z-y+x)/2
	//~ b = (2x-(z-y+x))/2 => (x-z+y)/2
	// Sort the given four numbers
	vector<ll> n(4);
	for(int i=0;i<4;i++) scanf("%lld", &n[i]);
	sort(n.begin(), n.end());
	ll a = (n[2]-n[1]+n[0])/2;
	ll b = (n[0]-n[2]+n[1])/2;
	ll c = (n[1]-n[0]+n[2])/2;
	cout << a << " " << b << " " << c << endl;
}


int main() {
	testcase();
	return 0;
}
