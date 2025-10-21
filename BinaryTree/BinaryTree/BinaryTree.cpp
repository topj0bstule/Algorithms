#include <iostream>
#include <fstream>
#include <vector>

struct Tree {
    int number;
    Tree* left;
    Tree* right;
    Tree(int number_) : number(number_), left(nullptr), right(nullptr) {};
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

Tree* insertTree(Tree* tree, int& temp) {
    if (tree == nullptr) return new Tree(temp);
    if (temp > tree->number)
        tree->right = insertTree(tree->right, temp);
    else if (temp < tree->number)
        tree->left = insertTree(tree->left, temp);
    return tree;
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

int treeHeight(Tree* tree) {
    if (tree == nullptr) return 0;
    return max(treeHeight(tree->right), treeHeight(tree->left)) + 1;
}

int kolvoNumbers(Tree* tree) {
    if (tree != nullptr)
        return 1 + kolvoNumbers(tree->left) + kolvoNumbers(tree->right);
    else return 0;
}

bool equalHeightSubtree(Tree* tree) {
    if (tree == nullptr) return 1;
    return treeHeight(tree->left) == treeHeight(tree->right) ? 1 : 0;
}

bool equalKolvoNumbers(Tree* tree) {
    if (tree == nullptr) return 1;
    return kolvoNumbers(tree->left) == kolvoNumbers(tree->right) ? 1 : 0;
}

std::vector<int> findAllEverageEl(Tree* tree, std::vector<int>& result) {
    if (tree == nullptr) return result;
    findAllEverageEl(tree->left, result);
    if (equalHeightSubtree(tree) && !equalKolvoNumbers(tree))
        result.push_back(tree->number);
    findAllEverageEl(tree->right, result);
    return result;
}

int findEverageValue(std::vector<int> result) {
    if (result.size() == 0 || result.size() % 2 == 0) return -1;
    return result[result.size() / 2];
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
    while (in >> temp) tree = insertTree(tree, temp);
    in.close();

    std::vector<int> result;
    findAllEverageEl(tree, result);
    if (!result.empty())
        tree = delNumFromTree(tree, findEverageValue(result));

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return 1;
    }
    printDirectLeftBypass(tree, out);
    out.close();
    deleteTree(tree);
}