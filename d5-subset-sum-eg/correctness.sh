#!/bin/bash

EXEC=./subsum

diff <(${EXEC} 30 100 146 20) <(echo "Number of subsets = 1343")
diff <(${EXEC} 32 1000 2000 1) <(echo "Number of subsets = 870")
