# Cluster-Benchmarking
Cluster Benchmarking of CPU, RAM, I/O and network using C
Read benchmarking specific folder for readme details

# INTRODUCTION
Benchmarking of the components of the processor, memory, network and hard disk is complete. Several experiments are performed on different parameters. Three tests for each experiment are completed, and the mean and average deviation of the results is mentioned. Each experiment takes several seconds to reduce the effect of the initial load or any other system noise. The general values are used on the graphs. This document illustrates the design strategy for CPU / memory / disk/ network and has a corresponding section under each of them, showing diagrams / trends. 
## GENERAL POINTS
We have created a single interface for calling all test checks based on command line parameters. Benchmarking code for memory, network and disk is written in C language and CPU is written in C programming. 

