### Краткие выводы

1. На "идеальных"(уникальные и равномерне) данных версия с параллелизацией только на шаге рекурсии работает лучше всего
2. С ростом числа дубликатов как последовательная, так и параллельные версии работают (ожидаемо) быстрее, но выигрыш от
   использования параллелизации снижается. Тем не менее, версии, в которых процесс фильтрации и заполнения массива
   отсортированными значениями последовательный, работают хуже, чем та, где он параллелен, так как при число слоев
   рекурсии уменьшается, а работа на каждом слое, наоборот, увеличивается, и становится выгоднее параллелить ее.
3. С увеличением скошенности распределения скорость работы в абсолютных показателях также увеличивается за счет
   уменьшения числа слоев рекурсии, так как, попадая в "частое" значение, оставляем меньшее число элементов, не равных
   ему, для сортировки на следующем уровне. Тут так же, как и с увеличением числа уникальных элементов, прирост скорости
   от параллелизации снижается, но тут еще играет роль то, что при неравномерном распределении часто ветви рекурсии
   значительно отличаются по глубине, и тогда, во-первых, наиболее глубокая ветвь становится узким местом, а во-вторых,
   потоки простаивают. Аналогично увеличению числа дубликатов версия с параллелизированными фильтрами и заполнением
   становится эффективнее остальных.

Current number of threads 4

```
Started trials to search for the optimal block size
0: block 4 finished in 80236
1: block 32 finished in 25149
2: block 64 finished in 20094
3: block 128 finished in 16718
4: block 256 finished in 16084
5: block 512 finished in 14942
6: block 1024 finished in 13482
7: block 2048 finished in 12429
8: block 4096 finished in 12984
9: block 8192 finished in 11926
10: block 16384 finished in 11595
11: block 32768 finished in 11377
12: block 65536 finished in 11102
13: block 131072 finished in 11110
14: block 262144 finished in 11111
15: block 524288 finished in 10679
16: block 1048576 finished in 10425
17: block 2097152 finished in 10742
18: block 4194304 finished in 10705
19: block 8388608 finished in 10197
20: block 16777216 finished in 10938
21: block 33554432 finished in 11316
Exponential search finished with best time 10197 reached on 8388608
0: block 10485744 finished in 9959; block 10551296 finished in 10500
1: block 10485712 finished in 10147; block 10551297 finished in 11022
2: block 10485648 finished in 9865; block 10551298 finished in 10363
3: block 10485520 finished in 10151; block 10551299 finished in 10065
4: block 10485264 finished in 11095; block 10551300 finished in 10696
5: block 10484752 finished in 10520; block 10551301 finished in 10967
6: block 10483728 finished in 10353; block 10551302 finished in 10476
7: block 10481680 finished in 10638; block 10551303 finished in 11380
8: block 10477584 finished in 10193; block 10551304 finished in 10450
9: block 10469392 finished in 11215; block 10551305 finished in 11543
10: block 10453008 finished in 10214; block 10551306 finished in 10091
11: block 10420240 finished in 11517; block 10551307 finished in 10116
12: block 10354704 finished in 10131; block 10551308 finished in 9909
13: block 10223632 finished in 10856; block 10551309 finished in 10416
14: block 9961488 finished in 11142; block 10551310 finished in 10459
15: block 9437200 finished in 10165; block 10551311 finished in 11278
16: block 8388624 finished in 10083; block 10551312 finished in 10015
17: block 6291472 finished in 11129; block 10551313 finished in 11185
18: block 2097168 finished in 10717; block 10551314 finished in 10756
2nd phase finished with best time 9865 reached on 10485648
Started trials to search for the optimal block size
0: block 4 finished in 85366
1: block 32 finished in 27605
2: block 64 finished in 19977
3: block 128 finished in 16392
4: block 256 finished in 14274
5: block 512 finished in 13052
6: block 1024 finished in 12992
7: block 2048 finished in 11805
8: block 4096 finished in 11359
9: block 8192 finished in 10841
10: block 16384 finished in 11052
11: block 32768 finished in 11188
12: block 65536 finished in 10621
13: block 131072 finished in 10872
14: block 262144 finished in 10472
15: block 524288 finished in 10051
16: block 1048576 finished in 10369
17: block 2097152 finished in 10021
18: block 4194304 finished in 9557
19: block 8388608 finished in 10224
20: block 16777216 finished in 10392
21: block 33554432 finished in 10671
Exponential search finished with best time 9557 reached on 4194304
0: block 5242864 finished in 10143; block 5308416 finished in 10082
1: block 5242832 finished in 10188; block 5308417 finished in 9902
2: block 5242768 finished in 9950; block 5308418 finished in 9389
3: block 5242640 finished in 9539; block 5308419 finished in 9835
4: block 5242384 finished in 9962; block 5308420 finished in 9721
5: block 5241872 finished in 9592; block 5308421 finished in 10092
6: block 5240848 finished in 10165; block 5308422 finished in 9723
7: block 5238800 finished in 10021; block 5308423 finished in 9793
8: block 5234704 finished in 9781; block 5308424 finished in 9973
9: block 5226512 finished in 9894; block 5308425 finished in 10221
10: block 5210128 finished in 10378; block 5308426 finished in 10074
11: block 5177360 finished in 9917; block 5308427 finished in 9964
12: block 5111824 finished in 9782; block 5308428 finished in 9848
13: block 4980752 finished in 9629; block 5308429 finished in 9481
14: block 4718608 finished in 10131; block 5308430 finished in 9790
15: block 4194320 finished in 10011; block 5308431 finished in 9755
16: block 3145744 finished in 10437; block 5308432 finished in 9593
17: block 1048592 finished in 10057; block 5308433 finished in 9758
2nd phase finished with best time 9389 reached on 5308418
```

### Run on random integers from [INT_MIN; INT_MAX]

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   30008   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   9702    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   9662    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   9799    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   30039   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   10501   |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   9787    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   9699    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   29632   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   10611   |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   9708    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   10410   |    1    |
| 3 |         Sequential          |    1    | 200000000 |   30179   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   11038   |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   9194    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   9996    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   29923   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   10977   |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   11478   |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   9509    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.8354   |
| Parallel. Sequential filter |  3.00612   |
|     Parallel. Only fork     |  3.03137   |

### Run on the same values equal to integer from [INT_MIN; INT_MAX]

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |    111    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |    69     |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |    61     |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |    90     |    1    |
| 1 |         Sequential          |    1    | 100000000 |    110    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |    75     |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |    67     |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |    77     |    1    |
| 2 |         Sequential          |    1    | 100000000 |    110    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |    68     |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |    64     |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |    89     |    1    |
| 3 |         Sequential          |    1    | 100000000 |    110    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    66     |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |    63     |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |    75     |    1    |
| 4 |         Sequential          |    1    | 100000000 |    110    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |    71     |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |    62     |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |    77     |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   1.5942   |
| Parallel. Sequential filter |  1.74603   |
|     Parallel. Only fork     |  1.35802   |

### Run on already sorted distinct values

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   12353   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   5153    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4675    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4697    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   12446   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4682    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   4845    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4761    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   12381   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   5173    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   6177    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   5787    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   12396   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4375    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4701    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4611    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   12192   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   4481    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4787    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4632    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.58864   |
| Parallel. Sequential filter |  2.45245   |
|     Parallel. Only fork     |  2.52256   |

### Run on reversed sorted sequence of distinct integers

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   14643   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   5321    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   8110    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   5211    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   14447   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4940    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   5549    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   5863    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   14723   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   5082    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   5519    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   5076    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   14829   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   6097    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   5369    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   6409    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   14784   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   5310    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   5519    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   5156    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.74486   |
| Parallel. Sequential filter |  2.44221   |
|     Parallel. Only fork     |  2.64929   |

### Run on Uniform; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   27800   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   10098   |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   9493    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   8995    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   27666   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   9631    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   9372    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   9287    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   27690   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   8539    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   9149    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   9383    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   27587   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   11873   |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   9086    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   9354    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   27822   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   9053    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   9596    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   9197    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.81693   |
| Parallel. Sequential filter |  2.96745   |
|     Parallel. Only fork     |  2.99827   |

### Run on Uniform; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   17272   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   7424    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   6203    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   6514    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   17443   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   7442    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   6826    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   6182    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   17123   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   6053    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   6540    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   6720    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   17316   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   7503    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   7515    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   6477    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   17011   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   7116    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   6539    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   6047    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.42479   |
| Parallel. Sequential filter |  2.56291   |
|     Parallel. Only fork     |  2.69771   |

### Run on Uniform; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   11606   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   5035    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   5803    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   6306    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   11249   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   5445    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   6097    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   5258    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   11572   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   4728    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   5909    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4824    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   11729   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   5216    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4838    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   5125    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   11736   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   5162    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4909    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4850    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.26265   |
| Parallel. Sequential filter |  2.10089   |
|     Parallel. Only fork     |  2.19613   |

### Run on Uniform; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   6311    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3110    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3508    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4342    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   5939    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   3260    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   4101    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3630    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   6113    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3257    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   5169    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4229    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   5967    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3008    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   3978    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3926    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   5943    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3421    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4306    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3671    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  1.88539   |
| Parallel. Sequential filter |  1.43732   |
|     Parallel. Only fork     |  1.52917   |

### Run on StudentT ν=1(cauchy); 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   23214   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   9394    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   7746    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   8056    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   23492   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   7886    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   8367    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   7688    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   23656   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   8016    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   9474    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   9435    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   23479   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   9583    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   9006    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   7846    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   23169   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   8728    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   8099    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   7977    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.68341   |
| Parallel. Sequential filter |  2.74092   |
|     Parallel. Only fork     |   2.8539   |

### Run on StudentT ν=1(cauchy); 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   15275   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   6448    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   6131    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   6561    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   15393   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   5939    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   5468    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   6078    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   15269   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   7308    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   6285    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   6182    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   15444   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   5822    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   7118    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   6746    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   15403   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   5560    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   6212    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   6319    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.4708   |
| Parallel. Sequential filter |  2.46011   |
|     Parallel. Only fork     |  2.40803   |

### Run on StudentT ν=1(cauchy); 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   10008   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   4587    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   5278    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4606    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   10420   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4374    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   4892    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4990    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   9947    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   4972    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   5282    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4674    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   10111   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4694    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4929    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   5095    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   9693    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   4364    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4776    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4797    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.18247   |
| Parallel. Sequential filter |  1.99463   |
|     Parallel. Only fork     |  2.07678   |

### Run on StudentT ν=1(cauchy); 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   4744    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2411    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3125    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3367    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   4865    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2500    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3448    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3257    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   5137    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2637    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4454    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3080    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   5074    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2544    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   3802    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3552    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   5037    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2347    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3128    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4098    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  1.99879   |
| Parallel. Sequential filter |  1.38429   |
|     Parallel. Only fork     |  1.43256   |

### Run on StudentT ν=1000(normal); 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   26215   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   8359    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   8436    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   9195    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   26496   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   10595   |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   9756    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   8963    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   26247   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   9002    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   8857    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   9017    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   26025   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   8802    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   9619    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   9933    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   26037   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   9626    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   9316    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   9064    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.82492   |
| Parallel. Sequential filter |   2.8495   |
|     Parallel. Only fork     |  2.83777   |

### Run on StudentT ν=1000(normal); 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   16505   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   6375    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   6142    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   6461    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   16587   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   6912    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   7155    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   6009    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   16669   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   6149    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   6092    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   6106    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   16593   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   6340    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   6551    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   7314    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   16441   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   6586    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   6246    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   6121    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.55856   |
| Parallel. Sequential filter |  2.57247   |
|     Parallel. Only fork     |  2.58654   |

### Run on StudentT ν=1000(normal); 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   11121   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   5064    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   5054    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   5864    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   10946   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   5301    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   6374    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   5524    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   10936   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   5337    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4921    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   5523    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   11135   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4686    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   5249    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4974    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   11150   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   5045    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   5024    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   5029    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.17401   |
| Parallel. Sequential filter |  2.07682   |
|     Parallel. Only fork     |  2.05444   |

### Run on StudentT ν=1000(normal); 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 200000000 |   6030    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3203    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4842    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4208    |    1    |
| 1 |         Sequential          |    1    | 200000000 |   5827    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   3182    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3641    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3643    |    1    |
| 2 |         Sequential          |    1    | 200000000 |   5729    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3265    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3679    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4736    |    1    |
| 3 |         Sequential          |    1    | 200000000 |   5905    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3091    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   3538    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4391    |    1    |
| 4 |         Sequential          |    1    | 200000000 |   5831    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2862    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3529    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4050    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  1.87949   |
| Parallel. Sequential filter |   1.5251   |
|     Parallel. Only fork     |  1.39453   |

### Run on LogNormal σ=2; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   10651   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3631    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3841    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3793    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   10752   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4277    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3570    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4134    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   10706   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3892    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3743    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3773    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   10660   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   5139    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4060    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3628    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   10710   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   4127    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3596    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3703    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.53857   |
| Parallel. Sequential filter |   2.8429   |
|     Parallel. Only fork     |  2.81004   |

### Run on LogNormal σ=2; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   6973    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2740    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2915    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2787    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   6963    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2825    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2940    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2920    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7087    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3307    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3400    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2846    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7044    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3257    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2765    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2851    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7072    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3326    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3063    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2637    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.27337   |
| Parallel. Sequential filter |  2.32991   |
|     Parallel. Only fork     |  2.50249   |

### Run on LogNormal σ=2; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   4319    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2205    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2374    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2580    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4337    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2006    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1940    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2619    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4359    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2324    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2540    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2120    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   4305    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2148    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2743    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2314    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4424    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2006    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2103    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2366    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.03463   |
| Parallel. Sequential filter |  1.85812   |
|     Parallel. Only fork     |  1.81242   |

### Run on LogNormal σ=2; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   1966    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |    904    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1293    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1454    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   1817    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   1059    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1732    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1710    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   1972    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |    967    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1396    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   1545    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   1883    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    949    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1571    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1448    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   1911    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |    982    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1556    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1735    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  1.96399   |
| Parallel. Sequential filter |  1.26508   |
|     Parallel. Only fork     |  1.20976   |

### Run on LogNormal σ=0.3; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   11989   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   4340    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4276    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4166    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   12200   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4915    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   5067    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4733    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   12123   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   5289    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4526    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3980    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   12074   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4038    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4266    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4090    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   12136   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3914    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4208    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4221    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.69038   |
| Parallel. Sequential filter |  2.70904   |
|     Parallel. Only fork     |  2.85606   |

### Run on LogNormal σ=0.3; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   7642    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3133    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3122    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2922    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   7658    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   3120    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3113    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2999    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7560    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3105    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3337    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2884    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7596    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3134    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2936    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3081    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7518    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3324    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2951    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3048    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.40089   |
| Parallel. Sequential filter |  2.45681   |
|     Parallel. Only fork     |   2.5432   |

### Run on LogNormal σ=0.3; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   4849    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2437    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2445    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2538    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4961    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2325    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2995    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2244    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4950    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2339    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2592    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2221    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   5081    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   1952    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2427    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2344    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4967    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   1910    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2588    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3064    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.26323   |
| Parallel. Sequential filter |  1.90149   |
|     Parallel. Only fork     |  1.99879   |

### Run on LogNormal σ=0.3; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   2335    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   1173    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1762    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1599    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   2418    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   1253    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1534    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1889    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   2475    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   1220    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1662    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   1554    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   2340    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   1284    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1928    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1804    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   2359    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   1195    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2148    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1628    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  1.94694   |
| Parallel. Sequential filter |   1.3206   |
|     Parallel. Only fork     |  1.40791   |

### Run on "Paretto" {10, 80, 10}, 1 mode; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   11062   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3839    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4124    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3725    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   11055   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4410    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   4143    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3745    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   11169   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3864    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4910    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3882    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   11278   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3905    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   3832    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4023    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   11340   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3827    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3912    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3972    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.81683   |
| Parallel. Sequential filter |  2.67208   |
|     Parallel. Only fork     |  2.88964   |

### Run on "Paretto" {10, 80, 10}, 5 modes; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   11280   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   5007    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3942    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3818    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   11233   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4361    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3888    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4445    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   11219   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3812    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3952    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4229    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   11250   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3793    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4163    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3970    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   11191   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3910    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4084    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3883    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.69013   |
| Parallel. Sequential filter |  2.80499   |
|     Parallel. Only fork     |  2.76087   |

### Run on "Paretto" {10, 80, 10}, 1 mode; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   7349    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3653    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2974    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3123    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   7372    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   3184    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2657    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3101    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7417    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2829    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3177    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3029    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7333    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2721    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2920    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2822    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7480    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2527    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3062    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2788    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.4782   |
| Parallel. Sequential filter |  2.49831   |
|     Parallel. Only fork     |  2.48654   |

### Run on "Paretto" {10, 80, 10}, 5 modes; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   7386    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2953    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2630    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2917    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   7331    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   3174    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2768    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2987    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7330    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3030    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2773    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2876    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7308    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2938    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2935    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3295    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7382    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3100    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2776    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   3032    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.41757   |
| Parallel. Sequential filter |  2.64661   |
|     Parallel. Only fork     |  2.43198   |

### Run on "Paretto" {10, 80, 10}, 1 mode; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   4481    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   1917    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2369    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2499    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4482    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2066    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1959    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2195    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4608    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   1888    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2419    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2068    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   4618    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   1950    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1964    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2332    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4572    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2217    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1955    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2239    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.26806   |
| Parallel. Sequential filter |  2.13408   |
|     Parallel. Only fork     |  2.00883   |

### Run on "Paretto" {10, 80, 10}, 5 modes; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   4570    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2155    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2863    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2521    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4478    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2166    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1993    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2115    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4664    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2567    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2758    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2217    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   4586    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2421    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2128    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2019    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4403    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2012    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2219    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2245    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.0053   |
| Parallel. Sequential filter |  1.89799   |
|     Parallel. Only fork     |  2.04229   |

### Run on "Paretto" {10, 80, 10}, 1 mode; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   1875    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |    937    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1754    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1634    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   1789    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |    836    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1577    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1758    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   1920    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |    778    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1609    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   1305    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   1855    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    973    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1925    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1688    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   1810    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |    988    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1301    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1573    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.04989   |
| Parallel. Sequential filter |  1.13227   |
|     Parallel. Only fork     |  1.16216   |

### Run on "Paretto" {10, 80, 10}, 5 modes; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   1764    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |    781    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1658    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1836    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   1765    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |    891    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1349    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1311    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   1833    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |    960    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1506    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   1399    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   1750    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    899    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1603    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1917    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   1873    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |    841    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1661    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1829    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.05606   |
| Parallel. Sequential filter |  1.15563   |
|     Parallel. Only fork     |  1.08384   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 1 mode; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   12091   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   4169    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4227    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4146    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   12164   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   5278    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   4107    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4263    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   12157   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   3990    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4131    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4079    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   12013   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4050    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4435    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4133    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   12149   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   4704    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4415    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4092    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.72961   |
| Parallel. Sequential filter |  2.84166   |
|     Parallel. Only fork     |  2.92467   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 5 modes; 10^8 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   11910   |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   4160    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   4409    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   4003    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   12099   |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   4818    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3917    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   4231    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   12055   |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   4217    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   4485    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   4194    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   12076   |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   4295    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   4525    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   4143    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   12021   |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3865    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   4233    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   4079    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.81714   |
| Parallel. Sequential filter |  2.78971   |
|     Parallel. Only fork     |  2.91332   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 1 mode; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   7770    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2896    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2870    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2954    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   7721    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2695    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2970    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   3090    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7594    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2904    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2956    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3079    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7755    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3348    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2770    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3073    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7738    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3078    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   3138    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2951    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.58546   |
| Parallel. Sequential filter |  2.62415   |
|     Parallel. Only fork     |  2.54705   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 5 modes; 10^6 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   7840    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   3298    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   3497    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   3661    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   7697    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2816    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   3451    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2952    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   7784    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2810    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   3493    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   3153    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   7704    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   3053    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2781    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   3081    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   7665    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   3108    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2897    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2858    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.5648   |
| Parallel. Sequential filter |  2.40087   |
|     Parallel. Only fork     |  2.46355   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 1 mode; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   5017    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   1937    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2169    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2605    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4929    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2300    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2073    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2308    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4952    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2135    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2339    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2500    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   4914    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2392    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2221    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2307    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4955    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2406    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2524    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2216    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |   2.2171   |
| Parallel. Sequential filter |  2.18675   |
|     Parallel. Only fork     |  2.07499   |

### Run on "Paretto" {8, 40, 6, 41, 7}, 5 modes; 10^4 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   4866    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   2473    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   2383    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   2705    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   4819    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   2141    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   2236    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   2208    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   4844    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   2611    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   2249    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2125    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   4812    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |   2262    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   2291    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   2673    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   4804    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   2324    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   2445    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   2255    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.04445   |
| Parallel. Sequential filter |  2.08147   |
|     Parallel. Only fork     |  2.01797   |

### Run on Paretto {8, 40, 6, 41, 7}, 1 mode; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   2107    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |    985    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1528    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1920    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   2233    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |    981    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1850    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1961    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   2258    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |    979    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1633    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   1564    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   2202    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    925    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1524    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1640    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   2179    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |   1159    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1736    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1852    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.18408   |
| Parallel. Sequential filter |  1.32709   |
|     Parallel. Only fork     |  1.22832   |

### Run on Paretto {8, 40, 6, 41, 7}, 5 modes; 10^2 unique

```
Sequential trials started

Parallel trials started (all parallelized)
Parallel trials started (sequential filter)
Parallel trials started (only fork)
```

| # |            Name             | Threads | BlockSize | Time (ms) | Correct |
|:-:|:---------------------------:|:-------:|:---------:|:---------:|:-------:|
| 0 |         Sequential          |    1    | 100000000 |   2189    |    1    |
| 0 | Parallel. All parallelized  |    4    | 10485648  |   1021    |    1    |
| 0 | Parallel. Sequential filter |    4    | 10485648  |   1690    |    1    |
| 0 |     Parallel. Only fork     |    4    |  5308418  |   1669    |    1    |
| 1 |         Sequential          |    1    | 100000000 |   2132    |    1    |
| 1 | Parallel. All parallelized  |    4    | 10485648  |   1065    |    1    |
| 1 | Parallel. Sequential filter |    4    | 10485648  |   1802    |    1    |
| 1 |     Parallel. Only fork     |    4    |  5308418  |   1557    |    1    |
| 2 |         Sequential          |    1    | 100000000 |   2143    |    1    |
| 2 | Parallel. All parallelized  |    4    | 10485648  |   1091    |    1    |
| 2 | Parallel. Sequential filter |    4    | 10485648  |   1532    |    1    |
| 2 |     Parallel. Only fork     |    4    |  5308418  |   2163    |    1    |
| 3 |         Sequential          |    1    | 100000000 |   2112    |    1    |
| 3 | Parallel. All parallelized  |    4    | 10485648  |    978    |    1    |
| 3 | Parallel. Sequential filter |    4    | 10485648  |   1750    |    1    |
| 3 |     Parallel. Only fork     |    4    |  5308418  |   1499    |    1    |
| 4 |         Sequential          |    1    | 100000000 |   2331    |    1    |
| 4 | Parallel. All parallelized  |    4    | 10485648  |    982    |    1    |
| 4 | Parallel. Sequential filter |    4    | 10485648  |   1720    |    1    |
| 4 |     Parallel. Only fork     |    4    |  5308418  |   1507    |    1    |

|            Name             | Sequential |
|:---------------------------:|:----------:|
| Parallel. All parallelized  |  2.12366   |
| Parallel. Sequential filter |  1.28445   |
|     Parallel. Only fork     |  1.29899   |