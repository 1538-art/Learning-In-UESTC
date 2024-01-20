#ifndef HEADER_FILE
#define HEADER_FILE
#define WIDTH 30
#define HEIGHT 20
typedef struct user{
    char name[11];
	int acc;
	char pas[11];
	int score[3][3];
	struct user *pnext;
}user;
typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    Position head;
    Position tail[WIDTH * HEIGHT];
    int length;
} Snake;

typedef struct
{
    Position position;
    int eaten;
} Food;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;


void openfile(user **head);
void login(user *head);
void regist(user **head);
void homepage(user *head);
void loginpage(user *head);
void registpage(user **head);
void gamepage(user **head,int account);
void dele(user **head,int account);
void locallist(user **head,int account);
void putinlocallist(user** head,int account ,int scorenum,int num);

int  sweep();
void mapChange(int x, int y);
int num(int x, int y);

void drawMap(Snake snake, Food food);
void updateSnake(Snake *snake, Direction direction, Food *food);
void generateFood(Food *food, Snake snake);
int snake();
void dele(user **head);

void Locate(int x, int y);
void control(char a[15][50], int* y, int* ming, int s);
int jumpman();
#endif
