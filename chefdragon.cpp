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
#define pll pair<ll, ll>
#define test ll t; cin >> t; while(t--)

template<typename... T>
void read(T&... args) {
	((cin >> args), ...);
}

template<typename... T>
void write(T... args) {
	((cout << args << " "), ...);
}

ll getMid(ll start, ll end) {
    return start + (end-start)/2;
}

pll constructSegTree(vector<ll> a,vector<ll> b, ll start, ll end, vector<pll> &segTree, ll treeNode) {
    // debug() << imie(a) << imie(b) << imie(start) << imie(end) << imie(segTree) << imie(treeNode);
    if(start == end) {
        segTree[treeNode] = {b[start], a[start]};
        return segTree[treeNode];
    }
    ll mid = getMid(start, end);
    pll p1 = constructSegTree(a, b, start, mid, segTree, 2*treeNode);
    pll p2 = constructSegTree(a, b, mid+1, end, segTree, 2*treeNode+1);
    segTree[treeNode] = {p1.first+p2.first, max(p1.second, p2.second)}; 
    return segTree[treeNode];
}

void updateTree(vector<ll> &a, vector<pll> &segTree, ll start, ll end, ll index, ll value, ll treeNode) {
    if(index < start || index > end) return;
    if(start == end) {
        a[index] = value;
        segTree[treeNode].first = value;
    }
    else {
        ll mid = getMid(start, end);
        if(index >= start && index <= mid)
            updateTree(a, segTree, start, mid, index, value, 2*treeNode);
        else
            updateTree(a, segTree, mid+1, end, index, value, 2*treeNode+1);
        segTree[treeNode].first = segTree[2*treeNode].first + segTree[2*treeNode+1].first;
        segTree[treeNode].second = max(segTree[2*treeNode].second, segTree[2*treeNode+1].second);
    }
}

ll Max_Util(vector<pll> segTree, ll start, ll end, ll l, ll r, ll treeNode) {
    // debug() << imie(segTree) << imie(start) << imie(end) << imie(l) << imie(r) << imie(treeNode);
    if (l <= start && r >= end) return segTree[treeNode].second;
    if (end < l || start > r) return -1;
    ll mid = getMid(start, end);
    return max(Max_Util(segTree, start, mid, l, r, 2*treeNode), Max_Util(segTree, mid+1, end, l, r, 2*treeNode+1));
}

ll getMax(vector<pll> segTree, ll n, ll l, ll r) {
    if(l < 1 || r > n) return -1;
    if(l > r)
        return Max_Util(segTree, 1, n, r, l, 1);
    return Max_Util(segTree, 1, n, l, r, 1);
}

pll Query_Left(vector<pll> segTree, ll start, ll end, ll l, ll r, ll treeNode) {
    // debug() << imie(segTree) << imie(start) << imie(end) << imie(l) << imie(r) << imie(treeNode);
    if(l <= start && r >= end) return segTree[treeNode];
    if(end < l || start > r) return {0, -1};
    ll mid = getMid(start, end);
    pll p1 = Query_Left(segTree, start, mid, l, r, 2*treeNode);
    pll p2 = Query_Left(segTree, mid+1, end, l, r, 2*treeNode+1);
    // If left pair has greater height than right pair then sum both
    if(p1.second > p2.second) 
        return {p1.first+p2.first, p1.second};
    // Otherwise just return whatever is on right
    return p2;
}

pll Query_Right(vector<pll> segTree, ll start, ll end, ll l, ll r, ll treeNode) {
    // debug() << imie(segTree) << imie(start) << imie(end) << imie(l) << imie(r) << imie(treeNode);
    if(l <= start && r >= end) return segTree[treeNode];
    if(end < l || start > r) return {0, -1};
    ll mid = getMid(start, end);
    pll p1 = Query_Right(segTree, mid+1, end, l, r, 2*treeNode+1);
    pll p2 = Query_Right(segTree, start, mid, l, r, 2*treeNode);
    // If left pair has greater height than right pair then sum both
    if(p1.second > p2.second) return {p1.first+p2.first, p1.second};
    // Otherwise just return whatever is on right
    return p2;
}

ll query(vector<pll> segTree, ll n, ll l, ll r) {
    // debug() << imie(segTree) << imie(l) << imie(r) << imie(n);
    if(l < 1 || r > n) return -1;
    pll p1;
    if(l < r) {
        p1 = Query_Left(segTree, 1, n, l, r, 1);
        return p1.first; 
    }
    p1 = Query_Right(segTree, 1, n, r, l, 1);
    return p1.first; 
}

void updateBit(vector<pll> &tree, ll n, ll i, vector<ll> p, vector<ll> a) {
    ll temp = i+1;
    while(temp <= n) {
        tree[temp].first += a[i];
        tree[temp].second = max(tree[temp].second, p[i]);
        temp += temp & (-temp);
    }
}

void queryMax(vector<pll> &tree, ll i) {
    ll sum = 0;
    ll temp = temp + 1;
    while(temp > 0) {
        sum += tree[temp].first;
        temp -= temp & (-temp);
    }
}

pll constructBitTree(vector<ll> a, vector<ll> p, vector<pll> &tree, ll n) {
    for(ll i= 1;i <= n;i++) {
        tree[i] = {0, 0};
    }

    for(ll i= 1;i <= n;i++) {
        updateBit(tree, n, i, p, a);
    }
}


void testcase() {
	//Implementation goes here
    ll n, q;
    read(n, q);
    vector<ll> p(n+1), a(n+1);
    vector<pll> segTree(2*n);
    ll i; 
    for(i=1;i<=n;i++) {
        read(p[i]);
    }
    for(i=1;i<=n;i++) {
        read(a[i]);
    }
    constructSegTree(p,a, 1, n, segTree, 1);
    debug() << imie(segTree);
    int qtype;
    ll b, c, res;
    while(q--) {
        read(qtype, b, c);
        // debug() << imie(qtype) << imie(b) << imie(c);
        if(qtype == 1) {
            updateTree(a, segTree, 1, n, b, c, 1);
        }
        else {
            if(b == c) {
                res = a[b];
            }
            else {
                ll maxElem = getMax(segTree,n,b,c);
                // debug() << imie(maxElem);
                if(p[b] != maxElem) {
                    res = -1;
                }
                else {
                    res = a[b];
                    // debug() << imie(res);
                    ll start = b > c ? b-1: b+1;
                    // debug() << imie(start) << imie(b) << imie(c);
                    res += query(segTree, n, start, c);
                }
                write(res);
                cout << endl;
            }
        }
    }
}


int main() {
    testcase();
	return 0;
}
