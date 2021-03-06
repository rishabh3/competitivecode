#include<iostream>
#include<algorithm>
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
    int m, n;
    read(n, m);
    vector<ll> seq(n);
    int i;
    int max_len = 0;
    loop(i,n) {
        read(seq[i]);
    }
    if(m > *max_element(seq.begin(), seq.end()) || m < *min_element(seq.begin(), seq.end()) || find(seq.begin(), seq.end(), m) != seq.end()) {
        max_len = -1;
    }
    else {
        i = 0;
        int j = n-1;
        max_len = n;
        while(i < j) {
            if(seq[i] < m && seq[j] > m) {
                i++;
                j--;
            }
            else if(seq[i] > m) {
                max_len -= (i+1);
                //int temp = max(i+1, max_len);
                //if(temp != max_len) {
                //    max_len = temp;
                //    break;
                //}
                max_len = max(i+1, max_len);
                i++;
            }
            else if(seq[j] < m) {
                max_len -= (n-j);
                //int temp = max(n-j, max_len);
                //if(temp != max_len) {
                //    max_len = temp;
                //    break;
                //}
                max_len = max(n-j, max_len);
                j--;
            }
        }
    }
    write(max_len);
    cout << endl;
}


int main() {
    int test;
    read(test);
    while(test--)
	testcase();
	return 0;
}
