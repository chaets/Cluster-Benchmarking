###### Compile #####

make all

########### Network Benchmark ###########

<mode (TCP UDP)>
<block size (1B, 1KB, 32KB)> # in bytes 1, 1000, 32000
<number of threads (1,2,4,8)>


########### Network Benchmark ###########

1.Run Makefile
2.Run the net.slurm file with command "sbatch net.slurm"
3.It will run the run_net.sh file with all the input parameters inside the single core.
4.Refer the output folder for the out put as required.


IPERF Benchmark 
1.	Create the script as shown below onto cluster to run iperf benchmark. This script creates the server. Which will keep listening for incoming connections.  
2.	Check whether the server is listening using squeue on cluster.   
3.	You can also check for the status of the server in output file.   
4.	Now create the script for the client to connect to the server.  
5.	Now check whether the client is connected to the server in the output file generated.  
6.	Look for the speed of the network i.e 1.75 GBytes 
