

#include <bits/stdc++.h>
#include <regex>
#define pb push_back
using namespace std;
#define SIZE 1009
const int MOD = 1e9 + 7, p = 31;
// Class to store (key,value) pair
void printChoices()
{
    cout << "Press 1 for Entering new Contact in the list" << endl;
    cout << "Press 2 for Deleting  a Contact from the list" << endl;
    cout << "Press 3 for Editing a Contact" << endl;
    cout << "Press 4 for Displaying all the contacts" << endl;
    cout << "Press 5 for Searching a Contact" << endl;
    cout << "Press 6 to exit " << endl;
}
char TakeInput()
{
    cout << "Enter your choice " << endl;
    char k;
    cin >> k;
    return k;
}
class HashNode
{
public:
    string value;
    string key;

    // Constructor of hashnode
    HashNode(string key, string value)
    {
        this->value = value;
        this->key = key;
    }
};

// Class for the map
class HashMap
{
private:
    // hash element array
    HashNode **arr;

    // current curr_size
    int curr_size;
    // sub node
    HashNode *sub;

public:
    // Constructor for HashMap
    HashMap()
    {
        // Initial SIZE of hash array
        curr_size = 0;
        arr = new HashNode *[SIZE];

        // Initialise all elements of array as NULL
        for (int i = 0; i < SIZE; i++)
            arr[i] = NULL;
        sub = new HashNode("*", "*");
        // sub node with value and key *
    }
    // hash function to find index with given key
    int hashFunc(string key)
    {
        int sum = 0;
        string s = key;
        for (int i = 0; s[i] != '\0'; i++)
        {
            sum = (sum + s[i] - '0') % MOD;
        }
        return sum % SIZE;
    }

    // int hashFunc(string s)
    // {
    //     long long int pvalue=1;
    //    long long int hashsum=0;
    //    for(int i=0;i<s.length();i++)
    //    {
    //    hashsum=(hashsum+(s[i]-'0')*pvalue)%MOD;
    //    pvalue=(pvalue*p)%MOD;
    //    }
    //    return hashsum%SIZE;
    // }
    // Function to add key value pair
    void insertContact(string key, string value)
    {
        HashNode *tmp = new HashNode(key, value);

        // Apply hash function to find index for given key
        int hIndex = hashFunc(key);

        // find next free space
        while (arr[hIndex] != NULL && arr[hIndex]->key != "*")
        {
            hIndex++;
            hIndex %= SIZE;
        }
        // if new is to be inserted size increased
        curr_size++;
        arr[hIndex] = tmp;
    }

    // Function to delete a key value pair
    string deleteContact(string key)
    {
        // Apply hash function
        int hIndex = hashFunc(key);
        int ctr = 0;
        // finding the node with given key
        while (arr[hIndex] != NULL)
        {
            if (ctr++ > SIZE)
                return "-1";
            // if node found
            if (arr[hIndex]->key == key)
            {
                HashNode *tmp = arr[hIndex];

                // Insert sub node
                arr[hIndex] = sub;

                // Reduce curr_size
                curr_size--;
                return tmp->value;
            }
            hIndex++;
            hIndex %= SIZE;
        }
        // If not found return "*"
        return "*";
    }
    // Function to update value for a given key
    string Edit(string key, string value)
    {
        int hIndex = hashFunc(key);

        int ctr = 0;

        // finding the node with given key
        while (arr[hIndex] != NULL)
        {

            if (ctr++ > SIZE)
                return "-1";

            // if node found return its value
            if (arr[hIndex]->key == key)
                arr[hIndex]->value = value;
            hIndex++;
            hIndex %= SIZE;
        }

        return "*";
    }

    // Function to search the value for a given key
    string search(string key)
    {
        // Apply hash function to find index for given key
        int hIndex = hashFunc(key);
        int ctr = 0;
        // finding the node with given key
        while (arr[hIndex] != NULL)
        {

            if (ctr++ > SIZE) // to avoid infinite loop
                return "-1";

            // if node found return its value
            if (arr[hIndex]->key == key)
                return arr[hIndex]->value;
            hIndex++;
            hIndex %= SIZE;
        }

        // If not found return "-1"
        return "-1";
    }

    // Return current curr_size
    int getSize()
    {
        return curr_size;
    }

    // Return true if curr_size is 0
    bool isEmpty()
    {
        return curr_size == 0;
    }

    // Function to display the stored key value pairs
    void display()
    {
        if (getSize() == 0)
        {
            cout << "The Phonebook is Empty!!" << endl;
        }
        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i] != NULL && arr[i]->key != "*")
                cout << "Name : " << arr[i]->value << "\t"
                     << "Number : " << arr[i]->key << endl;
        }
    }
    bool regcheck(string patt)
    {
        // regex nummob("(0|91)?[7-9][0-9]{9}");
        // regex numl("(020)?[0-9]{8}");
        // return regex_match(patt, nummob);
        return true;
    }
};
// Phonebook main class
class PhoneBook
{
private:
    string name;
    string number;
    HashMap *Phonebook = new HashMap; // Map matching contact numbers to names
    map<string, vector<string>> mp;   // Map matching names to their contact numbers

public:
    // Constructor for PhoneBook class
    PhoneBook()
    {
        name = "\0";
        number = "\0";
    }
    int getSize()
    {
        return Phonebook->getSize();
    }

    // Function to enter a new contact in the Phonebook
    void EnterContact()
    {
        if (SIZE == Phonebook->getSize())
        {
            cout << "Please delete contact if you want to enter more " << endl;
            return;
        }
        cout << "Enter the name :" << endl;
        getline(cin >> ws, name);
        cout << "Enter the Phone Number :" << endl;
    l1:
        cin >> number;
        if (!Phonebook->regcheck(number))
        {
            cout << "Not a valid number." << endl;
            cout << "Please enter a valid number" << endl;
            goto l1;
        }
        // Checking for duplicate phone number entry
        if (Phonebook->search(number) != "-1")
        {
            cout << "Number is already registered to: " << Phonebook->search(number) << endl;
            cout << "Please enter another number: " << endl;
            goto l1;
        }
        mp[name].pb(number);
        Phonebook->insertContact(number, name);
        if (Phonebook->getSize() == SIZE)
        {
            cout << "WARNING: The phonebook is out of space " << endl;
            cout << endl;
        }
    }
    // Function to delete existing contacts
    void DeleteContact()
    {
        if (Phonebook->getSize() == 0)
        {
            cout << "The Phonebook directory is empty" << endl;
            cout << "You cannot edit any contacts " << endl;
            cout << endl;
            return;
        }
        string num;
        string newname;
        int x;
        cout << "Enter 1 to delete by name" << endl;
        cout << "Enter 2 to delete by number" << endl;
        cin >> x;
        if (x == 1)
        {
        l2:
            string y;
            cout << "Please Enter the name of the person" << endl;

            getline(cin >> ws, y);

            if (y.length() == 0)
            {
                cout << y << endl;
                cout << "Please enter a valid string fuck" << endl;
                goto l2;
            }
            if (mp[y].size() == 0)
            {
                cout << "The name is not in the phonebook directory" << endl;
                mp.erase(y);
                goto l2;
            }

            if (mp[y].size() == 1)
            {
                string pnum = mp[y][0];
                string k = Phonebook->deleteContact(pnum); // the return type of the function is string
                cout << "You deleted contact of person" << k << endl;
                cout << endl;
                mp[y].pop_back();
                mp.erase(y);
                cout << "The contact has been deleted successfully" << endl;
            }
            else
            {
                int index, j = 1;
                for (auto i : mp[y])
                {
                    cout << j << " " << i << endl;
                    j++;
                }
                j--;
                cout << "Enter the index of the contact you want to delete " << endl;
            l3:
                cin >> index;
                if (index > mp[y].size() or index < 1)
                {
                    cout << "Please enter a valid index" << endl;
                    goto l3;
                }
                string pnum = mp[y][index - 1];

                cout << "You deleted Contact number of person " << Phonebook->deleteContact(pnum) << endl;
                cout << endl;
                j = 0;
                for (auto i : mp[y])
                {
                    if (i == pnum)
                        break;
                    else
                        j++;
                }
                int k = mp[y].size();
                if (k == 1 or k - 1 == j)
                {
                    mp[y].pop_back();
                    if (k == 1)
                    {
                        mp.erase(y);
                    }
                }
                else
                {
                    for (int g = j; g < k - 1; g++)
                    {
                        mp[y][g] = mp[y][g + 1];
                    }
                    mp[y].pop_back();
                }
            }
        }

        else if (x == 2)
        {
            cout << "Enter the contact number" << endl;

        l4:
            string phnum;
            cin >> phnum;
            if (Phonebook->search(phnum) == "-1")
            {
                cout << "This phone number is not in the directory" << endl;
                cout << "Please kindly enter a valid contact number" << endl;
                goto l4;
            }
            string p = Phonebook->search(phnum);
            cout << "You deleted the contact of person " << Phonebook->deleteContact(phnum) << endl;

            int j = 0;
            for (auto i : mp[p])
            {
                if (i == phnum)
                    break;
                else
                    j++;
            }
            int k = mp[p].size();
            if (k == 1 or k - 1 == j)
            {
                mp[p].pop_back();
            }
            else
            {
                for (int g = j; g < k - 1; g++)
                {
                    mp[p][g] = mp[p][g + 1];
                }
                mp[p].pop_back();
            }
        }
        else
        {
            cout << "Please Enter only 1 or 2 " << endl;
            DeleteContact();
        }
        cout << "Delete Successful!" << endl;
    }
    // Function to display the PhoneBook
    void DisplayContact()
    {
        Phonebook->display();
        cout << endl;
    }
    // Function to update fields in the PhoneBook
    void EditContact()
    {
        if (Phonebook->getSize() == 0)
        {
            cout << "The Phonebook directory is empty" << endl;
            cout << "You cannot edit any contacts " << endl;
            cout << endl;
            return;
        }
        string num;
        string newname;
        int x;
        cout << "Enter 1 to edit by name" << endl;
        cout << "Enter 2 to edit by number" << endl;
        cin >> x;

        if (x == 1)
        {
        l5:
            string y;
            cout << "Please Enter the name of the person" << endl;
            getline(cin >> ws, y);

            if (y.length() == 0)
            {
                cout << "Please enter a valid string " << endl;
                goto l5;
            }
            if (mp[y].size() == 0)
            {

                cout << "The name is not in the phonebook directory" << endl;
                mp.erase(y);
                goto l5;
            }
            int j = 1;
            int index = 1;
            if (mp[y].size() > 1)
            {
                cout << "Enter the index of the contact you want to edit" << endl;
            l6:
                for (auto i : mp[y])
                {
                    cout << j << " " << i << endl;
                    j++;
                }
                j--;
                cin >> index;
                if (index > mp[y].size() or index < 1)
                {
                    cout << "Please enter a valid index" << endl;
                    goto l6;
                }
            }

            cout << "Enter new phone number" << endl;
        l7:
            string nnum;
            cin >> nnum;
            if (!Phonebook->regcheck(nnum))
            {
                cout << "Not a valid phone number" << endl;
                cout << "Please enter a valid contact number" << endl;
                goto l7;
            }
            if (nnum == mp[y][index - 1])
            {
                cout << "New number cannot be same as old number" << endl;
                cout << "Please enter a new phone number" << endl;
                goto l7;
            }
            if (Phonebook->search(nnum) != "-1")
            {
                cout << "This phone number is already in use by " << Phonebook->search(nnum) << endl;
                cout << "Please kindly enter a valid contact number" << endl;
                goto l7;
            }
            else
            {
                string pnum = mp[y][index - 1];
                Phonebook->deleteContact(pnum);
                Phonebook->insertContact(nnum, y);
                mp[y][index - 1] = nnum;
                cout << "Edit Successful!" << endl;
            }
        }
        else if (x == 2)
        {
            cout << "Enter the contact number" << endl;
        l8:
            string phnum;
            cin >> phnum;
            if (!Phonebook->regcheck(phnum))
            {
                cout << "Not a valid phone number" << endl;
                cout << "Please enter a valid contact number" << endl;
                goto l8;
            }
            if (Phonebook->search(phnum) == "-1")
            {
                cout << "This phone number is not in the directory" << endl;
                cout << "Please kindly enter a valid contact number" << endl;
                goto l8;
            }
            cout << "Enter the new name " << endl;
            string str;
            getline(cin >> ws, str);
            string p = Phonebook->search(phnum);
            Phonebook->Edit(phnum, str);

            int j = 0;
            for (auto i : mp[p])
            {
                if (i == phnum)
                    break;
                else
                    j++;
            }
            int k = mp[p].size();
            if (k == 1 or k - 1 == j)
            {
                mp[p].pop_back();
                if (k == 1)
                    mp.erase(p);
            }
            else
            {
                for (int g = j; g < k - 1; g++)
                {
                    mp[p][g] = mp[p][g + 1];
                }
                mp[p].pop_back();
            }
            mp[str].pb(phnum);
            cout << "Edit Successful!" << endl;
        }
        else
        {
            cout << "Please Enter only 1 or 2 " << endl;
            EditContact();
        }
    }
    // Function to retrieve information from the Phonebook
    void Search()
    {
        if (Phonebook->getSize() == 0)
        {
            cout << "The Phonebook directory is empty" << endl;
            cout << "You cannot search any contacts " << endl;
            cout << endl;
            return;
        }
        string num;
        string newname;
        int x;
        cout << "Enter 1 to search by name" << endl;
        cout << "Enter 2 to search by number" << endl;
        cin >> x;

        if (x == 1)
        {
        l9:
            string y;
            cout << "Please Enter the name of the person" << endl;
            getline(cin >> ws, y);

            if (y.length() == 0)
            {
                cout << "Please enter a valid string " << endl;
                goto l9;
            }
            if (mp[y].size() == 0)
            {
                cout << "The name is not in the phonebook directory" << endl;
                mp.erase(y);
                goto l9;
            }
            for (auto i : mp[y])
            {
                cout << i << endl;
            }
            cout << endl;
        }
        else if (x == 2)
        {
        l10:
            string phnum;
            cin >> phnum;
            if (Phonebook->search(phnum) == "-1")
            {
                cout << "This phone number is not in the directory" << endl;
                cout << "Please kindly enter a valid contact number" << endl;
                goto l10;
            }
            cout << "Enter the contact number" << endl;

            cout << Phonebook->search(phnum) << endl;
        }
        else
        {
            cout << "Please Enter only 1 or 2 " << endl;
            Search();
        }
    }
};
// driver code
void solve()
{
    PhoneBook pbk;
    char num;

    // bool choice = true;
    bool var = true;
    while (var)
    {

        printChoices();
        num = TakeInput(); // this is for choice 1
        switch (num)
        {
        case '1':
            pbk.EnterContact();
            break;
        case '2':
            pbk.DeleteContact();
            break;
        case '3':
            pbk.EditContact();
            break;
        case '4':
            pbk.DisplayContact();
            break;
        case '5':
            pbk.Search();
            break;
        case '6':
            var = false;
            break;
        default:
            cout << "Please Enter a valid number" << endl;
            cout << endl;
        }
    }
}

int32_t main()
{
    solve();
    return 0;
}
