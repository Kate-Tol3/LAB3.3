
#ifndef RANGE_H
#define RANGE_H
#include <sstream>


template <typename T, typename Comparator = std::less_equal<T>>
class Range {
public:
    T start;
    T end;
    Comparator comp;

    Range(T start, T end, Comparator comp = Comparator()) : start(start), end(end), comp(comp) {
        if (start >= end) {
            throw std::invalid_argument("Start must be less than end in a range.");
        }
    }
    Range(): start(T()), end(T()) {}

    // Проверка, входит ли значение в диапазон
    bool contains(const T& value) const {
        return comp(start, value) && comp(value, end);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "[" << start << ", " << end << "]";
        return oss.str();
    }

    bool operator==(const Range& other) const {
        return start == other.start && end == other.end;
    }

    bool operator<(const Range<T, Comparator>& other) const {
        return start < other.start || (start == other.start && end < other.end);
    }

};






#endif //RANGE_H
