#include "btree.hpp"
#include <stdexcept>

template <typename T, typename Key, int Degree>
btree<T, Key, Degree>::btree() : root(std::make_unique<node>()) {}

template <typename T, typename Key, int Degree>
void btree<T, Key, Degree>::split_child(node *node,
                                        size_t child_index) noexcept {
  throw std::runtime_error("Not implemented");
}

template <typename T, typename Key, int Degree>
bool btree<T, Key, Degree>::contains(const Key &key) const noexcept {
  node *curr_node = root.get();

  while (true) {

    size_t child_index{};
    for (const Key &s_key : curr_node->keys) {
      if (key == s_key)
        return true;

      if (key < s_key)
        break;

      child_index++;
    }

    if (key > curr_node->keys[curr_node->n_keys - 1]) {
      child_index = curr_node->keys.size();
    }

    if (curr_node->n_children - 1 != child_index)
      return false;

    curr_node = curr_node->children[child_index].get();
  }
}

template <typename T, typename Key, int Degree>
const T &btree<T, Key, Degree>::get(const Key &key) const {
  node *curr_node = root.get();
  while (true) {
    size_t child_index{};
    for (const Key &s_key : curr_node->keys) {
      if (key == s_key)
        // child_index also tracks where the value index would be
        return curr_node->values[child_index];

      if (key < s_key)
        break;

      child_index++;
    }

    if (key > curr_node->keys[curr_node->n_keys - 1]) {
      child_index = curr_node->keys.size();
    }

    if (curr_node->n_children - 1 != child_index)
      throw KeyNotFoundException("Key not found");

    curr_node = curr_node->children[child_index].get();
  }
}
