#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib\bookList.h"
#include "lib\userList.h"
#include "lib\init.h"
#include "lib\menu.h"
#include "lib\saveInfo.h"
#include "lib\network.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }

    // init
    bookList *list = (bookList *)malloc(sizeof(bookList));
    userList *ulist = (userList *)malloc(sizeof(userList));
    userList *alist = (userList *)malloc(sizeof(userList));
    initList(list);
    initUserList(ulist);
    initAdminList(alist);

    // connect
    Connection network = buildConnection(argv[1]);

    // index
    userNode *user = welcomeMenu(list, ulist, alist, network.clientfd);
    if (user)
    {
        if (user->userInfomation.isAdmin == 0)
        {
            userMenu(list, user, network.clientfd);
        }
        else if (user->userInfomation.isAdmin == 1)
        {
            adminMenu(list, ulist, network.clientfd);
        }
    }

    // close
    closeConnect(network);

    // save
    saveBookInfo(list);
    saveUserInfo(ulist);

    // free
    freeList(list, ulist, alist);

    // end
    return 0;
}