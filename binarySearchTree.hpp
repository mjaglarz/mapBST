#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <typename T = int>
class BinarySearchTree{
public:
  struct Node{
    T key;
    Node* left;
    Node* right;

    Node(T value):key(value), left(nullptr), right(nullptr){}
  };

  T* insert(const T& x){ return insert(root_, x); }
  bool remove(const T& x);
  Node* search(const T& x) const { return search(root_, x); }
  T* find(const T& x){ return find(root_, x); }
  const T* findRec(const T& x) const { return findRec(root_, x); }
  Node* findParent(const T& x) const { return findParent(root_, x); }
  std::size_t size() const;
  T minimum(){ return minimum(root_); }
  T maximum(){ return maximum(root_); }
  int depth(){ return depth(root_); }
  void print(std::ostream& output, Node* root) const;
  void printInorder(){ printInorder(root_); }
  void printPreorder(){ printPreorder(root_); }
  void printPostorder(){ printPostorder(root_); }
  bool isEmpty() const;

  Node* rootPointer() const;
  void copyTree(Node* root);
  void freeMemory(Node* root);
  void swapTree(BinarySearchTree<T>& first, BinarySearchTree<T>& second);

  const BinarySearchTree<T>& operator=(const BinarySearchTree<T>& tree);
  const BinarySearchTree<T>& operator=(BinarySearchTree<T>&& tree);
  friend std::ostream& operator<<(std::ostream& output, const BinarySearchTree<T>& tree){
    tree.print(output, tree.root_); return output << "\n";
  }

  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree<T>& tree);
  BinarySearchTree(BinarySearchTree<T>&& tree) noexcept;
  ~BinarySearchTree();

private:
  Node* root_;
  int size_;

  T* insert(Node* root, const T& x);
  Node* remove(Node* root, const T& x);
  Node* search(Node* root, const T& x) const;
  T* find(Node* root, const T& x) const;
  const T* findRec(Node* root, const T& x) const;
  Node* findParent(Node* root, const T& x) const;
  T minimum(Node* root) const;
  T maximum(Node* root) const;
  int depth(Node* root) const;
  void printInorder(Node* root) const;
  void printPreorder(Node* root) const;
  void printPostorder(Node* root) const;
};

template <typename T>
T* BinarySearchTree<T>::insert(Node* root, const T& x){
  if(isEmpty()){
    root_ = new Node(x);
    size_++;
    return &root_->key;
  }

  if(x > root->key){
    if(root->right != nullptr){
      insert(root->right, x);
    }else{
      root->right = new Node(x);
      size_++;
      return &root->right->key;
    }
  }else{
    if(root->left != nullptr){
      insert(root->left, x);
    }else{
      root->left = new Node(x);
      size_++;
      return &root->left->key;
    }
  }

  return nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::remove(Node* root, const T& x){
  if(root == nullptr){ return nullptr; }

  if(root->key > x){
    root->left = remove(root->left, x);
  }else if(root->key < x){
    root->right = remove(root->right, x);
  }else{
    if(root->left == nullptr){
      Node* temp = root->right;

      delete root;
      size_--;
      return temp;
    }else if(root->right == nullptr){
      Node* temp = root->left;

      delete root;
      size_--;
      return temp;
    }

    Node* temp = root->right;
    while(temp->left != nullptr){
      temp = temp->left;
    }

    root->key = temp->key;
    root->right = remove(root->right, temp->key);
  }

  return root;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& x){
  if(remove(root_, x) == nullptr){
    return false;
  }else return true;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::search(Node* root, const T& x) const{
  while(root != nullptr){
    if(root->key == x){
      return root;
    }else if(x < root->key){
      root = root->left;
    }else{
      root = root->right;
    }
  }

  return root;
}

template <typename T>
T* BinarySearchTree<T>::find(Node* root, const T& x) const{
  while(root != nullptr){
    if(root->key == x){
      return &root->key;
    }else if(x < root->key){
      root = root->left;
    }else{
      root = root->right;
    }
  }

  return nullptr;
}

template <typename T>
const T* BinarySearchTree<T>::findRec(Node* root, const T& x) const{
  if(root == nullptr){
    return nullptr;
  }else if(root->key == x){
    return &root->key;
  }else if(x < root->key){
    return findRec(root->left, x);
  }else{
    return findRec(root->right, x);
  }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findParent(Node* root, const T& x) const{
  if(root == nullptr){
    return nullptr;
  }else if((root->right != nullptr && root->right->key == x) || (root->left != nullptr && root->left->key == x)){
    return root;
  }else if(x < root->key){
    return findParent(root->left, x);
  }else{
    return findParent(root->right, x);
  }
}

template <typename T>
std::size_t BinarySearchTree<T>::size() const{
  return size_;
}

template <typename T>
T BinarySearchTree<T>::minimum(Node* root) const{
  if(isEmpty()){ throw "BST is empty"; }

  while(root->left != nullptr){
    root = root->left;
  }

  return root->key;
}

template <typename T>
T BinarySearchTree<T>::maximum(Node* root) const{
  if(isEmpty()){ throw "BST is empty"; }

  while(root->right != nullptr){
    root = root->right;
  }

  return root->key;
}

template <typename T>
int BinarySearchTree<T>::depth(Node* root) const{
  if(root == nullptr){
    return 0;
  }else{
    int leftSubTree = depth(root->left);
    int rightSubTree = depth(root->right);

    if(leftSubTree > rightSubTree){
      return leftSubTree + 1;
    }else{
      return rightSubTree + 1;
    }
  }
}

template <typename T>
void BinarySearchTree<T>::print(std::ostream& output, Node* root) const{
  if(root == nullptr){ return; }

  print(output, root->left);
  std::cout << root->key << " ";
  print(output, root->right);
}

template <typename T>
void BinarySearchTree<T>::printInorder(Node* root) const{
  if(root == nullptr){ return; }

  printInorder(root->left);
  std::cout << root->key << " ";
  printInorder(root->right);
}

template <typename T>
void BinarySearchTree<T>::printPreorder(Node* root) const{
  if(root == nullptr){ return; }

  std::cout << root->key << " ";
  printPreorder(root->left);
  printPreorder(root->right);
}

template <typename T>
void BinarySearchTree<T>::printPostorder(Node* root) const{
  if(root == nullptr){ return; }

  printPostorder(root->left);
  printPostorder(root->right);
  std::cout << root->key << " ";
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() const{
  return size_ == 0;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::rootPointer() const{
  return root_;
}

template <typename T>
void BinarySearchTree<T>::copyTree(Node* root){
  if(root != nullptr){
    insert(root->key);
    copyTree(root->left);
    copyTree(root->right);
  }
}

template <typename T>
void BinarySearchTree<T>::freeMemory(Node* root){
  if(root == nullptr){
    return;
  }

  freeMemory(root->left);
  freeMemory(root->right);
  delete root;
}

template <typename T>
void BinarySearchTree<T>::swapTree(BinarySearchTree<T>& first, BinarySearchTree<T>& second){
  std::swap(first.root_, second.root_);
  second.root_ = nullptr;
}

template <typename T>
const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& tree){
  if(this != &tree){
    freeMemory(root_);
    root_ = nullptr;
    copyTree(tree.root_);
  }
  
  return *this;
}

template <typename T>
const BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& tree){
  swapTree(*this, tree);
  return *this;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree():root_(nullptr), size_(0){}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree):root_(nullptr), size_(0){
  copyTree(tree.root_);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& tree) noexcept:root_(nullptr), size_(0){
  swapTree(*this, tree);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){ freeMemory(root_); }

#endif
