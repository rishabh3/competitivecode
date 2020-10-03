#include<iostream>
#include<numeric>
#include<vector>
#include<map>
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

void push(vector<ll> &a,ll times, ll elem) {
	ll i;
	loop(i, times) {
		a.pb(elem);
	}
}

ll sol1(ll xor_elem, map<ll, pll> count) {
    ll res = -1;
    if(xor_elem == 0) {
        res = 0;
		vector<ll> t1;
		for(auto it=count.begin();it != count.end();it++) {
			pll p = it->second;
			ll times = abs(p.first - p.second)/2;
			if(p.first != p.second) {
				push(t1, times, it->first);
			}
		}
        sort(t1.begin(), t1.end());
        //debug() << imie(t1);
        res = accumulate(t1.begin(), t1.begin() + t1.size()/2, 0);
    }
    return res;
}

ll sol2(map<ll, pll> count) {
    ll res = 0;
    vector<ll> t1;
    for(auto it=count.begin();it != count.end();it++) {
        pll p = it->second;
        ll times = abs(p.first - p.second)/2;
        ll tot = p.first + p.second;
        if(tot%2 != 0) {
            res = -1;
            return res;
        }
        if(p.first != p.second) {
            push(t1, times, it->first);
        }
    }
    sort(t1.begin(), t1.end());
    res = accumulate(t1.begin(), t1.begin()+t1.size()/2,0);
    return res;
    return res;
}

ll sol3(ll xor_elem, ll n,vector<ll> a, vector<ll> b, map<ll, pll> count) {
    ll i1=0, i2=0;
    ll j1=n-1, j2=n-1;
    ll res = 0;
    if(xor_elem != 0) {
        return -1;
    }
    while(i1<j1) {
        //debug() << imie(count);
        if(a[i1] == b[i2]) {
            count[a[i1]].first--;
            count[a[i1]].second--;
            i1++;
            i2++;
        }
        if(a[j1] == b[j2]) {
            count[a[j1]].first--;
            count[a[j1]].second--;
            j1--;
            j2--;
        }
        if(a[i1] != b[i2]) {
            if(a[i1] < b[i2]) {
                res += a[i1];
                if(count[a[i1]].first < count[a[i1]].second) {
                    count[a[i1]].first++;
                    count[a[i1]].second--;
                    count[a[j1]].first--;
                    count[a[j1]].second++;
                    j1-=min(count[a[j1]].first, count[a[j1]].second);
                }
                else if(count[a[i1]].first > count[a[i1]].second) {
                    count[a[i1]].first--;
                    count[a[i1]].second++;
                    count[b[j2]].first++;
                    count[b[j2]].second--;
                    j2-=min(count[b[j2]].first, count[b[j2]].second);
                }
                i1 += min(count[a[i1]].first, count[a[i1]].second);
            }
            else if(a[i1] > b[i2]) {
                res += b[i2];
                if(count[b[i2]].first < count[b[i2]].second) {
                    count[b[i2]].first++;
                    count[b[i2]].second--;
                    count[a[j1]].first--;
                    count[a[j1]].second++;
                    j1-=min(count[a[j1]].first, count[a[j1]].second);
                }
                else if(count[b[i2]].first > count[b[i2]].second) {
                    count[b[i2]].first--;
                    count[b[i2]].second++;
                    count[b[j2]].first++;
                    count[b[j2]].second--;
                    j2-=min(count[b[j2]].first, count[b[j2]].second);
                }
                i2 += min(count[b[i2]].first, count[b[i2]].second);
            }

        }
    }
    return res;
}

ll sol4(ll xor_elem, ll n, vector<ll> a, vector<ll> b) {
    ll res = 0;
    if(xor_elem != 0) return -1;
    vector<ll> t1(2*n);
    auto it = set_symmetric_difference(a.begin(), a.begin()+n, b.begin(), b.begin()+n, t1.begin()); 
    t1.resize(it- t1.begin());
    //debug() << imie(t1);
    res = accumulate(t1.begin(), t1.begin()+t1.size()/2, 0);
    res /= 2;
    return res;
}

ll sol5(vector<ll> a, vector<ll> b, ll n, ll xor_elem) {
    ll i = 0, j = n-1, res = 0;
    if(xor_elem > 0) return -1;
    while(i < j) {
        if(a[i] == b[i]) {
            i++;
        }
        if(a[j] == b[j]) {
            j--;
        }
        if(a[i] != b[i]) {
            if(a[i] < b[i]) {
                res += a[i];
                ll temp = b[j];
                b[j] = a[i];
                a[i] = temp;
            }
            if(a[i] > b[i]) {
                res += b[i];
                ll temp = a[j];
                a[j] = b[i];
                b[i] = temp;
            }
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        j--;
        i++;
    }
    return res;
}

ll sol6(vector<ll> a, vector<ll> b, vector<ll> c, ll xor_elem,ll n) {
    vector<ll> temp;
    if(xor_elem != 0) return -1;
    //debug() << imie(a) << imie(b);
    for(int i=0;i < c.size();i++) {
        //debug() << imie(i%2==0);
        if(i%2 == 0) {
            // check element is there in first array
            bool is_present = binary_search(a.begin(), a.end(), c[i]);
            //debug() << imie(i) << imie(c[i]) << imie(is_present) << imie(a);
            if(!is_present) temp.pb(c[i]);
        }
        else {
            // check element is there in second array
            bool is_present = binary_search(b.begin(), b.end(), c[i]);
            //debug() << imie(i) << imie(c[i]) << imie(is_present) << imie(b);
            if(!is_present) temp.pb(c[i]);
        }
        //debug() << imie(temp);
    }
    //debug() << imie(temp);
    return accumulate(temp.begin(), temp.begin() + temp.size()/2, 0);
}

ll sol7(ll xor_elem, map<ll, pll> count) {
    vector<ll> a, b;
    if(xor_elem != 0) return -1;
    for(auto it=count.begin();it!=count.end();it++) {
        pll p = it->second;
        if(p.first > p.second) a.pb(it->first);
        else if(p.first < p.second) b.pb(it->first);    
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<ll>());
    ll i=0, j=0;
    ll res = 0;
    while(i < a.size() && j < b.size()) {
        res += min(a[i],b[j]);
        count[a[i]].first--;
        count[a[i]].second++;
        count[b[j]].first++;
        count[b[j]].second--;
        pll p2 = count[b[j]];
        pll p1 = count[a[i]];
        if(p1.first == p1.second) i++;
        if(p2.first == p2.second) j++;
    }
    return res;
}

ll sol8(ll xor_elem, vector<ll> a, vector<ll> b) {
    vector<ll> x, y;
    ll i =0, j =0;
    if(xor_elem != 0) return -1;
    while(i < a.size() && j < b.size()) {
        if(a[i] != b[j]) {
            if(a[i] < b[j]) {
                x.pb(a[i]);
                i++;
            }
            else {
                y.pb(b[j]);
                j++;
            }
        }
        else {
            i++;
            j++;
        }
    }
    if(i != a.size()) {
        while(i < a.size()) {
            x.pb(a[i]);
            i++;
        }
    }
    if(j != b.size()) {
        while(j < b.size()) {
            y.pb(b[j]);
            j++;
        }
    }
    // debug() << imie(x) << imie(y);
    sort(y.begin(), y.end(), greater<ll>());
    i = 0;
    ll res = 0;
    while(i < x.size()) {
        if(i%2 != 0) {
            //swap
            res += min(x[i],y[i]);
        }
        i++;
    }
    return res;
}

bool equal_pair(pll p1) {
    return p1.first == p1.second;
}

ll sol9(ll xor_elem, map<ll, pll> &count, ll min_elem) {
    if(xor_elem > 0) return -1;
    vector<ll> a, b;
    pll p1 = count[min_elem];
    pll p2 = count[min_elem];
    ll res = 0;
    ll swap_cnt = abs(p1.first - p1.second)/2;
    ll equalize_val = (p1.first + p1.second)/2;
    p1.first = equalize_val;
    p1.second = equalize_val;
    count[min_elem] = p1;
    for(auto it=count.begin();it != count.end();it++) {
        ll temp = it->first;
        pll ptemp = count[temp];
        if(temp != min_elem) {
            if(swap_cnt == 0) {
                if(!equal_pair(ptemp)) {
                    ll times = abs(ptemp.first - ptemp.second)/2;
                    if(ptemp.first > ptemp.second) {
                        push(a, times, temp);
                    }
                    else {
                        push(b, times, temp);
                    }
                }
            }
            else {
                if(p2.first < p2.second) {
                    while(swap_cnt && ptemp.first > ptemp.second) {
                        count[temp].first--;
                        count[temp].second++;
                        swap_cnt--;
                        res += min_elem;
                    }
                }
                else if(p2.first > p2.second) {
                    while(swap_cnt && ptemp.first < ptemp.second) {
                        count[temp].first++;
                        count[temp].second--;
                        swap_cnt--;
                        res += min_elem;
                    }
                }
            }
        }
    }
    ll i;
    loop(i, a.size()) {
        res += min(2*min_elem, min(a[i], b[i]));
    }
    return res;
}

ll sol10(ll n, ll xor_elem,vector<ll> a, vector<ll> b, map<ll, pll> count, ll min_elem) {
    if(xor_elem != 0) return -1;
    ll i =0, j=0, res = 0;
    while(i < n && j < n) {
        pll p1 = count[a[i]];
        pll p2 = count[b[j]];
        // debug() << imie(a);
        // debug() << imie(b);
        // debug() << imie(count);
        // debug() << imie(p1) << imie(p2) << imie(i) << imie(j) << imie(a[i]) << imie(b[j]) << imie(res);
        // cout << "======================================================================================" << endl;
        if(p1.first == p1.second) i++;
        if(p2.first == p2.second) j++;
        if(a[i] == b[j]) {
            i++;
            j++;
        }
        else {
            if(p1.first > p1.second) {
                if(p2.first > p2.second) j++;
                else if(p2.first < p2.second) {
                    res += min(2*min_elem, min(a[i],b[j]));
                    p1.first--;
                    p2.first++;
                    p1.second++;
                    p2.second--;
                    count[a[i]] = p1;
                    count[b[j]] = p2;
                    i++;
                    j++;
                }
            }
            else if(p1.first < p1.second) {
                if(p2.second > p2.first) j++;
                else if(p2.second < p2.first) {
                    res += min(2*min_elem, min(a[i], b[j]));
                    p1.first++;
                    p2.first--;
                    p1.second--;
                    p2.second++;
                    count[a[i]] = p1;
                    count[b[j]] = p2;
                    i++;
                    j++;
                }
            }
        }
    }
    return res;
}

ll sol11(ll xor_elem, vector<ll> a, ll min_elem) {
    if(xor_elem != 0) return -1;
    ll res = 0;
    for(ll i = 0;i < a.size() /2;i+=2) {
        res += a[i] < 2*min_elem ? a[i]: 2*min_elem;
    }
    return res;
}

void testcase() {
	ll n;
	read(n);
	vector<ll> a(n), b(n), c(2*n);
	// map<ll, pll> count;
	ll i;
	ll xor_elem = 0;
	loop(i, n) {
		read(a[i]);
		 // if(count.find(a[i]) == count.end()) {
		 // 	count[a[i]] = {1,0};	
		 // }
         // else {
		 // 	count[a[i]].first++;
    	 // }
		xor_elem ^= a[i];
	}
	loop(i, n) {
		read(b[i]);
		 // if(count.find(b[i]) == count.end()) {
		 // 	count[b[i]] = {0,1};
		 // }
		 // else {
		 // 	count[b[i]].second++;
		 // }
		xor_elem ^= b[i];
	}
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // i = 0;
    // ll j = 0;
    auto it = set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    c.resize(it-c.begin());
    // while(i < n && j < n) {
    //     if(a[i] == b[j]) {
    //         a[i] = 0;
    //         b[j] = 0;
    //         i++;
    //         j++;
    //     }
    //     else {
    //         if(a[i] < b[j]) i++;
    //         else if(a[i] > b[j]) j++;
    //     }
    // }
    // sort(a.begin(), a.end());
    // sort(b.begin(), b.end());
    ll res = 0;
    //debug() << imie(a) << imie(c) << imie(b);
    // if(c.size() != 0) { 
    //     sort(c.begin(), c.end());
    //     res = sol6(a, b, c, xor_elem, n);
    // }
    // ll res1 = sol1(xor_elem, count);
    // res = sol9(xor_elem, count, min(*min_element(a.begin(), a.end()), *min_element(b.begin(), b.end())));
    res = sol11(xor_elem, c, min(a[0], b[0]));
    // write(res, res1);
    write(res);
	cout << endl;
}


int main() {
	test{
		testcase();
	}
	return 0;
}
