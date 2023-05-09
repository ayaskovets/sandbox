#include "binarysearch.hpp"
#include "quicksort.hpp"
#include "heapsort.hpp"
#include "mergesort.hpp"
#include "insertionsort.hpp"
#include "binarysearchtree.hpp"
#include "calculator.hpp"
#include "avltree.hpp"
#include "redblacktree.hpp"

#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <functional>
#include <map>
#include <chrono>

template <class Sort, class Container, class Compare>
void sort(Sort sort_func, Container cont, Compare comp, bool verbose) {
  if (verbose) {
    std::cout << "SB::array:  ";
    for (auto& elem : cont) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }

  std::chrono::time_point start = std::chrono::system_clock::now();
  sort_func(cont.begin(), cont.end(), comp);
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

  if (verbose) {
    std::cout << "SB::sorted: ";
    for (auto& elem : cont) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "SB::container size: " << std::setw(15) << cont.size() << std::setw(10) << duration.count() << " ms\n";
};

template<class Sort, class Container, class FillCallback, class Compare>
void test(Sort sort_func, std::vector<size_t> container_size_table, FillCallback fill, Compare comp, bool verbose = true) {
  for (const size_t size : container_size_table) {
    Container cont(size);
    fill(cont);
    sort<Sort, Container, Compare>(sort_func, cont, comp, verbose);
  }

  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  srand(static_cast<unsigned int>(time(0)));

  std::vector<size_t> container_size_table = { 20 }; bool verbose = true; // work tests
  //std::vector<size_t> container_size_table = { 11, 101, 1001, 10001, 100001, 1000001, 10000001 }; bool verbose = false; // time tests

  typedef int elem_type;
  typedef std::vector<elem_type> container_type;
  typedef std::function<bool(const elem_type&, const elem_type&)> comp_type;
  typedef std::function<void(container_type&)> fill_type;

  auto comp = [](const elem_type& a, const elem_type& b) {
    return a < b;
  };

  auto fill = [](container_type& sortable) {
    for (auto& elem : sortable) {
      elem = rand() % sortable.size();
    }
  };

  /*std::cout << "SB::Quick:\n";
  test<std::function<void(container_type::iterator, container_type::iterator, comp_type)>, container_type, fill_type, comp_type>(
    sandbox::sort::quicksort<container_type::iterator, comp_type>, container_size_table, fill, comp, verbose);

  std::cout << "SB::Heap:\n";
  test<std::function<void(container_type::iterator, container_type::iterator, comp_type)>, container_type, fill_type, comp_type>(
    sandbox::sort::heapsort<container_type::iterator, comp_type>, container_size_table, fill, comp, verbose);

  std::cout << "SB::Merge:\n";
  test<std::function<void(container_type::iterator, container_type::iterator, comp_type)>, container_type, fill_type, comp_type>(
      sandbox::sort::mergesort<container_type::iterator, comp_type>, container_size_table, fill, comp, verbose);

  std::cout << "SB::Shell:\n";
  test<std::function<void(container_type::iterator, container_type::iterator, comp_type)>, container_type, fill_type, comp_type>(
      sandbox::sort::shellsort<container_type::iterator, comp_type>, container_size_table, fill, comp, verbose);

  std::cout << "SB::Insertion:\n";
  test<std::function<void(container_type::iterator, container_type::iterator, comp_type)>, container_type, fill_type, comp_type>(
      sandbox::sort::insertionsort<container_type::iterator, comp_type>, container_size_table, fill, comp, verbose);*/

  int val = 2;

  sandbox::tree::BinarySearchTree<int> bst;
  bst.insert(val);
  sandbox::tree::AVLTree<int> avl;
  sandbox::tree::RedBlackTree<int> rbt;

  //std::vector<int> v = {1, 2, 5, 7, 8};
  //sandbox::search::binarysearch(v.begin(), v.end(), comp, 0);

  sandbox::tools::Calculator calc;
  std::cout << calc.calculate("2 + 2 * 3") << std::endl;

  return 0;
}
