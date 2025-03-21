#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T = int>
class MyVector
{
public:
    using iterator = T*;
    using citerator = const T*;

    using riterator = std::reverse_iterator<iterator>;
    using criterator = std::reverse_iterator<citerator>;

    MyVector(): m_arr{ nullptr }, m_size{ 0 }, m_capacity{ 0 }
    {
    }

    MyVector(int x): m_arr{ nullptr }, m_size{ x }, m_capacity{ x }
    {
        if (x < 0)
        {
            throw std::invalid_argument("Size of vector can not be negative.\n");
        }
        m_arr = new T[m_size];
    }

    MyVector(std::initializer_list<T> list)
        : m_arr(nullptr), m_size(list.size()), m_capacity(list.size())
    {
        m_arr = new T[m_capacity];
        size_t i{};
        
        for (T element : list)
        {
            m_arr[i++] = element;
        }
    }

    MyVector(const MyVector& arr): m_arr(new T[arr.capacity()]), m_size(arr.size()), m_capacity(arr.capacity())
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            m_arr[i] = arr[i];
        }
    }

    iterator begin() noexcept
    {
        return m_arr;
    }

    iterator end() noexcept
    {
        return m_arr + m_size;
    }

    citerator cbegin() noexcept
    {
        return m_arr;
    }

    citerator cend() noexcept
    {
        return m_arr + m_size;
    }

    riterator rbegin() noexcept
    {
        return std::reverse_iterator(end());
    }

    riterator rend() noexcept
    {
        return std::reverse_iterator(begin());
    }

    criterator crbegin() noexcept
    {
        return std::reverse_iterator(cend());
    }

    criterator crend() noexcept
    {
        return std::reverse_iterator(cbegin());
    }

    void push_back(const T& value)
    {
        if (m_size >= m_capacity)
        {
            m_capacity *= 2;
            T* new_arr = new T[m_capacity];

            for (size_t i{}; i < m_size; ++i)
            {
                new_arr[i] = m_arr[i]; 
            }

            delete[] m_arr;
            m_arr = new_arr;
            new_arr = nullptr;
        }
        m_arr[m_size++] = value;
    }

    void pop_back()
    {
        if (m_size < 1)
        {
            throw std::out_of_range("The array is empty.\n");
        }
        --m_size;
    }

    constexpr size_t size() const
    {
        return m_size;
    }

    constexpr size_t capacity() const
    {
        return m_capacity;
    }

    T& operator[](int index)
    {
        if (index < 0 || index > m_size - 1)
        {
            throw std::out_of_range("You went out.\n");
        }

        return m_arr[index];
    }

    const T& operator[](int index) const
    {
        if (index < 0 || index > m_size - 1)
        {
            throw std::out_of_range("You went out.\n");
        }

        return m_arr[index];
    }

    bool operator==(const MyVector& vect)
    {
        bool flag{ true };

        if (m_size != vect.size())
        {
            flag = false;
        }
        else
        {
            for (size_t i{}; i < vect.size(); ++i)
            {
                if (m_arr[i] != vect[i])
                {
                    flag = false;
                }
            }
        }

        return flag;
    }

    void operator=(const MyVector& arr)
    {
        if (m_capacity < arr.size())
        {
            if (m_arr != nullptr)
                delete[] m_arr;
            m_arr = new T[arr.capacity()];
        }

        m_size = arr.size();
        m_capacity = arr.capacity();

        for (size_t i{}; i < m_size; ++i)
        {
            m_arr[i] = arr[i];
        }
    }

    void print() const
    {
        for (size_t i{}; i < m_size; ++i)
        {
            std::cout << m_arr[i] << ' ';
        }
        std::cout << '\n';
    }

    ~MyVector()
    {
        delete[] m_arr;
    }

private:
    T* m_arr;
    size_t m_size{};
    size_t m_capacity{};
};

int main()
{
    MyVector zero{ 1, 2 };

    zero.print();
    
    for (int i{}; i < 10; ++i)
    {
        zero.push_back(i+1);
        zero.print();
    }

    MyVector one { zero };
    one.print();


    return 0;
}