# Assignment 1 - Software Development for Algorithmic Problems

## Project Structure

- **search Folder**: Contains `mainSEARCH.cpp` and `mainSEARCH.h` for Part A.
- **cluster Folder**: Contains `mainCluster.cpp` and `mainCluster.h` for Part B.
- **brute Folder**: Brute force implementations for HyperCube and LSH.
- **data Folder**: Contains implementations for `item`, `Curve`, `Grid`, and `GridContinuous` classes.
- **src Folder**: Utility functions for Parts A and B, and files from the provided black box code.
- **structures Folder**: Contains implementations of various classes (`Cluster`, `G`, `H`, `Hash`, `HashTable`, `Hypercube`).
- **tests Folder**: Contains data files (`queries`, `dataset`) and `cluster.conf`.
- **headers Folder**: All header files except main function headers.
- **Test Files**: `Test.cpp`, `Test.h`, `TestMain.cpp` for cpp unit testing of `curve` and `item` classes.
- **Makefile**: For building the project.
- **output.txt**: For collecting program outputs.

## Compilation and Execution

- **Compile the program**:

  ```
    make
  ```

- **Execute the programs using**:

  ```
    make out1 # LSH
    make out2 # Hypercube
    make out3 # Clustering
  ```

- **Alternatively, run the executables with**:

  ```
    ./outLSH -i dataset.txt -q query.txt -k [int] -L [int] -o output.txt -N [int] -r [int]

    ./outCUBE -i dataset.txt -q query.txt -k [int] -M [int] -probes [int] -o output.txt -N [int] -r [int]

    ./outCLUSTER -i dataset.txt -c cluster.conf -o output.txt complete(optional) -m [string]

  ```

## Key Classes:

- **item**: Represents a vector with an id and coordinates.
- **Hi**: Represents h functions with unique t, w, and v values.
- **Gi**: Represents g functions with unique k, w, h functions, and r values.
- **HashTable and HashNode**: Custom hash table implementation.
- **Hash**: Structure for LSH algorithm.
- **HyperCube**: Structure for Hypercube algorithm.
- **Clustering and Cluster**: Structures for Clustering algorithm.

## General Approach:

- **LSH**: Create a Hash, read vectors, hash them, and answer queries.
- **Hypercube**: Similar to LSH, but uses a HyperCube structure.
- **Clustering**: Initializes and processes using functionality() which calls kMeansPP, Assign, and Silhouette().
