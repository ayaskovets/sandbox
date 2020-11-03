#pragma once

#include <algorithm>
#include <utility>

namespace sandbox {

  namespace tree {

    template <typename T>
    class AVLTree {

      class AVLNode {
        friend class AVLTree;

        T key;

        AVLNode* left;
        AVLNode* right;

        int height;

      public:
        template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
        explicit AVLNode(U&& Key = U()) : key(std::forward<U>(Key)), right(nullptr), left(nullptr), height(0) {}
      };

      AVLNode* root;

    public:
      AVLTree() : root(nullptr) {}

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      explicit AVLTree(U&& key) {
        root = new AVLNode(std::forward<U>(key));
        root->height = 1;
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void insert(U&& key) {
        insertNode(root, std::forward<T>(key));        
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      const AVLNode* find(U&& key) const {
        return findNode(root, std::forward<T>(key));
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void remove(U&& key) {
        removeNode(root, std::forward<T>(key));
      }

      ~AVLTree() {
        deleteSubtree(root);
      }

    private:
      int height(const AVLNode* const node) {
        return node ? node->height : 0;
      }

      int balanceFactor(const AVLNode* const node) {
        return node ? height(node->left) - height(node->right) : 0;
      }

      void rotateLeft(AVLNode*& node) {
        if (node && node->right) {
          AVLNode* right = node->right;
          node->right = right->left;
          right->left = node;

          node->height = std::max(height(node->left), height(node->right)) + 1;
          right->height = std::max(height(right->left), height(right->right)) + 1;

          node = right;
        }
      }

      void rotateRight(AVLNode*& node) {
        if (node && node->left) {
          AVLNode* left = node->left;
          node->left = left->right;
          left->right = node;

          node->height = std::max(height(node->left), height(node->right)) + 1;
          left->height = std::max(height(left->left), height(left->right)) + 1;

          node = left;
        }
      }

      void insertNode(AVLNode*& node, T&& key) {
        if (!node) {
          node = new AVLNode(std::forward<T>(key));
        }
        else if (key < node->key) {
          insertNode(node->left, std::forward<T>(key));
        }
        else if (node->key < key) {
          insertNode(node->right, std::forward<T>(key));
        }
        else {
          node->key = key;
          return;
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balance_factor = balanceFactor(node);
        if (balance_factor > 1) {
          if (balanceFactor(node->left) < 0) {
            rotateLeft(node->left);
          }

          rotateRight(node);
        }
        else if (balance_factor < -1) {
          if (balanceFactor(node->right) > 0) {
            rotateRight(node->right);
          }

          rotateLeft(node);
        }
      }

      const AVLNode* findNode(const AVLNode* const node, T&& key) const {
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

      AVLNode* successor(AVLNode* const node) const noexcept {
        if (node && node->left) {
          return successor(node->left);
        }

        return node;
      }

      void removeNode(AVLNode*& node, T&& key) {
        if (node) {
          if (key < node->key) {
            removeNode(node->left, std::forward<T>(key));
          }
          else if (node->key < key) {
            removeNode(node->right, std::forward<T>(key));
          }
          else {
            if (node->left && node->right) {
              AVLNode* suc = successor(node->right);
              std::swap(node->key, suc->key);
              removeNode(node->right, std::move(suc->key));
            }
            else if (!node->right && !node->left) {
              deleteNode(node);
            }
            else {
              AVLNode* del = node;
              node = node->left ? node->left : node->right;
              deleteNode(del);
            }
          }

          if (node) {
            node->height = std::max(height(node->left), height(node->right)) + 1;

            int balance_factor = balanceFactor(node);
            if (balance_factor > 1) {
              if (balanceFactor(node->left) < 0) {
                rotateLeft(node->left);
              }

              rotateRight(node);
            }
            else if (balance_factor < -1) {
              if (balanceFactor(node->right) > 0) {
                rotateRight(node->right);
              }

              rotateLeft(node);
            }
          }
        }
      }

      void deleteNode(AVLNode*& node) {
        if (node) {
          delete node;
          node = nullptr;
        }
      }

      void deleteSubtree(AVLNode*& node) {
        if (node) {
          deleteSubtree(node->left);
          deleteSubtree(node->right);

          deleteNode(node);
        }
      }
    };

  }

}
