// Count the number of occurances of each prefix
vector<int> ans(n + 1);
for (int i = 0; i < n; i++) ans[lps[i]]++;
for (int i = n - 1; i > 0; i--) ans[lps[i - 1]] += ans[i];
for (int i = 0; i <= n; i++) ans[i]++;