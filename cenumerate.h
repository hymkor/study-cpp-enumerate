#include <functional>

template <typename T>
class make_const_enumerator {
    typename T::const_iterator m_cursor,m_end;
public:
    make_const_enumerator(const T &t)
        : m_cursor(t.begin()) , m_end(t.end()) {}
    bool operator() (typename T::value_type &store) {
        if( m_cursor == m_end ){
            return false;
        }
        store = *m_cursor;
        m_cursor++;
        return true;
    };
};

template <typename T>
using enumerator = std::function<bool(T&)>;
