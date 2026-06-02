# Fortress Defense

A selected competitive programming solution from a Chinese Informatics Olympiad problem set.

* **Difficulty:** 2200
* **Topics:** Shortest Path, Dijkstra, Edge Deletion, Segment Tree

## Problem Summary

Given a weighted undirected graph, remove exactly one edge so that the shortest distance from vertex `1` to vertex `n` becomes as large as possible. Also count the number of edge removals achieving this value.

## Solution Idea

I first extract a shortest path from `1` to `n`. Then alternative routes bypassing segments of this path are processed with a **segment tree** to allow the best distance after deleting each shortest path edge to be computed efficiently.

The reduction is highly creative and the implementation is non-trivial.

## Files

```text
solution dijkstra.cpp      # Optimized solution
tests/            # Generated tests
```

This repository contains my implementation and generated tests for reference.
