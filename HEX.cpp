// HEX.cpp : Ten plik zawiera funkcjÄ âmainâŁ. W nim rozpoczyna siÄ i koÅczy wykonywanie programu.
//

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;


void initInputList(char list[]) {
    for (int i = 0; i < 121; i++) {
        list[i] = '0';
    }
}


char* getHEX(bool& readingHEX, char list[], int& fieldNumber, int& redPawns, int& bluePawns) {
    fieldNumber = 0;
    redPawns = 0;
    bluePawns = 0;

    while (readingHEX) {
        char line[70];
        cin.getline(line, 70);

        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '-' && line[i + 1] == '-' && line[i + 2] == '-') {
                readingHEX = false;
            }
            else if (line[i] == '<') {
                if (line[i + 2] == 'r') {
                    list[fieldNumber] = 'r';
                    redPawns++;
                }
                else if (line[i + 2] == 'b') {
                    list[fieldNumber] = 'b';
                    bluePawns++;
                }
                else {
                    list[fieldNumber] = 'x';
                }
                fieldNumber++;

            }
        }
    }
    char* HEXinList = new char[fieldNumber];
    for (int i = 0; i < fieldNumber; i++) {
        HEXinList[i] = list[i];
    }

    return HEXinList;
}

int isBoardCorrect(int redPawns, int bluePawns) {
    if (redPawns == bluePawns) {
        return 1;
    }
    else if (redPawns == bluePawns + 1) {
        return 1;
    }
    else return 0;
}


char** transformHEX(char list[], int HexSize) {

    char** HEXinArr = new char* [HexSize];

    for (int i = 0; i < HexSize; i++) {
        HEXinArr[i] = new char[HexSize];
    }


    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            HEXinArr[i][j] = 'E';
        }
    }
    int prevCord = 0;


    for (int i = 0; i < HexSize; i++) {
        prevCord = prevCord + i;
        HEXinArr[i][0] = list[prevCord];
        int prevCordinArr = 0;
        int distance = i + 2;
        if (distance > HexSize) {
            distance = HexSize;
        }

        int repetition = 0;
        bool lowerDistance = false;

        if (i == HexSize - 1) {
            prevCordinArr = (HexSize * HexSize) / 2 - HexSize / 2;
            distance = HexSize;
            for (int j = 1; j < HexSize; j++) {
                HEXinArr[i][j] = list[prevCordinArr + distance];
                prevCordinArr += distance;
                distance--;
            }
        }
        else {
            prevCordinArr = prevCord;
            for (int j = 1; j < HexSize; j++) {
                HEXinArr[i][j] = list[prevCordinArr + distance];
                prevCordinArr += distance;
                if (!lowerDistance && distance != HexSize) {
                    distance++;
                }
                else if (lowerDistance) {
                    distance--;
                }

                else if (distance == HexSize) {
                    repetition++;
                    if (repetition == 2) {
                        distance--;
                        repetition = 0;
                        lowerDistance = true;
                    }
                }

            }


        }


        repetition = 0;
        lowerDistance = false;
    }

    return HEXinArr;
}

int dfsRed(char** HEXinArr, int** visited, int y, int x, int HexSize) {
    if (x == HexSize - 1 && HEXinArr[y][x] == 'r') {
        return 1;

    }

    if (HEXinArr[y][x + 1] == 'r' && !visited[y][x + 1]) {
        visited[y][x + 1] = 1;
        if (dfsRed(HEXinArr, visited, y, x + 1, HexSize)) {
            return 1;
        }
    }

    if (y < HexSize - 1 && HEXinArr[y + 1][x] == 'r' && !visited[y + 1][x]) {
        if (x > 0) {
            visited[y + 1][x] = 1;
        }

        if (dfsRed(HEXinArr, visited, y + 1, x, HexSize)) {
            return 1;
        }
    }

    if (y < HexSize - 1 && HEXinArr[y + 1][x + 1] == 'r' && !visited[y + 1][x + 1]) {
        visited[y + 1][x + 1] = 1;
        if (dfsRed(HEXinArr, visited, y + 1, x + 1, HexSize)) {
            return 1;
        }
    }
    ///czesc od blue:
    if (y > 0 && HEXinArr[y - 1][x] == 'r' && !visited[y - 1][x]) {
        visited[y - 1][x] = 1;
        if (dfsRed(HEXinArr, visited, y - 1, x, HexSize)) {
            return 1;
        }
    }

    if (x > 0 && HEXinArr[y][x - 1] == 'r' && !visited[y][x - 1]) {
        visited[y][x - 1] = 1;
        if (dfsRed(HEXinArr, visited, y, x - 1, HexSize)) {
            return 1;
        }
    }

    if (x > 0 && y > 0 && HEXinArr[y - 1][x - 1] == 'r' && !visited[y - 1][x - 1]) {
        visited[y - 1][x - 1] = 1;
        if (dfsRed(HEXinArr, visited, y - 1, x - 1, HexSize)) {
            return 1;
        }
    }



    return 0;
}


int isGameOverRed(char** HEXinArr, int HexSize) {
    int** visited = new int* [HexSize];
    int result = 0;
    
    for (int i = 0; i < HexSize; i++) {
        visited[i] = new int[HexSize];
    }


    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            visited[i][j] = 0;
        }
    }


    for (int i = 0; i < HexSize; i++) {
        if (HEXinArr[i][0] == 'r' && !visited[i][0]) {
            visited[i][0] = 1;
            result = dfsRed(HEXinArr, visited, i, 0, HexSize);
            if (result) {
                break;
            }
            else continue;
        }



    }

    for (int i = 0; i < HexSize; i++) {
        delete[] visited[i];
        visited[i] = nullptr;
    }
    delete[] visited;
    return result;

}


int dfsBlue(char** HEXinArr, int** visited, int y, int x, int HexSize) {
    if (y == 0 && HEXinArr[y][x] == 'b') {
        return 1;
    }

    if (HEXinArr[y - 1][x] == 'b' && !visited[y - 1][x]) {
        visited[y - 1][x] = 1;
        if (dfsBlue(HEXinArr, visited, y - 1, x, HexSize)) {
            return 1;
        }
    }

    if (x > 0 && HEXinArr[y][x - 1] == 'b' && !visited[y][x - 1]) {
        visited[y][x - 1] = 1;
        if (dfsBlue(HEXinArr, visited, y, x - 1, HexSize)) {
            return 1;
        }
    }

    if (x > 0 && HEXinArr[y - 1][x - 1] == 'b' && !visited[y - 1][x - 1]) {
        visited[y - 1][x - 1] = 1;
        if (dfsBlue(HEXinArr, visited, y - 1, x - 1, HexSize)) {
            return 1;
        }
    }



    ///czesc od red:

    if (x < HexSize - 1 && HEXinArr[y][x + 1] == 'b' && !visited[y][x + 1]) {
        visited[y][x + 1] = 1;
        if (dfsBlue(HEXinArr, visited, y, x + 1, HexSize)) {
            return 1;
        }
    }

    if (y < HexSize - 1 && HEXinArr[y + 1][x] == 'b' && !visited[y + 1][x]) {

        visited[y + 1][x] = 1;


        if (dfsBlue(HEXinArr, visited, y + 1, x, HexSize)) {
            return 1;
        }
    }

    if (y < HexSize - 1 && x < HexSize - 1 && HEXinArr[y + 1][x + 1] == 'b' && !visited[y + 1][x + 1]) {
        visited[y + 1][x + 1] = 1;
        if (dfsBlue(HEXinArr, visited, y + 1, x + 1, HexSize)) {
            return 1;
        }
    }

    return 0;
}


int isGameOverBlue(char** HEXinArr, int HexSize) {
    int** visited = new int* [HexSize];
    int result = 0;
 
    for (int i = 0; i < HexSize; i++) {
        visited[i] = new int[HexSize];
    }


    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < HexSize; i++) {
        if (HEXinArr[HexSize - 1][i] == 'b' && !visited[HexSize - 1][i]) {
            visited[HexSize - 1][i] = 1;
            result = dfsBlue(HEXinArr, visited, HexSize - 1, i, HexSize);
            if (result) {
                break;
            }
            else continue;
        }
    }

    for (int i = 0; i < HexSize; i++) {
        delete[] visited[i];
        visited[i] = nullptr;
    }
    delete[] visited;
    return result;

}


void isGameOver(char** HEXinArr, int HexSize, int redPawns, int bluePawns) {
    if (!isBoardCorrect(redPawns, bluePawns)) {
        cout << "NO\n";
    }
    else if (isGameOverRed(HEXinArr, HexSize) && isGameOverBlue(HEXinArr, HexSize)) {
        cout << "NO\n";
    }
    else if (isGameOverRed(HEXinArr, HexSize)) {
        cout << "YES RED\n";
    }
    else if (isGameOverBlue(HEXinArr, HexSize)) {
        cout << "YES BLUE\n";
    }
    else {
        cout << "NO\n";
    }
}


int isBoardPossibleRed(char** HEXinArr, int HexSize) {
    if (!isGameOverRed(HEXinArr,HexSize)) {
        return 1;
    }
    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            if (HEXinArr[i][j] == 'r') {
                HEXinArr[i][j] = 'x';
                if (!isGameOverRed(HEXinArr,HexSize)) {
                    HEXinArr[i][j] = 'r';
                    return 1;
                }
                HEXinArr[i][j] = 'r';
            }
        }
    }
    
    return 0;
}

int isBoardPossibleBlue(char** HEXinArr, int HexSize) {
    if (!isGameOverBlue(HEXinArr,HexSize)) {
        return 1;
    }
    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            if (HEXinArr[i][j] == 'b') {
                HEXinArr[i][j] = 'x';
                if (!isGameOverBlue(HEXinArr,HexSize)) {
                    HEXinArr[i][j] = 'b';
                    return 1;
                }
                HEXinArr[i][j] = 'b';
            }
        }
    }
    

    return 0;
}


int isBoardPossible(char** HEXinArr, int HexSize, int redPawns, int bluePawns) {
    int result;
    if (!isBoardCorrect(redPawns, bluePawns)) {
        result = 0;
    }
    else if (!isBoardPossibleRed(HEXinArr, HexSize) || !isBoardPossibleBlue(HEXinArr, HexSize)) {
        result = 0;
    }
    else if (isGameOverRed(HEXinArr, HexSize) && redPawns == bluePawns + 1) {
        result = 1;
    }
    else if (isGameOverBlue(HEXinArr, HexSize) && redPawns == bluePawns) {
        result = 1;
    }
    else if (isBoardPossibleRed(HEXinArr, HexSize) && isBoardPossibleBlue(HEXinArr, HexSize) && !isGameOverBlue(HEXinArr, HexSize) && !isGameOverRed(HEXinArr, HexSize)) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
    
}


int canPlayerWin1MoveNaive(char** HEXinArr, int HexSize, int redPawns, int bluePawns, int player) {



    if (!isBoardCorrect(redPawns, bluePawns) || !isBoardPossible(HEXinArr, HexSize, redPawns, bluePawns)) {
        return 0;
    }

    if (isGameOverBlue(HEXinArr, HexSize) || isGameOverRed(HEXinArr, HexSize)) {
        return 0;
    }


    char** copiedHEX = new char* [HexSize];
    for (int i = 0; i < HexSize; i++) {
        copiedHEX[i] = new char[HexSize];
    }


    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            copiedHEX[i][j] = HEXinArr[i][j];
        }
    }
    

    int turn = (redPawns == bluePawns) ? 1 : 2;
    int result = 0;

    int freeFields = 0;
    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            if (copiedHEX[i][j] == 'x') {
                freeFields++;
            }
        }
    }

    if (player == 1) {
        for (int i = 0; i < HexSize; i++) {
            for (int j = 0; j < HexSize; j++) {
                if (copiedHEX[i][j] == 'x') {
                    copiedHEX[i][j] = 'r';
                    if (isGameOverRed(copiedHEX, HexSize)) {
                        
                        result = 1;
                        break;
                    }
                    copiedHEX[i][j] = 'x';

                }
            }
            if (result)break;
        }
    }
    else if (player == 2) {
        for (int i = 0; i < HexSize; i++) {
            for (int j = 0; j < HexSize; j++) {
                if (copiedHEX[i][j] == 'x') {
                    copiedHEX[i][j] = 'b';
                    if (isGameOverBlue(copiedHEX, HexSize)) {
                        result = 1;
                        break;
                    }
                    copiedHEX[i][j] = 'x';

                }
            }
            if (result)break;
        }
    }
   
    
    for (int i = 0; i < HexSize; i++) {
        delete[] copiedHEX[i];
        copiedHEX[i] = nullptr;
    }
    delete[] copiedHEX;

    int isPlace = 0;
    if (turn == 1 && player == 1) {
        isPlace = (freeFields >= 1) ? 1 : 0;
    }
    else if (turn == 2 && player == 1) {
        isPlace = (freeFields >= 2) ? 1 : 0;
    }
    else if (turn == 1 && player == 2) {
        isPlace = (freeFields >= 2) ? 1 : 0;
    }
    else if (turn == 2 && player == 2) {
        isPlace = (freeFields >= 1) ? 1 : 0;
    }
    
    if (result && isPlace) {
        return 1;
    }
    else return 0;
}

int canPlayerWin2MovesNaive(char** HEXinArr, int HexSize, int redPawns, int bluePawns, int player) {



    if (!isBoardCorrect(redPawns, bluePawns) || !isBoardPossible(HEXinArr, HexSize, redPawns, bluePawns)) {
        return 0;
    }

    if (isGameOverBlue(HEXinArr, HexSize) || isGameOverRed(HEXinArr, HexSize)) {
        return 0;
    }

    char** copiedHEX = new char* [HexSize];
    for (int i = 0; i < HexSize; i++) {
        copiedHEX[i] = new char[HexSize];
    }


    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            copiedHEX[i][j] = HEXinArr[i][j];
        }
    }

    

    int turn = (redPawns == bluePawns) ? 1 : 2;
    int result = 0;

    int freeFields = 0;
    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            if (copiedHEX[i][j] == 'x') {
                freeFields++;
            }
        }
    }

    int winningAtFirst = 0;
    char pawn = (player == 1) ? 'r' : 'b';
    for (int i = 0; i < HexSize; i++) {
        for (int j = 0; j < HexSize; j++) {
            if (copiedHEX[i][j] == 'x') {
                copiedHEX[i][j] = pawn;
                if (player == 1) {
                    if (isGameOverRed(copiedHEX, HexSize)) {
                        copiedHEX[i][j] = 'x';
                        winningAtFirst++;
                        continue;
                    }
                    else {
                        if (winningAtFirst) {
                            result = 1;
                            break;
                        }
                    }
                }
                else if (player == 2) {
                    if (isGameOverBlue(copiedHEX, HexSize)) {
                        copiedHEX[i][j] = 'x';
                        winningAtFirst++;
                        continue;
                    }
                    else {
                        if (winningAtFirst) {
                            result = 1;
                            break;
                        }
                    }
                }

                for (int k = i; k < HexSize; k++) {
                    for (int l = (k == i) ? j + 1 : 0; l < HexSize;l++) {
                        if (copiedHEX[k][l] == 'x') {
                            copiedHEX[k][l] = pawn;

                            if (player == 1) {
                                if (isGameOverRed(copiedHEX, HexSize)) {
                                    result = 1;
                                    break;
                                }
                                else {
                                    copiedHEX[k][l] = 'x';
                                }
                            }
                            else if (player == 2) {
                                if (isGameOverBlue(copiedHEX, HexSize)) {
                                    result = 1;
                                    break;

                                }
                                else {
                                    copiedHEX[k][l] = 'x';
                                }
                            }

                        }
                    }
                    if (result) break;
                }
                if (result) break;
                copiedHEX[i][j] = 'x';
                

            }
        }
        if (result) break;
    }

    
    int isPlace = 0;
    if (turn == 1 && player == 1) {
        isPlace = (freeFields >= 3) ? 1 : 0;
    }
    else if (turn == 2 && player == 1) {
        isPlace = (freeFields >= 4) ? 1 : 0;
    }
    else if (turn == 1 && player == 2) {
        isPlace = (freeFields >= 4) ? 1 : 0;
    }
    else if (turn == 2 && player == 2) {
        isPlace = (freeFields >= 3) ? 1 : 0;
    }

    for (int i = 0; i < HexSize; i++) {
        delete[] copiedHEX[i];
        copiedHEX[i] = nullptr;
    }
    delete[] copiedHEX;

    if (result && isPlace) {
        return 1;
    }
    else return 0;
}

char* readLine() {
    char input[50];
    int i = 0;

    while (i < 50) {
        char c = std::cin.get();
        if (c == '\n' || c == EOF) {
            break;
        }
        input[i++] = c;
    }
    input[i] = '\0';

    char* line = new char[i + 1];
    strcpy(line, input);

    return line;
}

int main() {

    char buffer;
    bool readingHEX = false;
    char list[121];
    int fieldNumber = 0;
    int redPawns = 0;
    int bluePawns = 0;
    int HexSize = 0;
    char* HEXinList = nullptr;
    char** HEXinArr = nullptr;
    char* input = nullptr;


    while (cin >> buffer) {

        if (buffer == '-') {
            input = readLine();
            if (strcmp(input, "--") == 0) {
                if (readingHEX == false) {
                    readingHEX = true;
                    if (HEXinList != nullptr) {
                        delete[] HEXinList;
                        HEXinList = nullptr;
                        for (int i = 0; i < HexSize; i++) {
                            delete[] HEXinArr[i];
                            HEXinArr[i] = nullptr;
                        }
                        delete[] HEXinArr;
                        HEXinArr = nullptr;
                    }
                    initInputList(list);
                   
                }

            }
        }



        if (readingHEX) {
            HEXinList = getHEX(readingHEX, list, fieldNumber, redPawns, bluePawns);
        }

        HexSize = sqrt(fieldNumber);
        HEXinArr = transformHEX(list, HexSize);


        if (buffer == 'B') {
            input = readLine();
            if (strcmp(input, "OARD_SIZE") == 0) {
                cout << sqrt(fieldNumber) << "\n";
            }
        }

        if (buffer == 'P') {
            input = readLine();
            if (strcmp(input, "AWNS_NUMBER") == 0) {
                cout << redPawns + bluePawns << "\n";
            }
        }

        if (buffer == 'I') {
            input = readLine();
            if (strcmp(input, "S_BOARD_CORRECT") == 0) {
                if (isBoardCorrect(redPawns, bluePawns)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            else if (strcmp(input, "S_BOARD_POSSIBLE") == 0) {
                if (isBoardPossible(HEXinArr, HexSize, redPawns, bluePawns)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            else if (strcmp(input, "S_GAME_OVER") == 0) {
                isGameOver(HEXinArr, HexSize, redPawns, bluePawns);
            }
        }

        if (buffer == 'C') {
            input = readLine();
            if (strcmp(input, "AN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0) {
                if (canPlayerWin1MoveNaive(HEXinArr, HexSize, redPawns, bluePawns, 1)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            else if (strcmp(input, "AN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0) {
                if (canPlayerWin1MoveNaive(HEXinArr, HexSize, redPawns, bluePawns, 2)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            else if (strcmp(input, "AN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0) {
                if (canPlayerWin2MovesNaive(HEXinArr, HexSize, redPawns, bluePawns, 1)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            else if (strcmp(input, "AN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0) {
                if (canPlayerWin2MovesNaive(HEXinArr, HexSize, redPawns, bluePawns, 2)) {
                    cout << "YES\n";
                }
                else cout << "NO\n";
            }
            
        }

    }

    if (HEXinList != nullptr) {
        delete[] HEXinList;
        HEXinList = nullptr;
    }

    for (int i = 0; i < HexSize; i++) {
        delete[] HEXinArr[i];
        HEXinArr[i] = nullptr;
    }
    delete[] HEXinArr;
    HEXinArr = nullptr;
    delete[] input;
}