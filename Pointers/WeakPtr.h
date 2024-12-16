#pragma once

#include "SharedPtr.h"
#include <stdexcept>

template <typename T>
class WeakPtr {
private:
    ControlBlock<T>* control_block;

public:

    WeakPtr() : control_block(nullptr) {}

    // Constructor from SharedPtr
    WeakPtr(const SharedPtr<T>& shared_ptr) : control_block(shared_ptr.control_block) {
        if (control_block) {
            ++(control_block->weak_count);
        }
    }

    // Copy constructor
    WeakPtr(const WeakPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->weak_count);
        }
    }

    // Move constructor
    WeakPtr(WeakPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    // Destructor
    ~WeakPtr() {
        release();
    }

    // Copy assignment
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                ++(control_block->weak_count);
            }
        }
        return *this;
    }

    // Move assignment
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            control_block = other.control_block;
            other.control_block = nullptr;
        }
        return *this;
    }

    // Resource release
    void release() {
        if (control_block) {
            if (--control_block->weak_count == 0 && control_block->ref_count == 0) {
                delete control_block;  // Delete the control block if no strong or weak references exist
            }
            control_block = nullptr;
        }
    }

    // Check if the object is still available
    const bool expired() const {
        return !control_block || control_block->ref_count == 0;
    }

    // Convert to SharedPtr
    SharedPtr<T> lock() {
        if (!expired()) {
            return SharedPtr<T>(*this);
        }
        return SharedPtr<T>(nullptr);
    }

    const SharedPtr<T> lock() const {
        if (!expired()) {
            return SharedPtr<T>(*this);
        }
        return SharedPtr<T>(nullptr);
    }

    void swap(WeakPtr& other) noexcept {
        std::swap(control_block, other.control_block);
    }

    const int useCount() const { return control_block ? control_block->weak_count : 0; }
    int useCount() { return control_block ? control_block->weak_count : 0; }

    const bool isNull() const { return !control_block || control_block->s_ptr == nullptr; }
    bool isNull() { return !control_block || control_block->s_ptr == nullptr; }

    // Access the object (for non-arrays)
    const T& operator*() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }
    T& operator*() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return *control_block->s_ptr;
    }

    // Access the object or array element via pointer (for arrays)
    const T* operator->() const {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }
    T* operator->() {
        if (expired()) throw std::out_of_range("The pointer has expired.\n");
        return control_block->s_ptr;
    }

    // Get the raw pointer
    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    // Check if the WeakPtr is the only one managing the resource
    const bool unique() const {
        return control_block && control_block->weak_count == 1;
    }
    bool unique() {
        return control_block && control_block->weak_count == 1;
    }

    friend class SharedPtr<T>;
};
