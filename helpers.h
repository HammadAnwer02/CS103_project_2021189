#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::for_each;
using std::toupper;
using std::setw;
using std::fstream;
using std::ios;
using std::ifstream;
using std::setfill;




const int not_found = -1;
const int max_books = 50;
const int max_users = 10;
const int max_books_per_user = 3;
const int n = 2;//additional columns for the user array
const int book_columns = 3;
const int loan = 1;
const int returnBook = 2;
const int by_id = 4;
const int by_name = 5;
const int return_books_by_user= 7;
const int not_available=8;

int count_books_by_user(string [][max_books_per_user+n]);

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
void startScreen(char &opt)
{
    cout << setw(50) << setfill('_')<< endl
    << "|" << setw(17) << setfill(' ') << "GIKI LIBRARY MANAGEMENT SYSTEM" << "|" 
<< setw(50) << setfill('_') << "\n\n\n\n";

cout << "Would you like to continue? (Enter Y or y) : ";
cin >> opt;
}
void Select_Option(char &function)
{
    system("CLS");
     cout << "\n\nChoose one of the following options: " <<endl << setw(100) << std::setfill('_') << "\n\n"
            << "1) To Add student to library," << endl <<setw(100)  << "\n\n"
            << "2) To delete a student from the library, " << endl << setw(100) << "\n\n"
            << "3) To Search for a book in the library," << endl << setw(100) << "\n\n"
            << "4) To Search for how many books a user has issued, " << endl << setw(100) << "\n\n"
            << "5) To Loan a book from the library," << endl << setw(100) << "\n\n"
            << "6) To Return a book to the library," << endl << setw(100) << "\n\n"
            << "7) To print all the users currently in the library," << endl << setw(100) << "\n\n"
            << "8) To display all the books available." << endl << setw(100) << "\n\n" << std::setfill(' ');
    cout << "\n\nEnter the operation you would like to perform: ";
    cin >> function;
    cout << "\n\n";
}
void delete_usr(string arr[][max_books_per_user + n], int elem)
{
    // start look from the element we are trying to delete
    for (int j = elem; j < (max_users-1);j++)
        for (int i = 0; i < max_books_per_user + n; i++)
        {
            string element1 = arr[j + 1][i];
            arr[j][i] = element1; // shift userid in subsequent index to current inde
            if (j == (max_users - 2))
                arr[j][i] = "";
        }
}
bool isEmpty(string s)
{
    // check if whatever string we are searching is empty or not
    if (s.compare("") == 0)
        return true;
    else
        return false;
}
void tokenize(string usr[][max_books_per_user + n], string s, int i, string del = ",")
{
    int start = 0, j = 0;
    int end = s.find(del); // find position of the charcter we have used for spliting
    while (end != -1) // loop until we have reached end of string
    {                                               
        usr[i][j] = s.substr(start, end - start); // extract parts of string
        j++;// change the column we are inputting the string to
        start = end + del.size(); // extract next part
        end = s.find(del, start); // search position for next part of string splitter
    }
    usr[i][j] = s.substr(start, end - start);
}
void tokenize_books(string books[][book_columns], string b, int i, string del = ",")
{
    int start = 0, j = 0;
    int end = b.find(del); // find position of the charcter we have used for spliting
    // loop until we have reached end of string
    while (end != -1)
    {
        // extract parts of string
        books[i][j] = b.substr(start, end - start);
        j++;// change the column we are inputting the string to
        start = end + del.size(); // extract next part
        end = b.find(del, start); // search position for next part of string splitter
    }
    books[i][j] = b.substr(start, end - start);
}
int has_book(string bks[][book_columns], string bk_to_find)
{

    for (int i = 0; i < max_books; i++) // check if item is found or not
    {
        string book = bks[i][0]; // store the book we are searching from
        for_each(book.begin(), book.end(), [](char& c) {
            c = toupper(c);});
        for_each(bk_to_find.begin(), bk_to_find.end(), [](char& c) {  // we are converting to lowercase to make search case insensitive
            c = toupper(c);});
        int x = (book).compare(bk_to_find); // We are checking comparision here

        if (x == 0)
            return i;
    }
    return not_found;
}
bool user_has_book(string bks[][book_columns], string bk_to_find)
{
     for (int i = 0; i < max_books; i++) // check if item is found or not
    {
        string book = bks[i][0]; // store the book we are searching from
        for_each(book.begin(), book.end(), [](char& c) {
            c = toupper(c);});
        for_each(bk_to_find.begin(), bk_to_find.end(), [](char& c) {  // we are converting to lowercase to make search case insensitive
            c = toupper(c);});
        int x = (book).compare(bk_to_find); // We are checking comparision here

        if (isEmpty(bks[i][2]))
            return false;
    }
    return true;
}
int isFreeSlot(string usr[][max_books_per_user + n], int books = 0)
{
    for (int i = 0; i < max_users; i++)
        if (isEmpty(usr[i][books]))
            return i;
    return not_found;
}
int check_user(string usr[][max_books_per_user + n], string user_to_find, int check)
{
    // check if user exists
    if (check == by_id)
    {
        for (int i = 0; i < max_users; i++)
        {
            string user = usr[i][0];
            if (user.compare(user_to_find) == 0)
                return i;
        }
    }
    else if (check == by_name)
    {
        for (int i = 0; i < max_users; i++)
        {
            string user = usr[i][1];
            if (user.compare(user_to_find) == 0)
                return i;

        }
    }
    return not_found;

}
string isValidUser(bool do_ignore)
{
cout << "Enter the Student's ID: ";
    string user; // check if user is entering ID of valid lenght
    if(do_ignore)
        cin.ignore();
    do
    {
        
        getline(cin, user);
        if(!is_number(user))
            cout << "Student ID can only be a positive integer of 7 digits! Please re-enter: ";
    } while (!is_number(user));
    return user;
}
int get_book_count(string user[][max_books_per_user + n], string usr)
{
    int user_index = check_user(user, usr, by_id), count_books = 0;
    if (user_index != not_found)
    {
        for (int j = 2; j < (max_books_per_user + n); j++)
            if (!isEmpty(user[user_index][j])) count_books++;
            else
            break;
        return count_books;
    }
    else
        cout << "The student has no books";
        return not_found;
}
void sort_array(string user[][max_books_per_user + n])
{


    for (int j = max_users; j >= 1; j--) {

        for (int i = 0;i < j-1;i++)
        {
            bool flag = false;
            if (user[i][0].compare(user[i + 1][0]) > 0)
                flag = true;
            for (int k = 0; k < (max_books_per_user+n);k++)
            {
                if (flag) 
                {
                    string temp = user[i][k];
                    user[i][k] = user[i + 1][k];
                    user[i + 1][k] = temp;
                }
            }

        }

    }
}
void update_usr_file(string users[][max_books_per_user + n], fstream& usr_file)
{

    std::remove("user.csv");
    usr_file.open("user1.csv", ios::out);
    if (!usr_file.is_open())
    {
        cout << "The file does not exist!\n\n";
    }
    else
    {
        // if file exists
        for (int i = 0; i < max_users; i++)
        {
            for (int j = 0; j < (max_books_per_user + n); j++)
            {
                if (!isEmpty(users[i][j]))
                {
                    usr_file << users[i][j] << ",";
                }
            }
            usr_file << endl;
        }
        usr_file.close();
        std::rename("user1.csv", "user.csv");
    }
}
void update_bk_file(string bks[][book_columns], fstream& bk_file)
{
    std::remove("books.csv");
    bk_file.open("book1.csv", ios::out);
    if (!bk_file.is_open())
        cout << "The file does not exist!\n\n";
    else
    {
        // if file exists
        for (int i = 0; i < max_books; i++)
        {
            for (int j = 0; j < book_columns; j++)
                if (!isEmpty(bks[i][j]))
                    bk_file << bks[i][j] << ",";
            bk_file << endl;
        }
        bk_file.close();
        std::rename("book1.csv", "books.csv");
    }
}
int user_book_index(string users[][max_books_per_user + n], string book, int user_index)
{
    for (int j = 2; j < max_books_per_user + n; j++)
    {
        string user_book = users[user_index][j]; // store the book we are searching from
        for_each(user_book.begin(), user_book.end(), [](char& c) {
            c = toupper(c);});


        // we are converting to lowercase to make search case insensitive
        for_each(book.begin(), book.end(), [](char& c) {
            c = toupper(c);});

        // We are checking comparsion here
        int x = (user_book).compare(book);
        if (x == 0)
        {
            return j;
        }
    }
    return not_found;
}
void update_books(string users[][max_books_per_user + n], string books[][book_columns], int u, int b, int operation)
{
    // get the index of the book 
    // at the index i
    switch (operation)
    {
    case loan:
    {
        books[b][2] = users[u][1];
        books[b][1] = "Unavailable";
        break;
    }
    case returnBook:
        {books[b][1] = "Available  ";
        books[b][2] = "";
        int usr_bk_index = user_book_index(users, books[b][0], u);
        users[u][usr_bk_index] = "";
        break;}
    case return_books_by_user:
        {
            int book_count = get_book_count(users, users[u][0]);
        for(int j = 2; j < (2+book_count); j++)
        {
            int book_index = has_book(books, users[u][j]);
            books[book_index][1] = "Available  ";
            books[book_index][2] = "";
        }
        cout << "\n" << users[u][1] << " has returned the book: " << "\"" << books[b][0] << "\"\n\n";
        // check the user books and compare with books array
        // if same update books[b][1] =" Available" books[b][2] = ""
        break;}
    }
}
void initializeArrays(string users[][max_books_per_user+n], string books[][book_columns], fstream &user_file, fstream &book_file)
{
    string usr_file_input, book_file_input;
     // Enter the data from user file to user array
    user_file.open("user.csv", ios::in);

    if (!user_file) // check if user file exists or not
        cout << "The Student file does not exist.";
    else
        for (int count = 0; user_file && count < max_users; count++) // enter data if user file exists and number of users does not exceed the limit
            // take input from file and splits the file data into strings seperated by ','
            if (getline(user_file, usr_file_input))
                tokenize(users, usr_file_input, count, ",");
    // free up memory from file
    user_file.close();

    book_file.open("books.csv", ios::in);
    // Take input from book file
    if (!book_file) // check if book file exists fileor not
        cout << "The book file does not exist.";
    else
    {
        for (int count = 0; book_file && count < max_books; count++)
            // take input from file and splits the file data into strings seperated by ','
            if (getline(book_file, book_file_input))
                tokenize_books(books, book_file_input, count, ",");
    }
    book_file.close();
}

