#include <iostream>
#include <string>

struct Node {
    int val = 1e9;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;

    Node() = default;

    Node(int value) : val(value) {};
};

int height(Node *node) {
    return (node == nullptr ? 0 : node->height);
}

int getBalance(Node *node) {
    return (node == nullptr ? 0 : height(node->right) - height(node->left));
}

Node *leftRotate(Node *left) {
    Node *right = left->right;
    left->right = right->left;
    right->left = left;
    left->height = std::max(height(left->left), height(left->right)) + 1;
    right->height = std::max(height(right->left), height(right->right)) + 1;
    return right;
}

Node *rightRotate(Node *right) {
    Node *left = right->left;
    right->left = left->right;
    left->right = right;
    left->height = std::max(height(left->left), height(left->right)) + 1;
    right->height = std::max(height(right->left), height(right->right)) + 1;
    return left;
}

Node *rebalance(Node *node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->right) < 0) node->right = rightRotate(node->right);
        return leftRotate(node);
    } else if (balance < -1) {
        if (getBalance(node->left) > 0) node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    return node;
}

Node *newNode(int val) {
    Node *temp = new Node(val);
    return temp;
}

int find(Node *node, int val) {
    Node *curr = node;
    while (curr != nullptr) {
        if (curr->val == val) {
            break;
        }
        curr = (curr->val > val ? curr->left : curr->right);
    }
    if (curr == nullptr) return 1e9;
    else return curr->val;
}

Node *insertNode(Node *top, int val) {
    if (top == nullptr) return newNode(val);
    else if (val < top->val) top->left = insertNode(top->left, val);
    else if (val > top->val) top->right = insertNode(top->right, val);
    return rebalance(top);
}

Node *deleteMin(Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = deleteMin(node->left);
    return rebalance(node);
}

Node *deleteNode(Node *top, int val) {
    if (top == nullptr) return nullptr;
    else if (val < top->val) top->left = deleteNode(top->left, val);
    else if (val > top->val) top->right = deleteNode(top->right, val);
    else {
        Node *left = top->left;
        Node *right = top->right;
        delete top;
        if (right == nullptr) return left;
        Node *mostLeft = right;
        while (mostLeft->left != nullptr) mostLeft = mostLeft->left; //finding most left of the right subtree
        mostLeft->right = deleteMin(right);//inserting all the elements from the leaf without one key
        mostLeft->left = left;
        return rebalance(mostLeft);
    }
    return rebalance(top);
}

int prev(Node *node, int val) {
    if (node == nullptr) return 1e9;
    if (node->val < val) {
        int x = prev(node->right, val);
        if (x == 1e9) return node->val;
        else return x;
    }
    if (node->val >= val) return prev(node->left, val);
    else return 1e9;
}

int next(Node *node, int val) {
    if (node == nullptr) return 1e9;
    if (node->val > val) {
        int x = next(node->left, val);
        if (x == 1e9) return node->val;
        else return x;
    }
    if (node->val <= val) return next(node->right, val);
    else return 1e9;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string ord;
    int x;
    Node *root = nullptr;
    while (std::cin >> ord >> x) {
        if (ord == "insert") {
            root = insertNode(root, x);
        } else if (ord == "delete") {
            root = deleteNode(root, x);
        } else if (ord == "exists") {
            int found = find(root, x);
            if (found == 1e9) std::cout << "false\n";
            else std::cout << "true\n";
        } else if (ord == "next") {
            int val = next(root, x);
            if (val == 1e9) std::cout << "none\n";
            else std::cout << val << '\n';
        } else if (ord == "prev") {
            int val = prev(root, x);
            if (val == 1e9) std::cout << "none\n";
            else std::cout << val << '\n';
        }
    }
}