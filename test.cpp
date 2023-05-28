#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "filter_iterator.h"

using namespace std;
using namespace qujifa::iterator;


// Data type to be used in this test
struct DbRecord {
    int seqNum;
    string company;
    string state;
    string industry;
};

// filter function: iterate all "Bank" records
bool filterBank(const DbRecord& entry) {
    return entry.industry == "Bank";
}  

// filter function: iteratl all "NY" "Bank" records
bool filterBankNY(const DbRecord& entry) {
    return entry.industry == "Bank" && entry.state == "NY";
}

int main()
{  
    // create a QuDataSet object
    QuDataSet<DbRecord> myData;

    // populate with mock data
    myData.data().push_back({1, "Amazon", "WA", "HighTech"});
    myData.data().push_back({2, "Microsoft", "WA", "HighTech"});
    myData.data().push_back({3, "Intel", "CA", "HighTech"});
    myData.data().push_back({4, "Apple", "CA", "HighTech"});
    myData.data().push_back({5, "Zoom", "CA", "HighTech"});
    myData.data().push_back({6, "Tesla", "CA", "HighTech"});
    myData.data().push_back({7, "Citi", "NY", "Bank"});
    myData.data().push_back({8, "CVR", "TX", "Oil"});
    myData.data().push_back({9, "TI", "TX", "HighTech"});
    myData.data().push_back({10, "Costco", "WA", "Retails"});
    myData.data().push_back({11, "Boeing", "WA", "Airplane"});
    myData.data().push_back({12, "Wells Fargo", "CA", "Bank"});
    myData.data().push_back({13, "Exxon", "TX", "Oil"});
    myData.data().push_back({14, "Pfezer", "NY", "Medical"});
    myData.data().push_back({15, "Bank Of America", "NC", "Bank"});
    myData.data().push_back({16, "JPM Chase", "NY", "Bank"});
 
    // by default, iterate all data records
    cout << "By default iterate all records - \n";
    cout << "----------------------------------------\n";
    cout << "Seq   Company         State     Industry\n";
    cout << "---   -------         -----     --------\n";
    QuDataSet<DbRecord>::Iterator it = myData.begin();
    for(; it != myData.end(); ++it) {
        cout << left << setw(6)
        << it->seqNum << setw(16)
        << it->company << setw(10)
        << it->state 
        << it->industry
        << endl;
    } 
    cout << "----------------------------------------\n\n";

    // set filter: iterate all banks
    myData.setFilter(filterBank);
    it = myData.begin();
    cout << "all Bank records - \n";
    cout << "----------------------------------------\n";
    cout << "Seq   Company         State     Industry\n";
    cout << "---   -------         -----     --------\n";
     for(; it != myData.end(); ++it) {
        cout << left << setw(6)
        << it->seqNum << setw(16)
        << it->company << setw(10)
        << it->state 
        << it->industry
        << endl;
    } 
    cout << "----------------------------------------\n\n";
 
    // set filter: iterate all NY banks
    myData.setFilter(filterBankNY);
    it = myData.begin();
    cout << "all NY Bank records - \n";
    cout << "----------------------------------------\n";
    cout << "Seq   Company         State     Industry\n";
    cout << "---   -------         -----     --------\n";
    for(; it != myData.end(); ++it) {
        cout << left << setw(6)
        << it->seqNum << setw(16)
        << it->company << setw(10)
        << it->state 
        << it->industry
        << endl;
    } 
    cout << "----------------------------------------\n\n";

    return 0;
}

/* Test Output:

By default iterate all records - 
----------------------------------------
Seq   Company         State     Industry
---   -------         -----     --------
1     Amazon          WA        HighTech
2     Microsoft       WA        HighTech
3     Intel           CA        HighTech
4     Apple           CA        HighTech
5     Zoom            CA        HighTech
6     Tesla           CA        HighTech
7     Citi            NY        Bank
8     CVR             TX        Oil
9     TI              TX        HighTech
10    Costco          WA        Retails
11    Boeing          WA        Airplane
12    Wells Fargo     CA        Bank
13    Exxon           TX        Oil
14    Pfezer          NY        Medical
15    Bank Of America NC        Bank
16    JPM Chase       NY        Bank
----------------------------------------

all Bank records - 
----------------------------------------
Seq   Company         State     Industry
---   -------         -----     --------
7     Citi            NY        Bank
12    Wells Fargo     CA        Bank
15    Bank Of America NC        Bank
16    JPM Chase       NY        Bank
----------------------------------------

all NY Bank records - 
----------------------------------------
Seq   Company         State     Industry
---   -------         -----     --------
7     Citi            NY        Bank
16    JPM Chase       NY        Bank
----------------------------------------

*/
