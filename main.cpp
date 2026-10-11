#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <utility> 

using namespace std;

struct node {
    int data;
    int index;
    vector<node*> children;

    node(int val, int idx) : data(val), index(idx) {}
};

node* buildLISTree(const vector<int>& arr) {
    node* root = new node(INT_MIN, -1);
    vector<node*> allNodes = {root};

    for (size_t i = 0; i < allNodes.size(); ++i) {
        node* curr = allNodes[i];
        int startIdx = curr->index + 1;

        for (size_t j = startIdx; j < arr.size(); ++j) {
            if (curr->index == -1 || arr[j] > curr->data) {
                node* child = new node(arr[j], j);
                curr->children.push_back(child);
                allNodes.push_back(child);
            }
        }
    }
    return root;
}

void dfs(node *start) {
    if (!start) return;

    stack<pair<node*, vector<int>>> st;
    st.push(make_pair(start, vector<int>()));

    vector<vector<int>> all_paths;
    int max_len = 0;

    while (!st.empty()) {
        pair<node*, vector<int>> top_item = st.top();
        st.pop();

        node* temp = top_item.first;
        vector<int> current_path = top_item.second;

        if (temp->index != -1) {
            current_path.push_back(temp->data);
        }

        if (temp->children.empty() && !current_path.empty()) {
            all_paths.push_back(current_path);
            if ((int)current_path.size() > max_len) {
                max_len = current_path.size();
            }
        }

        for (node* child : temp->children) {
            st.push(make_pair(child, current_path));
        }
    }

    cout << "Panjang LIS Maksimum: " << max_len << "\n";
    cout << "Subsequence Optimal:\n";
    for (const auto& path : all_paths) {
        if ((int)path.size() == max_len) {
            cout << "[ ";
            for (int val : path) cout << val << " ";
            cout << "]\n";
        }
    }
}

int main() {
    vector<int> sequence = {4, 1, 13, 7, 0, 2, 8, 11, 3};

    node* root = buildLISTree(sequence);
    dfs(root);

    return 0;
}
