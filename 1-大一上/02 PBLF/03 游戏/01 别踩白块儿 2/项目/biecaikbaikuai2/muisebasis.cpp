#include "sumup.h"
#include "musicbasis.h"
FILE* file1;
FILE* file2;
FILE* file3;
FILE* file4;

FILE* file;//�����ļ�
// ������Ӧ��Ƶ��ӳ���
const char* notes[] = { "C3,", "C3#", "D3,", "D3#", "E3,", "F3,", "F3#", "G3,", "G3#", "A3,", "A3#", "B3,",
				  "C4,", "C4#", "D4,", "D4#", "E4,", "F4,", "F4#", "G4,", "G4#", "A4,", "A4#", "B4,",
				  "C5,", "C5#", "D5,", "D5#", "E5,", "F5,", "F5#", "G5,", "G5#", "A5,", "A5#", "B5," };

double frequencies[]; 
void playNote(char* note, int duration) {//�������ź���
	// ����������ӳ����е�λ��
	int index = -1;
	for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); ++i) {
		if (strcmp(notes[i], note) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		// ������Ч����
		fprintf(stderr, "Invalid note: %s\n", note);
		return;
	}

	// ����������Ӧ��Ƶ��
	double frequency = frequencies[index];

	// ��������
	Beep(frequency * fre, duration * spe);
}