#include <iostream>
using namespace std;

typedef struct link{
    char id;
    link *right, *left;
} tree;

tree* form(char *str, int i);

tree* atom(char *str, int i){
    tree *node = new(tree);
    if(str[i] - '0' <=9 && str[i] - '0' >=0){
        node->id = str[i];
        node->left = NULL;
        node->right = NULL;
    }
    if(str[i] == '!'){
        tree *t1;
        node->id = str[i];
        i++;
        if(str[i] == '('){
            i++;
            int k=1;
            char s[256];
            int j = 0;
            while(k){
                if(str[i] == '(')
                    k++;
                if(str[i] == ')')
                    k--;
                s[j] = str[i];
                j++;
                i++;
            }
            s[j-1] = NULL;
            i++;
            t1 = form(s, 0);
            node->left = t1;
            node->right = NULL;
        }
        else
            t1 = atom(str, i);
        node->left = t1;
        node->right = NULL;
    }
    if(str[i] == '('){
        i++;
        char s[256];
        int j = 0;
        int k = 1;
        while(k){
            if(str[i] == '(')
                k++;
            if(str[i] == ')')
                k--;
            s[j] = str[i];
            j++;
            i++;
        }
        s[j-1] = NULL;
        node = form(s, 0);
    }
    return node;
}

tree* term(char *str, int i){
    char stn[256];
    int j = 0;
    while(str[i] != '*' && str[i] && str[i] != '('){
        stn[j] = str[i];
        j++;
        i++;
    }
    if(str[i] == '('){
        stn[j] = str[i];
        j++;
        i++;
        int k = 1;
        while(k){
            if(str[i] == '(')
                k++;
            if(str[i] == ')')
                k--;
            stn[j] = str[i];
            i++;
            j++;
        }
    }
    stn[j] = NULL;
    tree *t1 = new(tree);
    t1 = atom(stn, 0);
    while(str[i] == '*'){
        tree *node = new(tree);
        node->id = str[i];
        node->left = t1;
        i++;
        char stn[256];
        int j = 0;
        while(str[i] != '*' && str[i] && str[i] != '('){
            stn[j] = str[i];
            j++;
            i++;
        }
        if(str[i] == '('){
            stn[j] = str[i];
            j++;
            i++;
            int k = 1;
            while(k){
                if(str[i] == '(')
                    k++;
                if(str[i] == ')')
                    k--;
                stn[j] = str[i];
                j++;
                i++;
            }
        }
        stn[j] = NULL;
        t1 = atom(stn, 0);
        node->right = t1;
        t1 = node;
    }
    return t1;
}


tree* form(char *str, int i){
    char pch[256];
    int j = 0;
    while(str[i] && str[i] != '+') {
        while (str[i] != '+' && str[i] && str[i] != '(') {
            pch[j] = str[i];
            j++;
            i++;
        }
        if (str[i] == '(') {
            pch[j] = str[i];
            j++;
            i++;
            int k = 1;
            while (k) {
                if (str[i] == '(')
                    k++;
                if (str[i] == ')')
                    k--;
                pch[j] = str[i];
                j++;
                i++;
            }
        }
        pch[j] = NULL;
    }
    tree* t1 = term(pch, 0);
    while(str[i] == '+'){
        tree *p = new(tree);
        p->id = str[i];
        p->left = t1;
        i++;
        char pch[256];
        int j = 0;
        while(str[i] != '+' && str[i] && str[i] != '('){
            pch[j] = str[i];
            j++;
            i++;
        }
        if(str[i] == '('){
            pch[j] = str[i];
            j++;
            i++;
            int k = 1;
            while(k){
                if(str[i] == '(')
                    k++;
                if(str[i] == ')')
                    k--;
                pch[j] = str[i];
                j++;
                i++;
            }
        }
        pch[j] = NULL;
        t1 = term(pch, 0);
        p->right = t1;
        t1 = p;
    }
    return t1;
}

bool result(tree* t){
    if(t->left == NULL && t->right == NULL) {
        if (t->id == '0')
            return false;
        else return true;
    }
    else{
        switch(t->id){
            case '!':
                return !result(t->left);
            case '+':
                return result(t->left) || result(t->right);
            case '*':
                return result(t->left) && result(t->right);
        }
    }
}

int main()
{
    int i = 0;
    char str[256];
    cin >> str;
    tree *res = form(str, i);
    cout << result(res);
    return 0;
}
