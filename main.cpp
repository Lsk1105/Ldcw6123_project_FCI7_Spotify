//Subject: LDCW6123 - FUNDAMENTALS OF DIGITAL COMPETENCE FOR PROGRAMMER
//Topic: Spotify
//Title program: Music Recommendation Assistant
//Inputs: Music preference
//Outputs: A suggested music title and its artist
#include <iostream>
#include <vector>
using namespace std;

struct Song {
    string title;
    string artist;
    vector<string> genres;
    int year;
};

vector<Song> musicList = {
    {"Gemuruh", "Faizal Tahir", {"rock","pop"}, 2007},
    {"Shape of You", "Ed Sheeran", {"pop"}, 2017}
};

vector<Song> getMusicList()
{
    return musicList;
};

// Recommend song based on user preference
bool recommendByGenre(const string preference, Song result)
{
    return true;
};

// Recommend newest release song
bool showNewestRelease(Song result)
{
    return true;
};

// Random recommend a song
bool todayRecommend(Song result)
{
    return true;
};

void checkResult(const bool found, const Song result)
{
    if (found)
        cout << "\nRecommended Song:\n"
             << result.title << " (" << result.year <<")"<< " by " << result.artist << endl;
    else
        cout << "No songs found."<< endl;

    cout << endl;
}

int main() {

    cout << "=== Spotify Music Recommendation Assistant ===" << endl;

    int choice;
    Song result;
    bool found = false;

    result = {"Gemuruh", "Faizal Tahir", {"rock","pop"}, 2007};
    do
    {
        cout << "Options:\n"
         << "1. Recommend by genres\n"
         << "2. Show newest releases (by year)\n"
         << "3. Spotify's Today Recommend \n"
         << "0. Exit\n\n";

        cin >> choice;

        if (choice == 1)
        {
            string preference;
            cout << "\nEnter your music preference (genre): \n";
            cin >> preference;

            found = recommendByGenre(preference,result);
            checkResult(found,result);
        }
        else if (choice == 2)
        {
            found = showNewestRelease(result);
            checkResult(found,result);
        }
        else if (choice == 3)
        {
            found = todayRecommend(result);
            checkResult(found,result);
        }

        else if (choice == 0)
                cout << "Good bye. See you again!"<< endl;
        else
        {
            cout << "Invalid input./n"
                 << "Please enter a number between 0 to 2./n/n";
        }

    }while (choice!=0);



    return 0;
}
