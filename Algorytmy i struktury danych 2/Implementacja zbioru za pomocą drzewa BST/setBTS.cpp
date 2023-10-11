#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTSet
{
private:
    TreeNode *root;
    int size;

public:
    BSTSet() : root(NULL), size(0) {}

    int getSize()
    {
        return size;
    }

    void printSet()
    {
        printTree(root);
    }

    void insert(int x)
    {
        root = insertNode(root, x);
    }

    void withdraw(int x)
    {
        root = deleteNode(root, x);
    }

    bool isInSet(int x)
    {
        return searchNode(root, x);
    }

    BSTSet operator+(BSTSet &obj)
    {
        BSTSet res;
        setUnion(root, obj.root, res);
        return res;
    }

    BSTSet operator*(BSTSet &obj)
    {
        BSTSet res;
        setIntersection(root, obj.root, res);
        return res;
    }

    BSTSet operator-(BSTSet &obj)
    {
        BSTSet res;
        setDifference(root, obj.root, res);
        return res;
    }

    bool operator==(BSTSet &obj)
    {
        return isEqual(root, obj.root);
    }

    bool operator<=(BSTSet &obj)
    {
        return isSubset(root, obj.root);
    }

private:
    void printTree(TreeNode *node)
    {
        if (node != NULL)
        {
            printTree(node->left);
            cout << node->val << " ";
            printTree(node->right);
        }
    }

    TreeNode *insertNode(TreeNode *node, int x)
    {
        if (node == NULL)
        {
            node = new TreeNode(x);
            size++;
        }
        else if (x < node->val)
        {
            node->left = insertNode(node->left, x);
        }
        else if (x > node->val)
        {
            node->right = insertNode(node->right, x);
        }
        return node;
    }

    TreeNode *deleteNode(TreeNode *node, int x)
    {
        if (node == NULL)
        {
            return node;
        }
        else if (x < node->val)
        {
            node->left = deleteNode(node->left, x);
        }
        else if (x > node->val)
        {
            node->right = deleteNode(node->right, x);
        }
        else
        {
            if (node->left == NULL)
            {
                TreeNode *temp = node->right;
                delete node;
                size--;
                return temp;
            }
            else if (node->right == NULL)
            {
                TreeNode *temp = node->left;
                delete node;
                size--;
                return temp;
            }
            TreeNode *temp = minValueNode(node->right);
            node->val = temp->val;
            node->right = deleteNode(node->right, temp->val);
        }
        return node;
    }

    TreeNode *minValueNode(TreeNode *node)
    {
        TreeNode *current = node;
        while (current && current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    bool searchNode(TreeNode *node, int x)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->val == x)
        {
            return true;
        }
        if (x < node->val)
        {
            return searchNode(node->left, x);
        }
        else
        {
            return searchNode(node->right, x);
        }
    }

    void setUnion(TreeNode *node1, TreeNode *node2, BSTSet &res)
    {
        if (node1 != NULL)
        {
            res.insert(node1->val);
            setUnion(node1->left, node2, res);
            setUnion(node1->right, node2, res);
        }
        if (node2 != NULL)
        {
            res.insert(node2->val);
            setUnion(node1, node2->left, res);
            setUnion(node1, node2->right, res);
        }
    }

    void setIntersection(TreeNode *node1, TreeNode *node2, BSTSet &res)
    {
        if (node1 == NULL || node2 == NULL)
        {
            return;
        }
        if (node1->val < node2->val)
        {
            setIntersection(node1->right, node2, res);
        }
        else if (node1->val > node2->val)
        {
            setIntersection(node1, node2->right, res);
        }
        else
        {
            res.insert(node1->val);
            setIntersection(node1->left, node2->left, res);
            setIntersection(node1->right, node2->right, res);
        }
    }

    void setDifference(TreeNode *node1, TreeNode *node2, BSTSet &res)
    {
        if (node1 == NULL)
        {
            return;
        }
        if (!searchNode(node2, node1->val))
        {
            res.insert(node1->val);
        }
        setDifference(node1->left, node2, res);
        setDifference(node1->right, node2, res);
    }

    bool isEqual(TreeNode *node1, TreeNode *node2)
    {
        if (node1 == NULL && node2 == NULL)
        {
            return true;
        }
        else if (node1 == NULL || node2 == NULL)
        {
            return false;
        }
        else
        {
            return (node1->val == node2->val) && isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right);
        }
    }

    bool isSubset(TreeNode *node1, TreeNode *node2)
    {
        if (node1 == NULL)
        {
            return true;
        }
        if (node2 == NULL)
        {
            return false;
        }
        if (node1->val == node2->val)
        {
            return isSubset(node1->left, node2->left) && isSubset(node1->right, node2->right);
        }
        if (node1->val < node2->val)
        {
            return isSubset(node1, node2->left);
        }
        else
        {
            return isSubset(node1->left, node2) && isSubset(node1->right, node2);
        }
    }
};
int main()
{
    BSTSet s1;
    s1.insert(3);
    s1.insert(1);
    s1.insert(4);
    s1.insert(2);
    cout << "Size of set s1: " << s1.getSize() << endl;
    cout << "Elements of set s1: ";
    s1.printSet();
    cout << endl;

    BSTSet s2;
    s2.insert(4);
    s2.insert(2);
    s2.insert(5);
    s2.insert(6);
    cout << "Size of set s2:" << s2.getSize() << endl;
    cout << "Elements of set s2: ";
    s2.printSet();
    cout << endl;
    BSTSet s3 = s1 + s2;
    cout << "Union of sets s1 and s2: ";
    s3.printSet();
    cout << endl;

    BSTSet s4 = s1 * s2;
    cout << "Intersection of sets s1 and s2: ";
    s4.printSet();
    cout << endl;

    BSTSet s5 = s1 - s2;
    cout << "Difference of sets s1 and s2: ";
    s5.printSet();
    cout << endl;

    BSTSet s6;
    s6.insert(1);
    s6.insert(2);
    s6.insert(3);
    cout << "Equality of sets s1 and s6: " << (s1 == s6) << endl;
    cout << "Subset relation between sets s1 and s6: " << (s1 <= s6) << endl;

    return 0;
}