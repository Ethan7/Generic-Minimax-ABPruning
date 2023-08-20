/* By Ethan Hughes */
/* Written 3/5/2020 */
/* Revised 7/3/2023 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARCADE 0
#define CHESS 14

#define EMPTY -1
#define P1PAWN 17
#define P1ROOK 18
#define P1BISHOP 19
#define P1KNIGHT 20
#define P1QUEEN 21
#define P1KING 22
#define P2PAWN 23
#define P2ROOK 24
#define P2BISHOP 25
#define P2KNIGHT 26
#define P2QUEEN 27
#define P2KING 28

struct chess{
	int p1castle1;
	int p1castle2;
	int p2castle1;
	int p2castle2;
	int p1kingx;
	int p1kingy;
	int p2kingx;
	int p2kingy;
	int p1enpassant;
	int p2enpassant;
	int chessboard[8][8];
};

void *allocmove(int gametype){
	struct chess *chessboard = (struct chess *) calloc(1, sizeof(struct chess));
	return (void *) chessboard;
}

void freemove(void *gamestate, int gametype){
	struct chess *chessboard = (struct chess *) gamestate;
	free(chessboard);
}

void copymove(void *action, void *gamestate, int gametype){
	struct chess *copyboard = (struct chess *) action;
	struct chess *chessboard = (struct chess *) gamestate;
	memcpy(copyboard, chessboard, sizeof(struct chess));
}

void printmove(void *gamestate, int gametype){
	struct chess *chess_state = (struct chess *) gamestate;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			switch(chess_state->chessboard[j][i]){
				case P1PAWN:
					printf("P1");
					break;
				case P1KNIGHT:
					printf("N1");
					break;
				case P1BISHOP:
					printf("B1");
					break;
				case P1ROOK:
					printf("R1");
					break;
				case P1QUEEN:
					printf("Q1");
					break;
				case P1KING:
					printf("K1");
					break;
				case P2PAWN:
					printf("P2");
					break;
				case P2KNIGHT:
					printf("N2");
					break;
				case P2BISHOP:
					printf("B2");
					break;
				case P2ROOK:
					printf("R2");
					break;
				case P2QUEEN:
					printf("Q2");
					break;
				case P2KING:
					printf("K2");
					break;
				case EMPTY:
					printf("  ");
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}

//Deternube if after the given move your king is left exposed
int kingatrisk(struct chess *chess_state, int beforex, int beforey, int afterx, int aftery, int pturn){
	int placemarker = chess_state->chessboard[afterx][aftery];
	chess_state->chessboard[afterx][aftery] = chess_state->chessboard[beforex][beforey];
	chess_state->chessboard[beforex][beforey] = EMPTY;
	int kingx = 0;
	int kingy = 0;
	//Get coords of king we are checking
	if(pturn){
		kingx = chess_state->p2kingx;
		kingy = chess_state->p2kingy;
		if(chess_state->chessboard[chess_state->p2kingx][chess_state->p2kingy] != P2KING){
			kingx = afterx;
			kingy = aftery;
		}
	} else {
		kingx = chess_state->p1kingx;
		kingy = chess_state->p1kingy;
		if(chess_state->chessboard[chess_state->p1kingx][chess_state->p1kingy] != P1KING){
			kingx = afterx;
			kingy = aftery;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx+x > 7 || (chess_state->chessboard[kingx+x][kingy]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx+x][kingy]-P1PAWN) % 6 == P1ROOK-P1PAWN || (chess_state->chessboard[kingx+x][kingy]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx+x][kingy]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx-x < 0 || (chess_state->chessboard[kingx-x][kingy]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx-x][kingy]-P1PAWN) % 6 == P1ROOK-P1PAWN || (chess_state->chessboard[kingx-x][kingy]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx-x][kingy]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingy+x > 7 || (chess_state->chessboard[kingx][kingy+x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx][kingy+x]-P1PAWN) % 6 == P1ROOK-P1PAWN || (chess_state->chessboard[kingx][kingy+x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx][kingy+x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingy-x < 0 || (chess_state->chessboard[kingx][kingy-x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx][kingy-x]-P1PAWN) % 6 == P1ROOK-P1PAWN || (chess_state->chessboard[kingx][kingy-x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx][kingy-x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx+x > 7 || kingy+x > 7 || (chess_state->chessboard[kingx+x][kingy+x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx+x][kingy+x]-P1PAWN) % 6 == P1BISHOP-P1PAWN || (chess_state->chessboard[kingx+x][kingy+x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx+x][kingy+x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx-x < 0 || kingy+x > 7 || (chess_state->chessboard[kingx-x][kingy+x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx-x][kingy+x]-P1PAWN) % 6 == P1BISHOP-P1PAWN || (chess_state->chessboard[kingx-x][kingy+x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx-x][kingy+x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx+x > 7 || kingy-x < 0 || (chess_state->chessboard[kingx+x][kingy-x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx+x][kingy-x]-P1PAWN) % 6 == P1BISHOP-P1PAWN || (chess_state->chessboard[kingx+x][kingy-x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx+x][kingy-x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	for(int x = 1; x < 8; x++){
		if(kingx-x < 0 || kingy-x < 0 || (chess_state->chessboard[kingx-x][kingy-x]-P1PAWN) / 6 == pturn){
			break;
		} else if((chess_state->chessboard[kingx-x][kingy-x]-P1PAWN) % 6 == P1BISHOP-P1PAWN || (chess_state->chessboard[kingx-x][kingy-x]-P1PAWN) % 6 == P1QUEEN-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		} else if((chess_state->chessboard[kingx-x][kingy-x]-P1PAWN) / 6 > -1){
			break;
		}
	}
	if(kingx+2 < 8 && kingy+1 < 8 && (chess_state->chessboard[kingx+2][kingy+1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+2][kingy+1]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+2 < 8 && kingy-1 > -1 && (chess_state->chessboard[kingx+2][kingy-1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+2][kingy-1]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+1 < 8 && kingy+2 < 8 && (chess_state->chessboard[kingx+1][kingy+2]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+1][kingy+2]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+1 < 8 && kingy-2 > -1 && (chess_state->chessboard[kingx+1][kingy-2]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+1][kingy-2]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-2 > -1 && kingy+1 < 8 && (chess_state->chessboard[kingx-2][kingy+1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-2][kingy+1]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-2 > -1 && kingy-1 > -1 && (chess_state->chessboard[kingx-2][kingy-1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-2][kingy-1]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-1 > -1 && kingy+2 < 8 && (chess_state->chessboard[kingx-1][kingy+2]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-1][kingy+2]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-1 > -1 && kingy-2 > -1 && (chess_state->chessboard[kingx-1][kingy-2]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-1][kingy-2]-P1PAWN) % 6 == P1KNIGHT-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+1 < 8 && (chess_state->chessboard[kingx+1][kingy]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+1][kingy]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-1 > -1 && (chess_state->chessboard[kingx-1][kingy]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-1][kingy]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingy+1 < 8 && (chess_state->chessboard[kingx][kingy+1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx][kingy+1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingy-1 > -1 && (chess_state->chessboard[kingx][kingy-1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx][kingy-1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+1 < 8 && kingy+1 < 8 && (chess_state->chessboard[kingx+1][kingy+1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+1][kingy+1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
		if(pturn == 0 && chess_state->chessboard[kingx+1][kingy+1] == P2PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx+1 < 8 && kingy-1 > -1 && (chess_state->chessboard[kingx+1][kingy-1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx+1][kingy-1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
		if(pturn == 1 && chess_state->chessboard[kingx+1][kingy-1] == P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-1 > -1 && kingy+1 < 8 && (chess_state->chessboard[kingx-1][kingy+1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-1][kingy+1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
		if(pturn == 0 && chess_state->chessboard[kingx-1][kingy+1] == P2PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	if(kingx-1 > -1 && kingy-1 > -1 && (chess_state->chessboard[kingx-1][kingy-1]-P1PAWN) / 6 != pturn){
		if((chess_state->chessboard[kingx-1][kingy-1]-P1PAWN) % 6 == P1KING-P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
		if(pturn == 1 && chess_state->chessboard[kingx-1][kingy-1] == P1PAWN){
			chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
			chess_state->chessboard[afterx][aftery] = placemarker;
			return 1;
		}
	}
	chess_state->chessboard[beforex][beforey] = chess_state->chessboard[afterx][aftery];
	chess_state->chessboard[afterx][aftery] = placemarker;
	return 0;
}

struct chess *getboard(struct chess *chess_state, int buttonx, int buttony, int chosenx, int choseny, int turn){
	struct chess *newboard = (struct chess *) calloc(1, sizeof(struct chess));
	memcpy(newboard, chess_state, sizeof(struct chess));
	//Move piece
	newboard->chessboard[buttonx][buttony] = newboard->chessboard[chosenx][choseny];
	newboard->chessboard[chosenx][choseny] = EMPTY;
	if(turn == 0){
		if(newboard->chessboard[buttonx][buttony] == P1KING){
			newboard->p1kingx = buttonx;
			newboard->p1kingy = buttony;
			newboard->p1castle1 = 1;
			newboard->p1castle2 = 1;
			if(buttonx-chosenx == 2){
				newboard->chessboard[7][0] = EMPTY;
				newboard->chessboard[4][0] = P1ROOK;
			} else if(buttonx-chosenx == -2){
				newboard->chessboard[0][0] = EMPTY;
				newboard->chessboard[2][0] = P1ROOK;
			}
		} else if (chosenx == 0 && choseny == 0){
			newboard->p1castle1 = 1;
		} else if (chosenx == 7 && choseny == 0){
			newboard->p1castle2 = 1;
		} else if (buttonx == 0 && buttony == 7){
			newboard->p2castle1 = 1;
		} else if (buttonx == 7 && buttony == 7){
			newboard->p2castle2 = 1;
		}
		if(newboard->chessboard[buttonx][buttony] == P1PAWN && buttony-choseny == 2){
			newboard->p1enpassant = buttonx;
		} else {
			newboard->p1enpassant = -1;
		}
		if(newboard->chessboard[buttonx][buttony] == P1PAWN && buttonx == newboard->p2enpassant && buttony == 5){
			newboard->chessboard[buttonx][4] = EMPTY;
		}
		if(buttony == 7 && newboard->chessboard[buttonx][buttony] == P1PAWN){
			newboard->chessboard[buttonx][buttony] = P1QUEEN; //Change this to where it could be any piece
		}
	} else {
		if(newboard->chessboard[buttonx][buttony] == P2KING){
			newboard->p2kingx = buttonx;
			newboard->p2kingy = buttony;
			newboard->p2castle1 = 1;
			newboard->p2castle2 = 1;
			if(buttonx-chosenx == 2){
				newboard->chessboard[7][7] = EMPTY;
				newboard->chessboard[4][7] = P2ROOK;
			} else if(buttonx-chosenx == -2){
				newboard->chessboard[0][7] = EMPTY;
				newboard->chessboard[2][7] = P2ROOK;
			}
		} else if (chosenx == 0 && choseny == 7){
			newboard->p2castle1 = 1;
		} else if (chosenx == 7 && choseny == 7){
			newboard->p2castle2 = 1;
		} else if (buttonx == 0 && buttony == 0){
			newboard->p1castle1 = 1;
		} else if (buttonx == 7 && buttony == 0){
			newboard->p1castle2 = 1;
		}
		if(newboard->chessboard[buttonx][buttony] == P2PAWN && choseny-buttony == 2){
			newboard->p2enpassant = buttonx;
		} else {
			newboard->p2enpassant = -1;
		}
		if(newboard->chessboard[buttonx][buttony] == P2PAWN && buttonx == newboard->p1enpassant && buttony == 2){
			newboard->chessboard[buttonx][3] = EMPTY;
		}
		if(buttony == 0 && newboard->chessboard[buttonx][buttony] == P2PAWN){
			newboard->chessboard[buttonx][buttony] = P2QUEEN; //Change this to where it could be any piece
		}
	}
	return newboard;
}

//Determine all potential moves with given piece and display them
int getmoves(struct chess *chess_state, int i, int j, int pturn, int moves, struct chess ***chess_total_moves){
	struct chess *chess_moves[22];// = (struct chess **) calloc(22, sizeof(struct chess *));
	int moves_len = 0;

	switch(((chess_state->chessboard[i][j]-P1PAWN) % 6)+P1PAWN){
		case P1PAWN:
			if(chess_state->chessboard[i][j] == P1PAWN){
				if(chess_state->chessboard[i][j+1] == EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j+1, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j+1, i, j, pturn);
						moves_len++;
					}
					if(j == 1 && chess_state->chessboard[i][3] == EMPTY){
						if(!kingatrisk(chess_state, i, j, i, 3, pturn)){
							chess_moves[moves_len] = getboard(chess_state, i, 3, i, j, pturn);
							moves_len++;
						}
					}
				}
				if(i > 0 && chess_state->chessboard[i-1][j+1] / P2PAWN == 1){
					if(!kingatrisk(chess_state, i, j, i-1, j+1, pturn)){
						//chess_state->chessboard not included because you would be taking a piece
						chess_moves[moves_len] = getboard(chess_state, i-1, j+1, i, j, pturn);
						moves_len++;
					}
				}
				if(i < 7 && chess_state->chessboard[i+1][j+1] / P2PAWN == 1){
					if(!kingatrisk(chess_state, i, j, i+1, j+1, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+1, j+1, i, j, pturn);
						moves_len++;
					}
				}
				if(i > 0 && i-1 == chess_state->p2enpassant && j == 4){
					if(!kingatrisk(chess_state, i, j, i-1, 5, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-1, 5, i, j, pturn);
						moves_len++;
					}
				}
				if(i+1 == chess_state->p2enpassant && j == 4){
					if(!kingatrisk(chess_state, i, j, i+1, 5, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+1, 5, i, j, pturn);
						moves_len++;
					}
				}
			} else {
				if(chess_state->chessboard[i][j-1] == EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j-1, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j-1, i, j, pturn);
						moves_len++;
					}
					if(j == 6 && chess_state->chessboard[i][4] == EMPTY){
						if(!kingatrisk(chess_state, i, j, i, 4, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, 4, i, j, pturn);
							moves_len++;
						}
					}
				}
				if(i > 0 && (chess_state->chessboard[i-1][j-1]-P1PAWN) / 6 == 0){
					if(!kingatrisk(chess_state, i, j, i-1, j-1, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-1, j-1, i, j, pturn);
						moves_len++;
					}
				}
				if(i < 7 && (chess_state->chessboard[i+1][j-1]-P1PAWN) / 6 == 0){
					if(!kingatrisk(chess_state, i, j, i+1, j-1, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+1, j-1, i, j, pturn);
						moves_len++;
					}
				}
				if(i > 0 && i-1 == chess_state->p1enpassant && j == 3){
					if(!kingatrisk(chess_state, i, j, i-1, 2, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-1, 2, i, j, pturn);
						moves_len++;
					}
				}
				if(i+1 == chess_state->p1enpassant && j == 3){
					if(!kingatrisk(chess_state, i, j, i+1, 2, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+1, 2, i, j, pturn);
						moves_len++;
					}
				}
			}
			break;
		case P1ROOK:
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || (chess_state->chessboard[i+x][j]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || (chess_state->chessboard[i-x][j]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(j+x > 7 || (chess_state->chessboard[i][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(j-x < 0 || (chess_state->chessboard[i][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j-x, i, j, pturn);
					moves_len++;
				}
			}
			break;
		case P1BISHOP:
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || j+x > 7 || (chess_state->chessboard[i+x][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || j+x > 7 || (chess_state->chessboard[i-x][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || j-x < 0 || (chess_state->chessboard[i+x][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j-x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || j-x < 0 || (chess_state->chessboard[i-x][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j-x, i, j, pturn);
					moves_len++;
				}
			}
			break;
		case P1KNIGHT:
			if(i+2 < 8 && j+1 < 8 && (chess_state->chessboard[i+2][j+1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+2, j+1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+2, j+1, i, j, pturn);
					moves_len++;
				}
			}
			if(i+2 < 8 && j-1 > -1 && (chess_state->chessboard[i+2][j-1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+2, j-1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+2, j-1, i, j, pturn);
					moves_len++;
				}
			}
			if(i+1 < 8 && j+2 < 8 && (chess_state->chessboard[i+1][j+2]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+1, j+2, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+1, j+2, i, j, pturn);
					moves_len++;
				}
			}
			if(i+1 < 8 && j-2 > -1 && (chess_state->chessboard[i+1][j-2]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+1, j-2, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+1, j-2, i, j, pturn);
					moves_len++;
				}
			}
			if(i-2 > -1 && j+1 < 8 && (chess_state->chessboard[i-2][j+1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-2, j+1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-2, j+1, i, j, pturn);
					moves_len++;
				}
			}
			if(i-2 > -1 && j-1 > -1 && (chess_state->chessboard[i-2][j-1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-2, j-1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-2, j-1, i, j, pturn);
					moves_len++;
				}
			}
			if(i-1 > -1 && j+2 < 8 && (chess_state->chessboard[i-1][j+2]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-1, j+2, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-1, j+2, i, j, pturn);
					moves_len++;
				}
			}
			if(i-1 > -1 && j-2 > -1 && (chess_state->chessboard[i-1][j-2]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-1, j-2, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-1, j-2, i, j, pturn);
					moves_len++;
				}
			}
			break;
		case P1QUEEN:
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || (chess_state->chessboard[i+x][j]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || (chess_state->chessboard[i-x][j]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(j+x > 7 || (chess_state->chessboard[i][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(j-x < 0 || (chess_state->chessboard[i][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j-x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || j+x > 7 || (chess_state->chessboard[i+x][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || j+x > 7 || (chess_state->chessboard[i-x][j+x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j+x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j+x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j+x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j+x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j+x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i+x > 7 || j-x < 0 || (chess_state->chessboard[i+x][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i+x][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i+x, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i+x, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i+x, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+x, j-x, i, j, pturn);
					moves_len++;
				}
			}
			for(int x = 1; x < 8; x++){
				if(i-x < 0 || j-x < 0 || (chess_state->chessboard[i-x][j-x]-P1PAWN) / 6 == pturn){
					break;
				} else if(chess_state->chessboard[i-x][j-x] != EMPTY){
					if(!kingatrisk(chess_state, i, j, i-x, j-x, pturn)){
						chess_moves[moves_len] = getboard(chess_state, i-x, j-x, i, j, pturn);
						moves_len++;
					}
					break;
				}
				if(!kingatrisk(chess_state, i, j, i-x, j-x, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-x, j-x, i, j, pturn);
					moves_len++;
				}
			}
			break;
		case P1KING:
			if(pturn == 0 && chess_state->p1castle1 == 0 && chess_state->chessboard[1][0] == EMPTY && chess_state->chessboard[2][0] == EMPTY){
				if(!kingatrisk(chess_state, i, j, 1, 0, pturn)){
					chess_moves[moves_len] = getboard(chess_state, 1, 0, i, j, pturn);
					moves_len++;
				}
			} else if(pturn == 1 && chess_state->p2castle1 == 0 && chess_state->chessboard[1][7] == EMPTY && chess_state->chessboard[2][7] == EMPTY){
				if(!kingatrisk(chess_state, i, j, 1, 7, pturn)){
					chess_moves[moves_len] = getboard(chess_state, 1, 7, i, j, pturn);
					moves_len++;
				}
			}
			if(pturn == 0 && chess_state->p1castle2 == 0 && chess_state->chessboard[4][0] == EMPTY && chess_state->chessboard[5][0] == EMPTY && chess_state->chessboard[6][0] == EMPTY){
				if(!kingatrisk(chess_state, i, j, 5, 0, pturn)){
					chess_moves[moves_len] = getboard(chess_state, 5, 0, i, j, pturn);
					moves_len++;
				}  
			} else if(pturn == 1 && chess_state->p2castle2 == 0 && chess_state->chessboard[4][7] == EMPTY && chess_state->chessboard[5][7] == EMPTY && chess_state->chessboard[6][7] == EMPTY){
				if(!kingatrisk(chess_state, i, j, 5, 7, pturn)){
					chess_moves[moves_len] = getboard(chess_state, 5, 7, i, j, pturn);
					moves_len++;
				}
			}
			if(i+1 < 8 && (chess_state->chessboard[i+1][j]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+1, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+1, j, i, j, pturn);
					moves_len++;
				}
			}
			if(i-1 > -1 && (chess_state->chessboard[i-1][j]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-1, j, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-1, j, i, j, pturn);
					moves_len++;
				}
			}
			if(j+1 < 8 && (chess_state->chessboard[i][j+1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i, j+1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j+1, i, j, pturn);
					moves_len++;
				}
			}
			if(j-1 > -1 && (chess_state->chessboard[i][j-1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i, j-1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i, j-1, i, j, pturn);
					moves_len++;
				}
			}
			if(i+1 < 8 && j+1 < 8 && (chess_state->chessboard[i+1][j+1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+1, j+1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+1, j+1, i, j, pturn);
					moves_len++;
				}
			}
			if(i+1 < 8 && j-1 > -1 && (chess_state->chessboard[i+1][j-1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i+1, j-1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i+1, j-1, i, j, pturn);
					moves_len++;
				}
			}
			if(i-1 > -1 && j+1 < 8 && (chess_state->chessboard[i-1][j+1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-1, j+1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-1, j+1, i, j, pturn);
					moves_len++;
				}
			}
			if(i-1 > -1 && j-1 > -1 && (chess_state->chessboard[i-1][j-1]-P1PAWN) / 6 != pturn){
				if(!kingatrisk(chess_state, i, j, i-1, j-1, pturn)){
					chess_moves[moves_len] = getboard(chess_state, i-1, j-1, i, j, pturn);
					moves_len++;
				}
			}
			break;
		default:
			break;
	}
	//If we are calling the function to add new moves and not just get the number of moves
	if(chess_total_moves != NULL){
		//Increase the size of the main moves list array by the number of new moves and then copy in the new moves
		*chess_total_moves = realloc(*chess_total_moves, (moves+moves_len)*sizeof(struct chess *));
		memcpy((*chess_total_moves)+moves, chess_moves, moves_len*sizeof(struct chess *));
	} else {
		for(int i = 0; i < moves_len; i++){
			free(chess_moves[i]);
		}
	}
	return moves_len;
}

//Check if player 1 or player 2 is in checkmate
int checkmate(struct chess *chess_state, int pturn){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			//Check if they have any moves that don't leave them in check
			if(chess_state->chessboard[i][j] != EMPTY && chess_state->chessboard[i][j] / P2PAWN == pturn && getmoves(chess_state, i, j, pturn, 0, NULL) > 0){
				return 0;
			}
		}
	}
	return pturn+1;
}

void **moves(void *gamestate, int turn, int *movecount, int *movesize, int gametype){
	*movesize = sizeof(struct chess *);
	struct chess *chess_state = (struct chess *) gamestate;
	struct chess **moves = (struct chess **) calloc(1, sizeof(struct chess *));
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(chess_state->chessboard[i][j] != EMPTY && chess_state->chessboard[i][j] / P2PAWN == turn % 2){
				*movecount += getmoves(chess_state, i, j, turn % 2, *movecount, &moves);
			}
		}
	}
	return (void **) moves;
}

void static_eval(void *gamestate, int *eval, int *terminal, int turn, int gametype){
	struct chess *chess_state = (struct chess *) gamestate;
	if(turn % 2 == 0 && checkmate(chess_state, 1)){
		*terminal = 1;
		*eval = 10000;
		return;
		//printf("PLAYER 1 WINS!\n");
	} else if(turn % 2 == 1 && checkmate(chess_state, 0)){
		*terminal = 1;
		*eval = -10000;
		return;
		//printf("PLAYER 2 WINS!\n");
	}
	//int evalflip = (turn % 2)*2-1;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			switch(chess_state->chessboard[i][j]){
				case P1PAWN:
					(*eval) += 1;
					break;
				case P1KNIGHT:
					(*eval) += 3;
					break;
				case P1BISHOP:
					(*eval) += 3;
					break;
				case P1ROOK:
					(*eval) += 4;
					break;
				case P1QUEEN:
					(*eval) += 9;
					break;
				case P1KING:
					break;
				case P2PAWN:
					(*eval) -= 1;
					break;
				case P2KNIGHT:
					(*eval) -= 3;
					break;
				case P2BISHOP:
					(*eval) -= 3;
					break;
				case P2ROOK:
					(*eval) -= 4;
					break;
				case P2QUEEN:
					(*eval) -= 9;
					break;
				case P2KING:
					break;
				case EMPTY:
					break;
				default:
					break;
			}
		}
	}
	/*if(turn % 2){
		(*eval) *= -1;
	}*/
}

void *openmove(char *filename, int gametype){
	struct chess *chess_state = (struct chess *) calloc(1, sizeof(struct chess));
	FILE *movefile = fopen(filename, "r");
	char linefeed[16];
	for(int i = 0; i < 8; i++){
		fgets(linefeed, 16, movefile);
		for(int j = 0; j < 8; j++){
			switch(linefeed[j*2]){
				case 1: //TODO: FIX THIS
				//TODO: FIX THIS BY CHANGING THE NUMBER DEFINES TO ALPHANUMERICS char values
				//starting with EMPTY as '0' and P1PAWN as 'a' and P1KNIGHT as 'b' and so on.
				//This way the math will work out.
					chess_state->chessboard[i][j] = P1PAWN;
					break;
			}
		}
		//TODO: add lines to fgets the other properties of the chess board state
	}
	fclose(movefile);
	return (void *)chess_state;
}

void *startstate(int gametype){
	struct chess *chess_state = (struct chess *) calloc(1, sizeof(struct chess));
	for(int i = 0; i < 8; i++){
		for(int j = 2; j < 6; j++){
			chess_state->chessboard[i][j] = EMPTY;
		}
	}

	chess_state->p1enpassant = -1;
	chess_state->p2enpassant = -1;

	//Setup initial board pieces
	for(int i = 0; i < 8; i++){
		chess_state->chessboard[i][1] = P1PAWN;
		chess_state->chessboard[i][6] = P2PAWN;
	}
	chess_state->chessboard[0][0] = P1ROOK;
	chess_state->chessboard[1][0] = P1KNIGHT;
	chess_state->chessboard[2][0] = P1BISHOP;
	chess_state->chessboard[3][0] = P1KING;
	chess_state->p1kingx = 3;
	chess_state->p1kingy = 0;
	chess_state->p1castle1 = 0;
	chess_state->p1castle2 = 0;
	chess_state->chessboard[4][0] = P1QUEEN;
	chess_state->chessboard[5][0] = P1BISHOP;
	chess_state->chessboard[6][0] = P1KNIGHT;
	chess_state->chessboard[7][0] = P1ROOK;
	
	chess_state->chessboard[0][7] = P2ROOK;
	chess_state->chessboard[1][7] = P2KNIGHT;
	chess_state->chessboard[2][7] = P2BISHOP;
	chess_state->chessboard[3][7] = P2KING;
	chess_state->p2kingx = 3;
	chess_state->p2kingy = 7;
	chess_state->p2castle1 = 0;
	chess_state->p2castle2 = 0;
	chess_state->chessboard[4][7] = P2QUEEN;
	chess_state->chessboard[5][7] = P2BISHOP;
	chess_state->chessboard[6][7] = P2KNIGHT;
	chess_state->chessboard[7][7] = P2ROOK;
	return (void *) chess_state;
}