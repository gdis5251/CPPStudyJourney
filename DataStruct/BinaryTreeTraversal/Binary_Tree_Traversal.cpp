#include <iostream>
#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};

// 非递归前序遍历
std::vector<int> PreorderTraversal(TreeNode* root)
{
    std::vector<int> ans;
    if (root == nullptr)
    {
        return ans;
    }

    std::stack<TreeNode*> s;
    s.push(root);

    while (!s.empty())
    {
        TreeNode* cur = s.top();
        s.pop();

        ans.push_back(cur->val);

        if (cur->right != nullptr)
        {
            s.push(cur->right);
        }
        
        if (cur->left != nullptr)
        {
            s.push(cur->left);
        }
    }

    return ans;
}


// 非递归中序遍历
std::vector<int> InorderTraversal(TreeNode* root)
{
    std::vector<int> ans;
    if (root == nullptr)
    {
        return ans;
    }

    std::stack<TreeNode*> s;
    TreeNode* cur = root;

    while (cur != nullptr || !s.empty())
    {
        while (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }

        // 走到这里说明向左已经走到底了
        cur = s.top();
        s.pop();

        ans.push_back(cur->val);

        cur = cur->right;
    }

    return ans;
}


// 非递归后序遍历
std::vector<int> PostorderTraversal(TreeNode* root)
{
    std::vector<int> ans;
    if (root == nullptr)
    {
        return ans;

    }

    std::stack<TreeNode*> s;
    TreeNode* cur = root;

    while (cur != nullptr || !s.empty())
    {
        while (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left;

        }

        cur = s.top();

        if (cur->right == nullptr)
        {
            ans.push_back(cur->val);
            s.pop();

            if (!s.empty())
            {
                TreeNode* parent = s.top();
                if (parent->left == cur)
                {
                    parent->left = nullptr;

                }
                else if (parent->right == cur)
                {
                    parent->right = nullptr;

                }

            }
            cur = nullptr;

        }
        else
        {
            cur = cur->right;

        }

    }

    return ans;
}
