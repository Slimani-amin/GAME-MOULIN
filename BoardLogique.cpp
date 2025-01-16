#include "BoardLogique.hpp"

bool checkMillFormation(int position, cellule* board, couleur col)
{
    bool mill[] = {
        (isMill(board, 1, 2, col) || isMill(board, 9, 21, col)),//0
        (isMill(board, 0, 2, col) || isMill(board, 4, 7, col)),//1
        (isMill(board, 0, 1, col) || isMill(board, 14, 23, col)),//2
        (isMill(board, 4, 5, col) || isMill(board, 10, 18, col)),//3
        (isMill(board, 3, 5, col) || isMill(board, 7, 1, col)),//4
        (isMill(board, 4, 3, col) || isMill(board, 13, 20, col)),//5
        (isMill(board, 8, 7, col) || isMill(board, 11, 15, col)),//6
        (isMill(board, 1, 4, col) || isMill(board, 8, 6, col)),//7
        (isMill(board, 7, 6, col) || isMill(board, 12, 17, col)),//8
        (isMill(board, 0, 21, col) || isMill(board, 10, 11, col)),//9
        (isMill(board, 11, 9, col) || isMill(board, 3, 18, col)),//10
        (isMill(board, 9, 10, col) || isMill(board, 15, 6, col)),//11
        (isMill(board, 17, 8, col) || isMill(board, 13, 14, col)),//12
        (isMill(board, 12, 14, col) || isMill(board, 5, 20, col)),//13
        (isMill(board, 13, 12, col) || isMill(board, 2, 23, col)),//14
        (isMill(board, 16, 17, col) || isMill(board, 11, 6, col)),//15
        (isMill(board, 15, 17, col) || isMill(board, 19, 22, col)),//16
        (isMill(board, 15, 16, col) || isMill(board, 12, 8, col)),//17
        (isMill(board, 19, 20, col) || isMill(board, 10, 3, col)),//18
        (isMill(board, 18, 20, col) || isMill(board, 16, 22, col)),//19
        (isMill(board, 18, 19, col) || isMill(board, 13, 5, col)),//20
        (isMill(board, 9, 0, col) || isMill(board, 22, 23, col)),//21
        (isMill(board, 19, 16, col) || isMill(board, 21, 23, col)),//22
        (isMill(board, 14, 2, col) || isMill(board, 21, 22, col)) };//23
    return mill[position];
}

bool VoisinPlein(cellule *board,int i)
{
    int* tab;
    tab = voisin(i);
    for (int j = 0; j < 4; j++) {
        if (tab[j] != -1) {
            if (board[tab[j]].etat == vide) {
                return false;
            }
        }
    }
    return true;
}

bool isMill(cellule* board, int pos1, int pos2, couleur col)
{
    return (board[pos1].etat == col && board[pos2].etat == col && board[pos1].etat != vide);
}

bool EstVoisin(int from, int to)
{
    if (from == to) {
        return false;
    }
    int* tab;
    tab = voisin(from);
    for (int i = 0; i < 4; i++) {
        if (to == tab[i]) {
            return true;
        }
    }
    return false;
}

void color(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void pion(cellule *board,int i)
{
    if (board[i].etat == noir)
    {
        color(9, 11);
        cout << i;
        color(7, 0);
    }
    else if (board[i].etat == blanc)
    {

        color(5, 0);
        cout << i;
        color(7, 0);
    }
    else {
        color(7, 0);
        cout << i;

    }
}

void printBoard(cellule *board)
{
    cout << "\t\t\t\t ";  pion(board,21); cout << "----------------------"; pion(board,22); cout << "----------------------"; pion(board, 23); cout << "" << endl;
    cout << "\t\t\t\t |                      |                      |" << endl;
    cout << "\t\t\t\t |       "; pion(board, 18); cout << "--------------"; pion(board, 19); cout << "--------------"; pion(board, 20); cout << "      |" << endl;
    cout << "\t\t\t\t |       |              |               |      |" << endl;
    cout << "\t\t\t\t |       |              |               |      |" << endl;
    cout << "\t\t\t\t |       |        "; pion(board, 15); cout << "-----"; pion(board, 16); cout << "-----"; pion(board, 17); cout << "      |      |" << endl;
    cout << "\t\t\t\t |       |        |             |       |      |" << endl;
    cout << "\t\t\t\t |       |        |             |       |      |" << endl;
    cout << "\t\t\t\t "; pion(board, 9); cout << "-------"; pion(board, 10); cout << "-------"; pion(board, 11); cout << "            "; pion(board, 12); cout << "------"; pion(board,13); cout << "-----"; pion(board,14); cout << "" << endl;
    cout << "\t\t\t\t |       |        |             |       |      |" << endl;
    cout << "\t\t\t\t |       |        |             |       |      |" << endl;
    cout << "\t\t\t\t |       |        "; pion(board, 6); cout << "-----"; pion(board, 7); cout << "-----"; pion(board, 8); cout << "      |      |" << endl;
    cout << "\t\t\t\t |       |                |             |      |" << endl;
    cout << "\t\t\t\t |       |                |             |      |" << endl;
    cout << "\t\t\t\t |       "; pion(board, 3); cout << "--------------"; pion(board, 4); cout << "-------------"; pion(board, 5); cout << "     |" << endl;
    cout << "\t\t\t\t |                        |                    |" << endl;
    cout << "\t\t\t\t |                        |                    |" << endl;
    cout << "\t\t\t\t "; pion(board, 0); cout << "------------------------"; pion(board, 1); cout << "--------------------"; pion(board, 2); cout << "" << endl;
}   

void removeOpponentStone(cellule *board ,tour role)
{
    couleur myColor = (role == player1 ? noir : blanc);
    couleur opponentColor = (role == player1 ? blanc : noir);

    for (int i = 0; i < 24; i++)
    {
        if (board[i].etat == opponentColor)
        { // Trouver un pion de l'adversaire
            if (!checkMillFormation(i, board, blanc))
            {                         // Vérifier qu'il n'est pas dans un moulin
                board[i].etat = vide; // Enlever le pion
                cout << "Pion adverse enlevé à la position " << i << endl;
                return; // Sortir après avoir enlevé un pion
            }
        }
    }
}

void mainLoop(cellule *board, tour role, int countBlanc, int countNoir, int turn)
{
    int position;
    for (int i = 0; i < 24; i++)
    {
        board[i].valeur = i;
        board[i].etat = vide;
    }
    role = player1;
    system("cls");
    printBoard(board);

    while (turn < 18)
    {
        cout << "Player " << (role == player1 ? "Noir" : "Blanc") << ", enter a position (0-23): ";
        if (role == player1)
        {
            cin >> position;
            while (position < 0 || position > 23 || board[position].etat != vide)
            {
                cout << "Invalid input. Please enter a valid position (0-23) that is unoccupied: ";
                cin >> position;

            }
            board[position].etat = noir;
        }
        else
        {
            // Player2 enters their position manually
            cin >> position;
            while (position < 0 || position > 23 || board[position].etat != vide)
            {
                cout << "Invalid input. Please enter a valid position (0-23) that is unoccupied: ";
                cin >> position;
            }
            board[position].etat = blanc;
        }

        // Place the stone and check for mill
        system("cls");
        printBoard(board);


        if (role == player2)
        {
            if (checkMillFormation(position, board, blanc))
            {
                // Specific logic for player2 after forming a mill
                cout << "You formed a mill! Enter an opponent's stone to remove: ";
                int removePosition;
                cin >> removePosition; // Assume valid input for simplicity
                while (removePosition < 0 || removePosition > 23 || board[removePosition].etat != noir || checkMillFormation(removePosition, board, noir)) {
                    cout << "Invalid input. Try again: ";
                    cin >> removePosition;
                }
                board[removePosition].etat = vide;
            }

        }
        if (role == player1)
        {
            if (checkMillFormation(position, board, noir)) {
                cout << "You formed a mill! Enter an opponent's stone to remove: ";
                int removePosition;
                cin >> removePosition; // Assume valid input for simplicity
                while (removePosition < 0 || removePosition > 23 || board[removePosition].etat != blanc || checkMillFormation(removePosition, board, blanc)) {
                    cout << "Invalid input. Try again: ";
                    cin >> removePosition;
                }
                board[removePosition].etat = vide;
            }

        }

        system("cls");
        printBoard(board);
        role = (role == player1 ? player2 : player1); // Switch player
        turn++;

    }
    for (int i = 0; i < 24; i++) {
        if (board[i].etat == noir) {
            countNoir++;
        }
        if (board[i].etat == blanc) {
            countBlanc++;
        }

    }
    while (countNoir != 2 || countBlanc != 2)
    {
        int from, to;
        cout << " entrer une position : ";
        cin >> from;
        if (role == player1) {
            while (board[from].etat != noir || from < 0 || from > 23)
            {
                cout << " Position Invalide : ";
                cin >> from;
            }
        repet1:
            cout << " entrer la destination : ";
            cin >> to;
            while (board[to].etat != vide || to < 0 || to > 23)
            {
                cout << " Position Invalide : ";
                cin >> to;
            }
            if (countNoir > 3)
            {
                if (EstVoisin(from, to))
                {
                    board[to].etat = noir;
                    board[from].etat = vide;
                }
                else
                {
                    goto repet1;
                }
            }
            else if (countNoir == 3)
            {
                board[to].etat = noir;
                board[from].etat = vide;
            }

            if (checkMillFormation(to, board, noir))
            {
                cout << "You formed a mill! Enter an opponent's stone to remove: ";
                int removePosition;
                cin >> removePosition;
                while (removePosition < 0 || removePosition > 23 || board[removePosition].etat != blanc || checkMillFormation(removePosition, board, blanc)) {
                    cout << "Invalid input. Try again: ";
                    cin >> removePosition;
                }
                board[removePosition].etat = vide;
                countBlanc--;

            }

        }
        else {
            while (board[from].etat != blanc || from < 0 || from > 23)
            {
                cout << " Position Invalide : ";
                cin >> from;
            }
        repet2:

            cout << " entrer la destination : ";
            cin >> to;
            while (board[to].etat != vide || to < 0 || to > 23)
            {
                cout << " Position Invalide : ";
                cin >> to;
            }
            if (countBlanc > 3) {
                if (EstVoisin(from, to))
                {
                    board[to].etat = blanc;
                    board[from].etat = vide;
                }
                else
                {
                    goto repet2;
                }
            }
            else if (countBlanc == 3)
            {
                board[to].etat = blanc;
                board[from].etat = vide;
            }


            if (checkMillFormation(to, board, blanc))
            {
                cout << "You formed a mill! Enter an opponent's stone to remove: ";
                int removePosition;
                cin >> removePosition;
                while (removePosition < 0 || removePosition > 23 || board[removePosition].etat != noir || checkMillFormation(removePosition, board, noir))
                {
                    cout << "Invalid input. Try again: ";
                    cin >> removePosition;
                }
                board[removePosition].etat = vide;
                countNoir--;

            }
        }
        system("cls");
        printBoard(board);
        role = (role == player1 ? player2 : player1); // Switch player

        if (countNoir == 2) {
            cout << "Player2 win! " << endl;
            break;
        }
        else if (countBlanc == 2) {
            cout << "Player1 win! " << endl;
            break;
        }

    }

}

int* voisin(int position)
{
    static int adjacent[24][4] = {
        {1, 9, -1, -1},//0
        {0, 2, 4, -1},//1
        {1, 14, -1, -1},//2
        {4, 10, -1, -1},//3
        {1, 3, 5, 7},//4
        {4, 13, -1, -1},//5
        {7, 11, -1, -1},//6
        {4, 6, 8, -1},//7
        {7, 12, -1, -1},//8
        {0, 10, 21, -1},//9
        {3, 9, 11, 18},//10
        {6, 10, 15, -1 },//11
        {8, 13, 17, -1},//12
        {5, 12, 14, 20},//13
        {2, 13, 23, -1},//14
        {11, 16, -1, -1},//15
        {15, 17, 19, -1},//16
        {12, 16, -1, -1},//17
        {10, 19, -1, -1},//18
        {16, 18, 20, 22},//19
        {13, 19, -1, -1},//20
        {9, 22, -1, -1},//21
        {19, 21, 23, -1},//22
        {14, 22, -1, -1} };//23

    return adjacent[position];
}

Node* CreeNode(cellule* grille, phase PHASE, int PionNoir, int PionBlanc) {
    Node* n = new Node(grille);
    n->PHASE = PHASE;
    n->PionNoir = PionNoir;
    n->PionBlanc = PionBlanc;
    return n;
}


int CheckWinner(cellule* grille, phase etat) {
    if (etat == 1) {
        return 0;
    }

    int cmptNoir = 0;
    int cmptBlanc = 0;
    for (int i = 0; i < 24; i++) {
        if (grille[i].etat == noir) {
            cmptNoir++;
        }
        else if (grille[i].etat == blanc) {
            cmptBlanc++;
        }
    }
    if (cmptNoir <= 2) {
        return -1;
    }
    else if (cmptBlanc <= 2) {
        return 1;
    }

    return 0;

}

int getNumberOfPions(cellule* grille, tour player) {
    couleur col;
    if (player == player1) {
        col = noir;
    }
    else {
        col = blanc;
    }
    int cmpt = 0;
    for (int i = 0; i < 24; i++) {
        if (grille[i].etat == col) {
            cmpt++;
        }

    }
    return cmpt;

}

int getNumberOfMoulins(cellule* grille, tour player) {
    int cmpt = 0;
    vector<int> indice;
    couleur col;
    if (player == player1) {
        col = noir;
    }
    else {
        col = blanc;
    }
    for (int i = 0; i < 24; i++) {
        if (checkMillFormation(i, grille, col)) {
            cmpt++;
        }

    }
    return cmpt ;
}


int getNumberOfBlockedPions(cellule* grille, tour player) {
    int cmpt = 0;
    couleur col, contrecol;
    if (player == player1) {
        col = noir;
        contrecol = blanc;
    }
    else {
        col = blanc;
        contrecol = noir;
        for (int i = 0; i < 24; i++) {
            if (grille[i].etat == contrecol) {
                int* tab = voisin(i);
                bool estbloked = true;
                for (int j = 0; tab[j] != -1 && j < 4; j++) {
                    if (grille[tab[j]].etat != col) {
                        estbloked = false;
                    }

                }
                if (estbloked) {
                    cmpt++;
                }
            }

        }

    }
    return cmpt;
}

int getNumberOfPossibleMoves(cellule* grille, tour player) {
    int cmpt = 0;
    couleur col;
    if (player == player1) {
        col = noir;
    }
    else {
        col = blanc;
    }
    for (int i = 0; i < 24; i++) {
        if (grille[i].etat == col) {
            int* tab = voisin(i);
            for (int j = 0; tab[j] != -1 && j < 4; j++) {
                if (grille[tab[j]].etat == vide) {
                    cmpt++;
                }
            }
        }
    }
    return cmpt;

}


int heuristique(cellule* grille, tour currentPlayer, phase etat) {
    couleur col, contrcol;
    if (etat != phase1) {
        if (currentPlayer == player1) {
            col = noir;
            contrcol = blanc;

        }
        else {
            col = blanc;
            contrcol = noir;
        }
        int cmptcol = 0, cmptcontr = 0;
        for (int i = 0; i < 24; i++) {
            if (grille[i].etat == col) {
                cmptcol++;
            }
            else if (grille[i].etat == contrcol) {
                cmptcontr++;
            }
        }
        if (cmptcol < 3) {
            return 10000;
        }
        if (cmptcontr) {
            return -10000;
        }
    }

    int score = 0;

    // Points pour les pions sur le plateau
    int player1Pions = getNumberOfPions(grille, player1);
    int player2Pions = getNumberOfPions(grille, player2);
    score += (player1Pions - player2Pions) * 100;

    // Points pour les moulins formés
    int player1Moulins = getNumberOfMoulins(grille, player1);
    int player2Moulins = getNumberOfMoulins(grille, player2);
    score += (player1Moulins - player2Moulins) * 50;

    // Points pour les pions bloqués
    int player1Blocked = getNumberOfBlockedPions(grille, player1);
    int player2Blocked = getNumberOfBlockedPions(grille, player2);
    score -= (player1Blocked - player2Blocked) * 20;

    // Points pour les possibilités de mouvement
    int player1Moves = getNumberOfPossibleMoves(grille, player1);
    int player2Moves = getNumberOfPossibleMoves(grille, player2);
    score += (player1Moves - player2Moves) * 5;
    ;





    return (currentPlayer == player1) ? score : -score;
}

void GenererSuccesseur(Node* node, tour player) {
    int Noir = 0, Blanc = 0;
    for (int i = 0; i < 24; i++) {
        if (node->grille[i].etat == noir) {
            Noir++;
        }
        else if (node->grille[i].etat == blanc) {
            Blanc++;
        }
    }
    if (node->PHASE != phase1 && (Noir < 3 || Blanc < 3)) {
        return;
    }
    couleur col, contrecol;
    int cmptcol, cmptcontrecol;
    phase phasesuivant = node->PHASE;
    if (player == player1) {
        col = noir;
        contrecol = blanc;
        cmptcol = node->PionNoir;
        cmptcontrecol = node->PionBlanc;
    }
    else {
        col = blanc;
        contrecol = noir;
        cmptcol = node->PionBlanc;
        cmptcontrecol = node->PionNoir;
    }
    if (node->PHASE == phase1 && cmptcol == 0) {
        phasesuivant = phase2;
    }
    if (node->PHASE == phase1) {
        for (int i = 0; i < 24; i++) {
            if (node->grille[i].etat == vide) {
                if (checkMillFormation(i, node->grille, col)) {
                    vector <int> indice;
                    for (int j = 0; j < 24; j++) {
                        if (node->grille[j].etat == contrecol && !checkMillFormation(j, node->grille, contrecol)) {
                            indice.push_back(j);

                        }
                    }
                    if (indice.size() == 0) {
                        for (int j = 0; j < 24; j++) {
                            if (node->grille[j].etat == contrecol) {
                                indice.push_back(j);

                            }
                        }
                    }
                    for (int j = 0; j < indice.size(); j++) {
                        Node* ChildNode;
                        if (player == player1) {
                            ChildNode = CreeNode(node->grille, phasesuivant, cmptcol - 1, cmptcontrecol);
                        }
                        else {
                            ChildNode = CreeNode(node->grille, phasesuivant, cmptcontrecol, cmptcol - 1);
                        }
                        ChildNode->grille[i].etat = col;
                        ChildNode->grille[indice[j]].etat = vide;
                        node->children.push_back(ChildNode);

                    }
                }
                else {
                    Node* ChildNode;
                    if (player == player1) {
                        ChildNode = CreeNode(node->grille, phasesuivant, cmptcol - 1, cmptcontrecol);
                    }
                    else {
                        ChildNode = CreeNode(node->grille, phasesuivant, cmptcontrecol, cmptcol - 1);
                    }
                    ChildNode->grille[i].etat = col;
                    node->children.push_back(ChildNode);
                }
            }




        }
    }
    else if (node->PHASE == phase2) {
        for (int i = 0; i < 24; i++) {
            vector<int> indiceCase;
            if (node->grille[i].etat == col && !VoisinPlein(node->grille, i)) {

                indiceCase.clear();
                int* tab = voisin(i);
                for (int j = 0; tab[j] != -1 && j < 4; j++) {
                    if (node->grille[tab[j]].etat == vide) {
                        indiceCase.push_back(tab[j]);
                    }
                }
                node->grille[i].etat = vide;
                for (vector<int>::iterator it = indiceCase.begin(); it != indiceCase.end(); it++) {
                    node->grille[*it].etat = col;
                    if (checkMillFormation(*it, node->grille, col)) {
                        vector <int> indice;
                        for (int j = 0; j < 24; j++) {
                            if (node->grille[j].etat == contrecol && !checkMillFormation(j, node->grille, contrecol)) {
                                indice.push_back(j);

                            }
                        }
                        if (indice.size() == 0) {
                            for (int j = 0; j < 24; j++) {
                                if (node->grille[j].etat == contrecol) {
                                    indice.push_back(j);

                                }
                            }
                        }
                        for (int j = 0; j < indice.size(); j++) {
                            Node* ChildNode;
                            if ((player == player2 && Noir == 4) || (player == player1 && Blanc == 4)) {

                                ChildNode = CreeNode(node->grille, phase3, cmptcontrecol, cmptcol);
                            }
                            else {
                                ChildNode = CreeNode(node->grille, phase2, cmptcontrecol, cmptcol);
                            }


                            //ChildNode->grille[i].etat = vide;
                            ChildNode->grille[indice[j]].etat = vide;
                            // ChildNode->grille[*it].etat = col;
                            node->children.push_back(ChildNode);

                        }

                    }
                    else {
                        Node* ChildNode;
                        ChildNode = CreeNode(node->grille, phasesuivant, cmptcontrecol, cmptcol);
                        // ChildNode->grille[i].etat = vide;
                         //ChildNode->grille[*it].etat = col;
                        node->children.push_back(ChildNode);
                    }
                    node->grille[*it].etat = vide;

                }
                node->grille[i].etat = col;

            }

        }

    }
    else {
        for (int i = 0; i < 24; i++) {
            if (node->grille[i].etat == col) {
                node->grille[i].etat = vide;
                for (int j = 0; j < 24; j++) {
                    if (node->grille[j].etat == vide) {
                        node->grille[j].etat = col;
                        if (checkMillFormation(j, node->grille, col)) {
                            vector <int> indice;
                            for (int j = 0; j < 24; j++) {
                                if (node->grille[j].etat == contrecol && !checkMillFormation(j, node->grille, contrecol)) {
                                    indice.push_back(j);

                                }
                            }
                            if (indice.size() == 0) {
                                for (int j = 0; j < 24; j++) {
                                    if (node->grille[j].etat == contrecol) {
                                        indice.push_back(j);

                                    }
                                }
                            }
                            for (int k = 0; k < indice.size(); k++) {
                                Node* ChildNode;
                                ChildNode = CreeNode(node->grille, phasesuivant, cmptcontrecol, cmptcol);
                                // ChildNode->grille[i].etat = vide;
                                ChildNode->grille[indice[k]].etat = vide;
                                //ChildNode->grille[j].etat = col;
                                node->children.push_back(ChildNode);
                            }
                        }
                        else {
                            Node* ChildNode;
                            ChildNode = CreeNode(node->grille, phasesuivant, cmptcontrecol, cmptcol);
                            //ChildNode->grille[i].etat = vide;
                           // ChildNode->grille[j].etat = col;
                            node->children.push_back(ChildNode);
                        }
                        node->grille[j].etat = vide;
                    }
                }
                node->grille[i].etat = col;
            }
        }
    }


}





void DestroyNode(Node* node) {
    if (node != nullptr) {
        for (Node* child : node->children) {
            DestroyNode(child);
        }
        node->children.clear();
        delete node;
    }
}

int minimax(Node* node, int depth, bool maximizingPlayer, int alpha, int beta, tour currentPlayer) {
    // Cas de base : feuille ou profondeur maximale atteinte
    GenererSuccesseur(node, currentPlayer);
    if (node->children.empty() || depth == 0) {
        //if (maximizingPlayer) {
            node->h = heuristique(node->grille, player1, node->PHASE);
        //}
        return  node->h;
    }
    tour suivantplayer;
    if (currentPlayer == player1) {
        suivantplayer = player2;
    }
    else {
        suivantplayer = player1;
    }



    if (maximizingPlayer) {
        int maxEval = -1000000000;
        for (Node* child : node->children) {
            int eval = minimax(child, depth - 1, false, alpha, beta, suivantplayer);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break; // Coupe beta
            }
        }
        node->h = alpha;
        return alpha;
    }
    else {
        int minEval = 1000000000;
        for (Node* child : node->children) {
            int eval = minimax(child, depth - 1, true, alpha, beta, suivantplayer);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break; // Coupe alpha
            }
        }
        node->h = beta;
        return beta;
    }
}




