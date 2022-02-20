#include <iostream>
using namespace std;

#define tab "\t"

class List {
    class Element
    {
        int Data;       // Значение элемента
        Element* pNext; // Адрес следующего элемента
        Element* pPrev; // Адрес предыдущего элемента
        
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
        Data(Data), pNext(pNext), pPrev(pPrev)
        {
            //cout << "EConstructor: " << this << endl;
        }
        ~Element()
        {
            //cout << "EDestructor: " << this << endl;
        }
        friend class List;
    }*Head, *Tail;
    size_t size;
    
    class BaseIterator
    {
    protected:
        Element* Temp;
    public:
        BaseIterator(Element* Temp = nullptr) : Temp(Temp)
        {
            cout << "BitConstructor" << this << endl;
        }
        ~BaseIterator()
        {
            cout << "BitDestructor" << this << endl;
        }
        virtual BaseIterator& operator ++() = 0;
        //virtual BaseIterator operator ++(int) = 0;
        
        virtual BaseIterator& operator --() = 0;
        //virtual BaseIterator operator --(int) = 0;
        
        bool operator== (const BaseIterator& other)const
        {
            return this -> Temp == other.Temp;
        }
        bool operator!= (const BaseIterator& other)const
        {
            return this -> Temp != other.Temp;
        }
        const int& operator*() const
        {
            return Temp -> Data;
        }
        operator bool() const
        {
            return Temp;
        }
    };
    
public:
    class ConstIterator: public BaseIterator
    {
    public:
        ConstIterator(Element* Temp = nullptr) : BaseIterator(Temp)
        {
            cout << "СItConstructor: \t" << this << endl;
        }
        ~ConstIterator()
        {
            cout << "СItDestructor: \t" << this << endl;
        }
        ConstIterator& operator ++ ()
        {
            Temp = Temp -> pNext;
            return *this;
        }
        ConstIterator operator ++ (int)
        {
            ConstIterator old = *this;
            Temp = Temp -> pNext;
            return old;
        }
        ConstIterator& operator -- ()
        {
            Temp = Temp -> pPrev;
            return *this;
        }
        ConstIterator operator -- (int)
        {
            ConstIterator old = *this;
            Temp = Temp -> pPrev;
            return old;
        }
    };
    class ConstReverseIterator : public BaseIterator
    {
    public:
        ConstReverseIterator(Element* Temp = nullptr) : BaseIterator(Temp)
        {
            cout << "СRItConstructor: \t" << this << endl;
        }
        ConstReverseIterator& operator++()
        {
            Temp = Temp -> pPrev;
            return *this;
        }
        ConstReverseIterator operator++(int)
        {
            ConstReverseIterator old = *this;
            Temp = Temp -> pPrev;
            return old;
        }
        ConstReverseIterator& operator--()
        {
            Temp = Temp -> pPrev;
            return *this;
        }
        ConstReverseIterator operator--(int)
        {
            ConstReverseIterator old = *this;
            Temp = Temp -> pPrev;
            return old;
        }
    };
    
    class Iterator: public ConstIterator
    {
    public:
        Iterator(Element* Temp = nullptr): ConstIterator(Temp)
        {
            //cout << "ItConstructor:\t" << this << endl;
        }
        ~Iterator()
        {
            //cout << "ItDestructor:\t" << this << endl;
        }
        int& operator*()
        {
            return Temp -> Data;
        }
    };
    class ReverseIterator: public ConstReverseIterator
    {
    public:
        ReverseIterator(Element* Temp = nullptr): ConstReverseIterator(Temp)
        {
            cout << "RItConstructor:\t" << this << endl;
        }
        ~ReverseIterator()
        {
            cout << "RItDestructor:\t" << this << endl;
        }
        int& operator*()
        {
            return Temp -> Data;
        }
    };
    ConstIterator сbegin()const
    {
        return Head;
    }
    ConstIterator сend()const
    {
        return nullptr;
    }
    
    ConstReverseIterator сrbegin()const
    {
        return Tail;
    }
    ConstReverseIterator сrend()const
    {
        return nullptr;
    }
    Iterator begin()const
    {
        return Head;
    }
    Iterator end()const
    {
        return nullptr;
    }
    
    ReverseIterator rbegin()const
    {
        return Tail;
    }
    ReverseIterator rend()const
    {
        return nullptr;
    }
    
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        //cout << "LConstructor: " << this << endl;
    }
    List(const initializer_list<int>& il) : List()
    {
        cout << typeid(il.begin()).name() << endl;
        for (int const* it = il.begin(); it != il.end(); ++it) {
            push_back(*it);
        }
    }
    ~List()
    {
        while(Head) pop_front();
        // while(Tail) pop_back();
        //cout << "LDestructor: " << this << endl;
    }
    
    // MARK: -- ADDING ELEMENTS:
    
    void push_front(int Data)
    {
        if (Head == nullptr&&Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        
//        Element* New = new Element(Data);
//        New->pNext = Head;
//        Head->pPrev = New;
//        Head = New;
        
        Head = Head->pPrev = new Element(Data, Head);
        size++;
    }
    
    void push_back(int Data)
    {
        if(Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size ++;
            return;
        }
//        Element* New = new Element(Data);
//        New -> pPrev = Tail;
//        Tail -> pNext = New;
//        Tail = New;
        
        Tail = Tail -> pNext = new Element(Data, nullptr, Tail);
        size ++;
    }
    void insert(int index, int Data)
    {
        if(index > size) return;
        if (index == 0) return push_front(Data);
        if (index == size) return push_back(Data);
        Element* Temp;
        if (index < size / 2)
        {
            Temp = Head;
            for (int i = 0; i < index; ++i) {
                Temp = Temp -> pNext;
            }
        }
        else
        {
            Temp = Tail;
            for (int i = 0; i < size - 1 - index; ++i) {
                Temp = Temp -> pPrev;
            }
        }
        //Неважно, с какой стороны мы дошли до нужного элемента. Процедура добавления нового элемента будет идентичной
//        Element* New = new Element(Data);
//        New -> pNext = Temp;
//        New -> pPrev = Temp -> pPrev;
//        Temp -> pPrev -> pNext = New;
//        Temp -> pPrev = New;
        
        Temp -> pPrev = Temp -> pPrev -> pNext = new Element(Data, Temp, Temp -> pPrev);
        size ++;
    }
    // MARK: -- REMOVING ELEMENTS:
    void pop_front()
    {
        if(Head == nullptr && Tail == nullptr)
            return;
        if(Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
            size--;
            return;
        }
        Head = Head -> pNext;
        delete Head -> pPrev;
        Head -> pPrev = nullptr;
        size --;
    }
    void pop_back()
    {
        if(Head == Tail)
            return pop_front();
        Tail = Tail -> pPrev;
        delete Tail -> pNext;
        Tail -> pNext = nullptr;
        size--;
    }
    // MARK: --  METHODS:
    
    void print()const
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Element's count of the list: " << size << endl;
    }
    void reverse_print()const
    {
        for(Element* Temp = Tail; Temp; Temp=Temp->pPrev)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Element's count of the list: " << size << endl;
    }
};

//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

int main(int argc, const char * argv[])
{
#ifdef RANGE_BASED_FOR_ARRAY
    int n;
    cout << "Enter size: "; cin >> n;
    List list;
    for (int i = 0; i < n; i++)
    {
        //list.push_front(rand() % 100);
        list.push_back(rand() % 100);
    }

    int index;
    int value;
    cout << "Enter index: "; cin >> index;
    cout << "Enter value: "; cin >> value;
    list.insert(index, value);

    list.print();
    cout << endl;
    list.reverse_print();
#endif
    
#ifdef RANGE_BASED_FOR_LIST
    List list = { 3, 5, 8, 13, 21 };
    
    list.print();
    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    for (List::ConstReverseIterator it = list.сrbegin(); it; ++it)
    {
        cout << *it << tab;
    }
    
#endif

    return 0;
}
