#include <iostream>
using namespace std;

#define tab "\t"

template <typename T>
class List {
    class Element
    {
        T Data;       // Значение элемента
        Element* pNext; // Адрес следующего элемента
        Element* pPrev; // Адрес предыдущего элемента
        
    public:
        Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
        Data(Data), pNext(pNext), pPrev(pPrev)
        {
            //cout << "EConstructor: " << this << endl;
        }
        ~Element()
        {
            //cout << "EDestructor: " << this << endl;
        }
        friend class List<T>;
    }*Head, *Tail;
    size_t size;
    
    class BaseIterator
    {
    protected:
        Element* Temp;
    public:
        BaseIterator(Element* Temp = nullptr) : Temp(Temp)
        {
            //cout << "BitConstructor" << this << endl;
        }
        ~BaseIterator()
        {
            //cout << "BitDestructor" << this << endl;
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
        const T& operator*() const
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
            //cout << "СItConstructor: \t" << this << endl;
        }
        ~ConstIterator()
        {
            //cout << "СItDestructor: \t" << this << endl;
        }
        ConstIterator& operator ++ ()
        {
            BaseIterator::Temp = BaseIterator::Temp -> pNext;
            return *this;
        }
        ConstIterator operator ++ (int)
        {
            ConstIterator old = *this;
            BaseIterator::Temp = BaseIterator::Temp -> pNext;
            return old;
        }
        ConstIterator& operator -- ()
        {
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
            return *this;
        }
        ConstIterator operator -- (int)
        {
            ConstIterator old = *this;
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
            return old;
        }
    };
    class ConstReverseIterator : public BaseIterator
    {
    public:
        ConstReverseIterator(Element* Temp = nullptr) : BaseIterator(Temp)
        {
            //cout << "СRItConstructor: \t" << this << endl;
        }
        ConstReverseIterator& operator++()
        {
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
            return *this;
        }
        ConstReverseIterator operator++(int)
        {
            ConstReverseIterator old = *this;
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
            return old;
        }
        ConstReverseIterator& operator--()
        {
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
            return *this;
        }
        ConstReverseIterator operator--(int)
        {
            ConstReverseIterator old = *this;
            BaseIterator::Temp = BaseIterator::Temp -> pPrev;
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
        T& operator*()
        {
            return BaseIterator::Temp -> Data;
        }
    };
    class ReverseIterator: public ConstReverseIterator
    {
    public:
        ReverseIterator(Element* Temp = nullptr): ConstReverseIterator(Temp)
        {
            //cout << "RItConstructor:\t" << this << endl;
        }
        ~ReverseIterator()
        {
            //cout << "RItDestructor:\t" << this << endl;
        }
        T& operator*()
        {
            return BaseIterator::Temp -> Data;
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
    List(const initializer_list<T>& il) : List()
    {
        cout << typeid(il.begin()).name() << endl;
        for (T const* it = il.begin(); it != il.end(); ++it) {
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
    
    void push_front(T Data)
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
    
    void push_back(T Data)
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
    void insert(int index, T Data)
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
//#define RANGE_BASED_FOR_LIST

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
    List<int> list = { 3, 5, 8, 13, 21 };
    
    list.print();
    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    for (List<int>::ConstReverseIterator it = list.сrbegin(); it; ++it)
    {
        cout << *it << tab;
    }
    
#endif

//    List<double> d_list = {2.5, 3.14, 5.2, 8.3};
//
//    for (double i:d_list)
//    {
//        cout << i << tab;
//    }
//    cout << endl;
//
//    for(List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
//    {
//        cout << *it << tab;
//    }
//    cout << endl;
//    return 0;
    
    List <std::string> s_list = { "Have", " a", " nice", " day" };
    for (std::string i : s_list)
    {
        cout << i << tab;
    }
    cout << endl;
    
    for(List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
    {
        cout << *it << tab;
    }
    cout << endl;
}
