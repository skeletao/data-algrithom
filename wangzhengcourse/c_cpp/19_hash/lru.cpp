#ifndef LRU_HASH_LINKED_LIST_HPP
#define LRU_HASH_LINKED_LIST_HPP

#include <iostream>
#include <unordered_map>
#include <string>

template<typename K, typename V>
class lru
{
private:
    struct link{
      link *prev;
      link *next;
      K key;
      V value;  
      link(K k, V v): key(k), value(v),prev(nullptr),next(nullptr)
      {}
    };
    std::unordered_map<K, link*> hash;
    link* head;
    int size;
    int count;
    void remove_tail();
    void add_to_head(link*);
    void move_to_head(link*);
public:
    lru(int);
    ~lru();
    void put(K, V);
    V get(K);
    void display();
};


template<typename K, typename V>
lru<K,V>::lru(int n)
{
    size = n;
    count = 0;
    head = nullptr;
}

template<typename K, typename V>
lru<K, V>::~lru()
{
    link *node = head;
    while (count-- > 0)
    {
        node = head;
        head = head->next;
        delete node;
    }
    head = nullptr;
    hash.clear();
    size = 0;
}

template<typename K, typename V>
void lru<K, V>::put(K k, V v)
{
    auto p = hash.find(k);
    if (p != hash.end())
    {
        p->second->value = v; 
        move_to_head(p->second);
        return;
    }

    if (size == count)
    {
        hash.erase(head->prev->key);
        remove_tail();
        count--;
    }
    link *tmp = new link(k, v);
    add_to_head(tmp);
    count++;
    hash[k] = tmp;
}

template<typename K, typename V>
V lru<K, V>::get(K k)
{
    auto p = hash.find(k);
    if (p != hash.end())
    {
        move_to_head(p->second);
        return p->second->value;
    } else
    {
        return NULL;
    }
}

template<typename K, typename V>
void lru<K, V>::add_to_head(link *node)
{
    if (head == nullptr)
    {
        head = node;
        head->prev = head;
        head->next = head;
    } 
    else
    {
        node->prev = head->prev;
        node->next = head;
        head->prev->next = node;
        head->prev = node;
        head = node;
    }
}

template<typename K, typename V>
void lru<K, V>::remove_tail()
{
    if (head==nullptr) return;

    if (head->prev == head->next) 
    {
        delete head;
        head = nullptr;
        return;
    }

    link *tail = head->prev;
    tail->prev->next = head;
    head->prev = tail->prev;
    delete tail;
}

template<typename K, typename V>
void lru<K, V>::move_to_head(link *node)
{
    if (head == nullptr || head->prev == head->next || head==node) return;
    if (head->next == node && node->prev == head)
    {
        head = node;
        return;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        node->prev = head->prev;
        node->next = head;
        head->prev->next = node;
        head->prev = node;
        head = node;
    }
    
}


template<typename K, typename V>
void lru<K, V>::display()
{
    link *node = head;
    int i = count;
    while (i > 0)
    {
        std::cout << node->key << "[" << node->value << "] ";
        node = node->next;
        i--;
    }
    std::cout << std::endl;
}

#endif


int main(void)
{
    lru<std::string, int> lru(5);

    lru.put("one", 1);
    lru.put("two", 2);
    lru.put("three", 3);
    lru.put("four", 4);
    lru.put("five", 5);
    lru.put("six", 6);
    std::cout << "********put 1~6, size:5********" << std::endl;
    lru.display();

    lru.put("one", 1);
    lru.put("two", 2);
    std::cout << "********put 1 and 2********" << std::endl;
    lru.display();

    lru.get("two");
    lru.get("six");
    std::cout << "********get 2 and 6********" << std::endl;
    lru.display();

    return 0;
}