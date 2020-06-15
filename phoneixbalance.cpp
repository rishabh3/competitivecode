#include<iostream>
#include<vector>

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
	int n;
	scanf("%d", &n);
	vector<ll> powers(n);
	ll sum1 = 0, sum2 = 0;
	for(int i=n; i>0;i--) {
		powers[n-i] = (1<<i);
	}
	// Highest and second highest will never be together
	sum1 += powers[0];
	sum2 += powers[1];
	int size1=1, size2=1;
	//~ debug() << imie(powers);
	for(int i=2;i <n;i++) {
		ll temp1 = llabs((sum1+powers[i])-sum2);
		ll temp2 = llabs(sum1-(sum2+powers[i]));
		ll minval = min(temp1, temp2);
		ll diff = llabs(size1-size2);
		if(diff == (n-i)) {
			if(size1 < size2) {
				sum1+=powers[i];
				size1++;
			}
			else {
				sum2+=powers[i];
				size2++;
			}
		}
		else {
			if(minval == temp1) {
				sum1+=powers[i];
				size1++;
			}
			else {
				sum2+=powers[i];
				size2++;
			}
		}
		//~ debug() << imie(powers[i]) << imie(sum1) << imie(sum2) << imie(size1) << imie(size2) << imie(n-i) << imie(llabs(size2-size1));
	}
	cout << llabs(sum1-sum2) << endl;
}


int main() {
	int test;
	scanf("%d", &test);
	while(test--) testcase();
	return 0;
}
