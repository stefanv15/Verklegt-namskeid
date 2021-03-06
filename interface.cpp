#include "interface.h"
#include "person.h"
#include <ctype.h>

Interface::Interface()
{

}

void Interface::programInfo() const
{
    cout << "**************************************************" << endl;
    cout << "*                    WELCOME                     *" << endl;
    cout << "*  This program allows you to store info about   *" << endl;
    cout << "*  the most common computer scientists, search   *" << endl;
    cout << "*  and sort your list.                           *" << endl;
    cout << "*                                                *" << endl;
    cout << "**************************************************" << endl;

}

void Interface::pickOption()
{
    cout << endl;
    cout << "1 - Add computer scientist." << endl;
    cout << "2 - Show list." << endl;
    cout << "3 - Exit." << endl;
}

Person Interface::getPersoninfo()
{
    string name;
    string gender;
    int dayOfBirth;
    int dayOfDeath;

    cin.ignore();

    cout << "Name of computer scientist: ";
    getline(cin, name);
    cout << "Gender (f/m): ";
    cin >> gender;
    cout << "Enter year of birth (yyyy): ";
    cin >> dayOfBirth;
    cout << "Year of passing (yyyy, Type -1 if scientist is alive): ";
    cin >> dayOfDeath;

    return Person(name, gender, dayOfBirth, dayOfDeath);
}

void Interface::printList(vector<Person> listOfPersons)
{
    cout << endl;
    cout << "LIST OF COMPUTER SCIENTISTS" << endl;
    cout << "---------------------------" << endl;
    for(unsigned int i = 0; i < listOfPersons.size(); i++)
    {
        cout << "Name: " << listOfPersons[i].getName() << endl;
        cout << "Gender: " << (listOfPersons[i].getGender()=="m"?"Male":"Female") << endl;
        cout << "Born: " << listOfPersons[i].getDayOfBirth() << endl;
        if (listOfPersons[i].getDayOfDeath() > 0)
            cout << "Died: " << listOfPersons[i].getDayOfDeath() << endl;
        cout << "---------------------------" << endl;
    }
    cout << "push 4 to search!!!!!!!" << endl;
}

char Interface::askToSort()
{
    char answer;
    cout << "Do you want to sort the list? (y/n)" << endl;
    cin >> answer;

    if(answer == 'y')
        printSorted();

    return answer;
}

void Interface::start()
{
    programInfo();     // welcome note.

    int numb;

    while(true)
    {
        pickOption();

        cin >> numb;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(100,'\n');
        }

        //Error message
        if(numb < 1 || numb > 4)

        {
            cout << "The input you entered is not a valid option. Pick again!" << endl;
        }

        switch(numb)
        {
            case 1:
            {
                Person p = getPersoninfo(); //sækja upplýsingar um persónu.
                m_worker.createPerson(p);   //býr til eintak af persónu.
                break;
            }
            case 2:
            {
                vector<Person> list = m_worker.getList(); // Sækja lista.
                printList(list);
                askToSort();

                break;
            }
            case 3:
            {
                m_worker.saveAllData(); // Geymum öll gögn áður en forriti er lokað.
                return;
            }
            case 4:
            {
                string search;

                cout << "Enter search word: ";
                cin >> search;

                vector<Person> searchlist = m_worker.searchScientist(search); //
                printList(searchlist);

            }
       }
     }
}

void Interface::printSorted()
{
    vector<Person>listOfPersons = m_worker.sortList(m_worker.getList());
    printList(listOfPersons);
}
