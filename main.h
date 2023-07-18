#include <iostream>

#include <conio.h>
#include <windows.h>
#include <cstring> 


#define N_CELL_W 19
#define N_CELL_H 16

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13    // the enter key on Windows 10 is 13 (not 10).


void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;  // set the cursor visibility
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(out, &cursorInfo);
}


void ClearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    ShowConsoleCursor(false);
}





class Caro {
private:
	int cell[N_CELL_W * N_CELL_H][3];
    int cell_posX;
    int cell_posY;
    bool game_over;
    bool turn;
public:
	Caro() {
        game_over = false;
        turn = true; // true=X, false=O
        cell_posX = 0;
        cell_posY = 0;
        int x = 0;
        int y = -1;
        for (int i = 0; i < N_CELL_H; i++) {
            y += 3;
            x = 6;
            for (int j = 0; j < N_CELL_W; j++) {

                cell[i * N_CELL_W + j][0] = x;
                cell[i * N_CELL_W + j][1] = y;
                cell[i * N_CELL_W + j][2] = 0;
                x += 6;
            }
        }
	}

	void board();
	void draw();
    void move();
    void run();
    void check();
};


void set_cursor(int x, int y) {
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}


void Caro::board() {
    int x = 0, y = -1;
    unsigned char b = 196;
    unsigned char a = 179;
    for (int j = 0; j < 16; j++) {
        x = 2;
        y += 1;
        set_cursor(x, y);

        for (int i = 0; i < 116; i++)
            std::cout << b;

        std::cout << std::endl;

        x = 3; y += 1;
        set_cursor(x, y);

        for (int i = 0; i < 20; i++) {
            std::cout << a;
            x += 6;
            set_cursor(x, y);
        }
        std::cout << std::endl;

        x = 3; y += 1;
        set_cursor(x, y);

        for (int i = 0; i < 20; i++) {
            std::cout << a;
            x += 6;
            set_cursor(x, y);
        }
        std::cout << std::endl;
    }
    x = 2;
    y += 1;
    set_cursor(x, y);

    for (int i = 0; i < 116; i++)
        std::cout << b;

    std::cout << std::endl;

}



void Caro::draw() {

    move();
    
    for (int i = 0; i < N_CELL_H; i++) {

        for (int j = 0; j < N_CELL_W; j++) {

            set_cursor(cell[i * N_CELL_W + j][0], cell[i * N_CELL_W + j][1]);

            if (cell[i * N_CELL_W + j][2] == 1) {
                std::cout << "X";
            }
            else if (cell[i * N_CELL_W + j][2] == 2) {
                std::cout << "O";
            }
        }
    }

    check();
}


void Caro::move() {

    set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0]-1, cell[cell_posX * N_CELL_W + cell_posY][1]);
    unsigned char v = 254;
    std::cout << v;

    if (_kbhit()) {

        set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0]-1, cell[cell_posX * N_CELL_W + cell_posY][1]);
        std::cout << " ";

        int press = _getch();
        if (press == ENTER && cell[cell_posX * N_CELL_W + cell_posY][2] == 0) {
            if (turn) cell[cell_posX * N_CELL_W + cell_posY][2] = 1;               
            else cell[cell_posX * N_CELL_W + cell_posY][2] = 2;
            turn = !turn;
        }

        else if (press == KEY_LEFT || press == KEY_RIGHT || press == KEY_UP || press == KEY_DOWN) {

            switch (press) {
                
            case KEY_LEFT:
                if (cell_posY > 0) {
                    set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0], cell[cell_posX * N_CELL_W + cell_posY][1]);
                    std::cout << " ";
                    cell_posY--; 
                }
                break;

            case KEY_RIGHT:
                if (cell_posY < N_CELL_W - 1) {
                    set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0], cell[cell_posX * N_CELL_W + cell_posY][1]);
                    std::cout << " ";
                    cell_posY++;
                }
                break;

            case KEY_UP:
                if (cell_posX > 0) {
                    set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0], cell[cell_posX * N_CELL_W + cell_posY][1]);
                    std::cout << " ";
                    cell_posX--;
                }
                break;

            case KEY_DOWN:
                if (cell_posX < N_CELL_H - 1) {
                    set_cursor(cell[cell_posX * N_CELL_W + cell_posY][0], cell[cell_posX * N_CELL_W + cell_posY][1]);
                    std::cout << " ";
                    cell_posX++;
                }
                break;
            }
        }
        
    }

}



void Caro::check() {
    int point = 0;
    bool left = false;
    bool right = false;
    int k = cell[cell_posX * N_CELL_W + cell_posY][2];
    int y = cell_posY;
    int y1 = cell_posY;
    int x = cell_posX;
    int x1 = cell_posX;
    while (y < N_CELL_W && k != 0 && cell[x * N_CELL_W + y][2] == k) {
        y++;
        point++;
    }


    if (y < N_CELL_W) {
        if (cell[x * N_CELL_W + y][2] == 0) right = left = true;
    }
    else  right = true;


    while (y1 >= 0 && k != 0 && cell[x * N_CELL_W + y1][2] == k) {
        y1--;
        point++;
    }

    if (y1 >= 0) {
        if (cell[x * N_CELL_W + y1][2] == 0) right = left = true;
    }
    else left = true;


    if (point - 1 >= 5 && left && right) {
        game_over = true;
        return;
    }



}

void Caro::run() {
    while (!game_over) {
        ClearScreen();
        board();
        draw();

    }

}