#include <iostream>
#include <string>
#include "List.h"
#include "Treap.h"
#include <fstream>
using namespace std;
template<class T>
void listAllFriends(Treap myTreap, List<T> myList) {
    Treap::Node* Root = myTreap.getRoot();
    if (Root != NULL)
    {
        listAllFriendsRecursion(Root, myList);
    }
    else
        cout << "no friends found\n";
}

template<class T>
void listAllFriendsRecursion(Treap::Node* root, List<T> myList) {
    if (root != NULL)
    {
        listAllFriendsRecursion(root->left, myList);
        cout << "username: " << root->username << endl;
        cout << "name:" << (myList.search(root->username)).pointer->name << endl;
        listAllFriendsRecursion(root->right, myList);
    }
}

void peopleYouMayKnow(List<string>::Iterator iter, List<string> users)
{
    List<string>::Iterator iter2 = users.begin();
    int i = 0, count = 0;
    for (i = 0; i < users.size() && count < 5; i++)
    {
        if (iter.pointer->friendTree.find(iter.pointer->friendTree.getRoot(), *iter2) == false)
        {
            iter2.pointer->display();
            count++;
        }
        ++iter2;
    }
}

int mainmenu()
{
    int x;
    cout << "------choose one action from the list-----\n";
    cout << "1-list all friends\n2-Search user by username\n3-Add friend\n4-remove friend\n5-Show people you may Know\n6-Log out\n";
    cin >> x;
    return x;
}
int login()
{
    int x;
    cout << "------choose one action from the list-----\n";
    cout << "1-Login\n2-Exit\n";
    cin >> x;
    return x;
}
void AddFriend(string user1, string user2, Treap& t1, Treap& t2)
{
    if (t1.search(user2) == false) {
        t1.Insert(user1);
        t2.Insert(user2);
        cout << "You are now friends." << endl;
    }
    else {
        cout << "You are already friends." << endl;
    }
}
int main() {
    fstream file;
    List<string>users;
    file.open("all-users.in", ios::in);
    if (!file.is_open())
    {
        cout << "error openning all-users file";
    }
    else
    {
        string name, username, email;
        while (getline(file, username, ','))
        {
            getline(file, name, ',');
            getline(file, email);
            name.erase(0, 1);
            email.erase(0, 1);
            users.pushBack(username, name, email);
        }
    }
    file.close();
    file.open("all-users-relations.in", ios::in);
    if (!file.is_open())
    {
        cout << "error openning all-users-relations file";
    }
    else {
        string username1, username2;
        List<string>::Iterator it1, it2;
        while (getline(file, username1, ','))
        {
            getline(file, username2);
            username2.erase(0, 1);
            it1 = users.search(username1);
            it2 = users.search(username2);
            it1.pointer->friendTree.Insert(username2);
            it2.pointer->friendTree.Insert(username1);
        }
    }
    file.close();
    string username;
    int choise = 0;
    List<string> ::Iterator iter;
    cout << "----------welcome to chat-----------\n";
    while (choise != 2)
    {
        choise = login();
        if (choise == 1) {
            cout << "-------enter username to login------\nusername: ";
            cin >> username;
            iter = users.search(username);
            if (iter != NULL) {
                while (choise != 6) {
                    choise = mainmenu();
                    if (choise == 1)
                    {
                        listAllFriends(iter.pointer->friendTree, users);
                        choise = 0;
                    }
                    else if (choise == 2)
                    {
                        List<string>::Iterator it2;
                        cout << "enter username:";
                        cin >> username;
                        if (iter.pointer->friendTree.search(username))
                        {
                            it2 = users.search(username);
                            it2.pointer->display();
                        }
                        else {
                            cout << "not found" << endl;
                        }
                        choise = 0;
                    }
                    else if (choise == 3)
                    {
                        List<string>::Iterator it2;
                        cout << "enter username:";
                        cin >> username;
                        it2 = users.search(username);
                        if (it2 != NULL) {
                            AddFriend(username, *iter, iter.pointer->friendTree, it2.pointer->friendTree);
                        }
                        else {
                            cout << "User Name not found" << endl;
                        }
                        choise = 0;
                    }
                    else if (choise == 4)
                    {
                        List<string>::Iterator it2;
                        cout << "enter username:";
                        cin >> username;
                        it2 = users.search(username);
                        iter.pointer->friendTree.removeFriend(username);
                        it2.pointer->friendTree.removeFriend(*iter);
                        choise = 0;
                    }
                    else if (choise == 5)
                    {
                        peopleYouMayKnow(iter, users);
                        choise = 0;
                    }
                }
            }
            else {
                cout << "User Name not found" << endl;
            }
        }
    }
}
