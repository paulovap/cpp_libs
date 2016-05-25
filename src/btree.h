#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
namespace btree {

struct node
{
    int val;
    int ht;
    node* left;
    node* right;
};

// AVL Tree
inline int avl_height(node *root) {
    return root ? root->ht : -1;
}
inline int avl_factor(node *root) {
    if (!root)
        return 0;
    return avl_height(root->left) - avl_height(root->right);
}
inline void avl_update_height(node *root) {
    if (!root)
        return;
    root->ht = std::max(avl_height(root->left), avl_height(root->right)) + 1;
}

inline node* make_node(int val, int ht = 0) {
    auto n = new node;
    n->ht = ht;
    n->left = nullptr;
    n->right = nullptr;
    n->val = val;
    return n;
}

inline void avl_free(node *root) {
    if (root) {
        avl_free(root->left);
        avl_free(root->right);
        delete root;
    }
}

node* avl_rotate(node *root, node *parent)
{
    if (!root)
        return nullptr;

    int root_factor = avl_factor(root);
    bool node_in_left = parent && parent->left == root;

    if (root_factor == 2 && avl_factor(root->left) == -1){
        //LR
        auto aux = root->left;
        root->left = root->left->right;
        aux->right = root->left->right;
        root->left->left = aux;
    }
    else if (root_factor == 2 && avl_factor(root->left) == 1){
        //LL
        auto l = root->left;
        auto lr = root->left->right; //C
        if (parent) {
            if (node_in_left)
                parent->left = root->left;
            else
                parent->right = root->left;
        }
        root->left = lr;
        l->right = root;
        root = l;
    }
    else if (root_factor == -2 && avl_factor(root->right) == 1){
        //RL
        auto aux = root->right;
        root->right = aux->left;
        aux->left = aux->left->right;
        root->right->right = aux;
    }
    else if (root_factor == -2 && avl_factor(root->right) == -1){
        //RR
        auto r = root->right;
        auto rl = root->right->left; //C
        if (parent) {
        if (node_in_left)
            parent->left = r;
        else
            parent->right = r;
        }
        root->right = rl;
        r->left = root;
        root = r;
    }
    if (root->left) {
        avl_update_height(root->left->left);
        avl_update_height(root->left->right);
    }
    if (root->right) {
        avl_update_height(root->right->left);
        avl_update_height(root->right->right);
    }
    avl_update_height(root->left);
    avl_update_height(root->right);
    avl_update_height(root);

    if (std::abs(avl_factor(root)) == 2)
        root = avl_rotate(root, parent);
    return root;
}

node* avl_insert(node* root, int val, node *parent = nullptr) {
    if (!root)
        return make_node(val);
    //insert
    if (root->val > val)
        root->left = avl_insert(root->left, val, root);
    else
        root->right = avl_insert(root->right, val, root);

    avl_update_height(root);

    if (std::abs(avl_factor(root)) == 2)
        return avl_rotate(root, parent);
    return root;
}

node* avl_search(node *root, int val) {
    if (!root)
        return nullptr;
    if (val == root->val)
        return root;
    if (root->val > val)
        return avl_search(root->left, val);
    return avl_search(root->right, val);
}

}

#endif // BTREE_H
