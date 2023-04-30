long long pow(long long a, long long b, long long mod) {
  long long res = 1ll;
  while (b) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

long long factorial(long long x) {
  long long res = 1;
  for (long long i = 1; i <= x; ++i) {
    res *= i;
  }
  return res;
}
