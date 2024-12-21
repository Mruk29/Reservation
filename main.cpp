#include <bits/stdc++.h>
using namespace std;

// Base class
class client {
public:
    static int c_id_count;
    int cost_cnt;
    char c_type;

    virtual void check() {
        fstream fin;
        fin.open("client.csv", ios::in);
        if (!fin.is_open()) {
            cout << "Unable to open client.csv file." << endl;
            return;
        }

        int target_phn, phn, count = 0;
        cout << "Enter the phone number of the client to display details: ";
        cin >> target_phn;
        vector<string> row;
        string line, word;

        while (getline(fin, line)) {
            row.clear();
            stringstream s(line);
            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            if (row.size() >= 3) {
                phn = stoi(row[2]);
                if (target_phn == phn) {
                    count = 1;
                    cout << "Client ID: " << row[0] << "\n";
                    cout << "Name: " << row[1] << "\n";
                    cout << "Phone No: " << row[2] << "\n";
                    cout << "Address: " << row[3] << "\n";
                    cout << "NID: " << row[4] << "\n";
                    break;
                }
            }
        }

        if (count == 0) {
            cout << "Record not found\n";
        }

        fin.close();
    }

    virtual int update() {
        fstream fout;
        fout.open("client.csv", ios::out | ios::app);
        if (!fout.is_open()) {
            cout << "Unable to open client.csv file." << endl;
            return 0;
        }

        int c_id;
        string c_name, c_phone_no, c_address, c_nid;
        cout << "Enter Client ID: ";
        cin >> c_id;
        cout << "Enter Client Name: ";
        cin >> c_name;
        cout << "Enter Client Phone No: ";
        cin >> c_phone_no;
        cout << "Enter Client Address: ";
        cin >> c_address;
        cout << "Enter Client NID: ";
        cin >> c_nid;

        fout << c_id << "," << c_name << "," << c_phone_no << "," << c_address << "," << c_nid << "\n";
        fout.close();

        return c_id;
    }
};

class client_hotelroom : virtual public client {
public:
    void check() {
        ifstream inf("hotelroom.txt");
        if (!inf.is_open()) {
            cout << "Unable to open hotelroom file." << endl;
            return;
        }

        int room_id;
        string room_type, room_book;
        cout << "Available hotel rooms to book: \n";

        while (inf >> room_id >> room_type >> room_book) {
            if (room_book == "NULL") {
                cout << room_id << " " << room_type << endl;
            }
        }

        inf.close();
    }

    int update() {
        int target_room_id, c_id;
        cout << "Please enter the required room id: ";
        cin >> target_room_id;
        cout << "Please enter the client id: ";
        cin >> c_id;

        string client_id = to_string(c_id);
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");

        if (!inf.is_open() || !outf.is_open()) {
            cout << "Unable to open hotelroom files." << endl;
            return 0;
        }

        int room_id;
        string room_type, room_book;
        bool room_found = false;

        while (inf >> room_id >> room_type >> room_book) {
            if (room_id == target_room_id && room_book == "NULL") {
                outf << room_id << " " << room_type << " " << client_id << "\n";
                cost_cnt += 1000;
                room_found = true;
            } else {
                outf << room_id << " " << room_type << " " << room_book << "\n";
            }
        }

        if (!room_found) {
            cout << "Room not available for booking." << endl;
        }

        outf.close();
        inf.close();

        remove("hotelroom.txt");
        rename("hotelroom1.txt", "hotelroom.txt");

        return cost_cnt;
    }
};

// Similar corrections should be applied to other derived classes and methods as required.

// Main function
int main() {
    client *bptr;
    client c1;
    client_hotelroom h1;
    int t;

    while (true) {
        cout << "\nType 1 to search for a client id\nType 2 to create a client id\nType 0 to end: ";
        cin >> t;

        bptr = &c1;

        if (t == 1) {
            bptr->check();
        } else if (t == 2) {
            bptr->update();
        } else if (t == 0) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }

        cout << "\nType 1 to book a hotel room\nType 0 to end: ";
        cin >> t;

        if (t == 1) {
            bptr = &h1;
            bptr->check();
            cout << "\nType 1 to book, Type 0 to cancel: ";
            cin >> t;
            if (t == 1) {
                bptr->update();
            }
        } else if (t == 0) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
