#!/bin/bash

EXEC=./nqueens

diff <(${EXEC} <<< 8) <(echo "Solutions = 92")
diff <(${EXEC} <<< 4) <(echo "Solutions = 2")
diff <(${EXEC} <<< 3) <(echo "Solutions = 0")
diff <(${EXEC} <<< 12) <(echo "Solutions = 14200")
