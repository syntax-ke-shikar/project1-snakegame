#include <iostream>
#include <conio.h>                                                                                      //for console input / output
#include <windows.h>
#include <ctime>
#include <vector>
#include<fstream>                                                                                      //file handling
#include<cstdlib>                                                                                      // for rand and srand functions
using namespace std;

class SnakeGame {
private:
    struct Node {
        int x, y;
        Node* next;
        Node(int x, int y) : x(x), y(y), next(nullptr) {}
    };

    struct obstacle{
        int obsx;int obsy;
    };
    obstacle o[5];

    bool gameOver1,gameOver2, isMultiplayer;
    const int width = 30;
    const int height = 30;
    int x1, y1, x2, y2, fruitX, fruitY, score1, score2;
    Node *snake1, *tail1, *snake2, *tail2;
    
    HANDLE hConsole;

    enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    direction dir1, dir2;


public:

    

    void HideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.bVisible = false;
        cursorInfo.dwSize = 1;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
    
    SnakeGame(bool multiplayer)                                                                      // constructor
        : isMultiplayer(multiplayer)                                                                 // assigns value to these variables
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Setup();
        HideCursor();
        
    }

    ~SnakeGame() {                                                                                   //destructor 
                                                                       
        del_snake(snake1);
        del_snake(snake2);  

    }


    int load_highscore() {
        int highScore;
        ifstream file("highscore.txt");
        if (file) file >> highScore;
        else highScore = 0;
        file.close();
        return highScore;
    }

    void save_highscore() {
        int highScore=load_highscore();
        
        if (score1 > highScore) {
            highScore = score1;
            ofstream file("highscore.txt");
            file << highScore;
            file.close();
        }
    }
    void del_snake(Node*& head) {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void obstacles()
    {
        if (!isMultiplayer) {
            for (int i = 0; i < 5; i++) {
                o[i].obsx=rand()%width;
                o[i].obsy=rand()%height;
            }
        }
    }


    void Setup() 
    {
        gameOver1 = false;gameOver2=false;
        dir1 = RIGHT;                                                                               //initial directions of the snake
        dir2 = UP;
        x1 = width / 4; y1 = height / 2;                                                            // initial coordinates of snakes
        x2 = 3 * width / 4; y2 = height / 2;                                                        
        score1 = score2 = 0;
        snake1 = tail1 = nullptr;
        snake2 = tail2 = nullptr;

        HideCursor();
        
        
        srand(static_cast<unsigned int>(time(0)));                          // to ensure that the sequence of random number generated is different each time
        fruitX = rand() % width;
        fruitY = rand() % height;
        
        for (int i = 0; i < 3; i++) {                                                               // To initialise the snake's length to 3 units
            addtail(snake1, tail1, x1 - i, y1);
            if (isMultiplayer) 
                addtail(snake2, tail2, x2 + i, y2);
        }

        if (!isMultiplayer) 
            obstacles();
    }

    void addtail(Node*& head, Node*& tail, int x, int y) 
    {
        Node* new_part = new Node(x, y);
        if (!head) {                                                                                
            head = tail = new_part;
        }
        else
        {
            new_part->next = head;                                                                // adding a new node at the front 
            head = new_part;
        }
    }

    
    bool collision(Node* head, int x, int y) 
    {
        while (head) 
        {
            if (head->x == x && head->y == y) return true;
            head = head->next;
        }
        return false;
    }

    void movesnake(int& x, int& y, direction dir, Node*& head, Node*& tail, int& score,bool gameOver)
    {
        if(!gameOver)
        {
            int prevX = x, prevY = y;
            switch (dir) {
                case LEFT: x--; break;
                case RIGHT: x++; break;
                case UP: y--; break;
                case DOWN: y++; break;
            }
            if (x >= width || x < 0 || y >= height || y < 0)
            {
                if(head==snake1)
                    gameOver1=true;
                gameOver2=true;

            }
            if (collision(head, x, y)) 
            {
                   if(head==snake1)                                                            // checks collision of the snake with itself
                        gameOver1 = true;
                   gameOver2=true;
            }

            // Check collision with the other snake (only in multiplayer mode)
            if (isMultiplayer)
            {

                if (head == snake1 && collision(snake2, x, y)) 
                    gameOver1 = true; // Snake 1 hits Snake 2

                if (head == snake2 && collision(snake1, x, y)) 
                    gameOver2 = true; // Snake 2 hits Snake 1

            }

            if (!isMultiplayer) 
                for(int i=0;i<5;i++)
                {
                    if(x==o[i].obsx && y==o[i].obsy)
                        gameOver1=true;
                }
            
            bool fruit_check = (x == fruitX && y == fruitY);                                               // checks whether fruit is eaten or not
            if (fruit_check) {
                score += 10; 
                fruitX = rand() % width; 
                fruitY = rand() % height;                                                            // generates next fruit coordinates
                addtail(head, tail, prevX, prevY);                                                   // increases the tail segment
            } 
            else 
            {
                Node* new_head = new Node(prevX, prevY);                                   //moves the snake ahead by updating both head and tail coordinates
                new_head->next = head;
                head = new_head;
                Node* temp = head;
                while (temp->next->next) 
                    temp = temp->next;
                delete temp->next;                                                       //deletes the last segment of the tail to ensure length remains same 
                temp->next = nullptr;
            }
        }
        else 
            del_snake(head);
    }

    void Draw() {
 

    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);                         //moves the cursor to the topleft point on the screen (to prevent flickering)

    string output;
    for (int i = 0; i < width + 2; i++) output += "#";
    output += "\n";

    for (int i = 0; i < height; i++) {
        output += "#";                                                                               // draws the boundaries
        for (int j = 0; j < width; j++) {                       
            if (i == y1 && j == x1) output += "O";                                                   //The head of snake1
            else if (isMultiplayer && i == y2 && j == x2) output += "X";                             //head of snake2
            else if (i == fruitY && j == fruitX) output += "F";                                      // draws the fruit
            else {
                bool printed = false;
                
                // Draw Snake 1
                Node* temp = snake1;
                while (temp) {
                    if (temp->x == j && temp->y == i && !gameOver1) {
                        output += "o";
                        printed = true;
                        break;
                    }
                    temp = temp->next;
                }
                
                // Draw Snake 2 (for Multiplayer Mode)
                if (isMultiplayer) {
                    temp = snake2;
                    while (temp) {
                        if (temp->x == j && temp->y == i && !gameOver2) {
                            output += "x";
                            printed = true;
                            break;
                        }
                        temp = temp->next;
                    }
                }

                // Draw Obstacles
                for (int k=0;k<5;k++) {
                    if (o[k].obsx == j && o[k].obsy == i) {
                        output += "#";
                        printed = true;
                        break;
                    }
                }

                if (!printed) output += " ";
            }
        }
        output += "#\n";
    }

    for (int i = 0; i < width + 2; i++) output += "#";
    output += "\n";
    output += "Score1: " + to_string(score1);
    
    if (isMultiplayer) 
    {
        output += " Score2: " + to_string(score2);
        output+="\n";
    }
    else
    {
        save_highscore();                                                                            //updates the HighScore in the file
        output += " High Score: " + to_string(load_highscore()) +"\n";
    }

    cout << output;
}

    void Input() {
        if (_kbhit()) {                                                                      // checks for input from keyboard w/o waiting for enter 
            switch (_getch()) {                                                                      // gets the key that has been pressed 
                case 'a': if (dir1 != RIGHT) dir1 = LEFT; break;
                case 'd': if (dir1 != LEFT) dir1 = RIGHT; break;
                case 'w': if (dir1 != DOWN) dir1 = UP; break;
                case 's': if (dir1 != UP) dir1 = DOWN; break;
                case 'j': if (isMultiplayer && dir2 != RIGHT) dir2 = LEFT; break;
                case 'l': if (isMultiplayer && dir2 != LEFT) dir2 = RIGHT; break;
                case 'i': if (isMultiplayer && dir2 != DOWN) dir2 = UP; break;
                case 'k': if (isMultiplayer && dir2 != UP) dir2 = DOWN; break;
                case 'x': gameOver1 = true; break;
            }
        }
    }

    void Logic()
    {
        movesnake(x1, y1, dir1, snake1, tail1, score1,gameOver1);
        if (isMultiplayer) 
        {
            movesnake(x2, y2, dir2, snake2, tail2, score2,gameOver2);
        }
    }

    bool IsgameOver() const                                                                   // function to check if game is over
        { 
            if (isMultiplayer)
            {
                if(gameOver1 && gameOver2)
                        return gameOver1;
            }                                                                       
            return gameOver1;
        } 
    
    int multi_winner()
    {
        if(score1>score2)
            return 1;
        else if(score2>score1)
            return 2;
        else
            return 3;
    }
};

int main() {
    int choice, mode;
    while (true) {
        cout << "1. Single Player\n2. Multiplayer\n";
        cin >> choice;
        bool multiplayer = (choice == 2);

        system("CLS");                                          

        SnakeGame game(multiplayer);
        while (!game.IsgameOver() )
        {
            game.Draw();
            game.Input();
            game.Logic();
            Sleep(150);
        }
        cout << "Game Over!\n";
        if(multiplayer)
        {
            int win=game.multi_winner();
            if(win==1)
                cout<<"Player 1 wins!!\n";
            else if(win==2)
                cout<<"Player 2 wins!!\n";
            else    
                cout<<"It's a TIE\n";
        }
        Sleep(4000);
        system  ("CLS");
        cout << "Do you want to restart? (y/n): ";
        char restart;
        cin >> restart;
        if (restart != 'y' && restart != 'Y') break;
    }
    return 0;
}
