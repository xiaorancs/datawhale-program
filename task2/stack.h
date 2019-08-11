/**
 * File: stack.h
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#ifndef DATAWHALE_STACK_H
#define DATAWHALE_STACK_H

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

namespace datawhale {
typedef size_t uint32_t;

template<class T, uint32_t dw_size = 1024>
class Stack {
public:
    Stack(uint32_t _capacity = dw_size) {
        this->len = 0;
        this->capacity = _capacity;
        this->data = new T[_capacity];
    }
    ~Stack() {
        this->len = 0;
        this->capacity = 0;
        delete [] this->data;
    }

    bool empty() {
        return this->len == 0;
    }

    void pop() {
        assert(len > 0);
        len --;
    }

    const T& top() const {
        assert(len > 0);
        return data[len - 1];
    }

    void push(const T& value) {
        if (len == capacity) {
            capacity <<= 1;
            T* new_data = new T[capacity];
            memcpy(new_data, data, len);
            delete [] data;
            data = new_data;
        }
        data[len ++] = value;
    }

    uint32_t size() {
        return len;
    }

    // 0表示栈顶元素
    const T& operator[] (uint32_t index) const {
        assert(index < len);
        return data[len - 1 - index];
    }

    Stack(const Stack& other) {
        data = other.data;
        len = other.len;
        capacity = other.capacity;
        data = new T[capacity];
        memcpy(data, other.data, capacity);
    }
                            
    Stack& operator=(const Stack& other) {
        data = other.data;
        len = other.len;
        capacity = other.capacity;
        data = new T[capacity];
        memcpy(data, other->data, capacity);
    }

private:
    uint32_t len;
    uint32_t capacity;
    T* data;
}; // class stack

} // namespace datawhale

#endif // DATAWHALE_STACK_H
