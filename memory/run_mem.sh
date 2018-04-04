#!/bin/bash

echo 'Workload	Concurrency	BlockSize	MyRAMBenchValue	TheoreticalValue	MyRAMBenchEfficiency'

./MyRAMBench memory-RWR-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-2thread.dat >> Out.txt	
./MyRAMBench memory-RWS-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-2thread.dat >> Out.txt	
./MyRAMBench memory-RWS-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWR-1-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-10000000-2thread.dat >> Out.txt	
./MyRAMBench memory-RWS-10000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1000-4thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-1thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-2thread.dat >> Out.txt
./MyRAMBench memory-RWS-1-4thread.dat >> Out.txt


