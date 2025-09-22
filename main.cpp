//Subject: LDCW6123 - FUNDAMENTALS OF DIGITAL COMPETENCE FOR PROGRAMMER
//Topic: Spotify
//Title program: Music Recommendation Assistant
//Inputs: Music preference
//Outputs: A suggested music title and its artist
//Outputs: A database chart for songs and genres
//Added list of Genres available
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;

struct Song {
    string title;
    string artist;
    vector<string> genres;
    int year;
    float popularity; // Added popularity rating (0.0-10.0)
};

// Expanded music database
vector<Song> musicList = {
    {"Gemuruh", "Faizal Tahir", {"rock", "pop"}, 2007, 8.5},
    {"Shape of You", "Ed Sheeran", {"pop"}, 2017, 9.2},
    {"Bohemian Rhapsody", "Queen", {"rock", "opera"}, 1975, 9.8},
    {"Blinding Lights", "The Weeknd", {"rnb", "synth-pop"}, 2019, 9.1},
    {"Hotel California", "Eagles", {"rock", "classic rock"}, 1976, 9.5},
    {"Feel Good Inc.", "Gorillaz", {"alternative", "hip-hop"}, 2005, 9.0},
    {"Stairway to Heaven", "Led Zeppelin", {"rock", "hard rock"}, 1971, 9.7},
    {"Old Town Road", "Lil Nas X", {"country", "hip-hop"}, 2019, 8.9},
    {"Best Part", "Daniel Caesar ft. H.E.R.", {"rnb", "soul"}, 2017, 9.3},
    {"Romantic Homicide", "d4vd", {"indie", "bedroom pop"}, 2022, 8.6},
    {"Golden", "Jill Scott", {"rnb", "neo-soul"}, 2000, 9.0},
    {"She's My Collar", "Gorillaz", {"alternative", "synth-pop"}, 2017, 8.8},
    {"Thunderstruck", "AC/DC", {"rock", "hard rock"}, 1990, 9.1},
    {"Come Through and Chill", "Miguel ft. J. Cole", {"rnb", "hip-hop"}, 2017, 8.6},
    {"Here With Me", "d4vd", {"indie", "alt-pop"}, 2022, 8.4},
    {"Dare", "Gorillaz", {"electronic", "dance"}, 2005, 8.7},
    {"Adorn", "Miguel", {"rnb", "pop"}, 2012, 9.2},
    {"Silent Running", "Gorillaz", {"alternative", "electronic"}, 2020, 8.5},
    {"Boo'd Up", "Ella Mai", {"rnb", "contemporary"}, 2018, 8.5},
    {"Sleep Well", "d4vd", {"indie", "bedroom pop"}, 2023, 8.3}
};

vector<Song> getMusicList() {
    return musicList;
}

// Convert string to lowercase for case-insensitive comparison
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Check if song contains the specified genre
bool hasGenre(const Song& song, const string& genre) {
    string lowerGenre = toLowerCase(genre);
    for (const string& songGenre : song.genres) {
        if (toLowerCase(songGenre) == lowerGenre) {
            return true;
        }
    }
    return false;
}

// Recommend song based on user preference (genre)
bool recommendByGenre(const string preference, Song& result) {
    vector<Song> matchingSongs;
    
    // Find all songs that match the genre
    for (const Song& song : musicList) {
        if (hasGenre(song, preference)) {
            matchingSongs.push_back(song);
        }
    }
    
    if (matchingSongs.empty()) {
        return false;
    }
    
    // Sort by popularity and return the most popular
    sort(matchingSongs.begin(), matchingSongs.end(), 
         [](const Song& a, const Song& b) {
             return a.popularity > b.popularity;
         });
    
    result = matchingSongs[0];
    return true;
}

// Recommend newest release song
bool showNewestRelease(Song& result) {
    if (musicList.empty()) {
        return false;
    }
    
    // Find the song with the latest year
    Song newestSong = musicList[0];
    for (const Song& song : musicList) {
        if (song.year > newestSong.year || 
           (song.year == newestSong.year && song.popularity > newestSong.popularity)) {
            newestSong = song;
        }
    }
    
    result = newestSong;
    return true;
}

// Random recommend a song
bool todayRecommend(Song& result) {
    if (musicList.empty()) {
        return false;
    }
    
    // Use current time as seed for random generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, musicList.size() - 1);
    
    int randomIndex = distribution(generator);
    result = musicList[randomIndex];
    return true;
}

// Enhanced result display with more information
void checkResult(const bool found, const Song& result) {
    if (found) {
        cout << "\n" << string(50, '=') << endl;
        cout << "🎵 RECOMMENDED SONG 🎵" << endl;
        cout << string(50, '=') << endl;
        cout << "Title: " << result.title << endl;
        cout << "Artist: " << result.artist << endl;
        cout << "Year: " << result.year << endl;
        cout << "Rating: " << fixed << setprecision(1) << result.popularity << "/10.0" << endl;
        cout << "Genres: ";
        for (size_t i = 0; i < result.genres.size(); i++) {
            cout << result.genres[i];
            if (i < result.genres.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << string(50, '=') << endl;
    } else {
        cout << "\n❌ No songs found matching your criteria." << endl;
        cout << "Try a different genre like: rock, pop, hip-hop, country, etc." << endl;
    }
    cout << endl;
}

// Display available genres
void showAvailableGenres() {
    cout << "\n📋 Available Genres:" << endl;
    cout << "rock, pop, rnb, hip-hop, country, alternative, indie, soul, " << endl;
    cout << "ballad, hard rock, classic rock, electronic, dance, bedroom pop, alt-pop, synth-pop" << endl;
    cout << endl;
}

// Display program statistics
void showStats() {
    cout << "\n📊 Music Database Statistics:" << endl;
    cout << "Total songs: " << musicList.size() << endl;
    
    // Count genres
    vector<string> allGenres;
    for (const Song& song : musicList) {
        for (const string& genre : song.genres) {
            allGenres.push_back(genre);
        }
    }
    
    // Get unique genres count
    sort(allGenres.begin(), allGenres.end());
    allGenres.erase(unique(allGenres.begin(), allGenres.end()), allGenres.end());
    cout << "Available genres: " << allGenres.size() << endl;
    
    // Find year range
    int minYear = musicList[0].year, maxYear = musicList[0].year;
    for (const Song& song : musicList) {
        minYear = min(minYear, song.year);
        maxYear = max(maxYear, song.year);
    }
    cout << "Year range: " << minYear << " - " << maxYear << endl;
    cout << endl;
}

int main() {
    cout << "🎵 === SPOTIFY MUSIC RECOMMENDATION ASSISTANT === 🎵" << endl;
    cout << "Welcome to your personal music discovery experience!" << endl;
    
    int choice;
    Song result;
    bool found = false;
    
    do {
        cout << "\n" << string(60, '-') << endl;
        cout << "🎯 RECOMMENDATION OPTIONS:" << endl;
        cout << "1. 🎸 Recommend by Genre" << endl;
        cout << "2. 🆕 Show Newest Releases" << endl;
        cout << "3. 🎲 Today's Random Pick" << endl;
        cout << "4. 📋 Show Available Genres" << endl;
        cout << "5. 📊 Database Statistics" << endl;
        cout << "0. 👋 Exit" << endl;
        cout << string(60, '-') << endl;
        cout << "Enter your choice (0-5): ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                string preference;
                cout << "\n🎸 Enter your preferred music genre: ";
                cin >> preference;
                found = recommendByGenre(preference, result);
                checkResult(found, result);
                if (!found) {
                    showAvailableGenres();
                }
                break;
            }
            case 2: {
                found = showNewestRelease(result);
                cout << "\n🆕 Here's the newest release in our database:";
                checkResult(found, result);
                break;
            }
            case 3: {
                found = todayRecommend(result);
                cout << "\n🎲 Your random song of the day:";
                checkResult(found, result);
                break;
            }
            case 4: {
                showAvailableGenres();
                break;
            }
            case 5: {
                showStats();
                break;
            }
            case 0: {
                cout << "\n🎵 Thank you for using Spotify Music Recommendation Assistant!" << endl;
                cout << "Keep discovering great music! Goodbye! 🎶" << endl;
                break;
            }
            default: {
                cout << "\n❌ Invalid input!" << endl;
                cout << "Please enter a number between 0 and 5." << endl << endl;
                break;
            }
        }
    } while (choice != 0);
    
    return 0;
}
