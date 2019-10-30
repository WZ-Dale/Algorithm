/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal

给定一个 N 叉树，返回其节点值的层序遍历。 (即从左到右，逐层遍历)。
例如，给定一个 3叉树，返回其层序遍历:
        [
            [1],
            [3,2,4],
            [5,6]
        ]
说明：树的深度不会超过 1000。树的节点总数不会超过 5000。
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int val;
    vector<Node*> children;

    Node(){}

    Node(int _val, vector<Node*> _children){
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    vector<vector<int>> levelOrder(Node* root){
        //定义一个容器，用于返回结果
        vector<vector<int>> treeVec;
        if (root == nullptr){
            return treeVec;
        }
        //临时存放每一层的元素
        vector<int> newFloor;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            //获取当前层元素个数，即整个队列元素
            int size = q.size();
            //存放新层元素之前先清空
            newFloor.clear();
            while(size--){
                //取队首元素
                Node* node = q.front();
                q.pop();
                //添加到数组中
                newFloor.push_back(node->val);
                //并将其孩子入队
                for(auto& child : node->children){
                    if(child){
                        q.push(child);
                    }
                }
            }
            //新层有元素,则放入vector
            if(!newFloor.empty()){
                treeVec.push_back(newFloor);
            }
        }
        return treeVec;
    }
};
void print_vv(vector<vector<int>>& vv){
    for(int i = 0; i < vv.size(); ++i){
        for(int j = 0; j < vv[i].size(); ++j){//注意这里当前第几行就计算第几行的size
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    Node node5(5, {}), node6(6, {});
    Node node3(3, {&node5, &node6}), node2(2, {}), node4(4, {});
    Node node1(1, {&node3, &node2, &node4});
    Solution S;
    vector<vector<int>> vv = S.levelOrder(&node1);
    print_vv(vv);
    return 0;
}