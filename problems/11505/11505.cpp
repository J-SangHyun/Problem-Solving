#include <iostream>
#include <vector>

#define LEFT(node) (2*(node))
#define RIGHT(node) (2*(node) + 1)
#define DENOMINATOR ((long long)1000000007)

using namespace std;
typedef long long VALUE;
void build_tree(vector<VALUE> &input, vector<VALUE> &tree, int node, int start, int end);
void update_tree(vector<VALUE> &input, vector<VALUE> &tree, int node, int start, int end, int idx, VALUE val);
VALUE query_tree(vector<VALUE> &tree, int node, int start, int end, int left, int right);

int main(void) {
    int N, M, K, n, h = 0;
    cin >> N >> M >> K;
    
    // calculate tree height
    n = N - 1;
    while(n > 0) {
        n = n >> 1;
        h++;
    }
    
    // build initial segment tree
    vector<VALUE> input(N);
    vector<VALUE> tree(1 << (h+1));
    for(int i = 0; i < N; i++) {
        cin >> input[i];
    }
    build_tree(input, tree, 1, 0, N-1);
    
    int a, b, c;
    for(int i = 0; i < M+K; i++) {
        cin >> a >> b >> c;
        if(a == 1) {
            update_tree(input, tree, 1, 0, N-1, b-1, c);
        }
        else if(a == 2) {
            cout << query_tree(tree, 1, 0, N-1, b-1, c-1) << "\n";
        }
    }
    return 0;
}

void build_tree(vector<VALUE> &input, vector<VALUE> &tree, int node, int start, int end) {
    if(start == end) {
        tree[node] = input[start];
    }
    else {
        build_tree(input, tree, LEFT(node), start, (start+end)/2);
        build_tree(input, tree, RIGHT(node), (start+end)/2 + 1, end);
        tree[node] = (tree[LEFT(node)] * tree[RIGHT(node)]) % DENOMINATOR;
    }
}

void update_tree(vector<VALUE> &input, vector<VALUE> &tree, int node, int start, int end, int idx, VALUE val) {
    if(idx < start || idx > end) {
        return;
    }
    if(start == end) {
        input[idx] = val;
        tree[node] = val;
        return;
    }
    update_tree(input, tree, LEFT(node), start, (start+end)/2, idx, val);
    update_tree(input, tree, RIGHT(node), (start+end)/2 + 1, end, idx, val);
    tree[node] = (tree[LEFT(node)] * tree[RIGHT(node)]) % DENOMINATOR;
}

VALUE query_tree(vector<VALUE> &tree, int node, int start, int end, int left, int right) {
    if(left > end || right < start) {
        return 1;
    }
    if(left <= start && end <= right) {
        return tree[node];
    }
    VALUE lprod = query_tree(tree, LEFT(node), start, (start+end)/2, left, right);
    VALUE rprod = query_tree(tree, RIGHT(node), (start+end)/2 + 1, end, left, right);
    return (lprod * rprod) % DENOMINATOR;
}

