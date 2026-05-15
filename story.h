#pragma once
#include <iostream>
#include <string>
using namespace std;
//circular linked list
class StoryNode {
public:
    int storyID;
    int userID;
    string content;
    StoryNode* next;

    StoryNode(int sID, int uID, const string& c) {
        storyID = sID;
        userID = uID;
        content = c;
        next = nullptr;
    }
};

class StoryList {
private:
    StoryNode* tail;
    int storyCounter;

public:
    StoryList() {
        tail = nullptr;
        storyCounter = 1;
    }

    void addStory(int userID, const string& content) {
        StoryNode* newStory = new StoryNode(storyCounter++, userID, content);

        if (!tail) {
            tail = newStory;
            tail->next = tail;
        }
        else {
            newStory->next = tail->next;
            tail->next = newStory;
            tail = newStory;
        }

        cout << "Story added successfully! Story ID: " << newStory->storyID << endl;
    }

    void removeStory(int storyID) {
        if (!tail) {
            cout << "No stories to remove." << endl;
            return;
        }

        StoryNode* curr = tail->next;
        StoryNode* prev = tail;
        bool found = false;

        do {
            if (curr->storyID == storyID) {
                found = true;

                if (curr == tail && curr->next == tail) { 
                    delete curr;
                    tail = nullptr;
                }
                else {
                    prev->next = curr->next;
                    if (curr == tail) tail = prev;
                    delete curr;
                }

                cout << "Story removed successfully" << endl;
                break;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != tail->next);

        if (!found) cout << "Story ID not found!" << endl;
    }

    void displayStories() {
        if (!tail) {
            cout << "No stories to display." << endl;
            return;
        }

        StoryNode* curr = tail->next;
        cout << endl;
        cout << "- User's Stories -"<<endl;
        do {
            cout << "User ID: " << curr->userID
                << " | Story ID: " << curr->storyID
                << " | Content: " << curr->content << endl;
            curr = curr->next;
        } while (curr != tail->next);
        cout << endl;
    }

    StoryNode* getTail() { return tail; }

    ~StoryList() {
        if (!tail) return;

        StoryNode* curr = tail->next;
        StoryNode* nextNode;

        do {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        } while (curr != tail->next);

        tail = nullptr;
    }
};
