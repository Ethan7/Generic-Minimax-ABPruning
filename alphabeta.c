/* Written by Ethan Hughes */
/* Written on 7/3/2023 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TIMELIMIT 1

void *startstate(int gametype);

void *allocmove(int gametype);

void freemove(void *gamestate, int gametype);

void *openmove(char *filename, int gametype);

void copymove(void *action, void *gamestate, int gametype);

void **moves(void *gamestate, int turn, int *movecount, int *movesize, int gametype);

void static_eval(void *gamestate, int *eval, int *terminal, int turn, int gametype);

void printmove(void *gamestate, int gametype);

//returns best next move, evaluation for said move, and number of static evaluations
void alphabeta(void *gamestate, int depth, int a, int b, int max_depth, void *action, int *estimate, int *evals, int turn, long start, int gametype, int *terminate){
	if(time(NULL) - start > TIMELIMIT){
		return;
	}
    int eval = 0;
	int terminal = 0;
    static_eval(gamestate, &eval, &terminal, turn, gametype);
    if (depth == max_depth || terminal){ //if max depth reached or end game reached then bubble up
        if(terminal && depth == 0){
            *terminate = 0;
        }
        copymove(action, gamestate, gametype);
		*estimate = eval;
		*evals = 1;
        return; //return unmoved state, current static evaluation, and 1 eval count
    }
    int besteval = ((depth % 2)*2-1) * 1000000; //store the equivalent of -/+ infinity to be overwritten
    int evaluations = 1; //number of times the board has been evaluated
    void *bestmove = NULL; //best move from the current gamestate
    int movecount = 0;
    int movesize = 0;
	void **movelist = moves(gamestate, turn, &movecount, &movesize, gametype);
    for(int i = 0; i < movecount; i++){
        void *move = movelist[i];
        alphabeta(move, depth+1, a, b, max_depth, action, estimate, evals, turn+1, start, gametype, terminate); //recursive call for each possible move
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
    copymove(action, bestmove, gametype);
	*estimate = besteval;
	*evals = evaluations;
    for(int i = 0; i < movecount; i++){
        freemove(movelist[i], gametype);
    }
    free(movelist); //TODO: Maybe change to freemovelist (new function)
    return;
}

int main(int argc, char const* argv[]){
    if(argc == 0){ //Change the number of gametypes when I add more games
        printf("usage: ./alphabeta [gametype(0...0)] [continuous-mode(0/1)] [boardstate-filename(string)] [current-turn(0...99)]");
    }
    int gametype = 0;
    if(argc > 1){
        gametype = atoi(argv[1]);
    }
    int continuous = 0;
    if(argc > 2){
        continuous = atoi(argv[2]);
    }
    void *gamestate = startstate(gametype);
    int turn = 0;
    if(argc > 4){
        freemove(gamestate, gametype);
        gamestate = openmove((char *)argv[3], gametype);
        turn = atoi(argv[4]);
    }

    //evaluate with minimax
    void *newstate = allocmove(gametype);
    void *newmove = allocmove(gametype);
    int terminate = 1;
    do{
        int estimate = 0;
        int evaluations = 0;
        int finalestimate = 0;
        int finalevals = 0;
        int max_depth = 1;
        long start = time(NULL);
        while(time(NULL) - start < TIMELIMIT){
            copymove(newmove, newstate, gametype);
            finalestimate = estimate;
            finalevals = evaluations;
            alphabeta(gamestate, 0, -1000000, 1000000, max_depth, newstate, &estimate, &evaluations, turn, start, gametype, &terminate);
            max_depth++;
        }
        //write best move
        printmove(newmove, gametype);
        printf("Positions evaluated by static estimation: %d\n", finalevals);
        printf("MINIMAX estimate: %d\n", finalestimate);
        printf("Final depth reached by iterative deepening: %d\n", max_depth-1);
        copymove(gamestate, newmove, gametype);
        turn++;
    } while (continuous && terminate);

    return 0;
}