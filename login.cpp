#include <bits/stdc++.h>
using namespace std;

int arr[100];

class User
{
public:
    string name;
    string address;
    string email;
    string pass;
    bool chk = false;

    void sign_up()
    {
        ofstream outfile;
        outfile.open("user.txt", ios::out | ios::app);
        cout << "Enter your name: ";
        cin >> name;
        outfile << "Name: " << name << "\n";
        cout << "\nEnter your email: ";
        cin >> email;
        outfile << "Email: " << email << "\n";
        cout << "\nEnter your password: ";
        cin >> pass;
        outfile << "Password: " << pass << "\n";
        cout << "\nEnter your address: ";
        cin >> address;
        cout << endl;
        outfile << "Address: " << address << "\n\n\n";
    }

    void sign_in()
    {
        cout << "Please enter your email:\n";
        cin >> email;
        cout << "\nPlease enter your password:\n";
        cin >> pass;
        Check();
    }

    void Check()
    {
        fstream fin;
        fin.open("user.txt", ios::in);
        string line;

        string chk1 = "Email: " + email;
        string chk2 = "Password: " + pass;

        bool c1 = false, c2 = false;

        while (fin)
        {
            getline(fin, line);

            if (c1 == false and line == chk1)
                c1 = true;

            if (c2 == false and chk2 == line)
                c2 = true;

            if (c1 and c2)
            {
                chk = true;
                break;
            }
        }

        int choose;

        if (!chk)
        {
            cout << "Your password or email is wrong or you haven't registered.\nPlease re-enter or register::\n";
            cout << "Press 1 for register\nPress 2 for resubmission\n";
            cin >> choose;
            if (choose == 1)
                sign_up();
            else
                sign_in();
        }
        else
            return;
    }
};

class movie
{
public:
    vector<string> v;

    void getData()
    {
        fstream input;
        input.open("movieList.txt", ios::in);
        string line;

        while (input)
        {
            getline(input, line);
            v.push_back(line);
        }
    }

    void show()
    {
        for (int i = 0; i < v.size(); i++)
            cout << v[i] << endl;
    }
};

class theater : public movie
{
public:
    int v8[100], v1[100], v5[100];

    theater()
    {
        for (int i; i < 100; i++)
        {
            v8[i] = 0;
            v5[i] = 0;
            v1[i] = 0;
        }
    }
};

class TIME : public theater
{
public:
    int noob = 0;
    int seats;

    bool Check(int, theater &, int);
    void DisplaySeats(theater &, int);
    void BookSeats(theater &, int);

    void timet()
    {
        theater();
        cout << "show time:\n1. 8:00am\n2. 1:00pm\n3. 5:00pm" << endl;
        cout << "Choose your show time : ";
        int x;
        cin >> x;

        theater t1, t2, t3;
        cout << "\nEnter the number of seats you want: ";
        cin >> seats;

        theater *selectedTheater = nullptr;

        if (x == 1)
        {
            if (Check(seats, t1, x))
                selectedTheater = &t1;
            else if (Check(seats, t2, x))
                selectedTheater = &t2;
            else if (Check(seats, t3, x))
                selectedTheater = &t3;
            else
            {
                noob = 1;
                cout << "In 8:00am no seats are available" << endl;
                return;
            }
        }
        else if (x == 2)
        {
            if (Check(seats, t1, x))
                selectedTheater = &t1;
            else if (Check(seats, t2, x))
                selectedTheater = &t2;
            else if (Check(seats, t3, x))
                selectedTheater = &t3;
            else
            {
                noob = 1;
                cout << "In 1:00pm no seats are available" << endl;
                return;
            }
        }
        else if (x == 3)
        {
            if (Check(seats, t1, x))
                selectedTheater = &t1;
            else if (Check(seats, t2, x))
                selectedTheater = &t2;
            else if (Check(seats, t3, x))
                selectedTheater = &t3;
            else
            {
                noob = 1;
                cout << "In 5:00pm no seats are available" << endl;
                return;
            }
        }

        if (selectedTheater != nullptr)
        {
            DisplaySeats(*selectedTheater, x);
            BookSeats(*selectedTheater, x);
        }
    }
};

bool TIME::Check(int cnt, theater &t, int x)
{
    int *seatsArray = (x == 1) ? t.v8 : (x == 2) ? t.v1
                                                 : t.v5;

    int availableSeats = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (seatsArray[i] == 0)
            availableSeats++;
        if (availableSeats >= cnt)
            return true;
    }

    return false;
}

void TIME::DisplaySeats(theater &t, int x)
{
    int *seatsArray = (x == 1) ? t.v8 : (x == 2) ? t.v1
                                                 : t.v5;

    cout << "Available seats are: " << endl;
    for (int i = 1; i <= 100; i++)
    {
        if (seatsArray[i] == 0)
            cout << i << "A ";
        else
            cout << i << "X ";
        if (i % 10 == 0)
            cout << endl;
    }
}

void TIME::BookSeats(theater &t, int x)
{
    int *seatsArray = (x == 1) ? t.v8 : (x == 2) ? t.v1
                                                 : t.v5;

    for (int i = 0; i < seats; i++)
    {
        int seatNumber;
        do
        {
            seatNumber = rand() % 100 + 1;
        } while (seatsArray[seatNumber] != 0);
        arr[i] = seatNumber;
        seatsArray[seatNumber] = 1;
    }
}

class ticket : public TIME, public User
{
public:
    int no;

    void buy(int no)
    {
        cout << "For movie no " << no << " the available ";
        timet();

        if (noob == 0)
        {
            cout << "\n\nPrice of ticket :" << seats * 300 << "tk" << endl;
            cout << "\nYour seats are: \n";

            for (int i = 0; i < seats; i++)
                cout << arr[i] << " ";

            cout << "\n\nConfirm purchase?\nY/N" << endl;
            char q;
            cin >> q;

            if (q == 'Y')
                cout << "Your ticket is purchased" << endl;
        }
    }

    void booking(int no)
    {
        cout << "For movie no " << no << " the available ";
        timet();

        if (noob == 0)
        {
            cout << "\nYour seats are: \n";
            for (int i = 0; i < seats; i++)
                cout << arr[i] << " ";

            cout << "\n\nConfirm booking?\nY/N" << endl;
            char q;
            cin >> q;

            if (q == 'Y')
                cout << "Your ticket is booked" << endl;
        }
    }

    void available()
    {
        cout << "Available movies are\n\n";
        getData();
        show();
        cout << "\nWhich movie do you want to watch?\nEnter the serial number: ";
        cin >> no;
        cout << "\n\n1 For buy ticket\n2 For booking " << endl;
        int x;
        cin >> x;

        if (x == 1)
            buy(no);
        else
            booking(no);
    }
};

int main()
{
    ticket TKT;
    cout << "\t\t\t\t\t __________________________________________" << endl;
    cout << "\t\t\t\t\t|                                          |" << endl;
    cout << "\t\t\t\t\t|       Welcome to TheaterTrack            |" << endl;
    cout << "\t\t\t\t\t|__________________________________________|" << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\tDo you have an account?" << endl;
    cout << "\t\t\t\t\t\tY/N" << endl;
    char x;
    cin >> x;

    if (x == 'Y')
        TKT.sign_in();

    else
        TKT.sign_up();

    movie mo;

    while (1)
    {
        cout << "\t\t\t\t\t __________________________________________" << endl;
        cout << "\t\t\t\t\t|                                          |" << endl;
        cout << "\t\t\t\t\t|       Welcome to TheaterTrack            |" << endl;
        cout << "\t\t\t\t\t|__________________________________________|" << endl
             << endl
             << endl;
        cout << "\t\t\t\t\t\tPlease choose your option:" << endl;
        cout << "\t\t\t\t\t\t1.Check all movies" << endl;
        cout << "\t\t\t\t\t\t2.Purchase tickets" << endl;
        cout << "\t\t\t\t\t\t3.Exit" << endl;
        int m;
        cin >> m;

        if (m == 1)
        {
            mo.getData();
            mo.show();
            cout << "\nDo you want to go back to the homepage?" << endl;
            cout << "Y/N" << endl;
            cin >> x;

            if (x == 'Y')
                continue;

            else
            {
                cout << "Thanks for visiting";
                break;
            }
        }

        else if (m == 2)
        {
            TKT.available();
            cout << "\nDo you want to go back to the homepage?" << endl;
            cout << "Y/N" << endl;
            cin >> x;

            if (x == 'Y')
                continue;

            else
            {
                cout << "Thanks for visiting";
                break;
            }
        }

        else
        {
            cout << "Thanks for visiting";
            return 0;
        }
    }
}
