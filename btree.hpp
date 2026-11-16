#include <memory>
#include <stdexcept>
#include <vector>

class KeyNotFoundException : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

template <typename T, typename Key, int Degree> class btree {
private:
  struct node {
    std::vector<Key> keys;
    std::vector<T> values;
    std::vector<std::unique_ptr<node>> children;

    size_t n_keys;
    size_t n_children;

    node()
        : keys(Degree - 1), values(Degree - 1), children(), n_keys{},
          n_children{} {}

    void insert_key_value(Key &&key, T &&value) noexcept {
      size_t insertion_index{};
      for (size_t i{}; i < keys.size(); ++i) {
        if (key < keys[i])
          insertion_index = i;
      }

      if (key > keys[n_keys - 1])
        insertion_index = n_keys;

      for (size_t i{n_keys}; i-- > insertion_index;) {
        keys[i] = keys[i + 1];
        values[i] = values[i + 1];
      }

      keys[insertion_index] = std::move(key);
      values[insertion_index] = std::move(value);
    }
  };

  std::unique_ptr<node> root;

  void split_child(node *node, size_t child_index) noexcept;

public:
  btree();

  bool contains(const Key &key) const noexcept;
  const T &get(const Key &key) const;
  T &get_non_const(const Key &key);
};
