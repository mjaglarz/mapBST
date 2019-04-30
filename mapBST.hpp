#ifndef MAPBST_H
#define MAPBST_H

#include <iostream>
#include "binarySearchTree.hpp"

template <typename K, typename V>
class MapBST{
  class MapElement{
  public:
    std::pair<K, V> key_value_;

    bool operator==(const MapElement& element) const;
    bool operator<(const MapElement& element) const;
    bool operator>(const MapElement& element) const;
    friend std::ostream& operator<<(std::ostream& output, const MapElement& mapElement){
      return output << "\nKey: " << mapElement.key_value_.first << " Value: " << mapElement.key_value_.second;
    }

    MapElement() = default;
    MapElement(const std::pair<K, V>& key_value): key_value_(key_value){}
    MapElement(const K& key, const V& value){ key_value_ = std::make_pair(key, value); }
  };

  class Iterator{
    friend class MapBST<K, V>;
  private:
    const MapBST<K, V>* map_;
    typename BinarySearchTree<MapElement>::Node* node_;

    Iterator(const MapBST<K, V>* map, typename BinarySearchTree<MapElement>::Node* node):map_(map), node_(node){}
  public:
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;
    Iterator& operator++();
    Iterator operator++(int);
    V& operator*() const;
    V* operator->() const;
    operator bool() const{ return this->node_ != nullptr; }

    Iterator& operator=(const Iterator&) = default;
    Iterator& operator=(Iterator&&) = default;

    Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) = default;
    ~Iterator() = default;
  };

  class ConstIterator{
    friend class MapBST<K, V>;
  private:
    const MapBST<K, V>* map_;
    typename BinarySearchTree<MapElement>::Node* node_;

    ConstIterator(const MapBST<K, V>* map, typename BinarySearchTree<MapElement>::Node* node):map_(map), node_(node){}
  public:
    bool operator==(const ConstIterator& it) const;
    bool operator!=(const ConstIterator& it) const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    const V& operator*() const;
    const V* operator->() const;
    operator bool() const{ return this->node_ != nullptr; }

    ConstIterator& operator=(const ConstIterator&) = default;
    ConstIterator& operator=(ConstIterator&&) = default;

    ConstIterator() = default;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator(ConstIterator&&) = default;
    ~ConstIterator() = default;
  };

private:
  BinarySearchTree<MapElement> bst_;

public:
  std::pair<Iterator, bool> insert(const std::pair<K, V>& key_value);
  std::pair<Iterator, bool> insert(const K& key, const V& value);
  bool remove(const K& key);
  Iterator find(const K& key);
  ConstIterator find(const K& key) const;
  std::size_t size() const;
  bool empty() const;

  void swapMap(MapBST<K, V>& first, MapBST<K, V>& second);

  Iterator begin();
  Iterator end();
  ConstIterator begin() const;
  ConstIterator end() const;

  V& operator[](const K& key);
  const MapBST<K, V>& operator=(const MapBST<K, V>& map);
  const MapBST<K, V>& operator=(MapBST<K, V>&& map);
  friend std::ostream& operator<<(std::ostream& output, const MapBST<K, V>& map){
    return output << map.bst_;
  }

  MapBST():bst_(){}
  MapBST(const MapBST<K, V>& map) = default;
  MapBST(MapBST<K, V>&& map) noexcept = default;
  ~MapBST() = default;
};

template <typename K, typename V>
bool MapBST<K, V>::MapElement::operator==(const MapElement& element) const{
  return key_value_.first == element.key_value_.first;
}

template <typename K, typename V>
bool MapBST<K, V>::MapElement::operator<(const MapElement& element) const{
  return key_value_.first < element.key_value_.first;
}

template <typename K, typename V>
bool MapBST<K, V>::MapElement::operator>(const MapElement& element) const{
  return key_value_.first > element.key_value_.first;
}


template <typename K, typename V>
bool MapBST<K, V>::Iterator::operator==(const Iterator& it) const{
  return (map_->bst_.rootPointer() == it.map_->bst_.rootPointer() && node_ == it.node_);
}

template <typename K, typename V>
bool MapBST<K, V>::Iterator::operator!=(const Iterator& it) const{
  return !(*this == it);
}

template <typename K, typename V>
typename MapBST<K, V>::Iterator& MapBST<K, V>::Iterator::operator++(){
  if(node_ == nullptr){
    node_ = map_->bst_.rootPointer();
    if(node_ == nullptr){
       throw "Map is empty";
    }
    while(node_->left != nullptr){
      node_ = node_->left;
    }
    return *this;
  }

  if(node_->right != nullptr){
    node_ = node_->right;
    while(node_->left != nullptr){
      node_ = node_->left;
    }
  }else{
    typename BinarySearchTree<MapElement>::Node* temp;
    temp = map_->bst_.findParent(node_->key);
    while(temp != nullptr && node_ == temp->right){
      node_ = temp;
      temp = map_->bst_.findParent(temp->key);
    }
    node_ = temp;
  }

  return *this;
}

template <typename K, typename V>
typename MapBST<K, V>::Iterator MapBST<K, V>::Iterator::operator++(int){
  Iterator result(*this);
  ++(*this);
  return result;
}

template <typename K, typename V>
V& MapBST<K, V>::Iterator::operator*() const{
  return node_->key.key_value_.second;
}

template <typename K, typename V>
V* MapBST<K, V>::Iterator::operator->() const{
  return &node_->key.key_value_.second;
}


template <typename K, typename V>
bool MapBST<K, V>::ConstIterator::operator==(const ConstIterator& it) const{
  return (map_->bst_.rootPointer() == it.map_->bst_.rootPointer() && node_ == it.node_);
}

template <typename K, typename V>
bool MapBST<K, V>::ConstIterator::operator!=(const ConstIterator& it) const{
  return !(*this == it);
}

template <typename K, typename V>
typename MapBST<K, V>::ConstIterator& MapBST<K, V>::ConstIterator::operator++(){
  if(node_ == nullptr){
    node_ = map_->bst_.rootPointer();
    if(node_ == nullptr){
       throw "Map is empty";
    }
    while(node_->left != nullptr){
      node_ = node_->left;
    }
    return *this;
  }

  if(node_->right != nullptr){
    node_ = node_->right;
    while(node_->left != nullptr){
      node_ = node_->left;
    }
  }else{
    typename BinarySearchTree<MapElement>::Node* temp;
    temp = map_->bst_.findParent(node_->key);
    while(temp != nullptr && node_ == temp->right){
      node_ = temp;
      temp = map_->bst_.findParent(temp->key);
    }
    node_ = temp;
  }

  return *this;
}

template <typename K, typename V>
typename MapBST<K, V>::ConstIterator MapBST<K, V>::ConstIterator::operator++(int){
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template <typename K, typename V>
const V& MapBST<K, V>::ConstIterator::operator*() const{
  return node_->key.key_value_.second;
}

template <typename K, typename V>
const V* MapBST<K, V>::ConstIterator::operator->() const{
  return &node_->key.key_value_.second;
}


template <typename K, typename V>
std::pair<typename MapBST<K, V>::Iterator, bool> MapBST<K, V>::insert(const std::pair<K, V>& key_value){
  MapElement mapElement = MapElement(key_value);
  if(bst_.find(mapElement) != nullptr){
    return std::make_pair(Iterator(this, nullptr), false);
  }else{
    bst_.insert(mapElement);
    return std::make_pair(Iterator(this, bst_.search(mapElement)), true);
  }
}

template <typename K, typename V>
std::pair<typename MapBST<K, V>::Iterator, bool> MapBST<K, V>::insert(const K& key, const V& value){
  MapElement mapElement = MapElement(key, value);
  if(bst_.find(mapElement) != nullptr){
    return std::make_pair(Iterator(this, nullptr), false);
  }else{
    bst_.insert(mapElement);
    return std::make_pair(Iterator(this, bst_.search(mapElement)), true);
  }
}

template <typename K, typename V>
bool MapBST<K, V>::remove(const K& key){
  MapElement mapElement = MapElement(key, V());
  return bst_.remove(mapElement);
}

template <typename K, typename V>
typename MapBST<K, V>::Iterator MapBST<K, V>::find(const K& key){
  MapElement mapElement = MapElement(key, V());
  return Iterator(this, bst_.search(mapElement));
}

template <typename K, typename V>
typename MapBST<K, V>::ConstIterator MapBST<K, V>::find(const K& key) const{
  MapElement mapElement = MapElement(key, V());
  return ConstIterator(this, bst_.search(mapElement));
}

template <typename K, typename V>
std::size_t MapBST<K, V>::size() const{
  return bst_.size();
}

template <typename K, typename V>
bool MapBST<K, V>::empty() const{
  return bst_.empty();
}

template <typename K, typename V>
void MapBST<K, V>::swapMap(MapBST<K, V>& first, MapBST<K, V>& second){
  std::swap(first.bst_, second.bst_);
  second.bst_ = nullptr;
}

template <typename K, typename V>
typename MapBST<K, V>::Iterator MapBST<K, V>::begin(){
  typename BinarySearchTree<MapElement>::Node* root = bst_.rootPointer();
  if(root == nullptr){
    return Iterator(this, nullptr);
  }

  while(true){
    if(root->left != nullptr){
      root = root->left;
    }else if(root->right != nullptr){
      root = root->right;
    }else{
      return Iterator(this, root);
    }
  }
}

template <typename K, typename V>
typename MapBST<K, V>::Iterator MapBST<K, V>::end(){
  return Iterator(this, nullptr);
}

template <typename K, typename V>
typename MapBST<K, V>::ConstIterator MapBST<K, V>::begin() const{
  typename BinarySearchTree<MapElement>::Node* root = bst_.rootPointer();
  if(root == nullptr){
    return ConstIterator(this, nullptr);
  }

  while(true){
    if(root->left != nullptr){
      root = root->left;
    }else if(root->right != nullptr){
      root = root->right;
    }else{
      return ConstIterator(this, root);
    }
  }
}

template <typename K, typename V>
typename MapBST<K, V>::ConstIterator MapBST<K, V>::end() const{
  return ConstIterator(this, nullptr);
}

template <typename K, typename V>
V& MapBST<K, V>::operator[](const K& key){
  MapElement mapElement = MapElement(key, V());
  typename BinarySearchTree<MapElement>::Node* temp = bst_.search(mapElement);
  if(temp != nullptr){
    return temp->key.key_value_.second;
  }else{
    bst_.insert(mapElement);
    return bst_.search(mapElement)->key.key_value_.second;
  }
}

template <typename K, typename V>
const MapBST<K, V>& MapBST<K, V>::operator=(const MapBST<K, V>& map){
  if(this != &map){
    bst_.freeMemory(bst_.rootPointer());
    bst_.copyTree(map.bst_.rootPointer());
  }

  return *this;
}

template <typename K, typename V>
const MapBST<K, V>& MapBST<K, V>::operator=(MapBST<K, V>&& map){
  swapMap(*this, map);
  return *this;
}

#endif
