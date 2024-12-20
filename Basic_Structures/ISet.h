#ifndef ISET_H
#define ISET_H


template <typename T>
class ISet {
public:
    virtual ~ISet() = default;

    virtual void insert(const T& element) = 0;
    virtual void erase(const T& element) = 0;
    virtual bool contains(const T& element) const = 0; //find
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;

    // Математические операции
    virtual ISet<T>* setUnion(ISet<T>& s) = 0;  // Объединение
    virtual ISet<T>* intersect(ISet<T>& s) = 0;  // Пересечение
    virtual ISet<T>* subtract(ISet<T>& s) = 0;  // Разность
    virtual bool isSubset(const ISet<T>& set) const = 0;  // Подмножество
    virtual bool isEqual(const ISet<T>& set) const = 0;  // Равенство
    virtual bool operator==(const ISet<T>& set) const = 0;

};

#endif //ISET_H
