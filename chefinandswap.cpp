#include<iostream>

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
#define pb push_back
#define loop(i,n) for(i=0;i<n;i++)
#define loopk(i, n, k) for(i=k;i<n;i++)
#define test ll t; cin >> t; while(t--)

template<typename... T>
void read(T&... args) {
	((cin >> args), ...);
}

template<typename... T>
void write(T... args) {
	((cout << args << " "), ...);
}


ll sum(ll start, ll end)
{
    return ((start+end)*(end - start + 1))/2;
}

ll get_start(ll n)
{
    ll half = n%2 == 0 ? n/2: (n+1)/2;
    return half+1;
}

void testcase() {
	//Implementation goes here
	/*
	1,2,3 sum is 6 half 3 and one element which is equal to 3 so there are 2 choices to swap with
	1,2,3,4 sum is 10 half 5 and no element which is equal to 5
	1,2,3,4,5,6,7 half sum 14 5,6,7 is greater than half sum
	1,2,3,4,5,6,7,8 sum is 36 half sum is 18 and 6,7,8 sum is greater than half sum
	1,2,3,4,5,6,7,8,9,10,11 sum is 66 half is 33 last 4 elements ka sum is greater than half sum
	1,2,3,4,5,6,7,8,9,10,11,12 sum is 78 half is 34 last 4 elements ka sum is greater than half sum
	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 sum is 120 and half sum is 60 last 5 elements is greater than half sum
	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 sum is 136 and half sum is 68 last 5 elements sum is 70 which is greater than half sum
	3 -> 1 (4*1 - 1)
	4 -> 2 (4*1)
	7 -> 3 (4*2 - 1)
	8 -> 3 (4*2)
	11 -> 4 (4*3 - 1)
	12 -> 4 (4*3)
	15 -> 5 (4*4 - 1)
	16 -> 5 (4*4)
	*/
    ll n;
    read(n);
    ll _sum = sum(1, n);
    ll moves = 0;
    if(n == 3) moves = 2;
	else if (n == 4) moves = 2;
    else if (_sum % 2 == 0) {
	  ll temp = (n%2 == 0) ? (n/4) : ((n+1)/4);
	  moves = temp + 1;
    }
    cout << moves << endl;
}


int main() {
    ll t;
    read(t);
    while(t--) testcase();
	return 0;
}
