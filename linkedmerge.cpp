#include <iostream>
#include <stack>
#include <iomanip> 
#include <cmath> 

using namespace std;

int opCount = 0; //  for complexyit analysis
int totalMergeCount = 0;


struct Node {
    int data;
    Node* next;
    Node (int value) {
        data = value;
        next = nullptr;
    }
};

class SLinkedList {
private:
    Node* head;

public:
    SLinkedList();
    ~SLinkedList();

    void insertNode(int);
    void insertForMerge(int);
    bool deleteNode(int);
    void displayList() const;
    Node* getHead() const;
    void resetToInitialState();
    bool isEmpty() const;
    void buildFromInput();
    int getLength() const;
    bool isSameVal(int);

    int countInsert;
    int countMerge;
    int countDelete;
    
};

SLinkedList::SLinkedList() {
    head = nullptr;
    countInsert=0;
    countMerge=0;
    countDelete= 0;
}

SLinkedList::~SLinkedList(){
    Node* nodePtr = head;
     
    while(nodePtr!= nullptr) {
        Node* nextNode = nodePtr -> next;

        delete nodePtr;
        nodePtr = nextNode;
    }
}

void SLinkedList :: insertNode (int value) {
    if (isSameVal(value)) {
        cout << "This value (" << value << ") is already in the list. Please enter a different value." << endl;
        return;
    }

    opCount++;  //creating new node
    Node* newNode = new Node(value);
    countInsert ++;

    if (head == nullptr || value < head->data) {
        opCount += 2;  // controls + assign
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* currentNode = head;
    while (currentNode->next != nullptr && currentNode->next->data < value) {
        currentNode = currentNode->next;
        opCount += 2; 
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
    opCount += 2;

}

void SLinkedList::insertForMerge(int value) {
    opCount++;
    Node* newNode = new Node(value);
    countInsert++;

    if (head == nullptr || value < head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* currentNode = head;
    while (currentNode->next != nullptr && currentNode->next->data < value) {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}


bool SLinkedList ::isSameVal(int value) {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data == value) return true;
        currentNode = currentNode->next;
    }
    return false;
}


void SLinkedList :: displayList () const {
    if (isEmpty()) {
        cout << "The list is empty. There are no nodes to display." << endl;
        return;
    }

    Node * nodePtr = head;

    while (nodePtr != nullptr) {
        cout << nodePtr->data << " ";
        nodePtr = nodePtr ->next;
    }

    cout << endl;

}

bool SLinkedList :: deleteNode ( int value){
    if (isEmpty()) {
        cout << "The list is already empty." << endl;
        return false;
    }

    Node * nodePtr = head;
    if(head->data == value){
        head = head->next;
        delete nodePtr;
        countDelete ++;
        return true;
    }

    Node* previousNode = nullptr;
    while (nodePtr != nullptr && nodePtr->data != value) {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }

    if(nodePtr !=nullptr){
        previousNode ->next = nodePtr ->next;
        delete nodePtr;
        countDelete ++;
        return true;
    } else {
        cout << "Value (" << value << ") not found. Deletion failed!" << endl;
        return false;
    }
}

Node* SLinkedList::getHead() const {
    return head;
}

bool SLinkedList::isEmpty() const {
    return head == nullptr;
}

void SLinkedList :: resetToInitialState () {
    while (head) {
        Node* temp = head;
        head = head -> next;
        delete temp;
    }
    countInsert = 0;
    countMerge = 0;
    countDelete = 0;
}

SLinkedList* mergeLists(SLinkedList* list1, SLinkedList* list2) {
    opCount++; 
    SLinkedList* mergedList = new SLinkedList();
    Node* ptr1 = list1->getHead();
    Node* ptr2 = list2->getHead();

    while (ptr1 != nullptr && ptr2 != nullptr) {
        opCount++;
        if (ptr1->data <= ptr2->data) {
            mergedList->insertForMerge(ptr1->data);
            ptr1 = ptr1->next;
        } else {
            mergedList->insertForMerge(ptr2->data);
            ptr2 = ptr2->next;
        }
    }

    while (ptr1 != nullptr) {
        mergedList->insertForMerge(ptr1->data);
        ptr1 = ptr1->next;
        opCount++;
    }

    while (ptr2 != nullptr) {
        mergedList->insertForMerge(ptr2->data);
        ptr2 = ptr2->next;
        opCount++;
    }

    mergedList->countInsert = mergedList->getLength();
    totalMergeCount++;
    mergedList->countMerge = totalMergeCount;

    return mergedList;
}


void arrangeOperationStats(const SLinkedList& list1, const SLinkedList& list2, const SLinkedList* merged) {
    cout << "\n\n"
         << left << setw(15) << "List"
         << setw(10) << "Insert"
         << setw(10) << "Delete"
         << setw(10) << "Merge" << endl;

    cout << string(45, '-') << endl;

    cout << left << setw(15) << "List 1"
         << setw(10) << list1.countInsert
         << setw(10) << list1.countDelete
         << setw(10) << list1.countMerge << endl;

    cout << left << setw(15) << "List 2"
         << setw(10) << list2.countInsert
         << setw(10) << list2.countDelete
         << setw(10) << list2.countMerge << endl;

    cout << left << setw(15) << "Merged List"
         << setw(10) << merged->countInsert
         << setw(10) << merged->countDelete
         << setw(10) << merged->countMerge << endl;

    cout << left << setw(15) << "Complexity"
         << setw(10) << "O(n)"
         << setw(10) << "O(n)"
         << setw(10) << "O(n + m)" << endl;

         cout << string(45, '-') << endl;
         cout << "Total Number of Operations (opCount): " << opCount << endl;



}

void SLinkedList::buildFromInput() {
    int n, val;

    while (true) {
        cout << "Please enter the number of elements to add to List: " ;

        cin >> n;

        if (cin.fail() || n <= 0) {
            cout << "Please enter a valid positive number."<< endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }

    int count = 0;  // Kaç başarılı eleman girildiğini tutar

    while (count < n) {
        cout << count + 1 << ": ";
        cin >> val;

        if (cin.fail()) {
            cout << "Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (isSameVal(val)) {
            cout << "This value (" << val << ") is already in the list. Please enter a different value." << endl;
            continue;
        }

        insertNode(val);
        count++;  // sadece başarılı olduğpunda artır
    }
}



int SLinkedList::getLength() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

char showMainMenu() {
    char choice;
    cout << "\n=== Welcome ===" << endl;
    cout << "Which operation would you like to perform?" << endl;
    cout << "a) Merge Lists" << endl;
    cout << "b) Exit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    return choice;
}

char showSubMenu() {
    char subChoice;
    cout << "\nWould you like to perform another operation?" << endl;
    cout << "a) Insert Node" << endl;
    cout << "b) Delete Node" << endl;
    cout << "c) Main Menu" << endl;
    cout << "d) Exit" << endl;
    cout << "Your choice: ";
    cin >> subChoice;
    return subChoice;
}
int main() {
    while (true) {
        char choice = showMainMenu();  // Ana menüyü göster

        if (choice == 'a' || choice == 'A') {
            SLinkedList list1, list2;

            cout << "\n***** LİST 1 *****" << endl;
            list1.buildFromInput();

            cout << "\n***** LİST 2 *****" << endl;
            list2.buildFromInput();

            SLinkedList* merged = mergeLists(&list1, &list2);

            cout << "\n******************************************"<<endl;
            cout << "\nList 1: ";
            list1.displayList();
            cout << "Length: " << list1.getLength() << endl;

            cout << "\nList 2: ";
            list2.displayList();
            cout << "Length: " << list2.getLength() << endl;

            cout << "\nMerged List: ";
            merged->displayList();
            cout << "Length: " << merged->getLength() << endl;

            arrangeOperationStats(list1, list2, merged);
        
            cout << "\n******************************************"<<endl;

            while (true) {
                char subChoice = showSubMenu();  // Alt menüyü göster

                if (subChoice == 'a' || subChoice == 'A') {
                    int listNo, value;

                    while (true) {
                        cout << "Which list would you like to insert into? (1 or 2): ";
                        cin >> listNo;

                        if (cin.fail() || (listNo != 1 && listNo != 2)) {
                            cout << "Please make a valid choice (1 or 2). \n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                        } else {
                            break;
                        }
                    }

                    while (true) {
                        cout << "Enter the value you would like to insert: ";
                        cin >> value;

                        if (cin.fail()) {
                            cout << "Please enter a valid integer.\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            continue;
                        }

                        bool alreadyExists = (listNo == 1) ? list1.isSameVal(value) : list2.isSameVal(value);

                        if (alreadyExists) {
                            cout << "This value already exists. Please enter a value that is not already in the list.\n";
                        } else {
                            break;
                        }
                    }

                    if (listNo == 1) {
                        list1.insertNode(value);
                    } else {
                        list2.insertNode(value);
                    }

                    cout << "\nInsert operation completed successfully!\n";

                } else if (subChoice == 'b' || subChoice == 'B') {
                    int listNo, value;

                    while (true) {
                        cout << "Which list would you like to delete from? (1 or 2): ";
                        cin >> listNo;

                        if (cin.fail() || (listNo != 1 && listNo != 2)) {
                            cout << "Please make a valid choice (1 or 2). \n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                        } else {
                            break;
                        }
                    }

                    while (true) {
                        cout << "Enter the value you would like to delete: ";
                        cin >> value;

                        if (cin.fail()) {
                            cout << "Please enter a valid number. ";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            continue;
                        }

                        bool success = (listNo == 1) ? list1.deleteNode(value) : list2.deleteNode(value);

                        if (!success) {
                            cout << "This value is not in the list. Please enter a value that exists.\n";

                        } else {
                            cout << "\nDelete operation completed successfully!\n";
                            break;
                        }
                    }

                } else if (subChoice == 'c' || subChoice == 'C') {
                    delete merged;
                    break;  // yeni bir merge işlemi için döngüyü kır

                } else if (subChoice == 'd' || subChoice == 'D') {
                    char confirm;
                    cout << "Are you sure you want to exit? (y/n): ";
                    cin >> confirm;

                    if (confirm == 'y' || confirm == 'Y') {
                        delete merged;
                        cout << "Goodbye..." << endl;
                        return 0;
                    } else {
                        continue;
                    }

                } else {
                    cout << "Please select a valid option (a, b, c, or d)." << endl;
                    continue;
                }

                // Her işlem sonrası listeleri ve merge işlemini güncelle
                delete merged;
                merged = mergeLists(&list1, &list2);



                cout << "\n\n************* UPDATED LISTS *************\n" << endl;
                cout << "List 1: ";
                list1.displayList();
                cout << "Length: " << list1.getLength() << endl;

                cout << "List 2: ";
                list2.displayList();
                cout << "Length: " << list2.getLength() << endl;

                cout << "Merged List: ";
                merged->displayList();
                cout << "Length: " << merged->getLength() << endl;

                arrangeOperationStats(list1, list2, merged);

                cout << "\n******************************************"<<endl;

        
            }

        } else if (choice == 'b' || choice == 'B') {
            cout << "Goodbye..." << endl;
            break;

        } else {
            cout << "Please select a valid option (a, b, c, or d)." << endl;
        }
    }

    return 0;
}