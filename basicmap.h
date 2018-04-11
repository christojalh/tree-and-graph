

#ifndef BASICMAP
#define BASICMAP

template<T>
class MyMap
{
public:
    void connect(T& objA, T& objB);
    // std::queue
    int shortestDistance(T& objA, T& objB);

private:
    struct Node
    {
        T m_data;
        std::vector<Node*> m_neighbors;
    }
};

#endif