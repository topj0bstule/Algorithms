#include <iostream>
#include <fstream>

struct Tree {
    int number;
    Tree* left;
    Tree* right;
    Tree(int number_) : number(number_), left(nullptr), right(nullptr) {};
};

void printDirectLeftBypass(Tree* tree, std::ofstream& out) {
    if (tree != nullptr) {
        out << tree->number << "\n";
        printDirectLeftBypass(tree->left, out);
        printDirectLeftBypass(tree->right, out);
    }
}

Tree* insertTree(Tree* tree, int& temp) {
    if (tree == nullptr) return new Tree(temp);

    if (temp > tree->number)
        tree->right = insertTree(tree->right, temp);
    else if (temp < tree->number)
        tree->left = insertTree(tree->left, temp);
    return tree;
}

int findMin(Tree* tree) {
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree->number;
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
                tree->number = findMin(tree->right);
                tree->right = delNumFromTree(tree->right, findMin(tree->right));
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

int main()
{
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return 1;
    }

    int delNumber;
    in >> delNumber;
    in.ignore();
    Tree* tree = nullptr;
    int temp = 0;
    while (in >> temp) tree = insertTree(tree, temp);
    in.close();

    tree = delNumFromTree(tree, delNumber);

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return 1;
    }
    printDirectLeftBypass(tree, out);
    out.close();
}