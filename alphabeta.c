/* Written by Ethan Hughes */
/* Written on 7/3/2023 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TIMELIMIT 1

//Get the starting state of the game
void *startstate();

//Dynamically allocate a move
void *allocmove();

//Free a dynamically allocated move
void freemove(void *gamestate);

//Open a move from a file and return it
void *openmove(char *filename);

//Save a move to a file
void savemove(char *filename, void *gamestate);

//Copy a single move from one pointer to another
void copymove(void *action, void *gamestate);

//Return a list of all moves that can be taken from the given state and how many there are
void **moves(void *gamestate, int turn, int *movecount);

//Get the static evaluation from a given move including whether it is terminal
void static_eval(void *gamestate, int *eval, int *terminal, int turn);

//Print a move
void printmove(void *gamestate);

//returns best next move, evaluation for said move, and number of static evaluations
void alphabeta(void *gamestate, int depth, int a, int b, int max_depth, void *action, int *estimate, int *evals, int turn, long start, int *terminate){
	if(time(NULL) - start > TIMELIMIT){
		return;
	}
    int eval = 0;
	int terminal = 0;
    static_eval(gamestate, &eval, &terminal, turn);
    if (depth == max_depth || terminal){ //if max depth reached or end game reached then bubble up
        if(terminal && depth == 0){
            *terminate = 0;
        }
        copymove(action, gamestate);
		*estimate = eval;
		*evals = 1;
        return; //return unmoved state, current static evaluation, and 1 eval count
    }
    int besteval = ((depth % 2)*2-1) * 1000000; //store the equivalent of -/+ infinity to be overwritten
    int evaluations = 1; //number of times the board has been evaluated
    void *bestmove = NULL; //best move from the current gamestate
    int movecount = 0;
	void **movelist = moves(gamestate, turn, &movecount);
    for(int i = 0; i < movecount; i++){
        void *move = movelist[i];
        alphabeta(move, depth+1, a, b, max_depth, action, estimate, evals, turn+1, start, terminate); //recursive call for each possible move
        evaluations += *evals; //gather up prior evaluation counts
        if((depth % 2 == 0 && *estimate > besteval) || (depth % 2 == 1 && *estimate < besteval)){
            besteval = *estimate; //get max for max level or min for min level
            //bestdepth = *retdepth;
            bestmove = move; //get best move for given level
        }
        //alpha best pruning
        if((depth % 2 == 0 && besteval > b) || (depth % 2 == 1 && besteval < a)){
            break;
        }
        //update alpha beta values
        if(depth % 2 == 0 && besteval > a){
            a = besteval;
        } else if(depth % 2 == 1 && besteval < b){
            b = besteval;
        }
    }
    if(bestmove == NULL){
        return;
    }
    copymove(action, bestmove);
	*estimate = besteval;
	*evals = evaluations;
    for(int i = 0; i < movecount; i++){
        freemove(movelist[i]);
    }
    free(movelist);
    return;
}

int main(int argc, char const* argv[]){
    //Program argument handling
    if(argc == 0){ //different programs are compiled for each game type
        printf("usage: ./[program name (alphabeta-chess/alphabeta-checkers/...)] [continuous-mode(0/1)] [boardstate-saving-filename(string)] [boardstate-loading-filename(string)] [current-turn(0...99)]");
    }
    int continuous = 0;
    if(argc > 1){
        continuous = atoi(argv[1]);
    }
    char *savegame = NULL;
    if(argc > 2){
        savegame = argv[2];
    }
    void *gamestate = startstate();
    int turn = 0;
    if(argc > 4){
        freemove(gamestate);
        gamestate = openmove((char *)argv[3]);
        turn = atoi(argv[4]);
    }

    void *newstate = allocmove();
    void *newmove = allocmove();
    //Keep finding best next move until one side wins if continuous
    int terminate = 1;
    do{
        //evaluate with minimax
        int estimate = 0;
        int evaluations = 0;
        int finalestimate = 0;
        int finalevals = 0;
        int max_depth = 1;
        long start = time(NULL);
        while(time(NULL) - start < TIMELIMIT){
            //Store last depth's best move
            copymove(newmove, newstate);
            finalestimate = estimate;
            finalevals = evaluations;
            //Find this depth's best move (iterative deepening works best with high branching factor games)
            alphabeta(gamestate, 0, -1000000, 1000000, max_depth, newstate, &estimate, &evaluations, turn, start, &terminate);
            max_depth++;
        }
        //write best move
        printmove(newmove);
        printf("Positions evaluated by static estimation: %d\n", finalevals);
        printf("MINIMAX estimate: %d\n", finalestimate);
        printf("Final depth reached by iterative deepening: %d\n", max_depth-1);
        //Copy the new state to the current state and increase the turn count
        copymove(gamestate, newmove);
        turn++;
    } while (continuous && terminate);
    if(terminate == 0){
        printf("Game terminated at turn: %d\n", turn);
    }
    if(savegame != NULL){
        savemove(savegame, newmove);
    }
    freemove(newstate);
    freemove(newmove);
    freemove(gamestate);

    return 0;
}