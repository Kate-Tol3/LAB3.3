template <typename T>
class Stack {
private:
    struct stackNode {
        T data;
        stackNode* next;
        explicit stackNode(const T& data) : data(data), next(nullptr) {}
    };

    stackNode* top;  // Указатель на верхний элемент стека
    int size;   // Количество элементов в стеке

public:
    // Конструктор
    Stack() : top(nullptr), size(0) {}

    // Деструктор для освобождения памяти
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Конструктор копирования
    Stack(const Stack& other) : top(nullptr), size(0) {
        stackNode* current = other.top;
        Stack<T> tempStack;  // Временный стек для инверсии элементов

        // Копирование всех элементов в временный стек
        while (current) {
            tempStack.push(current->data);
            current = current->next;
        }

        // Перенос элементов из временного стека в текущий
        while (!tempStack.isEmpty()) {
            push(tempStack.peek());
            tempStack.pop();
        }
    }

    // Оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {  // Самоприсваивание
            // Освобождаем текущую память
            while (!isEmpty()) {
                pop();
            }

            // Копируем элементы из другого стека
            stackNode* current = other.top;
            Stack<T> tempStack;

            while (current) {
                tempStack.push(current->data);
                current = current->next;
            }

            // Переносим элементы из временного стека
            while (!tempStack.isEmpty()) {
                push(tempStack.peek());
                tempStack.pop();
            }
        }
        return *this;
    }

    // Проверка, пуст ли стек
    bool isEmpty() const {
        return size == 0;
    }

    // Добавление элемента в стек
    void push(const T& value) {
        stackNode* newstackNode = new stackNode(value);
        newstackNode->next = top;
        top = newstackNode;
        ++size;
    }

    // Удаление элемента из стека
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        stackNode* temp = top;
        top = top->next;
        delete temp;
        --size;
    }

    // Получение верхнего элемента
    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top->data;
    }

    // Получение размера стека
    int getSize() const {
        return size;
    }

    // Оператор сравнения для стеков
    bool operator==(const Stack<T>& other) const {
        if (size != other.size) {
            return false;
        }

        stackNode* current = top;
        stackNode* otherCurrent = other.top;

        while (current) {
            if (current->data != otherCurrent->data) {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        return true;
    }

    // Оператор неравенства для стеков
    bool operator!=(const Stack<T>& other) const {
        return !(*this == other);
    }
};
