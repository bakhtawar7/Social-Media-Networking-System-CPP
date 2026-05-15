#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include"posts.h"
#include"user.h"
using namespace std;
//helper function 
void copy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
//Notification Queue ADT 
class NotificationNode {
public:
    int notifyID;
    int toUserID;
    int fromUserID;
    char type[20];
    char message[100];
    NotificationNode* next;

    NotificationNode(int id, int to, int from, const char* t, const char* msg) {
        notifyID = id;
        toUserID = to;
        fromUserID = from;
        copy(type, t);
        copy(message, msg);
        next = NULL;
    }
};

class NotificationQueue {
private:
    NotificationNode* front;
    NotificationNode* rear;

public:
    NotificationQueue() { front = rear = NULL; }

    void enqueue(int id, int to, int from, const char* type, const char* msg) {
        NotificationNode* newNode = new NotificationNode(id, to, from, type, msg);
        if (rear == NULL) front = rear = newNode;
        else { rear->next = newNode; rear = newNode; }
        cout << "Notification added" << endl;
    }

    void dequeue() {
        if (front == NULL) {
            cout << "No notifications" << endl;
            return;
        }
        NotificationNode* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        cout << "Notification removed" << endl;
    }

    void display() {
        if (front == NULL) {
            cout << "No notifications" << endl;
            return;
        }
        NotificationNode* temp = front;
        while (temp != NULL) {
            cout << "NotifyID: " << temp->notifyID << " | To: " << temp->toUserID
                << " | From: " << temp->fromUserID
                << " | Type: " << temp->type
                << " | Message: " << temp->message << endl;
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream file("notifications.txt");
        NotificationNode* temp = front;
        while (temp != NULL) {
            file << temp->notifyID << " " << temp->toUserID << " "
                << temp->fromUserID << " " << temp->type << " "
                << temp->message << endl;
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("notifications.txt");
        if (!file) return;
        int nid, to, from;
        char type[20], msg[100];
        while (file >> nid >> to >> from >> type) {
            file.get();             //skip space
            file.getline(msg, 100);
            NotificationNode* newNode = new NotificationNode(nid, to, from, type, msg);
            if (rear == NULL) front = rear = newNode;
            else { rear->next = newNode; rear = newNode; }
        }
        file.close();
    }

    ~NotificationQueue() {

        NotificationNode* temp;
        while (front != nullptr) {
            temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};