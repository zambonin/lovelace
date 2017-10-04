#!/bin/bash

EXEC=./run_knn.py

${EXEC} tests/Fisher_dataset.csv tests/Fisher_testset.csv output.csv 5
diff output.csv tests/Fisher_output.csv
