#include <iostream>
#include <string>
#include "mapBST.hpp"

using std::cout;
using std::endl;

template <typename Iterator>
void printDebugInfo(const std::pair<Iterator, bool>& insertInfo){
  cout << (insertInfo.second ? "Added " + *insertInfo.first : "Couldn't add an element.") << endl;
}

template <typename Iterator>
void printDebugInfo(const Iterator& findInfo){
  cout << (findInfo ? "Found " + *findInfo : "Couldn't find an element.") << endl;
}

template <typename K, typename V>
void printMapSizeAndElements(MapBST<K, V> &map){
  cout << "Size: " << map.size() << endl;
  for(auto &it : map) cout << it << ", ";
  cout << endl;
}

template <typename K, typename V>
void printMapSizeAndElements(const MapBST<K, V> &map){
  cout << "Size: " << map.size() << endl;
  for(const auto &it : map) cout << it << ", ";
  cout << endl;
}

int main(){
  MapBST<int, std::string> map;

  printDebugInfo(map.insert( { 8, "eight" } ));
  printDebugInfo(map.insert( { 4, "four" } ));
  printDebugInfo(map.insert( { 10, "ten" } ));
  printDebugInfo(map.insert( { 10, "ten" } ));
  printDebugInfo(map.insert( { 2, "two" } ));
  printDebugInfo(map.insert( { 5, "five" } ));
  printDebugInfo(map.insert( { 9, "nine" } ));
  printDebugInfo(map.insert( { 12, "twelve" } ));
  printDebugInfo(map.insert( { 12, "twelve" } ));
  printDebugInfo(map.insert( { 1, "one" } ));
  printDebugInfo(map.insert( { 14, "fourteen" } ));
  printDebugInfo(map.insert( { 7, "seven" } ));

  {
    auto map2 = map;
    printMapSizeAndElements(map2);
  }

  auto it = map.find(10);
  *it = "10 (corrected)";
  printDebugInfo(map.find(5));
  map.remove(4);
  printDebugInfo(map.find(5));
  map.remove(12);
  map.remove(14);
  printDebugInfo(map.insert( { 0, "zero" } ));
  printDebugInfo(map.insert( { 16, "sixteen" } ));

  {
    MapBST<int, std::string> map3;
    map3 = map;
    printMapSizeAndElements(map3);
  }

  map.remove(8);
  printMapSizeAndElements(map);
  const auto map4 = map;
  printMapSizeAndElements(map4);
  auto it2 = map4.find(10);

  map[2] = "two (corrected)";
  map[20] = "twenty";
  printMapSizeAndElements(map);

  return 0;
}
