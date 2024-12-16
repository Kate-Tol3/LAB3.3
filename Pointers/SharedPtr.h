#pragma once

#include <stdexcept>

template <typename T>
struct ControlBlock {
    T* s_ptr;
    int ref_count;// счётчик сильных ссылок
    int weak_count;// счётчик слабых ссылок
    bool is_array;

    ControlBlock(T* ptr = nullptr, bool isArray = false)
        : s_ptr(ptr), ref_count(1), weak_count(0), is_array(isArray) {}

   //уничтожаеи объект, а не сам блок
    void deleteObject() {
        if (is_array) {
            delete[] s_ptr;
        } else {
            delete s_ptr;
        }
        s_ptr = nullptr;
    }
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
private:
    ControlBlock<T>* control_block;

public:
    // конструктор для одиночных объектов
    explicit SharedPtr(T* p = nullptr)
        : control_block(p ? new ControlBlock<T>(p, false) : nullptr) {}

    // конструктор для массивов
    explicit SharedPtr(T* p, bool isArray)
        : control_block(p ? new ControlBlock<T>(p, isArray) : nullptr) {}

    // Copy constructor
    SharedPtr(const SharedPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->ref_count);
        }
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    // Construct from a WeakPtr
    SharedPtr(const WeakPtr<T>& weak) : control_block(weak.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    ~SharedPtr() {
        release();
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                ++(control_block->ref_count);
            }
        }
        return *this;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            control_block = other.control_block;
            other.control_block = nullptr;
        }
        return *this;
    }

    void release() {
        if (control_block) {
            if (--control_block->ref_count == 0) {
                control_block->deleteObject();  // Delete the managed object or array
                if (control_block->weak_count == 0) {
                    delete control_block;  // Delete the control block if no weak references exist
                }
            }
            control_block = nullptr;
        }
    }

    // доступ к объекту для не-массивов
    const T& operator*() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }
    T& operator*() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }

    // доступ по указателю для всех обектов
    const T* operator->() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }
    T* operator->() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }

    // subscript operator только для массивов
    T& operator[](size_t index) {
        if (!control_block || !control_block->is_array) {
            throw std::out_of_range("Not managing an array.\n");
        }
        return control_block->s_ptr[index];
    }

    // Get the raw pointer
    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    const int useCount() const { return control_block ? control_block->ref_count : 0; }
    int useCount() { return control_block ? control_block->ref_count : 0; }

    const bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }
    bool isNull() { return control_block == nullptr || control_block->s_ptr == nullptr; }

    void swap(SharedPtr& other) noexcept {
        std::swap(control_block, other.control_block);
    }

    const bool expired() const {
        return !control_block || control_block->ref_count == 0;
    }

    const bool unique() const {
        return control_block && control_block->ref_count == 1;
    }

    friend class WeakPtr<T>;
};