#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const int ships_count = 2;
char alphabet[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int player_field[10][10];
int computer_field[10][10];

void clear_screen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

int character_to_number(char character) {
    for (int i = 0; i < 10; ++i) {
        if (alphabet[i] == character) return i;
    }
    return -1;
}

int get_ships_count(bool computer) { 
    int count = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int result;

            if (computer) {
                result = computer_field[i][j];
            } else {
                result = player_field[i][j];
            }

            if (result == 1) {
                count += 1;
            }
        }
    } 
    return count; 
}

void print_game_over(bool win) {
    clear_screen();

    string text;

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "    _____                        ____                " << endl;
    cout << "  / ____/___ _____ ___  ___     / __ \\_   _____  _____" << endl;
    cout << " / / __/ __ `/ __ `__ \\/ _ \\   / / / / | / / _ \\/ ___/" << endl;
    cout << "/ /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /    " << endl;
    cout << "\\____/\\__,_/_/ /_/ /_/\\___/   \\____/ |___/\\___/_/     " << endl;
    cout << endl;
    cout << endl;

    if (win) {
        text = "\033[1;32mYou win!\033[0m";
    } else {
        text = "\033[1;31mYou lose!\033[0m";
    }

    int text_space = (52 - text.length()) / 2;

    cout << setw(text_space) << ' ' << text << setw(text_space) << ' ';
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

void generate_computer_ship() {
    srand(time(0));

    int i = rand() % 10;
    int j = rand() % 10;

    if (computer_field[i][j] == 0) {
        computer_field[i][j] = 1;
    } else {
        generate_computer_ship();
    }
}

void create_fields() {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            player_field[i][j] = 0;
            computer_field[i][j] = 0;
        }
    }
}

string computer_fire(string result) {
    srand(time(0));

    int i = rand() % 10;
    int j = rand() % 10;

    if (player_field[i][j] == 1) {
        player_field[i][j] = 2;
        result += " " + string(1, alphabet[j]) + to_string(i + 1) + " computer \033[1;32mhit\033[0m!";
    } else if (player_field[i][j] == 0){
        player_field[i][j] = 3;
        result += " " + string(1, alphabet[j]) + to_string(i + 1) + " computer \033[1;31mmissed\033[0m!";
    } else {
        return computer_fire(result);
    }
    
    return result;
}

string get_cell(int value) {
    string cell;

    if (value == 0) {
        cell = "\033[1;36m.\033[0m";                
    } else if (value == 1) {
        cell = "#";
    } else if (value == 2) {
        cell = "\033[1;31m*\033[0m";                
    } else {
        cell = "\033[1;33mx\033[0m";
    }

    return cell;
}

void draw_buttle_field(bool enter_mode) {
    clear_screen();

    string title;
    int title_space;
    string player_title;
    string computer_title;
    int player_title_space;
    int computer_title_space;

    if (enter_mode == true) {
        title = "Set your ships";
        title_space = (26 - title.length()) / 2;
    } else {
        title = "Buttle";
        title_space = (52 - title.length()) / 2;
        player_title = "Player";
        player_title_space = (26 - player_title.length()) / 2;
        computer_title = "Computer";
        computer_title_space = (26 - computer_title.length()) / 2;
    }

    cout << string(title_space, ' ') << title << string(title_space, ' ');
    cout << endl;

    if (enter_mode == true) {
        cout << endl;
    } else {
        cout << string(player_title_space, ' ') << player_title << string(player_title_space, ' ');
        cout << string(2, ' ');
        cout << string(computer_title_space, ' ') << computer_title << string(computer_title_space, ' ');
        cout << endl;
    }

    cout << setw(3) << ' ';
    for (int i = 0; i < 10; i++) {
        cout << setw(1) << ' ' << alphabet[i];
    }

    cout << setw(5) << ' ';

    if (enter_mode == false) {
        cout << setw(3) << ' ';
        for (int i = 0; i < 10; i++) {
            cout << setw(1) << ' ' << alphabet[i]; 
        }
    }


    cout << endl;
    
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i + 1 << '|';
        for (int j = 0; j < 10; j++) {
            cout << ' ' << get_cell(player_field[i][j]);
        }
         
        cout << setw(5) << ' ';
        
        if (enter_mode == false) {
            cout << setw(2) << i + 1 << '|' ;
            for  (int j = 0; j < 10; j++) {
                int value;
                if (computer_field[i][j] > 1) {
                    value = computer_field[i][j];    
                } else {
                    value = 0;
                }
                cout << ' ' << get_cell(value);
            }
        }

        cout << endl;
    }
    cout << endl;
}

int * data_input(bool enter_mode) {
    char character;
    int row;
    int col;
    static int coords[2];

    cout << "Letter: ";
    cin >> character;
    cout << "Number: ";
    cin >> row;

    character = toupper(character);
    col = character_to_number(character);

    if (col == -1 || row > 10) {
        draw_buttle_field(enter_mode);
        cout << "\033[1;31mCell does not exists, try again\033[0m" << endl;
        return data_input(enter_mode);
    }

    coords[0] = row - 1;
    coords[1] = col;

    return  coords;
}

int main() {
    create_fields();
    
    draw_buttle_field(true);

    for (int i = 0; i < ships_count; i++) {
        int * coords;

        coords = data_input(true);
        
        player_field[coords[0]][coords[1]] = 1;

        generate_computer_ship();
        draw_buttle_field(true);
    }

    draw_buttle_field(false);

    while (true) {
        int * coords;
        int player_ships_count = 0;
        int computer_ships_count = 0;
        string result;

        coords = data_input(false);

        if (computer_field[coords[0]][coords[1]] == 1) {
            computer_field[coords[0]][coords[1]] = 2;
            result = string(1, alphabet[coords[1]]) + to_string(coords[0]) + " you \033[1;32mhit\033[0m!";
        } else if (computer_field[coords[0]][coords[1]] == 0) {
            computer_field[coords[0]][coords[1]] = 3;
            result = string(1, alphabet[coords[1]]) + to_string(coords[0]) + " you \033[1;31mmissed\033[0m!";
        }

        player_ships_count = get_ships_count(false);
        
        draw_buttle_field(false);
        
        
        if (player_ships_count == 0) {
            print_game_over(true);
            break;
        } 
        
        result = computer_fire(result);
        
        computer_ships_count = get_ships_count(true);

        draw_buttle_field(false);
        
        if (computer_ships_count == 0) {
            print_game_over(false);
            break;
        }

        cout << result;

        string computer_ships_text = " Computer ships count: " + to_string(computer_ships_count);

        cout << computer_ships_text << endl;
    }  
    
    return 0;
}
