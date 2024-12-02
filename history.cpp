#include "history.h"


template<typename T>
History<T>::History()
    : head(nullptr), tail(nullptr), current(nullptr) {}


template<typename T>
History<T>::~History() {
    clear();
}


template<typename T>
void History<T>::add(const T& value) {
    HistoryNode<T>* newNode = new HistoryNode<T>(value);

    if (current != nullptr && current != tail) {
        clearRedo();
    }

    if (tail == nullptr) {
        head = tail = current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        current = tail;
    }
}


template<typename T>
bool History<T>::undo() {
    if (current && current->prev) {
        current = current->prev;
        return true;
    }
    return false;
}


template<typename T>
bool History<T>::redo() {
    if (current && current->next) {
        current = current->next;
        return true;
    }
    return false;
}


template<typename T>
const T& History<T>::getCurrent() const {
    if (current) {
        return current->data;
    }
    throw std::runtime_error("No current operation");
}


template<typename T>
void History<T>::printHistory() const {
    HistoryNode<T>* node = head;
    while (node) {
        qDebug() << node->data;
        node = node->next;
    }
}


template<typename T>
void History<T>::printCurrentState() const {
    if (current) {
        qDebug() << "Current operation:" << current->data;
    } else {
        qDebug() << "No current operation.";
    }
}


template<typename T>
void History<T>::clearRedo() {
    if (current) {
        HistoryNode<T>* node = current->next;
        while (node) {
            HistoryNode<T>* nextNode = node->next;
            node = nextNode;
        }
        tail = current;
    }
}


template<typename T>
void History<T>::clear() {
    HistoryNode<T>* currentNode = head;
    while (currentNode) {
        HistoryNode<T>* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = tail = current = nullptr;
}

template class History<QString>;
