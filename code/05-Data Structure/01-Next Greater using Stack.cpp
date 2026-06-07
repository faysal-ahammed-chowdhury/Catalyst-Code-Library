stack<pair<int, int>> st;
int right[n + 1]; // $a[i]$ is maximum from index $i$ to $right[i]$
for (int i = 1; i <= n; i++) {
  while (!st.empty() and st.top().first < a[i]) {
    right[st.top().second] = i - 1;
    st.pop();
  }
  st.push({a[i], i});
}
while (!st.empty()) {
  right[st.top().second] = n;
  st.pop();
}