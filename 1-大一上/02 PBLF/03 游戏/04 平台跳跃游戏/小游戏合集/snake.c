#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "head.h"



void drawMap(Snake snake, Food food)
{
    for (int i = 0; i < HEIGHT + 2; i++)
    {
        for (int j = 0; j < WIDTH + 2; j++)
        {
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1)
            {
                printf("#");
            }
            else if (i == snake.head.y && j == snake.head.x)
            {
                printf("@");
            }
            else if (i == food.position.y && j == food.position.x)
            {
                printf("*");
            }
            else
            {
                int isTail = 0;
                for (int k = 0; k < snake.length; k++)
                {
                    if (i == snake.tail[k].y && j == snake.tail[k].x)
                    {
                        printf("+");
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail)
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void updateSnake(Snake *snake, Direction direction, Food *food)
{
    Position prevHead = snake->head;
    Position prevTail = snake->tail[snake->length - 1];

    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->tail[i] = snake->tail[i - 1];
    }
    snake->tail[0] = prevHead;

    switch (direction)
    {
    case UP:
        snake->head.y--;
        break;
    case DOWN:
        snake->head.y++;
        break;
    case LEFT:
        snake->head.x--;
        break;
    case RIGHT:
        snake->head.x++;
        break;
    }

    if (snake->head.x == food->position.x && snake->head.y == food->position.y)
    {
        snake->length++;
        food->eaten = 1;
    }
}

void generateFood(Food *food, Snake snake)
{
    do
    {
        food->position.x = rand() % WIDTH + 1;
        food->position.y = rand() % HEIGHT + 1;
    } while (food->position.x == snake.head.x && food->position.y == snake.head.y);

    food->eaten = 0;
}

int snake()
{
    Snake snake;
    snake.head.x = WIDTH / 2;
    snake.head.y = HEIGHT / 2;
    snake.length = 1;

    Direction direction = RIGHT;

    Food food;
    generateFood(&food, snake);

    int score = 0;
    int gameover = 0;

    while (!gameover)
    {
        system("cls");
        drawMap(snake, food);
        printf("press w s a d to control the snake to go UP DOWN LEFT RIGHT");
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case 'w':
            case 'W':
                if (direction != DOWN)
                {
                    direction = UP;
                }
                break;
            case 's':
            case 'S':
                if (direction != UP)
                {
                    direction = DOWN;
                }
                break;
            case 'a':
            case 'A':
                if (direction != RIGHT)
                {
                    direction = LEFT;
                }
                break;
            case 'd':
            case 'D':
                if (direction != LEFT)
                {
                    direction = RIGHT;
                }
                break;
            }
        }

        updateSnake(&snake, direction, &food);

        if (snake.head.x == 0 || snake.head.x == WIDTH + 1 ||
            snake.head.y == 0 || snake.head.y == HEIGHT + 1)
        {
            gameover = 1;
        }

        for (int i = 0; i < snake.length; i++)
        {
            if (snake.head.x == snake.tail[i].x && snake.head.y == snake.tail[i].y)
            {
                gameover = 1;
                break;
            }
        }

        if (food.eaten)
        {
            generateFood(&food, snake);
            score++;
        }

        Sleep(100);
    }

    system("cls");
    printf("Game Over\n");
    printf("Score: %d\n", score);

    return score;
}
