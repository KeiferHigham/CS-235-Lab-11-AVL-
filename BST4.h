#ifndef AVLFINALLAB_BST4_H
#define AVLFINALLAB_BST4_H

#include "BST4Interface.h"
#include "sstream"

using namespace std;


template<typename T>

class BinaryTree : public BSTInterface<T> {

private:


    struct BTNode {

        BTNode(const T &inputData, BTNode *leftValue = NULL, BTNode *rightValue = NULL) {
            data = inputData;
            left = leftValue;
            right = rightValue;
        }

        ~BTNode() {};

        T data;
        BTNode *left;
        BTNode *right;
    };

    BTNode* root;
public:

    BinaryTree() {
        root = NULL;    // sets the data value to 3 and default parameters of node constructor point to Null
    }
    ~BinaryTree() {
        clearTree();
    }


    /** Return true if node added to BST, else false */
    bool addNode(const T& item) {
        return addNode(this->root, item);
    }

    bool addNode(BTNode*& regionalRoot, const T& item) {     // I need to be able to pass in parameter of type BtNODE pointer
        bool returnVal;
        if(regionalRoot == NULL) {
            regionalRoot = new BTNode(item);
            return true;
        }
        else {
            if(item < regionalRoot->data) {
               returnVal = addNode(regionalRoot->left, item);
               if (returnVal) Balance(regionalRoot);
               return returnVal;

            }
            else if(regionalRoot->data < item) {
                returnVal = addNode(regionalRoot->right, item);
                if (returnVal) Balance(regionalRoot);
                return returnVal;
            }
            else {
                return false;
            }
        }
    }

    /** Return true if node removed from BST, else false */
    bool removeNode(const T& item) {

        return removeNode(root, item);
    }

    bool removeNode(BTNode*& regionRoot, const T& item) {
        bool returnVal;

        if(regionRoot == NULL) {
            return false;
        }
        else {
            if(item < regionRoot->data) {
                returnVal = removeNode(regionRoot->left, item);
                if(returnVal) {
                   Balance(regionRoot);
                }
                return returnVal;
            }
            else if(regionRoot->data < item){
                returnVal = removeNode(regionRoot->right, item);
                if(returnVal) {
                    Balance(regionRoot);
                }
                return returnVal;
            }
            else {
                BTNode* oldRoot = regionRoot;
                 if(regionRoot->right == NULL && regionRoot->left == NULL) {
                      regionRoot = NULL;
                }

                else if(regionRoot->left == NULL) {
                    regionRoot = regionRoot->right;
                    Balance(regionRoot);
                }
                else if(regionRoot->right == NULL) {
                    regionRoot = regionRoot->left;
                    Balance(regionRoot);
                }
                else {
                    Replace(oldRoot, oldRoot->left);
                      Balance(regionRoot);
                }
                delete oldRoot;
                return true;
            }
        }
    }


    /** Return true if BST cleared of all nodes, else false */
    bool clearTree() {
        clearTree(root);
        root = NULL;
        if(root == NULL) {
            return true;
        }
        return false;
    }

    void clearTree(BTNode*& r) {
        if(r == NULL) {
            return;
        }
        clearTree(r->left);
        clearTree(r->right);
        cout << r->data << endl;
        delete r;
    }
    int compare(int a, int b) {
        if(a >= b) {
            return a;
        }
        else {
            return b;
        }
    }

    int getHeight(BTNode* localRoot) {
        if(localRoot == NULL) {
            return 0;
        }
        return max(getHeight(localRoot->left), getHeight(localRoot->right)) + 1;
    }
    void RotateRight(BTNode*& root) {
        BTNode* temp = root->left;
        root->left = temp->right;
        temp->right = root;
        root = temp;
    }

    void RotateLeft(BTNode*& root)  {
        BTNode* temp = root->right;
        root->right = temp->left;
        temp->left = root;
        root = temp;
    }
    int difference(BTNode* temp) {
        if(temp == NULL) {
            return 0;
        }
        int leftHeight = getHeight(temp->left);
        int rightHeight = getHeight(temp->right);
        int difference = rightHeight - leftHeight;
        return difference;
    }

    void Balance(BTNode*& localRoot) {
        if (localRoot == NULL) return;
        if (difference(localRoot) == -2 && difference(localRoot->left) <= 0) {
            RotateRight(localRoot);
        } else if (difference(localRoot) == 2 & difference(localRoot->right) >= 0) {
            RotateLeft(localRoot);
        } else if (difference(localRoot) == -2 && difference(localRoot->left) == 1) {
            RotateLeft(localRoot->left);     // turns tree into a left left tree
            RotateRight(localRoot);          // balances the tree
        } else if (difference(localRoot) == 2 && difference(localRoot->right) == -1) {
            RotateRight(localRoot->right); // turns tree into a right right tree
            RotateLeft(localRoot); // balances the tree
        }
    }

    void Replace(BTNode*& oldRoot, BTNode*& regionalRoot) {
        if(regionalRoot->right != NULL) {
            Replace(oldRoot, regionalRoot->right);
            Balance(regionalRoot);
        }
        else  {
            oldRoot->data = regionalRoot->data;
            oldRoot = regionalRoot;
            regionalRoot = regionalRoot->left;
        }
    }

    /** Return a level order traversal of a BST as a string */
    string toString() const {
        stringstream out;
        if (root == NULL) {
            out << " empty";
        }
        else
        {
            int level = 0;
            do
            {
                out << endl << "  " << ++level << ":";
            } while (outLevel(root, level, out));
        }
        return out.str();

    }

    /** Output nodes at a given level */
    bool outLevel(BTNode* root, int level, stringstream& out) const {
        if (root == NULL) {
            return false;
        }
        if (level == 1)
        {
            out << " " << root->data;
            if ((root->left != NULL) || (root->right != NULL)) {
                return true;
            }

            else  {
                return false;
            }
        }
        if ((level == 2) && root->left == NULL && root->right != NULL) {
            out << " _";
        }
        bool left = outLevel(root->left, level - 1, out);
        bool right = outLevel(root->right, level - 1, out);
        if ((level == 2) && root->left != NULL && !root->right) {
            out << " _";
        }
        return left || right;
    } // end outLevel()

    int Size(BTNode *r) {
        if(r == NULL) {
            return 0;
        }
        else {
            return(Size(r->left) + 1 + Size(r->right));
        }
    }

    int Size() {
        return Size(root);
    }

    bool Find(const T& value, BTNode* r) {
        if(r == NULL) {
            return false;
        }
        else if(value == r->data) {
            return true;
        }
        else if(value < r->data) {
            return Find(value, r->left);
        }
        else if(value > r->data) {
            return Find(value, r->right);
        }
    }

    bool Find(const T& value) {
        return Find(value, root);
    }






};
#endif //AVLFINALLAB_BST4_H
