#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posx;
    int posy;
    int velx;
    int vely;
} Particle;

void simulateParticle(FILE *in, FILE *out) {

    //move all particles FIRST
    //check final positions and see if one xy pos == another particles xy pos
    
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

    
    
    //particle maker
    // Particle p [100];
    // p[0].posx = 5;
    // printf("%d\n", p[0].posx);

    return 0;
}