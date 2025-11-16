Изначально я реализовала сортировки в виде имплементаций функции `void sort(sequence<int>& arr)` в классах-наследниках
интерфейcа `QuickSort`, `SequentialSort` и `ParallelSort`:

```
class QuickSort {
public:
    virtual void sort(PSeq<int> &arr) = 0;
};

class SequentialQuickSort : public QuickSort {
private:
    size_t lastSortedSz;

    static void sortSlice(const SeqIt &begin, const SeqIt &end) { ... }

public:
    void sort(PSeq<int> &arr) override {
        sortSlice(arr.begin(), arr.end());
    };
    friend class ParallelQuickSort;
};

class ParallelQuickSort : public QuickSort {
private:
    static void sortInternal(const SeqIt &begin, const SeqIt &end, int &bls) {...}
public:
    void sort(PSeq<int> &arr) override {
        sortInternal(arr.begin(), arr.end(), blockSize);
    };
};
```

Но работало это отвратительно медленно в случае как последовательной, так и параллельной версии, поэтому в тех местах,
где требовалось наличие представителя QuickSort, он был заменен
на `type QSortingFunc = std::function<void(PSeq<int> &)>`, представляющий абстракцию над типом сортирующей функции. Это
работает значительно быстрее. чем классы, но тем не меннее измерение времении, запускаемое на лямбде

```
LL runTimed(QSortingFunc &quickSort, PSeq<int> &arr) {
    const auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr);
    const auto end = std::chrono::high_resolution_clock::now();
}
```

дает намного более медленные показатели, чем чистое измерение, запущенное непосредственно на конкретной функции (скорее
всего, если заменить тип `QSortingFunc quickSort` на `template <typename T>; T quickSort`, будет быстрее в абсолютном
выражении)

``` 
// void parallelQuickSort(Pseq<int> &arr)
const auto start = std::chrono::high_resolution_clock::now();
parallelQuickSort(arr);
const auto end = std::chrono::high_resolution_clock::now();
```

Несмотря на высокие абсолютные показатели, данная реализация не искажает (во всяком случае не достаточно значительно,
чтобы это было заметно) относительные результаты времени работы одной и другой имплементаций QuickSort'а.

Тестирование проводилось на нескольких наборах числел размером 10^8 или 2*10^8:

- `random integers from [INT_MIN; INT_MAX]` - 2*10^8 случайно взятых целых чисел из отрезка [INT_MIN; INT_MAX]
- `values equal to integer from [INT_MIN; INT_MAX]` - выбрано 1 случайное число из отрезка [INT_MIN; INT_MAX], которым
  заполнен массив на 10^8 элементов
- `already sorted distinct values` - взяли последовательность чисел от -10^8 до 10^8
- `reversed sorted sequence of distinct integers` - взяли последовательность чисел от 10^8 до -10^8
- `shuffled sequence of distinct integers` - взяли случайную перестановку последовательности чисел от -10^8 до 10^8

Во всех случаях параллельная версия имеет преимущество примерно в 3.7 раз; исключение - массив с одинаковыми значениями,
что ожидаемо, потому как в последовательной реализации будет просто 1 проход по массиву с проверкой на "<",
а в параллельной таких проходов будет 3.

Также стоит отметить, что размер блока, который будет сортироваться последовательно, подбирается автоматически, и
наилучшие результаты получаются на блоках порядка 10^5, однако (можно посмотреть в выводе программы ниже) и на меньших
блоках работает не намного хуже

Проверка корректности работы, то есть того, что массив оказался отсортированным, осуществляется с помощью
функции `parlay::is_sorted`, и ее результаты отражены в графе "Correct" в таблицах ниже

Далее представлен вывод программы в консоль (специально прописывала, чтобы получалась валидная md разметка):

Current amount of threads 4

```
Started trials to search for the optimal block size
0: block 4 finished in 128877
1: block 32 finished in 69659
2: block 64 finished in 61680
3: block 128 finished in 58974
4: block 256 finished in 57214
5: block 512 finished in 55862
6: block 1024 finished in 55456
7: block 2048 finished in 56060
8: block 4096 finished in 54292
9: block 8192 finished in 54444
10: block 16384 finished in 54032
11: block 32768 finished in 53449
12: block 65536 finished in 53146
13: block 131072 finished in 52847
14: block 262144 finished in 53272
15: block 524288 finished in 52245
16: block 1048576 finished in 52401
17: block 2097152 finished in 53065
18: block 4194304 finished in 56653
19: block 8388608 finished in 58771
20: block 16777216 finished in 58970
21: block 33554432 finished in 68205
Exponential search finished with best time 52245 reached on 524288
0: block 655344 finished in 54058; block 720896 finished in 52642
1: block 655312 finished in 52955; block 720897 finished in 53424
2: block 655248 finished in 52531; block 720898 finished in 52459
3: block 655120 finished in 51983; block 720899 finished in 52344
4: block 654864 finished in 53106; block 720900 finished in 53315
5: block 654352 finished in 53042; block 720901 finished in 52507
6: block 653328 finished in 53038; block 720902 finished in 52014
7: block 651280 finished in 52043; block 720903 finished in 52574
8: block 647184 finished in 53142; block 720904 finished in 52583
9: block 638992 finished in 53135; block 720905 finished in 53330
10: block 622608 finished in 52836; block 720906 finished in 53164
11: block 589840 finished in 52706; block 720907 finished in 52377
12: block 524304 finished in 52752; block 720908 finished in 53673
13: block 393232 finished in 52225; block 720909 finished in 52117
14: block 131088 finished in 52968; block 720910 finished in 53115
2nd phase finished with best time 51983 reached on 655120
```

### Run on random integers from [INT_MIN; INT_MAX]

```
Sequential trials started

Parallel trials started
```

|  #  |    Name    | Threads | BlockSize | Time (ms) | Correct |
|:---:|:----------:|:-------:|:---------:|:---------:|:-------:|
|  1  | Sequential |    1    | 200000000 |  195121   |    1    |
|  1  |  Parallel  |    4    |  655120   |   52669   |    1    |
|  2  | Sequential |    1    | 200000000 |  195069   |    1    |
|  2  |  Parallel  |    4    |  655120   |   53448   |    1    |
|  3  | Sequential |    1    | 200000000 |  194848   |    1    |
|  3  |  Parallel  |    4    |  655120   |   52619   |    1    |
|  4  | Sequential |    1    | 200000000 |  194687   |    1    |
|  4  |  Parallel  |    4    |  655120   |   52511   |    1    |
|  5  | Sequential |    1    | 200000000 |  195078   |    1    |
|  5  |  Parallel  |    4    |  655120   |   52344   |    1    |
| avg | Sequential | 194960  | Parallel  |   52718   | 3.69817 |

**Parallel acceleration: 3.69817**

### Run on the same values equal to integer from [INT_MIN; INT_MAX]

```
Sequential trials started

Parallel trials started
```

|  #  |    Name    | Threads | BlockSize | Time (ms) | Correct |
|:---:|:----------:|:-------:|:---------:|:---------:|:-------:|
|  1  | Sequential |    1    | 100000000 |    112    |    1    |
|  1  |  Parallel  |    4    |  655120   |    66     |    1    |
|  2  | Sequential |    1    | 100000000 |    110    |    1    |
|  2  |  Parallel  |    4    |  655120   |    77     |    1    |
|  3  | Sequential |    1    | 100000000 |    113    |    1    |
|  3  |  Parallel  |    4    |  655120   |    74     |    1    |
|  4  | Sequential |    1    | 100000000 |    110    |    1    |
|  4  |  Parallel  |    4    |  655120   |    74     |    1    |
|  5  | Sequential |    1    | 100000000 |    119    |    1    |
|  5  |  Parallel  |    4    |  655120   |    72     |    1    |
| avg | Sequential |   112   | Parallel  |    72     | 1.55556 |

**Parallel acceleration: 1.55556**

### Run on already sorted distinct values

```
Sequential trials started

Parallel trials started
```

|  #  |    Name    | Threads | BlockSize | Time (ms) | Correct |
|:---:|:----------:|:-------:|:---------:|:---------:|:-------:|
|  1  | Sequential |    1    | 200000000 |  183957   |    1    |
|  1  |  Parallel  |    4    |  655120   |   48446   |    1    |
|  2  | Sequential |    1    | 200000000 |  183669   |    1    |
|  2  |  Parallel  |    4    |  655120   |   48658   |    1    |
|  3  | Sequential |    1    | 200000000 |  183743   |    1    |
|  3  |  Parallel  |    4    |  655120   |   47729   |    1    |
|  4  | Sequential |    1    | 200000000 |  183688   |    1    |
|  4  |  Parallel  |    4    |  655120   |   49011   |    1    |
|  5  | Sequential |    1    | 200000000 |  183696   |    1    |
|  5  |  Parallel  |    4    |  655120   |   49197   |    1    |
| avg | Sequential | 183750  | Parallel  |   48608   | 3.78024 |

**Parallel acceleration: 3.78024**

### Run on reversed sorted sequence of distinct integers

```
Sequential trials started

Parallel trials started
```

|  #  |    Name    | Threads | BlockSize | Time (ms) | Correct |
|:---:|:----------:|:-------:|:---------:|:---------:|:-------:|
|  1  | Sequential |    1    | 200000000 |  185846   |    1    |
|  1  |  Parallel  |    4    |  655120   |   49437   |    1    |
|  2  | Sequential |    1    | 200000000 |  185892   |    1    |
|  2  |  Parallel  |    4    |  655120   |   48068   |    1    |
|  3  | Sequential |    1    | 200000000 |  186142   |    1    |
|  3  |  Parallel  |    4    |  655120   |   50350   |    1    |
|  4  | Sequential |    1    | 200000000 |  185998   |    1    |
|  4  |  Parallel  |    4    |  655120   |   48728   |    1    |
|  5  | Sequential |    1    | 200000000 |  185699   |    1    |
|  5  |  Parallel  |    4    |  655120   |   48920   |    1    |
| avg | Sequential | 185915  | Parallel  |   49100   | 3.78646 |

**Parallel acceleration: 3.78646**

### Run on shuffled sequence of distinct integers

```
Sequential trials started

Parallel trials started
```

|  #  |    Name    | Threads | BlockSize | Time (ms) | Correct |
|:---:|:----------:|:-------:|:---------:|:---------:|:-------:|
|  1  | Sequential |    1    | 200000000 |  202091   |    1    |
|  1  |  Parallel  |    4    |  655120   |   54262   |    1    |
|  2  | Sequential |    1    | 200000000 |  202124   |    1    |
|  2  |  Parallel  |    4    |  655120   |   54154   |    1    |
|  3  | Sequential |    1    | 200000000 |  206647   |    1    |
|  3  |  Parallel  |    4    |  655120   |   53741   |    1    |
|  4  | Sequential |    1    | 200000000 |  206302   |    1    |
|  4  |  Parallel  |    4    |  655120   |   53890   |    1    |
|  5  | Sequential |    1    | 200000000 |  201816   |    1    |
|  5  |  Parallel  |    4    |  655120   |   53804   |    1    |
| avg | Sequential | 203796  | Parallel  |   53970   | 3.7761  |