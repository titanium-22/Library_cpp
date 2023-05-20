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

// factorial -----------------
long long factorial(long long x) {
  long long res = 1;
  for (long long i = 1ll; i <= x; ++i) {
    res *= i;
  }
  return res;
}
// factorial -----------------

// get_primelist -----------------
vector<int> get_primelist(int MAX) {
  vector<int> is_prime(MAX+1, 1);
  is_prime[0] = 0;
  is_prime[1] = 0;
  for (int i = 2; i < sqrt(MAX)+1; ++i) {
    if (!is_prime[i]) continue;
    for (int j = i+i; j < MAX+1; j+=i) {
      is_prime[j] = 0;
    }
  }
  return is_prime;
}
// get_primelist -----------------

