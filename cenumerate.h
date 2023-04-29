#include <functional>

template <typename T>
class const_enumerator_impl {
    typename T::const_iterator m_cursor,m_end;
public:
    const_enumerator_impl(typename T::const_iterator begin,typename T::const_iterator end)
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
const_enumerator_impl<T> make_const_enumerator(const T &collection)
{
    return const_enumerator_impl<T>(collection.cbegin(), collection.cend());
}
