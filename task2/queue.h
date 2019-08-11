/**
 * File: queue.h
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#ifndef DATAWHALE_QUEUE_H
#define DATAWHALE_QUEUE_H

#include <memory.h>
#include <stdlib.h>
#include <assert.h>


namespace datawhale {
typedef size_t uint32_t;

template<class T, uint32_t dw_size = 1024>
class Queue {
public:
    Queue(uint32_t _capacity = dw_size) {
        this->len = 0;
        this->capacity = _capacity;
        this->data = new T[_capacity];
        this->iback = 0;
        this->ifront = 0;
    }

    ~Queue() {
        this->len = 0;
        this->capacity = 0;
        this->iback = 0;
        this->ifront = 0;
        delete [] this->data;
    }

    /**
     * 是否为空
     */
    bool empty() {
        return this->len == 0;
    }

    /**
     * 长度
     */
    uint32_t size() const {
        return len;
    } 

    /**
     * 返回队首元素
     */
    const T& front() const {
        assert(len != 0);
        return data[ifront];
    } 

    /**
     * 返回队尾元素
     */
    const T& back() const {
        assert(len != 0);
        return data[iback - 1];
    }

    /**
     * 入队
     */
    void push(const T& value) {
        if ((iback + 1) % capacity == ifront) { // 循环队列已满，浪费一个空间保证队满判断, 
                                                // 新循环队列复制, 所有从头开始
            uint32_t x_capacity = capacity << 1;
            T* new_data = new T[x_capacity];
            for (int i = ifront; i % capacity != iback; i ++) {
                new_data[i - ifront] = data[i % capacity];
            }
            ifront = 0;
            iback = len;
            capacity = x_capacity;
            delete [] data;
            this->data = new_data;
        }
        data[iback % capacity] = value;
        iback ++;
        len ++;
    }

    /**
     * 入队
     */
    void push_back(const T& value) {
        push(value);
    }

    /**
     * 删除队首
     */
    void pop_front() {
        assert(len != 0);
        ++ ifront;
        len --;
    }

    /**
     * 删除队尾
     */
    void pop_back() {
        assert(len != 0);
        -- iback;
        len --;
    }

    /**
     * 出队
     */
    void pop() {
        pop_front();
    }
    
    Queue(const Queue& other) { 
        len = other.len;
        capacity = other.capacity;
        ifront = other.ifront;
        iback = other.iback;
        data = new T[capacity];
        memcpy(data, other->data, capacity);
    }
                            
    Queue& operator=(const Queue& other) {
        len = other.len;
        capacity = other.capacity;
        ifront = other.ifront;
        iback = other.iback;
        data = new T[capacity];
        memcpy(data, other->data, capacity);    
    }
private:
    uint32_t len;
    uint32_t capacity;
    T* data;
    uint32_t ifront;
    uint32_t iback;

}; // Queue

} // namespace datawhale

#endif // DATAWHALE_QUEUE_H