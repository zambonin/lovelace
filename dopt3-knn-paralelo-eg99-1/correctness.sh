#!/bin/bash

EXEC=./run_knn.py

${EXEC} tests/Fisher_dataset.csv tests/Fisher_testset.csv output.csv 5
diff output.csv tests/Fisher_output.csv
${EXEC} tests/average_dataset.csv tests/average_testset.csv output.csv 13
diff output.csv tests/average_output.csv
