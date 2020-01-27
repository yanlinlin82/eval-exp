# Evaluate Expression

## Introduction

There are two algorithms for evaluating an expression:

* [stack.cpp](stack.cpp) - by stack
* [recursive.cpp](recursive.cpp) - by recursive function

## Quick Usage

```sh
$ g++ stack.cpp && ./a.out
infix   : 1*(2+3/4)
postfix : 1234/+*
evaluate: 2
```

```sh
$ g++ recursive.cpp && ./a.out
infix   : 1*(2+3/4)
evaluate: 2
```

## Reference

* <https://www.tutorialspoint.com/data_structures_algorithms/expression_parsing_using_statck.htm>
* <https://en.wikipedia.org/wiki/Recursive_descent_parser>
* <https://en.wikipedia.org/wiki/Parsing_expression_grammar>
