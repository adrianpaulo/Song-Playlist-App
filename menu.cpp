/* Adrian Balbuena
 * Section 9
 * Assignment #4
 * Due: November 13, 2018 */

#include "Playlist.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    Playlist p1;

    char titleAdd[41];
    char artistAdd[26];
    char typeAddTemp;
    Genre typeAdd = COUNTRY;
    int durationAdd;

    char titleOrArtist[41];
    char nameGiven[41];

    char newPlaylistTitle[21] = { '\0' };
    char menuSelection = 'M';
    bool incorrectInput;
    bool incorrectInputRename;

    cout << "*** Welcome to Spotify-ish ***" << endl;
    cout << "Please input the name for your playlist: ";

    //do while statement to ask user for correct title
    do {
        cin.getline(newPlaylistTitle, 21);
        if (isspace(newPlaylistTitle[0])) {
            cout << "Invalid playlist name. Please re-enter: ";
            incorrectInput = true;
        }
        else {
            p1.updatePlayListTitle(newPlaylistTitle);
            incorrectInput = false;
        }
    }while (incorrectInput);

    cout << endl;

    //Display the main program menu
    cout << "\nA: Add a song to the playlist" << endl;
    cout << "F: Find a song in the playlist" << endl;
    cout << "R: Rename playlist" << endl;
    cout << "S: Remove a song" << endl;
    cout << "D: Display the playlist" << endl;
    cout << "G: Genre summary" << endl;
    cout << "M: Show this Menu" << endl;
    cout << "Q: Quit/exit the program" << endl;

    bool valid = true;
    do {
    cout << "> " ;
    cin >> menuSelection;
    cout << endl;

    cin.ignore();

    if (menuSelection == 'A' || menuSelection == 'a') {
        /*
         Allows the user to add a song to his/her playlist...
         Asks the user for the song's title, artist, genre, and duration.
         */
        cout << "Enter title: ";
        cin.getline(titleAdd, 41);
        cout << "Enter author: ";
        cin.getline(artistAdd, 26);
        bool genreInvalid;
        cout << "Enter Genre - (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B: ";
        do {
            genreInvalid = true;
        cin >> typeAddTemp;

        if (typeAddTemp == 'C' || typeAddTemp == 'c')
            typeAdd = COUNTRY;
        else if (typeAddTemp == 'E' || typeAddTemp == 'e')
            typeAdd = EDM;
        else if (typeAddTemp == 'P' || typeAddTemp == 'p')
            typeAdd = POP;
        else if (typeAddTemp == 'R' || typeAddTemp == 'r')
            typeAdd = ROCK;
        else if (typeAddTemp == 'B' || typeAddTemp == 'b')
            typeAdd = RB;
        else {
            cout << "Invalid genre entry. Please re-enter: ";
            genreInvalid = false;
            }
        } while (!genreInvalid);

        cout << "Enter the duration of the song (in seconds): ";

        bool durationInvalid;
        do {
            cin >> durationAdd;
            if (durationAdd <= 0) {
                cout << "Must enter a positive duration. Please re-enter: ";
                durationInvalid = true;
            }
            else {
                durationInvalid = false;
            }
        } while(durationInvalid);

        //Playlist member function that takes in all these parameters
        //then adds to listOfSongs

        p1.addSong(titleAdd, artistAdd, typeAdd, durationAdd);

        if (p1.getCurrentSize() == p1.getMaxSize()) {
            //when all slots are filled, size needs to grow
            p1.grow();
            cout << "** Array being resized to <" << p1.getMaxSize() << "> allocated slots" << endl;
        }
    }
    else if (menuSelection == 'F' || menuSelection == 'f') {
        /*
         Allows the user to search his/her playlist of a song...
         given the song's title or artist
         */
        cout << "Please enter the Title/Artist to search (up to 40 characters): ";
        cin.getline(titleOrArtist, 41);

        int countFind = 0;

        for (int i = 0; i < p1.getCurrentSize(); i++) {
            int index = p1.lookup(titleOrArtist, i);
            if (index >= 0) {
                if (countFind == 0) {
                    cout << "The following songs match your search:" << endl;
                    cout << "~ ";
                }
                p1.getlistOfSongs(index).display();
                countFind++;
            }
        }
        if (countFind == 0) {
            /*
             if countFind == 0; that means that index was never 0 or greater...
             */
            cout << "No songs found" << endl;
        }
    }
    else if (menuSelection == 'R' || menuSelection == 'r') {
        /*
         Allow the user to rename his/her playlist...
         */

        cout << "Please enter a new playlist name (up to 20 characters): ";
        do {
            cin.getline(newPlaylistTitle, 21);
            if (isspace(newPlaylistTitle[0])) {
                //(error check for empty spaces)
                cout << "Invalid playlist name. Please re-enter: ";
                incorrectInputRename = true;
            }
            else {
                p1.updatePlayListTitle(newPlaylistTitle);
                incorrectInputRename = false;
            }
        }while (incorrectInputRename);
    }
    else if (menuSelection == 'S' || menuSelection == 's') {
        /*
         Allows the user to remove a song from his/her playlist...
         by asking for the song's name.
         */
        int tempSize = p1.getCurrentSize();
        cout << "Please enter the song to remove (up to 40 characters): ";
        cin.getline(nameGiven, 41);
        p1.remove(nameGiven);

        if (tempSize == p1.getCurrentSize()) {
            /*
             If the size prior to the remove function was called is the same as the size...
             after it was called, that means that no song was removed.
             */
            cout << "No songs removed from " << p1.getPlaylistTitle() << endl;
        }
    }
    else if (menuSelection == 'D' || menuSelection == 'd') {
        /*
         Displays to the user the songs in his/her playlist
         */
        if (p1.getCurrentSize() > 0) {
            cout << setw(41) << left << "Song" << setw(26) << "Artist" << setw(10) << "Genre";
            cout << setw(10) << "Duration" << endl;
            for (int i = 0; i < 85; i++) {
                cout << "-";
                if (i == 84) {
                    cout << endl;
                }
            }
            if (p1.getCurrentSize() <= 0) {
                cout << "The playlist <" << p1.getPlaylistTitle() << "> is empty" << endl;
            }
            else
                p1.displayPlaylist();

            cout << "Number of songs: " << p1.getCurrentSize() << endl;
            cout << "Total duration: " << p1.getPlaylistDuration()/60 << ":";
            if (p1.getPlaylistDuration()%60 < 10) {
                /*
                 print '0' because it was only printing out a single if mod < 10;
                 */
                cout << "0";
            }
            cout << p1.getPlaylistDuration()%60 << endl;
        }
        else {
            cout << "The Playlist <" << p1.getPlaylistTitle() << "> is empty" << endl;
        }
    }
    else if (menuSelection == 'G' || menuSelection == 'g') {
        /*
         Displays to the the user the songs in his/her playlist...
         under the genre of their choosings
         */
        char temp = 'C';
        Genre genreSearch = COUNTRY;
        int count = 0;
        bool genreInvalid = false;
        do {
            cout << "Enter Genre - (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B: ";
            cin >> temp;

            if (temp == 'C' || temp == 'c')
                genreSearch = COUNTRY;
            else if (temp == 'E' || temp == 'e')
                genreSearch = EDM;
            else if (temp == 'P' || temp == 'p')
                genreSearch = POP;
            else if (temp == 'R' || temp == 'r')
                genreSearch = ROCK;
            else if (temp == 'B' || temp == 'b')
                genreSearch = RB;
            else {
                cout << "Invalid genre entry. Please re-enter: ";
                genreInvalid = true;
            }
        } while (genreInvalid);

        for (int i = 0; i < p1.getCurrentSize(); i++) {
            if (p1.getlistOfSongs(i).getGenre() == genreSearch) {
                count++;
                if (count == 1) {
                    cout << setw(41) << left << "Song" << setw(26) << "Artist" << setw(10) << "Genre";
                    cout << setw(10) << "Duration" << endl;
                    for (int i = 0; i < 85; i++) {
                        cout << "-";
                        if (i == 84) {
                            cout << endl;
                        }
                    }
                }
                p1.getlistOfSongs(i).display();
            }
        }
        if (count == 0) {
            cout << "The playlist <" << p1.getPlaylistTitle() << "> is empty" << endl;
        }
    }
    else if (menuSelection == 'M' || menuSelection == 'm') {
        //re-Displays the main program menu
        cout << "\nA: Add a song to the playlist" << endl;
        cout << "F: Find a song in the playlist" << endl;
        cout << "R: Rename playlist" << endl;
        cout << "S: Remove a song" << endl;
        cout << "D: Display the playlist" << endl;
        cout << "G: Genre summary" << endl;
        cout << "M: Show this Menu" << endl;
        cout << "Q: Quit/exit the program" << endl;
    }
    else if (menuSelection == 'Q' || menuSelection == 'q') {
        /*
         Quits the program and the loop...
         Displaying the playlist information to the user upon doing so
         */
        if (p1.getCurrentSize() > 0) {
            cout << setw(41) << left << "Song" << setw(26) << "Artist" << setw(10) << "Genre";
            cout << setw(10) << "Duration" << endl;
            for (int i = 0; i < 85; i++) {
                cout << "-";
                if (i == 84) {
                    cout << endl;
                }
            }
            if (p1.getCurrentSize() <= 0) {
                cout << "The playlist <" << p1.getPlaylistTitle() << "> is empty" << endl;
            }
            else
                p1.displayPlaylist();

            cout << "Number of songs: " << p1.getCurrentSize() << endl;
            cout << "Total duration: " << p1.getPlaylistDuration()/60 << ":";
            if (p1.getPlaylistDuration()%60 < 10) {
                /*
                 print '0' because it was only printing out a single if mod < 10;
                 */
                cout << "0";
            }
            cout << p1.getPlaylistDuration()%60 << endl;
        }
        else {
            if (p1.getCurrentSize() <= 0) {
                cout << "The playlist <" << p1.getPlaylistTitle() << "> is empty" << endl;
            }
            else
                p1.displayPlaylist();
        }

        cout << "\n";
        cout << "Exiting Program. Your playlist was " << p1.getCurrentSize() << " songs long.";
        cout << endl;
        valid = false;
    }
    else {
        //error checking for invalid char
        cout << "Not a valid option, choose again." << endl;
    }

    } while (valid);

    return 0;
}