#include "helpers.h"

void printuser(string user[][max_books_per_user + n])
{
    // Create the Headers before outputting
    cout << setw(10) << "Student ID" << setw(23) << "Names" << setw(50) << "Books Owned" << endl;
    cout << setw(85) << setfill('_') << "\n\n"; // Create headers before outputting

    for (int i = 0; i < max_users; i++)
    {
        int book_count = get_book_count(user, user[i][0]);
        cout << setfill(' ') << setw(10) << user[i][0] << setw(25) << user[i][1];
        if (!isEmpty(user[i][0]))
        {
            for (int j = 2; j < (2 + book_count); j++)
            {
                if (j == 2)
                    cout << setw(50);
                if (j < (book_count + 2) && !isEmpty(user[i][j]))
                    cout << user[i][j] << ", ";
                else
                    cout << user[i][j];
            }
        }
        cout << endl;
    }
}
void add_users(string usr[][max_books_per_user + n], fstream& user_file)
{        // removes any previous iputs in the input stream
    string user = isValidUser(true); // keep taking input from user until they enter a vvalid reg no
    cout << "Enter the name of the user: ";
    string user_name;
    getline(cin, user_name);
    int user_index = isFreeSlot(usr); // get the index where we have to add the user
    if (user_index != not_found)  // check if array is empty or not
    {

        usr[user_index][0] = user; // the first column stores the id
        usr[user_index][1] = user_name;
        sort_array(usr); // the second stores the name
        update_usr_file(usr, user_file);  // format the user inputs before adding to file to help in survey later.
        cout << "\nThe user has successfully been added. \n\n"; // Prompt for successful operation
    }
    else
        cout << "No free slot inside the library!" << "\n\n"; // Prompt for failure
}
void delete_user(string usr[][max_books_per_user + n], string books[][book_columns], fstream& user_file, fstream& book_file)
{
    cout << "For the student you want to delete, ";
    string user = isValidUser(true);
    int user_index = check_user(usr, user, by_id); // check if user exists or not
    if (user_index != not_found) {
        update_books(usr, books, user_index, -2, return_books_by_user);
        delete_usr(usr, user_index);
        update_usr_file(usr, user_file);
        update_bk_file(books, book_file);
        cout << "\nThe student has been deleted\n\n";
    }

    else  // if not found do not add
        cout << "User being deleted does not exist!" << endl; // Prompt for failure
}
void search_book(string bks[][book_columns])
{
    cout << "Enter the book you want to search for: ";
    cin.ignore();
    string book;
    getline(cin, book);
    if (has_book(bks, book) != -1)
     cout << "Yes the book is available :D\n\n" ;
     else if (user_has_book(bks, book))
      cout << "Sorry the book is currently borrowed by someone :(\n\n";
    else
        cout << "Sorry the book is not in the library :(\n\n";

}
void printbooks(string bks[][book_columns])
{
    cout << "\nStatus" << setw(55) << "Book" << std::left << setw(62) << std::right << "Owner(if any)\n";
    cout << setw(125) << setfill('_') << "\n\n"; // Create headers before outputting
    for (int i = 0; i < max_books; i++)
    {
        if (isEmpty(bks[i][0]))
            break;
        cout << setfill(' ') << bks[i][1] << setw(50) << bks[i][0] << setw(60) << std::right << bks[i][2] << endl;
    }
}
void return_book(string users[][max_books_per_user + n], string books[][book_columns], fstream& user_file, fstream& book_file)
{
    cout << "Enter the book you would like to return: ";
    cin.ignore();
    string book;
    getline(cin, book);
    int book_index = has_book(books, book);
    if (book_index != not_found)
    {

        int user_index = check_user(users, books[book_index][2], by_name);
        if (user_index != not_found)
        {
            update_books(users, books, user_index, book_index, returnBook);
            cout << "\nThe student with ID " << users[user_index][0] << " has returned the book " << books[book_index][0] << "\n\n";
            update_bk_file(books, book_file);
            update_usr_file(users, user_file);
            
        }
    }
    else {
        cout << "The book you entered does not exist.";
    }
}
void loan_books(string user[][max_books_per_user + n], string books[][book_columns], fstream& user_file, fstream& bk_file)
{
    cout << "Enter which book you would like to loan: ";
    cin.ignore();
    string book;
    getline(cin, book);
    int book_index = has_book(books, book);
    if (book_index == not_found)
        cout << "Book entered does not exist in the libary!\n";
    else {
        cout << "For the student that wants to loan the book, ";
        string usr = isValidUser(false);
        int user_index = check_user(user, usr, by_id);
        if (user_index == not_found)
            cout << "Student entered is not in the library!\n\n";
        else {
            bool isFreeslot = false;
            if (user_index != not_found)
                for (int j = 2; j < (max_books_per_user + n); j++)
                    if (isEmpty(user[user_index][j]))
                    {
                        isFreeslot = true;
                        user[user_index][j] = books[book_index][0];
                        update_books(user, books, user_index, book_index, loan);
                        update_bk_file(books, bk_file);
                        update_usr_file(user, user_file);
                        cout << "\nStudent has been given the book.\n\n";
                        break;
                    }
                    else
                        cout << "\nStudent does not exist!\n\n";

            if (!isFreeSlot)
                cout << "\nStudent can only have 3 books at max!\n\n";
        }
    }
}
int count_books_by_user(string users[][max_books_per_user + n])
{
    string user = isValidUser(true);
    cout << "\nThe student has " << get_book_count(users, user) << " books.\n\n";
    return get_book_count(users, user);
}
