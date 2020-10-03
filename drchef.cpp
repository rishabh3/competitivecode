#include<iostream>
#include<numeric>
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
#define MAX 10e+9
#define test ll t; cin >> t; while(t--)

template<typename... T>
void read(T&... args) {
	((cin >> args), ...);
}

template<typename... T>
void write(T... args) {
	((cout << args << " "), ...);
}

ll get_num_days(vector<ll> pop) {
    ll count = 0;
    for(ll it: pop) {
        if(it != 0) count++;  
    }
    return count;
}

pair<ll, ll>  get_element(vector<ll> pop, ll k) {
    ll res = 0;
    ll res1 = MAX;
    for(ll i: pop) {
        if(i > k) {
            if(i < res1) res1 = i;
        }
        else {
            if(i > res) res = i;
        }
    }
    return {res, res1};
}


void testcase() {
    ll n, x;
    read(n, x);
    vector<ll> pop(n);
    ll i;
    loop(i, n) {
        read(pop[i]);
    }
    ll days = 0;
    sort(pop.begin(), pop.end());
    ll max_elem = pop[pop.size()-1];
    // debug() << imie(max_elem) << imie(x);
    if(x >= max_elem) {
        days = n;
        loop(i, n) {
            pop[i] = 0;
        }
    }
    else {
        i = 0;
        while(true) {
            // debug() << imie(x) << imie(pop) << imie(days);
            if(x >= max_elem || i >= n) {
                break;
            }
            if(x < pop[i]) {
                x *= 2;
                days++;
            }
            else {
                if(2*pop[i] >= x) {
                    x = 2*pop[i];
                    days++;
                    pop[i] = 0;
                }
                i++;
            }
        }
    }
    days += get_num_days(pop);
    write(days);
    cout << endl;
}


int main() {
    test {
	    testcase();
    }
	return 0;
}
