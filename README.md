# Graph Simplification for Interleaved Dyck-Reachability
This repostory contains an implementation of the paper
- Yuanbo Li, Qirun Zhang, Thomas Reps. Fast Graph Simplification for Interleaved Dyck-Reachability. In *PLDI 2020*.
## Interleaved Dyck language
The implementation currently supports the interleaved Dyck language of two Dyck lauanges representing Brackets and Prernetheses, respectively.

## Input format
The implementation accepts an input graph in the dot format. A labeled edge is encoded as
```
0->1[label="ob--1"]
```
 - 0 and 1 are the vertex ids;
 - "ob" means an open bracket. Similarly, we have "cb" for a close bracket, "op" for an open parenthesis, and "cp" for an close parenthesis;
 - "--1" means the index of the bracket/parenthesis is 1.

## Usage
copy your dot file and name it as "current.dot" in the directory

run ./graph_reduce.sh

## Example
``example/example.dot`` contains the motivation example (Figure 1b) in the PLDI 2020 paper.
```
cp example/example.dot current.dot
./graph_reduce.sh
```

The resulting graph is in current.dot
