long long pow_mod(long long a, long long b, long long mod) {
  long long res = 1ll;
  while (b) {
    if (b & 1ll) res = res * a % mod;
    a = a * a % mod;
    b >>= 1ll;
  }
  return res;
}

long long pow(long long a, long long b) {
  long long res = 1ll;
  while (b) {
    if (b & 1ll) res *= a;
    a *= a;
    b >>= 1ll;
  }
  return res;
}

long long factorial(long long x) {
  long long res = 1;
  for (long long i = 1ll; i <= x; ++i) {
    res *= i;
  }
  return res;
}
