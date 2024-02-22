#include <stdio.h>
#include <stdlib.h>

//A01362009
//A01362704
//A01215993
//A01316524

typedef struct {
    int exist;
    int posx;
    int posy;
    int velx;
    int totalX;
    int vely;
    int totalY;
    int currentSteps;
    // Particle *next;
} Particle;

void printOutput(Particle *Ps, FILE *out, int rows, int cols, char ** grid) {
    // for (int j = 0; j < cols; j++) {
    //     for (int i = rows-1; i >= 0; i--) {
    //         if (grid[i][j] == '0') {
    //             fputc(' ', out);
    //         }
    //         if (grid[i][j] == '1') {
    //             fputc('*', out);
    //         }
    //         if (grid[i][j] == '2') {
    //             fputc('+', out);
    //         }
    //     }
    //     fputc('\n', out);
    // }
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         if (grid[i][j] == '0') {
    //             fputc(' ', out);
    //         }
    //         if (grid[i][j] == '1') {
    //             fputc('*', out);
    //         }
    //         if (grid[i][j] == '2') {
    //             fputc('+', out);
    //         }
    //     }
    //     fputc('\n', out);
    // }

    for(int i = rows - 1; i >= 0; i--){
        for(int j = 0; j < cols; j++){
            if (grid[i][j] == '0') {
                fputc(' ', out);
            }
            if (grid[i][j] == '1') {
                fputc('*', out);
            }
            if (grid[i][j] == '2') {
                fputc('+', out);
            }
        } if (i != 0) {
            fputc('\n', out);
        }
    }
}

void simulateParticle(FILE *in, FILE *out, Particle *Ps, int seconds, int numParticles, int rows, int cols, char ** grid) {

    int MaxVel = 0;

    //move all particles FIRST
    //check final positions and see if one xy pos == another particles xy pos
    //currentSteps used to check how many steps have been taken by a particle
    //change Ps[j].posx + Ps[j].velx == -1 to Ps[j].posx + Ps[j].velx < 0 and do it for the other if statements
    for(int i = 0; i < numParticles; i++){
        MaxVel += abs(Ps[i].velx) + abs(Ps[i].vely);
    }

    for (int i = 0; i < seconds; i++) {
        while (MaxVel > 0){
            for (int j = 0; j < numParticles; j++) {
                // printf("Before for number %d: [%d][%d][%d][%d]\n", j+1, Ps[j].posx, Ps[j].posy, Ps[j].velx, Ps[j].vely);

                //bounds checking 
                if(Ps[j].velx < 0){
                    if(Ps[j].posx - 1 == 0) {
                        Ps[j].velx *= -1;
                    }
                }
                else if (Ps[j].velx > 0){
                    if(Ps[j].posx + 2 == cols) {
                        Ps[j].velx *= -1;
                    }
                }

                if(Ps[j].vely < 0){
                    if(Ps[j].posy - 1 == 0) {
                        Ps[j].vely *= -1;
                    }
                }
                else if (Ps[j].vely > 0){
                    if(Ps[j].posy + 2 == rows) {
                        Ps[j].vely *= -1;
                    }
                }

                // if(Ps[j].posx + 1 == cols || Ps[j].posx - 1 == 0) {
                //     Ps[j].velx *= -1;
                // }

                // if(Ps[j].posy + 1 == rows || Ps[j].posy - 1 == 0) {
                //     Ps[j].vely *= -1;
                // }


                //checks if particle can move in x or y direction 
                if(Ps[j].totalX == 0 && Ps[j].totalY == 0){
                    continue;
                }

                //checks and moves it in x direction 
                if (Ps[j].totalX != 0) {
                    if(Ps[j].velx < 0){
                        Ps[j].posx -= 1;
                        Ps[j].totalX += 1;
                        MaxVel--;
                    } else {
                        Ps[j].posx += 1;
                        Ps[j].totalX -= 1;
                        MaxVel--;
                    }
                }

                //checks and moves it in y direction 
                if (Ps[j].totalY != 0) {
                    if(Ps[j].vely < 0){
                        Ps[j].posy -= 1;
                        Ps[j].totalY += 1;
                        MaxVel--;
                    } else {
                        Ps[j].posy += 1;
                        Ps[j].totalY -= 1;
                        MaxVel--;
                    }
                }


                // printf("After for number  %d: [%d][%d][%d][%d]\n", j+1, Ps[j].posx, Ps[j].posy, Ps[j].velx, Ps[j].vely);
                // printf("\n");


                // printf("%d: [%d][%d][%d][%d]\n", j+1, Ps[i].posx, Ps[i].posy, Ps[i].velx, Ps[i].vely);
            }

            //collision checker
            

        }

        for (int u = 0; u < numParticles; u++) {
            for (int p = 0; p < numParticles; p++) {
                if (u == p) {
                    continue;
                }
                else {
                    if (Ps[u].posx == Ps[p].posx && Ps[u].posy == Ps[p].posy) {
                        Ps[u].exist = 0;
                        Ps[p].exist = 0;
                    }
                }
            }
        }

        for(int i = 0; i < numParticles; i++){
            MaxVel += abs(Ps[i].velx) + abs(Ps[i].vely);
        }

        for(int i = 0; i < numParticles; i++){
            Ps[i].totalX = Ps[i].velx;
            Ps[i].totalY = Ps[i].vely;
        }
    }

    for (int i = 0; i < numParticles; i++) {
        if (Ps[i].exist == 1) {
            grid[Ps[i].posy][Ps[i].posx] = '2';
        }
    }

    for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // printf("%c", grid[i][j]);
            }
            // printf("\n");
    }
    // printf("\n");

    //prints to array
    printOutput(Ps, out, rows, cols, grid);

    // free(Ps);
    
}


void fileChecker(FILE *in, FILE *out) {
    char isError = fgetc(in);
    if (isError == 'E') {
        return;
    }

    while (isError != 'E') {
        isError = fgetc(in);
        if (isError == 'E') {
            return;
        }
        if (isError == '\n') {
            continue;
        }
        else if (isError == ',') {
            isError = fgetc(in);
            if (isError == '-') {
                isError = fgetc(in);
                if (isError < '0' || isError > '9') {
                    fputs("Error", out);
                    exit(0);   
                } else {
                    continue;
                }
            } else if (isError < '0' || isError > '9') {
                    fputs("Error", out);
                    exit(0);   
                }
        }
        else if (isError == '-') {
            isError = fgetc(in);
            if (isError < '0' || isError > '9') {
                fputs("Error", out);
                exit(0);   
            } else {
                continue;
            }
        }
        else if ((isError < '0' || isError > '9') && isError != (char)13) {
            fputs("Error", out);
            exit(0); 
        }
    } 
   

}

//struct creation and

int main(int argc, char **argv) {
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    fileChecker(in, out);
    rewind(in);

    int cols;
    fscanf(in, "%d", &cols);
    cols += 2;

    int rows;
    fscanf(in, "%d", &rows);
    rows += 2;

    if (cols - 2 == 0 || rows - 2 == 0) {
        fputs("Error", out);
        exit(0);
    }

    int seconds;
    fscanf(in, "%d", &seconds);

    // printf("%d\n", rows);
    // printf("%d\n", cols);
    // printf("%d\n", seconds);

    char **grid = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
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
                // printf("%c", grid[i][j]);
            }
            // printf("\n");
    }
    // printf("\n");

    //calculate how many particles there are
    char buff[10];
    int numParticles;
    while (fgets(buff, 10, in) != NULL) {
        numParticles++;
    }

    //initializes Particles array
    // fseek(in, 8, SEEK_SET);
    char trash[15];
    rewind(in);
    fgets(trash, 5, in);
    fgets(trash, 5, in);
    fgets(trash, 5, in);

    Particle Ps [numParticles];
    int number = 0;
    while (fscanf(in, "%d, %d, %d, %d", &Ps[number].posx, &Ps[number].posy, &Ps[number].velx, &Ps[number].vely) == 4) {
        // printf("[%d][%d][%d][%d]\n", Ps[number].posx, Ps[number].posy, Ps[number].velx, Ps[number].vely);
        Ps[number].totalX = Ps[number].velx;
        Ps[number].totalY = Ps[number].vely;
        Ps[number].posx++;
        Ps[number].posy++;
        Ps[number].exist = 1;
        if (Ps[number].posx > rows || Ps[number].posy > cols) {
            fputs("Error", out);
            exit(0);
        }
        number++;
    }

    simulateParticle(in, out, Ps, seconds, number, rows, cols, grid);

    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}