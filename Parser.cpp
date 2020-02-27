#include "Lexer.h"

// Constructs AST Nodes
void BinaryTree::insertLeft(string newNode) {
    if (this->leftChild == NULL) {
        this->leftChild = new BinaryTree(newNode);
    }
    else {
        BinaryTree* t = new BinaryTree(newNode);
        t->leftChild = this->leftChild;
        this->leftChild = t;
    }
}

void BinaryTree::insertRight(string newNode) {
    if (this->rightChild == NULL) {
        this->rightChild = new BinaryTree(newNode);
    }
    else {
        BinaryTree* t = new BinaryTree(newNode);
        t->rightChild = this->rightChild;
        this->rightChild = t;
    }
}

// Traverse between nodes
BinaryTree* BinaryTree::getRightChild() { return this->rightChild; }
BinaryTree* BinaryTree::getLeftChild() { return this->leftChild; }

// Set and get node values
void BinaryTree::setRootVal(string obj) { this->key = obj; }
string BinaryTree::getRootVal() { return this->key; }


// Build the AST given a vector of tokens
BinaryTree* buildParseTree(tokvector tokens) {

    // Defines stack for parent nodes
    stack<BinaryTree*> parentStack;

    // Construct root node
    BinaryTree* eTree = new BinaryTree("");

    // Set current tree to root
    BinaryTree* currentTree = eTree;
    parentStack.push(eTree);

    // Define operators for rules
    vector<string> vect{ "+", "-", "*", "/" };
    vector<string> vect2{ "+", "-", "*", "/", ")" };

    int len = tokens.size();
    int z = 0;
    typeState tState = TSTART;

    while (z < len) {
        switch (tState) {
        case TSTART:
            if (tokens[z].tokVal == "(" || tokens[z].tokType == "Number") {
                currentTree->insertLeft("");
                parentStack.push(currentTree);
                currentTree = currentTree->getLeftChild();
                z++;
                tState = READTOK;
            }
        case READTOK:
            if (tokens[z].tokVal == "(") {
                currentTree->insertLeft("");
                parentStack.push(currentTree);
                currentTree = currentTree->getLeftChild();
                tState = READTOK; z++;
            }

            // Operators push  the pointer to right child
            else if (find(vect.begin(), vect.end(), tokens[z].tokVal) != vect.end()) {
                currentTree->setRootVal(tokens[z].tokVal);
                currentTree->insertRight("");
                parentStack.push(currentTree);
                currentTree = currentTree->getRightChild();
                tState = READTOK; z++;
            }

            // Close brackets backtracks
            else if (tokens[z].tokVal == ")") {
                currentTree = parentStack.top();
                parentStack.pop();
                tState = READTOK; z++;
            }

            // Number sets val and backtracks
            else if (find(vect2.begin(), vect2.end(), tokens[z].tokVal) == vect2.end()) {
                try {
                    currentTree->setRootVal(tokens[z].tokVal);
                    BinaryTree* parent = parentStack.top();
                    parentStack.pop();
                    currentTree = parent;
                    tState = READTOK; z++;
                }

                catch (string ValueError) {
                    cerr << "token " << tokens[z].tokVal << " is not a valid integer" << endl;
                }
            }
        }
    }
    return eTree;
}

void postorderPrint(BinaryTree* tree, string arr[]) {
    static int i = 0;
    if (tree == NULL) return;

    postorderPrint(tree->getLeftChild(), arr);
    postorderPrint(tree->getRightChild(), arr);
    arr[i++] = tree->getRootVal();
}
