#include <functional>

template <typename T>
class pair_enumerator_impl {
    typename T::iterator m_cursor,m_end;
public:
    pair_enumerator_impl(typename T::iterator begin,typename T::iterator end)
        : m_cursor(begin) , m_end(end) {}
    bool operator() (typename T::key_type    &first,
                     typename T::mapped_type &second) {
        if( m_cursor == m_end ){
            return false;
        }
        first = m_cursor->first;
        second = m_cursor->second;
        m_cursor++;
        return true;
    };
};

template <typename Key,typename Mapped>
using pair_enumerator = const std::function<bool(Key&,Mapped&)>;

template <typename T>
pair_enumerator_impl<T> make_pair_enumerator(T &collection)
{
    return pair_enumerator_impl<T>(collection.begin(), collection.end());
}
