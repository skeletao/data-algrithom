#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#define INT32_MAX        2147483647

struct Edge
{
    int start;
    int dest;
    int weight;
    Edge(int s, int d, int w): start(s), dest(d), weight(w){}  
};

struct Vertex
{
    int node;
    int x;
    int y;
    int dis_s;
    int dis_d; // total distance from s->node->d
    Vertex(): node(0), x(0), y(0), dis_s(INT32_MAX), dis_d(INT32_MAX){}
    Vertex(int n, int x, int y): node(n), x(x), y(y), dis_s(INT32_MAX), dis_d(INT32_MAX){}
    Vertex(int n, int x, int y, int dis1, int dis2): node(n), x(x), y(y), dis_s(dis1), dis_d(dis2){}
    Vertex(const Vertex &v): node(v.node), x(v.x), y(v.y), dis_s(v.dis_s), dis_d(v.dis_d){}
    Vertex &operator =(const Vertex &v) {
        node = v.node;
        x = v.x;
        y = v.y;
        dis_s = v.dis_s;
        dis_d = v.dis_d;
        return *this;
    }
};

class MinHeap
{
    private:
        int size;
        int count;
        Vertex *array;
        int *pos;
    public:
        MinHeap(int n);
        ~MinHeap();
        void Swap(Vertex &node1, Vertex &node2);
        bool Compare(Vertex &node1, Vertex &node2);
        void HeapifyUp(int idx);
        void HeapifyDown(int idx);
        void Push(const Vertex &node);
        Vertex Pop();
        void Update(const Vertex &node);
        void Clears();
        bool IsEmpty();
};

MinHeap::MinHeap(int n)
{
    size = n;
    array = new Vertex[n];
    pos = new int[n];
    count = 0;
}

MinHeap::~MinHeap()
{
    delete[] array;
    array = nullptr;
}

void MinHeap::Swap(Vertex &node1, Vertex &node2)
{
    Vertex tmp(node1);
    node1 = node2;
    node2 = tmp;
    
    int tmp2 = pos[node1.node];
    pos[node1.node] = pos[node2.node];
    pos[node2.node] = tmp2;
}

bool MinHeap::Compare(Vertex &node1, Vertex &node2)
{
    return (node1.dis_d < node2.dis_d) ? true : false;
}


void MinHeap::HeapifyUp(int idx)
{
    while (idx > 0)
    {
        if (Compare(array[idx], array[(idx-1)/2]))
        {
            Swap(array[idx], array[(idx-1)/2]);
            idx = (idx-1)/2;
        } else
        {
            break;
        }
    }
}

void MinHeap::HeapifyDown(int idx)
{
    int min = idx;

    while (true)
    {
        if (idx*2+1 < count && Compare(array[idx*2+1], array[min])) min = idx*2+1;
        if (idx*2+2 < count && Compare(array[idx*2+2], array[min])) min = idx*2+2;
        if (idx == min) break;
        Swap(array[idx], array[min]);
        idx = min;
    }
}

void MinHeap::Push(const Vertex &node)
{
    if (count == size) return;
    
    array[count] = node;
    
    pos[node.node] = count;
    count += 1;

    HeapifyUp(count-1);
}

Vertex MinHeap::Pop()
{
    if (count == 0) throw("error");

    Vertex root = array[0];
    if (count == 1) 
    {
        count = 0;
        return root;
    }

    Swap(array[0], array[count-1]);
    count -= 1;
    HeapifyDown(0);
    return root;
}

void MinHeap::Update(const Vertex &node)
{
    int idx = pos[node.node];
    array[idx] = node;
    HeapifyUp(idx);
}

void MinHeap::Clears()
{
    count = 0;
}

bool MinHeap::IsEmpty()
{
    return count == 0;
}

#endif