#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "index.c"

#define RANKING_FILE "rankings.txt"


int Sum = 0;

typedef struct info
{
    int id;
    char* name;
    int scores;
}Player;

typedef struct node
{
    Player val;
    struct node* next;

}LinkNode;

LinkNode* L = NULL;

void delete_file()
{
    FILE* fp = NULL;

    if ((fp = fopen(RANKING_FILE, "w")) == NULL)
    {
        printf("Fail to open file\n");
        return;
    }

    fclose(fp);
}

void load_rankings(LinkNode** L)
{
    FILE* fp = NULL;
    if ((fp = fopen(RANKING_FILE, "r")) == NULL)
    {
        perror("fail to open file");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    if (ftell(fp) == 0)
    {
        *L = NULL;
        return;
    }


    fseek(fp, 0L, SEEK_SET);

    LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode));

    if (head == NULL)
    {
        return;
    }
    *L = head;



    Player player;
    char* name = malloc(sizeof(char) * 21);
    memset(name, 0, sizeof(char) * 21);
    fscanf(fp, "%d%s%d\n", &player.id, name, &player.scores);
    player.name = malloc(sizeof(char) * 20);
    strcpy(player.name, name);
    head->val = player;
    head->next = NULL;
    memset(name, 0, sizeof(name));
    Sum++;
    while (fscanf(fp, "%d%s%d\n", &player.id, name, &player.scores) != EOF)
    {
        name[19] = '\0';
        player.name = malloc(sizeof(char) * 20);
        strncpy(player.name, name, 19);
        player.name[19] = '\0';
        LinkNode* new = (LinkNode*)malloc(sizeof(LinkNode));
        if (new == NULL)
        {
            return;
        }
        new->val = player;
        new->next = head->next;
        head->next = new;
        memset(name, 0, sizeof(name));
        Sum++;
    }
    free(name);
    fclose(fp);
    return;
}

void show_rankings()
{
    FILE* fp;

    if ((fp = fopen(RANKING_FILE, "r")) == NULL)
    {
        printf("Fail to open file.\n");
    }
    char ch;
    fseek(fp, 0L, SEEK_END);
    if (ftell(fp) == 0)
    {
        return;
    }
    fseek(fp, 0L, SEEK_SET);

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");
    fclose(fp);
    return;
}

int add_rankings(char* name, int scores, LinkNode** L)
{
    LinkNode* cur, * new;
    LinkNode* head = *L;
    new = (LinkNode*)malloc(sizeof(LinkNode));
    Player pl;
    pl.id = Sum + 1;
    pl.scores = scores;
    pl.name = name;
    if (new == NULL)
    {
        return 0;
    }
    new->val = pl;
    new->next = NULL;
    if (*L == NULL)
    {
        *L = new;
        return 1;
    }
    cur = head->next;
    int i = 2;

    if (cur == NULL)
    {
        head->next = new;
        Sum++;
    }
    else
    {
        new->next = head->next;
        head->next = new;
        Sum++;
    }
    return 1;
}

int delete_rankings(LinkNode** L, char* name)
{
    LinkNode* pre = NULL, * cur = NULL;
    cur = *L;   
    while (cur != NULL)
    {
        if (strcmp(cur->val.name, name) == 0)
        {
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        printf("No such player\n");
        return 0;
    }
    else if (cur == *L)
    {
        *L = cur->next;
        free(cur);
    }
    else
    {
        pre->next = cur->next;
        free(cur);
    }
    return 0;
}

void reset_rankings(LinkNode** L)
{
    LinkNode* p;
    while (*L)
    {
        p = *L;
        *L = (*L)->next;
        free(p);
    }

    *L = NULL;

    Sum = 0;

}

void sort_rankings(LinkNode** L)
{
    LinkNode* p = *L;
    Player temp;

    if (p == NULL)
    {
        return;
    }

    for (int i = 0; i < Sum ; i++)
    {
        for (int j = 0; j < Sum; j++)
        {
            if (p != NULL && p->next != NULL && p->val.scores < p->next->val.scores)
            {
                temp = p->val;
                p->val = p->next->val;
                p->next->val = temp;
            }
            p = p->next;
        }
        p = *L;
    }
    return;
}

void save_to_file(LinkNode* L)
{
    LinkNode* p = L;
    FILE* fp;

    if ((fp = fopen(RANKING_FILE, "w+")) == NULL)
    {
        printf("Fail to save to file.\n");
        return;
    }
    if (p == NULL)
    {
        fclose(fp);
        return;
    }


    while (p)
    {
        
        int kk = fprintf(fp,"%-8d%-15s%-8d\n", p->val.id, p->val.name, p->val.scores);
        if (kk < 0)
        {
            printf("Fail to write to file.\n");
            return;
        }
        p = p->next;
    }

    fclose(fp);
    
    return;
}

int is_empty(LinkNode* L)
{
    return L == NULL;
}
