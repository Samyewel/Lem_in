# Lem-in

## Table of Contents
- [Introduction](#introduction)
- [Goal](#goal)
- [Algorithm](#algorithm)
- [Usage](#usage)
- [Reflections](#reflections)
- [Example](#example)

---

## Introduction

**Lem-in** is a graph traversal project designed as part of the 42 School curriculum. The objective is to find the most efficient way to move a set number of ants from a starting room to an ending room in a graph where rooms are connected by tunnels.

This project teaches pathfinding algorithms, optimization techniques, and handling edge cases in complex problem-solving.

This was a shared project between egaliber and Samyewel.

---

## Goal

The goal of the **Lem-in** project is to efficiently find multiple paths through a graph and move ants from a starting point to an endpoint while minimizing the total number of turns.

You are provided with a map of rooms connected by tunnels, with ants that need to travel from a `start` room to an `end` room. Your task is to:

1. Parse the map input.
2. Find the optimal paths to move all ants.
3. Display the movements in the minimum number of steps.

---

## Algorithm

To solve the **Lem-in** project, a combination of graph traversal algorithms, such as **Breadth-First Search (BFS)** and **Edmonds-Karp**, are used. The key steps are:

1. **Input Parsing**: Read and validate the map from standard input.
2. **Pathfinding**: Implement a BFS to find all available paths.
3. **Flow Management**: Use flow-based algorithms (like Edmonds-Karp) to manage the movement of ants along multiple paths while avoiding collisions.
4. **Ant Movement**: Distribute the ants across the found paths, ensuring that their movement minimizes the total number of turns.

Edge cases, such as isolated rooms or invalid maps, should be handled gracefully.

---

## Usage

Run the program with a map file:

bash

`./lem-in < map_file`

You can also pipe input:

`cat map_file | ./lem-in`

The eval_tests folder contains a makefile with plenty of tests for you to run and allows for easier usage than just command line entries.

---

## Reflections

Lem-in was easily the most challenging yet insightful project I faced during my time at 42. I had spent weeks attempting to brute-force the path flows in order to find the simplest, but this led to incredibly long runtimes in a project that asks for 12 seconds or less for solutions - this led to a lightbulb moment (me finally realising why Edmonds-Karp is so useful in the first place!).

---

## Credits

- For demonstration purposes, I am using azajay08's beautiful little visualiser!
- egaliber, for the great job on creating the functions to print the ant output.
- 42 for the eye-opening project creation.