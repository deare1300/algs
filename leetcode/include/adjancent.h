#ifndef ADJANCENT_H
#define ADJANCENT_H

template<class T>
struct Node
{
    T val;
    Node<T> *next;
    Node():val(0), next(0){}
    Node(T val):val(val),next(0){}
};

template<class S, class T>
struct Adjancent
{
    public:
        Adjancent();
        virtual ~Adjancent();
        Ajancent<S> *next;
        Node<T> *head;
        void addNode(Node<T> *node)
        {
            if(head == 0)
                head = node;
            Node<T> *p = head;
            while(p->next)
                p = p->next;
            p->next = node;
        }
    protected:
    private:
};

#endif // ADJANCENT_H
