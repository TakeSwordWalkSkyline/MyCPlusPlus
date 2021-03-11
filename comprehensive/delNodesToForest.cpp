/*Question:
 *给出二叉树的根节点root，树上每个节点都有一个不同的值。
 *如果节点值在to_delete中出现，我们就把该节点从树上删去，最后得到一个森林(一些不相交的树构成的集合)
 *返回森林中的每棵树。你可以按任意顺序组织答案。
 *
 *MyAnswer:
 *后序遍历二叉树,每个节点的值与 to_delete中的所有值进行对比,如果该节点值在to_delete中存在,则将该节点
 *的孩子节点作为新树的根节点存储与vector中返回，并且将该节点(利用引用)置为NULL
 *注意后序遍历可能会导致根节点没有被存储进vector中(当to_delete中没有根节点值时会出现该情况)，因此在 
 *所有子节点都遍历完成以后,需要将根节点push_back到vec中
 */


#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class DeleteNodeToForest {
public:
    // DeleteNodeToForest();
    // ~DeleteNodeToForest();

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete);
private:
    void search(TreeNode* &n, unordered_set<int> &delNodes); //这里n使用的是引用,这样在递归的时候可以访问到上层节点
private:
    vector<TreeNode*> m_forest;
};

void DeleteNodeToForest::search(TreeNode* &n, unordered_set<int> &delSet) {
    if (n == nullptr) {
        return ;
    }
    search(n->left, delSet);
    search(n->right, delSet);
    if (delSet.count(n->val)) {
        if (n->left) {
            m_forest.push_back(n->left);
        }
        if (n->right) {
            m_forest.push_back(n->right);
        }
        n = nullptr;
    }
}

vector<TreeNode*> DeleteNodeToForest::delNodes(TreeNode* root, vector<int> &to_delete) {
    unordered_set<int> del_set(to_delete.begin(), to_delete.end());
    search(root,del_set);
    if (root) {
        m_forest.push_back(root);
    }
    return m_forest;
}

int main() {
    TreeNode *Tree = new TreeNode(1); //root node;
    Tree->left = new TreeNode(2);
    Tree->right = new TreeNode(3);
    Tree->left->left = new TreeNode(4);
    Tree->left->right = new TreeNode(5);
    Tree->right->left = new TreeNode(6);
    Tree->right->right = new TreeNode(7);
    DeleteNodeToForest *DNTF = new DeleteNodeToForest();
    vector<int> v = {3, 5};
    vector<TreeNode*> result = DNTF->delNodes(Tree, v);
    for (vector<TreeNode*>::iterator it = result.begin(); it != result.end(); it ++) {
        std::cout << (*it)->val << std::endl;
        delete *it;
    }
    
    delete DNTF;
    return 0;
}
