#include <iostream>
#include <vector>
/**
 * Definition for a binary tree node.*/
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/*
 * Quetion:
 * 实现一个二叉搜索树迭代器。你将使用二叉搜索树的根节点初始化迭代器。
 * 调用 next() 将返回二叉搜索树中的下一个最小的数。
 * My answer:
 * 通过中序遍历二叉树,将所有元素从小到大返回并存储在vector中
 * 调用next()函数时依次返回vector中的元素
 * 调用hasNext()函数时判断cursor是否超出vector size
 */
class BSTIterator {
public:
    BSTIterator(TreeNode* root):m_bst(root),
                                m_cursor(0) {}
    int next() {
        int a = 0;
        if (orderly_vec.empty()) {
            in(m_bst);
        }
        a = orderly_vec[m_cursor];
        m_cursor ++;
        return a;
    }
    
    bool hasNext() {
        // 判断!orderly_vec.empty()是为了防止在调用next之前调用hasNext,因为此时orderly_vec中没有元素
        // 如果二叉树不为空,但又还未调用next,则应该返回true而不是false
        if (m_cursor >= orderly_vec.size() && !orderly_vec.empty()) { 
            return false;
        } else {
            return true;
        }
    }
private:
    void in(TreeNode *n) {
        if (n != NULL) {
            in(n->left);
            orderly_vec.push_back(n->val);
            in(n->right);
        }
    }
private:
    TreeNode *m_bst;
    std::vector<int> orderly_vec;
    int m_cursor;
};

int main() {
    return 0;
}
