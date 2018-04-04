#!/bin/bash

echo 'Workload	Concurrency	MyCPUBenchValue	TheoreticalValue		Efficiency'

./MyCPUBench cpu_DP_1thread.dat >> out.txt
