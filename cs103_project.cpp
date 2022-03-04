#include "libraries.h"

int main()
{
    // Initialize the variables and arrays that will store the infomration while program is being run
    string users[max_users][max_books_per_user + n] = { {"", "", "", "", ""} };
    string books[max_books][book_columns] = { {"", "Available  ", ""} };
    fstream user_file, book_file; 
    char option ='N', function = '0';

    // start the program 
    initializeArrays(users, books, user_file, book_file);
    startScreen(option);
    while (option == 'Y' || option == 'y')         // Continuosly takes input from user until they enter -1
    {
        Select_Option(function);
        switch (function)
        {
        case '1':                                // Take input user's name
            add_users(users, user_file); // add user to the file and the array
            break;
        case '2':
            delete_user(users, books, user_file, book_file); // delete user from array and file ( and also return all the books they have)
            break;
        case '3':
            search_book(books); // check if the book the user is searching for exists
            break;
        case '4':
            count_books_by_user(users);
            break;
        case '5':
            loan_books(users, books, user_file, book_file);
            break;
        case '6':
            return_book(users, books, user_file, book_file);
            break;
        case '7':
            printuser(users); // print all the current users
            break;
        case '8':
            printbooks(books);// print all the current books available
            break;
        default:
            cout << "Invalid input!" << endl; // if the option entered does not exist
            break;
        }
        cout << "Would you like to continue? (Enter Y or y): ";  cin >> option;   
    }
    cout << "\n\nInvalid Input! Program shutting down\n\n"; return 0;
}
