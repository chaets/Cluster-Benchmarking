## Compile

make all

########### CPU Benchmark Input ###########

<workload type (QP, HP, SP, DP)>
<number of threads (1,2,4)>
###### Compile #####

make all

########### CPU Benchmark ###########

1.Run Makefile
2.Run the run.slurm file with command "sbatch run.slurm"
3.It will run the frun_cpu.sh file with all the input parameters.
4.Refer the output folder for the out put as required.

########### Linpack Benchmark ###########

1.Unpack the Linpack package on cluster.
2.Edit the lininput_xeon64 to enter the number of tests, problem size, memory size and
number of threads as shown below.
3.Create the script to Linpack
4.Run the script
5.Look for the result in the slurm*.out file generated for verification.

Linpack Benchmark –  
 
1.	Unpack the Linpack package on cluster  
  
2.	Edit the lininput_xeon64 to enter the number of tests, problem size, memory size and number of threads. 
  
3.	Create the script to Linpack . 
  
 
4.	Run the script . 
  
 
5.	Look for the result in the slurm*.out file generated for verification. 
  
 
 
