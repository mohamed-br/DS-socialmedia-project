#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Treap
{
public:

    class Node
    {
    public:
        string username;
        int priority;
        Node* right, * left;
        Node()
        {
            left = right = nullptr;
        }
        Node(string username)
        {
            this->username = username;
            priority = rand() % 100;
            left = right = nullptr;
        }

    };

    Treap()
    {
        root = nullptr;
    }
    
    void Insert(string username)
    {
        root = insertion(root, username);
    }

    bool search(string username)
    {
        return find(root, username);
    }
    void removeFriend(string username)
    {
        remove(root, username);
    }
    Node* getRoot()
    {
        return root;
    }
public:
    Node* root;
    void  remove(Node*& root, string username)
    {
        if (root == nullptr) {
            cout << "not found\n";
            return;
        }
        if (username < root->username) {
            remove(root->left, username);
        }
        else if (username > root->username) {
            remove(root->right, username);
        }
        else {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }

            else if (root->left && root->right)
            {
                if (root->left->priority < root->right->priority)
                {
                    leftRotation(root);
                    remove(root->left, username);
                }
                else {
                    rightRotation(root);
                    remove(root->right, username);
                }
            }
            else {
                Node* child = (root->left) ? root->left : root->right;//choose child
                Node* tmp = root;
                root = child;
                delete tmp;
            }
        }
    }
    Node* leftRotation(Node* Root)
    {
        Node* X = Root->right;
        Node* Y = Root->right->left;
        X->left = Root;
        Root->right = Y;
        return X;

    }
    Node* rightRotation(Node* Root)
    {
        Node* A = Root->left;
        Node* B = Root->left->right;
        A->right = Root;
        Root->left = B;
        return A;
    }
    Node* insertion(Node* root, string key)
    {
        if (root == NULL) {
            root = new Node(key);
            return root;
        }

        else if (root->username >= key)
        {
            root->left = insertion(root->left, key);

            if (root->left->priority > root->priority)
                root = rightRotation(root);
        }
        else if (root->username <= key)
        {
            root->right = insertion(root->right, key);

            if (root->right->priority > root->priority)
                root = leftRotation(root);
        }
        return root;
    }

    bool find(Node* root, string username)
    {
        if (root == nullptr)
        {
            return false;
        }
        if (root->username == username)
        {
            return true;
        }
        else if (username < root->username)
        {
            return find(root->left, username);
        }
        else
        {
            return find(root->right, username);
        }
    }
};
#endif // TREAP_H