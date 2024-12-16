#pragma once

template <typename T>
class UnqPtr {
private:
    T* u_ptr;

public:

    explicit UnqPtr(T* p = nullptr) : u_ptr(p) {}

    ~UnqPtr() {
        delete u_ptr;
    }

    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // Move constructor
    UnqPtr(UnqPtr&& other) noexcept : u_ptr(other.u_ptr) {
        other.u_ptr = nullptr;
    }

    // Move assignment operator
    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete u_ptr;
            u_ptr = other.u_ptr;
            other.u_ptr = nullptr;
        }
        return *this;
    }


    T& operator*() {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return *u_ptr;
    }
    T* operator->() {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return u_ptr;
    }

    const T& operator*() const {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return *u_ptr;
    }
    const T* operator->() const {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return u_ptr;
    }

    const bool isNull() const { return u_ptr == nullptr; }
    bool isNull() {return u_ptr == nullptr; }


    const T* get() const {
        return u_ptr;
    }
    T* get() {
        return u_ptr;
    }


    T* release() {
        T* temp = u_ptr;
        u_ptr = nullptr;
        return temp;
    }

    void reset(T* other = nullptr) {
        delete u_ptr;
        u_ptr = other;
    }

    void swap(UnqPtr& other) noexcept{
        T* temp = u_ptr;
        u_ptr = other.u_ptr;
        other.u_ptr = temp;
    }
};

// Специализация для массивов
template <typename T>
class UnqPtr<T[]> {
private:
    T* ptr;

public:

    UnqPtr() : ptr(nullptr) {}

    explicit UnqPtr(T* p) : ptr(p) {}

    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    UnqPtr(UnqPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~UnqPtr() {
        delete[] ptr;
    }

    T& operator[](size_t index) {
        if(ptr == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return ptr[index];
    }

    const T& operator[](size_t index) const {
        if(ptr == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return ptr[index];
    }

    explicit operator bool() const { return ptr != nullptr; }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        delete[] ptr;
        ptr = p;
    }

    void swap(UnqPtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }

    const T* get() const { return ptr;}

    T* get() { return ptr;}
};


