#include<iostream>
#include<vector>
#include<string>
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

bool checkAndPass(vector<string> &h) {
	string to_find = "OO";
	string to_replace_with = "++";
	for(int i=0;i<h.size();i++) {
		string temp = h[i];
		size_t found = temp.find(to_find);
		if(found != string::npos) {
			// Found;
			temp.replace(found, 2, to_replace_with);
			h[i] = temp;
			return true;
		}
	}
	return false;
}

void testcase() {
	int n;
	scanf("%d", &n);
	vector<string> h;
	for(int i=0;i < n;i++) {
		string temp;
		cin >> temp;
		h.push_back(temp);
	}
	if(checkAndPass(h)) {
		puts("YES");
		for(auto it=h.cbegin();it!=h.cend();it++) {
			cout << *it << endl;
		}
	}
	else puts("NO");
}


int main() {
	testcase();
	return 0;
}
