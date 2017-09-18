#!/bin/bash

EXEC=./mm

${EXEC} tests/matrix_1 tests/matrix_2 result
diff result tests/matrix_1x2
${EXEC} tests/big_matrix_1 tests/big_matrix_2 big_result
diff big_result tests/big_matrix_1x2
