#!/bin/bash

echo 'Protocol  Concurrency BlockSize   MyNETBenchValue TheoreticalValue    MyNETBenchEfficiency'



./MyNETBench-TCP network-TCP-1000-1thread.dat 0 & ./MyNETBench-TCP network-TCP-1000-1thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1000-2thread.dat 0 & ./MyNETBench-TCP network-TCP-1000-2thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1000-4thread.dat 0 & ./MyNETBench-TCP network-TCP-1000-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1000-8thread.dat 0 & ./MyNETBench-TCP network-TCP-1000-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1-1thread.dat 0 & ./MyNETBench-TCP network-TCP-1-1thread.dat 1  >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1-2thread.dat 0 & ./MyNETBench-TCP network-TCP-2-1thread.dat 1  >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1-4thread.dat 0 & ./MyNETBench-TCP network-TCP-4-1thread.dat 1  >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-1-8thread.dat 0 & ./MyNETBench-TCP network-TCP-8-1thread.dat 1  >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-32000-1thread.dat 0 & ./MyNETBench-TCP network-TCP-32000-1thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-32000-2thread.dat 0 & ./MyNETBench-TCP network-TCP-32000-2thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-32000-4thread.dat 0 & ./MyNETBench-TCP network-TCP-32000-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-TCP network-TCP-32000-8thread.dat 0 & ./MyNETBench-TCP network-TCP-32000-8thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt

sleep 20
./MyNETBench-UDP network-UDP-1000-1thread.dat 0 & ./MyNETBench-UDP network-UDP-1000-1thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1000-2thread.dat 0 & ./MyNETBench-UDP network-UDP-1000-2thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1000-4thread.dat 0 & ./MyNETBench-UDP network-UDP-1000-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1000-8thread.dat 0 & ./MyNETBench-UDP network-UDP-1000-8thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1-1thread.dat 0 & ./MyNETBench-UDP network-UDP-1-1thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1-2thread.dat 0 & ./MyNETBench-UDP network-UDP-1-2thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1-4thread.dat 0 & ./MyNETBench-UDP network-UDP-1-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-1-8thread.dat 0 & ./MyNETBench-UDP network-UDP-1-8thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-32000-1thread.dat 0 & ./MyNETBench-UDP network-UDP-32000-1thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-32000-2thread.dat 0 & ./MyNETBench-UDP network-UDP-32000-2thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-32000-4thread.dat 0 & ./MyNETBench-UDP network-UDP-32000-4thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt
sleep 20
./MyNETBench-UDP network-UDP-32000-8thread.dat 0 & ./MyNETBench-UDP network-UDP-32000-8thread.dat 1 >> /home/chetan/cloud/cs553-pa1/network/output.txt