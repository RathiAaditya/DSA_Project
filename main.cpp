#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;
class PhoneBook
{
private:
    map<int, string> m;
    map<int, int> mexist;
    map<string, vector<int>> mp;
    string name;
    int number;

public:
    void printChoices()
    {
        cout << "Press 1 for Entering new Contact in the list" << endl;
        cout << "Press 2 for Deleting  a Contact from the list" << endl;
        cout << "Press 3 for Editing a Contact name" << endl;
        cout << "Press 4 for Displaying all the contacts" << endl;
    }
    int TakeInput()
    {
        cout << "Enter your choice " << endl;
        int k;
        cin >> k;
        return k;
    }
    void EnterContact()
    {
        cout << "Enter the name :" << endl;
        cin >> name;
        cout << "Enter the Phone Number :" << endl;
        cin >> number; // validate the phone number using regex and check if it already exists
        // bool f=false for regex
        if (mexist[number] == 1)
        {
            cout << "This contact number is already taken by:" << m[number] << endl;
        }
        else if (name == "*")
        {
            cout << "You cannot save your contact using this name please try some other name" << endl;
        }
        // else if regex condition
        else
        {
            mexist[number] = 1;
            m[number] = name;
            mp[name].pb(number);
            cout << "Contact has been saved " << endl;
        }
    }
    void DeleteContact()
    {
        int x, z;
        string y;
        cout << "Enter 1 for delete by name " << endl;
        cout << "Enter 2 for delete by number" << endl;
        cin >> x;
        if (x == 1)
        {
        l1:
            cin >> y;
            if (mp[y].size() == 0)
            {
                cout << "Please check whether you have entered your name correctly" << endl;
                goto l1;
            }
            else if (mp[y].size() == 1)
            {
                cout << "Deleting contact" << endl;
                int p = mp[y].back();
                mp[y].pop_back();
                m[p] = "*";
                mexist[p] = 0;
            }
            else
            {
                cout << "Multiple contact numbers with this name exist " << endl;
                cout << "Please specify the value which you want to delete " << endl;
                int j = 1;
                for (auto i : mp[y])
                {
                    cout << j << " " << i << endl;
                    j++;
                }
                j--;
            l2:
                cout << "Enter the index for the number you want to delete " << endl;
                int k;
                cin >> k;
                if (k > j)
                {
                    cout << "Please Enter a valid index for deleting" << endl;
                    goto l2;
                }
                if (k == j)
                {
                    cout << "Deleting the contact " << endl;
                    mp[y].erase(mp[y].end());
                    // delete operation to be written
                }
                else if (k == 1)
                {
                    cout << "Deleting Contact " << endl;
                    mp[y].erase(mp[y].begin());
                }
                else
                {
                    for (int g = k - 1; g < mp[y].size() - 1; g++)
                    {
                        mp[y][g] = mp[y][g + 1];
                    }
                    mp[y].pop_back();
                    cout << "Deleting Contact" << endl;
                }
            }
        }
        else if (x == 2)
        {
        l7:
            cout << "Enter the number you want to delete " << endl;
            cin >> z;
            if (mexist[z] == 0)
            {
                cout << "Please Enter a contact number which is there in the phonebook " << endl;
                goto l7;
            }
            mexist[z] = 0;
            string s = m[z];
            m[z] = "*";
            int j = 1;
            for (auto i : mp[s])
            {
                if (mp[s][j] == z)
                    break;
                else
                    j++;
            }
            int k = mp[s].size();
            if (k == j)
            {
                cout << "Deleting the contact " << endl;
                mp[s].erase(mp[s].end());
                // delete operation to be written
            }
            else if (k == 1)
            {
                cout << "Deleting Contact " << endl;
                mp[s].erase(mp[s].begin());
            }
            else
            {
                for (int g = k - 1; g < mp[y].size() - 1; g++)
                {
                    mp[s][g] = mp[y][g + 1];
                }
                mp[s].pop_back();
                cout << "Deleting Contact" << endl;
            }
            // have to delete from mp
        }
        else
        {
            cout << "Please Enter only 1 or 2 " << endl;
            DeleteContact();
        }
    }

    void DisplayContact()
    {
        for (auto i : m)
        {
            if (i.second != "*")
            {
                cout << "Name:" << i.second << " "
                     << " Number:" << i.first << endl;
            }
        }
        cout << endl;
    }
    void EditContact()
    {
    l5:
        int x;
        cout << "Enter 1 to edit by name" << endl;
        cout << "Enter 2 to edit by number" << endl;
        cin >> x;
        if (x == 1)
        {
        l4:
            string y;
            cout << "Please Enter the name of the person" << endl;
            cin >> y;
            if (mp[y].size() == 0)
            {
                cout << "Please enter a valid string " << endl;
                goto l4;
            }
            int j = 1;
            for (auto i : mp[y])
            {
                cout << j << " " << i << endl;
                j++;
            }
            j--;
            int index;
            cout << "Enter the index of the contact you want to edit" << endl;
            cin >> index;
            int pnum = mp[y][index - 1];
            mexist[pnum] = 0;
            m[pnum] = '*';
            cout << "Enter new phone number" << endl; // have to validate this using regex
        l8:
            int nnum;
            cin >> nnum;
            if (mexist[nnum] == 1)
            {
                cout << "This phone number is already in use by " << m[nnum] << endl;
                cout << "Please kindly enter a valid contact number" << endl;
                goto l8;
            }
            mexist[nnum] = 1;
            mp[y][index - 1] = nnum;
            m[nnum] = y;

            // again take input index from user then delete function
            // also do mexist[this numbe r]=0 and m[number]='*'

            // or even instead of delete function take input number from user and just
            // replace the previous number with this new num -->followed this approach
        }
        else if (x == 2)
        {
            cout << "Enter the contact number" << endl;
            int phnum;
        l3:
            cin >> phnum;
            if (mexist[phnum] == 0)
            {
                cout << "Please Enter valid Contact number: " << endl;
                goto l3;
            }
            string z = m[phnum];
            // delete number from the string int mapping have to write a delete function for this
            string y;
            cout << "Enter the new name " << endl;
            cin >> y;
            m[phnum] = y;
            mp[y].pb(phnum);
        }
        else
        {
            cout << "Please Enter 1 or 2 only " << endl;
            goto l5;
        }
    }
};

void solve()
{
    PhoneBook pbk;
    int num;
    // First taking input from a text file then from user
    bool choice = true;
    while (choice)
    {
        pbk.printChoices();
        num = pbk.TakeInput(); // this is for choice 1
        switch (num)
        {
        case 1:
            pbk.EnterContact();
            break;
        case 2:
            pbk.DeleteContact();
            break;
        case 3:
            pbk.EditContact();
            break;
        case 4:
            pbk.DisplayContact();
            break;
        }
    }
}
int32_t main()
{
    solve();
    return 0;
}
