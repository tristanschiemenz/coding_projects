#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

string shuffle_single_word(string inword) {
    if (inword.size() > 2) {
        random_shuffle(inword.begin() + 1, inword.end() - 1);
    }
    return inword;
}

void shuffelFile(std::ifstream &file) {
    if (!file.is_open()) {
        cerr << "Unable to open the file 'input.txt'." << std::endl;
        return;
    }

    std::string line, processedLine;
    while (getline(file, line)) {
        processedLine.clear();  // Reset for each line

        size_t pos = 0;
        while (pos < line.size()) {
            size_t start = line.find_first_not_of(" ,.", pos);
            size_t end = line.find_first_of(" ,.", start);

            if (start == std::string::npos) break;

            if (end == std::string::npos) {
                end = line.size();
            }

            string word = line.substr(start, end - start);
            processedLine += shuffle_single_word(word);

            // If there's a delimiter, append it to the processed line
            if (end < line.size()) {
                processedLine += line[end];
            }

            pos = end + 1;
        }

        cout << processedLine << std::endl;  // Print the processed line
    }
    file.close();
}
string sorted_middle(const string& word) {
    if (word.size() <= 2) return "";
    string middle = word.substr(1, word.size() - 2);
    sort(middle.begin(), middle.end());
    return middle;
}

// Load the wordlist into a multimap.
multimap<string, string> load_wordlist(const string& filename) {
    ifstream file(filename);
    multimap<string, string> wordlist;
    string word;

    while (file >> word) {
        wordlist.insert({sorted_middle(word), word});
    }

    return wordlist;
}

string restore_word(const multimap<string, string>& wordlist, const string& shuffledWord) {
    auto range = wordlist.equal_range(sorted_middle(shuffledWord));
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.front() == shuffledWord.front() && it->second.back() == shuffledWord.back()) {
            return it->second;  // Return the matched original word.
        }
    }
    return shuffledWord;  // If no match is found, return the shuffled word as-is.
}

string restore_text(const multimap<string, string>& wordlist, const string& shuffledText) {
    istringstream iss(shuffledText);
    string word, restoredText;
    while (iss >> word) {
        restoredText += restore_word(wordlist, word) + " ";
    }
    return restoredText;
}

int main() {
    std::ifstream file("input.txt");
    // shuffelFile(file);

    auto wordlist = load_wordlist("woerterliste.txt");  // Assuming wordlist filename is wordlist.txt

    string shuffledText = "Der Twsit Eigsnclh tiwst = Duenrhg, Venurdrehg war ein Mdaotenz im 4/4-Tkat, der in den frhüen 1960er Jearhn populär wrude und zu Rcok'n'Roll, Ryhthm and Bleus oedr sielezpler Twsit-Msuik gnzteat wrid.";
    cout << restore_text(wordlist, shuffledText) << endl;

    return 0;
}

