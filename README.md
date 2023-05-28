# QuDataSet and QuDataSet::Iterator - C++ Multi Purpose Iterator Based on Filters

PURPOSE: to provide different ways to iterate data items
CLASSES: QuDataSet, QuDataSet::Iterator
 
DESCRIPTION: single data buffer (vector is used here to store data), we can iterate the data in 
  different ways based on a filter function provided. If no filter function is provided, the 
  iterator will traverse all items.

  for example, for following data items, we can create different iterators based on filters:
  data:      |d0 |d1 |d2 |d3 |d4 |d5 |d6 |d7 |d8 |d9 |d10|d11|d12|d13|d14|d15|d16|d17|d18|d19|...
  default      0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19 ...
  filter1              0           1   2                       3           4           5      ...
  filter2      0               1               2                               3              ...
 
USAGE: a usage example of how to use multi iterators is provided in test.cpp 
 
