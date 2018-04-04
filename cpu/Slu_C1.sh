

#!/bin/bash

for file in 1.slurm 2.slurm 3.slurm 4.slurm 5.slurm 6.slurm
do
	sbatch $file
done