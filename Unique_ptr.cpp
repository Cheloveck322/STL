#include <iostream>
#include <memory>
#include <string>

template <typename T>
class MyUnique_ptr
{
public:
    explicit MyUnique_ptr(T* ptr = nullptr): m_ptr(ptr)
    {
        std::cout << "Unique created.\n";
    }
    ~MyUnique_ptr()
    {
        std::cout << "Unique destroyed.\n";
        delete m_ptr;
    }

    MyUnique_ptr(const MyUnique_ptr&) = delete;
    MyUnique_ptr& operator=(const MyUnique_ptr&) = delete;

    MyUnique_ptr(MyUnique_ptr&& other) noexcept : m_ptr(other.m_ptr)
    {
        std::cout << "Unique created.\n";
        other.m_ptr = nullptr;
    }
    MyUnique_ptr* operator=(MyUnique_ptr&& other) noexcept
    {
        if (this != &other)
        {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T* get() const 
    {
        return m_ptr; 
    }

    T* release() noexcept
    {
        if (m_ptr)
            return get();
        return nullptr;
    }

    T& operator*() const noexcept
    {
        return *get();
    }

    T* operator->() const noexcept
    {
        return get();
    }

private:
    T* m_ptr;
};

struct Resource
{
    int m_a{ 0 };
    Resource(int a): m_a(a) { std::cout << "Object created.\n"; }
    ~Resource() { std::cout << "Object destroyed.\n"; }

    std::string Foo() { return "Foo()"; }
};

int main()
{
    Resource* r = new Resource(2);
    MyUnique_ptr<Resource> p1(r);
    MyUnique_ptr<Resource> p2 = std::move(p1);
    std::cout << p2->Foo() << '\n';
    std::cout << p1->Foo() << '\n';
    std::cout << p1.get() << '\n';
    return 0;
}