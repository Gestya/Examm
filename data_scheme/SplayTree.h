#pragma once

#include <iostream>

struct T_Node
{
    int number = { 0 };
    T_Node* left = { nullptr };
    T_Node* right = { nullptr };
};

class SplayTree
{
private:

    void InOrder(T_Node* root)
    {
        if (root)
        {
            InOrder(root->left);
            std::cout << "key: " << root->number;
            if (root->left)
                std::cout << " | left child: " << root->left->number;
            if (root->right)
                std::cout << " | right child: " << root->right->number;
            std::cout << "\n";
            InOrder(root->right);
        }
    }

    void show_all_node(T_Node* send_node)
    {
        if (send_node)
        {
            if (send_node->left != nullptr)
                show_all_node(send_node->left);

            std::cout << std::endl << send_node->number;

            if (send_node->right != nullptr)
                show_all_node(send_node->right);
        }
        else
        {
            std::cerr << "erorr: 404! Tree cvlear!";
        }
    }

    int height_tree(T_Node* root)
    {
        T_Node* temp = root;
        int h1 = 0, h2 = 0;
        if (temp == nullptr)
            return(0);
        if (temp->left)
            h1 = height_tree(temp->left);
        if (temp->right)
            h2 = height_tree(temp->right);
        return  (h1 > h2) ? h1 + 1 : h2 + 1;

    }

    T_Node* RR_Rotate(T_Node* k2)
    {
        T_Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    T_Node* LL_Rotate(T_Node* k2)
    {
        T_Node* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        return k1;
    }

    T_Node* Splay(int key, T_Node* root)
    {
        if (!root)
            return nullptr;
        T_Node header;
        header.left = header.right = nullptr;
        T_Node* LeftTreeMax = &header;
        T_Node* RightTreeMin = &header;
        while (1)
        {
            if (key < root->number)
            {
                if (!root->left)
                    break;
                if (key < root->left->number)
                {
                    root = RR_Rotate(root);
                    if (!root->left)
                        break;
                }
                RightTreeMin->left = root;
                RightTreeMin = RightTreeMin->left;
                root = root->left;
                RightTreeMin->left = nullptr;
            }
            else if (key > root->number)
            {
                if (!root->right)
                    break;
                if (key > root->right->number)
                {
                    root = LL_Rotate(root);
                    if (!root->right)
                        break;
                }
                LeftTreeMax->right = root;
                LeftTreeMax = LeftTreeMax->right;
                root = root->right;
                LeftTreeMax->right = nullptr;
            }
            else
                break;
        }
        LeftTreeMax->right = root->left;
        RightTreeMin->left = root->right;
        root->left = header.right;
        root->right = header.left;
        return root;
    }

    T_Node* New_Node(int key)
    {
        T_Node* new_node = new T_Node;
        if (!new_node)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        new_node->number = key;
        new_node->left = new_node->right = nullptr;
        return new_node;
    }

public:
    T_Node* insert(int arivved_number, T_Node* begin)
    {
        static T_Node* local_tree = nullptr;
        if (!local_tree)
            local_tree = New_Node(arivved_number);
        else
            local_tree->number = arivved_number;
        if (!begin)
        {
            begin = local_tree;
            local_tree = nullptr;
            return begin;
        }
        begin = Splay(arivved_number, begin);
        if (arivved_number < begin->number)
        {
            local_tree->left = begin->left;
            local_tree->right = begin;
            begin->left = nullptr;
            begin = local_tree;
        }
        else if (arivved_number > begin->number)
        {
            local_tree->right = begin->right;
            local_tree->left = begin;
            begin->right = nullptr;
            begin = local_tree;
        }
        else
            return begin;
        local_tree = nullptr;
        return begin;
    }

    T_Node* erase(int key, T_Node* root)
    {
        T_Node* temp;
        if (!root)
            return nullptr;
        root = Splay(key, root);
        if (key != root->number)
            return root;
        else
        {
            if (!root->left)
            {
                temp = root;
                root = root->right;
            }
            else
            {
                temp = root;
                root = Splay(key, root->left);
                root->right = temp->right;
            }
            delete temp;
            return root;
        }
    }

    T_Node* search(int key, T_Node* root)
    {
        //return Splay(key, root);
        if (!root)
            return nullptr;
        if (key == root->number)
            return root;
        else if (key < root->number)
            return search(key, root->left);
        else
            return search(key, root->right);
    }

    void show(T_Node* begin)
    {
        InOrder(begin);
        show_all_node(begin);
        int max = height_tree(begin);
        std::cout << std::endl << std::endl<< max << std::endl << std::endl;
    }
};
