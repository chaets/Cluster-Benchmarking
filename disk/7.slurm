#!/bin/bash

#SBATCH --nodes=1
#SBATCH --tmp=15G
#SBATCH --output=./output/DiskReadThroughput.out
#SBATCH --wait-all-nodes=1

srun ./d7.sh $SLURM_JOB_NODELIST
