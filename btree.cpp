#include "btree.hpp"

template <typename T, typename Key, int Degree>
btree<T, Key, Degree>::btree() : root(std::make_unique<node>()) {}

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

    if (key > curr_node->keys[curr_node->keys.size() - 1]) {
      child_index = curr_node->keys.size();
    }

    if (curr_node->n_children - 1 != child_index)
      return false;

    curr_node = curr_node->children[child_index].get();
  }
}
