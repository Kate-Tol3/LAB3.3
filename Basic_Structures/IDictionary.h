
#ifndef IDICTIONARY_H
#define IDICTIONARY_H

template <typename TKey, typename TElement>
class IDictionary {
public:
    virtual ~IDictionary() = default;

    // Атрибуты
    virtual int getCount() const = 0;
    virtual int getCapacity() const = 0;

    // Методы
    virtual TElement get(const TKey& key) const = 0;
    virtual bool containsKey(const TKey& key) const = 0;
    virtual void insert(const TKey& key, const TElement& element) = 0;
    virtual void remove(const TKey& key) = 0;
    virtual void set(const TKey& key, const TElement& element) = 0;
    virtual void clear() = 0;

};


#endif //IDICTIONARY_H
