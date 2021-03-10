#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define SUDOKU_SIZE 9
#define true 1
#define false 0
int LOG_SEQUENCE = false;

int yes = true;

void *f_line(void *param) 
{
	int *line_p = (int *)param;
	int bools[SUDOKU_SIZE] = {0};
	for(int i = 0; i < SUDOKU_SIZE; i++){
		if (LOG_SEQUENCE == true) printf("%d ", line_p[i]);
		
	}
	if (LOG_SEQUENCE == true) printf("\n");
	
	for(int i = 0; i < SUDOKU_SIZE; i++){
		int index = line_p[i] - 1;
		if(index < 0 || index >= SUDOKU_SIZE){
			yes = false;
			break;
		}
		if(bools[index]  != 0){
			yes = false;
			pthread_exit(0);
		} 
		else if(bools[index] == 0){
			bools[index] = 1;
		} 
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int N = argc;
	if (argc < 2) {
		fprintf(stderr,"ERROR - Input file missing <b.txt>\n");
		return -1;
	}

	int board[9][9];
	FILE *fp;
	char ch;
	fp = fopen(argv[1],"r");

    if(fp == NULL){
        printf("ERROR - Could not open file.\n");
        return -1;
    }

    int f = 0, c = 0;
    while((ch = getc(fp)) != EOF){
    	int currChar = (int)ch - 48;
    	if(currChar == -38){
    		f++;
    	}
    	if(currChar > 0 && currChar < 10){
    		board[f][c % SUDOKU_SIZE] = currChar;
    		c++;
    	}
    }
    fclose(fp);

    printf("Sudoku:");
    for(int i = 0; i < SUDOKU_SIZE; i++){
    	printf("\n");
    	if(i % 3 == 0 && i > 0) printf("---------------------\n");
    	for(int j = 0; j < SUDOKU_SIZE; j++){
    		if(j % 3 == 0 && j > 0) printf("| ");
    		printf("%d ", board[i][j]);
    	}
    }

    if (LOG_SEQUENCE == true) printf("\n\nMulti-thread Verifying Sequence:\n");

	pthread_t tid[27]; 
	pthread_attr_t attr[27]; 
	for(int i = 0; i < 27; i++){
		pthread_attr_init(&attr[i]);
	}

	int *line1 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line2 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line3 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line4 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line5 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line6 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line7 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line8 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *line9 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));

	int *col1 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col2 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col3 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col4 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col5 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col6 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col7 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col8 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *col9 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));

	int *grid1 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid2 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid3 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid4 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid5 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid6 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid7 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid8 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));
	int *grid9 = (int*) malloc((SUDOKU_SIZE) * sizeof(int));

	int *lines[9]= {line1, line2, line3, line4, line5, line6, line7, line8, line9};
	int *cols[9] = {col1, col2, col3, col4, col5, col6, col7, col8, col9};
	int *grids[9] = {grid1, grid2, grid3, grid4, grid5, grid6, grid7, grid8, grid9};

	for(int index = 0; index < SUDOKU_SIZE; index++){
		for(int i = 0; i < SUDOKU_SIZE; i++){
			lines[index][i] = board[index][i];
			cols[index][i] = board[i][index];
		}
		pthread_create(&tid[index],&attr[index],f_line,(void *)lines[index]);
		pthread_create(&tid[index + 9],&attr[index + 9],f_line,(void *)cols[index]);
	}


	int g = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			int k = 0;
			for(int r = (i % 3) * 3; r < (i % 3) * 3 + 3; r++){
				for(int c = (j % 3) * 3; c < (j % 3) * 3 + 3; c++){
					grids[g][k] = board[r][c];
					k++;
				}
			}
			pthread_create(&tid[g + 18],&attr[g + 18],f_line,(void *)grids[g]);
			g++;
		}
	}

	for(int i = 0; i < 27; i++){
		pthread_join(tid[i], NULL);
	}
	if(yes == true) printf("\nCorrect Solution.\n");
	else if (yes == false) printf("\nIncorrect Solution.\n");
}