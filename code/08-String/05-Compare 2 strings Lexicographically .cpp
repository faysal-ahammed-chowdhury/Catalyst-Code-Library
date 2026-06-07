// Time: O(logn)
string s;
Hashing hs;
// return 0 if both equal
// return 1 if first substring greater
// return -1 if second substring greater
// here lcp() provides the len of longest common prefix
int compare(int i, int j, int x, int y) {
  int common_prefix = lcp(i, j, x, y);
  int len1 = j - i + 1, len2 = y - x + 1;
  if (common_prefix == len1 and len1 == len2) return 0;
  else if (common_prefix == len1) return -1;
  else if (common_prefix == len2) return 1;
  else return (s[i + common_prefix - 1] < s[x + common_prefix - 1] ? -1 : 1);
}