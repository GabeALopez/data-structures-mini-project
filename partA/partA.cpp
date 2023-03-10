#include <iostream>
#include <vector>

using namespace std;
class Node {
  public: 
  int data;
  unsigned int height;
  Node * left;
  Node * right;
  Node * parent;
  Node() {
    data = 0;
    height = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
  }
  Node(int val) {
    data = val;
    height = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
  }
};

void inorder(Node * currentPtr);
Node * insert(Node * root, Node * element);
int add(Node * currentPtr);
int find(Node * currentPtr, int val);
Node * parent(Node * root, Node * node);
Node * minVal(Node * root);
Node * maxVal(Node * root);
int isLeaf(Node * node);
int hasOnlyLeftChild(Node * node);
int hasOnlyRightChild(Node * node);
Node * findNode(Node * currentPtr, int value);
Node * deleteNode(Node * root, int value);
int menu();
Node * next(Node * root, Node * N);
Node * leftDescendant(Node * N);
Node * rightAncestor(Node * root, Node * N);
vector<int> rangeSearch(int low, int high, Node * root);
int computeHeight(Node * targetNode);
bool isUnbalanced(Node * root, Node * workingNode);
int findLowestLeafHeight(Node * root, Node * workingNode);
void rotateRight(Node * workingNode);
void rotateLeft(Node * workingNode);
int balanceFactor(Node * root, Node * targetNode);
void adjustHeight(Node * targetNode);
void rebalance(Node * targetNode);
void rebalanceRight(Node * targetNode);
void rebalanceLeft(Node * targetNode);
void AVLInsert(Node * root, Node * workingNode);
void AVLDelete(Node * root, Node * workingNode);
bool avlInitialCheck(Node * targetNode);



void inorder(Node * currentPtr) {
  // Only traverse the node if it's not null.
  if (currentPtr != NULL) {
    inorder(currentPtr -> left); // Go Left.
    cout << " " << currentPtr -> data; // Print the root.
    inorder(currentPtr -> right); // Go Right.
  }
}


Node * insert(Node * root, Node * element) {
  // Inserting into an empty tree.
  if (root == NULL) {
    element->height = 0;
    return element;
  } else {
    // element should be inserted to the right.
    element->height++;
    //* element->parent = parent(root, element);
    if (element -> data > root -> data) {
      // There is a right subtree to insert the node.
      if (root -> right != NULL)
      {
        root -> right = insert(root -> right, element);
      }
      // Place the node directly to the right of root.
      else
      {
        root -> right = element;
        element->parent = parent(root, element);

      }
    }
    // element should be inserted to the left.
    else {
      // There is a left subtree to insert the node.
      if (root -> left != NULL)
        {
          root -> left = insert(root -> left, element);
        }
      // Place the node directly to the left of root.
      else
        root -> left = element;
        element->parent = parent(root, element);
    }
    // Return the root pointer of the updated tree.
    return root;
  }
}


int find(Node * currentPtr, int val) {
  // Check if there are nodes in the tree.
  if (currentPtr != NULL) {
    // Found the value at the root.
    if (currentPtr -> data == val)
      return 1;
    // Search to the left.
    if (val < currentPtr -> data)
      return find(currentPtr -> left, val);
    // Or search to the right.
    else
      return find(currentPtr -> right, val);
  } else
    return 0;
}


int add(Node * currentPtr) {
  if (currentPtr != NULL)
    return currentPtr -> data + add(currentPtr -> left) +
      add(currentPtr -> right);
  else
    return 0;
}


// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
Node * parent(Node * root, Node * node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root -> left == node || root -> right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (node -> data < root -> data)
    return parent(root -> left, node);
  // Look for node's parent in the right side of the tree.
  else if (node -> data > root -> data)
    return parent(root -> right, node);
  return NULL; // For any other cases.
}


// Returns a pointer to the node storing the minimum value in the tree
Node * minVal(Node * root) {
  // Root stores the minimal value.
  if (root -> left == NULL)
    return root;
  // The left subtree of the root stores the minimal value.
  else
    return minVal(root -> left);
}


// Returns a pointer to the node storing the maximum value in the tree
Node * maxVal(Node * root) {
  // Root stores the maximal value.
  if (root -> right == NULL)
    return root;
  // The right subtree of the root stores the maximal value.
  else
    return maxVal(root -> right);
}


// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(Node * node) {
  return (node -> left == NULL && node -> right == NULL);
}


// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(Node * node) {
  return (node -> left != NULL && node -> right == NULL);
}


// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(Node * node) {
  return (node -> left == NULL && node -> right != NULL);
}


// Returns a pointer to a node that stores value in it in the subtree
Node * findNode(Node * currentPtr, int value) {
  if(currentPtr == NULL){
    return NULL;
  }
    // Found the value at the root.
  if (currentPtr -> data == value) {
    return currentPtr;
  }
  if (value < currentPtr -> data) {
    return findNode(currentPtr -> left, value);
  }
  else {
    return findNode(currentPtr -> right, value);
  }
}


// Will delete the node storing value in the tree rooted at root. The
// value must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
Node * deleteNode(Node * root, int value) {
  Node * delnode, * newDelNode, * saveNode;
  Node * par;
  int saveVal;
  delnode = findNode(root, value); // Get a pointer to the node to delete.
  par = parent(root, delnode); // Get the parent of this node.
  // Take care of the case where the node to delete is a leaf node.
  if (isLeaf(delnode)) { // case 1
    // Deleting the only node in the tree.
    if (par == NULL) {
      delete root; // free the memory for the node.
      return NULL;
    }
    // Deletes the node if it's a left child.
    if (value < par -> data) {
      delete par -> left; // Free the memory for the node.
    }
    // Deletes the node if it's a right child.
    else {
      delete par -> right; // Free the memory for the node.
      par -> right = NULL;
    }
    return root; // Return the root of the new tree.
  }
  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChild(delnode)) {
    // Deleting the root node of the tree.
    if (par == NULL) {
      saveNode = delnode -> left;
      delete delnode; // Free the node to delete.
      return saveNode; // Return the new root node of the resulting tree.
    }
    // Deletes the node if it's a left child.
    if (value < par -> data) {
      saveNode = par -> left; // Save the node to delete.
      par -> left = par -> left -> left; // Readjust the parent pointer.
      delete saveNode; // Free the memory for the deleted node.
    }
    // Deletes the node if it's a right child.
    else {
      saveNode = par -> right; // Save the node to delete.
      par -> right = par -> right -> left; // Readjust the parent pointer.
      delete saveNode; // Free the memory for the deleted node.
    }
    return root; // Return the root of the tree after the deletion.
  }
  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChild(delnode)) {
    // Node to delete is the root node.
    if (par == NULL) {
      saveNode = delnode -> right;
      delete delnode;
      return saveNode;
    }
    // Delete's the node if it is a left child.
    if (value < par -> data) {
      saveNode = par -> left;
      par -> left = par -> left -> right;
      delete saveNode;
    }
    // Delete's the node if it is a right child.
    else {
      saveNode = par -> right;
      par -> right = par -> right -> right;
      delete saveNode;
    }
    return root;
  }
  //when delnode has two children
  // Find the new physical node to delete.
  newDelNode = minVal(delnode -> right);
  saveVal = newDelNode -> data;
  deleteNode(root, saveVal); // Now, delete the proper value.
  // Restore the data to the original node to be deleted.
  delnode -> data = saveVal;
  return root;
}


// Prints out the menu of choices for the user and returns their choice.
int menu() {
  int ans;
  cout << "Here are your choices.\n";
  cout << "1. Insert an item into your tree.\n";
  cout << "2. Delete an item from your tree.\n";
  cout << "3. Search for an item in your tree.\n";
  cout << "4. Print the sum of the nodes. \n";
  cout << "5. Print the next element of the node with key x.\n";
  cout << "6. Print the elements between x, and y\n";
  cout << "7. Print the height of the tree with root x\n";
  cout << "8. Print the sum of the list of elements between x, and y\n";
  cout << "9. Print out an in-order traversal\n";
  cout << "0. Exit.\n";
  cin >> ans;
  return ans;
}

Node * next(Node * root, Node * N)
{

  if(N->right != NULL)
  {

    return leftDescendant(N->right);

  }
  else
  {

    return rightAncestor(root, N);

  }

  

}

Node * leftDescendant(Node * N)
{

  if(N->left == NULL)
  {

    return N;

  }
  else
  {
    return leftDescendant(N->left);
  }

}

Node * rightAncestor(Node * root, Node * N)
{
  if(parent(root,N) == NULL){
    return NULL;
  }
  if(N->data < parent(root,N)->data)
  {
    return parent(root,N);
  }
  else
  {
    return rightAncestor(root, parent(root, N));
  }

}

vector<int> rangeSearch(int low, int high, Node * root)
{

  vector<int> myVect;
  Node * temp = findNode(root, low);

  while(temp->data <= high)
  {

    if(temp->data >= low)
    myVect.push_back(temp->data);

    temp = next(temp);    

  }

  return myVect;



}

int computeHeight(Node * targetNode)
{

  return targetNode->height;

}

bool isUnbalanced(Node * root, Node * workingNode) {

  int valHold = 0;

  if(isLeaf(workingNode))
  {

    valHold = workingNode->height;

  }
  else if(workingNode->right == NULL && workingNode->left != NULL)
    valHold = findLowestLeafHeight(root, workingNode) - 0; 
  else if(workingNode->left == NULL && workingNode->right != NULL)
    valHold = findLowestLeafHeight(root,workingNode) - 0; 
  else
  {
    valHold = balanceFactor(root, workingNode);
  }

  
  if(valHold < -1 || valHold > 1)
  return false;
  else
  return true;

}

//* The inserted Node is the deepest leaf
//! This might go wrong
int findLowestLeafHeight(Node * root, Node * workingNode)
{
 
  if(!isLeaf(workingNode))
  {
    if(workingNode->left == NULL)
    {
      return workingNode->right->height;

    }

    return findLowestLeafHeight(root, workingNode->left);

  }
  else
  {
    if(isLeaf(workingNode))
    {
      if(parent(root, workingNode)->right == NULL)
      {
        return workingNode->height;
      }
      return findLowestLeafHeight(root, parent(root, workingNode)->right); 
    }
    else
    return workingNode->height;
  }

}

//! This might also go wrong
void rotateRight(Node * workingNode)
{

  /*
    parentNode = P
    leftChildNode = Y
    rightLeftChildNode = B 
  
  */ 
    Node * parentNode = workingNode->parent; 
    Node * leftChildNode = workingNode->left;
    Node * rLChildNode = leftChildNode->right;



    leftChildNode->parent = parentNode;    
    parentNode->left = leftChildNode;
    workingNode->parent = leftChildNode;
    leftChildNode->right = workingNode;
    rLChildNode->parent = workingNode;
    workingNode->left = rLChildNode;


}

//! Same as rotate right
void rotateLeft(Node * workingNode)
{

  Node * parentNode = workingNode->parent;
  Node * rightChild = workingNode->right;
  Node * lRChild = rightChild->left;

  rightChild->parent = parentNode;
  parentNode->right = rightChild;
  workingNode->parent = rightChild;
  rightChild->left = workingNode;
  lRChild->parent = workingNode;
  workingNode->right = lRChild;

}

int balanceFactor(Node * root, Node * targetNode)
{

  return findLowestLeafHeight(root, targetNode) - findLowestLeafHeight(root, targetNode->right);

}

void adjustHeight(Node * targetNode)
{

  targetNode->height = 1 + max(targetNode->left->height, targetNode->right->height);

}

void rebalance(Node * root, Node * targetNode)
{

  Node * parentNode = targetNode->parent;  

  if(isUnbalanced(root, targetNode))
  {
    if(parentNode != NULL)
    rebalance(root, parentNode);

  }

  if(isUnbalanced(root, targetNode))
  {
    return;

  }

  Node * wNode = new Node();
  Node * xNode = new Node();
  Node * yNode = new Node();
  Node * zNode = new Node();

  if(targetNode->parent->parent->parent == NULL)
  {
 

    wNode = targetNode;
    xNode = targetNode;
    yNode = targetNode->parent;
    zNode = targetNode->parent->parent;

    if(zNode->left == yNode && yNode->left == xNode)
    {

      yNode->parent = zNode->parent;
      yNode->right = zNode;
      zNode->parent = yNode;
      zNode->left = NULL;
      root = yNode;


    }
    else if(zNode->right == yNode && yNode->right == xNode)
    {

      yNode->parent = zNode->parent;
      yNode->left = zNode;
      zNode->parent = yNode;
      zNode->right = NULL;
      root = yNode;

    }

    yNode->height--;
    zNode->height++;
    xNode->height--;

  }
  else
  {

    wNode = targetNode;
    xNode = targetNode->parent;
    yNode = targetNode->parent->parent;
    zNode = targetNode->parent->parent->parent;

    if(zNode->left == yNode && yNode->left == xNode)
    {

      yNode->parent = zNode->parent;
      zNode->left = yNode->right;
      yNode->right = zNode;
      zNode->parent = yNode;

      if(zNode == root)
      {
        yNode = root;

      }
      

      yNode->height--;
      xNode->height++;
      zNode->height++;


    }
    else if(zNode->left == yNode && yNode->right == xNode)
    {

      rotateLeft(zNode);

      //Rotate right
      yNode->parent = zNode->parent;
      yNode->right = zNode;
      zNode->parent = yNode;

      if(zNode == root)
      {

        xNode = root;

      }

      yNode->height++;
      zNode->height++;
      xNode->height--;

    }
    else if(zNode->right == yNode && yNode->right == xNode)
    {

      yNode->parent = zNode->parent;
      yNode->left = zNode;
      zNode->parent = yNode;

      if(zNode == root)
      {

        yNode = root;

      }

      yNode->height--;
      xNode->height++;
      zNode->height++;

    }
    else if(zNode->right == yNode && yNode->left == xNode)
    {

      rotateRight(zNode); 

      //Rotate left
      yNode->parent = zNode->parent;
      yNode->left = zNode;
      zNode->parent = yNode;

      if(zNode == root)
      {
        xNode = root;
      }


      yNode->height++;
      zNode->height++;
      xNode->height--;

    }



  }

  




  /*
  
    Have to redo whole function
    Look at balance rotations powerpoint'
    Look at X, Y, Z, and W
    W is going to be used to look for other cases

  */
  


  
  

} 



void rebalanceRight(Node * targetNode)
{

  Node * temp = targetNode->left;
  int leftHeight, rightHeight;

  if(temp->right == NULL)
  {

    rightHeight = 0;
    leftHeight = temp->left->height;

  }
  else if(temp->left == NULL)
  {

    leftHeight = 0;
    rightHeight = temp->right->height;

  }
  else
  {
    leftHeight = temp->left->height;
    rightHeight = temp->right->height;
  }

  if(rightHeight > leftHeight)
  {
    rotateLeft(temp);
    adjustHeight(temp);
  }
  
  rotateRight(temp);
  adjustHeight(temp);

}

void rebalanceLeft(Node * targetNode)
{

  Node * temp = targetNode->right;  

  if(temp->left->height > temp->right->height)
  {
    rotateRight(temp);
    adjustHeight(temp);
  }

  rotateLeft(temp);
  adjustHeight(temp);


}

void AVLInsert(Node * root, Node * workingNode)
{
  /*
  insert(root, workingNode);
  Node * temp = findNode(workingNode, workingNode->data);
  rebalance(root, temp);
  */




}

void AVLDelete(Node * root, Node * workingNode)
{

  Node * temp = workingNode->parent; 
  rebalance(root, temp);


}

int main() 
{
    Node * myRoot = NULL, * tempNode;
    int done = 0, ans = 1, val, val2, q6data;
    int low, high, sum;
    ans = menu();
    while (ans != 0) {
      switch(ans) {
        case 1:
          // Get value to insert.
          cout << "What value would you like to insert?\n";
          cin >> val;
          tempNode = new Node(val); // Create the node.
          tempNode->height = 0;
          // Insert the value.
          if(myRoot != NULL){
            AVLInsert(myRoot, tempNode);
          }
          else {
            myRoot = insert(myRoot, tempNode);
          }
          cout << "Inserted " << val << endl;
          break;
        case 2:
          cout << "What value would you like to delete?\n";
          cin >> val;
          if (!find(myRoot, val)) {
            cout << "Sorry that value isn't in the tree to delete.\n";
          }
          else {
            //myRoot = deleteNode(myRoot, val);
            AVLDelete(myRoot, deleteNode(myRoot,val));
          }
          break;
        case 3:
          cout << "What value would you like to search for?\n";
          cin >> val;
          if (find(myRoot, val)) {
            cout << " Found" << val << "in the tree.\n";
          }
          else {
            cout << " Did not find %d in the tree.\n";
          }
          break;
        case 4:
          cout << "The sum of the nodes in your tree is" << add(myRoot) << "\n";
          break;
        case 5:          
          cout << "What is the target node?\n";
          cin >> val;

          if(!find(myRoot, val)) {
            cout << "Node does not exist";
          }
          else {
            Node * temp = next(myRoot, findNode(myRoot, val));
            cout << "The value of the next node is " << temp->data;
          }
          break;
        case 6:
          int low, high;
          cout << "What are the two values?" << std::endl;
          cin >> low >> high;

          if(find(myRoot,low) & find(myRoot, high)) {
            vector<int> vectDisp = rangeSearch(low, high, myRoot);
            for(int x : vectDisp) {
              cout << x << " ";
            }
          }
          else {
            cout << "One or two values does not exist" << std::endl;
          }
          break;
        case 7:
          cout << "What is the target node?\n";
          cin >> val;

          if(!find(myRoot, val)) {
            cout << "The node does not exist" << std::endl;
          }
          else {
            cout << "The height of the target node is " << computeHeight(findNode(myRoot, val)) << std::endl;
          }
          break;
        case 8:
          cout << "What are the two values?" << std::endl;
          cin >> low >> high;

          if(find(myRoot,low) & find(myRoot, high)) {
            vector<int> vectDisp = rangeSearch(low, high, myRoot);
            for(int x : vectDisp) {
              sum += x;
            }
            cout << "Sum between " << low << " and " << high << " is " << sum << endl;
          }
          else {
            cout << "One or two values does not exist" << std::endl;
          }
          break;
        case 9:
          // Print the resulting tree.
          cout << "Here is an inorder traversal of your tree: ";
          inorder(myRoot);
          cout << "\n";
          break;
        case 0:
          std::cout << "exit" << std::endl;
          break;
        default:
          std::cout << "Invalid Input" << std::endl;
          break;
      };

      // See if they want to insert more nodes.
      ans = menu();
    }

    return 0;
}
