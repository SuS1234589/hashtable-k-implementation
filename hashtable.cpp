#include <algorithm>
#include <utility>
#include <vector>

template <typename K, typename V> struct Bucket {
  std::vector<std::pair<K, V>> elements;
  Bucket *next = nullptr;

  Bucket(size_t size) { elements.reserve(size); }
  ~Bucket() { delete next; }
};

template <typename K, typename V, typename Hash = std::hash<K>>
class Hashtable {
  std::vector<Bucket<K, V> *> table;
  size_t bucket_count;
  size_t bucket_element_count;
  Hash hasher; // lets see if we can code our own hash function

  size_t get_index(const K &key) const { return hasher(key) % bucket_count; }
  Bucket<K, V> *get_head(const K &key) {
    size_t index = hasher(key) % bucket_count;
    return table[index];
  }

public:
  Hashtable(size_t buckets, size_t bucket_size, Hash h = Hash())
      : bucket_count(buckets), bucket_element_count(bucket_size), hasher(h) {
    table.resize(bucket_count, nullptr);

    if (buckets == 0 || bucket_size == 0) {
      throw std::invalid_argument(
          "Number of buckets and bucket size must be greater than 0");
    }
  }

  ~Hashtable() {
    for (auto it : table)
      delete it;
  }

  int insert(const K &key, const V &value) {
    Bucket<K, V> *bucket = get_head(key);
    // this means the bucket is emptyy
    if (!bucket) {
      bucket = new Bucket<K, V>(bucket_element_count);
      bucket->elements.emplace_back(key, value);
      return 1;
    }
    // this is the case where the bucket is not empty
    while (bucket) {
      if (bucket->elements.size() < bucket_element_count) {
        bucket->elements.emplace_back(key, value);
        return 1;
      }
      if (!bucket->next)
        break;
      bucket = bucket->next;
      // now if all existing buckets are full we do this instead
    }
    bucket->next = new Bucket<K, V>(bucket_element_count);
    bucket->next->elements.emplace_back(key, value);
    return 1;
  }

  const V *find(const K &key) const {
    for (Bucket<K, V> *bucket = get_head(key); bucket; bucket = bucket->next) {
      auto it =
          std::find_if(bucket->elements.begin(), bucket->elements.end(),
                       [&key](const auto &pair) { return pair.first == key; });
      if (it != bucket->elements.end())
        return &it->second;
    }
    return nullptr;
  }

  int erase(const K &key, const V &value) {
    Bucket<K, V> *bucket = get_head(key);
    while (bucket) {
      for (auto it = bucket->elements.begin();
           it != bucket->elements.end(); it++) {
        if (it->first() == key && it->second() == value) {
          bucket->elements.erase(it);
          return 1;
        }
      }
      bucket = bucket->next;
    }
    return 0;
  }

  int remove(const K &key) {
    Bucket<K, V> *bucket = get_head(key);
    while (bucket) {
      for (auto it = bucket->elements.begin(); it != bucket->elements.end();
           it++) {
        if (it->first() == key) {
          bucket->elements.erase(it);
          return 1;
        }
      }
      bucket = bucket->next;
    }
    return 0;
  }
};

int main() { return 0; }
