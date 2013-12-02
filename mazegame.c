// Dylan G.
// A Maze game I wrote in C
/*		
			GAME DESCRIPTION:
*******************************************************************************
In this program, I will implement a program for an Easter egg hunt in an 11x19 
maze. My program will (1) read in from an input file the maze information; (2) 
show the egg hunter’s current location; and (3) repetitively moves the egg 
hunter to the direction of his chooses until the egg is found, or the hunter 
gets lost and asks for help, or the hunter quits. My program will display 
the floor plan of the maze and a path to find the egg at the end.
******************************************************************************
*******************************************************************************
---------Important Note:----------- 
I suggest opening this file using VIM for better viewing 
(color coded,etc.)
*******************************************************************************
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE !FALSE
#define PATHWAY 300

//Prototype functions:

void getmaze(void);
void printmazefile(void);
void userinput(void);
void move (int m);
void help(void);
void regenmap(void);
void printpath(void);
void define_visited_array(void);
void check_egg_walls(void);
void check_egg_existence(void);

//declare global variables:

int position[211][6], hy, hx, c1, c2, c3, c4, steps=0, hcount, search1, search2, timer=0;
char map[23][77], path[PATHWAY], visited[23][77]; 
FILE *f1,*f2,*f3;


//************************************************************
//***************Start: main FUNCTION*************************
//************************************************************

int main(int argc, char *argv[]) {


    if ( argc < 4 ) {
        puts("You must specify the input file and two output files!");
        return EXIT_FAILURE;
    }
    else if ( argc > 4 ) {
        puts("Too many command line arguments");
        return EXIT_FAILURE;
    }

//Open input file(f1) to read and open first output(f2) file to write

f1 = fopen(argv[1], "r");
f2 = fopen(argv[2], "w");
f3 = fopen(argv[3], "w");

  if (f1 == NULL)			//safety check
  { printf("File %s cannot open!\n", argv[1]);
    exit(0);
  }

getmaze();				//create floorplan from file

printmazefile();			//print floorplan to first output file

check_egg_existence();	//check to see if the maze has an egg in it

regenmap();		//print floorplan to screen (doesn't show egg position)

define_visited_array();		//fill an array for spaces already visited

userinput();				//get user input


//close input and output files
fclose (f1);
fclose (f2);
fclose (f3);

return 0;				//Exit program
//***********************************************************
//***************End: main FUNCTION**************************
//***********************************************************
}

//***************Start: getmaze FUNCTION*********************
void getmaze(void){

static int hunterx, huntery, eggx, eggy, hy, hx;
int a, b, c, d, row, column, count1, count2;

for(a=0;a<23;a++)			//define inital map as blank spaces
	for(b=0;b<77;b++)
			map[a][b]=' ';

for (a=0; a<2; a++) {			//scan location of hunter and egg
	for(b=0; b<2; b++){
	fscanf(f1, "%d", &position[a][b]);
	if(a==0){
		if(b==0)
			huntery=position[a][b];
		else
			hunterx=position[a][b];
	}
	if(a==1){
		if(b==0)
			eggy=position[a][b];
		else
			eggx=position[a][b];
	}
	}
}
c1= 22-((huntery+1)+huntery);
c2= (hunterx*4)+2;
hy=c1;
hx=c2;
search1=c1;				//initial hunter y location 
search2=c2;				//initial hunter x location
c3= 22-((eggy+1)+eggy);
c4= (eggx*4)+2;
map[c1][c2]='T';			//character for hunter
map[c3][c4]='G';			//character for egg

for (a=2; a<211; a++) {			//scan floor plan
	for(b=0; b<6; b++){
	fscanf(f1, "%d", &position[a][b]);
	if (b==0)
		count1=position[a][b];
	if (b==1)
		count2=position[a][b];
	c=22-((count1+1)+count1);
	d=(count2*4)+2;
	if(b==2){
		if(position[a][b]==0)
			map[c][d-2]=' ';
		else
			map[c][d-2]='|';
	}
	if(b==3){
		if(position[a][b]==0){
			map[c-1][d-1]=' ';
			map[c-1][d]=' ';
			map[c-1][d+1]=' ';}
		else{
			map[c-1][d-1]='-';
			map[c-1][d]='-';
			map[c-1][d+1]='-';}
	}
	if(b==4){
		if(position[a][b]==0)
			map[c][d+2]=' ';
		else
			map[c][d+2]='|';
	}
	if(b==5){
		if(position[a][b]==0){
			map[c+1][d-1]=' ';
			map[c+1][d]=' ';
			map[c+1][d+1]=' ';}
		else{
			map[c+1][d-1]='-';
			map[c+1][d]='-';
			map[c+1][d+1]='-';}
	}
	}
}

//***************End: getmaze FUNCTION*********************
}

//**************Start: printmazefile FUNCTION**************
void printmazefile(void){
int a,b;
for (a=0;a<23;a++){
	for (b=0;b<77;b++){
		fprintf(f2,"%c",map[a][b]);}	//print original floorplan
		fprintf(f2,"\n");
}
//***************End: getmaze FUNCTION*********************
}

//**************Start: userinput FUNCTION******************
void userinput(void){
	int done;
	char ch;

	done = FALSE;
	printf("\nYou may enter 'H' for help or 'Q' to quit at any time...\n");
	while(!done)
	{
		printf("Which direction would you like to move (W/N/E/S)? ");
		ch = getchar();
		printf("\n");
		switch(ch)
		{
			case 'Q':
			case 'q':
				system("clear");
				printf("Very well...Goodbye\n********************************************************************************\n********************************************************************************\n");
				done = TRUE;	//quit program
				break;
			case 'H':
			case 'h':
				printf("\nThe computer has moved you in the correct direction!\n");
				help();
				break;
			case 'W':
			case 'w':
				move(1);
				break;
			case 'N':
			case 'n':
				move(2);
				break;
			case 'E':
			case 'e':
				move(3);
				break;
			case 'S':
			case 's':
				move(4);
				break;
			default:
				system("clear");
				regenmap();
				printf("Careful, you have an invalid entry! [Press enter to continue]");
			//	fflush(stdin);
		} /* end switch */

//check and see if the egg has been found
		
		if(c1==c3 && c2==c4){
		system("clear");
		printf("********************************************************************************\n********************************************************************************\n********************************************************************************\n\n\t      Congratulations!  You have found the egg!\n\n********************************************************************************\n********************************************************************************\n********************************************************************************\n");
		printpath();		//Print path to egg in 2'nd output file
		exit(0);
}
		ch = getchar();
	} /* end while */
//***************End: userinput FUNCTION*********************
}

//***************Start: move FUNCTION*********************

void move(int m){
int yaba, done;
char temp;
yaba=m;
done = FALSE;
while(!done){
if (yaba==1 && map[c1][c2-2] != '|'){				//Move West
		temp=map[c1][c2-4];
		map[c1][c2-4] = map[c1][c2];
		map[c1][c2] = temp;
		c2=c2-4;
	//	search2=c2;
		visited[c1][c2]=' ';
		path[steps] ='W';
		steps++;
		system("clear");
		regenmap();
		done = TRUE;
		break;
}
if(yaba==2 && map[c1-1][c2] != '-' && map[c1-1][c2-1] != '-' ){	//Move North
		temp=map[c1-2][c2];
		map[c1-2][c2] = map[c1][c2];
		map[c1][c2] = temp;
		c1=c1-2;
	//	search1=c1;
		visited[c1][c2]=' ';
		path[steps] ='N';
		steps++;
		system("clear");
		regenmap();
		done = TRUE;
		break;
	}
if(yaba==3 && map[c1][c2+2] != '|'){				//Move East
		temp=map[c1][c2+4];
		map[c1][c2+4] = map[c1][c2];
		map[c1][c2] = temp;
		c2=c2+4;
	//	search2=c2;
		visited[c1][c2]=' ';
		path[steps] = 'E';
		steps++;
		system("clear");
		regenmap();
		done = TRUE;
		break;
}
if(yaba==4 && map[c1+1][c2] != '-' && map[c1+1][c2+1] != '-'){	//Move South
		temp=map[c1+2][c2];
		map[c1+2][c2] = map[c1][c2];
		map[c1][c2] = temp;
		c1=c1+2;
	//	search1=c1;
		visited[c1][c2]=' ';
		path[steps] = 'S';
		steps++;
		system("clear");
		regenmap();
		done = TRUE;
		break;
}

if (yaba==1 && map[c1][c2-2] == '|'){
	printf("*******************There is a wall here!  Please try again.********************\n");
	done = TRUE;}
if(yaba==2 && map[c1-1][c2] == '-' && map[c1-1][c2-1] == '-' ){
	printf("*******************There is a wall here!  Please try again.********************\n");
	done = TRUE;}
if(yaba==3 && map[c1][c2+2] == '|'){
	printf("*******************There is a wall here!  Please try again.********************\n");
	done = TRUE;}
if(yaba==4 && map[c1+1][c2] == '-' && map[c1+1][c2+1] == '-'){
	printf("*******************There is a wall here!  Please try again.********************\n");
	done = TRUE;}

	}//end of while(!done) loop
//***************End: move FUNCTION*************************
}

//***************Start: regenmap FUNCTION*******************
void regenmap(void){
map[c3][c4]=' ';
int a,b;
for (a=0;a<23;a++){
	for (b=0;b<77;b++){
		printf("%c",map[a][b]);
	}
	printf("\n");
}
//***************End: regenmap FUNCTION*********************
}

//***************Start:define help array FUNCTION***********************
void define_visited_array(void){
int yo, yo2;

for (yo=0; yo<23; yo++)
	for(yo2=0; yo2<77; yo2++)
		visited[yo][yo2]= 'x';
for(yo=0;yo<23;yo=yo+2)
	for(yo2=0;yo2<77;yo2++)
		visited[yo][yo2]= '.';
for(yo=0;yo<23;yo++)
	for(yo2=0;yo2<77;yo2=yo2+4)
		visited[yo][yo2]= '.';
for(yo=0;yo<23;yo++)
	for(yo2=1;yo2<77;yo2=yo2+4)
		visited[yo][yo2]= '.';
for(yo=0;yo<23;yo++)
	for(yo2=3;yo2<77;yo2=yo2+4)
		visited[yo][yo2]= '.';
}
//***************Start: help FUNCTION***********************
void help(void){

int yaba, done, xu=0, yu=0, inter[300], inter2[300], yes=1, no=0, checking;
char temp;
done = FALSE;
checking=no;
c1= search1;
c2= search2;
steps=0;
while(checking==no){
while(!done){
if(map[c1][c2+2] != '|' && visited[c1][c2+4] == 'x'){					//Move East
printf("east   y:%d x:%d\n", c1,c2);

		visited[c1][c2]=' ';
		c2=c2+4;
		visited[c1][c2]=' ';
		path[steps] = 'E';
		steps++;
		done=TRUE;
	if(visited[c1-2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1-1][c2-1] != '-' && map[c1][c2-2] != '|'){	
		//check for west and north intersection
			printf("intersection w&n");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an intersection & visited spots for east and north
	else if(map[c1-1][c2-1] != '-'  && visited[c1][c2+4]=='x' && visited[c1-2][c2]=='x' && map[c1][c2+2] != '|'){
			//check north and east
			printf("intersection n&e");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking north and east
	else if(visited[c1][c2+4]=='x' && visited[c1+2][c2]=='x' && map[c1][c2+2] != '|' && map[c1+1][c2+1] != '-' ){
			//check east and south
			printf("intersection e&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an east and south
	else if(visited[c1+2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1][c2-2] != '|' && map[c1+1][c2+1] != '-' ){
			//check west and south
			printf("intersection w&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking west and south
		break;

}
else if(map[c1-1][c2] != '-' && map[c1-1][c2-1] != '-' && visited[c1-2][c2] == 'x'){	//Move North
printf("north   y:%d x:%d\n", c1,c2);
		visited[c1][c2]=' ';
		c1=c1-2;
		visited[c1][c2]=' ';
		path[steps] ='N';
		steps++;
		done=TRUE;
	if(visited[c1-2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1-1][c2-1] != '-' && map[c1][c2-2] != '|'){	
		//check for west and north intersection
			printf("intersection w&n");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an intersection & visited spots for east and north
	else if(map[c1-1][c2-1] != '-'  && visited[c1][c2+4]=='x' && visited[c1-2][c2]=='x' && map[c1][c2+2] != '|'){
			//check north and east
			printf("intersection n&e");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking north and east
	else if(visited[c1][c2+4]=='x' && visited[c1+2][c2]=='x' && map[c1][c2+2] != '|' && map[c1+1][c2+1] != '-' ){
			//check east and south
			printf("intersection e&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an east and south
	else if(visited[c1+2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1][c2-2] != '|' && map[c1+1][c2+1] != '-' ){
			//check west and south
			printf("intersection w&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking west and south
		break;
	}

else if (map[c1][c2-2] != '|' && visited[c1][c2-4] == 'x'){			//Move West
printf("west   y:%d x:%d\n", c1,c2);
		visited[c1][c2]=' ';
		c2=c2-4;
		visited[c1][c2]=' ';
		path[steps] ='W';
		steps++;
		done=TRUE;
	if(visited[c1-2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1-1][c2-1] != '-' && map[c1][c2-2] != '|'){	
//check for west and north intersection
			printf("intersection w&n");		
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an intersection & visited spots for east and north
	else if(map[c1-1][c2-1] != '-'  && visited[c1][c2+4]=='x' && visited[c1-2][c2]=='x' && map[c1][c2+2] != '|'){
			//check north and east
			printf("intersection n&e");		
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking north and east
	else if(visited[c1][c2+4]=='x' && visited[c1+2][c2]=='x' && map[c1][c2+2] != '|' && map[c1+1][c2+1] != '-' ){
			//check east and south
			printf("intersection e&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an east and south
	else if(visited[c1+2][c2]=='x' && visited[c1][c2+4]=='x' && map[c1][c2-2] != '|' && map[c1+1][c2] != '-' ){
			//check west and south
			printf("intersection w&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking west and south
		break;
}

else if(map[c1+1][c2] != '-' && map[c1+1][c2+1] != '-' && visited[c1+2][c2]=='x'){	//Move South
printf("south   y:%d x:%d\n", c1,c2);
		visited[c1][c2]=' ';
		c1=c1+2;
		visited[c1][c2]=' ';
		path[steps] = 'S';
		steps++;
		done=TRUE;
	if(visited[c1-2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1-1][c2-1] != '-' && map[c1][c2-2] != '|'){	
		//check for west and north intersection
			printf("intersection w&n");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
	}//end of if statement checking an intersection & visited spots for east and north
	else if(map[c1-1][c2-1] != '-'  && visited[c1][c2+4]=='x' && visited[c1-2][c2]=='x' && map[c1][c2+2] != '|'){
			//check north and east
			printf("intersection n&e");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking north and east
	else if(visited[c1][c2+4]=='x' && visited[c1+2][c2]=='x' && map[c1][c2+2] != '|' && map[c1+1][c2+1] != '-' ){
			//check east and south
			printf("intersection e&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking an east and south
	else if(visited[c1+2][c2]=='x' && visited[c1][c2-4]=='x' && map[c1][c2-2] != '|' && map[c1+1][c2+1] != '-' ){
			//check west and south
			printf("intersection w&s");
			inter[yu]=c1;
			inter2[xu]=c2;
			xu++;
			yu++;
			timer++;
	}//end of if statement checking west and south
		break;

}
else if (c1==c3 && c2==c4){
		done=TRUE;

}
else if (visited[inter[yu-1]][inter2[xu-1]+4]!='x' && visited[inter[yu-1]+2][inter2[xu-1]]!='x' && visited[inter[yu-1]][inter2[xu-1]-4]!='x' && visited[inter[yu-1]-2][inter2[xu-1]]!='x'){
yu=yu-1;
xu=xu-1;
}
else if (map[inter[yu-1]][inter2[xu-1]+2]=='|' && visited[inter[yu-1]+2][inter2[xu-1]]!='x' && visited[inter[yu-1]][inter2[xu-1]-4]!='x' && visited[inter[yu-1]-2][inter2[xu-1]]!='x'){
yu=yu-1;
xu=xu-1;
}
else if (visited[inter[yu-1]][inter2[xu-1]+2]!='x' && map[inter[yu-1]+1][inter2[xu-1]+1]=='-' && visited[inter[yu-1]][inter2[xu-1]-4]!='x' && visited[inter[yu-1]-2][inter2[xu-1]]!='x'){
yu=yu-1;
xu=xu-1;
}
else if (visited[inter[yu-1]][inter2[xu-1]+4]!='x' && visited[inter[yu-1]+2][inter2[xu-1]]!='x' && visited[inter[yu-1]][inter2[xu-1]-4]!='x' && map[inter[yu-1]-1][inter2[xu-1]-1]=='-'){
yu=yu-1;
xu=xu-1;
}
else if (visited[inter[yu-1]][inter2[xu-1]+4]!='x' && visited[inter[yu-1]+2][inter2[xu-1]]!='x' && map[inter[yu-1]][inter2[xu-1]-4]=='|' && visited[inter[yu-1]-2][inter2[xu-1]]!='x'){
yu=yu-1;
xu=xu-1;
}

else{		//ran into dead end
c1=inter[yu-1];		//intersections' y location
c2=inter2[xu-1];	//intersections' x location
steps=steps-timer;	//clears a file print path you didn't use when you hit a dead end
timer=0;
break;
}
	}//end of while(!done) loop
if(c1==c3 && c2==c4){
	printf("The egg has been found!\n");
	printpath();		//Print path to egg in 2'nd output file
	checking = yes;
}
else{
	checking = no;
	done = FALSE;}
}//end of second while loop
exit(0);
}
//*****************End: help FUNCTION***********************

//**************Start: printpath FUNCTION*******************
void printpath(void){

int printcounter;

for(printcounter=0; printcounter <= steps; printcounter++)
	fprintf(f3, "%c",path[printcounter]);
//**************End: printpath FUNCTION*********************

}
//**************Start: check_egg_existence FUNCTION*******************

void check_egg_existence(void){
int a,b, yes=0, checker;
for (a=0;a<23;a++){
	for (b=0;b<77;b++){
		if(map[a][b]=='G')
			checker=yes;
}
}
if(checker!=yes){
	printf("THERE IS NO EGG IN THIS MAP.  Please load another maze.");
	exit(0);}
	}


