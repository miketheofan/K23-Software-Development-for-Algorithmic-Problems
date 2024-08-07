# Assignment 2 - Software Development for Algorithmic Problems

### Authors

- **Michael Theofanopoulos** (ID: 111 520 18 00 053)
- **Spyridon Dimisianos** (ID: 111 520 18 00 042)

## Project Structure

- **`search` Folder**

  - `mainSEARCH.cpp`
  - `mainSEARCH.h`

- **`cluster` Folder**

  - `mainCluster.cpp`
  - `mainCluster.h`

- **`brute` Folder**

  - `bruteFunctionsCUBE.cpp`
  - `bruteFunctionsLSH.cpp`

- **`data` Folder**

  - `items.cpp`
  - `Curve.cpp`
  - `Grid.cpp`
  - `GridContinuous.cpp`

- **`src` Folder**

  - `util.cpp`
  - `utilCLUSTER.cpp`
  - `utilLSH.cpp`

- **`structures` Folder**

  - `Cluster.cpp`
  - `G.cpp`
  - `H.cpp`
  - `Hash.cpp`
  - `HashTable.cpp`
  - `HyperCube.cpp`

- **`tests` Folder**

  - Test data files (queries, dataset)
  - `cluster.conf`

- **`headers` Folder**

  - All header files (excluding `main` function headers)

- **Additional Files**
  - `Test.cpp`, `Test.h`, `TestMain.cpp` (CPP unit tests)
  - `makefile`
  - `output.txt`

## Execution Instructions

**Compilation**

```sh
make
```

**Execute part A:**:

```
  make out1 # Part A
  make out2 # Part B
  make out3 # CPPUNIT
```

**Without makefile:**

```
  ./outSEARCH -i /tests/dataset.csv -q /tests/query.csv -k [int] -L [int] -M [int] - probes [int] -o output.txt -algorithm [string] -metric [string] -delta [double]

  ./outCLUSTER -i /tests/dataset.csv -c /tests/cluster.conf -o output.txt -update [string] -assignment [string] -complete [optional] -silhouette [optional]
```

## Class Descriptions

### New Classes

- **Curve**: Represents a curve with a list of item objects.
- **Grid**: Used for snapping curves in discrete Frechet.
- **GridContinuous**: Used in continuous Frechet.
- **Continuous**: Implements continuous Frechet algorithm with LSH.
- **Discrete**: Implements discrete Frechet algorithm with LSH.

## General Approach

The approach mirrors the previous project, with similar initialization for structures like LSH, Hypercube, and Cluster. Adjustments were made to optimize execution based on provided datasets.

**Note:** The code includes comments for ease of understanding.
