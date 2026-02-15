#include <iostream>
#include <cstdlib> //for rand()
#include <algorithm> //for swap()
#include <fstream>
#include <cctype>
#include <string>
#include <ctime>
#include <cmath>
#include <limits> // Required for numeric_limits
using namespace std;

time_t startTime;

void waitForUser() {
    cout << "\nPress Enter to continue...";
    // Clear any newline characters left in the buffer from previous 'cin' calls
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string dummy;
    getline(cin, dummy); // Wait for the user to press Enter
}

void shuffleArray(int arr[], int n) { //n is size of array
    for (int i = n - 1; i > 0; i--) { //start from end of array
        int j = rand() % (i + 1); //random index from 0 to i 
        // no matter what random number is generated, it will always be less than or equal to i
        swap(arr[i], arr[j]); //swap random index with current index
    }
}

bool isSafe(int board[9][9], int row, int col, int digit) {
    // row check
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == digit)
            return false;
    }
    // column check
    for (int j = 0; j < 9; j++) {
        if (board[j][col] == digit)
            return false;
    }
    //sub-grid check
    int str = row / 3 * 3; //row index of sub-grids first cell
    int stc = col / 3 * 3; //column index of sub-grids first cell
    for (int i = str; i < str + 3; i++) {
        for (int j = stc; j < stc + 3; j++)
            if (board[i][j] == digit)
                return false;
    }
    return true;
}

bool generateFullGrid(int grid[9][9], int row, int col) {

    //Base case 1: if we have reached the end of the grid
    if (row == 8 && col == 9)
        return true;

    //Base case 2: if we reach end of column, move to next row
    if (col == 9) {
        row++;
        col = 0;
    }

    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Array of numbers from 1 to 9
    shuffleArray(numbers, 9); // Shuffle the numbers array
    for (int i = 0; i < 9; i++) {
        int num = numbers[i];// Get the shuffled number 
        if (isSafe(grid, row, col, num)) { // Check if it's safe to place the number
            grid[row][col] = num; // Place the number
            if (generateFullGrid(grid, row, col + 1)) // Recur to place next number in the next cell
                return true;
        }
        grid[row][col] = 0; // set the cell back to 0 (backtracking)
    }
    return false; // Trigger backtracking (returning false takes it back to previous call)
}

// 3. Difficulty levels
void levels(int& removeCount, int& lives) {
    int level;
    //removeCount is number of cells to remove
    cout << "Select difficulty level:\n";
    cout << "Type\n1 for easy\n2 for medium\n3 for Hard\n ";
    cin >> level;
    switch (level) {
    case 1:
        // easy
        removeCount = 30;
        lives = 100;
        break;
    case 2:
        // medium
        removeCount = 40;
        lives = 35;
        break;
    case 3:
        //hard
        removeCount = 55;
        lives = 20;
        break;
    default:
        cout << "Invalid choice, defaulting to easy.\n";
        removeCount = 30;
        lives = 100;
    }
}

// 4. Removing cells to create puzzle
// In main: call the levels() function to get count of cells to remove

void removeCells(int grid[9][9], int count) {
    int cells[81]; //an array to store 1-81 (9x9 = 81 cells)
    for (int i = 0; i < 81; i++) {
        cells[i] = i + 1; //filling array with values from 1 to 81
    }
    shuffleArray(cells, 81); //shuffle the array using the same logic as before

    for (int i = 0; i < count; i++) {
        int cell = cells[i]; //get the cell number to remove

        // General rule for any N x N grid:
        // row = index / N
        // col = index % N
        // Division tells how many full rows have passed,
        // Modulo tells how far along the current row the cell is.

        int row = (cell - 1) / 9; //calculate row index, subtract 1 to convert to 0-based row
        int col = (cell - 1) % 9; //calculate column index, // subtract 1 to convert to 0-based column
        grid[row][col] = 0; //remove the cell by setting it to 0
    }
    //each number in the shuffled cells array corresponds to a unique cell in the grid
    //this prevents removing the same cell multiple times
    //so this is more efficient than randomly generating row and column indices repeatedly
}

void showAuthHeader() {
    cout << "========================================\n";
    cout << "        S U D O K U   M A S T E R\n";
    cout << "========================================\n";
}
int header_width = 40;
int grid_width = 28;
int padd = (header_width - grid_width) / 2;

void showInstructions() {
    system("cls"); // Clear screen
    showAuthHeader();
    cout << "------------- INSTRUCTIONS -------------\n";
    cout << "1. The goal is to fill a 9x9 grid with digits.\n";
    cout << "2. Each column, row, and 3x3 subgrid must contain\n";
    cout << "   digits 1-9.\n";

    cout << "------------- HOW TO PLAY -------------\n\n";

    cout << "1. DIFFICULTY LEVELS:\n";
    cout << "   - Easy:   100 Lives - 30 cells would be removed from the puzzle.\n";
    cout << "   - Medium: 35 Lives - 40 cells would be removed from the puzzle.\n";
    cout << "   - Hard:   20 Lives - 55 cells would be removed from the puzzle.\n\n";

    cout << "2. CONTROLS:\n";
    cout << "   - To play: Enter ROW space COL space VALUE\n";
    cout << "     (Example: '1 2 5' puts 5 in Row 1, Column 2)\n";
    cout << "   - Press 'h' for a Hint (Costs 100 pts)\n";
    cout << "   - Press 'q' to Quit game\n\n";

    cout << "3. FEEDBACK COLORS (What do they mean?):\n";
    cout << "   - Green:  Correct! The number belongs there.\n";
    cout << "   - Orange: Close! You are within 1 or 2 digits.\n";
    cout << "   - Red:    Far off. Try a completely different number.\n\n";

    cout << "4. SCORING & RULES:\n";
    cout << "   - You start with 1000 points.\n";
    cout << "   - Correct Move:  +25 Points\n";
    cout << "   - Invalid Move:  -50 Points & Lose 1 Life\n";
    cout << "   - Timer: Finish under 3 minutes! After that, -10 points per minute.\n";
    cout << "   - GAME OVER if Lives reach 0 or Score reaches 0.\n";

    waitForUser();
}

void padding() {
    for (int i = 0; i < padd; i++) {
        cout << " ";
    }
}

string printColor(int userVal, int correctVal) {
    if (userVal == correctVal) {
        return "\033[1;32m" + to_string(userVal) + "\033[0m"; // Green
    }
    else if (abs(userVal - correctVal) == 1 || abs(userVal - correctVal) == 2) {
        return "\033[0;33m" + to_string(userVal) + "\033[0m"; // Yellow
    }
    else {
        return "\033[1;31m" + to_string(userVal) + "\033[0m"; // Red
    }
}

int solution[9][9] = { 0 }; //global solution grid for coloring
bool userEntered[9][9] = { false }; //checking if user entered value or not for coloring

void displayFullGrid(int grid[9][9]) {
    padding();
    cout << "--- CURRENT GAME GRID ---\n\n";
    padding();
    cout << "    1 2 3   4 5 6   7 8 9\n";
    padding();
    cout << "  +-------+-------+------+\n";
    for (int i = 0; i < 9; i++) {
        padding();
        cout << i + 1 << " | ";
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                cout << ". ";
            }
            else if (userEntered[i][j]) {
                cout << printColor(grid[i][j], solution[i][j]) << " ";
            }
            else {
                cout << grid[i][j] << " ";
            }
            if (j == 2 || j == 5) {
                cout << "| ";
            }

        }
        cout << endl;
        if (i == 2 || i == 5 || i == 8) {
            padding();
            cout << "  +-------+-------+------+\n";
        }
    }
    padding();
    cout << "\n-------------------------------------\n";
}

void startTimer() {
    startTime = time(0);
}

int getElapsedTime() {
    return (int)(time(0) - startTime);
}

string convertTime(int totalSeconds) {
    int h = totalSeconds / 3600;
    int m = (totalSeconds % 3600) / 60;
    int s = totalSeconds % 60;

    //tenary operator to check if the num is single digit then it should print a leading 0.
    string hh = (h < 10 ? "0" : "") + to_string(h);
    string mm = (m < 10 ? "0" : "") + to_string(m);
    string ss = (s < 10 ? "0" : "") + to_string(s);

    return hh + ":" + mm + ":" + ss;
}

int calculateScore(int elapsedSeconds, int invalidMoves, int revealedBoxes, int score) {
    const int baseScore = 1000;

    int timePenalty = (elapsedSeconds > 180 ? (elapsedSeconds - 180) / 60 * 10 : 0);      // 2 points per second after 3 minutes
    int invalidPenalty = invalidMoves * 50;    // 50 points per invalid move
    int hintPenalty = revealedBoxes * 100;     // 100 points per revealed box

    int final_score = baseScore - (timePenalty + invalidPenalty + hintPenalty) + score;
    if (final_score < 0) final_score = 0; // Ensure score is not negative

    return final_score;
}

void showWin(int finalGrid[9][9], int totalSeconds, int invalidMoves, int revealedBoxes, int score) {
    system("cls");
    showAuthHeader();
    cout << "\n\n";
    displayFullGrid(finalGrid);
    cout << "\n****************************************\n";
    cout << "       C O N G R A T U L A T I O N S!   \n";
    cout << "****************************************\n";
    cout << "   You solved the puzzle in " + convertTime(totalSeconds) + " seconds!\n";
    cout << "   With a score of " << calculateScore(totalSeconds, invalidMoves, revealedBoxes, score) << "\n";
    cout << "****************************************\n\n";
    waitForUser();
}

bool checkLoss(int lives, int score, const string& currentUser) {
    if (lives <= 0) {
        system("cls");
        cout << "========================================\n";
        cout << "          G A M E   O V E R\n";
        cout << "========================================\n";
        cout << "Oh no! " << currentUser << ", you have no lives left.\n";
        cout << "Better luck next time!\n";
        waitForUser();
        return true; // game over
    }

    if (score <= 0) {
        system("cls");
        cout << "========================================\n";
        cout << "          G A M E   O V E R\n";
        cout << "========================================\n";
        cout << "Oh no! " << currentUser << ", your score dropped to zero.\n";
        cout << "Better luck next time!\n";
        waitForUser();
        return true; // game over
    }

    return false; // game continues
}

string toLowerStr(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

void signUp() {
    string user, pass;
    string u, p;
    int a;

    // showAuthHeader();
    cout << "-------------- SIGN UP -----------------\n";
    cout << "Enter new username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    // Check if user already exists
    ifstream fin;
    fin.open("users.txt");

    while (fin >> u >> p >> a) {
        if (u == user) {
            cout << "User already exists!\n";
            fin.close();
            return;
        }
    }
    fin.close();

    // Add user at end of file (NO OVERWRITING)
    ofstream fout;
    fout.open("users.txt", ios::app);
    fout << user << " " << pass << " 0\n";
    fout.close();

    cout << "Signup successful!\n";
}

bool login(string& currentUser, int& attempts) {
    string user, pass;
    string u, p;
    int a;

    showAuthHeader();
    cout << "--------------- LOGIN ------------------\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    ifstream fin("users.txt");
    ofstream temp("temp.txt");

    bool foundUser = false;
    bool correctPassword = false;
    while (fin >> u >> p >> a) {
        if (toLowerStr(u) == toLowerStr(user)) {
            foundUser = true;
            if (p == pass) {
                correctPassword = true;
                currentUser = u;
                a++;
                attempts = a;
            }
        }
        temp << u << " " << p << " " << a << endl; // writing all users back
    }
    if (!foundUser) {
        cout << "Username not found. Please sign up first.\n";
    }
    else if (!correctPassword) {
        cout << "Incorrect password. Try again!\n";
    }


    fin.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (foundUser) {
        cout << "----------------------------------------\n";
        cout << "Welcome " << currentUser << " | Attempt #: " << attempts << endl;
        cout << "----------------------------------------\n";
        return true;
    }
    else {
        cout << "Invalid Login!\n";
        return false;
    }
}

string getColoredValue(int userVal, int correctVal, string& feedback) {
    if (userVal == correctVal) {
        feedback = "Perfect! This is the correct value.";
        return "\033[1;32m" + to_string(userVal) + "\033[0m"; // Green
    }
    else if (abs(userVal - correctVal) == 1) {
        feedback = "Very close! You're just 1 away.";
        return "\033[0;33m" + to_string(userVal) + "\033[0m"; // Yellow
    }
    else if (abs(userVal - correctVal) == 2) {
        feedback = "Close! You're within 2 steps.";
        return "\033[0;33m" + to_string(userVal) + "\033[0m";// Yellow
    }
    else {
        feedback = "Far off! Try thinking about row, column, and box constraints.";
        return "\033[1;31m" + to_string(userVal) + "\033[0m"; // Red
    }
}

void revealRandomBox(int game[9][9], int solution[9][9], int originalGrid[9][9]) {
    int r, c;

    do {
        r = rand() % 9;
        c = rand() % 9;
    } while (originalGrid[r][c] != 0 || game[r][c] != 0);

    game[r][c] = solution[r][c];
    displayFullGrid(game);
    cout << "Revealed: The number at (" << r + 1 << "," << c + 1 << ") is " << game[r][c] << endl;;
}

//MAIN FUNCTION

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int grid[9][9] = { 0 };
    int originalGrid[9][9] = { 0 };

    int choice;
    string currentUser;
    int attempts = 0;
    bool loggedIn = false;

    while (true) {
        system("cls");
        showAuthHeader();

        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            signUp();
            waitForUser();
        }

        else if (choice == 2) {
            system("cls");
            loggedIn = login(currentUser, attempts);
            waitForUser();

            if (loggedIn) {
                // Post-login Menu Loop
                while (true) {
                    system("cls");
                    showAuthHeader();
                    cout << "User: " << currentUser << "\n\n";
                    cout << "1. Start Game\n";
                    cout << "2. Instructions\n";
                    cout << "3. Logout\n";
                    cout << "Enter choice: ";
                    int menuChoice;
                    cin >> menuChoice;

                    if (menuChoice == 2) {
                        showInstructions();
                    }
                    else if (menuChoice == 3) {
                        loggedIn = false;
                        break;
                    }
                    else if (menuChoice == 1) {
                        // START GAME SETUP
                        for (int i = 0; i < 9; i++)
                            for (int j = 0; j < 9; j++)
                                solution[i][j] = grid[i][j] = originalGrid[i][j] = 0;

                        generateFullGrid(solution, 0, 0);
                        for (int i = 0; i < 9; i++)
                            for (int j = 0; j < 9; j++)
                                grid[i][j] = solution[i][j];

                        int lives;
                        int score = 0;
                        int removeCount;
                        levels(removeCount, lives);
                        removeCells(grid, removeCount);
                        int to_fill = removeCount;
                        int filled = 0;

                        for (int i = 0; i < 9; i++)
                            for (int j = 0; j < 9; j++)
                                originalGrid[i][j] = grid[i][j];
                        for (int i = 0; i < 9; i++)
                            for (int j = 0; j < 9; j++)
                                userEntered[i][j] = false;

                        startTimer();

                        string input;
                        int invalidMoves = 0;
                        int revealedBoxes = 0;
                        while (true) {
                            system("cls");
                            showAuthHeader();
                            int elapsedSecs = getElapsedTime();
                            cout << "\tLives: " << lives << "    \tScore: " << calculateScore(elapsedSecs, invalidMoves, revealedBoxes, score) << "\n\n";
                            displayFullGrid(grid);
                            cout << "Elapsed Time: " + convertTime(getElapsedTime()) << endl;
                            /*cout << "\n--- SOLUTION (DEBUG) ---\n";
                            displayFullGrid(solution);*/

                            // Instructions for the user on every turn
                            cout << "Enter ROW (1-9) COL (1-9) VALUE (1-9), OR 'h' for Hint, OR 'q' to Quit: ";
                            cin >> input; // Read the first "token"

                            // 1. Check for Quit
                            if (input == "q" || input == "Q") {
                                int totalTime = getElapsedTime();
                                cout << "\nGame Over!\n";
                                cout << "Player: " << currentUser << "\nTime: " + convertTime(totalTime) + "s\n";
                                waitForUser();
                                break;
                            }

                            // 2. Check for Hint
                            else if (input == "h" || input == "H") {
                                revealRandomBox(grid, solution, originalGrid);
                                filled++;
                                revealedBoxes++;

                                if (filled == to_fill) {
                                    showWin(grid, getElapsedTime(), invalidMoves, revealedBoxes, score);
                                    break;
                                }
                                waitForUser();
                            }

                            // 3. Check for Numeric Input (The Move)
                            else if (isdigit(input[0])) {
                                int r_in, c_in, v_in;

                                // STEP 1: PARSE ROW 
                                try {
                                    r_in = stoi(input);
                                }
                                catch (...) {
                                    cout << "Invalid input format.\n";
                                    cin.clear();
                                    waitForUser();
                                    continue; // Restart loop
                                }

                                // STEP 2: VALIDATE ROW IMMEDIATELY
                                if (r_in < 1 || r_in > 9) {
                                    cout << "\nInvalid Row! Please enter a number between 1 and 9.\n";
                                    waitForUser();
                                    continue; // RESTART LOOP. Do not ask for column.
                                }

                                // STEP 3: GET COLUMN AND VALUE 
                                // If user typed "1 5 6" (all on one line), cin picks up 5 and 6 automatically.
                                // If they only typed "1" (newline detected), we prompt them.
                                if (cin.peek() == '\n') {
                                    cout << "Enter Column and Value: ";
                                }

                                // Check if input is actually numbers
                                if (!(cin >> c_in >> v_in)) {
                                    cout << "\nInvalid input! Columns and Values must be numbers.\n";
                                    cin.clear();
                                    waitForUser();
                                    continue;
                                }

                                // STEP 4: VALIDATE COL/VAL RANGES 
                                // Crucial: We check this BEFORE accessing the grid arrays.
                                if (c_in < 1 || c_in > 9 || v_in < 1 || v_in > 9) {
                                    cout << "\nInvalid Column or Value! Must be 1-9.\n";
                                    waitForUser();
                                    continue; // Restart loop so we never touch 'originalGrid' with bad indices
                                }

                                // STEP 5: LOGIC CHECKS (Safe Indices Guaranteed)
                                int r = r_in - 1;
                                int c = c_in - 1;

                                string feedback;
                                string coloredVal = getColoredValue(v_in, solution[r][c], feedback);

                                if (originalGrid[r][c] != 0) {
                                    cout << "Locked cell! You cannot change this.\n";
                                    waitForUser();
                                    continue;
                                }

                                if (!isSafe(grid, r, c, v_in)) {
                                    cout << "Rule violation! (Row/Col/Box conflict)\n";
                                    invalidMoves++;
                                    lives--;
                                    waitForUser();
                                    continue;
                                }

                                if (checkLoss(lives, calculateScore(elapsedSecs, invalidMoves, revealedBoxes, score), currentUser)) {
                                    break;
                                }

                                // STEP 6: EXECUTE VALID MOVE
                               // Track if cell was empty before
                              // STEP 6: EXECUTE VALID MOVE ---
                                bool wasEmpty = (grid[r][c] == 0);

                                if (wasEmpty) {
                                    filled++;  // count only once per cell

                                    // Give feedback ONLY on first-time entry
                                    if (v_in == solution[r][c]) {
                                        score += 25;
                                        cout << "Correct placement!\n";
                                    }
                                    else {
                                        cout << "Valid but incorrect placement!\n";
                                    }
                                }
                                else {
                                    // Overwriting previous user entry
                                    cout << "You updated your previous entry.\n";
                                }

                                // Apply move (always allowed for user-entered cells)
                                grid[r][c] = v_in;
                                userEntered[r][c] = true;

                                waitForUser();

                                // Check Win
                                if (filled == to_fill) {
                                    showWin(grid, getElapsedTime(), invalidMoves, revealedBoxes, score);
                                    break;
                                }
                            }
                            else {
                                cout << "Invalid command. Type 'h', 'q', or a row col and val.\n";
                                waitForUser();
                            }
                        }
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "Goodbye!\n"; break;
        }
        else {
            cout << "Invalid choice! Please enter 1, 2 or 3\n";
            cin.clear(); // Clear error flags (in case user types letters)
            waitForUser();
        }

    }
    return 0;
}