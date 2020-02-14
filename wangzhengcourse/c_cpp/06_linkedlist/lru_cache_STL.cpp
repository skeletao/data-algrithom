#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

class lru_cache {
    public:
        lru_cache(int);
        void refer(int);
        void display();
    
    private:
        list<int> dq;
        unordered_map<int, list<int>::iterator> map;
        int csize;
};

lru_cache::lru_cache(int n)
{
    csize = n;
}

void lru_cache::refer(int x)
{
    if (map.find(x) == map.end()) // not in the buffer
    {
        if (dq.size() == csize)  // buffer is full
        {
            int val = dq.back();
            dq.pop_back();
            map.erase(val);
        }
    } 
    else
    {
        dq.erase(map[x]);
    }
    
    dq.push_front(x);
    map[x] = dq.begin();
}

void lru_cache::display()
{
    for (auto it = dq.begin(); it != dq.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main(void)
{
    lru_cache lru(4);

    lru.refer(1);
    lru.refer(2);
    lru.refer(3);
    lru.refer(1);
    lru.refer(4);
    lru.refer(5);

    lru.display();

    // vector<int> vec;
    // vec.push_back(5);
    // vec.push_back(7);
    // vec.push_back(2);
    // vec.push_back(1);
    // vec.push_back(8);

    // for (int i = 0; i < vec.size(); i++)
    // {
    //     cout << vec[i] << endl;
    // }

    // vector<int>::iterator it = vec.begin();
    // cout << *it << endl;

    // for (; it != vec.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    return 0;
}