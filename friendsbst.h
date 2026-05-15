#pragma once
#include <iostream>
using namespace std;
//binary search tree
class FriendBSTNode {
public:
    int friendID;
    FriendBSTNode* left;
    FriendBSTNode* right;

    FriendBSTNode(int id) {
        friendID = id;
        left = right = NULL;
    }
};

class friendsbst {
private:
    FriendBSTNode* root;

    FriendBSTNode* insertRec(FriendBSTNode* node, int id) {
        if (node == NULL)
            return new FriendBSTNode(id);

        if (id < node->friendID)
            node->left = insertRec(node->left, id);
        else if (id > node->friendID)
            node->right = insertRec(node->right, id);

        return node;
    }

    bool searchRec(FriendBSTNode* node, int id) const {
        if (node == NULL)
            return false;

        if (node->friendID == id)
            return true;

        if (id < node->friendID)
            return searchRec(node->left, id);

        return searchRec(node->right, id);
    }

    void countMutualRec(FriendBSTNode* node,
        const friendsbst& other,
        int& count) const {
        if (node == NULL)
            return;

        countMutualRec(node->left, other, count);

        if (other.search(node->friendID))
            count++;

        countMutualRec(node->right, other, count);
    }

    void destroyRec(FriendBSTNode* node) {
        if (!node) return;
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }

public:
friendsbst() {
        root = NULL;
    }

    void addFriend(int id) {
        root = insertRec(root, id);
    }

    bool search(int id) const {
        return searchRec(root, id);
    }

    int countMutual(const friendsbst& other) const {
        int count = 0;
        countMutualRec(root, other, count);
        return count;
    }

    ~friendsbst() {
        destroyRec(root);
        root = NULL;
    }
};
