#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#define max 20
int print()//菜单
{
	int x;
	printf("1.查看所有房间\n");
	printf("2.办理入住\n");
	printf("3.办理退房\n");
	printf("4.查询房间信息\n");
	printf("5.查询客户信息\n");
	printf("6.显示空闲房间\n");
	printf("7.保存数据\n");
	printf("8.退出系统\n");
	scanf("%d", &x);
	return x;
}
typedef struct 
{
	int id;
	int type;
	int price;
	int state;
}room;
typedef struct
{
	int phone;
	int year;
	char name[max];
}custome;
custome guest[max];
room rooms[max];
void intirooms()//给每个房间初始化
{
	for (int i = 0; i < max; i++)
	{
		rooms[i].id = 101 + i;
		rooms[i].state = 0;
		if (i < 10)
		{
			rooms[i].type = 1;
			rooms[i].price = 200;
		}
		else
		{
			rooms[i].type = 2;
			rooms[i].price = 300;
		}
	}
}
void transfor(int a)//对房间是否有人state(0和1)识别
{
	if (a == 1)
	{
		printf("已入住\n");
	}
	else
	{
		printf("空闲\n");
	}
}
void checkrooms()//查看所有房间
{
	for (int i = 0; i < max; i++)
	{
		printf("房间号：%d\n类型是%d人房\n价格：%d\n", rooms[i].id, rooms[i].type, rooms[i].price);
		transfor(rooms[i].state);
	}
}

int check_in()//办理入住
{
	int i,j;
    input_room:
	printf("请输入入住房间号:");
	scanf("%d", &i);
	i -= 101;
	if (rooms[i].state == 0 && i < max && i >= 0)
	{
		rooms[i].state = 1;
		printf("请输入您的手机号码后四位\n");
		scanf("%d", &guest[i].phone);
		printf("请输入您的年龄\n");
		scanf("%d", &guest[i].year);
		printf("请输入您的名字\n");
		scanf("%s", guest[i].name);
		printf("入住成功\n");
		return 1;
	}
	else
	{
		printf("入住失败\n");
		printf("1.再次选择\n");
		printf("2.退出系统\n");
		scanf("%d", &j);
		if (j == 1)
		{
			goto input_room;
		}
		else
		{
			printf("已退出\n");
			return 0;
		}
	}
}
void checkout()//退房
{
	int x;
	char s[50];
    one_:
	printf("请输入要退房间号:");
	scanf("%d", &x);
	x -= 101;
	printf("请输入登记人名字:");
	scanf("%s", s);
	if (rooms[x].state == 1 && strcmp(guest[x].name, s) == 0&&(x< max&&x>= 0))
	{
		printf("验证成功\n");
		rooms[x].state = 0;
		memset(guest[x].name, 0, sizeof(guest[x].name));
		printf("退房成功\n");
	}
	else
	{
		printf("验证失败,请重新输入\n");
		goto one_;
	}
}
void check_information()//查看房间信息
{
	int x;
    next_:
	printf("请输入要查看房间号:");
	scanf("%d", &x);
	x -= 101;
	if (x < max && x >= 0)
	{
		printf("房间号:%d\n 房间类型:%d\n 房间价格:%d\n", rooms[x].id, rooms[x].type, rooms[x].price);
		transfor(rooms[x].state);
	}
	else
	{
		printf("输入错误,请重新输入\n");
		goto next_;
	}
}
void check_guest()//查看客户信息
{
	int x;
    next_:
	printf("请输入房间号:");
	scanf("%d", &x);
	x -= 101;
	if (x < max && x >= 0)
	{
		printf("客户名:%s\n 客户年龄:%d\n 客户手机号后四位:%d\n", guest[x].name, guest[x].year, guest[x].phone);
	}
	else
	{
		printf("输入错误,请重新输入\n");
		goto next_;
	}
}
void displayroom()
{
	for (int i = 0; i < max; i++)
	{
		if (rooms[i].state == 0)
		{
			printf("[%d为空闲]\n ", i + 101);
		}
	}
}
void saveRoom()
{
	FILE* fp = fopen("room.txt", "w");

	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	for (int i = 0; i < max; i++)
	{
		fprintf(fp, "%d %d %d %d\n",
			rooms[i].id,
			rooms[i].type,
			rooms[i].price,
			rooms[i].state);
	}
	fclose(fp);
	printf("房间数据保存成功\n");
}
void loadRoom()
{
	FILE* fp = fopen("room.txt", "r");
	if (fp == NULL)
	{
		printf("暂无历史数据\n");
		return;
	}
	for (int i = 0; i < max; i++)
	{
		fscanf(fp, "%d%d%d%d",
			&rooms[i].id,
			&rooms[i].type,
			&rooms[i].price,
			&rooms[i].state);
	}
	fclose(fp);
	printf("房间数据读取成功\n");
}
void saveGuest()
{
	FILE* fp = fopen("guest.txt", "w");

	if (fp == NULL)
	{
		printf("客户文件打开失败\n");
		return;
	}

	for (int i = 0; i < max; i++)
	{
		if (rooms[i].state == 1)
		{
			fprintf(fp, "%d %d %d %s\n",
				i,
				guest[i].phone,
				guest[i].year,
				guest[i].name);
		}
	}
	fclose(fp);
	printf("客户数据保存成功\n");
}
void loadGuest()
{
	FILE* fp = fopen("guest.txt", "r");
	if (fp == NULL)
	{
		printf("暂无客户数据\n");
		return;
	}
	int i = 0;
	while (fscanf(fp, "%d %d %d %s",
		&i,
		&guest[i].phone,
		&guest[i].year,
		guest[i].name) != EOF)
	{
		;
	}
	fclose(fp);
	printf("客户数据读取成功\n");
}
int main()
{
	intirooms();
	loadRoom();
	loadGuest();
	while (1)
	{
		int x = print();
		switch (x)
		{
		case 1://查看所有房间
			checkrooms();
			break;
		case 2://办理入住
			check_in();
			break;
		case 3://办理退房
			checkout();
			break;
		case 4://查询房间信息
			check_information();
			break;
		case 5://查询客户信息
			check_guest();
			break;
		case 6://显示空闲房间
			displayroom();
			break;
		case 7://保存数据
			saveRoom();
			saveGuest();
			printf("保存完成");
			break;
		case 8://退出系统
			saveRoom();
			saveGuest();
			printf("使用完成，欢迎下次使用\n");
			return 0;
		default:
			printf("输入错误\n");
		}
	}
	return 0;
}