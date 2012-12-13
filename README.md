Introduction
============

This tool generates task graph, modeling precedence constraints among tasks
and communication delays.

A task is formally defined by:
- edges, representing tasks. A specific worst-case computational time
  features each task
- vertexs, representing precedence constraints among tasks. Each of them is
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

Re-generate source files for the serialization:
    make gen
  
Compile:
    make


Other software
=============

TGFF: http://ziyang.eecs.umich.edu/~dickrp/tgff/
