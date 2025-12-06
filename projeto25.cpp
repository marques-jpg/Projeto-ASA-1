#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Read number of internal nodes
  int n;
  if (!(cin >> n)) return 0;

  // Arrays of weights P and character types C with sentinel at both ends
  vector<unsigned long long> P(n + 2);
  vector<char> C(n + 2);
  P[0] = P[n+1] = 1;    // sentinel weights
  C[0] = C[n+1] = 'T';  // sentinel types

  // Read internal weights
  for (int i = 1; i <= n; ++i) {
    if (!(cin >> P[i])) {
      return 0;
    }
  }

  // Read type string and fill C[1..n]
  string s;
  if (!(cin >> s)) return 0;
  if ((int)s.size() != n) return 0;
  for (int i = 1; i <= n; ++i) C[i] = s[i-1];

  // N is total number of positions including sentinels
  int N = n + 2;
  vector<int> type(N);

  // Map character type to integer code
  auto mapChar = [](char x)->int {
    if (x == 'P') return 0;
    if (x == 'N') return 1;
    if (x == 'A') return 2;
    if (x == 'B') return 3;
    return 4; // fallback
  };
  for (int i = 0; i < N; ++i) type[i] = mapChar(C[i]);

  // Static table for affinity/function between types
  static const int AfTable[5][5] = {
    {1,3,1,3,1},
    {5,1,0,1,1},
    {0,1,0,4,1},
    {1,3,2,3,1},
    {1,1,1,1,1}
  };

  // Affinity accessor
  auto Af = [&](int a, int b)->int { return AfTable[a][b]; };

  // Flatten 2D (l,r) index into 1D for dp and parent arrays
  auto idx = [&](int l, int r)->size_t { return (size_t)l * (size_t)N + (size_t)r; };
  vector<unsigned long long> dp((size_t)N * N, 0); // best score for interval (l,r)
  vector<int> parent((size_t)N * N, -1);           // best split point for (l,r)

  // Collect split points (internal nodes) for an interval using parent pointers.
  // The order produced is the in-order sequence of chosen splits.
  function<void(int,int,vector<int>&)> collect = [&](int l, int r, vector<int> &out) {
    int p = parent[idx(l,r)];
    if (p == -1) return;
    collect(l, p, out);
    collect(p, r, out);
    out.push_back(p);
  };

  // Dynamic programming over interval lengths
  for (int len = 2; len < N; ++len) {
    for (int l = 0; l + len < N; ++l) {
      int r = l + len;
      unsigned long long best = 0;
      int bestK = -1;
      // Try all possible split points k in (l, r)
      for (int k = l + 1; k <= r - 1; ++k) {
        // Compute gain contributed by connecting l-k and k-r using big intermediate multiplication
        __int128 g1 = (__int128)P[l] * Af(type[l], type[k]) * (__int128)P[k];
        __int128 g2 = (__int128)P[k] * Af(type[k], type[r]) * (__int128)P[r];
        unsigned long long gain = (unsigned long long)(g1 + g2);

        // Candidate total score = left + right + current gain
        unsigned long long cand = dp[idx(l,k)] + dp[idx(k,r)] + gain;

        if (cand > best) {
          // Better score found
          best = cand;
          bestK = k;
        } else if (cand == best) {
          // Tie-breaking: choose lexicographically smaller sequence of split points
          vector<int> candSeq;
          candSeq.reserve(len - 1);
          collect(l, k, candSeq);
          collect(k, r, candSeq);
          candSeq.push_back(k);

          if (bestK == -1) {
            bestK = k;
          } else {
            vector<int> curBestSeq;
            curBestSeq.reserve(len - 1);
            collect(l, bestK, curBestSeq);
            collect(bestK, r, curBestSeq);
            curBestSeq.push_back(bestK);
            if (candSeq < curBestSeq) bestK = k;
          }
        }
      }
      // Store best result and split for interval (l,r)
      dp[idx(l,r)] = best;
      parent[idx(l,r)] = bestK;
    }
  }

  // Output best score and the chosen internal nodes in order
  unsigned long long result = dp[idx(0, n+1)];
  cout << result << "\n";
  vector<int> out;
  out.reserve(n);
  collect(0, n+1, out);
  for (size_t i = 0; i < out.size(); ++i) {
    if (i) cout << ' ';
    cout << out[i];
  }
  cout << "\n";
  return 0;
}