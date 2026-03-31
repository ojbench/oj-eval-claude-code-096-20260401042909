#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from extended preorder traversal
TreeNode* buildTree(vector<int>& preorder, int& index) {
    if (index >= (int)preorder.size() || preorder[index] == -1) {
        index++;
        return nullptr;
    }

    TreeNode* root = new TreeNode(preorder[index]);
    index++;
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);

    return root;
}

// Record parent and depth for each node
void recordInfo(TreeNode* root, unordered_map<int, int>& parent,
                unordered_map<int, int>& depth) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);
    parent[root->val] = -1;  // root has no parent
    depth[root->val] = 0;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node->left) {
            parent[node->left->val] = node->val;
            depth[node->left->val] = depth[node->val] + 1;
            q.push(node->left);
        }

        if (node->right) {
            parent[node->right->val] = node->val;
            depth[node->right->val] = depth[node->val] + 1;
            q.push(node->right);
        }
    }
}

// Check if two nodes are cousins
bool areCousins(int x, int y, unordered_map<int, int>& parent,
                unordered_map<int, int>& depth) {
    // Check if both nodes exist
    if (parent.find(x) == parent.end() || parent.find(y) == parent.end()) {
        return false;
    }

    // Same depth and different parents
    return depth[x] == depth[y] && parent[x] != parent[y];
}

int main() {
    int q;
    cin >> q;

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    // Read preorder traversal
    vector<int> preorder;
    int val;
    while (cin >> val) {
        preorder.push_back(val);
    }

    // Build tree
    int index = 0;
    TreeNode* root = buildTree(preorder, index);

    // Record parent and depth
    unordered_map<int, int> parent;
    unordered_map<int, int> depth;
    recordInfo(root, parent, depth);

    // Process queries
    for (auto& query : queries) {
        int x = query.first;
        int y = query.second;
        cout << (areCousins(x, y, parent, depth) ? 1 : 0) << endl;
    }

    return 0;
}
