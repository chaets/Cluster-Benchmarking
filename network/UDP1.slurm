#!/bin/bash

#SBATCH --nodes=2
#SBATCH --ntasks=2

#SBATCH --output=./output/DiskReadThroughput.out
#SBATCH --wait-all-nodes=1

srun ./sh_UPD1.sh $SLURM_JOB_NODELIST
