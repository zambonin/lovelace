#!/bin/bash

EXEC=./subsum

diff <(${EXEC} 300 138000 58820 1) <(echo "Number of subsets = 1233")
