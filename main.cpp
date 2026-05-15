#include <iostream>
#include <fstream>
#include "posts.h"
#include "notifications.h"
#include "user.h"
#include "friendsbst.h"
using namespace std;

// MAIN FUNCTION
int main() {
    UserList users;
    PostStack posts;
    NotificationQueue notifications;

    users.loadFromFile();
    posts.loadFromFile();
    notifications.loadFromFile();

    int choice;
    do {
        cout << endl;
        cout << "SOCIAL MEDIA NETWORKING SYSTEM" << endl;
        cout << "1. Add User\n2. Delete User\n3. Search User\n4. Display Users\n";
        cout << "5. Update Bio\n6. Update Status\n7. Add Friend\n8. Remove Friend\n9. Display Friends\n";
        cout << "10. Add Post\n11. Remove Post\n12. Like Post\n13. Comment Post\n14. Display Posts\n";
        cout << "15. Add Notification\n16. Remove Notification\n17. Display Notifications\n";
        cout << "18. Mutual Friends (Advanced Search)\n";
        cout << "19. Add Story\n20. Display User Stories\n";
        cout << "0. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int id, age;
            char name[30], bio[50], email[50], gender;
            cout << "ID: "; cin >> id; cin.ignore();
            cout << "Name: "; cin.getline(name, 30);
            cout << "Bio: "; cin.getline(bio, 50);
            cout << "Email: "; cin.getline(email, 50);
            cout << "Age: "; cin >> age; cin.ignore();
            cout << "Gender (M/F): "; cin >> gender; cin.ignore();
            users.insertUser(id, name, bio, email, age, gender);
        }
        else if (choice == 2) {
            int id; cout << "UserID: "; cin >> id; cin.ignore();
            users.deleteUser(id);
        }
        else if (choice == 3) {
            int id; cout << "UserID: "; cin >> id; cin.ignore();
            users.searchUser(id);
        }
        else if (choice == 4) users.displayUsers();
        else if (choice == 5) {
            int id; char bio[50];
            cout << "UserID: "; cin >> id; cin.ignore();
            cout << "New Bio: "; cin.getline(bio, 50);
            users.updateBio(id, bio);
        }
        else if (choice == 6) {
            int id; char status[20];
            cout << "UserID: "; cin >> id; cin.ignore();
            cout << "New Status: "; cin.getline(status, 20);
            users.updateStatus(id, status);
        }
        else if (choice == 7) {
            int uid, fid;
            cout << "Your UserID: "; cin >> uid; cin.ignore();
            cout << "Friend's UserID: "; cin >> fid; cin.ignore();
            users.addFriend(uid, fid);
        }
        else if (choice == 8) {
            int uid, fid;
            cout << "Your UserID: "; cin >> uid; cin.ignore();
            cout << "Friend's UserID to remove: "; cin >> fid; cin.ignore();
            users.removeFriend(uid, fid);
        }
        else if (choice == 9) {
            int uid; cout << "UserID: "; cin >> uid; cin.ignore();
            users.displayFriends(uid);
        }
        else if (choice == 10) {
            int pid, uid; char content[100];
            cout << "PostID: "; cin >> pid; cin.ignore();
            cout << "UserID: "; cin >> uid; cin.ignore();
            cout << "Content: "; cin.getline(content, 100);
            posts.push(pid, uid, content);
        }
        else if (choice == 11) posts.pop();
        else if (choice == 12) {
            int pid; cout << "PostID to like: "; cin >> pid; cin.ignore();
            posts.likePost(pid);
        }
        else if (choice == 13) {
            int pid; cout << "PostID to comment: "; cin >> pid; cin.ignore();
            posts.commentPost(pid);
        }
        else if (choice == 14) posts.display();
        else if (choice == 15) {
            int nid, to, from; char type[20], msg[100];
            cout << "NotificationID: "; cin >> nid; cin.ignore();
            cout << "To UserID: "; cin >> to; cin.ignore();
            cout << "From UserID: "; cin >> from; cin.ignore();
            cout << "Type: "; cin.getline(type, 20);
            cout << "Message: "; cin.getline(msg, 100);
            notifications.enqueue(nid, to, from, type, msg);
        }
        else if (choice == 16) notifications.dequeue();
        else if (choice == 17) notifications.display();
        else if (choice == 18) {
            int u1, u2;
            cout << "First UserID: "; cin >> u1; cin.ignore();
            cout << "Second UserID: "; cin >> u2; cin.ignore();
            users.mutualFriends(u1, u2);
        }
        else if (choice == 19) {
            int uid; string content;
            cout << "UserID: "; cin >> uid; cin.ignore();
            cout << "Story Content: "; getline(cin, content);
            users.addStoryToUser(uid, content);
        }
        else if (choice == 20) {
            int uid;
            cout << "UserID: "; cin >> uid; cin.ignore();
            users.displayStoriesFeed(uid);
        }
        else if (choice == 0) {
            cout << "Exiting, saving data..." << endl;
            users.saveToFile();
            posts.saveToFile();
            notifications.saveToFile();
        }
        else cout << "Invalid choice" << endl;

    } while (choice != 0);

    return 0;
}
