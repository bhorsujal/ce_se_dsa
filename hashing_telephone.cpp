// Author: Sujal Bhor (21210)

#include <iostream>
#include <string>
using namespace std;

struct Client
{
    string name;
    long long teleNumber;

    Client(string name = "", long long tele = 0)
    {
        this->name = name;
        this->teleNumber = tele;
    }

    bool isEmpty() const
    {
        return name.empty() && teleNumber == 0;
    }
};

class Hash
{
private:
    static const int tableSize = 10;
    Client table[tableSize];

    long long hashFunction(long long PhoneNum)
    {
        return (3 * PhoneNum + 5) % tableSize;
    }

    bool isOriginal(int index)
    {
        return index == hashFunction(table[index].teleNumber);
    }

    bool isFull() const
    {
        for (int i = 0; i < tableSize; ++i)
        {
            if (table[i].isEmpty())
            {
                return false; // if at least one empty
            }
        }
        return true;
    }

public:
    Hash()
    {
        for (int i = 0; i < tableSize; ++i)
        {
            table[i] = Client();
        }
    }

    void insertLPWithoutReplacement(string name, long long TeleNum)
    {
        if (isFull())
        {
            cout << "Hash table is full. Cannot insert more elements." << endl;
            return;
        }

        long long index = hashFunction(TeleNum);
        while (!table[index].isEmpty())
        {
            index = (index + 1) % tableSize;
        }
        // Found an empty space
        table[index] = Client(name, TeleNum);
    }

    void insertLPWithReplacement(string name, long long telenum)
    {
        if (isFull())
        {
            cout << "Hash table is full. Cannot insert more elements." << endl;
            return;
        }

        long long index = hashFunction(telenum);

        if (table[index].isEmpty())
        {
            table[index] = Client(name, telenum);
        }
        else
        {
            if (isOriginal(index))
            {
                while (!table[index].isEmpty())
                {
                    index = (index + 1) % tableSize;
                }
                // Found an empty space
                table[index] = Client(name, telenum);
            }
            else
            {
                Client temp = table[index];
                table[index] = Client(name, telenum);
                while (!table[index].isEmpty())
                {
                    index = (index + 1) % tableSize;
                }
                // Found an empty space
                table[index] = temp;
            }
        }
    }

    bool search(string name, long long teleNumber, int &comparisons)
    {
        long long index = hashFunction(teleNumber);
        long long originalIndex = index; // Store the original index for comparison

        while (!table[index].isEmpty())
        {
            comparisons++;
            if (table[index].name == name && table[index].teleNumber == teleNumber)
            {
                cout << "Element found at index " << index << endl;
                return true;
            }
            index = (index + 1) % tableSize;
            // If we have cycled back to the original index, it means the element is not found
            if (index == originalIndex)
            {
                break;
            }
        }
        cout << "Element not found" << endl;
        return false;
    }

    void printTable() const
    {
        for (int i = 0; i < tableSize; ++i)
        {
            if (!table[i].isEmpty())
            {
                cout << "Index " << i << ": " << table[i].name << " --> " << table[i].teleNumber << endl;
            }
            else
            {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }
};

int main()
{
    Hash h;
    int choice;
    string name;
    long long teleNumber;
    int comparisons;

    do
    {
        cout << "\nHash Table Operations:" << endl;
        cout << "1. Insert with Replacement" << endl;
        cout << "2. Insert without Replacement" << endl;
        cout << "3. Search" << endl;
        cout << "4. Print Table" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter telephone number: ";
            cin >> teleNumber;
            h.insertLPWithReplacement(name, teleNumber);
            break;
        case 2:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter telephone number: ";
            cin >> teleNumber;
            h.insertLPWithoutReplacement(name, teleNumber);
            break;
        case 3:
            cout << "Enter name to search: ";
            cin >> name;
            cout << "Enter telephone number to search: ";
            cin >> teleNumber;
            comparisons = 0;
            h.search(name, teleNumber, comparisons);
            cout << "Number of comparisons: " << comparisons << endl;
            break;
        case 4:
            cout << "Hash Table Contents:" << endl;
            h.printTable();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}
