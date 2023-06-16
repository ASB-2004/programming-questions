#ifdef ONPC
#define _GLIBCXX_DEBUG
// #include "bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

#define sz(a) ((int)((a).size()))
#define char unsigned char
#define pi 3.141592653589793238

using namespace std;
// mt19937 rnd(239);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;
#ifdef ONPC
#include "debug.h"
#else
#define dbg(...)
#endif
template <int MODULO>
struct ModularInt {
    int value;
    ModularInt(ll llvalue)
        : value(llvalue % MODULO)
    {
        if (value < 0)
            value += MODULO;
    }
    ModularInt(const ModularInt<MODULO>& other)
        : value(other.value)
    {
    }
    ModularInt()
        : value(0)
    {
    }
    inline void operator+=(ModularInt<MODULO> other)
    {
        value += other.value;
        if (value >= MODULO)
            value -= MODULO;
    }
    inline ModularInt<MODULO> operator+(ModularInt<MODULO> other) const
    {
        return ModularInt<MODULO>(value + other.value >= MODULO ? value + other.value - MODULO : value + other.value);
    }
    inline void operator-=(ModularInt<MODULO> other)
    {
        value -= other.value;
        if (value < 0) {
            value += MODULO;
        }
    }
    inline ModularInt<MODULO> operator-(ModularInt<MODULO> other) const
    {
        return ModularInt<MODULO>(value - other.value < 0 ? value - other.value + MODULO : value - other.value);
    }
    inline ModularInt<MODULO> operator-() const { return ModularInt<MODULO>(value == 0 ? value : MODULO - value); }
    inline ModularInt<MODULO>& operator++()
    {
        ++value;
        if (value == MODULO) {
            value = 0;
        }
        return *this;
    }
    inline ModularInt<MODULO> operator++(int)
    {
        ModularInt<MODULO> old(*this);
        ++value;
        if (value == MODULO) {
            value = 0;
        }
        return old;
    }
    inline ModularInt<MODULO>& operator--()
    {
        --value;
        if (value == -1) {
            value = MODULO - 1;
        }
        return *this;
    }
    inline ModularInt<MODULO> operator--(int)
    {
        ModularInt<MODULO> old(*this);
        --value;
        if (value == -1) {
            value = MODULO - 1;
        }
        return old;
    }
    inline ModularInt<MODULO> operator*(ModularInt<MODULO> other) const { return ModularInt<MODULO>(1LL * value * other.value); }
    inline void operator*=(ModularInt<MODULO> other) { value = 1LL * value * other.value % MODULO; }
    friend ModularInt<MODULO> binpow(ModularInt<MODULO> a, ll bll)
    {
        if (a.value == 0) {
            return ModularInt<MODULO>(bll == 0 ? 1 : 0);
        }
        int b = bll % (MODULO - 1);
        int ans = 1;
        while (b) {
            if (b & 1) {
                ans = 1LL * ans * a.value % MODULO;
            }
            a.value = 1LL * a.value * a.value % MODULO;
            b >>= 1;
        }
        return ModularInt<MODULO>(ans);
    }
    inline ModularInt<MODULO> inv() const { return binpow(*this, MODULO - 2); }
    inline ModularInt<MODULO> operator/(ModularInt<MODULO> other) const { return (*this) * other.inv(); }
    inline void operator/=(ModularInt<MODULO> other) { value = 1LL * value * other.inv().value % MODULO; }
    inline bool operator==(ModularInt<MODULO> other) const { return value == other.value; }
    inline bool operator!=(ModularInt<MODULO> other) const { return value != other.value; }
    explicit operator int() const { return value; }
    explicit operator bool() const { return value; }
    explicit operator long long() const { return value; }
    friend istream& operator>>(istream& inp, ModularInt<MODULO>& mint)
    {
        inp >> mint.value;
        return inp;
    }
    friend ostream& operator<<(ostream& out, const ModularInt<MODULO>& mint)
    {
        out << mint.value;
        return out;
    }
};
const int MOD = 1000000007;

typedef ModularInt<MOD> MInt;
vector<MInt> fact(1, 1);
vector<MInt> inv_fact(1, 1);

MInt C(int n, int k)
{
    if (k < 0 || k > n) {
        return 0;
    }
    MInt t = 1;
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(t / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
int n;
int m;
const int N = 1e5 + 3;
vector<int> a(N);
MInt rec(vector<int> in)
{

    bool flag = true;
    for (int i = 0; i < sz(in); i++) {
        if (in[i] == 0) {
            flag = false;
        }
    }
    bool flag2 = true;
    for (int i = 0; i < n - 1; i++) {
        if (abs(in[i] - in[i + 1]) >= 2) {
            flag2 = false;
        }
    }
    if (!flag2 && flag) {
        return MInt(0);
    }
    if (flag == true) {
        return MInt(1);
    }
    MInt ans = 0;
    if (a[0] == 0) {
        for (int i = 0; i < m; i++) {
            in[0] = i + 1;
            ans += rec(in);
        }
        return ans;
    }
    for (int i = 0; i < sz(in); i++) {
        if (in[i] == 0) {
            in[i] = a[i - 1];
            ans += rec(in);
            if (a[i - 1] + 1 <= m) {
                in[i] = a[i - 1] + 1;
                ans += rec(in);
            }
            if (a[i - 1] - 1 >= 1) {
                in[i] = a[i - 1] - 1;
                ans += rec(in);
            }
        }
    }
    return ans;
};

int solve()
{
    cin >> n >> m;
    a.resize(n);
    for (int& val : a) {
        cin >> val;
    }
    MInt gans = rec(a);
    cout << gans << endl;
    return 0;
}

int32_t main()
{
    // sieve(2e5+10);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int TET = 1;
    for (int i = 1; i <= TET; i++) {
        if (solve()) {
            break;
        }
#ifdef ONPC
        cout << "__________________________" << endl;
#endif
    }
#ifdef ONPC
    cerr << endl
         << "finished in " << clock() * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
#endif
}
