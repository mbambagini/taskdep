Introduction
============

This tool generates task graph, modeling precedence constraints among tasks
and communication requirements.

A task is formally defined by:
- edges, representing tasks. A specific worst-case computational time
  features each task
- vertices, representing precedence constraints among tasks. Each of them is
  characterized by the amount of exchanged data.
  Such dependencies are represented as: a -> b. Meaning that the task b must
  start not earlier than the end of task a.


Required packages
=================

Required libraries:
- GFlags Library: http://code.google.com/p/gflags/
- Protobuf Library: http://code.google.com/p/protobuf/

Suggested software:
- Graphviz: http://www.graphviz.org/


How to
======

Compile:
```
make
```

Once the software has been compiled, execute:
```
./software --binaryFile BINARY_OUTPUT_FILE [OPTIONS]
                        ==================
```
where:
- binaryFile: Binary file with the generated task graph (string)
- plainTextFile: Plain text with the generated task graph (string)
- graphvizFile: DOT file with the generated task graph (string)
- maxWcet: Maximum Worst-Case Execution Time (int32)
- minWcet: Minimum Worst-Case Execution Time (int32)
- maxExchangedData: Maximum amount of exchanged data (int32)
- minExchangedData: Minimum amount of exchanged data (int32)
- dependencyDistance: Maximum dependency distance (int32)
- nOfDependencies: Number of Dependencies (int32)
- nOfTasks (Number of tasks) type: int32 default: 15
- probSeqPar (Ser/Par probability [0, 1]) type: double default: 0.5
- taskGenerator: Task generator to use:
-- 0: code-style generator
-- 1: data-flow generator												1

In case you want to regenerate source files for the serialization:
```
make gen
```



Compile:

___
make
___


Other software
=============

Alternative software that you would like to test:
- TGFF: http://ziyang.eecs.umich.edu/~dickrp/tgff/
- STG: http://www.kasahara.elec.waseda.ac.jp/schedule/
- TaskGraphGenerator: http://sourceforge.net/projects/taskgraphgen/
- http://ai.unibo.it/node/410
