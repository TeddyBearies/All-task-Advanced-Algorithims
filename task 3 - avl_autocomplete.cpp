#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct AVLNode {
    string key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(string k): key(k), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* n) {
    if (!n) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a>b) ? a:b;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x= y->left;
    AVLNode* T2= x->right;
    x->right= y;
    y->left= T2;
    y->height= max(height(y->left),height(y->right))+1;
    x->height= max(height(x->left),height(x->right))+1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y= x->right;
    AVLNode* T2= y->left;
    y->left= x;
    x->right= T2;
    x->height= max(height(x->left),height(x->right))+ 1;
    y->height= max(height(y->left),height(y->right))+ 1;
    return y;
}

int getBalance(AVLNode* n) {
    if (!n) return 0;
    return height(n->left)-height(n->right);
}


AVLNode* insert(AVLNode* node, string key) {
    if (!node) return new AVLNode(key);
    if (key < node->key)
        node->left= insert(node->left, key);
    else if (key > node->key)
        node->right= insert(node->right, key);
    else
        return node;
    node->height= 1+ max(height(node->left), height(node->right));
    int balance =getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right =rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool startsWith(const string& word, const string& prefix) {
    return word.substr(0, prefix.size())==prefix;
}

void findWords(AVLNode* root, const string& prefix, string results[], int& count, int maxCount) {
    if (!root) return;
    if (startsWith(root->key, prefix) && count<maxCount) {
        results[count]=root->key;
        count++;
    }
    if (root->key >= prefix)
        findWords(root->left, prefix, results, count, maxCount);
    if (root->key.size() >= prefix.size() && root->key.compare(0,prefix.size(),prefix)<=0)
        findWords(root->right,prefix,results,count,maxCount);
}

int main() {
    AVLNode* root = nullptr;
    string word;
    ifstream dict("dictionary.txt");
    if (!dict) {
        cout << "no dictionary file found"<<endl;
        return 1;
    }
    while (dict >>word) {
        root = insert(root,word);
    }
    dict.close();

    cout<<"dictionary loaded" << endl;
    cout<<"program started (type 'exit' to stop program):" << endl;

    string userInput;
    const int MAX_SUGGESTIONS= 100;
    string suggestions[MAX_SUGGESTIONS];

    while (true) {
        cout << "
 input: ";
        getline(cin, userInput);
        if (userInput== "exit") break;
        int found= 0;
        findWords(root,userInput,suggestions,found,MAX_SUGGESTIONS);
        if (found== 0)
            cout<<"no suggestion"<<endl;
        else {
            cout <<"suggestions:"<<endl;
            for (int i=0; i<found;++i)
                cout<<suggestions[i]<<endl;
        }
    }
    return 0;
}