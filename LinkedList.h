#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        // node default constructor
        Node(const T& d) : data(d), next(nullptr), prev(nullptr){}
    };
private:
    int nodeNum = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    // linked list default constructor
    LinkedList() : nodeNum(0), head(nullptr), tail(nullptr){}

    // copy constructor
    LinkedList(const LinkedList& obj){
        head = nullptr;
        Node* current = obj.head;
        while (current != nullptr){
            AddTail(current->data);
            current = current->next;
        }
    }

    // copy assignment operator
    LinkedList &operator=(const LinkedList &obj){
        if (this != &obj){
            Clear();
            Node* current = obj.head;
            while (current != nullptr){
                AddTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // destructor
    ~LinkedList(){
        Node* current = head;
        while (current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // operator
    bool operator==(const LinkedList& obj) const {
        Node* this_current = head;
        Node* obj_current = obj.head;
        while (this_current != nullptr && obj_current != nullptr) {
            if (this_current->data != obj_current->data) {
                return false;
            }
            this_current = this_current->next;
            obj_current = obj_current->next;
        }
        return (this_current == nullptr && obj_current == nullptr);
    }

    // functions
    void PrintForward();
    void PrintReverse();
    void PrintForwardRecursive(Node* current);
    void PrintReverseRecursive(Node* current);

    int NodeCount();
    void FindAll(vector<Node*>& find_node, T find_value);
    Node* Find(T find_value) const;
    Node* GetNode(int index) const;
    Node* Head();
    Node* Tail();

    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T arr[], int size);
    void AddNodesTail(const T arr[], int size);
    void InsertAfter(Node* node_before, T insert_data);
    void InsertBefore(Node* node_after, T insert_data);
    void InsertAt(T insert_data, int index);

    bool RemoveHead();
    bool RemoveTail();
    int Remove(const T& data);
    bool RemoveAt(int index);
    void Clear();

    T operator[](int index) const;
};

// behaviors
template<typename T>
void LinkedList<T>::PrintForward(){
    if (nodeNum == 0){
        return;
    }
    else{
        Node* temp = head;
        while(temp!= nullptr){
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
}

template<typename T>
void LinkedList<T>::PrintReverse(){
    if (nodeNum == 0){
        return;
    }
    else{
        Node* temp = tail;
        while (temp != nullptr){
            cout << temp->data << endl;
            temp = temp->prev;
        }
    }
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(Node* current){
    if (current == nullptr) {
        return;
    }
    cout << current->data << endl;
    PrintForwardRecursive(current->next);
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(Node* current){
    if (current == nullptr) {
        return;
    }
    cout << current->data << endl;
    PrintReverseRecursive(current->prev);
}

// accessors
template<typename T>
int LinkedList<T>::NodeCount(){
    return nodeNum;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& find_node, T find_value){
    Node* current = head;
    while (current != nullptr){
        if (current->data == find_value){
            find_node.push_back(current);
        }
        current = current->next;
    }
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(T find_value) const{
    Node* current = head;
    while (current != nullptr){
        if (current->data == find_value){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const{
    if (nodeNum < index < 0){
        throw out_of_range("bad");
    }
    Node* current = head;
    int node_counter = 0;
    while (current != nullptr){
        if (node_counter == index){
            return current;
        }
        current = current->next;
        node_counter++;
    }
    throw out_of_range("bad");
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head(){
    return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail(){
    return tail;
}

//insertions
template<typename T>
void LinkedList<T>::AddHead(const T& data){
    if (nodeNum == 0){
        Node* temp = new Node(data);
        head = temp;
        tail = temp;
        temp->prev = nullptr;
        nodeNum++;
    }
    else{
        Node* temp = new Node(data);
        temp->next = head;
        head->prev = temp;
        head = temp;
        nodeNum++;
    }
}

template<typename T>
void LinkedList<T>::AddTail(const T& data){
    if (tail == nullptr){
        Node* temp = new Node(data);
        tail = temp;
        head = temp;
        temp->next = nullptr;
        nodeNum++;
    }
    else{
        Node* temp = new Node(data);
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        nodeNum++;
    }
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T arr[], int size) {
    for (int i = size - 1; i >= 0; --i) {
        Node* newNode = new Node(arr[i]);
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++nodeNum;
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T arr[], int size) {
    for (int i = size - 1; i >= 0; --i) {
        Node* newNode = new Node(arr[i]);
        newNode->prev = tail;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        ++nodeNum;
    }
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node_before, T insert_data){
    if (node_before != nullptr) {
        Node* newNode = new Node(insert_data);
        newNode->next = node_before->next;
        if (node_before->next != nullptr){
            node_before->next->prev = newNode;
        }
        newNode->prev = node_before;
        node_before->next = newNode;
    }
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node_after, T insert_data){
    if (node_after != nullptr) {
        Node* newNode = new Node(insert_data);
        newNode->prev = node_after->prev;
        if (node_after->prev != nullptr) {
            node_after->prev->next = newNode;
        }
        else {
            head = newNode; // If node_after is the head
        }
        newNode->next = node_after;
        node_after->prev = newNode;
    }
}

template<typename T>
void LinkedList<T>::InsertAt(T insert_data, int index) {
    if (index < 0) {
        throw out_of_range("bad");
    }
    if (index == 0){
        Node* newNode = new Node(insert_data);
        newNode->next = head;
        head = newNode;
        nodeNum++;
        return;
    }
    Node* current = head;
    Node* previous = nullptr;
    int current_index = 0;
    while (current != nullptr && current_index < index){
        previous = current;
        current = current->next;
        current_index++;
    }
    if (current_index != index){
        throw out_of_range("bad");
    }
    Node* newNode = new Node(insert_data);
    newNode->next = current;
    previous->next = newNode;
    nodeNum++;
}

// removals
template<typename T>
bool LinkedList<T>::RemoveHead(){
    if (head == nullptr){
        return false;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr){
        head->prev = nullptr;
    }
    else{
        tail = nullptr;
    }
    delete temp;
    nodeNum--;
    return true;
}

template<typename T>
bool LinkedList<T>::RemoveTail(){
    if (tail == nullptr){
        return false;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr){
        tail->next = nullptr;
    }
    else{
        head = nullptr;
    }
    delete temp;
    nodeNum--;
    return true;
}

template<typename T>
int LinkedList<T>::Remove(const T& data){
    int instances_removed = 0;
    Node* current = head;
    Node* remove;
    while (current){
        if (current->data == data){
            current->next->prev = current->prev;
            current->prev->next = current->next;
            instances_removed += 1;
            nodeNum--;
            remove = current;
            current = current->next;
            delete remove;
        }
        else{
            current = current->next;
        }
    }
    return instances_removed;
}

template<typename T>
bool LinkedList<T>::RemoveAt(int index){
    if (index < 0 || index >= nodeNum) {
        return false;
    }
    if (nodeNum == 1){
        RemoveTail();
        nodeNum--;
    }
    else{
        Node* temp = GetNode(index);
        temp->prev->next = temp->next;
        delete temp;
        nodeNum--;
        return true;
    }
}

template<typename T>
void LinkedList<T>::Clear(){
    Node* current = head;
    while (current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    nodeNum = 0;
}

// operators
template<typename T>
T LinkedList<T>::operator[](int index) const{
    if (index < 0 && index > nodeNum){
        throw out_of_range("bad");
    }
    return GetNode(index)->data;
}
