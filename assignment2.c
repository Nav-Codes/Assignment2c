#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posx;
    int posy;
    int velx;
    int vely;
    int currentSteps;
    // Particle *next;
} Particle;

void simulateParticle(FILE *in, FILE *out, Particle *Ps, int seconds, int numParticles, int rows, int cols) {

    //move all particles FIRST
    //check final positions and see if one xy pos == another particles xy pos

    for (int i = 0; i < seconds; i++) {
        for (int j = 0; j < numParticles; j++) {
            printf("%d: [%d][%d][%d][%d]\n", j+1, Ps[j].posx, Ps[j].posy, Ps[j].velx, Ps[j].vely);
            if (Ps[j].currentSteps > 0) {
                if (Ps[j].posx + Ps[j].velx == -1 || Ps[j].posx + Ps[j].velx == cols - 1){
                    Ps[j].velx *= -1;
                }
                if (Ps[j].posy + Ps[j].vely == -1 || Ps[j].posy + Ps[j].vely == rows - 1){
                    Ps[j].vely *= -1;
                }
            }
            Ps[j].posy += Ps[j].vely;
            Ps[j].posx += Ps[j].velx;
            //printf("%d: [%d][%d][%d][%d]\n", j+1, Ps[i].posx, Ps[i].posy, Ps[i].velx, Ps[i].vely);
        }
        
        
        // for (int p = 0; p < numParticles; p++) {
        //     if (Ps[p].posx == NULL || Ps[p].posy == NULL) {
        //         continue;
        //     }
        //     for(int q = 0; q <= numParticles; q++) {
        //         if (p == q) {
        //             continue;
        //         }
        //         if ( Ps[q].posx == NULL ||  Ps[q].posy == NULL) {
        //             continue;
        //         }
        //         if (Ps[p].posx == Ps[q].posx && Ps[p].posy == Ps[q].posy) {
        //             Ps[p].posx = NULL;
        //             Ps[p].posy = NULL;
        //             Ps[q].posx = NULL;
        //             Ps[q].posy = NULL;
        //         }
        //     }
        // }


    }
    
}

void particleMaker(FILE *in) {

}

//struct creation and

int main(int argc, char **argv) {
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    int rows;
    fscanf(in, "%d", &rows);
    rows += 2;

    int cols;
    fscanf(in, "%d", &cols);
    cols += 2;

    int seconds;
    fscanf(in, "%d", &seconds);


    printf("%d\n", rows);
    printf("%d\n", cols);
    printf("%d\n", seconds);

    char **grid = malloc(sizeof(char*) * rows);
    for (int i = 0; i < cols; i++) {
        grid[i] = malloc(sizeof(char) * cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = '0';
        }
    }

    

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                grid[i][j] = '1';
            }
        }
    }
    for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%c", grid[i][j]);
            }
            printf("\n");
    }
    printf("\n");

    //calculate how many particles there are
    char buff[10];
    int numParticles;
    while (fgets(buff, 10, in) != NULL) {
        numParticles++;
    }

    //initializes Particles array
    fseek(in, 5, SEEK_SET);
    Particle Ps [numParticles];
    int number = 0;
    while (fscanf(in, "%d, %d, %d, %d", &Ps[number].posx, &Ps[number].posy, &Ps[number].velx, &Ps[number].vely) == 4) {
        printf("[%d][%d][%d][%d]\n", Ps[number].posx, Ps[number].posy, Ps[number].velx, Ps[number].vely);
        number++;
    }

    simulateParticle(in, out, Ps, seconds, numParticles, rows, cols);



    return 0;
}