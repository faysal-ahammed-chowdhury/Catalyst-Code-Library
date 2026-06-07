// Given an Array, if any $a_i=x$ exist all $x$ are consecutive. Given $[L,R]$ Q times, Print Max Freq.
struct node {
  int first_element, first_element_cnt;
  int last_element, last_element_cnt;
  int max_cnt;
};
node merge(node l, node r) {
  if(l.first_element == -1) return r;
  if(r.first_element == -1) return l;
  node ans;
  ans.max_cnt = max(l.max_cnt, r.max_cnt);
  if(l.last_element == r.first_element) {
    ans.max_cnt = max(ans.max_cnt, l.last_element_cnt + r.first_element_cnt);
  }
  ans.first_element = l.first_element;
  ans.first_element_cnt = l.first_element_cnt;
  if(l.first_element == r.first_element) {
    ans.first_element_cnt += r.first_element_cnt;
  }
  ans.last_element = r.last_element;
  ans.last_element_cnt = r.last_element_cnt;
  if(r.last_element == l.last_element) {
    ans.last_element_cnt += l.last_element_cnt;
  }
  return ans;
}