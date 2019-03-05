#include<stdio.h>
#include<stdlib.h>
#include<limits.h> 
#include<string.h> 
#include<time.h>
#include<conio.h> 
#include<windows.h> 
#include <graphics.h>
#include<time.h>
#define maxyear1 2018   
#define minyear1 1995  
#define maxmonth1 12
#define minmonth1 01
#define maxday1 31
#define minday1 01
#define maxhour1 24
#define minhour1 01
#define maxminute1 60
#define minminute1 01
#define maxsecond1 60
#define minsecond1 01
#define maxyear2 2018   
#define minyear2 1995  
#define maxmonth2 12
#define minmonth2 01
#define maxday2 31
#define minday2 01
#define maxhour2 24
#define minhour2 01
#define maxminute2 60
#define minminute2 01
#define maxsecond2 60
#define minsecond2 01
#define maxtype 0010
#define mintype 0000

typedef struct user
{
	char name[20];
	char number[5];
	int type;
}User;
typedef struct record
{
	char number[5];
	char time0[15];
	char time1[15];
}Record;
typedef struct date
{
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
}Date;
typedef struct datenum 
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}Datenum;

typedef struct count
{
	char name[20];
	char number[5];
	int type;
	int cost;
}Count;

MOUSEMSG m;
int flag_choice =5,falg_screen=1;
//int count_down = 300;    //打印下移
int year,month;
int output_flag,a;
int flag0 =1;
int surf_minute = 0;
double charge,cost;
User s1,s2,s3;            //s1手动输入  s2程序读入，储存 
Record t1,t2,t3,t4,t5;          // t1手动输入 t2程序读入 ，储存 t4筛选 
Date d1;
Count c1;                  // 
Datenum num1,num2,num3,num4;    //num1 开始上网时间  num2结束上网时间 
void write_userfile(void);
void write_recordfile(void);
void input_userdata(void);
void input_recorddata(void); 
void string_number_transfor(char *str,int *year,int *month,int *day,int *hour,int *minute,int *second);
void number_string_transfor(char *str,int *year,int *month,int *day,int *hour,int *minute,int *second);
void output_final_data(void);
void search_userfile(char *str);
int read_userfile(char *str);  
void read_recordfile(void);
void number_transfor(char *str,int a);
void find_message(void);
void charge_way(int minute,int mun);
void cost_statistics(char *str);
void filter_data(char *str);
int timecount (char at[],char ct[],int year,int month);
int month_date(int month,int year);
int recorddata_filter(char *str1,char *str2);
void rand_data(); 

void start_menu(void);       //windows
void mouse_catch(void);
void menu1(void);
void menu2(void);
void menu3(void);
void menu4(void);
void window1(void);


int main()  
{
	initgraph(640, 480);
	start_menu();
	HWND hwnd = GetHWnd();		
	SetWindowText(hwnd, "---上网计费系统---");			// 设置窗口标题文字
	while(flag0)
	{	
 	   	mouse_catch();			// 获取一条鼠标消息
 			
	}
	return 0;
}
	
void write_userfile(void)
{
	FILE *fp;
	fp = fopen("D:\\data1.txt","a+");	
	if (fp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fprintf(fp,"%s\t%s\t%d\n",s1.name,s1.number,s1.type); 
	fclose(fp);
}
		
void write_recordfile(void)  //-------------
{
	FILE *tp;
	tp = fopen("D:\\data2.txt","a+");	
	if (tp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fprintf(tp,"%s\t%s\t%s\n",t1.number,t1.time0,t1.time1);
	fclose(tp);
}

void input_userdata(void)
{
	int i,count,now;
	int	flag1 = 0;
	char s[20];
	char a[20],h[10];
	InputBox(s, 20, "你想添加多少行数据");
	sscanf(s, "%d", &count);	
	if((count == 0)||(s[0] == '\0'))
	{
		setcolor(RGB(66,66,66));
		outtextxy(285,330, _T("无数据输入"));	
		outtextxy(240,400, _T("看来你没有数据需要添加"));	//	fillroundrect(50, 300, 600, 430, 36, 36);
	} 
	for(i=0;i<count;i++)
	{
		window1();
		sprintf(h,"%d",i+1);
		outtextxy(308,350,h);
		outtextxy(285,350, _T("第"));	
		outtextxy(320,350, _T("次输入"));	
		InputBox(s1.name, 20, "请输入你的用户名");
		InputBox(s1.number, 5, "请输入你的用户帐号");
		InputBox(a, 2, "请输入你的计费方式");
		sscanf(a, "%d", &s1.type);
		while((s1.number[3]=='\0')||((s1.type)<0)||(s1.type>4)||(atoi(s1.name))||((s1.name[0]-48) == 0)||(a[0] == '\0'))
		{
			setcolor(RGB(66,66,66));
			now = MessageBox (NULL,TEXT("格式错误,要继续吗"), TEXT("error!"),MB_YESNO);//弹出窗口 
			if(now == 7)
			{
				flag1= 1;
				break;
			}
		//	outtextxy(285,330, _T("格式错误"));
			outtextxy(240,400, _T("请重新输入你的数据"));
			InputBox(s1.name, 20, "请输入你的用户名");
			InputBox(s1.number, 5, "请输入你的用户帐号");
			InputBox(a, 2, "请输入你的计费方式");
			sscanf(a, "%d", &s1.type);
		}

		if(flag1==0)
		{
			write_userfile();
		}
		if(now == 7)
		{
			break;
		}
	}
	if((count!=0)&&(flag1==0)&&(s[0]!='\0'))
	{	
		window1();
		setcolor(RGB(255, 255, 255));
		outtextxy(180,200, _T("你的数据已添加在 D:\\data1.txt 文件中"));
	}
	else if(flag1 == 1)
	{
		window1();
		setcolor(RGB(255, 255, 255));
		outtextxy(270,200, _T("数据添加失败"));
	}
}

void input_recorddata(void)
{
	int i,count,now;
	int	flag2 = 0;
	char s[20],h[10];
	InputBox(s, 20, "你想添加多少记录");
	sscanf(s, "%d", &count);	
	if((count == 0)||(s[0]=='\0'))
	{
		setcolor(RGB(66,66,66));
		outtextxy(285,330, _T("无数据输入"));	
		outtextxy(240,400, _T("看来你没有记录需要添加"));	//fillroundrect(50, 139, 600, 289, 36, 36);
	} 
	for(i=0;i<count;i++)
	{	
		window1();
		sprintf(h,"%d",i+1);
		outtextxy(308,350,h);
		outtextxy(285,350, _T("第"));	
		outtextxy(320,350, _T("次输入"));	
		InputBox(t1.number, 5, "请输入你的用户帐号");
		InputBox(t1.time0, 15, "请输入你的上网起始时间");
		InputBox(t1.time1, 15, "请输入你的上网终止时间");
//		scanf("%s%s%s",t1.number,t1.time0,t1.time1);

		while((recorddata_filter(t1.time0,t1.time1) == 0)||(t1.number[4]!='\0')||
			(t1.time0[13]=='\0')||(t1.time0[13] =='\0')||(t1.time0[14]!='\0')||(t1.time0[14]!='\0')||(strcmp(t1.time0,t1.time1)==1)||(t1.number[3] =='\0'))
		{
			setcolor(RGB(66,66,66));
			now = MessageBox (NULL,TEXT("格式错误,要继续吗"), TEXT("error!"),MB_YESNO);//弹出窗口
			if(now == 7)
			{
				flag2=1;
				break;
			}
			outtextxy(240,400, _T("请重新输入你的数据"));
			InputBox(t1.number, 5, "请输入你的用户帐号");
			InputBox(t1.time0, 15, "请输入你的上网起始时间");
			InputBox(t1.time1, 15, "请输入你的上网终止时间");
		}
		if(flag2==0)
		{
			write_recordfile();
		}
		if(now == 7)
		{
			break;
		}
	}
	if((count!=0)&&(flag2==0)&&(s[0]!='\0'))
	{	
		window1();
		setcolor(RGB(255, 255, 255));
		outtextxy(180,200, _T("你的上网记录已添加在 D:\\data2.txt 文件中"));
	}
	else if(flag2 == 1)
	{
		window1();
		setcolor(RGB(255, 255, 255));
		outtextxy(270,200, _T("记录添加失败"));
	}
}
	
void output_final_data(void)
{
//	char s[10];
//	char i[10];
	FILE *cp;
	cp = fopen("D:\\data3.txt","a+");	
	if (cp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fprintf(cp,"%s\t%s\t%d\t%.2lf\n",s2.number,s2.name,s2.type,charge); 


	fclose(cp);

}

void search_userfile(char *str)
{
//	int i;
	FILE *fp;
	fp = fopen("D:\\data1.txt","r");	
	if (fp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fscanf(fp,"%s%s%d",s2.name,s2.number,&s2.type);	
	while(!feof(fp))
	{
		if(strcmp(str,s2.number)==0)    //找出所有的 
		{	
			cost_statistics(s2.number);        
			filter_data(s2.number);		//*
			if(output_flag == 0)
			{
				output_final_data();
				output_flag = 1;
			}                           //*
		}

		fscanf(fp,"%s%s%d",s2.name,s2.number,&s2.type);	
	}
	
	fclose(fp);
}		

void cost_statistics(char *str)
{
	charge = 0;
	cost = 0;
	FILE *fb;
	fb = fopen("D:\\data2.txt","r");
	if (fb == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}	
	
	fscanf(fb,"%s%s%s",t3.number,t3.time0,t3.time1);
//	fscanf(ft,"%s%s%d",s3.name,s3.number,&s3.type);
	while(!feof(fb))
	{
		if(strcmp(str,t3.number)==0) 
		{			
			charge_way(surf_minute,read_userfile(t3.number));	
			cost += charge;
		}
		fscanf(fb,"%s%s%s",t3.number,t3.time0,t3.time1);

	}
	charge = cost;
//	printf("%.2f\n",charge);
	fclose(fb);
}

void filter_data(char *str)
{	

	output_flag = 0;
	int output_true;
	double cost;
	FILE *tf;
	tf = fopen("D:\\data3.txt","r");
	if (tf == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}	
	
	fscanf(tf,"%s%s%d%f",s3.number,s3.name,&s3.type,&cost);
//	printf("%s\t%s\t%d\t%.2lf\n",s3.number,s3.name,s3.type,cost);
//	printf("%d\n",output_true); 

	while(!feof(tf))
	{
	
		if(strcmp(str,s3.number) == 0)     //有一样的不打印
		{	
//			printf("look %s %s\n",s3.number,str);
			output_true = 1;
		}
		else
		{
//			printf("look %s %s\n",s3.number,str);
			output_true = 0;
		}
		output_flag = output_true||output_flag; //0打印 
	
		fscanf(tf,"%s%s%d%f",s3.number,s3.name,&s3.type,&cost);
//		printf("%s\t%s\t%d\t%.2lf\n",s3.number,s3.name,s3.type,cost);

//		printf("%d\n",output_true); 
//		printf("%d\n",output_flag); 

	}
//	printf("%d\n",output_flag); 

	fclose(tf);
}

int read_userfile(char *str)  
{
	int type;
	FILE *tp;
	tp = fopen("D:\\data1.txt","r");	
	if (tp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fscanf(tp,"%s%s%d",s3.name,s3.number,&s3.type);
	while(!feof(tp))
	{
		if(strcmp(str,s3.number)==0) 
		{
			type = s3.type;				
		}
		fscanf(tp,"%s%s%d",s3.name,s3.number,&s3.type);

	}
	fclose(tp);
	
	return type;
}


void read_recordfile(void)  //-------
{
	FILE *tp;
	tp = fopen("D:\\data2.txt","r");	
	if (tp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fscanf(tp,"%s%s%s",t3.number,t3.time0,t3.time1);
	
	fclose(tp);
}
		
void string_number_transfor(char *str,int *year,int *month,int *day,int *hour,int *minute,int *second) 
{
	int i;
	for(i=0;i<4;i++)
	{
		d1.year[i] = str[i];
	}

	for(i=0;i<2;i++)
	{
		d1.month[i] = str[i+4];
	}
	
	for(i=0;i<2;i++)
	{
		d1.day[i]= str[i+6];
	}

	for(i=0;i<2;i++)
	{
		d1.hour[i] = str[i+8];
	}
	
	for(i=0;i<2;i++)
	{
		d1.minute[i] = str[i+10];
	}
	
	for(i=0;i<2;i++)
	{
		d1.second[i] = str[i+12];
	}
	
	*year = atoi(d1.year);
	*month = atoi(d1.month);
	*day = atoi(d1.day);
	*hour = atoi(d1.hour);
	*minute = atoi(d1.minute);
	*second = atoi(d1.second);

}		

void number_transfor(char *str,int a) 
{
	int i;
	sprintf(str,"%2d",a);
	for(i=0;i<2;i++)
	{
		if(str[i]==' ')
		{
			str[i]='0';
		}
	} 
	
} 
		
void number_string_transfor(char *str,int *year,int *month,int *day,int *hour,int *minute,int *second)
{
	number_transfor(d1.year,*year);
	number_transfor(d1.month,*month);
	number_transfor(d1.day,*day);
	number_transfor(d1.hour,*hour);
	number_transfor(d1.minute,*minute);
	number_transfor(d1.second,*second);
	
	int i;
	for(i=0;i<4;i++)
	{
		str[i] = d1.year[i];
	}

	for(i=0;i<2;i++)
	{
		str[i+4] = d1.month[i];
	}
	
	for(i=0;i<2;i++)
	{
		str[i+6] = d1.day[i];
	}

	for(i=0;i<2;i++)
	{
		str[i+8] = d1.hour[i];
	}
	
	for(i=0;i<2;i++)
	{
		str[i+10] = d1.minute[i];
	}
	
	for(i=0;i<2;i++)
	{
		str[i+12] = d1.second[i];
	}
}	
		
		
void find_message(void) 
{	
	int flag_in = 0;
	int flag_error=0;
	int now;
	FILE *mp;           //清空文件
	mp = fopen("D:\\data3.txt","w");	
	if (mp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口
		exit(1);
	}
	fclose(mp);
	char c[5];
	char v[3];
//	printf("\t\t\t\t\t请输入你要查询的年份和月份\t");
	InputBox(c, 5, "请输入你要查询的年份");
	InputBox(v, 3, "请输入你要查询的月份");
	sscanf(c,"%d",&year);
	sscanf(v,"%d",&month);
	while((year<= 0)||(month>12)||(month<1)||(c[0]=='\0')||(v[0]=='\0'))
	{	
		setcolor(RGB(66, 66, 66));
		now = MessageBox (NULL,TEXT("格式错误,要继续吗"), TEXT("error!"),MB_YESNO);//弹出窗口
		if(now == 7)
		{
			flag_error=1;
			break;
		}
		
		outtextxy(259,400, _T("请重新输入你的数据"));
		InputBox(c, 5, "请输入你要查询的年份");
		InputBox(v, 5, "请输入你要查询的月份");
		sscanf(c,"%d",&year);
		sscanf(v,"%d",&month);
	} 
	
	FILE *tp;
	tp = fopen("D:\\data2.txt","r");	
	if (tp == 0)
	{
		MessageBox (NULL,TEXT("文件错误"), TEXT("!!"),MB_OK);//弹出窗口											//
		exit(1);
	}
	printf("\n"); 
	fscanf(tp,"%s%s%s",t2.number,t2.time0,t2.time1);
	string_number_transfor(t2.time0,&num1.year,&num1.month,&num1.day,&num1.hour,&num1.minute,&num1.second);
	string_number_transfor(t2.time1,&num2.year,&num2.month,&num2.day,&num2.hour,&num2.minute,&num2.second);

	while(!feof(tp))
	{
		if(((num1.year < year)&&(num2.year > year))||
			((num1.year < year)&&(num2.year >= year)&&(num2.month>=month))||
				((num1.year <= year)&&(num2.year > year)&&(num1.month<=month))||
					((num1.year == year)&&(num2.year == year)&&(num1.month<=month)&&(num2.month>=month)))
		{
			surf_minute = timecount(t2.time0,t2.time1,year,month);
			flag_in = 1; 
//			printf("%d\n",surf_minute);
//			printf("%s\t%s\t%s\n",t2.number,t2.time0,t2.time1);
			search_userfile(t2.number);
		}
		
		fscanf(tp,"%s%s%s",t2.number,t2.time0,t2.time1);
		string_number_transfor(t2.time0,&num1.year,&num1.month,&num1.day,&num1.hour,&num1.minute,&num1.second);
		string_number_transfor(t2.time1,&num2.year,&num2.month,&num2.day,&num2.hour,&num2.minute,&num2.second);
	}
	fclose(tp);
	if((flag_in == 0)||(flag_error ==1))
	{
		window1();
		MessageBox (NULL,TEXT("对不起，没有你要的费用记录"), TEXT("error"),MB_OK);//弹出窗口
		start_menu();

	}
	else if(flag_error ==0)
	{
		window1();
		MessageBox (NULL,TEXT("你现在在 D:\\data3.txt 中可以看到费用记录了"), TEXT("success"),MB_OK);//弹出窗口
		start_menu();
	 } 
}

		
void charge_way(int minute,int mun)
{

	switch(mun)

	{

	case 0:

		charge=0.03*minute;

		break;

	case 1:

		if (minute<=1800)

			charge=50;

		else

			charge=50+0.03*(minute-1800);

		break;

	case 2:

			if (minute<=3600)

			charge=95;

		else

			charge=95+0.03*(minute-3600);

		break;

	case 3:

			if (minute<=9000)

			charge=200;

		else

			charge=200+0.03*(minute-9000);

		break;

	case 4:

		charge=300;

		break;
	}
	
	if(minute == 0) 
	{
		charge=0;
	}
	
}
		
		
int timecount (char at[],char ct[],int year,int month)
{	
	int year1,month1,day1,hour1,min1,sec1;
	int year2,month2,day2,hour2,min2,sec2;
	int i;
	int x;
	char bt[15],et[15];

	for(i=0;i<=13;i++)
	{	bt[i]=at[i]-48;
		et[i]=ct[i]-48;
	}
	
	year1=bt[0]*1000+bt[1]*100+bt[2]*10+bt[3];
	month1=bt[4]*10+bt[5];
	day1=bt[6]*10+bt[7];
	hour1=bt[8]*10+bt[9];
	min1=bt[10]*10+bt[11];
	sec1=bt[12]*10+bt[13];

	year2=et[0]*1000+et[1]*100+et[2]*10+et[3];
	month2=et[4]*10+et[5];
	day2=et[6]*10+et[7];
	hour2=et[8]*10+et[9];
	min2=et[10]*10+et[11];
	sec2=et[12]*10+et[13];

	switch(month)
	{	case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			x=31;break;
		case 4:
		case 6:
		case 9:
		case 11:
			x=30;break;
		case 2:
			if((year1%400==0)||(year1%4==0&&year1%100!=0))
			{
				x=29;
			}
			else
			{
				x=28;
			}
	}

	if(year==year1&&year1!=year2)
	{	if(month==month1)
		{	x=x-day1;
			x=x*24+24-hour1;
			x=--x*60+min2+60-min1;
			if(sec2>sec1)
				x++;
		
		}
		else
		{	if(month1<month)
			{x=x*24+24-hour1;
		x=--x*60+min2+60-min1;
		if(sec2>sec1)
		x++;
		}
			else
			{x=0;}
		}
	}
	
	if(year==year2&&year1!=year2)
	{	if(month==month2)
		{	x=day2;
			x=(x-1)*24+hour2;
			x=--x*60+min2+60-min1;
			if(sec2>sec1)
			x++;
		
		}
		else
		{	if(month<month2)
			{x=x*24;
		x=--x*60+min2+60-min1;
		if(sec2>sec1)
		x++;
		}
			else
			{x=0;}
		}
	}

	if(year1<year&&year<year2)
	{x=x*24;
	x=--x*60+min2+60-min1;
	if(sec2>sec1)
		x++;
	}

	if(year<year1||year>year2)
	{	x=0;}

	if(year==year1&&year1==year2)
	{	if(month1==month2&&month==month1)
		{	x=day2-day1;
			x=(x-1)*24+hour2+24-hour1;
			x=--x*60+min2+60-min1;
			if(sec2>sec1)
			x++;
		}
		if(month==month1&&month1!=month2)
			{	x=x-day1;
				x=x*24+24-hour1;
				x=--x*60+min2+60-min1;
				if(sec2>sec1)
				x++;
			}
			
		if(month==month2&&month1!=month2)
			{	x=day2;
				x=(x-1)*24+hour2;
				x=--x*60+min2+60-min1;
				if(sec2>sec1)
				x++;
			}
		
		if(month<month2&&month>month1)
			{	x=x*24;
				x=--x*60+min2+60-min1;
				if(sec2>sec1)
				x++;
			}
		if(month>month2||month<month1)
			{	x=0;
			}

	}

//	printf("%d\n",x);

	return x;
}

int month_date(int month,int year)
{
	int x;
	switch(month)
	{	case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			x=31;break;
		case 4:
		case 6:
		case 9:
		case 11:
			x=30;break;
		case 2:
			if((year%400==0)||(year%4==0&&year%100!=0))
			{
				x=29;
			}
			else
			{
				x=28;
			}
	}
	return x;
}

int recorddata_filter(char *str1,char *str2)
{
	int s;
	string_number_transfor(str1,&num3.year,&num3.month,&num3.day,&num3.hour,&num3.minute,&num3.second);
	string_number_transfor(str2,&num4.year,&num4.month,&num4.day,&num4.hour,&num4.minute,&num4.second);
	if((num3.year>0)&&(num3.year<=2018)&&(num3.month>0)&&(num3.month<=12)&&(num3.day>0)&&(num3.day<month_date(num3.month,num3.year))&&
			(num3.hour>0)&&(num3.hour<=23)&&(num3.minute>0)&&(num3.minute<60)&&(num3.second>0)&&(num3.second<60)&&
				(num4.year>0)&&(num4.year<=2018)&&(num4.month>0)&&(num4.month<=12)&&(num4.day>0)&&(num4.day<month_date(num4.month,num3.year))&&
					(num4.hour>0)&&(num4.hour<=23)&&(num4.minute>0)&&(num4.minute<60)&&(num4.second>0)&&(num4.second<60))
	{
		s = 1;				//right
	}
	else 
	{
		s =0;                //wrong
	}
	
	return s;
 } 
 
 
void rand_data()
{

	char a1[5];
	setcolor(RGB(66,66,66));
	int print_flag =0; 
    int type,numyear1,nummonth1,numday1,numhour1,numminute1,numsecond1;
	int numyear2,nummonth2,numday2,numhour2,numminute2,numsecond2;
	MessageBox (NULL,TEXT("数据生成成功"), TEXT("数据生成中. . ."),MB_OK);//弹出窗口
	outtextxy(290, 320, _T("记录如下"));
    while((recorddata_filter(t5.time0,t5.time1) == 0)||(print_flag == 0)||(type==0))
	{
		srand(time(NULL));
    	type = rand() % (maxtype - mintype) + mintype; 
		srand(time(NULL));
    	numyear1 = rand() % (maxyear1 - minyear1) + minyear1; 
		srand(time(NULL));
		nummonth1 = rand() % (maxmonth1 - minmonth1) + minmonth1;
		srand(time(NULL));
		numday1 = rand() % (maxday1 - minday1) + minday1;
		srand(time(NULL));
		numhour1= rand() % (maxhour1 - minhour1) + minhour1;
		srand(time(NULL));
		numminute1 = rand() % (maxminute1 -minminute1) + minminute1;
		srand(time(NULL));
		numsecond1 = rand() % (maxsecond1 - minsecond1) + minsecond1;
    	numyear2 = rand() % (maxyear2 - minyear2) + minyear2; 
		nummonth2 = rand() % (maxmonth2 - minmonth2) + minmonth2;
		numday2 = rand() % (maxday2 - minday2) + minday2;
		numhour2= rand() % (maxhour2 - minhour2) + minhour2;
		numminute2 = rand() % (maxminute2 -minminute2) + minminute2;
		numsecond2 = rand() % (maxsecond2 - minsecond2) + minsecond2;
		number_string_transfor(t5.time0,&numyear1,&nummonth1,&numday1,&numhour1,&numminute1,&numsecond1);
		number_string_transfor(t5.time1,&numyear2,&nummonth2,&numday2,&numhour2,&numminute2,&numsecond2);
		if(strcmp(t5.time0,t5.time1)==-1)
		{
			print_flag =1; 
		}
		
	}

	number_string_transfor(t5.time0,&numyear1,&nummonth1,&numday1,&numhour1,&numminute1,&numsecond1);
	number_string_transfor(t5.time1,&numyear2,&nummonth2,&numday2,&numhour2,&numminute2,&numsecond2);

	
	sprintf(a1, "%04d", type);
	outtextxy(180, 380, a1);
	outtextxy(250, 380, t5.time0);
	outtextxy(380, 380, t5.time1);

} 




void start_menu(void)
{

	falg_screen =1;


	for(int y1=0; y1<480; y1++)
	{
		setlinecolor(RGB(231,231,231));
		line(0, y1, 639, y1);
	}

	for(int y2=10; y2<470; y2++)
	{
		setlinecolor(RGB(205,205,205));
		line(0, y2, 639, y2);
	}

	for(int y=10; y<460; y++)
	{
		setlinecolor(RGB(255,255,255));
		line(10, y, 629, y);
	}

	for(int m=55; m<105; m++)
	{
		setlinecolor(RGB(74,74,74));
		line(245, m, 405, m);
	}
	for(int p=155; p<205; p++)
	{
		setlinecolor(RGB(74,74,74));
		line(245, p, 405, p);
	}
	for(int l=255; l<305; l++)
	{
		setlinecolor(RGB(74,74,74));
		line(245, l, 405, l);
	}
	for(int v=355; v<405; v++)
	{
		setlinecolor(RGB(74,74,74));
		line(245, v, 405, v);
	}


	for(int i=50; i<100; i++)
	{
		setlinecolor(RGB(127,127,127));
		line(240, i, 400, i);
		setbkmode(TRANSPARENT);
		setcolor(RGB(255, 255, 255));
		outtextxy(265,68, _T("用 户 资 料 录 入"));

	}




	for(int j=150; j<200; j++)
	{
		setlinecolor(RGB(127,127,127));
		line(240, j, 400, j);
		setbkmode(TRANSPARENT);
		setcolor(RGB(255, 255, 255));
		outtextxy(265,168, _T("上 网 记 录 输 入"));
	}

	for(int a=250; a<300; a++)
	{
		setlinecolor(RGB(127,127,127));
		line(240, a, 400, a);
		setbkmode(TRANSPARENT);
		setcolor(RGB(255, 255, 255));
		outtextxy(265,268, _T("上 网 费 用 查 询"));
	}

	for(int b=350; b<400; b++)
	{
		setlinecolor(RGB(127,127,127));
		line(240, b, 400, b);
		setbkmode(TRANSPARENT);
		setcolor(RGB(255, 255, 255));
		outtextxy(258,368, _T("随机生成上网记录"));
	}



	for(int g=0; g<40; g++)
	{
		setlinecolor(RGB(66,66,66));
		line(570, g, 680, g);
		
	}
	
	for(int r=4; r<36; r++)
	{
		setlinecolor(RGB(127,127,127));
		line(574, r, 676, r);
		setbkmode(TRANSPARENT);
		setcolor(RGB(255, 255, 255));
		outtextxy(590,10, _T("退出"));
	}



}

void menu1(void)
{
	cleardevice();
	window1();

	input_userdata();

}

void menu2(void)
{
	cleardevice();
	window1();
	input_recorddata();
}

void menu3(void)
{
	cleardevice();
	window1();
	find_message();
}

void menu4(void)
{
	cleardevice();
	window1();
	rand_data();
}

void mouse_catch(void)
{
	m = GetMouseMsg();
	switch(m.uMsg)
	{
		case WM_LBUTTONDOWN:	
			if(((m.x>240)&&(m.x<400))&&(falg_screen ==1 ))
			{
				if((m.y<100)&&(m.y>50))		menu1();
				if((m.y<200)&&(m.y>150))	menu2();
				if((m.y<300)&&(m.y>250))	menu3();	
				if((m.y<400)&&(m.y>350))	menu4();
//				if((m.y<400)&&(m.y>350))	menu4();
			}
			if((m.x>570)&&(m.x<680)&&(m.y>0)&&(m.y<40))
			{
				flag0 = 0;
			}

			break;
		case WM_RBUTTONUP:
			start_menu();
			break;			// 按鼠标右键退出程序
	}

	
	


}

void window1(void)
{
	//	setorigin(320, 250);
	falg_screen=0;
 



	setbkcolor(RGB(83,83,83));

	cleardevice();

 

	// 设置绘图样式

	setlinecolor(RGB(212,212,212));							

	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);	// 设置线条样式为宽度 10 的实线，端点是平的

	setfillcolor(RGB(242,242,242));						

 

	// 画方块

	fillroundrect(230, 42, 400, 100, 30, 30);
	setcolor(RGB(66,66,66));
	outtextxy(252,64, _T("--右击返回主菜单--"));
	setlinecolor(RGB(212,212,212));							
	fillroundrect(50, 300, 600, 500, 30, 30);
//	setorigin(0, 0);
 
}

