class Solution {
    public:
        int maxPathSum(TreeNode *root) {
                int res = root->val;
                maxPathSumDFS(root, res);
        return res;
    }
    int maxPathSumDFS(TreeNode *root, int &res) {
        if (!root) return 0;
        int left = maxPathSumDFS(root->left, res);
        int right = maxPathSumDFS(root->right, res);
        int top = root->val + (left > 0 ? left : 0) + (right > 0 ? right : 0);
        res = max(res, top); // 这里是假设以当前节点为根节点时，用其值去更新全局最大值
        if (max(left, right) > 0){
            // 这种情况是以左右子树某一条路径和当前路径返回给父节点，进行递归求值
            return max(left, right) + root->val;
        }
        else{
            // 这种情况是左右子树路径和都小于0，则返回此节点的权值给父节点进行递归求值
            return root->val;
        }
    }
};
