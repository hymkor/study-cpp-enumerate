std::vector / std::set 両方からデータを取れる関数の本体をあまりテンプレートにしたくない
=============

現状こういうことはできない
------------------------

[main0.cpp](./main0.cpp)

```main0.cpp
#include <string>
#include <vector>
#include <set>
#include <list>

template<class T> void put(T cursor,T end);

int main(){
    std::vector<std::string> v;
    v.push_back( "a" );
    v.push_back( "b" );
    v.push_back( "c" );

    put( v.begin() , v.end() );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( s.begin() , s.end() );
}
```

[sub0.cpp](./sub0.cpp)

```sub0.cpp
#include <iostream>

template<class T> void put(T cursor,T end)
{
    for( ; cursor != end ; cursor++ ){
        std::cout << *cursor << std::endl;
    }
}
```

これをビルドするとリンクエラーになるので、関数 put をヘッダファイルに置くか、sub0.cpp 側ですべての想定される T の型に対して実体化しておかなくていけない[^externtemplate]

[^externtemplate]: externtemplate というものを使う。例：[main0_.cpp](https://github.com/hymkor/study-cpp-enumerate/blob/master/main0_.cpp),  [sub0_.cpp](https://github.com/hymkor/study-cpp-enumerate/blob/master/sub0_.cpp) ; 参考文献：[[C++11] extern templateの機能とその使い道 - Qiita](https://qiita.com/Kogia_sima/items/b7a1e23a78f81d913089)

put が巨大な関数の場合、前者はビルドが遅くなるし、後者のようなものはきちんとメンテしないと使わない無駄な実体が発生してしまう。

うまいことソースを分割したまま、任意のコンテナの要素を列挙できる仕組みは作れないか

過去のトライ
-----------

+ [std::vector / std::set 両方からデータを取れる関数をあまりテンプレートにしたくない - 標準愚痴出力](https://zetamatta.hatenablog.com/entry/2019/09/22/080313)
+ [(続) std::vector / std::set 両方からデータを取れる関数をあまりテンプレートにしたくない - 標準愚痴出力](https://zetamatta.hatenablog.com/entry/2019/09/22/131156)
+ [(続々) std::vector / std::set 両方からデータを取れる関数をあまりテンプレートにしたくない - 標準愚痴出力](https://zetamatta.hatenablog.com/entry/2019/09/22/163822)

最新成果
--------

### 利用例

#### 関数側 ([sub.cpp](./sub.cpp))

```sub.cpp
#include <string>
#include <iostream>
#include "enumerate.h"

void put(enumerator<std::string> &each)
{
    std::string value;
    while( each(value) ){
        std::cout << value << std::endl;
    }
}
```

+ `sub.cpp` 側では、`<vector>` も `<set>` も include していない
  ( ただし、`"enumerate.h"` の中で `<functional.h>` だけは include している。詳しくは後述 )
+ `std::vector` や `std::set` などのコレクションを引き受ける引数の型は `enumerator<T>` という型にしておく.

#### 呼び出し側 ([main.cpp](./main.cpp))

```main.cpp
#include <string>
#include <vector>
#include <set>
#include <list>
#include "enumerate.h"

extern void put(enumerator<std::string> &each);

int main(void)
{
    std::vector<std::string> v;
    v.push_back( "a" );
    v.push_back( "b" );
    v.push_back( "c" );

    put( make_enumerator(v) );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( make_enumerator(s) );

    std::list<std::string> ls;
    ls.push_back( "x" );
    ls.push_back( "y" );
    ls.push_back( "z" );

    put( make_enumerator(ls) );
}
```

+ 呼び出す際は、`std::vector<T>` や `std::set<T>` を `make_enumerator` という関数で、`enumerator<T>` へ変換して、`put` へ引き渡す.

#### 出力

``` ./main |
a
b
c
1
2
3
x
y
z
```

### 実装 ([enumerate.h](./enumerate.h))

+ `make_enumerator<T>` という型は `bool operator()(bool(T&))` というメソッドを持っており、関数の体裁で呼び出すことができる
+ つまり、関数オブジェクトであるから、 `std::function<bool(T&)>` へ変換することができる。
+ ゆえに関数側のパラメータは `std::set` や `std::vector` などの型に固定しなくてよくなる。

+ この二つの組み合わせだけでも利用可能であるが、見かけの体裁を読みやすくするため、次のようなガワをかぶせた。
    + `function<bool(T&)>` の別名として `enumerator<T>` を定義(using)

```enumerate.h
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
```

辞書向けバージョン
-----------------

### [sub2.cpp](./sub2.cpp)

```sub2.cpp
#include <string>
#include <iostream>
#include "enumerate2.h"

void sub(pair_enumerator<std::string,int> &each)
{
    std::string key;
    int value;
    while( each(key,value) ){
        std::cout << key << ":" << value << std::endl;
    }
}

```

### [main2.cpp](./main2.cpp)

```main2.cpp
#include <string>
#include <map>
#include <unordered_map>

#include "enumerate2.h"

extern void sub(pair_enumerator<std::string,int> &each);

int main(){
    std::map<std::string,int> map;
    map["ahaha"] = 1;
    map["ihihi"] = 2;
    map["ufufu"] = 3;
    sub(make_pair_enumerator(map));

    std::unordered_map<std::string,int> umap;
    umap["AHAHA"] = 1;
    umap["IHIHI"] = 2;
    umap["UFUFU"] = 3;
    sub(make_pair_enumerator(umap));
}
```

### [enumerate2.h](./enumerate2.h)

```enumerate2.h
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
```
