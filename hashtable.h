#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
#include <algorithm>

template <typename K, typename V>
struct Bucket {
    std::vector<std::pair<K, V>> elements;
    Bucket *next = nullptr;

    Bucket(size_t size) { elements.reserve(size); }
    ~Bucket() { delete next; }
};

template <typename K, typename V, typename Hash = std::hash<K>>
class Hashtable {
    size_t bucket_count;
    size_t bucket_element_count;
    Hash hasher;

    size_t get_index(const K &key) { return hasher(key) % bucket_count; }
    Bucket<K, V> *get_head(const K &key) const {
        size_t index = hasher(key) % bucket_count;
        return table[index];
    }

public:
     std::vector<Bucket<K, V> *> table;

    Hashtable(size_t buckets, size_t bucket_size, Hash h = Hash())
        : bucket_count(buckets), bucket_element_count(bucket_size), hasher(h) {
        table.resize(bucket_count, nullptr);

        if (buckets == 0 || bucket_size == 0) {
            throw std::invalid_argument("Number of buckets and bucket size must be greater than 0");
        }
    }

    ~Hashtable() {
        for (auto it : table)
            delete it;
    }

    V get(const K& key) const {
    const V* v = find(key);
    if (!v) throw std::runtime_error("Key not found");
    return *v;
    } 

    int insert(const K &key, const V &value) {
        Bucket<K, V> *bucket = get_head(key);
        while (bucket) {
            for (auto &pair : bucket->elements) {
                if (pair.first == key) {
                    pair.second = value;
                    return 0;
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
        return 1;
    }

    const V *find(const K &key) const {
        for (Bucket<K, V> *bucket = get_head(key); bucket; bucket = bucket->next) {
            auto it = std::find_if(bucket->elements.begin(), bucket->elements.end(),
                                   [&key](const auto &pair) { return pair.first == key; });
            if (it != bucket->elements.end())
                return &it->second;
        }
        return nullptr;
    }

    int erase(const K &key, const V &value) {
        Bucket<K, V> *bucket = get_head(key);
        while (bucket) {
            for (auto it = bucket->elements.begin(); it != bucket->elements.end(); ++it) {
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
            for (auto it = bucket->elements.begin(); it != bucket->elements.end(); ++it) {
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

#endif // HASHTABLE_H

