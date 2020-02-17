#include <iostream>
#include <list>
#include <memory>
#include <functional>
#include <cstring>

template<typename K, typename V>
class hash_table
{
public:
    using hash = std::hash<K>;
    using node = std::pair<K, V>;
    using ls = std::list<node>;
    hash_table(int, float);
    ~hash_table();
    node& find(K);
    void insert(K,V);
    void erase(K);
    void display();
private:
    int size; 
    int count;
    float load_factor;
    ls *table;
    hash hasher;
};

template<typename K, typename V>
hash_table<K, V>::hash_table(int n, float f): size(n), load_factor(f)
{
    count = 0;
    table = new ls[size];
    hasher = hash();
}

template<typename K, typename V>
hash_table<K, V>::~hash_table()
{
    for (int i = 0; i < size; i++)
    {
        table[i].clear();
    }
    delete[] table;
}

template<typename K, typename V>
typename hash_table<K, V>::node &hash_table<K, V>::find(K key)
{
    int index = hasher(key) % size;
    for (auto x : table[index])
    {
        if (x.first = key) return x;
    }
    return NULL;
}

template<typename K, typename V>
void hash_table<K, V>::insert(K key, V value)
{
    int index = hasher(key) % size;

    typename ls::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if ((*i).first == key) return;
    }

    table[index].emplace_back(key, value);
    count++;
}

template<typename K, typename V>
void hash_table<K, V>::erase(K key)
{
    int index = hasher(key) % size;
    typename ls::iterator i;

    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if ((*i).first == key) break;
    }

    if (i != table[index].end()) 
    {
        table[index].erase(i);
        count--;
    }
}


template<typename K, typename V>
void hash_table<K, V>::display()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "Bucket "<< i << ": ";
        for (auto x: table[i])
        {
            std::cout << x.first << "["  << x.second <<"] ";
        }
        std::cout << std::endl;
    }
}


int main(void)
{
    hash_table<std::string, int> table(5, 0.75);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    table.insert("four", 4);
    table.insert("five", 5);
    table.insert("six", 6);
    table.insert("seven", 7);
    table.insert("eight", 8);
    table.insert("nine", 9);
    table.insert("ten", 10);
    std::cout << "********Insert 1~10, size:5********" << std::endl;
    table.display();

    table.erase("two");
    table.erase("six");
    std::cout << "********Delete 2 and 6********" << std::endl;
    table.display();

    return 0;
}


