#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
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

int count_bit(ll a) {
    return (int)log2(a)+1;
}

pair<int, int> findMaxEntry(map<int, int> sampleMap) {
    pair<int, int> entryWithMaxValue = make_pair(0, 0);
    map<int, int>::iterator currentEntry;
    for (currentEntry = sampleMap.begin(); 
         currentEntry != sampleMap.end(); 
         ++currentEntry) {
        if (currentEntry->second 
            > entryWithMaxValue.second) { 
  
            entryWithMaxValue 
                = make_pair( 
                    currentEntry->first, 
                    currentEntry->second); 
        } 
    }
    return entryWithMaxValue;
}

int countSetBits(ll n) {
    int count = 0;
    while(n) {
        n &= (n-1);
        count++;
    }
    return count;
}

void testcase() {
    int n,k;
    read(n,k);
    vector<ll> a(n);
    int i;
    map<int, int> x;
    ll maxval = 0;
    loop(i, n) {
        read(a[i]);
        int cbit = count_bit(a[i]);
        int csetbit = countSetBits(a[i]);
        if(csetbit == k && maxval < a[i]) maxval = a[i];
        if(x.find(cbit) == x.end()) x[cbit] = 1;
        else x[cbit]++;
    }
    //debug() << imie(maxval);
    pair<int, int> max_pair = findMaxEntry(x); 
    int mval = max_pair.second;
    ll res;
    if(maxval == 0 && mval == k) {
        res = (1 << k) - 1;
    }
    else if(maxval == 0 && k==1) {
        res = (1 << (mval-1));
    }
    else {
        res = maxval;
    }
    write(res);
    cout << endl;
}


int main() {
    int test;
    read(test);
    while(test--)
	testcase();
	return 0;
}
