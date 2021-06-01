# Chronological Sorting and Median Filter
`sort.c` sorts the stdio file from old to new, removes duplicates, and median-filters given variables.

data.txt looks like this:
```
#this is header meta data yyyy.MM.dd (DDD) HH:mm:ss C-score   foF2  foF1   foE  foEs   hmEs   hmF2   hmF1    hmE    B0   B1   D1


2020.02.01 (032) 00:20:00      100 2.800 2.350 0.373    ---    --- 288.100 120.770 110.000 78.100 6.000

2020.01.31 (031) 23:05:00      100 3.500 2.350 0.631    ---    --- 234.200 120.770 110.000 43.300 3.080

2020.02.01 (032) 06:35:00      100 3.250 2.350 0.373    ---    --- 291.400 120.770 110.000 41.500 1.830



2020.02.01 (032) 11:30:00      100 2.600 4.223 0.680    ---    --- 273.500 185.047 110.000 63.400 6.000

2020.01.31 (031) 23:50:00      100 3.150 2.350 0.373    ---    --- 247.200 120.770 110.000 38.800 3.340

2020.01.31 (031) 23:05:00      100 3.500 2.350 0.631    ---    --- 234.200 120.770 110.000 43.300 3.080
```

Sorting is done with `qsort()`; Header row that starts with '#' is detected.

Rows with any missing data or duplication of any previous row are separated for inspection.

Median-filtering is done for `foF2` and `hmF2` with window size 3.

Result of 
```
./a.out < data.txt
```
is 
```
[Missing column] line 2:
[Missing column] line 3:
[Missing column] line 5:
[Missing column] line 7:
[Missing column] line 9:
[Missing column] line 10:
[Missing column] line 11:
[Missing column] line 13:
[Missing column] line 15:
[Duplicate line] line 16: 2020.01.31 (031) 23:05:00      100 3.500 2.350 0.631    ---    --- 234.200 120.770 110.000 43.300 3.080

#this is header meta data yyyy.MM.dd (DDD) HH:mm:ss C-score   foF2  foF1   foE  foEs   h`Es   hmF2   hmF1    hmE    B0   B1   D1
2020. 1.31 ( 31) 23: 5: 0 100 3.500 2.350 0.631 ------ --- 234.200 120.770 110.000 43.300 3.080
2020. 1.31 ( 31) 23:50: 0 100 3.150 2.350 0.373 ------ --- 247.200 120.770 110.000 38.800 3.340
2020. 2. 1 ( 32)  0:20: 0 100 2.800 2.350 0.373 ------ --- 288.100 120.770 110.000 78.100 6.000
2020. 2. 1 ( 32)  6:35: 0 100 3.250 2.350 0.373 ------ --- 291.400 120.770 110.000 41.500 1.830
2020. 2. 1 ( 32) 11:30: 0 100 2.600 4.223 0.680 ------ --- 273.500 185.047 110.000 63.400 6.000

Median Filter, foF2 & hmf2:
2020. 1.31 ( 31) 23: 5: 0 3.325 240.700
2020. 1.31 ( 31) 23:50: 0 3.150 247.200
2020. 2. 1 ( 32)  0:20: 0 3.150 288.100
2020. 2. 1 ( 32)  6:35: 0 2.800 288.100
2020. 2. 1 ( 32) 11:30: 0 2.925 282.450
```
