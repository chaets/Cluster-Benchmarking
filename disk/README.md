###### Compile ######

make all

########### Disk Benchmark Input ###########

<mode (RS WS RR WR)>
<block size (1KB, 1000KB, 10000KB, 100000KB)>
<number of threads (1,2,4)> # For throughput
<number of threads (1,2,4,8,16,32,64,128)> # For latency



make all

########### Disk Benchmark ###########

1.Run Makefile it will create MyRAMBench 
2.Run the 1.slurm file with command "sbatch 1.slurm"
3.It will run the run_disk.sh file with all the input parameters.
4.Refer the output folder for the out put as required.

IOZONE Benchmark 
1.	Download the iozone on your desktop and unpack it. 
2.	Move the Unpacked iozone package to the cluster. 
3.	Run the following command to enter the interactive mode on cluster. 
srun -n 1 -p interactive –pty /bin/bash 
4.	Build the script to run the following command or else run the command directly. 
 
iozone -R -l 2 -u 2 -r 4k -s 100m | tee -a /tmp/iozone_results.txt 
where -l is lower bound on no of threads to run, -u upper bound on no of threads to run, -r is record size, -s is the size of the file and iozone_results.txt stores the results of benchmark in file. 
  
5.	Look for the console output. 
6.	Once the command is done performing its operation, look for the results stored in the file iozone_results.txt.  
7.	Iteratively peform the tests for the different block sizes and given number of threads by modifying the paramters in command stated in step 4. 
