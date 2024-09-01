#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define RANKING_FILE "rankings.txt"


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


    //����
    void load_rankings(LinkNode** L);
    void show_rankings();
    int add_rankings(char* name, int scores, LinkNode** L);
    void save_to_file(LinkNode* L);
    void sort_rankings(LinkNode** L);
    void reset_rankings(LinkNode** L);
    int delete_rankings(LinkNode** L, char* name);
    void delete_file();

#ifdef __cplusplus
}
#endif