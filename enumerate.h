#include <functional>

template <typename T>
class make_enumerator {
    typename T::iterator m_cursor,m_end;
public:
    make_enumerator(T &t)
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
using enumerator = const std::function<bool(T&)>;
