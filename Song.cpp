/*  Adrian Balbuena
 *  Section 9
 *  Assignment #4
 *  Due: November 13, 2018
 */

#include "Song.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

Song::Song() {
    /*
     default values for title, artist, type, and duration;
     */
    strcpy(title, " ");
    strcpy(artist, " ");
    type = COUNTRY;
    duration = 0;
}

void Song::set(const char *t, const char *a, Genre g, int d) {
    /*
     sets values for previously blank values: title, artist, type, and duration.
     */
    strcpy(title, t);
    strcpy(artist, a);
    //You can't assign to an array, only copy to it.
    type = g;
    duration = d;
}

const char* Song::getTitle() const {
    /*
     returns the variable title from song.h
     */
    return title;
}

const char* Song::getArtist() const {
    /*
     returns the variable artist from song.h
     */
    return artist;
}

int Song::getDuration() const {
    /*
     returns the variable duration from song.h
     */
    return duration;
}

Genre Song::getGenre() const {
    /*
     returns the genre type from song.h
     */
    return type;
}

void Song::display() const {
    cout << setw(41) << left;
    cout << title;
    cout << setw(26);
    cout << artist;
    cout << setw(10);
    /*
     cout << type;
     does not print out i.e "Country" but instead i.e '0';
     if statement to cout necessary genre type;
     */
    if (type == COUNTRY) {
        cout << "Country";
    }
    else if (type == EDM) {
        cout << "EDM";
    }
    else if (type == POP) {
        cout << "Pop";
    }
    else if (type == ROCK) {
        cout << "Rock";
    }
    else if (type == RB) {
        cout << "R&B";
    }
    cout << duration/60 << ":";
    if (duration%60 < 10) {
        cout << "0";
    }
    cout << duration%60 << endl;
}


