// With Link Lists(one-way)
// Result Card - Using Structures
#include <iostream>
#include <string>
using namespace std;

#define MAXSUB 5        // Max Subjects

// Structure Declaration
struct myDate
{
    int dd,mm,yy;
};
struct student
{
    int rno;
    string name, fName;
    myDate DOB, DOA;
    int mks[MAXSUB], mobt;
    float perc;
    char grad;

    student* next;
};

// Function Prototypes
void readFun(student *&first);
void insertFun(student *&first);
bool searchFun(student *&first, int s);
void sortFun(student *&first);
void delFun(student *&first, int s);
void updFun(student *&first, int s);
void dispFun(student* &first);

bool isValidNum(int min, int max, int* valptr);
bool ageChecker(int* yyBptr, int* yyAptr);
bool isLeapYear(int* yearptr);
bool dateValid(myDate* dateCheckptr);

// function definitions
bool isValidNum(int min, int max, int* valptr)
{
    return ((*valptr>=min)&&(*valptr<=max));
}

bool ageChecker(int* yyBptr, int* yyAptr)
{
    return ((*yyAptr - *yyBptr) >= 17);
}

bool isLeapYear(int* yearptr) 
{
    return (*yearptr % 4 == 0 && *yearptr % 100 != 0) || (*yearptr % 400 == 0);
}

bool dateValid(myDate* dateCheckptr)
{
    if ((dateCheckptr->mm >= 1)&&(dateCheckptr->mm <= 12))
    {
        switch (dateCheckptr->mm)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            {
                if ((dateCheckptr->dd>=1)&&(dateCheckptr->dd<=31))
                    return true;
                else 
                    return false;
            }
        case 2:
            {
                if (isLeapYear(&(dateCheckptr->yy)))
                {
                    if ((dateCheckptr->dd>=1)&&(dateCheckptr->dd<=29))
                        return true;
                    else 
                        return false;
                }
                else    
                {
                    if ((dateCheckptr->dd>=1)&&(dateCheckptr->dd<=28))
                        return true;
                    else 
                        return false;
                }
            }
        case 4: case 6: case 9: case 11:  
            {
                if ((dateCheckptr->dd>=1)&&(dateCheckptr->dd<=30))
                    return true;
                else 
                    return false;
            }
        default:
            return false;
        }
    }
    else 
        return false;    
}

// Function Definitions
void readFun(student* &first)
{
    student *cur = NULL, *prev = NULL;
    char ch;
    int sum;
    int i;
    do {
        cur = new student;
        do{
            do {
                cout << "Reg#(4-digit): ";
                cin >> cur->rno;
                if (isValidNum(1000, 9999, &cur->rno))
                {
                    if(i>1)
                    {
                        if (!(searchFun(first,cur->rno)))
                            break;
                    else
                        cout<<"The Reg. Num alraedy exists...!\n";
                    }
                }
                else
                    cout<<"InValid Number.....!\n";
            } while(true);
            cout << "Name: ";
            cin.ignore(30,'\n');
            getline(cin, cur->name);

            cout << "Father Name: ";
            getline(cin, cur->fName);      
            do {
                cout<<"Enter the DOB of student:" << endl;
                do {
                    cout<<"Date: ";
                    cin>>cur->DOB.dd;
                    if (isValidNum(1,31,&cur->DOB.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Month: ";
                    cin>>cur->DOB.mm;
                    if (isValidNum(1,12,&cur->DOB.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Year: ";
                    cin>>cur->DOB.yy;
                    if (isValidNum(1000,9999,&cur->DOB.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                if (dateValid(&cur->DOB))
                    break;
                else
                {
                    cout<<"Error...Your DOB("<<cur->DOB.dd<<"."<<cur->DOB.mm<<"."<<
                        cur->DOB.yy<<") is Incorrect\n";
                }
            } while(true);

            do {
                cout<<"Enter the DOA of student:" << endl;
                do {
                    cout<<"Date: ";
                    cin>>cur->DOA.dd;
                    if (isValidNum(1,31,&cur->DOA.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Month: ";
                    cin>>cur->DOA.mm;
                    if (isValidNum(1,12,&cur->DOA.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Year: ";
                    cin>>cur->DOA.yy;
                    if (isValidNum(1000,9999,&cur->DOA.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                if (dateValid(&cur->DOA))
                    break;
                else
                {
                    cout<<"Error...Your DOA("<<cur->DOA.dd<<"."<<cur->DOA.mm<<"."<<
                        cur->DOA.yy<<") is Incorrect\n";
                }
            } while(true);

            if (!ageChecker(&cur->DOB.yy, &cur->DOA.yy))
            {
                cout<<"Admission Not possible! Student must be atleast 17 years old"<<endl;
            }
            else
                break;
        } while(true);

        sum = 0;
        cout << "Enter Marks [Max 100] of students:" << endl;
        for (int j=0; j < MAXSUB; j++)             // 5 subject marks
        {
            do {
                cout << "Enter Marks of Subject: " << j+1 << " : ";
                cin >> cur->mks[j];
                if (isValidNum(0,100,&cur->mks[j]))
                    break;
                else
                    cout<<"InValid Number.....!\n";
                } while(true);
            sum += cur->mks[j];
        }
        
        cur->mobt = sum;                      // marks obtained

        // %age calculation
        cur->perc = (cur->mobt * 100.0) / 500.0;
        // Grage Assignment
        if (cur->perc >= 80) cur->grad = 'A';
        else if (cur->perc >= 70) cur->grad = 'B';
        else if (cur->perc >= 60) cur->grad = 'C';
        else if (cur->perc >= 50) cur->grad = 'D';
        else cur->grad = 'F';
        i++;

        cur->next = NULL;

        if (first == NULL)
            first = prev = cur;
        else
        {
            prev->next = cur;
            prev = cur;
        }
        cout<<"Do you have another student(Y/N): ";
        cin>>ch;
        if(!((ch == 'Y')||(ch == 'y')))
            break;
    } while (true);
}// end of readFun

void insertFun(student *&first)
{
    int sum;
    student* nwNode = NULL, *cur = NULL, *prev = NULL;
    nwNode = new student;
    do{
        do {
            cout << "Reg#(4-digit): ";
            cin >> nwNode->rno;
            if (isValidNum(1000, 9999, &nwNode->rno))
            {
                if (!(searchFun(first,nwNode->rno)))
                    break;
                else
                    cout<<"The Reg. Num alraedy exists...!\n";
            }
            else
                cout<<"InValid Number.....!\n";
        } while(true);

        cout << "Name: ";
        cin.ignore(30,'\n');
        getline(cin, nwNode->name);

        cout << "Father Name: ";
        getline(cin, nwNode->fName);
        
        do {
            cout<<"Enter the DOB of student:" << endl;
            do {
                    cout<<"Date: ";
                    cin>>nwNode->DOB.dd;
                    if (isValidNum(1,31,&nwNode->DOB.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            do {
                    cout<<"Month: ";
                    cin>>nwNode->DOB.mm;
                    if (isValidNum(1,12,&nwNode->DOB.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            do {
                    cout<<"Year: ";
                    cin>>nwNode->DOB.yy;
                    if (isValidNum(1000,9999,&nwNode->DOB.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            if ((dateValid(&nwNode->DOB))&&(isValidNum(1000, 9999, &nwNode->DOB.yy)))
                break;
            else
            {
                cout<<"Error...Your DOB("<<nwNode->DOB.dd<<"."<<nwNode->DOB.mm<<"."<<
                    nwNode->DOB.yy<<") is Incorrect\n";
            }
        } while(true);

        do {
            cout<<"Enter the DOA of student:" << endl;
            do {
                    cout<<"Date: ";
                    cin>>nwNode->DOA.dd;
                    if (isValidNum(1,31,&nwNode->DOA.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            do {
                    cout<<"Month: ";
                    cin>>nwNode->DOA.mm;
                    if (isValidNum(1,12,&nwNode->DOA.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            do {
                    cout<<"Year: ";
                    cin>>nwNode->DOA.yy;
                    if (isValidNum(1000,9999,&nwNode->DOA.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
            if ((dateValid(&nwNode->DOA))&&(isValidNum(1000, 9999, &nwNode->DOA.yy)))
                break;
            else
            {
                cout<<"Error...Your DOA("<<nwNode->DOA.dd<<"."<<nwNode->DOA.mm<<"."<<
                    nwNode->DOA.yy<<") is Incorrect\n";
            }
        } while(true);

        if (!ageChecker(&nwNode->DOB.yy, &nwNode->DOA.yy))
        {
            cout<<"Admission Not possible! Student must be atleast 17 years old"<<endl;
        }
        else
            break;
    } while(true);

    sum = 0;
    cout << "Enter Marks [Max 100] of students:" << endl;
    for (int j=0; j < MAXSUB; j++)             // 5 subject marks
    {
        do {
            cout << "Enter Marks of Subject: " << j+1 << " : ";
            cin >> nwNode->mks[j];
            if (isValidNum(0,100,&nwNode->mks[j]))
                break;
            else
                cout<<"InValid Number.....!\n";
            } while(true);
        sum += nwNode->mks[j];
    }
        
    nwNode->mobt = sum;                      // marks obtained

    // %age calculation
    nwNode->perc = (nwNode->mobt * 100.0) / 500.0;
    // Grage Assignment
    if (nwNode->perc >= 80) nwNode->grad = 'A';
    else if (nwNode->perc >= 70) nwNode->grad = 'B';
    else if (nwNode->perc >= 60) nwNode->grad = 'C';
    else if (nwNode->perc >= 50) nwNode->grad = 'D';
    else nwNode->grad = 'F';

    nwNode->next = NULL;
    if (first == NULL) {
        first = nwNode;  // The new node becomes the first node
    }
    else if(nwNode->rno <= first->rno)
    {
        nwNode->next = first;
        first = nwNode;
    }
    else
    {
        cur = prev = first;
        while((cur != NULL)&&(cur->rno <= nwNode->rno))
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = nwNode;
        nwNode->next = cur;
    }
    cout<<"Student Inserted Successfully!"<<endl;
}// end of appFun

bool searchFun(student *&first, int s)
{
    student *cur = NULL, *prev = NULL;
    cur = first;
    while (cur != NULL) {
        if (cur->rno == s) {
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}// end of searchFun 

void sortFun(student *&first) {
    student *cur = NULL, *prev = NULL;
    if (first == NULL || first->next == NULL)
    {
        // List is empty or has only one element, no need to sort
        cout << "List is too small to sort." << endl;
    }
    else
    {
        prev = first;
        while(prev->next != NULL)
        {
            cur = prev->next;
            while(cur != NULL)
            {
                if(prev->rno > cur->rno)
                {
                    int temp = prev->rno;
                    prev->rno = cur->rno;
                    cur->rno = temp;
                }
                cur = cur->next;
            }
            prev = prev->next;
        }
        cout << "Data sorted successfully..." << endl;
    }
}// end of sortFun

void delFun(student *&first, int s)
{
    student *cur = NULL,*prev = NULL;
    cur = first;
    // If it is the first Node
    if(cur != NULL && cur->rno == s)
    {
        cur = first;
        first = first->next;
        delete cur;
        cout<<"Node deleted Successfully!"<<endl;
    }
    else
    {
        // Traversing - Searching
        while(cur != NULL && cur->rno != s)
        {
            prev = cur;
            cur = cur->next;
        }
        // in middle or at end
        if(cur != NULL)
        {
            prev->next = cur->next;
            delete cur;
            cout<<"Node deleted Successfully!"<<endl;
        }
        else 
            cout << "Student Not found in the List, can't be deleted..." << endl;
    }
}// end of delFun

void updFun(student *&first, int s)
{
    student *cur = NULL,*prev = NULL;
    cur = first;
    
    if (searchFun(cur, s))        // student found in the list
    {
        while(cur != NULL && cur->rno != s)
        {
            prev = cur;
            cur = cur->next;
        }
        cout << "OLD RECORD" << endl;
        cout << cur->rno << " - ";
        cout << cur->name << " - ";
        cout << cur->fName << " - ";
        cout << cur->DOB.dd<<"."<<cur->DOB.mm<<"."<<cur->DOB.yy<<" - ";
        cout << cur->DOA.dd<<"."<<cur->DOA.mm<<"."<<cur->DOA.yy<<" - ";
        for (int j = 0; j < MAXSUB; j++)
            cout << cur->mks[j] << " - ";
        cout << cur->mobt << " - " <<cur->perc << " - " 
             << cur->grad << endl;
        
        cout << "--------------------------------------------------" << endl;

        cout << "Now Enter New Data" << endl;
        int sum;
        do {
            cout << "Enter Data for Student Having Reg#: " << cur->rno << endl;
            cout << "Name: ";
            cin.ignore(30,'\n');
            getline(cin, cur->name);

            cout << "Father Name: ";
            getline(cin, cur->fName);        
            do {
                cout<<"Enter the DOB of student:" << endl;
                do {
                    cout<<"Date: ";
                    cin>>cur->DOB.dd;
                    if (isValidNum(1,31,&cur->DOB.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Month: ";
                    cin>>cur->DOB.mm;
                    if (isValidNum(1,12,&cur->DOB.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Year: ";
                    cin>>cur->DOB.yy;
                    if (isValidNum(1000,9999,&cur->DOB.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                if (dateValid(&cur->DOB))
                    break;
                else
                {
                    cout<<"Error...Your DOB("<<cur->DOB.dd<<"."<<cur->DOB.mm<<"."<<
                        cur->DOB.yy<<") is Incorrect\n";
                }
            } while(true);

            do {
                cout<<"Enter the DOA of student:" << endl;
                do {
                    cout<<"Date: ";
                    cin>>cur->DOA.dd;
                    if (isValidNum(1,31,&cur->DOA.dd))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Month: ";
                    cin>>cur->DOA.mm;
                    if (isValidNum(1,12,&cur->DOA.mm))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                do {
                    cout<<"Year: ";
                    cin>>cur->DOA.yy;
                    if (isValidNum(1000,9999,&cur->DOA.yy))
                        break;
                    else
                        cout<<"InValid Number.....!\n";
                } while(true);
                if (dateValid(&cur->DOA))
                    break;
                else
                {
                    cout<<"Error...Your DOA("<<cur->DOA.dd<<"."<<cur->DOA.mm<<"."<<
                        cur->DOA.yy<<") is Incorrect\n";
                }
            } while(true);

            if (!ageChecker(&cur->DOB.yy, &cur->DOA.yy))
            {
                cout<<"Admission Not possible! Student must be atleast 17 years old"<<endl;
            }
            else
                break;
        } while(true);

        sum = 0;
        cout << "Enter Marks [Max 100] of students:" << endl;
        for (int j=0; j < MAXSUB; j++)             // 5 subject marks
        {
            do {
                cout << "Enter Marks of Subject: " << j+1 << " : ";
                cin >> cur->mks[j];
                if (isValidNum(0,100,&cur->mks[j]))
                    break;
                else
                    cout<<"InValid Number.....!\n";
                } while(true);
            sum += cur->mks[j];
        }

        cur->mobt = sum;                      // marks obtained

        // %age calculation
        cur->perc = (cur->mobt * 100.0) / 500.0;
        // Grage Assignment
        if (cur->perc >= 80) cur->grad = 'A';
        else if (cur->perc >= 70) cur->grad = 'B';
        else if (cur->perc >= 60) cur->grad = 'C';
        else if (cur->perc >= 50) cur->grad = 'D';
        else cur->grad = 'F';
        
        cout << "Student's Record Updated successfully..." << endl;
    }
    else
        cout << "Student Not found in the List, can't be updated..." << endl;
}// end of updFun

void dispFun(student* &first)
{
    student* cur = first;
    while (cur != NULL)
    {
        cout << cur->rno << " - ";
        cout << cur->name << " - ";
        cout << cur->fName << " - ";
        cout << cur->DOB.dd << "."
             << cur->DOB.mm << "."
             << cur->DOB.yy << " - ";
        cout << cur->DOA.dd << "."
             << cur->DOA.mm << "."
             << cur->DOA.yy << " - ";
        for (int j = 0; j < MAXSUB; j++)
            cout << cur->mks[j] << " - ";
        cout << cur->mobt << " - " <<cur->perc << " - " 
             << cur->grad << endl;
        
        cur = cur->next;
    }
}// end of dispFun

int main() {

    //declarations    
    student* cur = NULL;
    student* prev = NULL;
    student* first = NULL;
    int sinfo;
    bool pos;
    int choice;
    
    // Menu
    do{
        cout << "**** MENU ****" << endl
            << " 1. Read & Store Data " << endl
            << " 2. Append new record " << endl
            << " 3. Search a record " << endl
            << " 4. Sort Data " << endl
            << " 5. Delete a record " << endl
            << " 6. Update a record " << endl
            << " 7. Display Result Card " << endl
            << " 8. Exit " << endl;
            
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: 
                //cout << "Read and Store the Data...\n";
                readFun(first);
                break;
            case 2: 
                // cout << "Append New Record...\n";
                insertFun(first);
                break;
            case 3:
                //cout << "Search a Record...\n";
                if (first != NULL)
                {
                    cout << "Enter Reg# of the student to be searched: ";
                    cin >> sinfo;
                    pos = searchFun( first,sinfo);
                    if (pos == false)
                        cout << "Student ID: " << sinfo << " not exists" <<endl;
                    else
                        cout << "Student ID: " << sinfo << " exists: " << endl;

                }
                else
                    cout << "First, store data using Option-1...\n";
                break;
            case 4: 
                //cout << "Sort Data with respect to reg. num...\n";
                if (first != NULL)
                {
                    sortFun(first);
                }
                 else
                    cout << "First, store data using Option-1...\n";
                break;
            case 5: 
                //cout << "Delete a Record...\n";
                if (first != NULL)
                {   cout << "Enter Reg# of the student to be deleted: ";
                    cin >> sinfo;
                    delFun(first,sinfo); 
                }
                 else
                    cout << "First, store data using Option-1...\n";    
                break;
            case 6: 
                //cout << "Update a Record...\n";
                if (first != NULL)
                {
                    cout << "Enter Reg# of the student to be updated: ";
                    cin >> sinfo;
                    updFun(first,sinfo);
                }
                 else
                    cout << "First, store data using Option-1...\n";    
                break;
            case 7: 
                //cout << "Display the Record...\n";
                if (first != NULL)
                {
                    dispFun(first);
                }
                 else
                    cout << "First, store data using Option-1...\n";    
                break;
            case 8: 
                exit(-1);
            default:
                cout << "Invalid Choice...\n";
        }// end of switch
    }while(true);
    system("pause");
    return 0;
}// end of main