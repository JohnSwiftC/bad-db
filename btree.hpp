#include <memory>
#include <vector>
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
  };

  std::unique_ptr<node> root;

public:
  btree();

  bool contains(const Key &key) const noexcept;
  const T &get(const Key &key) const;
  T &get_non_const(const Key &key);
};
