// HRMS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "nodelist.h"
#include "storage.h"
#include "data_types.h"

int main() {
    DiskStorage<User> userDatabase("users.db");

    if (userDatabase.nodeList.empty()) {
        User user;
        user.username = "alper";
        user.password = "sifre";
        user.emailAddress = "test@gmail.com";
        user.permissions = 53;

        userDatabase.nodeList.push(user);

        user.username = "kullanici";
        user.password = "gfdssfdsa";
        user.emailAddress = "dsafdas@gmail.com";
        user.permissions = 23;

        userDatabase.nodeList.push(user);

        printf("saved users, restart to load\n");
    }
    else {
        for (size_t i = 0; i < userDatabase.nodeList.size(); i++) {
            User& user = userDatabase.nodeList[i];

            printf("User %lld: %s|%s|%s|%d\n", i + 1,
                user.username.data(),
                user.password.data(),
                user.emailAddress.data(),
                user.permissions);
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu