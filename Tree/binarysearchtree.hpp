#pragma once
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <utility>

namespace sandbox {

  namespace trees {

    template <typename T>
    class BinarySearchTree {

      class BinaryNode {
        friend class BinarySearchTree;

        T _value;

        BinaryNode* _left;
        BinaryNode* _right;

      public:
        explicit BinaryNode(const T& value = T()) : _value(value) {
          _right = _left = nullptr;
        };
        explicit BinaryNode(T&& value) : _value(std::forward<T>(value)) {
          _right = _left = nullptr;
        };

        const T& value() const noexcept {
          return _value;
        }

        const BinaryNode* left() const noexcept {
          return _left;
        }

        const BinaryNode* right() const noexcept {
          return _right;
        }
      };

      BinaryNode* _root;

    public:
      BinarySearchTree() : _root(nullptr) {};
      explicit BinarySearchTree(const T& value) {
        _root = new BinaryNode(value);
      }
      explicit BinarySearchTree(T&& value) {
        _root = new BinaryNode(std::forward<T>(value));
      }

      const BinaryNode* root() const noexcept {
        return _root;
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void insert(U&& value) {
        _insert(_root, std::forward<T>(value));
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      const BinaryNode* find(U&& value) const {
        return _find(_root, std::forward<T>(value));
      }

      template <typename U, class = typename std::enable_if<std::is_same<typename std::decay<U>::type, T>::value>::type>
      void remove(U&& value) {
        _remove(_root, std::forward<T>(value));
      }

      ~BinarySearchTree() {
        _delete_subtree(_root);
      }

    private:
      void _insert(BinaryNode*& root, T&& value) {
        if (!root) {
          root = new BinaryNode(std::forward<T>(value));
        }
        else if (value < root->_value) {
          _insert(root->_left, std::forward<T>(value));
        }
        else if (root->_value < value) {
          _insert(root->_right, std::forward<T>(value));
        }
        else {
          root->_value = value;
        }
      }

      const BinaryNode* _find(const BinaryNode* const & root, T&& value) const {
        if (!root) {
          return root;
        }

        if (value < root->_value) {
          return _find(root->_left, std::forward<T>(value));
        }
        else if (root->_value < value){
          return _find(root->_right, std::forward<T>(value));
        }
        else {
          return root;
        }
      }

      BinaryNode* _min(BinaryNode* const & root) const noexcept {
        if (root) {
          if (root->_left) {
            return _min(root->_left);
          }
        }

        return root;
      }

      void _remove(BinaryNode*& root, T&& value) {
        if (root) {
          if (value < root->_value) {
            _remove(root->_left, std::forward<T>(value));
          }
          else if (root->_value < value) {
            _remove(root->_right, std::forward<T>(value));
          }
          else {
            if (root->_left && root->_right) {
              BinaryNode* suc = _min(root->_right);
              std::swap(root->_value, suc->_value);
              _remove(root->_right, std::move(suc->_value));
            }
            else if (!root->_right && !root->_left) {
              _delete_node(root);
            }
            else {
              BinaryNode* del = root;
              root = root->_left ? root->_left : root->_right;
              _delete_node(del);
            }
          }
        }
      }

      void _delete_node(BinaryNode*& node) {
        delete node;
        node = nullptr;
      }

      void _delete_subtree(BinaryNode*& root) {
        if (root) {
          _delete_subtree(root->_left);
          _delete_subtree(root->_right);

          _delete_node(root);
        }
      }
    };

  }

}

#endif // BINARYSEARCHTREE_HPP
