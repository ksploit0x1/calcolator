#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QDebug>

template<typename T>
class HistoryNode {
public:
    T data;
    HistoryNode<T>* next;
    HistoryNode<T>* prev;
    HistoryNode(const T& value)
        : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
class History {
public:
    History();
    ~History();

    void add(const T& value);

    bool undo();

    bool redo();

    const T& getCurrent() const;

    void printHistory() const;
    void printCurrentState() const;
    void clear();

private:
    HistoryNode<T>* head;
    HistoryNode<T>* tail;
    HistoryNode<T>* current;

    void clearRedo();

};

#endif // HISTORY_H
