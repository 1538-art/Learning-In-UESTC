
#ifndef _MAZE_GAME_MAIN_H_
#define _MAZE_GAME_MAIN_H_

//������ת��Ϊʵ��λ��
#define transfer_pos(x) (x * 30 + 20)
//��ʵ��λ��ת��Ϊ����
#define retransfer_pos(x) ((x - 20) / 30)

#define ISWALL 1
#define ISROAD 0
#define ISENTRY 2
#define ISEXIT 3

#define LEVEL_1_NUM 10
#define LEVEL_2_NUM 15
#define LEVEL_3_NUM 18

typedef struct player_t {
	char name[256];
	int level;
	int step;
	int second;
} player_t, *pplayer_t;

#endif
