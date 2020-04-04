# interdyck_graph_reduce
An implementation for interdyck graph reduction

## Input format
The implementation accept a graph input similar to a dot format. An edge should be represented as

0->1[label="ob--1"]

0 and 1 are the vertex ids and the in the label "ob--1", "o" means open bracket, 
an alternative choice is c, meaning close bracket.
"b" means the label of the edge is a bracket, an alternative is "p", meaning parenthesis. 
"--1" means the index of the bracket/parenthesis is 1.

## Usage
copy your dot file and name it as "current.dot" in the directory

run ./graph_reduce.sh

## Example
```
cp example/example.dot current.dot
./graph_reduce.sh
```

Then resulting graph is in current.dot
