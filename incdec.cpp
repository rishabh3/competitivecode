#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>

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

bool verify(set<ll> a, map<ll, int> x, ll max_elem) {
    if(x[max_elem] > 1) return false;
    for(auto it = a.begin();it != a.end(); it++) {
        if(x[*it] > 2) return false;
    }
    return true;
}

void testcase() {
    ll n;
    read(n);
    vector<ll> a(n);
    set<ll> b;
    map<ll, int> p;
    ll i;
    loop(i, n) {
        read(a[i]);
        b.insert(a[i]);
        if(p.find(a[i]) == p.end()) p[a[i]] = 1;
        else p[a[i]]++;
    }
    if(a.size() == b.size()) {
        sort(a.begin(), a.end());
        puts("YES");
        loop(i,n) {
            write(a[i]);
        }
        cout << endl;
    }
    else {
        if(verify(b,p,*max_element(a.begin(), a.end()))) {
            puts("YES");
            for(auto it=b.begin();it!=b.end();it++) {
                write(*it);
            }
            for(auto it = b.rbegin();it!=b.rend();it++) {
                if(p[*it] >1) {
                    write(*it);
                }
            }
            cout << endl;
        }
        else {
            puts("NO");
        }
    }
}


int main() {
    int test;
    read(test);
    while(test--)
	testcase();
	return 0;
}
