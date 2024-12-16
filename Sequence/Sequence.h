
#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class T>
class Sequence {
public:
    //destructor
    virtual ~Sequence() = default;

    //methods
    virtual const T& getFirst() const = 0;
    virtual const T& getLast() const = 0;

    virtual const T& get(int index) const = 0;
    virtual int getLength() const = 0;

    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* concat(const Sequence<T>& secondSequence) const = 0;
    virtual void print() const = 0;
    virtual const T& operator[](int index) const = 0;
    virtual T& operator[](int index) = 0;
    virtual void set(int index,const T& item) = 0;
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insertAt(const T& item, int index) = 0;

};

#endif //SEQUENCE_H
