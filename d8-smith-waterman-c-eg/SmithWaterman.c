
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t read_file(const char* filename, char** buffer);
int32_t compute_sw(const char* first_seq, const char* second_seq, uint32_t rows, uint32_t columns);

int32_t compute_sw(const char* first_seq, const char* second_seq, uint32_t rows, uint32_t columns) {
    // Creates a score matrix with the local alignment scores.
    // Returns the best alignment score found.
    int32_t max_score = 0;
    int32_t* score_matrix = malloc(columns * rows * sizeof(int32_t));
    // Initialize score_matrix with 0s at light speed
    memset(score_matrix, 0, columns * rows * sizeof(int32_t));

    int_fast8_t similarity;
    int_fast32_t up, diagonal, left, score, temp_score;

    // Computes the alignment scores
    for (uint32_t i = 1; i < rows; ++i) {
        int_fast8_t first = first_seq[i-1];
        for (uint32_t j = 1; j < columns; ++j) {
            similarity = first == second_seq[j-1] ? 2 : -1;
            diagonal = score_matrix[(i - 1) * columns + j - 1] + similarity;
            up = score_matrix[(i - 1) * columns + j] - 1;
            left = score_matrix[i * columns + j - 1] - 1;

            // Score is calculated in two different variables for profit
            score = up > 0 ? up : 0;
            temp_score = left > diagonal ? left : diagonal;
            if (temp_score > score) {
                score = temp_score;
            }

            score_matrix[i * columns + j] = score;

            if (score > max_score) {
                max_score = score;
            }
        }
    }

    free(score_matrix);

    return max_score;
}

uint32_t read_file(const char* filename, char** buffer) {
    FILE * file = fopen(filename, "rb");
    uint32_t length = 0;
    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        *buffer = malloc(length * sizeof(char));
        if (*buffer) {
            fread(*buffer, 1, length, file);
        }
        fclose(file);
    }
    return length;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Wrong number of parameters!\n");
        exit(1);
    }

    char * base1 = 0;
    char * base2 = 0;
    uint32_t length1 = read_file(argv[1], &base1);
    uint32_t length2 = read_file(argv[2], &base2);

    if (!base1 || !base2) {
        fprintf(stderr, "Could not allocate buffers!\n");
        return -1;
    }

    int32_t score = compute_sw(base1, base2, length1, length2);

    free(base1);
    free(base2);

    printf("Max Score is %d\n", score);
}
