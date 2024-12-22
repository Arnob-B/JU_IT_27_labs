class Solution {
  public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
      if(root== NULL) return {};
      queue<TreeNode*>pq;
      bool rev = 1;
      pq.push(root);
      vector<vector<int>> res;
      while(!pq.empty()){
        rev = !rev;
        vector<TreeNode*> arr;
        while(!pq.empty())
        {
          arr.push_back(pq.front());pq.pop();
        }
        vector<int>ires;
        for(TreeNode *it : arr){
          if(it!=nullptr)
          {
            if(it->left!=nullptr)pq.push(it->left);
            if(it->right!=nullptr)pq.push(it->right);
          }            
        }
        if(rev)for(int i= arr.size()-1;i>=0;i--){
          ires.push_back(arr[i]->val);
        }
        else for(int i= 0;i<arr.size();i++){
          ires.push_back(arr[i]->val);
        }
        res.push_back(ires);
      }
      return res;
    }
};
