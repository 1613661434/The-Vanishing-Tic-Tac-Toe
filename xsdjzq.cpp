#include <graphics.h>
#include <iostream>
#include <string>
using namespace std;
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 640
//消失的井字棋1
int index_x = 0;
int index_y = 0;

char board_data[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'}
};

char current_piece = 'O';

//检测指定的棋子的玩家是否获胜
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

//检测当前是否出现平局
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

//绘制棋盘网络
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//绘制棋子
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

//绘制提示信息
void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型: %c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}

//1模式启用的函数及结构体
struct piece  //循环队列储存落子信息
{
	int data[4][2] = {};
	int front = 0;
	int rear = 0;
	int count = 0;
}playO, playX;

bool Fallen_fruit = false; //false为当前玩家未落子，true为当前玩家已落子

//记录棋子的释放顺序以及信息并删除棋子
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

	//删除棋子
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

//绘制即将消失的棋子
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

//重新开始游戏
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
	//消失的井字棋2
	//选择模式
	system("color FC"); // 颜色改为亮红色
	cout << "消失的井字棋 版本: 1.3" << endl;
	cout << "作者:ol木子李lo" << endl;
	cout << "QQ:1613661434" << endl;
	cout << "输入数字指定模式" << endl;
	cout << "0为常规井字棋" << endl;
	cout << "1为消失的井字棋(无提示)" << endl;
	cout << "2为消失的井字棋(有提示)" << endl;
	cout << "请选择模式:" << endl;
	char m = 0;
	string mtemp = {};
FLAG:
	getline(cin,mtemp);
	m = mtemp[0];
	if (m != '0' && m != '1' && m != '2')
	{
		cout << "数字不对，请重新输入:" << endl;
		goto FLAG;
	}

	// 获取屏幕分辨率
	const int screen_width = GetSystemMetrics(SM_CXSCREEN);
	const int screen_height = GetSystemMetrics(SM_CYSCREEN);

	// 计算窗口起始坐标
	const int start_x = (screen_width - WINDOW_WIDTH) / 2;
	const int start_y = (screen_height - WINDOW_HEIGHT) / 2;

	// 创建窗口
	HWND hwnd = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	// 设置窗口位置
	SetWindowPos(hwnd, NULL, start_x, start_y,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SWP_NOZORDER | SWP_NOACTIVATE);

	ExMessage msg;

	BeginBatchDraw(); //开始批量绘图
	bool running = true;
	while (running)
	{
		int start_time = clock(); //获取一次循环的开头时间

		while (peekmessage(&msg))
		{
			//检测鼠标左键按下的消息
			if (msg.message == WM_LBUTTONDOWN)
			{
				//计算点击位置
				int x = msg.x;
				int y = msg.y;

				index_x = x / 200;
				index_y = y / 200;

				//尝试落子
				if (board_data[index_y][index_x] == '-')
				{
					board_data[index_y][index_x] = current_piece;
					Fallen_fruit = true; //true为当前玩家已落子
					//切换棋子类型
					if (current_piece == 'O')
						current_piece = 'X';
					else
						current_piece = 'O';
				}
			}
		}
		cleardevice(); //清空画面

		//绘制
		DrawBoard();
		//如果选择了1模式且当前玩家已落子，则调用deletepiece函数
		if (m >= '1' && Fallen_fruit)
		{
			deletepiece();
			Fallen_fruit = false; //更新为false，表示为当前玩家为落子
		}

		DrawPiece();
		if (m == '2') DrawPiece_disappeared(); //如果选择了2模式，则绘制即将消失的棋子

		DrawTipText();

		FlushBatchDraw();

		if (CheckWin('X'))
		{
			if (MessageBox(GetHWnd(), _T("X 玩家获胜"), _T("游戏结束"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}
		else if (CheckWin('O'))
		{
			if (MessageBox(GetHWnd(), _T("O 玩家获胜"), _T("游戏结束"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}
		else if (CheckDraw())
		{
			if (MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY) { retry(); }
			else { running = false; }
		}

		int end_time = clock(); //获取一次循环的结尾时间
		int delta_time = end_time - start_time; //结尾-开头得出这一次循环所用的时间

		if (delta_time < 17) //控制在60帧率以减少CPU占用
		{
			Sleep(17 - delta_time);
		}
	}
	EndBatchDraw();

	return 0;
}