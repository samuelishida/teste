#include <stdio.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef char bool;

/*second*/

void cls()
{
	#ifdef __unix__
		system("clear");
	#elif _WIN32
		system("cls");
	#endif
}

int contNum(int num, int board[6][6])
{
	int i, j, cont=0;
	
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			if(board[i][j] == num) cont++;
	
	return cont;
}

int random(int board[6][6])
{
	int num;
	
	do
	{
		num = rand()%18 + 1;
	}while(contNum(num,board) >= 2);
	
	return num;
}

void printBoard(int board[6][6], int hits[6][6], int x1, int y1, int x2, int y2, int contHits, int contErr)
{
	int i, j;
	
	for(i=0; i<4; i++)
		printf(" ");
	for(i=0; i<6; i++)
		printf("%2d ",i+1);
	printf("\n");
	
	
	
	for(i=0; i<2; i++)
		printf(" ");
	for(i=0; i<=21; i++)
		printf("%c",220);
	printf("\n");
	
	
	
	for(i=0; i<6; i++)
	{
		printf("%d %c ",i+1,219);
		
		for(j=0; j<6; j++)
		{
			if( hits[i][j] || (x1 == i && y1 == j) || (x2 == i && y2 == j) )
				printf("%2d ",board[i][j]);
			else
				printf(" x ");
		}
		
		printf(" %c \n",219);
	}
	
	
	for(i=0; i<2; i++)
		printf(" ");
	for(i=0; i<=21; i++)
		printf("%c",223);
	
	printf("\n");
	
	printf("Hits:   %3d\n",contHits);
	printf("Misses: %3d\n\n",contErr);
}

bool game(int hits[6][6])
{
	int i, j;
	
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			if(!hits[i][j]) return TRUE;
}

int main(int argc, char *argv[]) 
{
	int i, j, board[6][6], hits[6][6], k, l, contHits=0, contErr=0, level;
	char in1[127], in2[127];
	time_t t;
	
	/* Creates a seed for rand() */
	srand(time(NULL));
	
	/* Creates the edges with the coordinates */
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			board[i][j] = random(board);
			
	cls();
	
	printf("Select a level (1-3): ");
	scanf("%d",&level);
			
	t = time(NULL);
	
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			hits[i][j] = TRUE;
	
	printBoard(board,hits,-1,-1,-1,-1,contHits, contErr);
	
	/* Wait 5*levels seconds */
	while(difftime(time(NULL),t) <= 5*level);
	
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			hits[i][j] = FALSE;
	
	cls();
	
	
	while(game(hits))
	{		
		printBoard(board,hits, -1, -1, -1, -1, contHits, contErr);
		
		printf("Enter a line and column: ");
		scanf("%s %s", in1, in2);
		
		/* Conerts string to int */
		i = atoi(in1) - 1;
		j = atoi(in2) - 1;
		
		cls();
		
		if(i > 6 || j > 6 || i < 0 || j < 0 || hits[i][j])
			continue;
		
		printBoard(board,hits, i, j, -1, -1,contHits, contErr);
		
		printf("Enter a line and column: ");
		scanf("%s %s", in1, in2);
		
		k = atoi(in1) - 1;
		l = atoi(in2) - 1;
		
		if(k > 6 || l > 6 || k < 0 || l < 0 || hits[k][l])
			continue;
		
		t = time(NULL);
		
		if( !(k == i && l == i))
		{
			if(board[i][j] == board[k][l] && !hits[i][j])
			{
				hits[i][j] = TRUE;
				hits[k][l] = TRUE;
				contHits++;
			}
			else
			{
				cls();
				printBoard(board,hits,i,j,k,l,contHits, contErr);
				
				printf("Press enter to continue...");
				
				/* Clear input buffer */
				fseek(stdin,0,SEEK_END);
				
				fgetc(stdin);
				
				fseek(stdin,0,SEEK_END);
				
				while(difftime(time(NULL),t) <= 2);
				
				contErr++;
			}
		}
		
		cls();
	}
	

    return 0;
}