#include<bits/stdc++.h>
#define ll long long
#define faster  std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLUE    "\033[94m"
#define CYAN    "\033[96m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define RED     "\033[91m"
#define MAGENTA "\033[95m"
#define WHITE   "\033[97m"

using namespace std;
using namespace chrono;

string show_menu() {
    system("cls");
    cout << WHITE << "_______________________________________" << RESET << endl;
    cout << WHITE << "|         " << BOLD << CYAN << "WELCOME TO THE MENU" << RESET << WHITE << "         |" << RESET << endl;
    cout << WHITE << "|        " << BOLD << CYAN << "Author : Parsa Sepehri" << RESET << WHITE << "       |" << RESET << endl;
    cout << WHITE << "_______________________________________" << RESET << endl;
    cout << endl;

    cout << GREEN << "1. " << YELLOW << "Make a new maze" << RESET << endl;
    cout << GREEN << "2. " << YELLOW << "Playground" << RESET << endl;
    cout << GREEN << "3. " << YELLOW << "Solve a maze" << RESET << endl;
    cout << GREEN << "4. " << YELLOW << "User information" << RESET << endl;
    cout << GREEN << "5. " << YELLOW << "History" << RESET << endl;
    cout << GREEN << "6. " << YELLOW << "Leaderboard" << RESET << endl;
    cout << RED << "7. " << "Exit" << RESET << endl;
    cout << endl;

    cout << CYAN << "Please choose an option (1-7): " << RESET << endl;
invalid:
    string num;
    cin >> num;
    if(num != "1" && num != "2" && num != "3" && num != "4" && num != "5" && num != "6" && num != "7"){
        cout << BOLD << RED << "Invalid choice,please choose an option (1-7): " << RESET << endl;
        goto invalid;
    }
    return num;
}
void easy_maze(){
    int x,y,p,al,au,bl,bu;string name;
    cout << YELLOW << "How many rows do you like to have?" << endl;
    cin >> x;
    cout << YELLOW << "How many columns do you like to have?" << endl;
    cin >> y;
    p = x + y - 2;

}
void hard_maze(){
    cout << "not finished" << endl;
}


int main(){
    faster;
start:
    string choice = show_menu();
    if(choice == "1"){
        cout  << BOLD << MAGENTA << "________Making a new maze map________" << RESET << endl;
        cout << GREEN << "1. " << YELLOW << "Easy mode" << RESET << endl;
        cout << GREEN << "2. " << YELLOW << "Hard mode" << RESET << endl;
        cout << GREEN << "3. " << YELLOW << "Return" << RESET << endl;
        invalid:
        cin >> choice;
        if(choice != "1" && choice != "2" && choice != "3"){
            cout << RED << "Invalid choice,please choose an option (1-3): " << RESET << endl;
            goto invalid;
        }
        if(choice == "1"){
            //loading animation
            char loading[] = {'|', '/', '-', '\\'};
            int i = 0;
            cout << CYAN << "Making the maze ";
            cout.flush();
            for (int j = 0; j < 20; ++j) {
                cout << "\rMaking the maze " << loading[i % 4];
                cout.flush();//immediately print in console
                this_thread::sleep_for(milliseconds(250));
                i++;
            }
            cout << RESET << endl;
            easy_maze();
        }
        else if(choice == "2"){
            //loading animation
            char loading[] = {'|', '/', '-', '\\'};
            int i = 0;
            cout << CYAN << "Making the maze ";
            cout.flush();
            for (int j = 0; j < 20; ++j) {
                cout << "\rMaking the maze " << loading[i % 4];
                cout.flush();//immediately print in console
                this_thread::sleep_for(milliseconds(250));
                i++;
            }
            cout << RESET << endl;
            hard_maze();
        }
        else{
            goto start;
        }
    }
    else if(choice == "2"){

    }
    else if(choice == "3"){

    }
    else if(choice == "4"){

    }
    else if(choice == "5"){

    }
    else if(choice == "6"){

    }
    else{
        cout << CYAN << "We are happy to see you,take care;)" << RESET << endl;
        return 0;
    }
    return 0;
}
