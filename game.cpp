// Wejscie wyjscie. Wypisywanie tekstu
#include <iostream>
// system(), Beep(), sleep()
#include <windows.h>
// getch()
#include <conio.h>
// vector
#include <vector>

// Stale typu int
int const MAP_X = 20;
int const MAP_Y = 30;

using namespace std;

// Przechowuje pozycję na plaszczyznie 2d
struct Position2D {
    int x, y;
};

// Glowna klasa gry
class Game {

    Position2D player;
    vector<Position2D> monsters;
    int score;
    int monster_selected;
public:
    Game() : monster_selected(0), score(0) {
    // Pozycja gracza na start
        player.x = 10;
        player.y = 15;

    }
    // Przegrana
    void fail() {
        system("cls");
        cout << "GAME OVER!" << endl;
        cout << "Monsters: " << monster_selected << endl;
        cout << "Score: " << score * monster_selected  << endl;
        Beep(500, 200);
        Beep(500, 200);
        Beep(500, 200);
        system("pause");
        exit(1);
    }
    // Start gry
    void start() {
        system("title game");
        char menu = 'f';

        cout << "Select number of monsters" << endl;
        cout << "a) 1, b) 2, c) 3, d)4 " << endl;
        cin >> menu;

        switch(menu)
        {
            case 'a':
                create_monsters(1);
                monster_selected = 1;
            break;
            case 'b':
                create_monsters(2);
                monster_selected = 2;
            break;
            case 'c':
                create_monsters(3);
                monster_selected = 3;
            break;
            case 'd':
                create_monsters(4);
                monster_selected = 4;
            break;
            default:
                create_monsters(4);
                monster_selected = 4;
        }

        cout << monster_selected << endl;
    }

    // Stworzenie potworow
    void create_monsters(int number)
    {
        // Tworzy potwory
        Position2D monster = {19, 29};
        Position2D monster2 = {0, 0};
        Position2D monster3 = {0, 29};
        Position2D monster4 = {19, 0};

        // Wrzuca stworzone potwory do wektora
        // w zeleznosci od tego ile zostalo wybranych
        switch(number)
        {
            case 1:
                monsters.push_back(monster);
            break;
            case 2:
                monsters.push_back(monster);
                monsters.push_back(monster2);
            break;
            case 3:
                monsters.push_back(monster);
                monsters.push_back(monster2);
                monsters.push_back(monster3);
            break;
            case 4:
                monsters.push_back(monster);
                monsters.push_back(monster2);
                monsters.push_back(monster3);
                monsters.push_back(monster4);
            break;
        }
    }

    // Podnosi wynik
    void score_up() {
        score++;
    }

    // Zwraca referencje do wektora Position2D
    // ktorzy przechowuje pozycje potworow
    vector<Position2D>& return_ref_to_monster() {
        return monsters;
    }

    // Przesuwa gracza
    void move_player()
    {
        // Pobiera klawisz do zmiennej move
        char move = getch();

        switch(move)
        {
            case 'w':
                if(player.x-1 == -1)
                    break;
                else
                    player.x--;
            break;
            case 's':
                if(player.x+1 == MAP_X)
                    break;
                else
                player.x++;
            break;
            case 'a':
                if(player.y-1 == -1)
                    break;
                else
                player.y--;
            break;
            case 'd':
                if(player.y+1 == MAP_Y)
                    break;
                else
                player.y++;
            break;
        }
    }

    // "ai" potworow
    void monster_ai() {

        // Prosty algorytm goniacego Ai
        for(int i = 0; i < monsters.size(); i++)
        {
            if(monsters[i].x < player.x)
                monsters[i].x++;
            if(monsters[i].x > player.x)
                monsters[i].x--;
            if(monsters[i].y < player.y)
                monsters[i].y++;
            if(monsters[i].y > player.y)
                monsters[i].y--;
            if(monsters[i].x < player.x)
            monsters[i].x++;

            // Jezeli jakis potwor ma takie same pozycje jak gracz
            // To znaczy, ze go zlapal wiec koniec gry
            if(monsters[i].y == player.y && monsters[i].x == player.x)
            {
                cout << "Got you!" << endl;
                fail();
            }
        }

    }

    // Zwraca referencje do Position2D przechowujacego
    // pozycje gracza
    Position2D& return_ref_to_player() {
        return player;
    }

};

class Map {
    // Mapa gry
    int map[MAP_X][MAP_Y];

public:
    // Zeruje mape
    Map() {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                map[i][j] = 0;
            }
        }
    }

    // Rysuje mape
    void draw() {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                // Zamienia liczy na
                // odpowiednie znaki graficzne
                switch(map[i][j])
                {
                    case 0:
                        cout << ".";
                    break;
                    case 1:
                        cout << "M";
                    break;
                    case 2:
                        cout << "@";
                    break;
                }
            }
            // Kolejny wiersz mapy
            cout << endl;
        }
    }

    // Resetuje mape
    void reset() {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                map[i][j] = 0;
            }

        }
    }
    // Umieszcza gracza na mapie
    void put_player(Position2D& player) {
        map[player.x][player.y] = 2;
    }

    // Umieszcza potwory na mapie
    void put_monster(vector<Position2D>& monsters) {
        for(int i = 0; i < monsters.size(); i++)
        {
            map[monsters[i].x][monsters[i].y] = 1;
        }
    }
};

int main()
{
    // Obiekty typu Map i Game
    Map m;
    Game g;

    // Start gry
    g.start();

    // Glowna petla gry
    for(;;) {
        m.reset();
        m.put_player(g.return_ref_to_player());
        m.put_monster(g.return_ref_to_monster());
        m.draw();
        g.monster_ai();
        g.move_player();
        g.score_up();
        system("cls");
    }
    return 0;
}