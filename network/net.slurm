#!/bin/bash

#SBATCH --nodes=1
#SBATCH --tmp=15G
#SBATCH --output=./output/DiskReadThroughput.out
#SBATCH --wait-all-nodes=1

srun ./run_net.sh $SLURM_JOB_NODELIST
