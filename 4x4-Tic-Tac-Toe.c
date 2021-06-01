#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>                    ///For making sounds and for adding text color
#include<time.h>                        ///For making time functions work
#include<string.h>

int end=0;                              ///Determines the game ended
int win=0;                              ///Determines whether a player won or not and recorded in file
char mode;                              ///Determines the mode of the game
int turns=0;                            ///Number of turns made (Both of the player and Computer)
char board[4][4]={{' ',' ',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}};  ///The board

void display_info(int n);               ///This function prints a message whether the player won,lost or drawn the game
void display_result(int n,int m);       ///This function will display the final result after game completion
void player_move();                     ///This function takes the player input
void computer_move();                   ///This function makes the computer input
void board_display();                   ///This function will display the board along with the hint box during each turn
void check_result();                    ///This function checks whether a winning combination exists in each turn
void winning_sound();                   ///This function makes a victory sound if the player wins
void losing_sound();                    ///This function makes a sad sound if the player loses or draws the game
void setcolor(int ForgC);               ///This function changes the color of the text for beautification

int main()
{
    FILE *f;
    char pname[50], scoreboard[100][100];
    int ci;
    printf("Let's play 4x4 Tic Tac Toe.\n\nYour mark will be shown as 'O'\n\n");
    printf("Enter player name: ");
    gets(pname);                                         ///Player name is taken to keep records
    printf("\n\n");
    printf("In which mode you want to play? Type 'e' for easy, 'h' for hard\n");
    for(;;)
    {
        scanf("%c",&mode);                              ///Takes the input whether the player wants to play in hard mode or easy mode
        getchar();
        if(mode=='e' || mode=='h')
            break;
        else
        {
            printf("Type 'e' or 'h'\n");
        }
    }
    printf("Press 'q' anytime to quit.\n\n");
    int i1=0;
    char name[50], tries[10], score[10], row[100];
    int t, s;

    f = fopen("scores.txt", "r");
    while(fgets(row, sizeof(row), f)){
        strcpy(scoreboard[i1++], row);

        if(i1==1) continue;

        ///extract name of each player
        int j;
        for(j=0; row[j]!='\t'; j++)
            name[j] = row[j];
        name[j] = '\0';

        /// if name matches current player than update score string after game
        ///no duplicate names should be used
        if(!strcmp(name, pname)){

            ///store string index to update
            ci = i1-1;

            ///extract previous try count of current player
            j++;
            int ti=0;
            for(; row[j]!='\t'; j++)
                tries[ti++] = row[j];
            tries[ti] = '\0';

            ///extract previous score of current player
            j++;
            int si=0;
            for(; row[j]!='\n'; j++)
                score[si++] = row[j];
            score[si] = '\0';

            /// convert to integer
            t = atoi(tries);
            s = atoi(score);
        }
    }

    fclose(f);

    printf("\t ___ ___ ___ ___\n");                 ///The initial instruction board to show the player which buttons he must press to mark at desired spot
    printf("\t|   |   |   |   |\n");
    printf("\t| a | b | c | d |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| e | f | g | h |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| i | j | k | l |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| m | n | o | p |\n");
    printf("\t|___|___|___|___|\n\n");
    printf("Press the letter on the keyboard to indicate in which slot you want to mark\n");
    int i;
    for(;;)
    {
        if(turns==16)         ///If 16 turns are done, result is checked.
        {
            check_result();
            break;
        }
        else
        {
            player_move();
            if(end==0)
                computer_move();
            else
                break;
            if(end==0)
                board_display();
            else
                break;
        }
    }
    ///update try and score count
    int new_player=0;
    if(!strcmp(pname, name)){
        if(win){
            sprintf(scoreboard[ci], "%s\t%d\t%d\n", pname, t+1, s+1);
            puts("Your current record: ");
            puts(scoreboard[ci]);
        }else{
            sprintf(scoreboard[ci], "%s\t%d\t%d\n", pname, t+1, s);
            puts("Your current record: ");
            puts(scoreboard[ci]);
        }
    }else{
        new_player =1;
    }
    ///write all scores including updated score to file
    f = fopen("scores.txt", "w");

    int k;
    for(k=0; k<i1; k++){
        fprintf(f, scoreboard[k]);
    }

    /// if no scores in file just add the top row
    if(k==0)
        fprintf(f, "Player\tTries\tScore\n");

    if(new_player){
        if(win)
            fprintf(f, "%s\t%d\t%d\n", pname, 1, 1);
        else
            fprintf(f, "%s\t%d\t%d\n", pname, 1, 0);
    }

    fclose(f);
}

void player_move()                     ///This function takes the player input
{
    char ch;
    for(;;)
    {
        scanf(" %c",&ch);
        getchar();
        if(ch=='a')
        {
            if(board[0][0]==' ')
            {
                 board[0][0]='O';
                 turns++;
                 printf("\a");        ///A beep is heard each time the player makes a move at a valid place
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='b')
        {
            if(board[0][1]==' ')
            {
                board[0][1]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='c')
        {
            if(board[0][2]==' ')
            {
                board[0][2]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='d')
        {
            if(board[0][3]==' ')
            {
                board[0][3]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='e')
        {
            if(board[1][0]==' ')
            {
                 board[1][0]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='f')
        {
            if(board[1][1]==' ')
            {
                 board[1][1]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='g')
        {
            if(board[1][2]==' ')
            {
                 board[1][2]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='h')
        {
            if(board[1][3]==' ')
            {
                board[1][3]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='i')
        {
            if(board[2][0]==' ')
            {
                board[2][0]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='j')
        {
            if(board[2][1]==' ')
            {
                board[2][1]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='k')
        {
            if(board[2][2]==' ')
            {
                 board[2][2]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='l')
        {
            if(board[2][3]==' ')
            {
                board[2][3]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='m')
        {
            if(board[3][0]==' ')
            {
                board[3][0]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='n')
        {
            if(board[3][1]==' ')
            {
                board[3][1]='O';
                turns++;
                printf("\a");
                break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='o')
        {
            if(board[3][2]==' ')
            {
                 board[3][2]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='p')
        {
            if(board[3][3]==' ')
            {
                 board[3][3]='O';
                 turns++;
                 printf("\a");
                 break;
            }
            else
                printf("The slot had already been marked. Try another one\n\n");
        }
        else if(ch=='q')                      ///pressing 'q' will terminate the whole program
        {
            printf("\nYou quit the game.\n");
            exit(0);
        }
        else
        {
            printf("You pressed a wrong button. Try the correct ones.\n\n");
        }
    }
    check_result();
}

void computer_move()          ///This function makes the computer input
{
    int a;
    time_t t;
    srand((unsigned) time(&t));  ///This line is used to generate random numbers (a time function)
    for(;;)
    {
        if(mode=='h')          ///This condition is checked when player plays in hard mode
        {
            printf("%c",mode);
            if((board[0][0]=='O' && board[0][1]=='O' && board[0][2]=='O' && board[0][3]==' ')||(board[0][0]=='X' && board[0][1]=='X' && board[0][2]=='X' && board[0][3]==' '))
            {
                board[0][3]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[0][1]=='O' && board[0][2]==' ' && board[0][3]=='O')||(board[0][0]=='X' && board[0][1]=='X' && board[0][2]==' ' && board[0][3]=='X'))
            {
                board[0][2]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[0][1]==' ' && board[0][2]=='O' && board[0][3]=='O')||(board[0][0]=='X' && board[0][1]==' ' && board[0][2]=='X' && board[0][3]=='X'))
            {
                board[0][1]='X';
                turns++;
                break;
            }
            else if((board[0][0]==' ' && board[0][1]=='O' && board[0][2]=='O' && board[0][3]=='O')||(board[0][0]==' ' && board[0][1]=='X' && board[0][2]=='X' && board[0][3]=='X'))
            {
                board[0][0]='X';
                turns++;
                break;
            }
            else if((board[1][0]=='O' && board[1][1]=='O' && board[1][2]=='O' && board[1][3]==' ')||(board[1][0]=='X' && board[1][1]=='X' && board[1][2]=='X' && board[1][3]==' '))
            {
                board[1][3]='X';
                turns++;
                break;
            }
            else if((board[1][0]=='O' && board[1][1]=='O' && board[1][2]==' ' && board[1][3]=='O')||(board[1][0]=='X' && board[1][1]=='X' && board[1][2]==' ' && board[1][3]=='X'))
            {
                board[1][2]='X';
                turns++;
                break;
            }
            else if((board[1][0]=='O' && board[1][1]==' ' && board[1][2]=='O' && board[1][3]=='O')||(board[1][0]=='X' && board[1][1]==' ' && board[1][2]=='X' && board[1][3]=='X'))
            {
                board[1][1]='X';
                turns++;
                break;
            }
            else if((board[1][0]==' ' && board[1][1]=='O' && board[1][2]=='O' && board[1][3]=='O')||(board[1][0]==' ' && board[1][1]=='X' && board[1][2]=='X' && board[1][3]=='X'))
            {
                board[1][0]='X';
                turns++;
                break;
            }
            else if((board[2][0]=='O' && board[2][1]=='O' && board[2][2]=='O' && board[2][3]==' ')||(board[2][0]=='X' && board[2][1]=='X' && board[2][2]=='X' && board[2][3]==' '))
            {
                board[2][3]='X';
                turns++;
                break;
            }
            else if((board[2][0]=='O' && board[2][1]=='O' && board[2][2]==' ' && board[2][3]=='O')||(board[2][0]=='X' && board[2][1]=='X' && board[2][2]==' ' && board[2][3]=='X'))
            {
                board[2][2]='X';
                turns++;
                break;
            }
            else if((board[2][0]=='O' && board[2][1]==' ' && board[2][2]=='O' && board[2][3]=='O')||(board[2][0]=='X' && board[2][1]==' ' && board[2][2]=='X' && board[2][3]=='X'))
            {
                board[2][1]='X';
                turns++;
                break;
            }
            else if((board[2][0]==' ' && board[2][1]=='O' && board[2][2]=='O' && board[2][3]=='O')||(board[2][0]==' ' && board[2][1]=='X' && board[2][2]=='X' && board[2][3]=='X'))
            {
                board[2][0]='X';
                turns++;
                break;
            }
            else if((board[3][0]=='O' && board[3][1]=='O' && board[3][2]=='O' && board[3][3]==' ')||(board[3][0]=='X' && board[3][1]=='X' && board[3][2]=='X' && board[3][3]==' '))
            {
                board[3][3]='X';
                turns++;
                break;
            }
            else if((board[3][0]=='O' && board[3][1]=='O' && board[3][2]==' ' && board[3][3]=='O')||(board[3][0]=='X' && board[3][1]=='X' && board[3][2]==' ' && board[3][3]=='X'))
            {
                board[3][2]='X';
                turns++;
                break;
            }
            else if((board[3][0]=='O' && board[3][1]==' ' && board[3][2]=='O' && board[3][3]=='O')||(board[3][0]=='X' && board[3][1]==' ' && board[3][2]=='X' && board[3][3]=='X'))
            {
                board[3][1]='X';
                turns++;
                break;
            }
            else if((board[3][0]==' ' && board[3][1]=='O' && board[3][2]=='O' && board[3][3]=='O')||(board[3][0]==' ' && board[3][1]=='X' && board[3][2]=='X' && board[3][3]=='X'))
            {
                board[3][0]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[1][0]=='O' && board[2][0]=='O' && board[3][0]==' ')||(board[0][0]=='X' && board[1][0]=='X' && board[2][0]=='X' && board[3][0]==' '))
            {
                board[3][0]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[1][0]=='O' && board[2][0]==' ' && board[3][0]=='O')||(board[0][0]=='X' && board[1][0]=='X' && board[2][0]==' ' && board[3][0]=='X'))
            {
                board[2][0]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[1][0]==' ' && board[2][0]=='O' && board[3][0]=='O')||(board[0][0]=='X' && board[1][0]==' ' && board[2][0]=='X' && board[3][0]=='X'))
            {
                board[1][0]='X';
                turns++;
                break;
            }
            else if((board[0][0]==' ' && board[1][0]=='O' && board[2][0]=='O' && board[3][0]=='O')||(board[0][0]==' ' && board[1][0]=='X' && board[2][0]=='X' && board[3][0]=='X'))
            {
                board[0][0]='X';
                turns++;
                break;
            }
            else if((board[0][1]=='O' && board[1][1]=='O' && board[2][1]=='O' && board[3][1]==' ')||(board[0][1]=='X' && board[1][1]=='X' && board[2][1]=='X' && board[3][1]==' '))
            {
                board[3][1]='X';
                turns++;
                break;
            }
            else if((board[0][1]=='O' && board[1][1]=='O' && board[2][1]==' ' && board[3][1]=='O')||(board[0][1]=='X' && board[1][1]=='X' && board[2][1]==' ' && board[3][1]=='X'))
            {
                board[2][1]='X';
                turns++;
                break;
            }
            else if((board[0][1]=='O' && board[1][1]==' ' && board[2][1]=='O' && board[3][1]=='O')||(board[0][1]=='X' && board[1][1]==' ' && board[2][1]=='X' && board[3][1]=='X'))
            {
                board[1][1]='X';
                turns++;
                break;
            }
            else if((board[0][1]==' ' && board[1][1]=='O' && board[2][1]=='O' && board[3][1]=='O')||(board[0][1]==' ' && board[1][1]=='X' && board[2][1]=='X' && board[3][1]=='X'))
            {
                board[0][1]='X';
                turns++;
                break;
            }
            else if((board[0][2]=='O' && board[1][2]=='O' && board[2][2]=='O' && board[3][2]==' ')||(board[0][2]=='X' && board[1][2]=='X' && board[2][2]=='X' && board[3][2]==' '))
            {
                board[3][2]='X';
                turns++;
                break;
            }
            else if((board[0][2]=='O' && board[1][2]=='O' && board[2][2]==' ' && board[3][2]=='O')||(board[0][2]=='X' && board[1][2]=='X' && board[2][2]==' ' && board[3][2]=='X'))
            {
                board[2][2]='X';
                turns++;
                break;
            }
             else if((board[0][2]=='O' && board[1][2]==' ' && board[2][2]=='O' && board[3][2]=='O')||(board[0][2]=='X' && board[1][2]==' ' && board[2][2]=='X' && board[3][2]=='X'))
            {
                board[1][2]='X';
                turns++;
                break;
            }
             else if((board[0][2]==' ' && board[1][2]=='O' && board[2][2]=='O' && board[2][3]=='O')||(board[0][2]==' ' && board[1][2]=='X' && board[2][2]=='X' && board[2][3]=='X'))
            {
                board[0][2]='X';
                turns++;
                break;
            }
             else if((board[0][3]=='O' && board[1][3]=='O' && board[2][3]=='O' && board[3][3]==' ')||(board[0][3]=='X' && board[1][3]=='X' && board[2][3]=='X' && board[3][3]==' '))
            {
                board[3][3]='X';
                turns++;
                break;
            }
             else if((board[0][3]=='O' && board[1][3]=='O' && board[2][3]==' ' && board[3][3]=='O')||(board[0][3]=='X' && board[1][3]=='X' && board[2][3]==' ' && board[3][3]=='X'))
            {
                board[2][3]='X';
                turns++;
                break;
            }
             else if((board[0][3]=='O' && board[1][3]==' ' && board[2][3]=='O' && board[3][3]=='O')||(board[0][3]=='X' && board[1][3]==' ' && board[2][3]=='X' && board[3][3]=='X'))
            {
                board[1][3]='X';
                turns++;
                break;
            }
             else if((board[0][3]==' ' && board[1][3]=='O' && board[2][3]=='O' && board[3][3]=='O')||(board[0][3]==' ' && board[1][3]=='X' && board[2][3]=='X' && board[3][3]=='X'))
            {
                board[0][3]='X';
                turns++;
                break;
            }
             else if((board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O' && board[3][3]==' ')||(board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X' && board[3][3]==' '))
            {
                board[3][3]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[1][1]=='O' && board[2][2]==' ' && board[3][3]=='O')||(board[0][0]=='X' && board[1][1]=='X' && board[2][2]==' ' && board[3][3]=='X'))
            {
                board[2][2]='X';
                turns++;
                break;
            }
            else if((board[0][0]=='O' && board[1][1]==' ' && board[2][2]=='O' && board[3][3]=='O')||(board[0][0]=='X' && board[1][1]==' ' && board[2][2]=='X' && board[3][3]=='X'))
            {
                board[1][1]='X';
                turns++;
                break;
            }
            else if((board[0][0]==' ' && board[1][1]=='O' && board[2][2]=='O' && board[3][3]=='O')||(board[0][0]==' ' && board[1][1]=='X' && board[2][2]=='X' && board[3][3]=='X'))
            {
                board[0][0]='X';
                turns++;
                break;
            }
            else if((board[0][3]=='O' && board[1][2]=='O' && board[2][1]=='O' && board[3][0]==' ')||(board[0][3]=='X' && board[1][2]=='X' && board[2][1]=='X' && board[3][0]==' '))
            {
                board[3][0]='X';
                turns++;
                break;
            }
            else if((board[0][3]=='O' && board[1][2]=='O' && board[2][1]==' ' && board[3][0]=='O')||(board[0][3]=='X' && board[1][2]=='X' && board[2][1]==' ' && board[3][0]=='X'))
            {
                board[2][1]='X';
                turns++;
                break;
            }
            else if((board[0][3]=='O' && board[1][2]==' ' && board[2][1]=='O' && board[3][0]=='O')||(board[0][3]=='X' && board[1][2]==' ' && board[2][1]=='X' && board[3][0]=='X'))
            {
                board[1][2]='X';
                turns++;
                break;
            }
            else if((board[0][3]==' ' && board[1][2]=='O' && board[2][1]=='O' && board[3][0]=='O')||(board[0][3]==' ' && board[1][2]=='X' && board[2][1]=='X' && board[3][0]=='X'))
            {
                board[0][3]='X';
                turns++;
                break;
            }
        }
        a=(rand()%16);              ///These conditions are checked in easy mode and in hard mode when the player or the computer is not near to win
        if(a==0)
        {
            if(board[0][0]==' ')
            {
                board[0][0]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==1)
        {
            if(board[0][1]==' ')
            {
                board[0][1]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==2)
        {
            if(board[0][2]==' ')
            {
                board[0][2]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==3)
        {
            if(board[0][3]==' ')
            {
                board[0][3]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==4)
        {
            if(board[1][0]==' ')
            {
                board[1][0]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==5)
        {
            if(board[1][1]==' ')
            {
                board[1][1]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==6)
        {
            if(board[1][2]==' ')
            {
                board[1][2]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==7)
        {
            if(board[1][3]==' ')
            {
                board[1][3]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==8)
        {
            if(board[2][0]==' ')
            {
                board[2][0]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==9)
        {
            if(board[2][1]==' ')
            {
                board[2][1]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==10)
        {
            if(board[2][2]==' ')
            {
                board[2][2]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==11)
        {
            if(board[2][3]==' ')
            {
                board[2][3]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==12)
        {
            if(board[3][0]==' ')
            {
                board[3][0]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==13)
        {
            if(board[3][1]==' ')
            {
                board[3][1]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==14)
        {
            if(board[3][2]==' ')
            {
                board[3][2]='X';
                turns++;
                break;
            }
            else
                continue;
        }
        else if(a==15)
        {
            if(board[3][3]==' ')
            {
                board[3][3]='X';
                turns++;
                break;
            }
            else
                continue;
        }
    }
    check_result();
}

void check_result()
{
            if(turns==16)
            {
                display_result(10,2);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][0]=='O' && board[0][1]=='O' && board[0][2]=='O' && board[0][3]=='O')
            {
                win=1;
                display_result(0,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[1][0]=='O' && board[1][1]=='O' && board[1][2]=='O' && board[1][3]=='O')
            {
                win=1;
                display_result(1,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[2][0]=='O' && board[2][1]=='O' && board[2][2]=='O' && board[2][3]=='O')
            {
                win=1;
                display_result(2,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[3][0]=='O' && board[3][1]=='O' && board[3][2]=='O' && board[3][3]=='O')
            {
                win=1;
                display_result(3,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][0]=='O' && board[1][0]=='O' && board[2][0]=='O' && board[3][0]=='O')
            {
                win=1;
                display_result(4,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][1]=='O' && board[1][1]=='O' && board[2][1]=='O' && board[3][1]=='O')
            {
                win=1;
                display_result(5,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][2]=='O' && board[1][2]=='O' && board[2][2]=='O' && board[3][2]=='O')
            {
                win=1;
                display_result(6,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][3]=='O' && board[1][3]=='O' && board[2][3]=='O' && board[3][3]=='O')
            {
                win=1;
                display_result(7,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O' && board[3][3]=='O')
            {
                win=1;
                display_result(8,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][3]=='O' && board[1][2]=='O' && board[2][1]=='O' && board[3][0]=='O')
            {
                win=1;
                display_result(9,0);
                delay_sound();
                winning_sound();
                end=1;
            }
            else if(board[0][0]=='X' && board[0][1]=='X' && board[0][2]=='X' && board[0][3]=='X')
            {
                display_result(0,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[1][0]=='X' && board[1][1]=='X' && board[1][2]=='X' && board[1][3]=='X')
            {
                display_result(1,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[2][0]=='X' && board[2][1]=='X' && board[2][2]=='X' && board[2][3]=='X')
            {
                display_result(2,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[3][0]=='X' && board[3][1]=='X' && board[3][2]=='X' && board[3][3]=='X')
            {
                display_result(3,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][0]=='X' && board[1][0]=='X' && board[2][0]=='X' && board[3][0]=='X')
            {
                display_result(4,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][1]=='X' && board[1][1]=='X' && board[2][1]=='X' && board[3][1]=='X')
            {
                display_result(5,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][2]=='X' && board[1][2]=='X' && board[2][2]=='X' && board[3][2]=='X')
            {
                display_result(6,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][3]=='X' && board[1][3]=='X' && board[2][3]=='X' && board[3][3]=='X')
            {
                display_result(7,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X' && board[3][3]=='X')
            {
                display_result(8,1);
                delay_sound();
                losing_sound();
                end=1;
            }
            else if(board[0][3]=='X' && board[1][2]=='X' && board[2][1]=='X' && board[3][0]=='X')
            {
                display_result(9,1);
                delay_sound();
                losing_sound();
                end=1;
            }
}

void board_display()        ///This function prints the board with marked places and also shows the hint box
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t\t\t\t\tSee and press the button where you want to mark.\n");
    printf("\t ___ ___ ___ ___ \t\t ___ ___ ___ ___\n");
    printf("\t|   |   |   |   |\t\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);                                    ///The setcolor function is responsible for changing the color of text
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\t\t| a | b | c | d |\n");
    printf("\t|___|___|___|___|\t\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\t\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\t\t| e | f | g | h |\n");
    printf("\t|___|___|___|___|\t\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\t\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\t\t| i | j | k | l |\n");
    printf("\t|___|___|___|___|\t\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\t\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\t\t| m | n | o | p |\n");
    printf("\t|___|___|___|___|\t\t|___|___|___|___|\n");
}


void display_result(int n,int m)
{
    if(n==0)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___ \n");
    printf("\t|   |   |   |   |\n");
    printf("\t|-");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf("-|-");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf("-|-");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf("-|-");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf("-|\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    }
    else if(n==1)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___ \n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t|-");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf("-|-");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf("-|-");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf("-|-");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf("-|\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    }
    else if(n==2)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t|-");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf("-|-");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf("-|-");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf("-|-");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf("-|\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    }
    else if(n==3)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t|-");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf("-|-");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf("-|-");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf("-|-");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf("-|\n");
    printf("\t|___|___|___|___|\n");
    }
    else if(n==4)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t| | |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|_|_|___|___|___|\n");
    printf("\t| | |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|_|_|___|___|___|\n");
    printf("\t| | |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|_|_|___|___|___|\n");
    printf("\t| | |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|_|_|___|___|___|\n");
    }
    else if(n==5)
    {
         printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   | | |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|_|_|___|___|\n");
    printf("\t|   | | |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|_|_|___|___|\n");
    printf("\t|   | | |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|_|_|___|___|\n");
    printf("\t|   | | |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|_|_|___|___|\n");
    }
    else if(n==6)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   | | |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|_|_|___|\n");
    printf("\t|   |   | | |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|_|_|___|\n");
    printf("\t|   |   | | |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|_|_|___|\n");
    printf("\t|   |   | | |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|_|_|___|\n");
    }
    else if(n==7)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   |   | | |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|_|_|\n");
    printf("\t|   |   |   | | |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|_|_|\n");
    printf("\t|   |   |   | | |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|_|_|\n");
    printf("\t|   |   |   | | |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|_|_|\n");
    }
    else if(n==8)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|\\  |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|__\\|___|___|___|\n");
    printf("\t|   |\\  |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|__\\|___|___|\n");
    printf("\t|   |   |\\  |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|__\\|___|\n");
    printf("\t|   |   |   |\\  |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|__\\|\n");
    }
    else if(n==9)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   |   |  /|\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|/__|\n");
    printf("\t|   |   |  /|   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|/__|___|\n");
    printf("\t|   |  /|   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|/__|___|___|\n");
    printf("\t|  /|   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|/__|___|___|___|\n");
    }
    else if(n==10)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    SetColor(10);
    printf("\t ___ ___ ___ ___\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[0][0]=='O')
        SetColor(4);
    else if(board[0][0]=='X')
        SetColor(3);
    printf("%c",board[0][0]);
    SetColor(10);
    printf(" | ");
    if(board[0][1]=='O')
        SetColor(4);
    else if(board[0][1]=='X')
        SetColor(3);
    printf("%c",board[0][1]);
    SetColor(10);
    printf(" | ");
    if(board[0][2]=='O')
        SetColor(4);
    else if(board[0][2]=='X')
        SetColor(3);
    printf("%c",board[0][2]);
    SetColor(10);
    printf(" | ");
    if(board[0][3]=='O')
        SetColor(4);
    else if(board[0][3]=='X')
        SetColor(3);
    printf("%c",board[0][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[1][0]=='O')
        SetColor(4);
    else if(board[1][0]=='X')
        SetColor(3);
    printf("%c",board[1][0]);
    SetColor(10);
    printf(" | ");
    if(board[1][1]=='O')
        SetColor(4);
    else if(board[1][1]=='X')
        SetColor(3);
    printf("%c",board[1][1]);
    SetColor(10);
    printf(" | ");
    if(board[1][2]=='O')
        SetColor(4);
    else if(board[1][2]=='X')
        SetColor(3);
    printf("%c",board[1][2]);
    SetColor(10);
    printf(" | ");
    if(board[1][3]=='O')
        SetColor(4);
    else if(board[1][3]=='X')
        SetColor(3);
    printf("%c",board[1][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[2][0]=='O')
        SetColor(4);
    else if(board[2][0]=='X')
        SetColor(3);
    printf("%c",board[2][0]);
    SetColor(10);
    printf(" | ");
    if(board[2][1]=='O')
        SetColor(4);
    else if(board[2][1]=='X')
        SetColor(3);
    printf("%c",board[2][1]);
    SetColor(10);
    printf(" | ");
    if(board[2][2]=='O')
        SetColor(4);
    else if(board[2][2]=='X')
        SetColor(3);
    printf("%c",board[2][2]);
    SetColor(10);
    printf(" | ");
    if(board[2][3]=='O')
        SetColor(4);
    else if(board[2][3]=='X')
        SetColor(3);
    printf("%c",board[2][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    printf("\t|   |   |   |   |\n");
    printf("\t| ");
    if(board[3][0]=='O')
        SetColor(4);
    else if(board[3][0]=='X')
        SetColor(3);
    printf("%c",board[3][0]);
    SetColor(10);
    printf(" | ");
    if(board[3][1]=='O')
        SetColor(4);
    else if(board[3][1]=='X')
        SetColor(3);
    printf("%c",board[3][1]);
    SetColor(10);
    printf(" | ");
    if(board[3][2]=='O')
        SetColor(4);
    else if(board[3][2]=='X')
        SetColor(3);
    printf("%c",board[3][2]);
    SetColor(10);
    printf(" | ");
    if(board[3][3]=='O')
        SetColor(4);
    else if(board[3][3]=='X')
        SetColor(3);
    printf("%c",board[3][3]);
    SetColor(10);
    printf(" |\n");
    printf("\t|___|___|___|___|\n");
    }
    display_info(m);
}
void display_info(int n)
{
    if(n==0)
        printf("\n\tCONGRATULATIONS! YOU WIN!\n\n");
    else if(n==1)
        printf("\n\tYOU LOST. BAD LUCK\n\n");
    else if(n==2)
        printf("\n\tMATCH DRAWN. BETTER LUCK NEXT TIME\n\n");
}
void delay_sound()
{
    int i;
    for(i=0;i<500000000;i++)
    {

    }
}
void winning_sound()
{
    Beep(600,200);
    Beep(512,200);
    Beep(655,200);
    Beep(524,200);
    Beep(725,200);
    Beep(536,200);
    Beep(600,200);
}
void losing_sound()
{
    Beep(500,400);
    Beep(400,500);
    Beep(300,500);
}

void SetColor(int ForgC)   ///Taken from stackoverflow. Used for colour
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}


/*
Name         | Value
             |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15

*/
