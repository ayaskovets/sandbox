#pragma once

#include <utility>

namespace sandbox {

  namespace tree {

    template <typename T>
    class BinarySearchTree {

      class BinaryNode {
        friend class BinarySearchTree;

        T key;

        BinaryNode* left;
        BinaryNode* right;

      public:
        template <typename U, class = std::enable_if_t<std::is_same<std::decay_t<U>, T>::value>>
        explicit BinaryNode(U&& Key = U()) : key(std::forward<U>(Key)) {
          right = left = nullptr;
        };
      };

      BinaryNode* root;

    public:
      BinarySearchTree() : root(nullptr) {};
      template <typename U, class = std::enable_if_t<std::is_same<std::decay_t<U>, T>::value>>
      explicit BinarySearchTree(T&& key) {
        root = new BinaryNode(std::forward<T>(key));
      }

      template <typename U, class = std::enable_if_t<std::is_same<std::decay_t<U>, T>::value>>
      void insert(U&& key) {
        insertNode(root, std::move(key));
      }

      template <typename U, class = std::enable_if_t<std::is_same<std::decay_t<U>, T>::value>>
      const BinaryNode* find(U&& key) const {
        return findNode(root, std::forward<T>(key));
      }

      template <typename U, class = std::enable_if_t<std::is_same<std::decay_t<U>, T>::value>>
      void remove(U&& key) {
        removeNode(root, std::forward<T>(key));
      }

      ~BinarySearchTree() {
        deleteSubtree(root);
      }

    private:
      void insertNode(BinaryNode*& node, T&& key) {
        if (!node) {
          node = new BinaryNode(std::forward<T>(key));
        }
        else if (key < node->key) {
          insertNode(node->left, std::forward<T>(key));
        }
        else if (node->key < key) {
          insertNode(node->right, std::forward<T>(key));
        }
        else {
          node->key = key;
        }
      }

      const BinaryNode* findNode(const BinaryNode* const node, T&& key) const {
        if (!node) {
          return nullptr;
        }

        if (key < node->key) {
          return findNode(node->left, std::forward<T>(key));
        }
        else if (node->key < key) {
          return findNode(node->right, std::forward<T>(key));
        }
        else {
          return node;
        }
      }

      BinaryNode* successor(BinaryNode* const node) const noexcept {
        if (node && node->left) {
          return successor(node->left);
        }

        return node;
      }

      void removeNode(BinaryNode*& node, T&& key) {
        if (node) {
          if (key < node->key) {
            removeNode(node->left, std::forward<T>(key));
          }
          else if (node->key < key) {
            removeNode(node->right, std::forward<T>(key));
          }
          else {
            if (node->left && node->right) {
              BinaryNode* suc = successor(node->right);
              std::swap(node->key, suc->key);
              removeNode(node->right, std::move(suc->key));
            }
            else if (!node->right && !node->left) {
              deleteNode(node);
            }
            else {
              BinaryNode* del = node;
              node = node->left ? node->left : node->right;
              deleteNode(del);
            }
          }
        }
      }

      void deleteNode(BinaryNode*& node) {
        if (node) {
          delete node;
          node = nullptr;
        }
      }

      void deleteSubtree(BinaryNode*& node) {
        if (node) {
          deleteSubtree(node->left);
          deleteSubtree(node->right);

          deleteNode(node);
        }
      }
    };

  }

}
