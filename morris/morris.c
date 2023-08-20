/* By Ethan Hughes */
/* Written on 7/7/2023 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BOARDSIZE 21
#define MAXMOVES 4200
#define TIMELIMIT 1
#define MIDGAMETURN 15

int closeMill(int j, char *b, char C){
    //char C = b[j];
    //if(C == 'x'){
    //    return 0;//False
	//}
    //groups = [[0, 6, 18], [1, 11, 20], [2, 7, 15], [3, 10, 17], [4, 8, 12], [5, 9, 14], [6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17], [18, 19, 20]]
    //for pair in groups:
    //    if j in pair:
    //        if pair.index(j) == 0 and b[pair[1]] == C and b[pair[2]] == C:
    //            return True
    //        elif pair.index(j) == 1 and b[pair[0]] == C and b[pair[2]] == C:
    //            return True
    //        elif pair.index(j) == 2 and b[pair[0]] == C and b[pair[1]] == C:
    //            return True
    //return False
    switch(j){
        case 0:
            return b[6] == C && b[18] == C;
        case 1:
            return b[11] == C && b[20] == C;
        case 2:
            return b[7] == C && b[15] == C;
        case 3:
            return b[10] == C && b[17] == C;
        case 4:
            return b[8] == C && b[12] == C;
        case 5:
            return b[9] == C && b[14] == C;
        case 6:
            return (b[0] == C && b[18] == C) || (b[7] == C && b[8] == C);
        case 7:
            return (b[2] == C && b[15] == C) || (b[6] == C && b[8] == C);
        case 8:
            return (b[4] == C && b[12] == C) || (b[6] == C && b[7] == C);
        case 9:
            return (b[5] == C && b[14] == C) || (b[10] == C && b[11] == C);
        case 10:
            return (b[3] == C && b[17] == C) || (b[9] == C && b[11] == C);
        case 11:
            return (b[1] == C && b[20] == C) || (b[9] == C && b[10] == C);
        case 12:
            return (b[4] == C && b[8] == C) || (b[13] == C && b[14] == C);
        case 13:
            return (b[16] == C && b[19] == C) || (b[12] == C && b[14] == C);
        case 14:
            return (b[5] == C && b[9] == C) || (b[12] == C && b[13] == C);
        case 15:
            return (b[2] == C && b[7]==15) || (b[16] == C && b[17] == C);
        case 16:
            return (b[13] == C && b[19] == C) || (b[15] == C && b[17] == C);
        case 17:
            return (b[3] == C && b[10] == C) || (b[15] == C && b[16] == C);
        case 18:
            return (b[0] == C && b[6] == C) || (b[19] == C && b[20] == C);
        case 19:
            return (b[13] == C && b[16] == C) || (b[18] == C && b[20] == C);
        case 20:
            return (b[1] == C && b[11] == C) || (b[18] == C && b[19] == C);
	}
	printf("ERROR IN MILLS.\n");
	return -1; //Error case
}

void neighbors(int j, int *ncount, int *ret){
    switch (j){
        case 0:
			*ncount = 2;
            memcpy(ret, (int[]){1,6}, (*ncount)*sizeof(int));
            return;
        case 1:
			*ncount = 2;
            memcpy(ret, (int[]){0,11}, (*ncount)*sizeof(int));
            return;
        case 2:
			*ncount = 2;
            memcpy(ret, (int[]){3,7}, (*ncount)*sizeof(int));
            return;
        case 3:
			*ncount = 2;
            memcpy(ret, (int[]){2,10}, (*ncount)*sizeof(int));
            return;
        case 4:
			*ncount = 2;
            memcpy(ret, (int[]){5,8}, (*ncount)*sizeof(int));
            return;
        case 5:
			*ncount = 2;
            memcpy(ret, (int[]){4,9}, (*ncount)*sizeof(int));
            return;
        case 6:
			*ncount = 3;
            memcpy(ret, (int[]){0,7,18}, (*ncount)*sizeof(int));
            return;
        case 7:
			*ncount = 4;
            memcpy(ret, (int[]){2,6,8,15}, (*ncount)*sizeof(int));
            return;
        case 8:
			*ncount = 3;
            memcpy(ret, (int[]){4,7,12}, (*ncount)*sizeof(int));
            return;
        case 9:
			*ncount = 3;
            memcpy(ret, (int[]){5,10,14}, (*ncount)*sizeof(int));
            return;
        case 10:
			*ncount = 4;
            memcpy(ret, (int[]){3,9,11,17}, (*ncount)*sizeof(int));
            return;
        case 11:
			*ncount = 3;
            memcpy(ret, (int[]){1,10,20}, (*ncount)*sizeof(int));
            return;
        case 12:
			*ncount = 2;
            memcpy(ret, (int[]){8,13}, (*ncount)*sizeof(int));
            return;
        case 13:
			*ncount = 3;
            memcpy(ret, (int[]){12,14,16}, (*ncount)*sizeof(int));
            return;
        case 14:
			*ncount = 2;
            memcpy(ret, (int[]){9,13}, (*ncount)*sizeof(int));
            return;
        case 15:
			*ncount = 2;
            memcpy(ret, (int[]){7,16}, (*ncount)*sizeof(int));
            return;
        case 16:
			*ncount = 4;
            memcpy(ret, (int[]){13,15,17,19}, (*ncount)*sizeof(int));
            return;
        case 17:
			*ncount = 2;
            memcpy(ret, (int[]){10,16}, (*ncount)*sizeof(int));
            return;
        case 18:
			*ncount = 2;
            memcpy(ret, (int[]){6,19}, (*ncount)*sizeof(int));
            return;
        case 19:
			*ncount = 3;
            memcpy(ret, (int[]){16,18,20}, (*ncount)*sizeof(int));
            return;
        case 20:
			*ncount = 2;
            memcpy(ret, (int[]){11,19}, (*ncount)*sizeof(int));
            return;
	}
}

//Take a piece if its not in a mill
char *GenerateRemove(char *gamestate, char *L){
    int mills = 1;
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'B'){
            if(!closeMill(location, gamestate, 'B')){
				char b[BOARDSIZE+1];
				b[BOARDSIZE] = 0;
                memcpy(b, gamestate, BOARDSIZE);
                b[location] = 'x';
				strcat(L, b);
                mills = 0;
            }
        }
    }
    if(mills){
        strcat(L, gamestate);
    }
    return L;
}

//Add a new piece
char *GenerateAdd(char *gamestate){
    char *l = (char *) calloc(MAXMOVES, 1);
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'x'){
			char b[BOARDSIZE+1];
			b[BOARDSIZE] = 0;
            memcpy(b, gamestate, BOARDSIZE);
            b[location] = 'W';
            if(closeMill(location, b, 'W')){
                GenerateRemove(b, l);
			} else {
                strcat(l, b);
			}
		}
	}
    return l;
}

//Move a piece to an adjacent space
char *GenerateMove(char *gamestate){
    char *L = (char *) calloc(MAXMOVES, 1);
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'W'){
			int ncount = 0;
            int n[4];
            neighbors(location, &ncount, n);
            for(int i = 0; i < ncount; i++){
				int j = n[i];
                if(gamestate[j] == 'x'){
					char b[BOARDSIZE+1];
					b[BOARDSIZE] = 0;
                    memcpy(b, gamestate, BOARDSIZE);
                    b[location] = 'x';
                    b[j] = 'W';
                    if(closeMill(j, b, 'W')){
                        GenerateRemove(b, L);
					} else {
						strcat(L, b);
					}
				}
			}
			//free(n); //Free neighbors array
		}
	}
    return L;
}

//Jump a piece to anywhere on the board
char *GenerateHopping(char *gamestate){
    char *L = (char *) calloc(MAXMOVES, 1);
    for(int alpha = 0; alpha < BOARDSIZE; alpha++){
        if(gamestate[alpha] == 'W'){
            for(int beta = 0; beta < BOARDSIZE; beta++){
                if(gamestate[beta] == 'x'){
					char b[BOARDSIZE+1];
					b[BOARDSIZE] = 0;
                    memcpy(b, gamestate, BOARDSIZE);
                    b[alpha] = 'x';
                    b[beta] = 'W';
                    if(closeMill(beta, b, 'W')){
                        GenerateRemove(b, L);
					} else {
						strcat(L, b);
					}
				}
			}
		}
	}
    return L;
}

//GenerateMovesMidgameEndgame
char *moves(char *gamestate, int opening){
	if(opening){
		return GenerateAdd(gamestate);
	}
    int wcount = 0;
    //if the board has at least 3 white pieces return hopping moves, else return normal moves
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'W'){
            wcount += 1;
        }
    }
    if (wcount > 3){
        return GenerateMove(gamestate);
    } else{
        return GenerateHopping(gamestate);
    }
}

void static_eval(char *gamestate, int *eval, int *terminal, int opening, int turn){
    //Evaluates how good the position is
    int whitep = 0;
    int blackp = 0;
    *eval = 0;
    int ncount = 1;
    int n[4];
    for(int location = 0; location < BOARDSIZE; location++){
        neighbors(location, &ncount, n);
        if(gamestate[location] == 'W'){
            whitep += ncount;
            *eval += 1;
        } else if( gamestate[location] == 'B'){
            blackp += ncount;
            *eval -= 1;
        }
        if(gamestate[location] == 'x' && closeMill(location, gamestate, 'W')){
            *eval += (1-(turn % 2))+1; //1 on opponent's turn, 2 on your turn
        } else if(gamestate[location] == 'x' && closeMill(location, gamestate, 'B')){
            *eval -= (turn % 2)+1; //2 on opponent's turn, 1 on your turn
        }
    }
    *terminal = 0; //False
	if(opening){
		return;
	}
    //Evaluates if the board is in a terminal position
	char *movelist = moves(gamestate, opening);
	int wmovesleft = strlen(movelist)/BOARDSIZE;
	free(movelist); //Free dynamic movelist
    for(int i = 0; i < BOARDSIZE; i++){
        if(gamestate[i] == 'W'){
            gamestate[i] = 'B';
        } else if(gamestate[i] == 'B'){
            gamestate[i] = 'W';
        }
    }
	movelist = moves(gamestate, opening);
	int bmovesleft = strlen(movelist)/BOARDSIZE;
	free(movelist); //Free dynamic movelist
    for(int i = 0; i < BOARDSIZE; i++){
        if(gamestate[i] == 'W'){
            gamestate[i] = 'B';
        } else if(gamestate[i] == 'B'){
            gamestate[i] = 'W';
        }
    }
    *eval = 1000*(*eval) - bmovesleft + wmovesleft;
    if(blackp <= 2){
        //printf("TEST white\n");
        *terminal = 1; //True
        *eval = 40000;
	} else if(whitep <= 2){
        //printf("TEST black\n");
        *terminal = 1; //True
        *eval = -40000;
	} else if(wmovesleft == 0){
        //printf("TEST moves\n");
        *terminal = 1; //True
        *eval = -40000;
	} else if(bmovesleft == 0){
        *terminal = 1; //True
        *eval = 40000;
    }
}

void swapblack(char *gamestate, int depth, int a, int b, int max_depth, char *move, int *estimate, long *evals, int *retdepth, int opening, int start, int turn);

//returns best next move, evaluation for said move, and number of static evaluations
void alphabeta(char *gamestate, int depth, int a, int b, int max_depth, char *move, int *estimate, long *evals, int *retdepth, int opening, int start, int turn){
	if(time(NULL) - start > TIMELIMIT){
		return;
	}
    if(turn + depth > MIDGAMETURN){ //When searching at depth switch from opening to midgame
        opening = 0;
    }
	int eval = 0;
	int terminal = 0;
    static_eval(gamestate, &eval, &terminal, opening, turn+depth);
    if (depth == max_depth || terminal){ //if max depth reached or end game reached then bubble up
		*estimate = eval;
		*evals = 1;
        *retdepth = depth;
        return; //return current static evaluation, and 1 eval count
    }
    int besteval = -1000000; //store the equivalent of -/+ infinity to be overwritten
    int bestdepth = 60; //store the equivalent of -/+ infinity to be overwritten (for reaching faster wins)
    if(depth > 0){
        besteval = eval * (((turn % 2)*2)-1);
        bestdepth = depth;
    }
    long evaluations = 1; //number of times the board has been evaluated
    char bestmove[BOARDSIZE]; //best move from the current gamestate
	char board[BOARDSIZE];
	char *boards = moves(gamestate, opening);
	int len = strlen(boards)/BOARDSIZE;
	int ptr = 0;
    for(int i = 0; i < len; i++){
		memcpy(board, &(boards[ptr]), BOARDSIZE);
		ptr += BOARDSIZE;
        swapblack(board, depth+1, a, b, max_depth, move, estimate, evals, retdepth, opening, start, turn); //recursive call for each possible move
        *estimate *= -1;
        evaluations += *evals; //gather up prior evaluation counts
        if(*estimate > besteval || (*estimate == besteval && *retdepth < bestdepth)){
            besteval = *estimate; //get max for max level or min for min level
            bestdepth = *retdepth;
			strcpy(bestmove, board);
			//memcpy(bestmove, &(boards[i*BOARDSIZE]), BOARDSIZE); //get best move for given level
        }
        //alpha best pruning
        if((depth % 2 == 0 && besteval > b) || (depth % 2 == 1 && -1*besteval < a)){
            break;
        }
        //update alpha beta values
        if(depth % 2 == 0 && besteval > a){
            a = besteval;
        } else if(depth % 2 == 1 && -1*besteval < b){
            b = besteval;
        }
    }
	free(boards); //Free dynamic movelist
	strcpy(move, bestmove);
	*estimate = besteval;
    *retdepth = bestdepth;
	*evals = evaluations;
    return;
}

//Switch out white black pieces to make move and then switch back
void swapblack(char *gamestate, int depth, int a, int b, int max_depth, char *move, int *estimate, long *evals, int *retdepth, int opening, int start, int turn){
    //printf("TEST1: %s\n", gamestate);
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'W'){
            gamestate[location] = 'B';
        } else if(gamestate[location] == 'B'){
            gamestate[location] = 'W';
        }
    }
    //printf("TEST2: %s\n", gamestate);
    alphabeta(gamestate, depth, a, b, max_depth, move, estimate, evals, retdepth, opening, start, turn);
    //printf("TEST3: %s\n", move);
    for(int location = 0; location < BOARDSIZE; location++){
        if(gamestate[location] == 'W'){
            gamestate[location] = 'B';
        } else if(gamestate[location] == 'B'){
            gamestate[location] = 'W';
        }
        //if(depth == 0){
            if(move[location] == 'W'){
                move[location] = 'B';
            } else if(move[location] == 'B'){
                move[location] = 'W';
            }
        //}
    }
    //printf("TEST4: %s\n", move);
    return;
}

//Pretty print board
void boardprint(char *gamestate){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            switch(i){
                case 0:
                    switch(j){
                        case 0:
                            printf("%c", gamestate[0]);
                            break;
                        case 6:
                            printf("%c", gamestate[1]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 1:
                    switch(j){
                        case 1:
                            printf("%c", gamestate[2]);
                            break;
                        case 5:
                            printf("%c", gamestate[3]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 2:
                    switch(j){
                        case 2:
                            printf("%c", gamestate[4]);
                            break;
                        case 4:
                            printf("%c", gamestate[5]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 3:
                    switch(j){
                        case 0:
                            printf("%c", gamestate[6]);
                            break;
                        case 1:
                            printf("%c", gamestate[7]);
                            break;
                        case 2:
                            printf("%c", gamestate[8]);
                            break;
                        case 4:
                            printf("%c", gamestate[9]);
                            break;
                        case 5:
                            printf("%c", gamestate[10]);
                            break;
                        case 6:
                            printf("%c", gamestate[11]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 4:
                    switch(j){
                        case 2:
                            printf("%c", gamestate[12]);
                            break;
                        case 3:
                            printf("%c", gamestate[13]);
                            break;
                        case 4:
                            printf("%c", gamestate[14]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 5:
                    switch(j){
                        case 1:
                            printf("%c", gamestate[15]);
                            break;
                        case 3:
                            printf("%c", gamestate[16]);
                            break;
                        case 5:
                            printf("%c", gamestate[17]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
                case 6:
                    switch(j){
                        case 0:
                            printf("%c", gamestate[18]);
                            break;
                        case 3:
                            printf("%c", gamestate[19]);
                            break;
                        case 6:
                            printf("%c", gamestate[20]);
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                    break;
            }
        }
        printf("\n");
    }
    return;
}

int main(int argc, char ** argv){
    int opening = 1;
    int black = 0;
    int turncount = 0;
    //Get initial gamestate
    char test[BOARDSIZE] = "xxxxxxxxxxxxxxxxxxxxx";
    char *gamestate = test;
	//char *gamestate = argv[1];
	//int max_depth_extra = atoi(argv[2]);
    if(argc > 2){
        opening = atoi(argv[2]);
    }
    if(argc > 3){
        black = atoi(argv[3]);
    }
    if(argc > 4){
        turncount = atoi(argv[4]);
    }
    //evaluate with minimax
	char newboard[BOARDSIZE];
	int estimate;
	long evaluations;
    int retdepth;
	char finished_board[BOARDSIZE];
	int finished_estimate = -1000000;
	long finished_evaluations;
	int depth_reached;
	int bestdepth = 60;
    
    while(1){
        evaluations = 0;
        estimate = 0;
        retdepth = 0;
        if(turncount > MIDGAMETURN){
            opening = 0;
        }
        black = turncount % 2;
        int start = time(NULL);
        for(int max_depth = 1; max_depth < 10; max_depth++){
            if(black){
                swapblack(gamestate, 0, -1000000, 1000000, max_depth, newboard, &estimate, &evaluations, &retdepth, opening, start, turncount);
            } else {
                alphabeta(gamestate, 0, -1000000, 1000000, max_depth, newboard, &estimate, &evaluations, &retdepth, opening, start, turncount);
            }
            if(time(NULL)-start > TIMELIMIT){
                finished_evaluations = evaluations;
                /*if(estimate > finished_estimate || (estimate == finished_estimate && retdepth < bestdepth)){				
                    memcpy(finished_board, newboard, BOARDSIZE);
                    finished_estimate = estimate;
                    depth_reached = max_depth;
                }*/
                break;
            }
            memcpy(finished_board, newboard, BOARDSIZE);
            finished_evaluations = evaluations;
            finished_estimate = estimate;
            depth_reached = max_depth;
		    bestdepth = retdepth;
        }
        //write best move
        printf("Turn %d: ", turncount+1);
        if(black){
            printf("Black's Turn\n");
        } else {
            printf("White's Turn\n");
        }
        printf("Board Position: %s\n", finished_board);
        printf("Positions evaluated by static estimation: %ld\n", finished_evaluations);
        printf("MINIMAX estimate: %d\n", finished_estimate);
        printf("Iterative Deepening reached depth of %d\n", depth_reached);
        printf("Time elapsed: %ld\n", time(NULL)-start);
        printf("Best result from depth: %d\n", bestdepth);
        boardprint(finished_board);
        int terminal;
        int eval;
        static_eval(finished_board, &eval, &terminal, opening, turncount);
        if(terminal){
            if(black){
                printf("BLACK WINS!\n");
            } else {
                printf("WHITE WINS!\n");
            }
            break;
        }
        if(turncount == 60){
            printf("GAME TIE\n");
            break;
        }
        turncount++;
        memcpy(gamestate, finished_board, BOARDSIZE);
    }
    return 0;
}