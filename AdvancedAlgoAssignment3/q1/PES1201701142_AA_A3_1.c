#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define DEBUG 0

#define CHARSIZE 256

typedef struct node
{
    int l;
    int r;                     // l and r only there to represent the substring of the text
    int leafnum;               // indicates the start of suffix if node ends with $
    struct node *children[CHARSIZE]; // tells if child[i] starts with a-z or chars or $
} node;

typedef struct stree
{
    node root;
    int n;
} stree;

void init_node(node *p)
{
    p->l = -1;
    p->r = -1;
    p->leafnum = -2;
    for (int i = 0; i < CHARSIZE; i++)
    {
        p->children[i] = NULL;
    }
}

int get_tidx(char c)
{
    return (int) c;
}

void to_lower(char *text, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] += 32;
    }
}

void insert_suffix(node *ptr, int edgesubst, int suff_start, char *text, int textlen)
{
    int tidx = get_tidx(text[edgesubst]);
    if (ptr->children[tidx] == NULL)
    {
        // there's no branch that starts with the same char as the given suffix
        // make a new branch (node)
        node *childsuff = (node *)malloc(sizeof(node));
        init_node(childsuff);

        childsuff->l = edgesubst;
        childsuff->r = textlen - 1;
        childsuff->leafnum = suff_start;
        ptr->children[tidx] = childsuff;
    }
    else
    {
        // check how much does the suffix match with the child
        int amt = 0;
        int idx_childstart = ptr->children[tidx]->l;
        int idx_childend = ptr->children[tidx]->r;
        int childlen = idx_childend - idx_childstart + 1;

        while (amt < childlen && text[edgesubst + amt] == text[idx_childstart + amt])
        {
            amt++;
        }

        if (amt == childlen)
        {
            insert_suffix(ptr->children[tidx], edgesubst + amt, suff_start, text, textlen);
        }
        else
        {
            node *childnode = ptr->children[tidx];

            node *newchildnode = (node *)malloc(sizeof(node));
            init_node(newchildnode);

            newchildnode->l = childnode->l;
            newchildnode->r = childnode->l + amt - 1;

            // change the l value to point to next char after match
            childnode->l += amt;

            newchildnode->children[get_tidx(text[childnode->l])] = childnode;

            // replace the current child with the new child
            ptr->children[tidx] = newchildnode;

            // insert the suffix into the newchildnode
            insert_suffix(newchildnode, edgesubst + amt, suff_start, text, textlen);
        }
    }
}

void make_tree(stree *tree, char *text, int textlen)
{
    // for each suffix of text, add suffix to tree
    for (int i = textlen - 1; i >= 0; --i)
    {
#if DEBUG
// if(i==0) raise(SIGINT);
#endif
        insert_suffix(&(tree->root), i, i, text, textlen);

        // display_tree(tree, text, textlen);
    }
}

void disp_node(node *ptr, char *text, int textlen)
{
    printf("(%d, %d, %d) ", ptr->l, ptr->r, ptr->leafnum);
    // if(ptr->leafnum != -2)
    // printf("(%d) \n", ptr->leafnum);

    if (ptr->l != -1)
    {
        for (int i = ptr->l; i <= ptr->r; i++)
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");

    for (int i = 0; i < CHARSIZE; i++)
    {
        if (ptr->children[i] != NULL)
        {
            disp_node(ptr->children[i], text, textlen);
        }
    }
}

void display_tree(stree *tree, char *text, int textlen)
{
    printf("--beginning of tree--\n");
    printf("%s %d\n", text, textlen);
    disp_node(&(tree->root), text, textlen);
    printf("--end of tree--\n\n");
}

void dfs_node_match(node *p, int rval)
{
    if (p->r == rval)
    {
        printf("%d ", p->leafnum);
        return;
    }
    else
    {
        for (int i = 0; i < CHARSIZE; i++)
        {
            if (p->children[i] != NULL)
            {
                dfs_node_match(p->children[i], rval);
            }
        }
    }
}

void find_all_matches(char *text, int textlen, char *pattern, int patlen, stree *tree)
{
    int matched = 0;
    node *t = &(tree->root);
    while (matched < patlen)
    {
        node *tc = t->children[get_tidx(pattern[matched])];
        if (tc != NULL)
        {
            int mt = 0;
            while (matched < patlen && tc->l + mt <= tc->r && text[tc->l + mt] == pattern[matched])
            {
                matched++;
                mt++;
            }

            if (matched == patlen)
            {
                // found our pattern, do dfs at tc
                dfs_node_match(tc, textlen - 1);
                printf("\n");
                return;
            }
            else
            {
                if (tc->l + matched > tc->r)
                    t = tc;
                else
                {
                    printf("-1\n");
                    return;
                }
            }
        }
        else
        {
            printf("-1\n");
            return;
        }
    }

    printf("-1\n");
    return;
}

int main()
{
    char text[4010];
    scanf("%[^\n]s", text);
    getchar();

    int textlen = strlen(text);
    text[textlen] = '$';
    text[textlen + 1] = '\0';
    textlen++;
    to_lower(text, textlen);

    stree tree;
    tree.n = 0;
    init_node(&(tree.root));

    make_tree(&tree, text, textlen);

#if DEBUG
    display_tree(&tree, text, textlen);
#endif

    int m;
    scanf("%d", &m);
    getchar();
    // printf("m: %d\n", m);

    for (int i = 0; i < m; i++)
    {
        char pattern[1010];
        scanf("%[^\n]s", pattern);
        getchar();
        int patlen = strlen(pattern);
        to_lower(pattern, patlen);
        // printf("Pat: %s\n", pattern);

        find_all_matches(text, textlen, pattern, patlen, &tree);
    }
}
