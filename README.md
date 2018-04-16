# Econophysics
Generators and analyzers for econophysics

This code is using [OpenMP](http://www.openmp.org/) for optimization, run it like:

`$ g++ main.cpp Analyzer.cpp Exchanger.cpp -fopenmp`

## Analyzer

This gives the Gini and Shanon Entropy of the analyzed data

#### Linux

`$ ./a.out 1 "file_to_analyze.extension"`

#### Windows

`$ a.exe 1 "file_to_analyze.extension"`

## Exchange generators

### Dragulescu-Yakovenko exchange

#### Linux

`$ ./a.out 2 1 > file.dat`

#### Windows

`$ a.exe 2 1 > file.dat`

### Chakraborti-Chakrabarti exchange

#### Linux

`$ ./a.out 2 2 > file.dat`

#### Windows

`$ a.exe 2 2 > file.dat`

### Bouchard-Mezard exchange

#### Linux

`$ ./a.out 2 3 > file.dat`

#### Windows

`$ a.exe 2 3 > file.dat`

The files generated with this exchangers can be analyzed with [Analyzer](#analyzer)