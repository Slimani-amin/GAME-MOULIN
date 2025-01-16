#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <windows.h>

using namespace std;

typedef enum couleur
{
    vide,
    noir,
    blanc
}couleur;


typedef enum winner
{
    aucun_gagnant,
    noir_gagnant,
    blanc_gagnant
}winner;


typedef enum tour
{
    player1,
    player2
}tour;

enum phase
{
    phase1,
    phase2,
    phase3
};
typedef enum phase phase;


typedef struct cellule
{
    int valeur;
    couleur etat;
}cellule;

typedef struct Node {
    cellule grille[24]; // Valeur du nœud
    int h;
    phase PHASE;
    int PionNoir;
    int PionBlanc;
    std::vector<Node*> children; // Vecteur de pointeurs vers les enfants

    Node(cellule state[24]) {
        for (int i = 0; i < 24; i++) {
            grille[i].etat = state[i].etat;
        }
    }
}Node;

//extern cellule board[24];
//extern tour role;
//extern int countNoir = 0;
//extern int countBlanc = 0;
//extern const int MAX_PIECES = 9;
//extern  const int MIN_PIECES = 3;

//extern int turn;


bool checkMillFormation(int position, cellule* board, couleur col);

bool isMill(cellule* board, int pos1, int pos2, couleur col);

bool EstVoisin(int from, int to);

void color(int textColor, int bgColor);

void pion(cellule* board, int i);

void printBoard(cellule* board);

//void removeOpponentStone(tour role);

Node* CreeNode(cellule* grille, phase PHASE, int PionNoir, int PionBlanc);

void mainLoop(cellule* board, tour role, int countBlanc, int countNoir, int turn);

int* voisin(int position);

bool EstVoisin(int from, int to);

bool isMill(cellule* board, int pos1, int pos2, couleur col);

bool checkMillFormation(int position, cellule* board, couleur col);

bool VoisinPlein(cellule *board,int i);

int minimax(Node* node, int depth, bool maximizingPlayer, int alpha, int beta, tour currentPlayer);

void DestroyNode(Node* node);

void GenererSuccesseur(Node* node, tour player);

int heuristique(cellule* grille, tour currentPlayer, phase etat);

int getNumberOfPossibleMoves(cellule* grille, tour player);

int getNumberOfBlockedPions(cellule* grille, tour player);

int getNumberOfMoulins(cellule* grille, tour player);

int getNumberOfPossibleMoves(cellule* grille, tour player);

int heuristique(cellule* grille, tour currentPlayer, phase etat);

void GenererSuccesseur(Node* node, tour player);






