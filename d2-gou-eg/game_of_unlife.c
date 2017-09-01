/* Game of Unlife - based on Conway's Game of Life
 * by llpilla - laercio.pilla@ufsc.br
 * Execution returns the number of iterations with people alive */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef uint32_t bool;
#define true 1
#define false 0

#define UNDEAD 2        //cell with someone undead
#define ALIVE 1         //cell with someone alive
#define DEAD 0          //cell with someone dead or just empty

/* display: prints the current state of the universe */
void display(void *u, uint32_t w, uint32_t h) {
	uint32_t (*univ)[w] = u;
    uint32_t x, y;
	printf("\033[2J"); //clears the screen
	printf("\033[H"); //moves the cursor to the upper-left corner of the screen

    for (y = 0; y < h; y++) { //for all lines
        for (x = 0; x < w; x++){ //for all columns
            uint32_t cell = univ[y][x];
            if (cell == DEAD) printf(" ");
            else if (cell == ALIVE) printf("\033[33mP"); //yellow people
            else printf("\033[36mU"); //cyan undead
        }
        printf("\033[E");
	}
	fflush(stdout);
}

/* evolve: computes one iteration of the game and evolves the universe */
void evolve(void *u, uint32_t w, uint32_t h) {
	uint32_t (*univ)[w] = u;
	uint32_t new[h][w];
    int x, y, x1, y1;

    // computes the evolution of all cells in the universe
    for (x = 0; x < w; x++){
        for (y = 0; y < h; y++){
            // iterates over the neighborhood of the cell (3x3)
	        uint32_t alive = 0, undead = 0; //number of 'people' around
	        for (x1 = x - 1; x1 <= x + 1; x1++){
	            for (y1 = y - 1; y1 <= y + 1; y1++){
                    // checks if the cell is inside the matrix
                    if (y1 >= 0 && y1 < h && x1 >= 0 && x1 < w){
   	                    if (univ[y1][x1] == ALIVE) alive++; //another neighbor alive
                        else if (univ[y1][x1] == UNDEAD) undead++; //oh no! another undead neighbor
                    }
                }
            }
#ifdef DEBUG
    fprintf( stderr, "univ[%u][%u] state %u alive=%u undead=%u\n", y, x, univ[y][x], alive, undead );
#endif
            // now we can check the situation of the cell
            if (univ[y][x] == ALIVE){
                /* Possible results (in order)
                 * if surrounded by two or more undeads, then becomes devoured (DEAD)
                 * if it has one undead neighbor but is in a group of three, continues fighting (ALIVE)
                 * if it has one undead neighbor and is alone or with one colleague only, becomes undead (UNDEAD)
                 * if there is no undead but is in a group of 5 or more, then dies from overcrowding (DEAD)
                 * else just stays alive (ALIVE)
                 * */
                if (undead > 1) new[y][x] = DEAD;
                else if ((undead == 1) && (alive > 2)) new[y][x] = ALIVE;
                else if ((undead == 1) && (alive <= 2)) new[y][x] = UNDEAD;
                else if (alive > 4) new[y][x] = DEAD;
                else new[y][x] = ALIVE;
            } else if (univ[y][x] == UNDEAD){
                /* Possible results (in order)
                 * if surrounded by four or more survivors, then it is destroyed (DEAD)
                 * if surrounded by three survivors but has other two colleagues, keeps attacking (UNDEAD)
                 * if it finds itself in a group of 5 or more undead, then starves (DEAD)
                 * else just stays undead (UNDEAD)
                 * */
                if (alive > 3) new[y][x] = DEAD;
                else if ((alive == 3) && (undead == 3)) new[y][x] = UNDEAD;
                else if (undead > 4) new[y][x] = DEAD;
                else new[y][x] = UNDEAD;
            } else {
                /* Possible results (in order)
                 * if three survivors are around, then they find a survivor (ALIVE)
                 * if three or more undead are around, then they raise a new undead (UNDEAD)
                 * else just stays dead or empty (DEAD)
                 * */
                if (alive == 3) new[y][x] = ALIVE;
                else if (undead > 2) new[y][x] = UNDEAD;
                else new[y][x] = DEAD;
            }
	    }
    }

    //copies data from the new universe to the current universe
    for (x = 0; x < w; x++){
        for (y = 0; y < h; y++){
	        univ[y][x] = new[y][x];
        }
    }
}

/* checkForSurvivors: checks if there is still anyone alive */
bool checkForSurvivors(void *u, uint32_t w, uint32_t h) {
	uint32_t (*univ)[w] = u;
    uint32_t x, y;
    bool survivors = false;

    for (x = 0; x < w; x++)
        for (y = 0; y < h; y++)
            if (univ[y][x] == ALIVE) survivors = true;

    return survivors;
}

/* initialize: creates the universe
 * Changes in this function can lead to different results. */
void initialize(void *u, uint32_t w, uint32_t h, uint32_t seed) {
	uint32_t (*univ)[w] = u;
    uint32_t x, y;
    srand(seed);

    for (y = 0; y < h; y++){
        for (x = 0; x < w; x++){
            /* Cell initial configuration probabilities:
             * P(ALIVE) =  0.5
             * P(DEAD) = 0.45
             * P(UNDEAD) = 0.05 */
            uint32_t status = rand() % 100;
            if (status < 50) univ[y][x] = ALIVE;
            else if (status < 95) univ[y][x] = DEAD;
            else univ[y][x] = UNDEAD;
        }
    }
}

/* game: simulates the whole game */
uint32_t game(uint32_t w, uint32_t h, uint32_t max_iterations, uint32_t seed) {
	uint32_t univ[h][w];
    uint32_t i;

    // First we get the initial setup of the universe
    initialize(univ, w, h, seed);
    // Then we iterate over it
    for (i = 0; i < max_iterations; i++) {
#ifdef DEBUG
	    display(univ, w, h);
	    usleep(1000000);
#endif
        if (!checkForSurvivors(univ, w, h)) break;   //stops iterating if everyone is dead
#ifdef DEBUG
    fprintf( stderr, "Iteration %u\n", i );
#endif
	    evolve(univ, w, h);
	}
    return i;
}

int main(int argc, char **argv)
{
    /* w = width of the universe
     * h = height of the universe
     * iter = maximum number of iterations
     * seed = pseudo-random number generator seed */
	uint32_t w = 5, h = 5, iter = 10, seed = 26;

    if (argc > 1) iter = atoi(argv[1]);
	if (argc > 2) w = atoi(argv[2]);
	if (argc > 3) h = atoi(argv[3]);
    if (argc > 4) seed = atoi(argv[4]);

    uint32_t survival_time = game(w, h, iter, seed);
    printf("%u\n",survival_time); //prints the number of iterations with people alive

}
