#include<iostream>
#include<queue>
#include<map>


using namespace std;

class Node
{
    public:
    int data;
    Node * left;
    Node * right;

    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

Node * buildTree(Node * root)
{
    
    cout<<"Enter the data to be inserted"<<endl;
    int data;
    cin>>data;
    root = new Node (data);

    if(data==-1)
    {
        return NULL;
    }

    cout<<"Enter the data to be inserted on the left of the data "<<data<<endl;
    root->left = buildTree(root->left);
    cout<<"Enter the data to be inserted on the right of the data "<<data<<endl;
    root->right = buildTree(root->right);
    return root;

}

void levelOrderTraversal(Node * root)
{
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node * temp = q.front();
        q.pop();

        if(temp==NULL)
        {
            cout<<endl;
            if(!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout<<temp->data<<" ";
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }
    
}
void inorder(Node * root)
{
    if(root==NULL)
    {
        return;
    }

    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void preorder(Node * root)
{
    if(root==NULL)
    {
        return;
    }

    cout<<root->data<<" ";

    preorder(root->left);
    preorder(root->right);
}

void postorder(Node * root)
{
    if(root==NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

void buildFromLevelOrder(Node *& root)
{
    queue<Node*> q;
    cout<<"Enter the data of the root"<<endl;
    int rootData;
    cin>>rootData;
    Node * root = new Node(root->data);
    q.push(root);

    while (!q.empty())
    {
        Node * temp = q.front();
        q.pop();

        cout<<"Enter the left node for"<<temp->data<<endl;
        int leftdata;
        cin>>leftdata;

        if(leftdata!=-1)
        {
            temp->left = new Node(leftdata);
            q.push(temp->left);
        }

        cout<<"Enter the right node for"<<temp->data<<endl;
        int rightdata;
        cin>>rightdata;
        
        if(rightdata!=-1)
        {
            temp->right = new Node(rightdata);
            q.push(temp->right);
        }
    }
    

}

//Q1 HEIGHT OF THE TREE

int height(Node * root)
{
    if(root==NULL)
    {
        return 0;
    }

    int left = height(root->left);
    int right = height(root->right);
    int ans = max(left,right)+1;
    return ans;
}


//Q2 DIAMETER OF THE TREE

int diameter(Node * root)
{
    if(root==NULL)
    {
        return 0;
    }

    int op1 = diameter(root->left);
    int op2 = diameter(root->right);
    int op3 = height(root->left)+height(root->right)+1;
    int ans = max(op1,max(op2,op3));
    return ans;
}

pair<int,int> diameterpairs(Node * root)
{
    if(root==NULL)
    {
        pair<int,int> p = make_pair(0,0);
        return p;
    }

    pair<int,int> left = diameterpairs(root->left);
    pair<int,int> right = diameterpairs(root->right);

    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + left.first + 1;

    pair<int,int> ans;

    ans.first = max(op1,max(op2,op3));
    ans.second = max(left.second,right.second) +1;
    return ans;
}

//Q3 CHECK BINARY TREE IS BALANCED OR NOT

bool isBalanced(Node * root)
{
    if(root==NULL)
    {
        return true;
    }

    bool left = isBalanced(root->left);
    bool right = isBalanced(root->right);

    bool diff = abs(height(root->left)-height(root->right))<=1;

    if(left && right && diff)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

pair<bool,int> isBalancedPair(Node * root)
{
    if(root==NULL)
    {
        pair<bool,int> p = make_pair(true,0);
        return p;
    }

    pair<bool,int> left = isBalancedPair(root->left);
    pair<bool,int> right = isBalancedPair(root->right);

    bool leftAns = left.first;
    bool rightAns = right.first;

    bool diff = abs(left.second-right.second)<=1;
    pair<bool,int> ans;
    ans.second = max(left.second,right.second)+1;

    if(leftAns && rightAns && diff)
    {
        ans.first = true;
    }
    else
    {
        ans.first = false;
    }

    return ans;
}

//Q4 DETERMINE IF TWO TREES ARE IDENTICAL OR NOT

bool isIdentical(Node * r1, Node * r2)
{
    if(r1==NULL && r2==NULL)
    {
        return true;
    }
    if(r1==NULL && r2!=NULL)
    {
        return false;
    }
    if(r1!=NULL && r2==NULL)
    {
        return false;
    }

    bool left = isIdentical(r1->left,r2->left);
    bool right = isIdentical(r1->right,r2->right);

    bool val = r1->data == r2->data;
    if(left && right && val)
    {
        return true;
    }
    else
    {
        return false;
    }

}


//Q5 CHECK SUMTREE - ROOT DATA IS EQUAL TO THE SUM OF ITS LEFT SUBTREE AND RIGHT SUBTREE.

pair<bool,int> isCheckSum(Node * root)
{
    if(root==NULL)
    {
        pair<bool,int> p = make_pair(true,0);
        return p;
    }

    if(root->left==NULL && root->right==NULL)
    {
        pair<bool,int> p = make_pair(true, root->data);
        return p;
    }

    pair<bool,int> leftAns = isCheckSum(root->left);
    pair<bool,int> rightAns = isCheckSum(root->right);

    bool left = leftAns.first;
    bool right = rightAns.first;

    int leftSum = leftAns.second;
    int rightSum = rightAns.second;

    pair<bool,int> ans;

    bool con = root->data == leftSum+rightSum;

    if(left && right && con)
    {
        ans.first = true;
        ans.second = root->data+ leftSum + rightSum;
    }
    else
    {
        ans.first = false;
    }

    return  ans;

}

bool isCheck(Node * root)
{
    return isCheckSum(root).first;
}


//Q6 ZIGZAG TRAVERSAL

vector<int> zigzagTraversal(Node * root)
{
    vector<int> result;
    if(root==NULL)
    {
        return result;
    }
    queue<Node*> q;
    q.push(root);
     
    bool LeftToRight = true;
    while(!q.empty())
    {
        int size = q.size();
        vector<int> ans(size);
        for (int i = 0; i < size; i++)
        {
            Node * frontNode = q.front();
            q.pop();
            int index = LeftToRight ? i: size-i-1;
            ans[index] = frontNode->data;

            if(frontNode->left)
            {
                q.push(frontNode->left);
            }

            if(frontNode->right)
            {
                q.push(frontNode->right);
            }

        }

        LeftToRight =!LeftToRight;

        for(auto i: ans)
        {
            result.push_back(i);
        }
        
    }
    return result;

}


//Q7 boundary traversal

void traversalLeft(Node * root, vector<int> ans)
{
    if((root==NULL)||(root->left==NULL && root->right==NULL))
    {
        return;
    }

    ans.push_back(root->data);

    if(root->left)
    {
        traversalLeft(root->left,ans);
    }
    else
    {
        traversalLeft(root->right,ans);
    }
}

void traversalLeaf(Node * root, vector<int> ans)
{
    if(root==NULL)
    {
        return;
    }

    if(root->left==NULL && root->right==NULL)
    {
        ans.push_back(root->data);
        return;
    }

    traversalLeaf(root->left,ans);
    traversalLeaf(root->right,ans);
}


void traversalRight(Node * root, vector<int> ans)
{
    if((root==NULL)||(root->left==NULL && root->right==NULL))
    {
        return;
    }

    if(root->right)
    {
        traversalRight(root->right,ans);
    }
    else
    {
        traversalRight(root->left,ans);
    }

    ans.push_back(root->data);
}
vector<int> boundaryTraversal(Node * root)
{
    vector<int> result;
    if(root==NULL)
    {
        return result;
    }
    result.push_back(root->data);

    traversalLeft(root->left,result);

    traversalLeaf(root->left,result);
    traversalLeaf(root->right,result);

    traversalRight(root->right, result);

    return result;
}


//Q8 - TOP VIEW OF THE BINARY TREE

vector<int> topview(Node * root)
{
    vector<int> ans;
    if(root==NULL)
    {
        return ans;
    }

    map<int,int> topNode;
    queue<pair<Node* ,int>> q;
    q.push(make_pair(root,0));

    while(!q.empty())
    {
        pair<Node * ,int> temp = q.front();
        q.pop();
        
        Node * frontNode  = temp.first;
        int hd = temp.second;

        if(topNode.find(hd)==topNode.end())
        {
            topNode[hd] = frontNode->data;
        }

        if(frontNode->left)
        {
            q.push(make_pair(frontNode->left,hd-1));
        }
        if(frontNode->right)
        {
            q.push(make_pair(frontNode->right,hd+1));
        }

    }

    for(auto i: topNode)
    {
        ans.push_back(i.second);
    }
    return ans;
}

/*Q9  SumOfBloodLine(Given a binary tree of size N. Your task is to complete the function sumOfLongRootToLeafPath(), that find the sum of all nodes on the longest path from root to leaf node.
If two or more paths compete for the longest path, then the path having maximum sum of nodes is being considered.)*/

void solve(Node * root,int len, int &maxLen, int sum, int &maxSum)
{
    if(root==NULL)
    {
        if(len> maxLen)
        {
            maxLen = len;
            maxSum = sum;
        }

        else if(len == maxLen)
        {
            sum = max(sum,maxSum);
        }
        return;
    }

    sum = sum+ root->data;

    solve(root->left, len+1, maxLen,sum,maxSum);
    solve(root->right,len+1,maxLen,sum,maxSum);
}

int sumOfLongRootToLeafNode(Node * root)
{
    int len = 0;
    int maxLen = 0;
    int sum = 0;
    int maxSum = INT_MIN;
 
    solve(root,len, maxLen,sum,maxSum);
    return maxSum;
}


/*Q10 Given a Binary Tree with all unique values and two nodes value, n1 and n2. 
The task is to find the lowest common ancestor of the given two nodes. We may assume that either
 both n1 and n2 are present in the tree or none of them are present.*/

Node * lca(Node * root, int n1, int n2)
{
    if(root==NULL)
    {
        return NULL;
    }

    if(root->data==n1 || root->data==n2)
    {
        return root;
    }

    Node * leftAns = lca(root->left, n1,n2);
    Node * rightAns = lca(root->right,n1,n2);

    if(leftAns!=NULL && rightAns!=NULL)
    {
        return root;
    }
    else if(leftAns!=NULL && rightAns==NULL)
    {
        return leftAns;
    }
    else if(leftAns==NULL && rightAns!=NULL)
    {
        return rightAns;
    }
    else
    {
        return;
    }
}


/*Q11 Given a binary tree and an integer K. Find the number of paths in the tree which have their sum equal to K.
A path may start from any node and end at any node in the downward direction.*/

void solvek(Node * root, int k ,vector<int> path, int &count)
{
    if(root==NULL)
    {
        return;
    }
    path.push_back(root->data);

    solvek(root->left, k, path,count);
    solvek(root->right, k, path, count);

    int size = path.size();
    int sum = 0;
    for(int i = size-1;i>=0;i--)
    {
        sum += path[i];
        if(sum==k)
        {
            count++;
        }
    }
}

int sumk(Node * root, int k)
{
    int count = 0;
    vector<int> path;
    solvek(root,k,path,count);
    return count;
}

//Q12 Given a binary tree of size  N, a node and a positive integer k., Your task is to complete the function kthAncestor(), the function should return the kth ancestor of the given node in the binary tree. If there does not exist any such ancestor then return -1.

Node * solvekth(Node * root, int node , int &k)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data == node)
    {
        return root;
    }

    Node * leftAns = solvekth(root->left,node,k);
    Node * rightAns = solvekth(root->right,node,k);

    if(leftAns!=NULL && rightAns==NULL)
    {
        k--;
        if(k<=0)
        {
            k = INT_MAX;
            return root;
        }
        return leftAns;
    }

    if(leftAns==NULL && rightAns!=NULL)
    {
        k--;
        if(k<=0)
        {
            k = INT_MAX;
            return root;
        }
        return rightAns;
    }
    return NULL;

}
int kAncestor(Node * root, int node, int k)
{
    Node * ans = solvekth(root,node,k);
    if(ans==NULL || ans->data==node)
    {
        return -1;
    }
    else
    {
        return ans->data;
    }
    return 0;
}


/*Q13 Given a binary tree with a value associated with each node,
 we need to choose a subset of these nodes such that sum of chosen 
 nodes is maximum under a constraint that no two chosen node in subset should be directly connected that is, 
 if we have taken a node in our sum then 
we can’t take its any children or parents in consideration and vice versa.*/
pair<int,int> solve1(Node * root)
{
    if(root==NULL)
    {
        pair<int,int> p = make_pair(0,0);
        return p;
    }

    pair<int,int> left = solve1(root->left);
    pair<int,int> right = solve1(root->right);

    pair<int,int> res;
    res.first = root->data + left.second+ right.second;
    res.second = max(left.first,left.second)+ max(right.first,right.second);

    return res;
}

int getMaxSum(Node * root)
{
    pair<int,int> ans = solve1(root);
    return max(ans.first,ans.second);
}

Node * createMapping(Node * root, int target, map<Node*, Node *> &NodeToParent)
{
    queue<Node*> q;
    q.push(root);
    NodeToParent[root] = NULL;
    Node * res ;
    while(!q.empty())
    {
        Node * front = q.front();
        q.pop();

        if(front->data==target)
        {
            res = front;
        }
        if(front->left)
        {
            q.push(front->left);
            NodeToParent[front->left] = front;
        }
        if(front->right)
        {
            q.push(front->right);
            NodeToParent[front->right] = front;
        }
    }
    return res;
}

int burnTree(Node * root, Node * targetNode, map<Node * , Node *> &NodeToParent)
{
    map<Node*, bool> visited;
    queue<Node * > q;

    q.push(root);
    visited[root] = true;
    int ans = 0;
    bool flag = 0;

    while(!q.empty())
    {
        int size = q.size();
        for(int i=0;i<size;i++)
        {
            Node * front = q.front();
            q.pop();
            if(front->left && !visited[front->left])
            {
                flag = 1;
                q.push(front->left);
                visited[front->left] = 1;
            }
            if(front->right && !visited[front->right])
            {
                flag = 1;
                q.push(front->right);
                visited[front->right] = 1;
            }
            if(NodeToParent[front] && !visited[NodeToParent[front]])
            {
                flag = 1;
                q.push(NodeToParent[front]);
                visited[NodeToParent[front]] = 1;
            }
        }

        if(flag==1)
        {
            ans++;
        }
    }
    return ans;
}

int burning(Node * root , int target)
{
    map<Node* , Node *> NodeToParent;
    Node * targetNode = createMapping(root,target,NodeToParent);
    int ans = burnTree(root,targetNode,NodeToParent);
    return ans;
}

int main()
{
    Node * root = NULL;
    root = buildTree(root);

    levelOrderTraversal(root);
}