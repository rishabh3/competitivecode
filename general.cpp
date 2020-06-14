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

int get_nearest_max(vector<int> h, int n, int max) {
	int nearest_max_swaps=0;
	for(int i=0;i<n;i++){
		if(h[i]==max) {
			nearest_max_swaps = i;
			break;
		}
	}
	return nearest_max_swaps;
}

int get_nearest_min(vector<int> h, int n, int min) {
	int nearest_min=0;
	for(int j=n-1;j>=0;j--){
		if(h[j]==min) {
			nearest_min = j;
			break;
		}
	}
	return nearest_min;
}

int position_min(vector<int> &h, int n, int nearest_min){
	int swap = 0;
	for(int i=nearest_min;i<n-1;i++){
			int temp = h[i+1];
			h[i+1] = h[i];
			h[i] = temp;
			swap++;
	}
	return swap;
}

int position_max(vector<int> &h, int n, int nearest_max) {
	int swap = 0;
	for(int i=nearest_max;i>0;i--){
		int temp = h[i-1];
		h[i-1] = h[i];
		h[i] = temp;
		swap++;
	}
	return swap;
}


void testcase() {
	int n;
	scanf("%d", &n);
	vector<int> h(n);
	for(int i=0;i<n;i++) {
		scanf("%d", &h[i]);
	}
	int _max = *max_element(h.begin(), h.end());
	int _min = *min_element(h.begin(), h.end());
	int swap = 0;
	int nearest_max = get_nearest_max(h, n, _max);
	int nearest_min = get_nearest_min(h, n, _min);
	int nearest_max_swaps=nearest_max, nearest_min_swaps=n-1-nearest_min;
	int min_swap = min(nearest_min_swaps, nearest_max_swaps);
	if(min_swap == nearest_min_swaps) {
		swap += position_min(h, n, nearest_min);
		nearest_max = get_nearest_max(h,n,_max);
		swap += position_max(h, n, nearest_max);
	}
	else {
		swap += position_max(h, n, nearest_max);
		nearest_min = get_nearest_min(h,n,_min);
		swap += position_min(h, n, nearest_min);
	}
	//~ debug() << imie(nearest_max_swaps) << imie(nearest_min_swaps) << imie(min_swap) << imie(h);
	printf("%d\n", swap);
}


int main() {
	testcase();
	return 0;
}
