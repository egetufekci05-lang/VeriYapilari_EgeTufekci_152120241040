#include <iostream>
#include <string>

using namespace std;


struct Song {
    string title;
    string artist;
    int ratings[3];
    Song *next;
    Song *prev;
};

class Playlist {
private:
    Song *head;
    Song *tail;
    Song *current;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }


    void addSong(string title, string artist, int r1, int r2, int r3) {
        Song *newSong = new Song();
        newSong->title = title;
        newSong->artist = artist;
        newSong->ratings[0] = r1;
        newSong->ratings[1] = r2;
        newSong->ratings[2] = r3;
        newSong->next = nullptr;
        newSong->prev = nullptr;

        if (head == nullptr) {

            head = tail = current = newSong;
        } else {

            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }


    void nextSong() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
            cout << "Sonraki sarki secildi: " << current->title << endl;
        } else {
            cout << "Listenin sonundasiniz!" << endl;
        }
    }


    void prevSong() {
        if (current != nullptr && current->prev != nullptr) {
            current = current->prev;
            cout << "Onceki sarki secildi: " << current->title << endl;
        } else {
            cout << "Listenin basindasiniz!" << endl;
        }
    }


    void removeCurrent() {
        if (current == nullptr) return;

        Song *toDelete = current;


        if (toDelete->prev != nullptr)
            toDelete->prev->next = toDelete->next;
        else
            head = toDelete->next;

        if (toDelete->next != nullptr)
            toDelete->next->prev = toDelete->prev;
        else
            tail = toDelete->prev;


        if (toDelete->next != nullptr)
            current = toDelete->next;
        else
            current = head;

        delete toDelete;
        cout << "Sarki listeden kaldirildi." << endl;
    }


    void display() {
        if (head == nullptr) {
            cout << "Liste bos!" << endl;
            return;
        }

        Song *temp = head;
        cout << "\n--- Calma Listesi ---\n";
        while (temp != nullptr) {

            if (temp == current)
                cout << "-> ";
            else
                cout << "   ";

            cout << "Baslik: " << temp->title << " | Sanatci: " << temp->artist << " | Puanlar: ";


            for (int i = 0; i < 3; i++) {
                cout << temp->ratings[i] << (i < 2 ? ", " : "");
            }
            cout << endl;

            temp = temp->next;
        }
        cout << "---------------------\n";
    }
};

int main() {
    Playlist myList;


    myList.addSong("1", "a", 10, 9, 10);
    myList.addSong("2", "b", 8, 7, 9);
    myList.addSong("3", "c", 6, 8, 7);

    myList.display();

    myList.nextSong();
    myList.display();

    myList.removeCurrent();
    myList.display();

    return 0;
}
