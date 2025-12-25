#include <iostream>
#include <fstream>

struct Tree {
    int number;
    int height = 0;
    int kolvoVershin = 0;
    bool isIt = 0;
    Tree* left = nullptr;
    Tree* right = nullptr;
    Tree(int number_) : number(number_){}
};

int max(int a, int b) {
    return a > b ? a : b;
}

void printDirectLeftBypass(Tree* tree, std::ofstream& out) {
    if (tree != nullptr) {
        out << tree->number << "\n";
        printDirectLeftBypass(tree->left, out);
        printDirectLeftBypass(tree->right, out);
    }
}

void insertTree(Tree*& root, int temp) {
    Tree** link = &root;
    while (*link) {
        Tree* node = *link;
        if (temp < node->number) link = &node->left;
        else if (temp > node->number) link = &node->right;
        else return;
    }
    *link = new Tree(temp);
}


Tree* delNumFromTree(Tree* tree, int number) {
    if (tree != nullptr) {
        if (number < tree->number) tree->left = delNumFromTree(tree->left, number);
        else if (number > tree->number) tree->right = delNumFromTree(tree->right, number);
        else {
            if (tree->left == nullptr && tree->right == nullptr) {
                delete tree;
                return nullptr;
            }
            else if (tree->left != nullptr && tree->right != nullptr) {
                Tree* temp = tree->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                tree->number = temp->number;
                tree->right = delNumFromTree(tree->right, tree->number);
                return tree;
            }
            else {
                if (tree->left != nullptr) {
                    Tree* temp = tree->left;
                    delete tree;
                    return temp;
                }
                else {
                    Tree* temp = tree->right;
                    delete tree;
                    return temp;
                }
            }
        }
    }
    else return nullptr;
    return tree;
}

void treeAction(Tree* tree, int& count) {
    if (tree == nullptr) return;
    treeAction(tree->left, count);
    treeAction(tree->right, count);
    if (tree->left == nullptr && tree->right == nullptr) {
        tree->height = 0;
        tree->kolvoVershin = 1;
        tree->isIt = false;
    }
    else if (tree->left == nullptr){
        tree->height = tree->right->height + 1;
        tree->kolvoVershin = tree->right->kolvoVershin + 1;
        tree->isIt = false;
    }
    else if (tree->right == nullptr) {
        tree->height = tree->left->height + 1;
        tree->kolvoVershin = tree->left->kolvoVershin + 1;
        tree->isIt = false;
    }
    else {
        tree->height = max(tree->left->height, tree->right->height) + 1;
        tree->kolvoVershin = tree->left->kolvoVershin + tree->right->kolvoVershin + 1;
        if ((tree->left->height == tree->right->height) && (tree->left->kolvoVershin != tree->right->kolvoVershin)) {
            tree->isIt = true;
            count++;
        }
        else tree->isIt = false;
    }
}

int findEverageValue(Tree* tree, int& count, int& temp) {
    if (tree == nullptr) return -1;
    int left = findEverageValue(tree->left, count, temp);
    if (left != -1) return left;
    if (tree->isIt) {
        if (temp == count) return tree->number;
        temp++;
    }
    int right = findEverageValue(tree->right, count, temp);
    if (right != -1) return right;
    return -1;
}


void deleteTree(Tree* tree) {
    if (tree == nullptr) return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    delete tree;
}

int main()
{
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return 1;
    }

    Tree* tree = nullptr;
    int temp = 0;
    while (in >> temp) insertTree(tree, temp);
    in.close();

    int count = 0;
    treeAction(tree, count);

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return 1;
    }
    if (count % 2 == 1) {
        int tempCounter = 0;
        count /= 2;
        tree = delNumFromTree(tree, findEverageValue(tree, count, tempCounter));
    }
    printDirectLeftBypass(tree, out);
    out.close();
    deleteTree(tree);

    return 0;
}