#include <functional>

template <typename T>
class make_pair_enumerator {
    typename T::iterator m_cursor,m_end;
public:
    make_pair_enumerator(T &t)
        : m_cursor(t.begin()) , m_end(t.end()) {}
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
