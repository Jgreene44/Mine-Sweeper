//
// Created by jgreene44 on 5/8/2019.
//

#include "game.h"

struct Game g;
/* Build board used for created random mines */
void makeFrontBoard()
{

    int i, j;

    //--------------------------------
    // Assign char for board elements
    //--------------------------------
    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            g.board[i][j] = 'o';

    // Place mines in this board, it remains
    // hidden from user until the game has
    // finished.
    populateBoard();
}

/* Build game board for user input */
void makeBackBoard()
{

    int i, j;
    int row, col, cur = 4;

    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            g.game_board[i][j] = 'o';

    //--------------------------------
    // Print board
    //--------------------------------
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");

    for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", g.game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

/* Create random places in the array for mines */
void populateBoard()
{
    int i, random;

    // Seeding srand() with time(0) so that
    // mine locations aren't the same every
    // time the game is played.
    srand(time(0));

    for (i = 0; i < BOARD_SIZE; i++)
    {
        random = rand() % (BOARD_SIZE);
        g.board[random][i] = '*';
    }

}

/* Print the game board */
void printFrontBoard()
{
    int row, col;

    system("cls");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");
    for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", g.game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

/* Print the full board showing mines */
void printBackBoard()
{
    int row, col;

    system("cls");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");
    for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", g.board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

/* Take user input for playing of the game */
int playGame()
{
    int r_selection = 0, c_selection = 0,
            nearbymines = 0, nearbymines2 = 0,
            nearbymines3 = 0, nearbymines4 = 0,
            nearbymines5 = 0, nearbymines6 = 0,
            nearbymines7 = 0, nearbymines8 = 0,
            i = 0;

    //----------------------------------------------
    // Recieves data from the user, first the row
    // number, then the column number...
    // I could think of other ways to do it, but
    // this one seemed easiest.
    //----------------------------------------------
    do {
        printf("\nMake a selection (ie. row [ENTER] col): \n");
        printf("Row--> ");
        scanf("%d", &r_selection);
        printf("Col--> ");
        scanf("%d", &c_selection);

    } while(r_selection < 1 || r_selection > BOARD_SIZE || c_selection < 1 || r_selection > BOARD_SIZE);
    // ^ Checks for any invalid input statements from user.

    checkMine(r_selection - 1, c_selection - 1);

    if(g.lost == 1){
        return -1;
    }


    // Checks for nearby mines at every direction from user
    // input location. Assigns that location the number
    // of mines found nearby, updating the board.
    nearbymines = checkNearbyMines(r_selection - 1, c_selection - 1);
    g.game_board[r_selection - 1][c_selection - 1] = (char)( ((int)'0') + nearbymines );

    if(nearbymines == 0)
    {
        if(c_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines == 0 && (c_selection - 1 + i) < BOARD_SIZE)
            {
                // This is checking elements to the right
                nearbymines = checkNearbyMines(r_selection - 1, (c_selection - 1 + i));
                if(nearbymines != -1)
                {
                    g.game_board[r_selection - 1][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines );
                    i++;
                }
            }
            if(r_selection != 1)
            {
                i = 0;
                while(nearbymines5 == 0 && (c_selection - 1 + i) < BOARD_SIZE && (r_selection - 1 - i) > 0)
                {
                    // This is checking elements to the diagonal-uright
                    nearbymines5 = checkNearbyMines((r_selection - 1 - i), (c_selection - 1 + i));
                    if(nearbymines5 != -1)
                    {
                        g.game_board[(r_selection - 1) - i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines5);
                        i++;
                    }
                }
            }
            if(r_selection != BOARD_SIZE)
            {
                i = 0;
                while(nearbymines6 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 + i) < BOARD_SIZE )
                {
                    // This is checking elements to the diagonal-dright
                    nearbymines6 = checkNearbyMines((r_selection - 1 + i), (c_selection - 1 + i));
                    if(nearbymines != -1)
                    {
                        g.game_board[(r_selection - 1) + i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines6);
                        i++;
                    }
                }
            }
        }

        if(r_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines2 == 0 && (r_selection - 1 + i) < BOARD_SIZE)
            {
                // This is checking elements heading down
                nearbymines2 = checkNearbyMines((r_selection - 1 + i), c_selection - 1);
                if(nearbymines2 != -1)
                {
                    g.game_board[(r_selection - 1) + i][c_selection - 1] = (char) ( ((int)'0') + nearbymines2 );
                    i++;
                }
            }

            if(c_selection != BOARD_SIZE)
            {
                i = 0;
                while(nearbymines7 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 - i) > 0)
                {
                    // This is checking elements to the diagonal-dleft
                    nearbymines7 = checkNearbyMines((r_selection - 1 + i), (c_selection - 1 - i));
                    if(nearbymines != -1)
                    {
                        g.game_board[(r_selection - 1) + i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines7);
                        i++;
                    }
                }
            }
        }

        if(r_selection != 1)
        {
            i = 0;
            while(nearbymines3 == 0 && (r_selection - i) > 0)
            {
                // This is checking elements heading up
                nearbymines3 = checkNearbyMines((r_selection - 1 - i), c_selection - 1);
                if(nearbymines3 != -1)
                {
                    g.game_board[(r_selection - 1) - i][c_selection - 1] = (char) ( ((int)'0') + nearbymines3 );
                    i++;
                }
            }
            if(c_selection != BOARD_SIZE)
            {
                while(nearbymines8 == 0 && (c_selection - 1 - i) > 0 && (r_selection - 1 - i) > 0)
                {
                    // This is checking elements to the diagonal-uleft
                    nearbymines8 = checkNearbyMines((r_selection - 1 - i), (c_selection - 1 - i));
                    if(nearbymines8 != -1)
                    {
                        g.game_board[(r_selection - 1) - i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines8);
                        i++;
                    }
                }
            }
        }

        if(c_selection != 1)
        {
            i = 0;
            while(nearbymines4 == 0 && (c_selection - i) > 0)
            {
                // This is checking elements to the left
                nearbymines4 = checkNearbyMines(r_selection - 1, (c_selection - 1 - i));
                if(nearbymines4 != -1)
                {
                    g.game_board[r_selection - 1][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines4 );
                    i++;
                }
            }
        }
    }



    // Handles a player winning.
    if(CheckGameState() == TRUE)
    {
        system("cls");
        printBackBoard();
        printf("\n\nYou've won the game!! Congrats!!\n\n");
        playAgain();
    }

    return 0;
}

/* Check whether user input has selected a mine */
void checkMine(int r, int c)
{
    if(g.board[r][c] == '*')
    {
        printf("\nYou've hit a mine! You lose!\n");
        getchar(); getchar();
        g.lost = 1;
    }
}

/* Another ridiculous function to find nearby mines.
 * I know, I know...it's messy, and needs a rewrite. */
int checkNearbyMines(int r, int c)
{
    int nearby_mine_count = 0;

    if(g.board[r][c] == '*')
    {
        return -1;
    }
    // Check for mines below and to the right.
    if(r < (BOARD_SIZE - 1) && c < (BOARD_SIZE - 1))
    {
        // Check for mine below
        if(g.board[r + 1][c] == '*')
            nearby_mine_count++;
        // Check for mine to the right.
        if(g.board[r][c + 1] == '*')
            nearby_mine_count++;
        // Check for mine diagonal-dright.
        if(g.board[r + 1][c + 1] == '*')
            nearby_mine_count++;

        // Check whether the columns to the left can be checked
        if(c != 0)
        {
            // Check for mine diagonal-dleft
            if(g.board[r + 1][c - 1] == '*')
                nearby_mine_count++;
            // Check for mine to the left
            if(g.board[r][c - 1] == '*')
                nearby_mine_count++;
        }
        // Check whether the rows above can be checked
        if(r != 0)
        {
            // Check for mine above
            if(g.board[r - 1][c] == '*')
                nearby_mine_count++;
            // Check for mine diagonal-uright
            if(g.board[r - 1][c + 1] == '*')
                nearby_mine_count++;
            // Check whether columns to the left can be checked
            if(c != 0)
            {
                // Check for mine diagonal-uleft
                if(g.board[r - 1][c - 1] == '*')
                    nearby_mine_count++;
            }
        }
    }
    // Check if selection is in last row
    if(r == (BOARD_SIZE - 1) && c != (BOARD_SIZE - 1))
    {
        // Check for mine above
        if(g.board[r - 1][c] == '*')
            nearby_mine_count++;
        // Check for mine diagonal-uright
        if(g.board[r - 1][c + 1] == '*')
            nearby_mine_count++;
    }
    // Check if selection is in last column
    if(c == (BOARD_SIZE - 1) && r != (BOARD_SIZE - 1))
    {
        // Check for mine to the left
        if(g.board[r][c - 1] == '*')
            nearby_mine_count++;
        // Check for mine diagonal-dleft
        if(g.board[r + 1][c - 1] == '*')
            nearby_mine_count++;
    }
    // Check whether selection is last in element
    if(r == (BOARD_SIZE - 1) && c == (BOARD_SIZE - 1))
    {
        // Check for mine to the left
        if(g.board[r][c - 1] == '*')
            nearby_mine_count++;
        // Check for mine diagonal-dleft
        if(g.board[r - 1][c - 1] == '*')
            nearby_mine_count++;
        // Check for mine above
        if(g.board[r - 1][c] == '*')
            nearby_mine_count++;
    }

    return nearby_mine_count;
}

/* Check if user has won game */
int CheckGameState()
{
    int row, col;

    for(row = 0; row < BOARD_SIZE; row++)
        for(col = 0; col < BOARD_SIZE; col++)
        {
            if(g.game_board[row][col] == 'o' && g.board[row][col] != '*')
                return FALSE;
        }

    return TRUE;
}
// Ask user if they wish to play again.
void playAgain()
{
    char ans;

    printf("\n\nWould you like to play again? (y/n) --> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start();
    }

    else
    {
        printf("\n\nThanks for playing! Bye.");
        (void) getchar();
        exit(EXIT_SUCCESS);
    }
}
// Displays the welcome message, and the GNU License
void header()
{
    puts("-----------------------Welcome to Minesweeper!---------------------------");
    puts("------------------By: Scott Mason & Jordan Greene------------------------");
    puts("-------------------------------------------------------------------------");
    puts("\n");

    printf("Please enter your name: ");
    scanf("%c", g.username);
}

void start() {
    g.lost = 0;    // User hasn't lost yet
    // Build both game boards (one for the user to see,
    // and the one with the mines).
    makeFrontBoard();
    makeBackBoard();

    // Start playing game
    do {
        playGame();
        printFrontBoard();
    } while (g.lost != 1);    // While the user hasn't lost, loop.

    // Once user is lost, print the board with all the mines.
    printBackBoard();

    // Play again?
    playAgain();
}