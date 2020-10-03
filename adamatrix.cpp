#include<iostream>
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
#define test ll t; cin >> t; while(t--)

template<typename... T>
void read(T&... args) {
	((cin >> args), ...);
}

template<typename... T>
void write(T... args) {
	((cout << args << " "), ...);
}

bool row_element(vector<vector<ll>> matrix, ll n)
{
    return matrix[0][n-1] == n;
}

ll count_misplaced_elements(vector<vector<ll>> matrix, ll n, bool elem)
{
    ll count = 0;
    if(elem)
    {
        for(ll i = 1;i < n;i++)
        {
            // debug() << imie(matrix[0][i]) << imie(count) << imie(i+1);
            if(matrix[0][i] != i+1)
            {
                count++;
            }
        }
    }
    else
    {
    
        for(ll i = 1;i < n;i++)
        {
            // debug() << imie(matrix[0][i]) << imie(count) << imie(i+1);
            if(matrix[i][0] != i+1)
            {
                count++;
            }
        }
    }
    return count > 0 ? 1: 0;
}

ll count_operations(vector<vector<ll>> matrix, ll n)
{
    vector<ll> row = matrix[0];
    bool prev_elem_in_col = row[1] != 2;
    ll op = 0;
    for(ll i = 2;i < n;i++)
    {
        bool current_elem_in_col = row[i] != i+1;
        // debug() << imie(current_elem_in_col) << imie(prev_elem_in_col) << imie(op);
        op += current_elem_in_col == prev_elem_in_col ? 0 : 1;
        prev_elem_in_col = current_elem_in_col;
    }
    if(row[n-1] != n) op++;
    return op;
}

void testcase() {
	//Implementation goes here
    ll n;
    read(n);
    vector<vector<ll>> matrix;
    for(int i = 0;i < n;i++)
    {
        vector<ll> v1;
        for(int j = 0;j < n;j++)
        {
            ll temp;
            read(temp);
            v1.push_back(temp);
        }
        matrix.push_back(v1);
    }
    // debug() << imie(matrix);
    ll op = count_operations(matrix, n);
    // debug() << imie(op);
    cout << op << endl;
}


int main() {
    ll t;
    read(t);
    while(t--) testcase();
	return 0;
}
