#!/bin/bash

echo 'Workload	Concurrency	BlockSize	MyDiskBenchThroughput	TheoreticalThroughput	Efficiency'

./MyDiskBench disk-WR-100000-1thread.dat >> Output.txt

