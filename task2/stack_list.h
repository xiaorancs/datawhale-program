/**
 * File: stack_list.h
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#ifndef DATAWHALE_STACK_LIST_H
#define DATAWHALE_STACK_LIST_H

#include <assert.h>
#include <stdlib.h>

namespace datawhale {

template<class T>
struct ListNode {
    ListNode* prev;
    ListNode* next;
    T value;
    ListNode() {}
    ListNode(T _value) : value(_value) {
        prev = NULL;
        next = NULL;
    }
};

template<class T>
class StackList {
public:
    StackList() {
        this->head = new ListNode<T>(); // 第一个指针不存储数据
        this->back = head;
        this->len = 0;
    }

    ~StackList() {
        ListNode<T>* tt = this->head;
        while (tt != back) {
            ListNode<T>* tmp = tt->next;
            delete tt;
            tt = tmp;
        }
        this->head = NULL;
        this->back = NULL;
        this->len = 0;
    }

    bool empty() {
        return this->len == 0;
    }

    void pop() {
        assert(len > 0);
        len --;
        ListNode<T>* tmp = back;
        back = back->prev;
        delete tmp;
    }

    const T& top() const {
        assert(len > 0 && back != NULL);
        return back->value;
    }

    void push(const T& value) {
        ListNode<T>* new_node = new ListNode<T>(value);
        back->next = new_node;
        new_node->prev = back;
        back = new_node;
        len ++;
    }

    size_t size() {
        return len;
    }

    StackList(const StackList& other) {
        head = new ListNode<T>();
        back = head;

        ListNode<T>* t_head = other.head;
        while (t_head->next != NULL) {
            ListNode<T>* tmp = new ListNode<T>(t_head->next->value);
            this->back->next = tmp;
            this->back = tmp;
            t_head = t_head->next;
        }
        len = other.len;
    }
                            
    StackList& operator=(const StackList& other) {
        Stack(other);
    }

private:
    ListNode<T>* head;
    ListNode<T>* back;
    size_t len;

}; // Stack

} // namespace datawhale

#endif // DATAWHALE_STACK_LIST_H