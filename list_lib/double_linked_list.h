#pragma once
#include <initializer_list>
#include <iterator>
#include <utility>

template <typename Type>
class DoubleLinkedList {
    // Узел списка
    struct Node {
        Node() = default;

        Node(Type val)
            : value{std::move(val)} {
        }

        Node(const Type& val, Node* node_next, Node* node_prev)
            : value(val)
            , next(node_next)
            , prev(node_prev) {
        }

        Type value;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class DoubleLinkedList;

        // Конвертирующий конструктор итератора из указателя на узел списка
        explicit BasicIterator(Node* node) {
            node_ = node;
        }

    public:
        // свойства итератора:
        // Категория итератора — bidirectional iterator
        using iterator_category = std::bidirectional_iterator_tag;
        // Тип элементов, по которым перемещается итератор
        using value_type = Type;
        // Тип, используемый для хранения смещения между итераторами
        using difference_type = std::ptrdiff_t;
        // Тип указателя на итерируемое значение
        using pointer = ValueType*;
        // Тип ссылки на итерируемое значение
        using reference = ValueType&;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept :
            node_(other.node_) {}

        BasicIterator& operator=(const BasicIterator& rhs) = default;

        bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return (node_ == rhs.node_);
        }

        bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            return !operator==(rhs);
        }

        bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return (node_ == rhs.node_);
        }

        bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return !operator==(rhs);
        }

        BasicIterator& operator++() noexcept {
            assert(node_ != nullptr);
            node_ = node_->next;
            return *this;
        }

        BasicIterator& operator--() noexcept {
            assert(node_ != nullptr);
            node_ = node_->prev;
            return *this;
        }

        BasicIterator operator++(int) noexcept {
            BasicIterator pastIter(this->node_);
            this->node_ = node_->next;
            return pastIter;
        }

        BasicIterator operator--(int) noexcept {
            BasicIterator pastIter(this->node_);
            this->node_ = node_->prev;
            return pastIter;
        }

        reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->value;
        }

        pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &(node_->value);
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    DoubleLinkedList() = default;

    DoubleLinkedList(std::initializer_list<Type> values) {
        for (auto& value : values) {
            PushBack(value);
        }
    }

    ~DoubleLinkedList() {
        Clear();
    }

    void Clear() noexcept {
        while (head_) {
            auto next = head_->next;
            delete head_;
            head_ = next;
            //delete std::exchange(head_, head_->next);
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void PushBack(Type value) {
        Node* node = new Node(std::move(value));
        if (tail_) {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        else {
            head_ = tail_ = node;
        }
        ++size_;
    }

    void PushFront(Type value) {
        auto node = new Node(std::move(value));
        if (head_) {
            head_->prev = node;
            node->next = head_;
            head_ = node;
        }
        else {
            head_ = tail_ = node;
        }
        ++size_;
    }

    void PopFront() noexcept {
        if (IsEmpty()) {
            return;
        }
        auto second_node = head_->next;
        delete head_;
        head_ = second_node;
        --size_;
    }

    Iterator Insert(ConstIterator pos, Type value) {
        if (pos == end()) {
            PushBack(std::move(value));
            return Iterator(end().node_);
        }
        if (pos == begin()) {
            PushFront(std::move(value));
            return Iterator(begin().node_);
        }
        Node* node = new Node(std::move(value));
        node->next = pos.node_;
        node->prev = pos.node_->prev;
        if (pos.node_->prev)
        {
            pos.node_->prev->next = node;
        }
        pos.node_->prev = node;
        ++size_;
        return Iterator(node);
    }

    void Erase(ConstIterator pos) noexcept {
        auto erase_node = pos.node_;
        if (erase_node->prev) {
            erase_node->prev->next = erase_node->next;
        }
        else {
            head_ = erase_node->next;
        }
        if (erase_node->next) {
            erase_node->next->prev = erase_node->prev;
        }
        else {
            tail_ = erase_node->prev;
        }
        delete erase_node;
        --size_;
    }

    bool IsEmpty() const noexcept {
        return (size_ > 0 ? false : true);
    }

    size_t GetSize() const noexcept {
        return size_;
    }

    Iterator begin() noexcept {
        return Iterator(head_);
    }

    Iterator end() noexcept {
        return Iterator(nullptr);
    }

    ConstIterator begin() const noexcept {
        return ConstIterator(head_);
    }

    ConstIterator end() const noexcept {
        return ConstIterator(nullptr);
    }

    ConstIterator cbegin() const noexcept {
        return ConstIterator(head_);
    }

    ConstIterator cend() const noexcept {
        return ConstIterator(nullptr);
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
};

template <typename Type>
bool operator==(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs.GetSize() != rhs.GetSize()) return false;
    if ((lhs.GetSize() == 0) && (rhs.GetSize() == 0)) return true;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
