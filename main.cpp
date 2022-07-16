#include <iostream>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;

typedef struct node
{
    char data;
    node *left,*right;
} node;
typedef struct
{
    node *root;
} Tree;
node* newNode(char val)
{
    node* n =(node*) malloc(sizeof(node));
    n->data = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void initTree(Tree *T)
{
    T->root = NULL;
}
void preorder(node* n)
{
    if (n)
    {
        cout<<n->data<<" ";
        preorder(n->left);
        preorder(n->right);
    }
}
void inorder(node *n)
{
    if (n)
    {
        inorder(n->left);
        cout<<n->data<<" ";
        inorder(n->right);
    }
}
void postorder(node *n)
{
    if (n)
    {
        postorder(n->left);
        postorder(n->right);
        cout<<n->data<<" ";
    }
}
int height(node *n)
{
    int h,Max;
    if(!n)
        return -1;
    else
    {
        h = height(n->left);
        Max = height(n->right);
        if(h>Max)
            Max = h;
        return Max+1;
    }
}
int Priority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    return 0;
}
string IntoPost(string s)
{
    stack<char> OP;
    string r="";
    for(int i=0; i<(int)s.length(); i++)
    {
        if(Priority(s[i])==0)
            r+=s[i];
        else
        {
            while(!OP.empty() && Priority(s[i])<Priority(OP.top()))
            {
                r+=OP.top();
                OP.pop();
            }
            OP.push(s[i]);
        }
    }
    while(!OP.empty())
    {
        r+=OP.top();
        OP.pop();
    }
    return r;
}
string IntoPre(string s)
{
    string t;
    reverse(s.begin(),s.end());
    t = IntoPost(s);
    reverse(t.begin(),t.end());
    return t;
}
node * addN(node *n, char v, int *i)
{
    if(!n)
    {
        n = newNode(v);
        *i = 1;
    }
    else
    {
        if(!(*i) && Priority(n->data)!=0)
            n->left = addN(n->left,v,i);
        if(!(*i) && Priority(n->data)!=0)
            n->right = addN(n->right,v,i);
    }
    return n;
}
void BuildTree(Tree *T, string s)
{
    node* n = T->root;
    for(int i=0; i<(int)s.length(); i++)
    {
        int c=0;
        n = addN(n,s[i],&c);
    }
    T->root = n;
}
node* bTree(node *n,int h)
{
    if(!n && h == 0)
        return NULL;
    if(!n && h>0 )
        n = newNode('$');
    n->left = bTree(n->left,h-1);
    n->right = bTree(n->right,h-1);

    return n;
}
void printTree(Tree T)
{
    Tree T2;
    T2.root = T.root;
    T2.root = bTree(T2.root,height(T2.root)+1);
    node *n =T2.root;
    node *t;
    string o,d;
    int h = height(n)+1;
    int k = h;
    queue<node*>Q1;
    Q1.push(n);
    o = "";
    d = "";
    int f=0;
    while(k--)
    {
        queue<node*>Q2;
        for(int i=0; i<pow(2,h-1); i++)
        {
            o+=" ";
            d+=" ";
        }
        while(!Q1.empty())
        {
            t=Q1.front();
            if(t->data != '$')
            {
                o+=t->data;
                if(f==0)
                {}
                else if(f&1)
                    d+="/",f++;
                else
                    d+="\\",f++;
            }
            else
                o+=" ",d+=" ";
            Q2.push(t->left);
            Q2.push(t->right);
            Q1.pop();
            for(int i=1; i<pow(2,h); i++)
                o+=" ",d+=" ";
            //o+="\t";
        }
        cout<<d<<endl<<o<<endl;
        //cout<<o<<endl;
        Q1=Q2;
        h--;
        o="";
        d="";
        f=1;
    }
}
int main()
{
    //"1-2+3-5";//"2-3*5+6";// "8-2+3+5";//2*3+8/4-5";//"5+4*3+1/2";//"8*2+3+5/9";
    string s ="2+3+4/8/7*5";
    string p =IntoPre(s);
    Tree T;
    initTree(&T);
    BuildTree(&T,p);
    preorder(T.root);
    cout<<endl;
    inorder(T.root);
    cout<<endl;
    postorder(T.root);
    cout<<endl;
    cout<<endl;
    printTree(T);
    return 0;
}
