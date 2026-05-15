#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "posts.h"
#include "notifications.h"
#include "friendsbst.h"
#include "story.h"
using namespace std;

void cpyStr(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class UserNode {
public:
    int userID;
    char name[30];
    char bio[50];
    char email[50];
    int age;
    char gender;
    char status[20];
    int followersCount;
    int followingCount;
    int* friends;
    int friendCount;
    friendsbst friendsTree;
    StoryList userStories; 
    UserNode* next;

    UserNode(int id, const char* n, const char* b,
        const char* e, int a, char g) {
        userID = id;
        cpyStr(name, n);
        cpyStr(bio, b);
        cpyStr(email, e);
        age = a;
        gender = g;
        cpyStr(status, "offline");
        followersCount = 0;
        followingCount = 0;
        friends = nullptr;
        friendCount = 0;
        next = nullptr;
    }

    ~UserNode() {
        if (friends) delete[] friends;
    }
};

class UserList {
private:
    UserNode* head;
    UserNode* tail;

public:
    UserList() : head(nullptr), tail(nullptr) {}
    void insertUser(int id, const char* name, const char* bio,
        const char* email, int age, char gender) {
        UserNode* newNode = new UserNode(id, name, bio, email, age, gender);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "User added successfully" << endl;
    }

    void deleteUser(int id) {
        UserNode* curr = head;
        UserNode* prev = nullptr;
        while (curr) {
            if (curr->userID == id) {
                if (!prev) head = curr->next;
                else prev->next = curr->next;

                if (curr == tail) tail = prev;

                delete curr;
                cout << "User deleted successfully" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "User not found" << endl;
    }

    UserNode* searchUserNode(int id) {
        UserNode* temp = head;
        while (temp) {
            if (temp->userID == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void searchUser(int id) {
        UserNode* temp = searchUserNode(id);
        if (!temp) { cout << "User not found" << endl; return; }

        cout << "ID: " << temp->userID
            << "\nName: " << temp->name
            << "\nBio: " << temp->bio
            << "\nEmail: " << temp->email
            << "\nAge: " << temp->age
            << "\nGender: " << temp->gender
            << "\nStatus: " << temp->status
            << "\nFollowers: " << temp->followersCount
            << "\nFollowing: " << temp->followingCount
            << "\nFriends: ";
        for (int i = 0; i < temp->friendCount; i++) cout << temp->friends[i] << " ";
        cout << endl;
    }

    void displayUsers() {
        if (!head) { cout << "No users available" << endl; return; }
        UserNode* temp = head;
        while (temp) {
            cout << temp->userID << " | " << temp->name << " | " << temp->bio << endl;
            temp = temp->next;
        }
    }

    void updateBio(int id, const char* newBio) {
        UserNode* temp = searchUserNode(id);
        if (!temp) { cout << "User not found" << endl; return; }
        cpyStr(temp->bio, newBio);
        cout << "Bio updated" << endl;
    }

    void updateStatus(int id, const char* newStatus) {
        UserNode* temp = searchUserNode(id);
        if (!temp) { cout << "User not found" << endl; return; }
        cpyStr(temp->status, newStatus);
        cout << "Status updated" << endl;
    }

    void addFriend(int userID, int friendID) {
        UserNode* user = searchUserNode(userID);
        UserNode* fr = searchUserNode(friendID);

        if (!user || !fr) { cout << "User or friend not found" << endl; return; }

        for (int i = 0; i < user->friendCount; i++)
            if (user->friends[i] == friendID) {
                cout << "Already friends" << endl;
                return;
            }

        int* temp = new int[user->friendCount + 1];
        for (int i = 0; i < user->friendCount; i++)
            temp[i] = user->friends[i];

        temp[user->friendCount] = friendID;
        if (user->friends) delete[] user->friends;

        user->friends = temp;
        user->friendCount++;
        user->followingCount++;
        fr->followersCount++;

        user->friendsTree.addFriend(friendID);
        fr->friendsTree.addFriend(userID);

        cout << "Friend added successfully" << endl;
    }

    void removeFriend(int userID, int friendID) {
        UserNode* user = searchUserNode(userID);
        UserNode* fr = searchUserNode(friendID);
        if (!user || !fr) { cout << "User or friend not found" << endl; return; }
        if (user->friendCount == 0) { cout << "No friends to remove" << endl; return; }

        int* temp = new int[user->friendCount - 1];
        int j = 0;
        for (int i = 0; i < user->friendCount; i++)
            if (user->friends[i] != friendID) temp[j++] = user->friends[i];

        delete[] user->friends;
        user->friends = temp;
        user->friendCount = j;
        if (j < user->followingCount) user->followingCount--;
        fr->followersCount--;

        cout << "Friend removed successfully" << endl;
    }

    void displayFriends(int id) {
        UserNode* user = searchUserNode(id);
        if (!user) { cout << "User not found" << endl; return; }
        if (user->friendCount == 0) { cout << "No friends" << endl; return; }

        cout << "Friends of " << user->name << ": ";
        for (int i = 0; i < user->friendCount; i++) cout << user->friends[i] << " ";
        cout << endl;
    }

    void mutualFriends(int id1, int id2) {
        UserNode* u1 = searchUserNode(id1);
        UserNode* u2 = searchUserNode(id2);

        if (!u1 || !u2) { cout << "User not found" << endl; return; }

        int mutual = u1->friendsTree.countMutual(u2->friendsTree);

        cout << "Mutual friends between " << u1->name << " and " << u2->name
            << " = " << mutual << endl;
    }

    //story management
    void addStoryToUser(int userID, const string& content) {
        UserNode* user = searchUserNode(userID);
        if (!user) { cout << "User not found." << endl; return; }
        user->userStories.addStory(userID, content);
    }

    void displayStoriesFeed(int startUserID) {
        if (!head) {
            cout << "No users available.\n";
            return;
        }

        UserNode* startUser = searchUserNode(startUserID);
        if (!startUser) {
            cout << "Starting user not found"<<endl;
            return;
        }

        UserNode* currUser = startUser;
        cout << endl;
        cout << "- Stories Feed -" << endl;

        do {
            //display all stories of current user
            StoryNode* tailStory = currUser->userStories.getTail();
            if (tailStory) {
                StoryNode* currStory = tailStory->next;
                do {
                    cout << "User ID: " << currStory->userID
                        << " | Story ID: " << currStory->storyID
                        << " | Content: " << currStory->content << endl;
                    currStory = currStory->next;
                } while (currStory != tailStory->next);
            }

           //moving to next user
            currUser = (currUser->next) ? currUser->next : head;

        } while (currUser != startUser);

        cout<<endl;
    }


   
    void saveToFile() {
        ofstream file("users.txt");
        if (!file) return;

        UserNode* temp = head;
        while (temp) {
            file << temp->userID << " "
                << temp->name << " "
                << temp->bio << " "
                << temp->email << " "
                << temp->age << " "
                << temp->gender << " "
                << temp->status << " "
                << temp->followersCount << " "
                << temp->followingCount << " "
                << temp->friendCount;

            for (int i = 0; i < temp->friendCount; i++)
                file << " " << temp->friends[i];

            file << endl;
            temp = temp->next;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("users.txt");
        if (!file) return;

        head = tail = nullptr;
        int id, age, followers, following, fCount;
        char name[30], bio[50], email[50], gender, status[20];

        while (file >> id >> name >> bio >> email >> age >> gender >> status
            >> followers >> following >> fCount) {

            UserNode* user = new UserNode(id, name, bio, email, age, gender);
            cpyStr(user->status, status);
            user->followersCount = followers;
            user->followingCount = following;
            user->friendCount = fCount;

            if (fCount > 0) {
                user->friends = new int[fCount];
                for (int i = 0; i < fCount; i++) {
                    file >> user->friends[i];
                    user->friendsTree.addFriend(user->friends[i]);
                }
            }

            if (!head) head = tail = user;
            else {
                tail->next = user;
                tail = user;
            }
        }

        file.close();
    }

    ~UserList() {
        while (head) {
            UserNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};
