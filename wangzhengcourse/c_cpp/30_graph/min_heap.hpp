#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

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
    int distance;
    Vertex(): node(0), distance(0){}
    Vertex(int n, int d): node(n), distance(d){}
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
        void Push(Vertex node);
        Vertex Pop();
        void Update(Vertex node);
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
    Vertex tmp;
    tmp.distance = node1.distance;
    tmp.node = node1.node;

    node1.distance = node2.distance;
    node1.node = node2.node;

    node2.distance = tmp.distance;
    node2.node = tmp.node;
    
    int tmp2 = pos[node1.node];
    pos[node1.node] = pos[node2.node];
    pos[node2.node] = tmp2;
}

bool MinHeap::Compare(Vertex &node1, Vertex &node2)
{
    return (node1.distance < node2.distance) ? true : false;
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

void MinHeap::Push(Vertex node)
{
    if (count == size) return;
    
    array[count].distance = node.distance;
    array[count].node = node.node;
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

void MinHeap::Update(Vertex node)
{
    int idx = pos[node.node];
    int dis = array[idx].distance;
    array[idx].distance = node.distance;
    HeapifyUp(idx);
}

bool MinHeap::IsEmpty()
{
    return count == 0;
}

#endif