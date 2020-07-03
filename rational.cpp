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
#define pb push_back
#define loop(i,n) for(i=0;i<n;i++)
#define loopk(i, n, k) for(i=k;i<n;i++)

template<typename... T>
void read(T&... args) {
	((cin >> args), ...);
}

template<typename... T>
void write(T... args) {
	((cout << args << " "), ...);
}

void testcase() {
    int n, k;
    read(n,k);
    vector<ll> bag(n);
    int i;
    loop(i, n) {
        read(bag[i]);
    }
    sort(bag.begin(), bag.end());
    vector<int> nums(k);
    int x = 0;
    loop(i, k) {
        read(nums[i]);
        x += nums[i] - 1;
    }
    sort(nums.begin(), nums.end(), greater<int>());
    ll sum = 0;
    ll max_elem;
    ll min_elem;
    int prev = 0;
    i = 0;
    int j = 0;
    int m = x;
    while(i < k) {
       // debug() << imie(i) << imie(j) << imie(m) << imie(max_elem) << imie(min_elem);
        max_elem = bag.at(m);
        if(j >= x) j = m;
        min_elem = bag.at(j);
        prev = nums.at(i)-1;
        sum += (max_elem + min_elem);
        j = j+prev;
        m++;
        i++;
        //debug() << imie(max_elem) << imie(min_elem) << imie(sum) << imie(j) << imie(m) << imie(i);
    }
    write(sum);
    cout << endl;
}


int main() {
    int test;
    read(test);
    while(test--)
	testcase();
	return 0;
}
