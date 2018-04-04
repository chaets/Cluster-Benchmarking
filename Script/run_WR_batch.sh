#!/bin/bash

for FILE in run_WR1.slurm run_WR2.slurm run_WR4.slurm run_WR8.slurm run_WR16.slurm run_WR32.slurm run_WR64.slurm run_WR128.slurm
do
	sbatch $FILE
done
