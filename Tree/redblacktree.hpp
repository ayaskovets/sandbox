#pragma once

#include <algorithm>
#include <utility>

namespace sandbox {

  namespace tree {

    template <typename T>
    class RedBlackTree {

      enum class RBColor {
        Red,
        Black
      };

      class RBNode {
        friend class RedBlackTree;

        T key;

        RBNode* parent;
        RBNode* left;
        RBNode* right;

        RBColor color;

        RBNode* grandparent() const noexcept {
          if (parent) {
            return parent->parent;
          }
          else {
            return nullptr;
          }
        }

        RBNode* sibling() const noexcept {
          if (parent) {
            return (this == parent->left ? parent->right : parent->left);
          }
          else {
            return nullptr;
          }
        }

        RBNode* uncle() const noexcept {
          if (parent) {
            return parent->sibling();
          }
          else {
            return nullptr;
          }
        }

      public:
        template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
        explicit RBNode(U&& Key = U(), RBColor Color = RBColor::Red) :
          key(std::forward<U>(Key)), parent(nullptr), right(nullptr), left(nullptr), color(Color) {
        }
      };

      RBNode* root;

    public:
      RedBlackTree() : root(nullptr) {}

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      explicit RedBlackTree(U&& key) {
        root = new RBNode(std::forward<U>(key));
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void insert(U&& key) {
        repairInsertion(insertNode(root, std::forward<T>(key)));

        while (root->parent) {
          root = root->parent;
        }
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      const RBNode* find(U&& key) const {
        return findNode(root, std::forward<T>(key));
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void remove(U&& key) {
        repairRemoval(removeNode(root, std::forward<T>(key)));

        while (root->parent) {
          root = root->parent;
        }
      }

      ~RedBlackTree() {
        deleteSubtree(root);
      }

    private:
      RBColor getColor(const RBNode* const node) const noexcept {
        return node ? node->color : RBColor::Black;
      }

      void setColor(RBNode* node, RBColor color) {
        if (node) {
          node->color = color;
        }
      }

      void rotateLeft(RBNode* node) {
        if (node && node->right) {
          RBNode* right = node->right;
          RBNode* parent = node->parent;

          node->right = right->left;
          right->left = node;
          node->parent = right;

          if (node->right) {
            node->right->parent = node;
          }

          if (parent) {
            if (node == parent->left) {
              parent->left = right;
            }
            else if (node == parent->right) {
              parent->right = right;
            }
          }

          right->parent = parent;
        }
      }

      void rotateRight(RBNode* node) {
        if (node && node->left) {
          RBNode* left = node->left;
          RBNode* parent = node->parent;

          node->left = left->right;
          left->right = node;
          node->parent = left;

          if (node->left) {
            node->left->parent = node;
          }

          if (parent) {
            if (node == parent->left) {
              parent->left = left;
            }
            else if (node == parent->right) {
              parent->right = left;
            }
          }

          left->parent = parent;
        }
      }

      void repairInsertion(RBNode*& node) {
        if (!node->parent) {
          setColor(node, RBColor::Black);
        }
        else if (getColor(node->parent) == RBColor::Black) {
          return;
        }
        else if (getColor(node->uncle()) == RBColor::Red) {
          setColor(node->parent, RBColor::Black);
          setColor(node->uncle(), RBColor::Black);
          setColor(node->grandparent(), RBColor::Red);

          repairInsertion(node->parent->parent);
        }
        else {
          RBNode* grandparent = node->grandparent();

          if (node->parent == grandparent->left && node == node->parent->right) {
            rotateLeft(node->parent);
            node = node->left;
            grandparent = node->grandparent();
          }
          else if (node->parent == grandparent->right && node == node->parent->left) {
            rotateRight(node->parent);
            node = node->right;
            grandparent = node->grandparent();
          }

          if (node == node->parent->left) {
            rotateRight(grandparent);
          }
          else {
            rotateLeft(grandparent);
          }

          setColor(node->parent, RBColor::Black);
          setColor(grandparent, RBColor::Red);
        }
      }

      RBNode*& insertNode(RBNode*& node, T&& key) {
        if (!node) {
          node = new RBNode(std::forward<T>(key));
          return node;
        }
        else if (key < node->key) {
          RBNode*& inserted = insertNode(node->left, std::forward<T>(key));
          node->left->parent = node;
          return inserted;
        }
        else if (node->key < key) {
          RBNode*& inserted = insertNode(node->right, std::forward<T>(key));
          node->right->parent = node;
          return inserted;
        }
        else {
          node->key = key;
          return node;
        }
      }

      const RBNode* findNode(const RBNode* const node, T&& key) const {
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

      void repairRemoval(RBNode*& node) {
        if (!node || node == root) {
          deleteNode(node);
        }
        else if (getColor(node) == RBColor::Red || getColor(node->left) == RBColor::Red || getColor(node->right) == RBColor::Red) {
          RBNode* child = (node->left ? node->left : node->right);
          setColor(child, RBColor::Black);

          if (child) {
            child->parent = node->parent;            
          }

          RBNode* del = node;
          node = child;

          deleteNode(del);
          return;
        }
        else {
          RBNode* sibling = nullptr;
          RBNode* parent = nullptr;
          RBNode* ptr = node;

          setColor(ptr, RBColor::Black);
          setColor(ptr->left, RBColor::Black);
          setColor(ptr->right, RBColor::Black);

          while (ptr != root && getColor(ptr->left) == RBColor::Black && getColor(ptr->right) == RBColor::Black) {
            parent = ptr->parent;

            bool left = (ptr == parent->left);

            sibling = ptr->sibling();
            if (getColor(sibling) == RBColor::Red) {
              setColor(sibling, RBColor::Black);
              setColor(parent, RBColor::Red);

              (left ? rotateLeft(parent) : rotateRight(parent));
            }
            else {
              if (getColor(sibling->left) == RBColor::Black && getColor(sibling->right) == RBColor::Black) {
                setColor(sibling, RBColor::Red);

                if (getColor(parent) != RBColor::Red) {
                  setColor(parent->left, RBColor::Black);
                  setColor(parent->right, RBColor::Black);                  
                }

                setColor(parent, RBColor::Black);

                ptr = parent;
              }
              else {
                if (getColor((left ? sibling->right : sibling->left)) == RBColor::Black) {
                  setColor((left ? sibling->left : sibling->right), RBColor::Black);
                  setColor(sibling, RBColor::Red);

                  (left ? rotateRight(sibling) : rotateLeft(sibling));
                  (left ? sibling = parent->right : sibling = parent->left);
                }

                setColor(sibling, parent->color);
                setColor(parent, RBColor::Black);

                setColor((left ? sibling->right : sibling->left), RBColor::Black);
                (left ? rotateLeft(parent) : rotateRight(parent));
                break;
              }
            }
          }
        }

        deleteNode(node);
        setColor(root, RBColor::Black);
      }

      RBNode* successor(RBNode* const & node) const noexcept {
        if (node && node->left) {
          return successor(node->left);
        }

        return node;
      }

      RBNode*& removeNode(RBNode*& node, T&& key) {
        if (node) {
          if (key < node->key) {
            return removeNode(node->left, std::forward<T>(key));
          }
          else if (node->key < key) {
            return removeNode(node->right, std::forward<T>(key));
          }
          else {
            if (node->left && node->right) {
              RBNode* suc = successor(node->right);
              std::swap(node->key, suc->key);
              return removeNode(node->right, std::move(suc->key));
            }
            else if (!node->right && !node->left) {
              return node;
            }
            else {
              return node->left ? node->left : node->right;
            }
          }
        }
        else {
          return node;
        }
      }

      void deleteNode(RBNode*& node) {
        if (node) {
          delete node;
          node = nullptr;
        }
      }

      void deleteSubtree(RBNode*& node) {
        if (node) {
          deleteSubtree(node->left);
          deleteSubtree(node->right);

          deleteNode(node);
        }
      }
    };

  }

}
