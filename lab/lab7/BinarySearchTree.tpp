#include <iostream>
using namespace std;
template <typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const string &name, const T1 &x, const T2 &y) : name(name), score{x, y}, left_sub_tree(nullptr), right_sub_tree(nullptr) {}

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const BinarySearchTree<T1, T2> &other_tree) : // TODO 1: copy the members of this node and two subtrees
                                                                                         BinarySearchTree(other_tree.name, other_tree.score.baseScore, other_tree.score.bonusScore)
{
    if (other_tree.left_sub_tree != nullptr)
    {
        this->left_sub_tree = new BinarySearchTree(*(other_tree.left_sub_tree));
    }
    if (other_tree.right_sub_tree != nullptr)
    {
        this->right_sub_tree = new BinarySearchTree(*(other_tree.right_sub_tree));
    }
}

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::~BinarySearchTree()
{
    // TODO 2: release the resources occupied by the two subtrees
    delete left_sub_tree;
    delete right_sub_tree;
}

template <typename T1, typename T2>
int BinarySearchTree<T1, T2>::size() const
{
    // TODO 3: return the size of the tree by recursively compute the size
    int left = 0;
    int right = 0;
    if (this->left_sub_tree == nullptr && this->right_sub_tree == nullptr)
    {
        return 1;
    }
    if (this->left_sub_tree != nullptr)
    {
        left = this->left_sub_tree->size();
    }
    if (this->right_sub_tree != nullptr)
    {
        right = this->right_sub_tree->size();
    }
    return (left + right + 1);
}

template <typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByScorePair(const T1 &x, const T2 &y) const
{
    // TODO 4: find the name of the node by the score.
    // If the score exists, call printName(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: call the function recursively
    // **Note**: You are expected to search either left or right tree and compare the value to get the node contains target ScorePair.
    bool left = false;
    bool right = false;
    if (x == this->score.baseScore && y == this->score.bonusScore)
    {
        printName();
        return true;
    }
    else if (x < this->score.baseScore || (x == this->score.baseScore && y < this->score.bonusScore))
    {
        if (this->left_sub_tree != nullptr)
        {
            left = this->left_sub_tree->findByScorePair(x, y);
        }
    }
    else
    {
        if (this->right_sub_tree != nullptr)
        {
            right = this->right_sub_tree->findByScorePair(x, y);
        }
    }
    return (left || right);
}

template <typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByName(const string &name) const
{
    // TODO 5: find the score of the node by the name.
    // If the score exists, call printPoint(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: use 'a.compare(b)' or 'a == b' to do the string comparison.
    bool left = false;
    bool right = false;
    if (this->name == name)
    {
        printPoint();
        return true;
    }
    if (this->left_sub_tree == nullptr && this->right_sub_tree == nullptr)
    {
        return false;
    }
    if (this->left_sub_tree != nullptr)
    {
        left = this->left_sub_tree->findByName(name);
    }
    if (this->right_sub_tree != nullptr)
    {

        right = this->right_sub_tree->findByName(name);
    }
    return (left || right);
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::insert(const string &name, const T1 &x, const T2 &y)
{
    if (findByName(name) || findByScorePair(x, y))
    {
        cout << "The data exists." << endl;
        return;
    }
    // TODO 6: Insert a node to the tree. Do nothing if any of name or score exists. (Which is given)
    // implement the remaining code below
    if (x < this->score.baseScore || (x == this->score.baseScore && y < this->score.bonusScore))
    {
        if (this->left_sub_tree != nullptr)
        {
            this->left_sub_tree->insert(name, x, y);
        }
        else
        {
            this->left_sub_tree = new BinarySearchTree(name, x, y);
        }
    }
    else if (x > this->score.baseScore || (x == this->score.baseScore && y > this->score.bonusScore))
    {
        if (this->right_sub_tree != nullptr)
        {
            this->right_sub_tree->insert(name, x, y);
        }
        else
        {
            this->right_sub_tree = new BinarySearchTree(name, x, y);
        }
    }
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::inorderTraversal() const
{
    // TODO 7: run printAll() by in order traversal
    if (this)
    {
        this->left_sub_tree->inorderTraversal();
        this->printAll();
        this->right_sub_tree->inorderTraversal();
    }
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::printName() const
{
    cout << "The name is " << name << "." << endl;
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::printPoint() const
{
    cout << "The score is "
         << "(" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::printAll() const
{
    cout << "Name: " << name << ", "
         << "Point: (" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}
