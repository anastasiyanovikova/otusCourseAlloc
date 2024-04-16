#pragma once
#include <iostream>
#include <map>
#include <memory>

unsigned long long getFuctorial(unsigned int n);

struct deleter
{
    void operator()(void * ptr)
    {
        ::operator delete(ptr);
    }
};

// Allocator
template <class T>
struct MyAllocator
{
    using value_type = T;
    std::shared_ptr<void> pool;
    static constexpr std::size_t PoolSize = 1000;
    std::size_t used_buf = 0;

    MyAllocator() noexcept: pool(::operator new(sizeof(T)*PoolSize), deleter()){
    }

    template <class U>
    MyAllocator(const MyAllocator<U>& other) noexcept{
        pool = other.pool;
    }

    MyAllocator select_on_container_copy_construction() const{
        return MyAllocator();
    }

    T* allocate(std::size_t objects){        
        if(used_buf + objects > PoolSize)
            throw std::bad_alloc();

        if(nullptr == pool)
            throw std::bad_alloc();

        auto result = reinterpret_cast<T*>(pool.get()) + used_buf*sizeof(T);
        used_buf += objects;
        return result;
    }
    void deallocate(T* ptr, std::size_t objects){
        if(nullptr == ptr)
            return;
        used_buf -= objects;
    }
    template <class U>
    struct rebind
    {
        typedef MyAllocator<U> other;
    };
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

};

template <class T, class U>
constexpr bool operator==(const MyAllocator<T>& a1, const MyAllocator<U>& a2){
    return a1.pool == a2.pool;
}
template <class T, class U>
bool operator!=(const MyAllocator<T>& a1, const MyAllocator<U>& a2){
    return a1.pool != a2.pool;
}

template <class T, class Allocator = std::allocator<T> >
class MyVector{
public:
    ~MyVector()
    {
        m_alloc.deallocate(m_data, m_capacity);
    }
    void push_back(const T& a_value)
    {
        if(m_size >= m_capacity)
            addMemory();
        m_data[m_size] = a_value;
        ++m_size;
    }
    std::size_t size() const
    {
        return m_size;
    }
    std::size_t capacity() const
    {
        return m_capacity;
    }
    T& operator[](std::size_t i)
    {
        if(i >= m_size)
            throw std::out_of_range("i >= size");
        T& value = *static_cast<T*>(m_data + i);
        return value;
    }

    const T& operator[](std::size_t i) const
    {
        if(i >= m_size)
            throw std::out_of_range("i >= size");
        const T& value = *static_cast<T*>(m_data + i);
        return value;
    }

private:
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
    T* m_data = nullptr;
    Allocator m_alloc;

    void addMemory()
    {
        auto prevCapacity = m_capacity;
        if(m_capacity == 0)
            m_capacity = 2;
        else
            m_capacity = m_capacity * 2;

        T* new_data = m_alloc.allocate(m_capacity);
        for(std::size_t i = 0; i < m_size; ++i)
            new_data[i] = m_data[i];

        if(m_data)
            m_alloc.deallocate(m_data, prevCapacity);
        m_data = new_data;
    }
};