#include  "Apps/SystemTask.h"

uint8 SERVO_MAPPING[10] = { 1,2,3,4,5,6,7,8,9,10 };

int abs(int shu);//����ֵ

int Init(); //��ʼ��
int Initaction();//��ʼ������ֱ��������
void Defaction();//Ĭ�϶�����̨��Ĭ�϶�����
void Move(int MoveSpeed, int turn);//�˶����� goʱSpeedΪ��ǰ����Style��left right go���ֱ�Ϊ��ת��תֱ��
void GetMove(int GetSpeed, int Stop, int sa);//��,StopΪtrueʱ��ʾ������ź�ʱ��ֹ��
void EndMove(int ST);//ֹͣ�˶�
void Moves(int MovesSpeed, int Stime);//ǰ�������ٶȡ�ʱ�䣩
void Switch();//����
void Getstage();//��̨
void lubo();//�˲�
int SStand();//������״̬����
int Edge();//����Ե�͵���
void StandA();//ǰ����
void StandB();//������
void TestMove();//�ƶ�����
void Attack1();//��������1
void SetGray();//�Ҷȱ궨
int daobian();//���߼��
void doit();//û������ĳ���ִ��

int goback = 0;//����Ե��

int AD = 0;//ADת��

int IO4 = 0;//����
int IO5 = 0;//����
int IO6 = 0;//����
int IO7 = 0;//ǰ��
int IO8 = 0;//ǰ��
int IO9 = 0;//ǰ��

int AD0 = 0;//ͷ
int AD1 = 0;//�ұ�
int AD2 = 0;//ǰ
int AD3 = 0;//���
int AD4 = 0;//���
int AD5 = 0;//�ҶȺ�
int AD6 = 0;//�Ҷ�ǰ
int AD7 = 0;


int iAD5 = 0;//��Ҷȱ궨
int iAD6 = 0;//ǰ�Ҷȱ궨


#define c 30  //doit ���ѭ������
			 /*********************************************************************/

#define dAD 100  
#define sAD 100//��Ե�Ҷ�

			 /************************************************************************/
#define left 1 
#define right 2
#define bleft 3 
#define bright 4
#define go 3
#define true 1
#define false 0
#define no 1  //û��
#define back 2  //��
#define front 3 //ǰ��
#define others 4  //����״̬
#define chaoqian 1
#define chaohou 2
#define bianyuan 1
#define nodiren 0
#define qianbianyuan 2
#define houbianyuan 3
#define zuobianyuan 12
#define youbianyuan 13
#define qianzuodaobian 4
#define qianyoudaobian 5
#define houzuodaobian 6
#define houyoudaobian 7
#define zuoqianjiao 8
#define zuohoujiao 9
#define youqianjiao 10 
#define youhoujiao 11

#define attack 9
#define qianbian 14
#define zuobian 15
#define youbian 16
#define houbian 17

int Speed = 0;//�ٶ�ֵ
int State = 1;//�㵹״̬��Ĭ��1û��
int nEdge = 0;//��Ե��ʼ̬
int k = 0;
int u;
int x = 0;
int AA = 1;
/*
************************************************
�������ұ�Ϊ���9�ţ�ǰ��Ϊ-������+
�������ұ�Ϊ���10�ţ�ǰ��Ϊ+������-
�����ID������� 1���� 2���� 3
�����ID���ұ��� 4, �� 5���� 6
�����ID������ 7������ 8
*************************************************
����ٶȷ�Χ��-1023~+1023��
����Ƕȷ�Χ��0~+1023����λ512 5��540Ϊ�м�λ��
*************************************************
*/

int main()
{
	Init(); //��ʼ��
			//SetGray();//�Ҷȱ궨
	Initaction();//��ʼ����
	Switch();//����
	Getstage();//��̨
	Defaction();//Ĭ�϶���
	while (true)
	{
		
		State = SStand();//����㵹
		switch (State)
		{
		case no:
			//AA = MFGetDigiInput(10);
			//if (AA == 0)
			//{
			//	Switch();//����
			//	Getstage();
			//}
			doit();
			break;
		case back:
			Move(0, 0);
			DelayMS(100);
			StandB();
			break;
		case front:
			Move(0, 0);
			DelayMS(100);
			StandA();
			break;
			/*case others:
			break;*/
		}
		/*	if (goback == 0)
		{
		if (Speed <= 250)
		{
		GetMove(500, true, 50);
		}
		Move(500, 0);
		DelayMS(10);
		}
		else if (goback == 1)
		{
		EndMove(30);
		GetMove(-400, false, 50);
		Move(-500, 400);
		DelayMS(800);
		EndMove(30);
		GetMove(500, false, 50);
		Move(500, 0);
		DelayMS(500);
		}*/
	}
}

void doit()//û���������ִ��
{
	nEdge = Edge();//���λ��
	switch (nEdge)
	{
	case houbianyuan:
		k = 0;
		for (u = 0; u < 25; u++)
		{//ǰ��
			if (u<1)
			{
				EndMove(30);
			}
			Move(400, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		//��ת         
		if (x == 0)
		{
			for (u = 0; u < c; u++)
			{//ǰ��
				MFSetServoRotaSpd(9, 0);
				MFSetServoRotaSpd(10, 600);
				MFServoAction();
				DelayMS(20);
				if (daobian() == 1)
				{
					break;
				}
			}
			x = 1;
		}
		else if (x == 1)
		{
			for (u = 0; u < c; u++)
			{//ǰ��
				MFSetServoRotaSpd(9, -600);
				MFSetServoRotaSpd(10, 0);
				MFServoAction();
				DelayMS(20);
				if (daobian() == 1)
				{
					break;
				}
			}
			x = 0;
		}
		break;
	case qianbianyuan:
		k = 0;
		for (u = 0; u < 25; u++)
		{//	//����
			if (u<1)
			{
				EndMove(30);
			}
			Move(-550, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 0)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{////��ת
			MFSetServoRotaSpd(9, 0);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case zuobianyuan:
		k = 0;
		for (u = 0; u < c; u++)
		{//	//��ת
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, 0);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{//ǰ��
			Move(400, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case youbianyuan:
		k = 0;
		for (u = 0; u < c; u++)
		{//	//��ת
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, -600);
			MFSetServoRotaSpd(10, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{//ǰ��
			Move(400, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case qianzuodaobian:
		k = 0;
		for (u = 0; u < 50; u++)
		{//����   
			if (u<1)
			{
				EndMove(30);
			}
			Move(-550, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 0)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{//��ת 
			MFSetServoRotaSpd(9, 0);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case qianyoudaobian:
		k = 0;
		for (u = 0; u < 20; u++)
		{////����
			if (u<1)
			{
				EndMove(30);
			}
			Move(-550, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 0)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{	//��ת      
			MFSetServoRotaSpd(9, -600);
			MFSetServoRotaSpd(10, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		};
		break;
	case houzuodaobian:
		k = 0;
		for (u = 0; u < 50; u++)
		{//ǰ��
			if (u<1)
			{
				EndMove(30);
			}
			Move(400, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{	//��ת   
			MFSetServoRotaSpd(9, 0);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case houyoudaobian:
		k = 0;
		for (u = 0; u < 25; u++)
		{//ǰ��
			if (u<1)
			{
				EndMove(30);
			}
			Move(400, 0);;
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		for (u = 0; u < c; u++)
		{//��ת     
			MFSetServoRotaSpd(9, -600);
			MFSetServoRotaSpd(10, 0);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case zuoqianjiao:
		k = 0;
		for (u = 0; u < c; u++)
		{//������ת  
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, 600);
			MFSetServoRotaSpd(10, -400);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 0)
			{
				break;
			}
		}
		break;
	case zuohoujiao:
		k = 0;
		for (u = 0; u < c; u++)
		{//ǰ����ת  
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, -400);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case youqianjiao:
		k = 0;
		for (u = 0; u < c; u++)
		{//������ת 
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, 400);
			MFSetServoRotaSpd(10, -600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 0)
			{
				break;
			}
		}
		break;
	case youhoujiao:
		k = 0;
		for (u = 0; u < c; u++)
		{//ǰ����ת   
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, -600);
			MFSetServoRotaSpd(10, 400);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case nodiren:
		/*k++;
		if (k <= 100)
		{*/
		if (Speed <= 250)
		{
			GetMove(500, true, 50);
		}
		Move(500, 0);
		DelayMS(15);
		//}
		/*else if (k>100)
		{
		Move(100, 500);
		DelayMS(15);
		if (k >= 140)
		{
		k = 0;
		}
		}*/
		break;
	case qianbian:
		k = 0;
		//ǰ�Ҷ�
		//����ǰ������������
		EndMove(25);
		Attack1();
		for (u = 0; u < 15; u++)
		{//ǰ��  
			if (u<1)
			{
				GetMove(1000, true, 20);
			}
			MFSetServoRotaSpd(9, -1000);
			MFSetServoRotaSpd(10, 1000);
			MFServoAction();
			DelayMS(20);
			Speed = 1000;
			if (daobian() == 1 || MFGetDigiInput(8) == 1)
			{
				EndMove(25);
				break;
			}
		}
		//ǰ��
		EndMove(30);
		Defaction();
		break;
	case zuobian:
		//ǰ�Ҷ�
		//ǰ����ת
		k = 0;
		EndMove(25);
		for (u = 0; u < 15; u++)
		{//ǰ����ת   
			if (u < 1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, -600);
			MFSetServoRotaSpd(10, -600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
	case youbian:
		//ǰ�Ҷ�
		//ǰ����ת
		k = 0;
		EndMove(25);
		for (u = 0; u < 15; u++)
		{//ǰ����ת   
			if (u<1)
			{
				EndMove(30);
			}
			MFSetServoRotaSpd(9, 600);
			MFSetServoRotaSpd(10, 600);
			MFServoAction();
			DelayMS(20);
			if (daobian() == 1)
			{
				break;
			}
		}
		break;
		//case houbian:
		//	k = 0;
		//	//ǰ�Ҷ�
		//	//����ǰ������������
		//	EndMove(30);
		//	MFSetServoRotaSpd(9, 600);
		//	MFSetServoRotaSpd(10, -600);
		//	MFServoAction();
		//	DelayMS(200);
		//	//Attack1;
		//	//ǰ��
		//	MFSetServoRotaSpd(9, 400);
		//	MFSetServoRotaSpd(10, -400);
		//	MFServoAction();
		//	DelayMS(200);
		//	break;
	}
}
int Init() //��ʼ��
{
	MFInit();
	DelayMS(1000);
	MFSetPortDirect(0x0C0F);// 0x00000C0F
	DelayMS(1000);
	MFInitServoMapping(&SERVO_MAPPING[0], 10);
	MFSetServoMode(1, 0);
	MFSetServoMode(2, 0);
	MFSetServoMode(3, 0);
	MFSetServoMode(4, 0);
	MFSetServoMode(5, 0);
	MFSetServoMode(6, 0);
	MFSetServoMode(7, 0);
	MFSetServoMode(8, 0);
	MFSetServoMode(9, 1);
	MFSetServoMode(10, 1);
	DelayMS(500);
	return 0;
}

int Initaction() //��ʼ������ֱ��������
{
	MFSetServoPos(1, 478, 512);
	MFSetServoPos(2, 526, 512);
	MFSetServoPos(3, 507, 512);
	MFSetServoPos(4, 532, 512);
	MFSetServoPos(5, 531, 512);
	MFSetServoPos(6, 529, 512);
	MFSetServoPos(7, 509, 512);
	MFSetServoPos(8, 531, 512);
	MFSetServoRotaSpd(9, 0);
	MFSetServoRotaSpd(10, 0);
	MFServoAction();
	DelayMS(1000);
	return 0;
}

void Getstage()//��̨
{
	Move(0, 0);
	DelayMS(20);
	MFSetServoPos(1, 489, 512);
	MFSetServoPos(2, 523, 512);
	MFSetServoPos(3, 908, 512);
	MFSetServoPos(4, 535, 512);
	MFSetServoPos(5, 516, 512);
	MFSetServoPos(6, 927, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(7, 185, 512);
	MFSetServoPos(8, 845, 512);
	MFServoAction();
	DelayMS(1000);
	Moves(700, 550);//��̨�ٶȡ�ʱ������
	MFSetServoPos(7, 530, 512);
	MFSetServoPos(8, 507, 512);
	MFServoAction();
	DelayMS(200);
}

void Moves(int MovesSpeed, int Stime)//��̨�ƶ�����
{
	GetMove(350, false, 70);
	while (true)
	{
		if (MFGetAD(4)<400)
		{
			break;
		}
	}
	GetMove(MovesSpeed, false, 200);
	Move(MovesSpeed, 0);
	MFServoAction();
	DelayMS(Stime);
	EndMove(50);
}

void GetMove(int GetSpeed, int Stop, int sa)
{
	int i = 0;
	int times = 0;
	times = abs((GetSpeed - Speed) / 50);
	for (i = 0; i <= times; i++)
	{
		MFSetServoRotaSpd(9, -Speed);
		MFSetServoRotaSpd(10, Speed);
		MFServoAction();
		DelayMS(sa);
		if (GetSpeed>0)
		{
			Speed += 50;
		}
		else if (GetSpeed <= 0)
		{
			Speed -= 50;
		}

		if (Stop == true)
		{
			if (MFGetDigiInput(8) == true)
			{
				break;
			}
			else
			{

			}
		}
		else
		{

		}

	}
}

int abs(int shu)
{
	if (shu >= 0)
	{
		return shu;
	}
	else
	{
		return -shu;
	}
}


void EndMove(int ST)
{
	int i = 0;
	int times = 0;
	times = abs(Speed / 70);
	for (i = 0; i <= times; i++)
	{
		MFSetServoRotaSpd(9, -Speed);
		MFSetServoRotaSpd(10, Speed);
		MFServoAction();
		DelayMS(ST);
		if (Speed>0)
		{
			Speed -= 70;
		}
		else if (Speed <= 0)
		{
			Speed += 70;
		}
	}
	MFSetServoRotaSpd(9, 0);
	MFSetServoRotaSpd(10, 0);
	MFServoAction();
	DelayMS(10);
	Speed = 0;
}



void TestMove()
{
	if (MFGetDigiInput(8) == false)
	{
		GetMove(500, true, 70);
		while (MFGetDigiInput(8) == false)
		{
			Move(500, 0);
		}
		EndMove(30);
	}
	else
	{
		Move(0, 0);
	}
}

void Move(int MoveSpeed, int turn)//�˶�����
{
	MFSetServoRotaSpd(9, -MoveSpeed);
	MFSetServoRotaSpd(10, MoveSpeed + turn);
	Speed = MoveSpeed;

}

void Defaction()//Ĭ�϶�����̨�ϣ�
{
	MFSetServoPos(7, 530, 512);
	MFSetServoPos(8, 507, 512);
	MFServoAction();
	DelayMS(150);
	MFSetServoPos(1, 565, 512);
	MFSetServoPos(2, 703, 512);
	MFSetServoPos(3, 750, 512);
	MFSetServoPos(4, 432, 512);
	MFSetServoPos(5, 355, 512);
	MFSetServoPos(6, 750, 512);
	MFServoAction();
	DelayMS(500);
}

void Switch()//����
{
	while (true)
	{
		if (MFGetAD(0) >= 450) break;
	}
}

int SStand()//������״̬����
{
	int i = 0;
	AD = 0;
	AD4 = 0;
	AD7 = 0;
	for (i = 0; i <20; i++)
	{
		AD4 += MFGetAD(4);
		AD7 += MFGetAD(7);
	}
	AD4 = AD4 / 20;
	AD7 = AD7 / 20;
	if (AD4 >= 200 && AD4 <= 700)
	{
		return no;		//û�е�
	}
	else if (AD4 < 200)
	{
		if (AD7 > 200)
		{
			return back;		//����
		}
		else
		{
			return no;
		}
	}
	else if (AD4 > 700)
	{
		if (AD7 > 200)
		{
			return front;		//ǰ��
		}
		else
		{
			return no;
		}
	}
	//else
	//{
	//	return others;		//��Ե״̬
	//}
}

void SetGray()//�궨�Ҷ�
{
	int i = 0;
	for (i = 0; i < 200; i++)
	{
		iAD5 += MFGetAD(5);
		iAD6 += MFGetAD(6);
	}
	iAD5 = iAD5 / 200;//��Ҷ�	
	iAD6 = iAD6 / 200;//ǰ�Ҷ�
}

int Location()
{
	AD5 = MFGetAD(5);
	AD6 = MFGetAD(6);
	if (AD5 - AD6 >= dAD)
	{
		return chaohou;
	}
	else if (AD5 - AD6 <= -dAD)
	{
		return chaoqian;
	}
	else
	{
		return others;
	}
}

void lubo()//�˲�
{
	AD0 = 0;
	AD1 = 0;
	AD2 = 0;
	AD3 = 0;

	AD5 = 0;
	AD6 = 0;

	IO4 = 0;
	IO5 = 0;
	IO6 = 0;
	IO7 = 0;
	IO8 = 0;
	IO9 = 0;
	int i = 0;
	for (i = 0; i < 50; i++)
	{


		AD1 += MFGetAD(1);
		AD2 += MFGetAD(2);
		AD3 += MFGetAD(3);
		AD0 += MFGetAD(0);

		AD5 += MFGetAD(5);
		AD6 += MFGetAD(6);
	}

	IO4 = MFGetDigiInput(4);
	IO5 = MFGetDigiInput(5);
	IO6 = MFGetDigiInput(6);
	IO7 = MFGetDigiInput(7);
	IO8 = MFGetDigiInput(8);
	IO9 = MFGetDigiInput(9);

	AD1 = AD1 / 50;
	AD2 = AD2 / 50;
	AD3 = AD3 / 50;
	AD0 = AD0 / 50;
	/*AD5 = AD5 / 50;
	AD6 = AD6 / 50;

	if (AD5 <= iAD5 || AD6 <= iAD6)
	{
	goback = 1;
	}
	else
	{
	goback = 0;
	}*/
	/*if (IO4 >= 8)
	{
	IO4 = 1;
	}
	else if (IO4 < 8)
	{
	IO4 = 0;
	}
	if (IO5 >= 8)
	{
	IO5 = 1;
	}
	else if (IO5 < 8)
	{
	IO5 = 0;
	}
	if (IO6 >= 8)
	{
	IO6 = 1;
	}
	else if (IO6 < 8)
	{
	IO6 = 0;
	}
	if (IO7 >= 8)
	{
	IO7 = 1;
	}
	else if (IO7 < 8)
	{
	IO7 = 0;
	}
	if (IO8 >= 8)
	{
	IO8 = 1;
	}
	else if (IO8 < 8)
	{
	IO8 = 0;
	}
	if (IO9 >= 8)
	{
	IO9 = 1;
	}
	else if (IO9 < 8)
	{s
	IO9 = 0;
	}*/
}


int daobian()//��Ե��⣬�ش��Ƿ񵽱ߣ�1ǰ���ߡ�0�󵽱�
{
	lubo();
	if (((IO7 == 1) || (IO9 == 1)) && ((IO4 == 0) || (IO6 == 0)))
	{
		return 1;
	}
	else if (((IO7 == 0) || (IO9 == 0)) && ((IO4 == 1) || (IO6 == 1)))
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

int Edge()//����Ե�͵���
{
	lubo();
	//if (AD5 <= sAD || AD6 <= sAD)
	//�������
	if ((IO7 == 1) || (IO9 == 1) || (IO4 == 1) || (IO6 == 1))
	{
		//����������
		if ((IO7 == 0) && (IO9 == 0) && (IO4 == 1) && (IO6 == 1))
		{
			return houbianyuan;
		}
		//ǰ��������
		else if ((IO7 == 1) && (IO9 == 1) && (IO4 == 0) && (IO6 == 0))
		{
			return qianbianyuan;
		}
		//����������
		else if ((IO7 == 1) && (IO9 == 0) && (IO4 == 1) && (IO6 == 0))
		{
			return zuobianyuan;
		}
		//����������
		else if ((IO7 == 0) && (IO9 == 1) && (IO4 == 0) && (IO6 == 1))
		{
			return youbianyuan;
		}
		//ǰ�󵽱�
		else if ((IO7 == 1) && (IO9 == 0) && (IO4 == 0) && (IO6 == 0))
		{
			return qianzuodaobian;
		}
		//ǰ�ҵ���
		else if ((IO7 == 0) && (IO9 == 1) && (IO4 == 0) && (IO6 == 0))
		{
			return qianyoudaobian;
		}
		//���󵽱�
		else if ((IO7 == 0) && (IO9 == 0) && (IO4 == 1) && (IO6 == 0))
		{
			return houzuodaobian;
		}
		//���ҵ���
		else if ((IO7 == 0) && (IO9 == 0) && (IO4 == 0) && (IO6 == 1))
		{
			return houyoudaobian;
		}
		//��ǰ��
		else if ((IO7 == 1) && (IO9 == 1) && (IO4 == 1) && (IO6 == 0))
		{
			return zuoqianjiao;
		}
		//����
		else if ((IO7 == 1) && (IO9 == 0) && (IO4 == 1) && (IO6 == 1))
		{
			return zuohoujiao;
		}
		//��ǰ��
		else if ((IO7 == 1) && (IO9 == 1) && (IO4 == 0) && (IO6 == 1))
		{
			return youqianjiao;
		}
		//�Һ��
		else if ((IO7 == 0) && (IO9 == 1) && (IO4 == 1) && (IO6 == 1))
		{
			return youhoujiao;
		}
	}
	else
	{
		if ((IO8 == 0) /*|| (IO5 == 0)*/ || (AD3 >= 65) || (AD1 >= 65))
		{
			//ǰ���е���
			if (IO8 == 0 && AD3 <= 65 && AD1 <= 65)
			{
				return qianbian;
			}
			//����е���
			else if (IO8 == 1 && AD3 >= 65 && AD1 <= 65)
			{
				return zuobian;
			}
			//�ұ��е���
			else if (IO8 == 1 && AD1 >= 65 && AD3 <= 65)
			{
				return youbian;
			}
			//����е���
			/*	else if (IO4 == 0)
			{
			return houbian;
			}*/
		}
		else
		{
			return nodiren;
		}
		//return nobianyuan;
	}
}
void StandA()//ǰ����
{
	Defaction();
	DelayMS(1000);
	MFSetServoPos(1, 779, 512);
	MFSetServoPos(2, 511, 512);
	MFSetServoPos(3, 528, 512);
	MFSetServoPos(4, 202, 512);
	MFSetServoPos(5, 547, 512);
	MFSetServoPos(6, 531, 512);
	MFSetServoPos(7, 276, 512);
	MFSetServoPos(8, 757, 512);
	MFServoAction();
	DelayMS(1000);
	MFSetServoPos(1, 581, 512);
	MFSetServoPos(2, 517, 512);
	MFSetServoPos(3, 523, 512);
	MFSetServoPos(4, 410, 512);
	MFSetServoPos(5, 543, 512);
	MFSetServoPos(6, 528, 512);
	MFSetServoPos(7, 488, 512);
	MFSetServoPos(8, 547, 512);
	MFServoAction();
	DelayMS(1000);
	Defaction();
	//GetMove(500, true, 30);
}

void StandB()//������
{
	Defaction();
	DelayMS(1000);
	MFSetServoPos(1, 540, 512);
	MFSetServoPos(2, 198, 512);
	MFSetServoPos(3, 842, 512);
	MFSetServoPos(4, 469, 512);
	MFSetServoPos(5, 832, 512);
	MFSetServoPos(6, 855, 512);
	MFSetServoPos(7, 525, 512);
	MFSetServoPos(8, 513, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(1, 149, 512);
	MFSetServoPos(2, 164, 512);
	MFSetServoPos(3, 809, 512);
	MFSetServoPos(4, 842, 512);
	MFSetServoPos(5, 865, 512);
	MFSetServoPos(6, 858, 512);
	MFSetServoPos(7, 519, 512);
	MFSetServoPos(8, 518, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(1, 176, 512);
	MFSetServoPos(2, 166, 512);
	MFSetServoPos(3, 197, 512);
	MFSetServoPos(4, 823, 512);
	MFSetServoPos(5, 860, 512);
	MFSetServoPos(6, 254, 512);
	MFSetServoPos(7, 516, 512);
	MFSetServoPos(8, 523, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(1, 183, 512);
	MFSetServoPos(2, 501, 512);
	MFSetServoPos(3, 200, 512);
	MFSetServoPos(4, 823, 512);
	MFSetServoPos(5, 552, 512);
	MFSetServoPos(6, 249, 512);
	MFSetServoPos(7, 513, 512);
	MFSetServoPos(8, 523, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(1, 101, 512);
	MFSetServoPos(2, 503, 512);
	MFSetServoPos(3, 460, 512);
	MFSetServoPos(4, 893, 512);
	MFSetServoPos(5, 556, 512);
	MFSetServoPos(6, 509, 512);
	MFSetServoPos(7, 695, 512);
	MFSetServoPos(8, 341, 512);
	MFServoAction();
	DelayMS(500);
	MFSetServoPos(1, 213, 512);
	MFSetServoPos(2, 521, 512);
	MFSetServoPos(3, 495, 512);
	MFSetServoPos(4, 758, 512);
	MFSetServoPos(5, 512, 512);
	MFSetServoPos(6, 509, 512);
	MFSetServoPos(7, 717, 512);
	MFSetServoPos(8, 319, 512);
	MFServoAction();
	DelayMS(1000);
	MFSetServoPos(1, 478, 512);
	MFSetServoPos(2, 526, 512);
	MFSetServoPos(3, 507, 512);
	MFSetServoPos(4, 532, 512);
	MFSetServoPos(5, 531, 512);
	MFSetServoPos(6, 529, 512);
	MFSetServoPos(7, 509, 512);
	MFSetServoPos(8, 531, 512);
	MFServoAction();
	DelayMS(1000);
	MFSetServoPos(1, 556, 512);
	MFSetServoPos(2, 375, 512);
	MFSetServoPos(3, 660, 512);
	MFSetServoPos(4, 470, 512);
	MFSetServoPos(5, 634, 512);
	MFSetServoPos(6, 680, 512);
	MFSetServoPos(7, 503, 512);
	MFSetServoPos(8, 532, 512);
	MFServoAction();
	DelayMS(1000);
	Defaction();
	//	GetMove(500, true, 30);
}


void Attack1()//��������1
{
	//EndMove(30);
	MFSetServoPos(1, 674, 600);
	MFSetServoPos(2, 620, 600);
	MFSetServoPos(3, 634, 600);
	MFSetServoPos(4, 366, 600);
	MFSetServoPos(5, 438, 600);
	MFSetServoPos(6, 664, 600);
	MFSetServoPos(7, 530, 512);
	MFSetServoPos(8, 507, 512);
	MFServoAction();
	DelayMS(800);
	//GetMove(600, false, 30);
	//Move(800, 0);
	//DelayMS(500);
	//Defaction();
	//DelayMS(800);
}