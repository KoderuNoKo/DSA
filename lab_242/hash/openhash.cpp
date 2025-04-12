#include <iostream>

using namespace std;

int hashFunction(int key, int capacity) {
    return key % capacity;
}

template<class K, class V>
class XHashMap {
public:
    class Entry {
    public:
        K key;
        V value;
        Entry* next;

        Entry(K key, V value, Entry* next = 0) {
            this->key = key;
            this->value = value;
            this->next = next;
        }
    };

private:
    Entry** table; // hash table
    int capacity; // size for the hash table
    int count;

public:
    // Constructor
    XHashMap() {
        this->capacity = 10;
        this->count = 0;
        table = new Entry * [capacity];
        //reset table to 0
        for (int i = 0; i < capacity; i++) {
            table[i] = 0;
        }
    }

    ~XHashMap() { // Destructor
        //Remove all entries in the current map
        for (int idx = 0; idx < this->capacity; idx++) {
            Entry* entry = this->table[idx];
            while (entry != 0) {
                Entry* next = entry->next;
                delete entry;
                entry = next;
            }
        }
        //Remove table
        delete[]table;
    }

    void put(int key, int value) {
        //TODO: Compute the index using the hash function
        int idx = hashFunction(key, this->capacity);

        //TODO: Check if the key exists in the linked list at the index, update if found
        Entry* row = this->table[idx];
        while (row) {
            if (row->key == key) {
                row->value = value;
                return;
            }
            row = row->next;
        }

        //TODO: If the key doesn't exist, create and insert a new entry
        this->table[idx] = new Entry(key, value, this->table[idx]);

        //TODO: Increment the count and ensure load factor by resizing if needed
        this->ensureLoadFactor(this->count + 1);
        this->count++;
    }

    void ensureLoadFactor(int current_size) {
        //TODO: Calculate the maximum allowed size based on the load factor (0.75 * capacity)
        int maxload = 0.75 * this->capacity - 1;

        //TODO: If the current size exceeds or equals the max allowed size, trigger rehashing
        if (current_size > maxload) {
            //TODO: Calculate the new capacity (1.5 times the old capacity)
            int newcap = 1.5 * this->capacity;

            //TODO: Call the rehash function with the new capacity
            this->rehash(newcap);
        }
    }

    void rehash(int newCapacity) {
        //TODO: Store the current table and capacity
        Entry** tempTable = this->table;
        int tempcap = this->capacity;

        //TODO: Create a new table with the new capacity and update the capacity
        this->table = new Entry * [newCapacity];
        this->capacity = newCapacity;

        //TODO: Initialize the new table with nullptr values
        for (int i = 0; i < this->capacity; i++) {
            this->table[i] = nullptr;
        }

        //TODO: For each index in the old table:
        //      - Traverse the linked list at that index
        //      - Recompute the new index for each entry using the new capacity
        //      - Insert the entry into the new table at the recomputed index
        for (int i = 0; i < tempcap; i++) {
            Entry* oldrow = tempTable[i];
            while (oldrow) {
                int idx = hashFunction(oldrow->key, this->capacity);
                this->table[idx] = new Entry(oldrow->key, oldrow->value, this->table[idx]);
                oldrow = oldrow->next;
            }
        }

        //TODO: Delete all entries in the old table by traversing each linked list and deleting nodes
        for (int i = 0; i < tempcap; i++) {
            Entry* row = tempTable[i];
            Entry* temp = nullptr;
            while (row) {
                temp = row;
                row = row->next;
                delete temp;
            }
            tempTable[i] = nullptr;
        }


        //TODO: Delete the old table array
        delete[] tempTable;
    }


    // print table method (for testing)
    void printTable() const {

        cout << "------------The hash table is shown below------------\n";
        for (int i = 0; i < capacity; i++) {
            Entry* entry = table[i];
            cout << "Index " << i << ": ";
            while (entry != 0) {
                cout << "(" << entry->key << ", " << entry->value << ") ";
                entry = entry->next;
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------\n";

    }

};

int main()
{
    XHashMap<int, int> map;
    map.put(112, 545);
    map.put(790, 999);
    map.put(350, 432);
    map.put(678, 805);
    map.put(432, 217);
    map.put(883, 374);
    map.put(112, 596);
    map.put(926, 314);
    map.put(240, 890);
    map.put(432, 410);
    map.printTable();
}