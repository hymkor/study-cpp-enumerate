#include <functional>

template <typename T>
class enumerator_maker {
    typename T::iterator m_cursor,m_end;
public:
    enumerator_maker(typename T::iterator begin,typename T::iterator end)
        : m_cursor(begin) , m_end(end) {}
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

template <typename T>
enumerator_maker<T> make_enumerator(T &collection)
{
    return enumerator_maker<T>(collection.begin(), collection.end());
}
