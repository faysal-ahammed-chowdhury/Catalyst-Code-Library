mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct node {
  int prior, size;
  int val, sum;
  node *l, *r;
  node(int value) {
    l = r = nullptr;
    val = value;
    sum = value;
    size = 1;
    prior = rnd();
  }
};
typedef node* pnode;
int sz(pnode t) {
  if (t == nullptr) {return 0;}
  return t->size;
}
void upd_sz(pnode t) {
  if (t != nullptr) {
    t->size = sz(t->l) + 1 + sz(t->r);
  }
}
////////////////////based on index
void reverse_check(pnode t) {
  if (t == nullptr) {return;}
  if (t->inv == 1) {
    swap(t->l, t->r);
    if (t->l != nullptr) {t->l->inv ^= 1;}
    if (t->r != nullptr) {t->r->inv ^= 1;}
    t->inv = 0;
  }
}

void fix_node_info(pnode& t, pnode l, pnode r) {
  if (!l || !r)return; // void(t = l?l:r);
  t->sum = l->sum + r->sum;
}

void update_node_info(pnode t) {
  if (!t) {return;}
  //reverse_check(t);
  t->sum = t->val;     //reset node
  fix_node_info(t, t->l, t);
  fix_node_info(t, t, t->r);
}

void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
  if (!t) {l = r = nullptr; return;}
  //reverse_check(t);
  int curr_pos = add + sz(t->l);
  if (curr_pos <= pos) {
    split(t->r, t->r, r, pos, curr_pos + 1); l = t;
  }
  else {
    split(t->l, l, t->l, pos, add); r = t;
  }
  upd_sz(t);
  update_node_info(t);
}
void merge(pnode &t, pnode l, pnode r) {
  //reverse_check(t);
  //reverse_check(l);
  //reverse_check(r);
  if (!l || !r) {t = l ? l : r;}
  else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    t = l;
  }
  else {
    merge(r->l, l, r->l);
    t = r;
  }
  upd_sz(t);
  //update_node_info(t);
}
////////////////////////////based on value
void split(pnode t, pnode &l, pnode &r, int key) {
  if (!t) {l = r = nullptr;}
  else if (t->val <= key) {
    split(t->r, t->r, r, key);
    l = t;
  }
  else {
    split(t->l, l, t->l, key);
    r = t;
  }
  upd_sz(t);
}
void merge_treap(pnode &t, pnode l, pnode r) {
  if (!l || !r) {
    t = l ? l : r;
    return;
  }
  if (l->prior < r->prior) {swap(l, r);}
  node *L, *R;
  split(r, L, R, l->val);
  merge_treap(l->r, l->r, R);
  merge_treap(l->l, L, l->l);
  t = l;
  upd_sz(t);
}
void erase(pnode &t, pnode &erase_part, int L, int R) {
  pnode l, r, mid, mr;
  split(t, l, r, L - 1);
  split(r, mid, mr, R);
  merge(t, l, mr);
  erase_part = mid;
  upd_sz(t);
}
void erase(pnode &t, int value) {
  if (!t) {return;}
  else if (t->val == value) {
    pnode temp = t;
    merge(t, t->l, t->r);
    free(temp);
  }
  else if (t->val < value) {
    erase(t->r, value);
  }
  else {
    erase(t->l, value);
  }
  upd_sz(t);
}
void output(pnode t) {
  if (t == nullptr) {return;}
  output(t->l);
  cout << t->val << " ";
  output(t->r);
}
//main function
/*
pnode root=nullptr;
merge(root,root, new node(354)); //inserting
*/