// OOPLab5True.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <algorithm>

template < typename  Key, typename  T, typename  Compare = std::less<Key>, typename  Allocator = std::allocator< std::pair<Key, T> > >
class assoc_array
{
public:
    class miterator
    {
        public:
            typedef miterator self_type;
            typedef std::pair<Key, T> value_type;
            typedef std::pair<Key, T>& reference;
            typedef std::pair<Key, T>* pointer;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef std::ptrdiff_t difference_type;
            miterator(pointer ptr) : ptr_(ptr) { };
            miterator() {};
            self_type operator=(const self_type& other) { ptr_ = other.ptr_; return *this; }
            self_type operator++() { ptr_++; return *this;  }
            self_type operator--() { ptr_--; return *this;  }
            self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
            self_type operator--(int junk) { self_type i = *this; ptr_--; return i; }
            reference operator*() { return *ptr_; }
            pointer operator->() { return ptr_; }
            bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
            bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
            pointer ptr_;
    };
    class mconst_iterator
    {
    public:
        typedef mconst_iterator self_type;
        typedef std::pair<Key, T> value_type;
        typedef std::pair<Key, T>& reference;
        typedef std::pair< Key, T>* pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        mconst_iterator(pointer ptr) : ptr_(ptr) { };
        mconst_iterator() {};
        self_type operator=(const self_type& other) { ptr_ = other.ptr_; return *this; }
        self_type operator++() { ptr_++; return *this; }
        self_type operator--() { ptr_--; return *this; }
        self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
        self_type operator--(int junk) { self_type i = *this; ptr_--; return i; }
        reference operator*() const{ return *ptr_; }
        pointer operator->() const{ return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        pointer ptr_;
        
    };

    typedef assoc_array<Key, T, Compare, Allocator> mymap;

    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef miterator iterator;
    typedef mconst_iterator const_iterator;
    typedef std::reverse_iterator<miterator> reverse_iterator;
    typedef std::reverse_iterator<mconst_iterator> const_reverse_iterator;





    assoc_array()
        : size(0), capacity(20), data(Allocator().allocate(20))
    {
    }

    assoc_array(const mymap& _Rhs)
        : size(_Rhs.size), capacity(_Rhs.size + 20), data(Allocator().allocate(_Rhs.size))
    {
        int count = 0;
        for (iterator i = &_Rhs.data[0]; i != &_Rhs.data[_Rhs.size]; ++i, ++count)
        {
            Allocator().construct(&data[count], *i);
        }
    }

    ~assoc_array()
    {
        if (!empty())
        {
            Allocator().deallocate(data, capacity);
        }
    }

    mymap& insert(const value_type& pair)
    {
        if (!is_present(pair))
        {
            if (++size >= capacity)
            {
                reserve(capacity * 2);
            }
            Allocator().construct(&data[size - 1], pair);
            return *this;
        }
    }

    bool is_present(const value_type& pair)
    {
        for (iterator i = begin(); i != end(); ++i)
        {
            if (i->first == pair.first)
            {
                return true;
            }
            return false;
        }
    }
    bool has_key(const key_type& _Key)
    {
        for (iterator i = begin(); i != end(); ++i)
        {
            if (i->first == _Key)
            {
                return true;
            }
        }
        return false;
    }

    mapped_type& operator[](const key_type& _Key)
    {
        if (has_key(_Key))
        {
            for (iterator i = begin(); i != end(); ++i)
            {
                if (i->first == _Key)
                {
                    return i->second;
                }
            }
        }
        size_type op = size;
        insert(value_type(_Key, mapped_type()));
        return data[op].second;
    }

    mymap& reserve(size_type _Capacity)
    {
        int count = 0;
        if (_Capacity < capacity)
        {
            return *this;
        }
        pointer buf = Allocator().allocate(_Capacity);
        for (iterator i = begin(); i != end(); ++i, ++count)
        {
            Allocator().construct(&buf[count], *i);
        }
        std::swap(data, buf);
        Allocator().deallocate(buf, capacity);
        capacity = _Capacity;
        return *this;
    }
    void erace(const key_type& Key)
    {
            int n = 0;
            for (iterator i = begin(); i != end(); ++i, n++)
            {
                if (i->first == Key)
                {
                    
                    std::move(++i, end(), i);
                    --size;
                    data[size].value_type::~value_type();
                    return;
                }
            }
    }
    size_type get_size() const { return get_size; }

    bool empty() const
    {
        return size == 0;
    }

    iterator begin()
    {
        return &data[0];
    }
    iterator end()
    {
        return &data[size];
    }

    reverse_iterator rbegin()
    {
        return &data[0];
    }
    reverse_iterator rend()
    {
        return &data[size];
    }
    const_iterator cbegin() const
    {
        return &data[0];
    }
    const_iterator cend() const
    {
        return &data[size];
    }
    const_reverse_iterator rbegin() const
    {
        return &data[0];
    }
    const_reverse_iterator rend() const
    {
        return &data[size];
    }

    iterator find(const key_type& Key)
    {
        for (iterator i = begin(); i != end(); ++i)
        {
            if (i->first == Key)
            {
                return i;
            }
        }
        iterator res = end();
        return res;
    }
private:
    pointer data;
    size_type size, capacity;
};
int main()
{

    assoc_array<std::string, int> map1;
    map1.insert({ "a", 30 });
    map1["b"] = 5;
    map1["c"] = 7;
    map1["aa"] = 22;
    map1["ba"] = 55;
    map1["ca"] = 77;
    std::cout << "Element <b> = " << map1["b"] << std::endl;
    auto result = map1.find("aa");
    std::inplace_merge(map1.cbegin(), map1.cbegin()++, map1.cend());
    if (result != map1.end())
    {
        std::cout<<"\nFound elem: " << "[" << result->first << "]" << "-->" << result->second << "\n\n";
    }
    else
    {
        std::cout << "\nCannot find elem\n\n";
    }
    for (assoc_array<std::string, int>::miterator i = map1.begin(); i != map1.end(); i++)
    {
        std::cout << "[" << i->first << "]" << "-->" << i->second << " ";
    }
    std::cout << std::endl;
    map1.erace("b");
    std::cout << "\nAfter arasing <b> pair\n" << std::endl;
    for (assoc_array<std::string, int>::miterator i = map1.begin(); i != map1.end(); i++)
    {
        std::cout << "[" << i->first << "]" << "-->" << i->second << " ";
    }
    std::cout << std::endl;
    system("pause");
}

