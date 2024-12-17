#include <graphics.h>
#include <iostream>
#include <string>
using namespace std;

//��ʧ�ľ�����1
int index_x = 0;
int index_y = 0;

char board_data[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'}
};

char current_piece = 'O';

//���ָ�������ӵ�����Ƿ��ʤ
bool CheckWin(char c)
{
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
}

//��⵱ǰ�Ƿ����ƽ��
bool CheckDraw()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board_data[i][j] == '-')
			{
				return false;
			}
		}
	}

	return true;
}

//������������
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//��������
void DrawPiece()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (board_data[i][j])
			{
			case 'O':
				circle(200 * j + 100, 200 * i + 100, 70);
				break;
			case 'X':
				line(200 * j + 40, 200 * i + 40, 200 * (j + 1) - 40, 200 * (i + 1) - 40);
				line(200 * (j + 1) - 40, 200 * i + 40, 200 * j + 40, 200 * (i + 1) - 40);
				break;
			case '-':
				break;
			}
		}
	}
}

//������ʾ��Ϣ
void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ��������: %c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}

//1ģʽ���õĺ������ṹ��
struct piece  //ѭ�����д���������Ϣ
{
	int data[4][2] = {};
	int front = 0;
	int rear = 0;
	int count = 0;
}playO, playX;

bool Fallen_fruit = false; //falseΪ��ǰ���δ���ӣ�trueΪ��ǰ���������

//��¼���ӵ��ͷ�˳���Լ���Ϣ��ɾ������
void deletepiece()
{
	if (current_piece == 'O')
	{
		playO.data[playO.rear][0] = index_y;
		playO.data[playO.rear][1] = index_x;
		playO.rear = (playO.rear + 1) % 4;
		playO.count++;
	}
	else
	{
		playX.data[playX.rear][0] = index_y;
		playX.data[playX.rear][1] = index_x;
		playX.rear = (playX.rear + 1) % 4;
		playX.count++;
	}

	//ɾ������
	if (current_piece == 'O' && playO.count >= 4)
	{
		//clearcircle(200 * piece[0][1] + 100, 200 * piece[0][2] + 100, 95);
		board_data[playO.data[playO.front][0]][playO.data[playO.front][1]] = '-';
		playO.front = (playO.front + 1) % 4;
		playO.count--;
	}
	else if (current_piece == 'X' && playX.count >= 4)
	{
		//clearcircle(200 * piece[1][1] + 100, 200 * piece[1][2] + 100, 95);
		board_data[playX.data[playX.front][0]][playX.data[playX.front][1]] = '-';
		playX.front = (playX.front + 1) % 4;
		playX.count--;
	}
}

//���Ƽ�����ʧ������
void DrawPiece_disappeared()
{
	if (playX.count >= 3)
	{
		circle(200 * playX.data[playX.front][1] + 100, 200 * playX.data[playX.front][0] + 100, 100);
	}

	if (playO.count >= 3)
	{
		line(200 * playO.data[playO.front][1], 200 * playO.data[playO.front][0], 200 * (playO.data[playO.front][1] + 1), 200 * (playO.data[playO.front][0] + 1));
		line(200 * (playO.data[playO.front][1] + 1), 200 * playO.data[playO.front][0], 200 * playO.data[playO.front][1], 200 * (playO.data[playO.front][0] + 1));
	}
}

//���¿�ʼ��Ϸ
void retry()
{
	memset(board_data, '-', sizeof(char) * 9);
	memset(playO.data, 0, sizeof(playO.data));
	playO.count = playO.front = playO.rear = 0;
	memset(playX.data, 0, sizeof(playX.data));
	playX.count = playX.front = playX.rear = 0;
	current_piece = 'O';
}


int main(void)
{
	//��ʧ�ľ�����2
	//ѡ��ģʽ
	system("color FC"); // ��ɫ��Ϊ����ɫ
	cout << "��ʧ�ľ����� �汾: 1.3" << endl;
	cout << "����:olľ����lo" << endl;
	cout << "QQ:1613661434" << endl;
	cout << "��������ָ��ģʽ" << endl;
	cout << "0Ϊ���澮����" << endl;
	cout << "1Ϊ��ʧ�ľ�����(����ʾ)" << endl;
	cout << "2Ϊ��ʧ�ľ�����(����ʾ)" << endl;
	cout << "��ѡ��ģʽ:" << endl;
	char m = 0;
	string mtemp = {};
FLAG:
	getline(cin,mtemp);
	m = mtemp[0];
	if (m != '0' && m != '1' && m != '2')
	{
		cout << "���ֲ��ԣ�����������:" << endl;
		goto FLAG;
	}

	initgraph(600, 600);

	ExMessage msg;

	BeginBatchDraw(); //��ʼ������ͼ
	bool running = true;
	while (running)
	{
		DWORD start_time = GetTickCount(); //��ȡһ��ѭ���Ŀ�ͷʱ��

		while (peekmessage(&msg))
		{
			//������������µ���Ϣ
			if (msg.message == WM_LBUTTONDOWN)
			{
				//������λ��
				int x = msg.x;
				int y = msg.y;

				index_x = x / 200;
				index_y = y / 200;

				//��������
				if (board_data[index_y][index_x] == '-')
				{
					board_data[index_y][index_x] = current_piece;
					Fallen_fruit = true; //trueΪ��ǰ���������
					//�л���������
					if (current_piece == 'O')
						current_piece = 'X';
					else
						current_piece = 'O';
				}
			}
		}
		cleardevice(); //��ջ���

		//����
		DrawBoard();
		//���ѡ����1ģʽ�ҵ�ǰ��������ӣ������deletepiece����
		if (m >= '1' && Fallen_fruit)
		{
			deletepiece();
			Fallen_fruit = false; //����Ϊfalse����ʾΪ��ǰ���Ϊ����
		}

		DrawPiece();
		if (m == '2') DrawPiece_disappeared(); //���ѡ����2ģʽ������Ƽ�����ʧ������

		DrawTipText();

		FlushBatchDraw();

		if (CheckWin('X'))
		{
			if (MessageBox(GetHWnd(), _T("X ��һ�ʤ"), _T("��Ϸ����"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}
		else if (CheckWin('O'))
		{
			if (MessageBox(GetHWnd(), _T("O ��һ�ʤ"), _T("��Ϸ����"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}
		else if (CheckDraw())
		{
			if (MessageBox(GetHWnd(), _T("ƽ��"), _T("��Ϸ����"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}

		DWORD end_time = GetTickCount(); //��ȡһ��ѭ���Ľ�βʱ��
		DWORD delta_time = end_time - start_time; //��β-��ͷ�ó���һ��ѭ�����õ�ʱ��

		if (delta_time < 1000 / 60) //������60֡���Լ���CPUռ��
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

	return 0;
}