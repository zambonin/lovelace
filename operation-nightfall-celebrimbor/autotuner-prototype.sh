EXEC_FILE="matmult"
Compilers=$1
Flags=$2
Steps=$3

time_c = 0
for c in Compilers; do
   $c mm.c $Flags -o $EXEC_FILE
done

chosen_compiler=

for f in Flags; do

done

for s in Steps; do

done
