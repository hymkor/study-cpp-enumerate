std::vector / std::set 両方からデータを取れる関数の本体をあまりテンプレートにしたくない
=============

std::vector / std::set 両方からデータを取れる関数をテンプレートにすると、 その関数をヘッダファイルに定義しなくちゃいけなくなるから。

過去のトライ
-----------

+ [std::vector / std::set 両方からデータを取れる関数をあまりテンプレートにしたくない - 標準愚痴出力](https://zetamatta.hatenablog.com/entry/2019/09/22/080313)
+ [(続) std::vector / std::set 両方からデータを取れる関数をあまりテンプレートにしたくない - 標準愚痴出力](https://zetamatta.hatenablog.com/entry/2019/09/22/131156)

最新成果
--------

### 利用例

#### 関数側 (sub.cpp)

```sub.cpp
#include <string>
#include <iostream>
#include "enumerate.h"

void put(const enumerator<std::string> &each)
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

#### 呼び出し側 (main.cpp)

```main.cpp
#include <string>
#include <vector>
#include <set>
#include "enumerate.h"

extern void put(const enumerator<std::string> &each);

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
}
```

+ 呼び出す際は、`std::vector<T>` や `std::set<T>` を `make_enumerator` という関数で、`enumerator<T>` へ変換して、`put` へ引き渡す.

#### 出力

```
$ a
a
b
c
1
2
3
```

### 実装 (enumerate.h)

+ `enumerator_impl<T>` という型は `bool operator()(bool(T&))` というメソッドを持っており、関数の体裁で呼び出すことができる
+ つまり、関数オブジェクトであるから、 `std::function<bool(T&)>` へ変換することができる。
+ ゆえに関数側のパラメータは `std::set` や `std::vector` などの型に固定しなくてよくなる。

+ この二つの組み合わせだけでも利用可能であるが、見かけの体裁を読みやすくするため、次のようなガワをかぶせた。
    + `enumerator_impl` のコンストラクタ → 型名を省略できるように関数 `make_enumerator` をかませる
    + `function<bool(T&)>` の別名として `enumerator<T>` を定義(using)

```enumerate.h
#include <functional>

template <typename T>
class enumerator_impl {
    typename T::iterator m_cursor,m_end;
public:
    enumerator_impl(typename T::iterator begin,typename T::iterator end)
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
enumerator_impl<T> make_enumerator(T &collection)
{
    return enumerator_impl<T>(collection.begin(), collection.end());
}
```
