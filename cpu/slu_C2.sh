

#!/bin/bash

for file in 7.slurm 8.slurm 12.slurm 9.slurm 10.slurm 11.slurm
do
	sbatch $file
done