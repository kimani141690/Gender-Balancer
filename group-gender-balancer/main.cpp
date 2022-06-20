#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//Function prototypes
void initialize();

void load_data();

void export_data();

void generate_and_view_stats(string database[114][4], const string& name);

void apply_shuffle_algorithm();

bool file_exists(const string& fileName);

string trim(string str);

void print_database(const string& database_name, string database[114][4]);

void generate_statistics (string database[114][4],
                          int& total_male_in_group_ics_a, int& total_female_in_group_ics_a, int& total_in_group_ics_a,
                          int& total_male_in_group_ics_b, int& total_female_in_group_ics_b, int& total_in_group_ics_b,
                          int& total_male_in_group_ics_c, int& total_female_in_group_ics_c, int& total_in_group_ics_c,
                          int& total_male, int& total_female, int& total_students);

void print_statistics (const string& name,
        const int& total_male_in_group_ics_a, const int& total_female_in_group_ics_a, const int& total_in_group_ics_a,
        const int& total_male_in_group_ics_b, const int& total_female_in_group_ics_b, const int& total_in_group_ics_b,
        const int& total_male_in_group_ics_c, const int& total_female_in_group_ics_c, const int& total_in_group_ics_c,
        const int& total_male, const int& total_female, const int& total_students);

//////////Global Variables////////////////////
//Database field documentation
//ICS Group|Student ID|Student Gender|Student Name
static string original_ics_database[114][4]; //2D Array to store original ICS Data
static string updated_ics_database[114][4]; //2D Array to store updated ICS Data
//////////Global Variables////////////////////

int main() {

    //Initialize databases with field headers
    original_ics_database[0][0] = "ICS Group";
    original_ics_database[0][1] = "Student ID";
    original_ics_database[0][2] = "Student Gender";
    original_ics_database[0][3] = "Student Name";

    updated_ics_database[0][0] = "ICS Group";
    updated_ics_database[0][1] = "Student ID";
    updated_ics_database[0][2] = "Student Gender";
    updated_ics_database[0][3] = "Student Name";

    cout << "\n"
            "   _____                _             ____        _                           \n"
            "  / ____|              | |           |  _ \\      | |                          \n"
            " | |  __  ___ _ __   __| | ___ _ __  | |_) | __ _| | __ _ _ __   ___ ___ _ __ \n"
            " | | |_ |/ _ \\ '_ \\ / _` |/ _ \\ '__| |  _ < / _` | |/ _` | '_ \\ / __/ _ \\ '__|\n"
            " | |__| |  __/ | | | (_| |  __/ |    | |_) | (_| | | (_| | | | | (_|  __/ |   \n"
            "  \\_____|\\___|_| |_|\\__,_|\\___|_|    |____/ \\__,_|_|\\__,_|_| |_|\\___\\___|_|   \n"
            "==============================================================================\n";
    cout << "v0.1-SNAPSHOT | © Arabella Mutende | 8th October, 2021" << endl << endl;

    cout << "Program Features:" << endl;
    cout << "1. View Original ICS Database." << endl;
    cout << "2. View Updated ICS Database." << endl;
    cout << "3. Load Data (Populates Original ICS Database)." << endl;
    cout << "4. View Original ICS Database Statistics." << endl;
    cout << "5. View Updated ICS Database Statistics." << endl;
    cout << "6. Apply Shuffle Algorithm (Populates Updated ICS Database)." << endl;
    cout << "7. Export Data (Extracts Updated ICS Database)." << endl;
    cout << "8. Reset Program." << endl;
    cout << "0. Exit Program." << endl;
    cout << endl;

    string option_chosen = "-1";
    int int_option_chosen = -1;

    cout << "Choose option [0-8]: ";
    getline(cin, option_chosen);

    const char *option_chosen_cstr = option_chosen.c_str();
    int_option_chosen = atoi(option_chosen_cstr);

    switch (int_option_chosen) {
        case 0: {
            cout << endl;
            cout << "Bye :)" << endl;
            exit(0);
        }

        case 1: {
            print_database("Original ICS Database", original_ics_database);
            cout << endl;
            main();
        }

        case 2: {
            print_database("Updated ICS Database", updated_ics_database);
            cout << endl;
            main();
        }

        case 3: {
            cout << endl;
            load_data();
            cout << "Data loaded successfully." << endl;
            main();
        }

        case 4: {
            cout << "Calculating Statistics. Please wait..." << endl;
            generate_and_view_stats(original_ics_database, "Original ICS Database");
            main();
        }

        case 5: {
            cout << "Calculating Statistics. Please wait..." << endl;
            generate_and_view_stats(updated_ics_database, "Updated ICS Database");
            main();
        }

        case 6: {
            cout << "Applying Shuffle Algorithm. Please wait..." << endl;
            apply_shuffle_algorithm();
            cout << "Shuffle Algorithm applied successfully." << endl;
            main();
        }

        case 7: {
            cout << endl;
            export_data();
            cout << "Data exported successfully." << endl;
            main();
        }

        case 8: {
            cout << "Resetting Program. Please wait..." << endl;
            initialize();
            cout << "Program reset successful." << endl;
            main();
        }

        default: {
            cout << "Invalid option '" << option_chosen << "'. Please try again." << endl << endl;
            main();
        }
    }

    return 0;
}

void initialize() {

    //Reset all fields
    for (int row=0; row<114; row++){
        for (int field=0; field<4; field++) {
            original_ics_database[row][field] = "";
            updated_ics_database[row][field] = "";
        }
    }

    //Initialize databases with field headers
    original_ics_database[0][0] = "ICS Group";
    original_ics_database[0][1] = "Student ID";
    original_ics_database[0][2] = "Student Gender";
    original_ics_database[0][3] = "Student Name";

    updated_ics_database[0][0] = "ICS Group";
    updated_ics_database[0][1] = "Student ID";
    updated_ics_database[0][2] = "Student Gender";
    updated_ics_database[0][3] = "Student Name";
}

void generate_and_view_stats(string database[114][4], const string& name){
    //Get Statistics
    int total_male_in_group_ics_a = 0;
    int total_female_in_group_ics_a = 0;
    int total_in_group_ics_a = 0;

    int total_male_in_group_ics_b = 0;
    int total_female_in_group_ics_b = 0;
    int total_in_group_ics_b = 0;

    int total_male_in_group_ics_c = 0;
    int total_female_in_group_ics_c = 0;
    int total_in_group_ics_c = 0;

    int total_male = 0;
    int total_female = 0;
    int total_students = 0;

    generate_statistics (database,
                         total_male_in_group_ics_a, total_female_in_group_ics_a, total_in_group_ics_a,
                         total_male_in_group_ics_b, total_female_in_group_ics_b, total_in_group_ics_b,
                         total_male_in_group_ics_c, total_female_in_group_ics_c, total_in_group_ics_c,
                         total_male, total_female, total_students);

    print_statistics(name, total_male_in_group_ics_a, total_female_in_group_ics_a, total_in_group_ics_a,
                     total_male_in_group_ics_b, total_female_in_group_ics_b, total_in_group_ics_b,
                     total_male_in_group_ics_c, total_female_in_group_ics_c, total_in_group_ics_c,
                     total_male, total_female, total_students);
}

//Shuffle Algorithm
/**
 * I'll do it simple. In the loop, if my previous iteration was a male and I put in group A,
 * then my current iteration I will put in group B  if it is a male.
 * If my previous iteration was a female, and I put in group A, then my next iteration I will put in group B, if
 * it is a female
 */
void apply_shuffle_algorithm() {
    string last_male_group = "ICSB"; //Set to ICSB so that program starts putting 1st in ICSA
    string last_female_group = "ICSB";

    for(int row=1; row<114; row++){
        string ics_group = original_ics_database[row][0];
        string student_id = original_ics_database[row][1];
        string student_gender = original_ics_database[row][2];
        string student_name = original_ics_database[row][3];

        //Gender Balance
        if(student_gender == "M"){
            if(last_male_group == "ICSA") {
                updated_ics_database[row][0] = "ICSB";
                last_male_group = "ICSB";
            } else {
                updated_ics_database[row][0] = "ICSA";
                last_male_group = "ICSA";
            }
        }

        if(student_gender == "F"){
            if(last_female_group == "ICSA") {
                updated_ics_database[row][0] = "ICSB";
                last_female_group = "ICSB";
            } else {
                updated_ics_database[row][0] = "ICSA";
                last_female_group = "ICSA";
            }
        }

        //Update the rest of the details
        updated_ics_database[row][1] = student_id;
        updated_ics_database[row][2] = student_gender;
        updated_ics_database[row][3] = student_name;
    }
}

void load_data(){
    //Get ICS Group CSV paths
    string ics_group_a_path;
    string ics_group_b_path;
    string ics_group_c_path;

    cout << "Enter path to ICS Group A CSV file: ";
    getline(cin, ics_group_a_path);

    //Check if files exist
    if(!file_exists(ics_group_a_path)){
        cout << "ISC Group A CSV file '"<< ics_group_a_path << "' does NOT exist or is not readable." << endl;
    }

    cout << "Enter path to ICS Group B CSV file: ";
    getline(cin, ics_group_b_path);

    //Check if files exist
    if(!file_exists(ics_group_b_path)){
        cout << "ISC Group B CSV file '"<< ics_group_b_path << "' does NOT exist or is not readable." << endl;
    }

    cout << "Enter path to ICS Group C CSV file: ";
    getline(cin, ics_group_c_path);

    //Check if files exist
    if(!file_exists(ics_group_c_path)){
        cout << "ISC Group C CSV file '"<< ics_group_c_path << "' does NOT exist or is not readable."<< endl;
    }

    int row_counter = 1; //Keep track of the database row

    //Read ISC Group A CSV file and store data in original_ics_database (2D Array)
    ifstream ics_group_a_file(ics_group_a_path);
    if (ics_group_a_file.is_open()) {
        string row;
        while (getline(ics_group_a_file, row)) {
            //Split each row by comma and store in database
            stringstream s_stream(row);
            for(int i=1; i<4; i++){
                if(s_stream.good()){
                    string field;
                    getline(s_stream, field, ',');
                    original_ics_database[row_counter][0] = "ICSA";
                    original_ics_database[row_counter][i] = trim(field);
                }
            }
            row_counter++;
        }
        ics_group_a_file.close();
    }

    //Read ISC Group B CSV file and store data in original_ics_database (2D Array)
    ifstream ics_group_b_file(ics_group_b_path);
    if (ics_group_b_file.is_open()) {
        string row;
        while (getline(ics_group_b_file, row)) {
            //Split each row by comma and store in database
            stringstream s_stream(row);
            for(int i=1; i<4; i++){
                if(s_stream.good()){
                    string field;
                    getline(s_stream, field, ',');
                    original_ics_database[row_counter][0] = "ICSB";
                    original_ics_database[row_counter][i] = trim(field);
                }
            }
            row_counter++;
        }
        ics_group_b_file.close();
    }

    //Read ISC Group C CSV file and store data in original_ics_database (2D Array)
    ifstream ics_group_c_file(ics_group_c_path);
    if (ics_group_c_file.is_open()) {
        string row;
        while (getline(ics_group_c_file, row)) {
            //Split each row by comma and store in database
            stringstream s_stream(row);
            for(int i=1; i<4; i++){
                if(s_stream.good()){
                    string field;
                    getline(s_stream, field, ',');
                    original_ics_database[row_counter][0] = "ICSC";
                    original_ics_database[row_counter][i] = trim(field);
                }
            }
            row_counter++;
        }
        ics_group_c_file.close();
    }
}

void export_data(){
    //Get ICS Group CSV ics_group_a_file paths
    string ics_group_a_path;
    string ics_group_b_path;

    cout << "Enter path to export updated ICS Group A CSV file: ";
    getline(cin, ics_group_a_path);

    cout << "Enter path to export updated ICS Group B CSV file: ";
    getline(cin, ics_group_b_path);

    cout << "Exporting data. Please wait..." << endl << endl;

    //Print to file
    ofstream out_ics_a(ics_group_a_path);
    ofstream out_ics_b(ics_group_b_path);

    for(int row=1; row<114; row++){
        string ics_group = updated_ics_database[row][0];
        string student_id = updated_ics_database[row][1];
        string student_gender = updated_ics_database[row][2];
        string student_name = updated_ics_database[row][3];

        if(ics_group == "ICSA"){
            out_ics_a << student_id << ',' << student_gender << ',' << student_name;
            out_ics_a << '\n';
        } else {
            out_ics_b << student_id << ',' << student_gender << ',' << student_name;
            out_ics_b << '\n';
        }
    }

    out_ics_a.close();
    out_ics_b.close();
}

void generate_statistics (string database[114][4],
                          int& total_male_in_group_ics_a, int& total_female_in_group_ics_a, int& total_in_group_ics_a,
                          int& total_male_in_group_ics_b, int& total_female_in_group_ics_b, int& total_in_group_ics_b,
                          int& total_male_in_group_ics_c, int& total_female_in_group_ics_c, int& total_in_group_ics_c,
                          int& total_male, int& total_female, int& total_students){
    for(int row=1; row<114; row++){
        string group = database[row][0];
        string gender = database[row][2];

        if(gender == "M") total_male++;
        if(gender == "F") total_female++;

        if(group == "ICSA"){
            total_in_group_ics_a++;
            if(gender == "M") total_male_in_group_ics_a++;
            if(gender == "F") total_female_in_group_ics_a++;
        }

        if(group == "ICSB"){
            total_in_group_ics_b++;
            if(gender == "M") total_male_in_group_ics_b++;
            if(gender == "F") total_female_in_group_ics_b++;
        }

        if(group == "ICSC"){
            total_in_group_ics_c++;
            if(gender == "M") total_male_in_group_ics_c++;
            if(gender == "F") total_female_in_group_ics_c++;
        }

    }
    total_students = total_male+total_female;
}

bool file_exists(const string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

string trim(string str){
    if (!str.empty() && str[str.size() - 1] == '\r') {
        str.erase(str.size() - 1);
    }
    return str;
}

void print_database(const string& database_name, string database[114][4]) {
    cout << endl;
    cout << "**************************** " << database_name << " ****************************" << endl;

    for (int row=0; row<114; row++){
        //if(row == 0) cout << "#" << "\t"; else if (row < 114) cout << row << "." << "\t"; //Attempt to number rows when printing

        for (int field=0; field<4; field++){
            string value = database[row][field];
            if(value.empty()){
                cout << "******************************************************************************" << endl << endl;
                return;
            }
            if(field == 0) {if(row == 0) cout << value << "\t"; else  cout << value << "\t\t";}
            if(field == 1) {if(row == 0) cout << value << "\t"; else  cout << value << "\t\t";}
            if(field == 2) {if(row == 0) cout << value << "\t"; else  cout << value << "\t\t\t\t";}
            if(field == 3) cout << value;
        }
        cout << endl;
    }
}

void print_statistics (const string& name,
        const int& total_male_in_group_ics_a, const int& total_female_in_group_ics_a, const int& total_in_group_ics_a,
        const int& total_male_in_group_ics_b, const int& total_female_in_group_ics_b, const int& total_in_group_ics_b,
        const int& total_male_in_group_ics_c, const int& total_female_in_group_ics_c, const int& total_in_group_ics_c,
        const int& total_male, const int& total_female, const int& total_students) {
    cout << endl;
    cout << "**************************** " << name << " ****************************" << endl;
    cout << "ICS Group" << "\t" << "No. of Male Students" << "\t" << "No. of Female Students" << "\t" << "Totals" << endl;
    cout << "ICS A" << "\t\t" << total_male_in_group_ics_a << "\t\t\t\t\t\t" << total_female_in_group_ics_a << "\t\t\t\t\t\t" << total_in_group_ics_a << endl;
    cout << "ICS B" << "\t\t" << total_male_in_group_ics_b << "\t\t\t\t\t\t" << total_female_in_group_ics_b << "\t\t\t\t\t\t" << total_in_group_ics_b << endl;
    cout << "ICS C" << "\t\t" << total_male_in_group_ics_c << "\t\t\t\t\t\t" << total_female_in_group_ics_c << "\t\t\t\t\t\t" << total_in_group_ics_c << endl;
    cout << "TOTALS" << "\t\t" << total_male << "\t\t\t\t\t\t" << total_female << "\t\t\t\t\t\t" << total_students << endl;
    cout << "******************************************************************************" << endl << endl;
}
