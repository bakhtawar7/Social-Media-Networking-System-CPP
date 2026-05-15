#pragma once
#include <iostream>
#include <fstream>
#include"user.h"
#include"notifications.h"
using namespace std;

//helper function 
void copyString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
//Post Stack ADT
class PostNode {
public:
    int postID;
    int userID;
    char content[100];
    int likesCount;
    int commentsCount;
    PostNode* next;

    PostNode(int id, int uid, const char* c) {
        postID = id;
        userID = uid;
        copyString(content, c);
        likesCount = 0;
        commentsCount = 0;
        next = NULL;
    }
};

class PostStack {
private:
    PostNode* top;

public:
    PostStack() { top = NULL; }

    void push(int postID, int userID, const char* content) {
        PostNode* newNode = new PostNode(postID, userID, content);
        newNode->next = top;
        top = newNode;
        cout << "Post added" << endl;
    }

    void pop() {
        if (top == NULL) {
            cout << "No posts" << endl;
            return;
        }
        PostNode* temp = top;
        top = top->next;
        delete temp;
        cout << "Latest post removed" << endl;
    }

    void likePost(int postID) {
        PostNode* temp = top;
        while (temp != NULL) {
            if (temp->postID == postID) {
                temp->likesCount++; cout << "Post liked" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Post not found" << endl;
    }

    void commentPost(int postID) {
        PostNode* temp = top;
        while (temp != NULL) {
            if (temp->postID == postID) {
                temp->commentsCount++; cout << "Comment added." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Post not found" << endl;
    }

    void display() {
        if (top == NULL) {
            cout << "No posts" << endl;
            return;
        }
        PostNode* temp = top;
        while (temp != NULL) {
            cout << "PostID: " << temp->postID << " | UserID: " << temp->userID
                << " | Content: " << temp->content
                << " | Likes: " << temp->likesCount
                << " | Comments: " << temp->commentsCount << endl;
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream file("posts.txt");
        PostNode* temp = top;
        while (temp != NULL) {
            file << temp->postID << " " << temp->userID << " " << temp->content
                << " " << temp->likesCount << " " << temp->commentsCount << "\n";
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("posts.txt");
        if (!file) return;
        int pid, uid, likes, comments;
        char content[100];
        while (file >> pid >> uid) {
            file.get();
            file.getline(content, 100);
            PostNode* newNode = new PostNode(pid, uid, content);
            newNode->next = top;
            top = newNode;
        }
        file.close();
    }

    ~PostStack() {

        PostNode* temp;
        while (top != nullptr) {
            temp = top;
            top = top->next;
            delete temp;
        }
    }
};