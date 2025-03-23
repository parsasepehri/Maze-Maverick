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
bool isnumber(string num){
    if(num[0] == '-'){
        for(int i = 1; i < num.size(); i++)
            if(isdigit(num[i]) == false)
                return false;
        return true;
    }
    else{
        for(int i = 0; i < num.size(); i++)
            if(isdigit(num[i]) == false)
                return false;
        return true;
    }
}
string fix_name(string filename) {
    replace(filename.begin(), filename.end(), ' ', '_');
    return filename;
}
void easy_maze(){
    string row_check,column_check,map_name;int path_size;const int maxx = numeric_limits<int>::max();
    //getting map name to save it
    cout << YELLOW << "Choose your map name: " << RESET;
    cout.flush();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,map_name);
    map_name = fix_name(map_name);//here we use that function to replace spaces with '_'
    cout << endl;
    //getting number of rows
    cout << YELLOW << "How many rows do you like to have?" << RESET << endl;
    check_row:
    cin >> row_check;
    //checking for valid row
    if(isnumber(row_check) == false || stoi(row_check) <= 1){
        cout << RED << "Please enter a valid number which should be greater than 1: " << RESET << endl;
        goto check_row;
    }

    //getting number of columns
    cout << YELLOW << "How many columns do you like to have?" << RESET << endl;
    check_column:
    cin >> column_check;
    //checking for valid column
    if(isnumber(column_check) == false || stoi(column_check) <= 1){
        cout << RED << "Please enter a valid number which should be greater than 1: " << RESET << endl;
        goto check_column;
    }
    const int cols = stoi(column_check),rows = stoi(row_check);
    //here we are making the maze map
    random_device rd;
    mt19937 g(rd());
    path_size = rows + cols - 2;
    uniform_int_distribution<int> matrix_limit(-3, 3);
    uniform_int_distribution<int> block_limit(2, 5);
    int maze[rows][cols];
    //initializing the maze so it can help us make blocks and others later
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols; j++){
            maze[i][j] = maxx;
        }
    }
    //we are recording the steps we can go
    vector<char> steps;
    //we have to go row - 1 times down
    for(int i = 0;i < rows - 1; i++){
        steps.push_back('d');
    }
    //we have to go column - 1 times right
    for(int i = 0;i < cols - 1; i++){
        steps.push_back('r');
    }
    //we have to shuffle the steps so that we can have different ways to reach the last one
    shuffle(steps.begin(),steps.end(), g);
    int num = 0,x = 0,y = 0,sum = 0;
    //initializing the way we have
    for(int i = 0; i < steps.size();i++){
        if(i == steps.size() - 2){
            zero_error:
            num = matrix_limit(g);
            if(sum + num == 0){
                goto zero_error;
            }
            maze[y][x] = num;
            sum += num;
        }
        else{
            num_error:
            num = matrix_limit(g);
            if(num == 0){
                goto num_error;
            }
            maze[y][x] = num;
            sum += num;
        }
        if(steps[i] == 'r'){
            x++;
        }
        if(steps[i] == 'd'){
            y++;
        }
    }
    maze[rows - 1][cols - 1] = sum;
    //here we are initializing others which are not in our path
    int number_of_blocks = block_limit(g), counts = 0;
    uniform_int_distribution<int> matrix_i(0,rows - 1);
    uniform_int_distribution<int> matrix_j(0,cols - 1);
    while(counts < number_of_blocks){
        if(maze[matrix_i(g)][matrix_j(g)] == maxx){
            maze[matrix_i(g)][matrix_j(g)] = 0;
            counts++;
        }
    }
    num = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0;j < cols; j++){
            if(maze[i][j] == maxx){
                num_error2:
                num = matrix_limit(g);
                if(num == 0){
                    goto num_error2;
                }
                maze[i][j] = num;
            }
        }
    }
    //saving the maze files to maps file
    map_name = map_name + ".txt";
    ofstream file(map_name);
    file << rows << " " << cols << '\n' << path_size << '\n';
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << maze[i][j] << " ";
        }
        file << '\n';
    }
    ofstream mapsfile("maps.txt", ios::app);
    mapsfile << "\n" << map_name;
}
void hard_maze(){
    string row_check,column_check,map_name,path_check,cell_min_check,cell_max_check,block_max_check,block_min_check;int path_size,cell_min,cell_max,block_min,block_max;
    const int maxx = numeric_limits<int>::max();
    //getting map name to save it
    cout << YELLOW << "Choose your map name: " << RESET;
    cout.flush();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,map_name);
    map_name = fix_name(map_name);//here we use that function to replace spaces with '_'
    cout << endl;
    //getting number of rows
    cout << YELLOW << "How many rows do you like to have?" << RESET << endl;
    check_row:
    cin >> row_check;
    //checking for valid row
    if(isnumber(row_check) == false || stoi(row_check) <= 1){
        cout << RED << "Please enter a valid number which should be greater than 1: " << RESET << endl;
        goto check_row;
    }
    const int rows = stoi(row_check);
    //getting number of columns
    cout << YELLOW << "How many columns do you like to have?" << RESET << endl;
    check_column:
    cin >> column_check;
    //checking for valid column
    if(isnumber(column_check) == false || stoi(column_check) <= 1){
        cout << RED << "Please enter a valid number which should be greater than 1: " << RESET << endl;
        goto check_column;
    }
    const int cols = stoi(column_check);
    //getting maximum and minimum of maze cells
    cout << YELLOW << "Choose a minimum for your maze cells: " << RESET << endl;
    check_minimum:
    cin >> cell_min_check;
    if(isnumber(cell_min_check) == false){
        cout << RED << "Please enter a valid number: " << RESET << endl;
        goto check_minimum;
    }
    cell_min = stoi(cell_min_check);
    cout << YELLOW << "Choose a maximum for your maze cells: " << RESET << endl;
    check_maximum:
    cin >> cell_max_check;
    if(isnumber(cell_max_check) == false || stoi(cell_max_check) < cell_min){
        cout << RED << "Please enter a valid number: " << RESET << endl;
        goto check_maximum;
    }
    cell_max = stoi(cell_max_check);
    //getting number of steps
    cout << YELLOW << "How many steps are there in your path?" << RESET << endl;
    check_path:
    cin >> path_check;
    //checking for valid path number
    if(isnumber(path_check) == false || stoi(path_check) <= 1){
        cout << RED << "Please enter a valid number which should be greater than 1: " << RESET << endl;
        goto check_path;
    }
    path_size = stoi(path_check);
    //inja bayad check beshe path vojod dare
    //getting maximum and minimum of blocks
    cout << YELLOW << "Choose a minimum number of the blocks: " << RESET << endl;
    check_minimum2:
    cin >> block_min_check;
    if(isnumber(block_min_check) == false || stoi(block_min_check) < 0){
        cout << RED << "Please enter a valid number: " << RESET << endl;
        goto check_minimum2;
    }
    block_min = stoi(block_min_check);
    cout << YELLOW << "Choose a maximum number of the blocks: " << RESET << endl;
    check_maximum2:
    cin >> block_max_check;
    if(isnumber(block_max_check) == false || stoi(block_max_check) < block_min || stoi(block_max_check) > rows * cols - path_size){
        cout << RED << "Please enter a valid number: " << RESET << endl;
        goto check_maximum2;
    }
    block_max = stoi(block_max_check);
    //here we are making the maze map
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> matrix_limit(cell_min,cell_max);
    uniform_int_distribution<int> block_limit(block_min, block_max);
    int maze[rows][cols];
    //initializing the maze so it can help us make blocks and others later
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols; j++){
            maze[i][j] = maxx;
        }
    }
    //we are recording the steps we can go
    vector<char> steps;
    //we have to go row - 1 times down
    for(int i = 0;i < rows - 1; i++){
        steps.push_back('d');
    }
    //we have to go column - 1 times right
    for(int i = 0;i < cols - 1; i++){
        steps.push_back('r');
    }
    //we have to shuffle the steps so that we can have different ways to reach the last one
    shuffle(steps.begin(),steps.end(), g);
    int num = 0,x = 0,y = 0,sum = 0;
    //initializing the way we have
    for(int i = 0; i < steps.size();i++){
        if(i == steps.size() - 2){
            zero_error:
            num = matrix_limit(g);
            if(sum + num == 0){
                goto zero_error;
            }
            maze[y][x] = num;
            sum += num;
        }
        else{
            num_error:
            num = matrix_limit(g);
            if(num == 0){
                goto num_error;
            }
            maze[y][x] = num;
            sum += num;
        }
        if(steps[i] == 'r'){
            x++;
        }
        if(steps[i] == 'd'){
            y++;
        }
    }
    maze[rows - 1][cols - 1] = sum;
    //here we are initializing others which are not in our path
    int number_of_blocks = block_limit(g), counts = 0;
    uniform_int_distribution<int> matrix_i(0,rows - 1);
    uniform_int_distribution<int> matrix_j(0,cols - 1);
    while(counts < number_of_blocks){
        if(maze[matrix_i(g)][matrix_j(g)] == maxx){
            maze[matrix_i(g)][matrix_j(g)] = 0;
            counts++;
        }
    }
    num = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0;j < cols; j++){
            if(maze[i][j] == maxx){
                num_error2:
                num = matrix_limit(g);
                if(num == 0){
                    goto num_error2;
                }
                maze[i][j] = num;
            }
        }
    }
    //saving the maze files to maps file
    map_name = map_name + ".txt";
    ofstream file(map_name);
    file << rows << " " << cols << '\n' << path_size << '\n';
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << maze[i][j] << " ";
        }
        file << '\n';
    }
    ofstream mapsfile("maps.txt", ios::app);
    mapsfile << "\n" << map_name;
}


int main(){
    faster;
start:
    string choice = show_menu();
    if(choice == "1"){
        cout  << BOLD << MAGENTA << "________Making a new maze map________" << RESET << endl;
        cout << GREEN << "1. " << YELLOW << "Easy mode" << RESET << endl;
        cout << GREEN << "2. " << YELLOW << "Hard mode" << RESET << endl;
        cout << GREEN << "3. " << YELLOW << "Return back to menu" << RESET << endl;
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
