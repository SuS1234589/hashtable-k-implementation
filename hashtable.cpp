#include <iostream>
#include <random>
#include <string>
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

  size_t get_index(const K &key) { return hasher(key) % bucket_count; }
  Bucket<K, V> *get_head(const K &key) const {
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

  // ah shit this makes duplicate
  // this should do the job
  int insert(const K &key, const V &value) {
    Bucket<K, V> *bucket = get_head(key);
    // just add the element
    while (bucket) {
      for (auto &pair : bucket->elements) {
        if (pair.first == key) {
          pair.second = value;
          return 0; // a value was updated
        }
      }
      if (!bucket->next)
        break;
      bucket = bucket->next;
    }

    if (!bucket) {
      bucket = new Bucket<K, V>(bucket_element_count);
      table[get_index(key)] = bucket;
    } else if (bucket->elements.size() >= bucket_element_count) {
      bucket->next = new Bucket<K, V>(bucket_element_count);
      bucket = bucket->next;
    }
    bucket->elements.emplace_back(key, value);
    return 1; //  a value was added
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

  // okay this should do the job
  int erase(const K &key, const V &value) {
    Bucket<K, V> *bucket = get_head(key);
    while (bucket) {
      for (auto it = bucket->elements.begin(); it != bucket->elements.end();
           ++it) {
        if (it->first == key && it->second == value) {
          it = bucket->elements.erase(it);
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
           ++it) {
        if (it->first == key) {
          it = bucket->elements.erase(it);
          return 1;
        }
        bucket = bucket->next;
      }
    }
    return 0;
  }
};

// this is the end

int main() {
  // Small table: 5 buckets, 2 elements per bucket
  Hashtable<int, std::string> ht(5, 2);

  std::cout << "=== Basic Insert & Find ===\n";
  ht.insert(1, "Alice");
  ht.insert(2, "Bob");
  ht.insert(3, "Charlie");
  ht.insert(4, "Diana");

  std::cout << "Find key 1: " << (ht.find(1) ? *ht.find(1) : "not found")
            << "\n";
  std::cout << "Find key 2: " << (ht.find(2) ? *ht.find(2) : "not found")
            << "\n";
  std::cout << "Find key 42 (missing): "
            << (ht.find(42) ? *ht.find(42) : "not found") << "\n";

  std::cout << "\n=== Bucket Overflow (Chaining) ===\n";
  // Force same bucket by using keys with same hash % bucket_count
  ht.insert(5, "Eve");    // should go into same bucket as key 0
  ht.insert(10, "Frank"); // should overflow if bucket size = 2

  std::cout << "Find key 5: " << (ht.find(5) ? *ht.find(5) : "not found")
            << "\n";
  std::cout << "Find key 10: " << (ht.find(10) ? *ht.find(10) : "not found")
            << "\n";

  std::cout << "\n=== Duplicate Keys ===\n";
  ht.insert(2, "Bobby");
  ht.insert(2, "Bob Jr");

  std::cout << "Find key 2 (first occurrence): "
            << (ht.find(2) ? *ht.find(2) : "not found") << "\n";

  std::cout << "\n=== Erase Specific Key-Value ===\n";
  std::cout << "Erase (3, Charlie): "
            << (ht.erase(3, "Charlie") ? "success" : "fail") << "\n";
  std::cout << "Find key 3: " << (ht.find(3) ? *ht.find(3) : "not found")
            << "\n";

  std::cout << "\n=== Remove All for a Key ===\n";
  std::cout << "Remove key 2: " << (ht.remove(2) ? "success" : "fail") << "\n";
  std::cout << "Find key 2: " << (ht.find(2) ? *ht.find(2) : "not found")
            << "\n";

  std::cout << "\n=== Stress Test with Random Data ===\n";
  Hashtable<int, int> bigHT(100, 3); // bigger table
  std::mt19937 rng(42);              // fixed seed for reproducibility
  std::uniform_int_distribution<int> dist(0, 1000);

  // Insert 1000 random pairs
  for (int i = 0; i < 1000; i++) {
    bigHT.insert(dist(rng), i);
  }

  // Search for some known keys
  std::cout << "Find random key 123: "
            << (bigHT.find(123) ? std::to_string(*bigHT.find(123))
                                : "not found")
            << "\n";
  std::cout << "Find random key 456: "
            << (bigHT.find(456) ? std::to_string(*bigHT.find(456))
                                : "not found")
            << "\n";
  std::cout << "Find random key 789: "
            << (bigHT.find(789) ? std::to_string(*bigHT.find(789))
                                : "not found")
            << "\n";

  std::cout << "\nAll tests done.\n";
}
