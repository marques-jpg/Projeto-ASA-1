# Protein Chain Energy Maximizer

## Overview
This repository contains the implementation of the first project for the Analysis and Synthesis of Algorithms (ASA) class. 

The project solves an optimization problem based on a virtual reality game. The goal is to remove amino acids from a chain in a way that maximizes the total released energy. The challenge focuses on designing an efficient algorithm that processes the optimal removal sequence within strict time and memory limits.

## Problem Description and Rules
The energy released when removing an amino acid $a_i$ from a protein is calculated based on three factors:
1. The potential energy of the removed amino acid ($P_i$).
2. The potential energy of the two closest neighboring amino acids ($P_{i-1}$ and $P_{i+1}$).
3. The biochemical affinity between the class of the amino acid and its neighbors (which can be Polar `P`, Non-Polar `N`, Acid `A`, or Base `B`).

The formula to calculate the energy of each removal is given by:
$$E_{libertada} = P_{i-1} \times Af(C(i-1), C(i)) \times P_{i} + P_{i} \times Af(C(i), C(i+1)) \times P_{i+1}$$


**Important Notes:**
* The affinities between classes are defined through an asymmetric table.
* The logical ends of the chain (positions 0 and $n+1$) act as fixation points. They belong to a special Terminal (`T`) class, have a potential energy of 1, and are completely neutral in any interaction ($Af(T, c) = Af(c, T) = 1$).

## Data Format

### Input
The program reads from *standard input* and expects the following format structured in three lines:
1. An integer $n \ge 1$, representing the total number of amino acids in the sequence.
2. A sequence of $n$ positive integers (space-separated), corresponding to the potential energy of each amino acid.
3. A sequence of $n$ characters (no spaces), denoting the biochemical classes (`P`, `N`, `A`, or `B`).

### Output
The program writes to *standard output* the following information:
1. **First line:** The maximum possible total released energy.
2. **Second line:** The exact removal sequence of the amino acids (represented by space-separated indices) that yielded the maximum gain. If multiple optimal sequences exist, the algorithm guarantees the presentation of the lexicographically smallest sequence.

## Installation and Execution

### Prerequisites
The implementation was developed in C++ (C++11 standard). It is strongly recommended to compile with the `-O3` optimization flag to ensure the best execution time, strictly complying with the Mooshak evaluation system limits.

### Compilation
```bash
g++ -std=c++11 -O3 -Wall projeto25.cpp -lm -o projeto
