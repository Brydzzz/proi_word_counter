## Zadanie 3 PROI - licznik

### Uwagi dotyczące implementacji

Zdecydowałam się dodawać słowa do `word_counter` leksykograficznie (rosnąco). Dzięki temu iterowanie przy pomocy `lex_iterator` jest bardzo szybkie, ponieważ nie musi on wykonywać dodatkowych operacji przy przechodzeniu przez wektor. Przyśpieszyło to również działanie pary operatorów indeksowania, ponieważ mogłam skorzystać z wyszukiwania binarnego.

**Dodatkowe metody klasy** `entry` (nie było ich w poleceniu)

- `entry& operator+=(int)` - używana przy dodawniu `entry` do licznika (`add_entry()`), szczególnie przydatna, przy dodawaniu do siebie dwóch liczników

- `bool operator<(std::string const& str_value) const` - potrzebna do używania `lower_bound` w metodach klasy `word_counter` -> `add_entry()` i operatory indeksowania

### Czas działania

Mierzony w `main.cpp` zbudowanym w trybie budowania `Release`

1. **Zliczenie słów z** `moby_dick.txt`

Czas trwania: ~`560ms`

2. **Zapisanie licznika w porządku leksykograficznym (rosnąco) do pliku**

Czas trwania: ~`2ms`

3. **Zapisanie licznika w kolejność od słowa najczęściej wystepującego, do słowa najrzadziej występującego do pliku**

Czas trwania: ~`1800ms`