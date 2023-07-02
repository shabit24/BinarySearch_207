#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insertRecursive(node->left, value);
        }
        else {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    Node* searchRecursive(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return searchRecursive(node->left, value);
        }
        else {
            return searchRecursive(node->right, value);
        }
    }

    Node* deleteRecursive(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->value) {
            node->left = deleteRecursive(node->left, value);
        }
        else if (value > node->value) {
            node->right = deleteRecursive(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* successor = findMinValue(node->right);
            node->value = successor->value;
            node->right = deleteRecursive(node->right, successor->value);
        }

        return node;
    }

    Node* findMinValue(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->value << " ";
            inorderRecursive(node->right);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    bool search(int value) {
        return searchRecursive(root, value) != nullptr;
    }

    void remove(int value) {
        root = deleteRecursive(root, value);
    }

    void inorderTraversal() {
        inorderRecursive(root);
    }
};

int main() {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    cout << bst.search(6) << endl;  // Output: 1 (true)
    cout << bst.search(9) << endl;  // Output: 0 (false)

    bst.remove(3);
    bst.inorderTraversal();  // Output: 2 4 5 6 7 8

    return 0;
}

