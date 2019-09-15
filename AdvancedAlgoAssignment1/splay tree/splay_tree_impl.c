#include "splay_tree_imp.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG 1

static int num_rotations = 0;

typedef struct node
{
    int key;
    int value;
    struct node *left, *right;
} node;

typedef struct tree
{
    node *root;
} tree;

//right rotates a tree rooted at root and returns new root
node *right_rotate(node *root)
{
    num_rotations++;
    node *newroot = root->left;
    root->left = newroot->right;
    newroot->right = root;
    return newroot;
}

//left rotates a tree rooted at root and returns new root
node *left_rotate(node *root)
{
    num_rotations++;
    node *newroot = root->right;
    root->right = newroot->left;
    newroot->left = root;
    return newroot;
}

//splays the tree/subtree at root based on the key and returns new node
//if key is not found, the last visited node is returned
node *splay(node *root, int key)
{

    if (root == NULL || root->key == key) //check if root is null
    {
        return root;
    }

    if (key < root->key)
    {
        if (root->left == NULL)
            return root;
        else
        {
            //check if key is present in left node
            if (root->left->key == key)
            {
                return right_rotate(root);
            }
            else if (key < root->left->key) //check if key is in the left of root->left, then splay and do RR rotation
            {
                root->left->left = splay(root->left->left, key);

                if (root->left->left != NULL)
                {
                    return right_rotate(right_rotate(root));
                }
                else
                {
                    return right_rotate(root);
                }
            }
            else //check if key is in the right of root->left, then splay and do LR rotation
            {
                root->left->right = splay(root->left->right, key);

                if (root->left->right != NULL)
                {
                    root->left = left_rotate(root->left);
                    return right_rotate(root);
                }
                else
                {
                    return right_rotate(root);
                }
            }
        }
    }
    else //if key > root->key
    {
        if (root->right == NULL)
            return root;
        else
        {
            if (root->right->key == key) //if key is present in root->right, left rotate and return
            {
                return left_rotate(root);
            }
            else if (key < root->right->key) //if key is in root->right->left subtree, splay and do RL rotation
            {
                root->right->left = splay(root->right->left, key);

                if (root->right->left != NULL)
                {
                    root->right = right_rotate(root->right);
                    return left_rotate(root);
                }
                else
                {
                    return left_rotate(root);
                }
            }
            else //if key is in root->right->right subtree, splay and do LL rotation
            {
                root->right->right = splay(root->right->right, key);

                if (root->right->right != NULL)
                {
                    return left_rotate(left_rotate(root));
                }
                else
                {
                    return left_rotate(root);
                }
            }
        }
    }
}

void *make_new_dictionary()
{
    tree *tree_ptr = (tree *)malloc(sizeof(tree));
    tree_ptr->root = NULL;

    return tree_ptr;
}

//Inserts new key-value pair into the dictionary. Update the value in case of duplicate keys
void insert(void *ptr, int key, int value)
{
    tree *tree_ptr = (tree *)ptr;
    tree_ptr->root = splay(tree_ptr->root, key);

    if (tree_ptr->root != NULL && tree_ptr->root->key == key)
    {
        tree_ptr->root->value = value;
    }
    else
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->key = key;
        newnode->value = value;
        newnode->left = newnode->right = NULL;

        if (tree_ptr->root == NULL)
        {
            tree_ptr->root = newnode;
        }
        else if (key < tree_ptr->root->key)
        {
            newnode->right = tree_ptr->root;
            newnode->left = tree_ptr->root->left;
            tree_ptr->root->left = NULL;

            tree_ptr->root = newnode;
        }
        else
        {
            newnode->left = tree_ptr->root;
            newnode->right = tree_ptr->root->right;
            tree_ptr->root->right = NULL;

            tree_ptr->root = newnode;
        }
    }
}

//Returns value if found else returns -1
int find(void *ptr, int key)
{
    tree *tree_ptr = (tree *)ptr;
    tree_ptr->root = splay(tree_ptr->root, key);

    if (tree_ptr->root != NULL && tree_ptr->root->key == key)
    {
        return tree_ptr->root->value;
    }

    return -1;
}

#if DEBUG

int getkey(node *n)
{
    if (n == NULL)
        return -1;
    return n->key;
}

void display(node *root)
{
    if (root != NULL)
    {
        printf("K: %d V: %d\tLeft: %d, Right: %d\n", root->key, root->value, getkey(root->left), getkey(root->right));
        display(root->left);
        display(root->right);
    }
}

/* 
node *newnode(int k, int v)
{
    node *n = (node *)malloc(sizeof(node));
    n->key = k;
    n->value = v;
    n->left = n->right = NULL;
    return n;
}


int main()
{
    tree *t = make_new_dictionary();
    t->root = newnode(100, 10);
    node *root = t->root;


    root->left = newnode(50, 10);
    root->left->left = newnode(40, 10);
    root->left->left->left = newnode(30, 10);
    root->left->left->left->left = newnode(20, 10);
    root->right = newnode(200, 10);

    display(t->root); printf("\n\n");
    insert(t, 25, 25);
    display(t->root); printf("\n\n");


}
*/

#endif

void disp_rotations(void *ptr)
{
    // display(((tree *)ptr)->root);
    printf("Number of rotations: %d\n", num_rotations);
}