/*�������� ������Ʈ 
�й� : 201611321
�̸� : �ӹμ�*/ 
#include<stdio.h>//�⺻ 
#include<string.h>//strcmp ��� 
#include<stdlib.h>
#include<windows.h>//�ܼ�+system 
#include<time.h>//����ð� 
#include<conio.h>//gotoxy()

#define LSIZE 100//��ü����ü ũ�� 
#define SIZE 20//����ü�� �迭 ũ�� 

void gotoxy(int x, int y);//ui�� ��ǥ 
void init_struct();//����ü �ʱ�ȭ 
void newmenu();//ui
void fillmenu();//ui++ 

int isyoon(int a);//���� üũ 
void calendar();//�޷� 
int check_freeday(int a,int b);//������ üũ 

void load();//�ε� 
void EraseSpace(char a_string[]);
void gotomain(char a[]);//-1�Է½� main������ 
int reset_menu(int i);//�Է¿� ��ǥ 
void input();//�Է� 
void modify();//���� 
int check_str(char m_name[],char a_name[]);//�˻��� check 

void find();//�˻� 
void delete1();//���� 
void all_print();//���� ��ü��� 
void check_OX();//ox üũ 
void check_percent();//üũ�� ��� ��ü��� 
void timeprint();//����ð� ��� 
void print_menu();
void print_menu1();
void print_menu2();//�޴��� ��� 
int menu_print();
int menu_print1();
int menu_print2();//�޴��� ���� 

typedef struct schedule{
	char name[SIZE];
	char year[SIZE];
	char month[SIZE];
	char day[SIZE];	
	char level[SIZE];
}schedule;	//����ü Ȱ����, �⵵, ��, ��, �߿䵵 

schedule a[LSIZE];

FILE *fp;//���� 1�� ��� 

void gotoxy(int x, int y){
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}//��ǥ���� �Լ� 

void init_struct(){
	int i;
	
	for(i = 0; i < LSIZE; i++){
		a[i].name[0] = '\0';
		a[i].year[0] = '\0';
		a[i].month[0] = '\0';
		a[i].day[0] = '\0';
		a[i].level[0] = '\0';
	}
}//����ü �ʱ�ȭ 

void newmenu(){
	int i;
	
	printf("������������������������������������������������������\n");
	for(i = 3; i < 17; i++){
		gotoxy(0,i);
		printf("��");
	}
	for(i = 3; i < 17; i++){
		gotoxy(52,i);
		printf("��");
	}
	printf("\n");
	printf("������������������������������������������������������");
}//�޴��׸��� 

void fillmenu(){
	int i;
	
	for(i = 1; i < 3; i++){
		gotoxy(0,i);
		printf("��");
	}
	for(i = 1; i < 3; i++){
		gotoxy(52,i);
		printf("��");
	}
}//������ �κ� ä��� 

int isyoon(int a) {
    if ((a % 4 == 0) && (a % 100 != 0) || (a % 400 == 0)) {
        return 1;
    }
    else {
        return 0;
    }
}//����üũ 

int check_freeday(int a,int b){
	if(a == b && (a == 1 || a == 5 || a == 6)){//1�� 1��, 5�� 5��, 6�� 6�� 
		return 1;
	}
	else if(b == 9 && (a == 3 || a == 10)){//3�� 9��, 10�� 9�� 
		return 1;
	}
	else if(a-2 == b && (a == 8 || a == 3)){//8�� 6��, 3�� 1�� 
		return 1;
	}
	else if(((a*2+1 == b || a*2-1 == b) && b % 5 == 0) && (a == 8 || a == 12)){//8�� 15��, 12�� 25�� 
		return 1;
	}
	else if((a == 3 || a == 10) && (a/3 == b)){//3�� 1��, 10�� 3�� 
		return 1;
	} 
	else{
		return 0;
	}
}//������ üũ 

void calendar(){
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	int year = t->tm_year, month = t->tm_mon, day = t->tm_mday;
	
	goto_loop_out:;
	 
	int i,j; // for���� ����
    int k = 0; // ����� ����
    int sum = 0; // ������ ��� �� ��� ����
    int chk = 0; // ���� Ȯ�� ����
    int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // �⺻ 1~12�� �ϼ�
	int key;//Ű���� ����Ű �ƽ�Ű�ڵ尪 �б� 
	
	system("cls");
    
	if (isyoon(year + 1900)) {
        chk = 1;//�����̸� chk = 1; 
        basicyear[1]++;//�迭[2]�� 28�� 1�߰� 
    }
    else{
        chk = 0;
	}//�����̸� 2�� 29�� �ƴϸ� 28�� 

    sum = 365;
    for (i = 1;i < year + 1900;i++) {
        if(isyoon(i)){
            sum += 366;//�����̸� 
        }
        else{
            sum += 365;//������ �ƴϸ� 	
        }
    }//0����� �۳���� ��ĥ���� ��
 
    for (i = 0;i < month;i++) {
        sum += basicyear[i];//�Է��� �ޱ��� ��ĥ���� 
    }
 
    k = sum % 7;//1��1�� ���� �������� ���(�ִ����� ����) 
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    
    printf("\t\t%d�� %d��\n",year + 1900, month + 1);
    printf("��\t��\tȭ\t��\t��\t��\t��\n");
    printf("===================================================\n");
 
    for (j = 0;j < k;j++) {
        printf("\t");//���� ���Ͽ� ���� ����
    }
 
    for (i = 1; i <= basicyear[month]; i++){
    	if(check_freeday(month + 1,i) == 1){
    		if(k == 6){
    			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
				printf("%d\t",i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
				k = -1;
				printf("\n");
			}
			else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
				printf("%d\t",i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
		}//������ 
        else if (k == 6){
        	printf("%d\t", i);
            k = -1;
            printf("\n");
        }//����� 
        else if(k == 0){
        	printf("%d\t", i);
		}//�Ͽ��� 
        else{
        	printf("%d\t", i);
		}//���� 
		k++;
    }
    printf("\n");//�޷���� 
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf("Ż���ҷ��� �ƹ�Ű�� ����");
    
    while(1){//Ű�Է� 
    	if(kbhit()){
    		key = getch();
    		if(key == 224 || key == 0){//����Ű �Է��ϸ� 224�� ���� ���ͼ� 
    			key = getch();//Ű�Է� �ޱ� 
    			switch(key){
    				case 72://��Ŭ�� 
    					year+=1;
    					goto goto_loop_out;
    					break;
    				case 75://��Ŭ�� 
    					month-=1;
    					if(month < 0){
    						month = 11;
							year -= 1;
						}//1�� ���̸� 1��--, 12���� 
    					goto goto_loop_out;
    					break;
    				case 77://��Ŭ�� 
    					month+=1;
    					if(month > 11){
    						month = 0;
							year += 1;
						}//12���� ������ 1��++, 1���� 
    					goto goto_loop_out;
    					break;
    				case 80://��Ŭ�� 
    					year-=1;
    					goto goto_loop_out;
    					break;
				}
			}
			else{
				main();
				exit(1);
			}
		}
	}
}

void load(){
	int i = 0;
	
	fp = fopen("test.txt","a+");//read ���·� ���� ���� 
	
	if(fp == NULL){//a+ �а� ���� ���� || a = ���Ⱑ�� 
		printf("������ �����ϴ�.\n");
		exit(1);
	}//������ ������ Ȯ�� 
	while(1){
		if(feof(fp)){
			break;
		}
		fscanf(fp, "%s %s %s %s %s\n",a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
		i++;
	}//������ ������ �о�´�.
	fclose(fp);
}

void EraseSpace(char a_string[]){//���������� �迭 �ޱ� 
	int i, index = 0;
	
	for(i = 0; a_string[i] != 0; i++){//�迭�� ���������� �ݺ� 
		if(a_string[i] != ' '){//i��° �迭�� �����̸� 
			a_string[index] = a_string[i];//�׷� 
			index++;
		}
	}
	a_string[index] = 0;
}//���� ���� �Լ� 

void gotomain(char a[]){
	if(atoi(a) == -1){
		main(); 
		exit(1);
	}
}//Ż���Լ�

int reset_menu(int i){
	if(i >= 16){
		i = 2;
		system("cls");
		newmenu();
		fillmenu();
	}
	return i;
}//�Է��Լ����� ���(ui�� �°� ��������) 

int check_str(char m_name[], char a_name[]){
	int len,len1;
	int count = 0;
	int i, j;
	
	len = strlen(m_name);
	len1 = strlen(a_name);//�迭 ������� 
	
	while(len+count <= len1){
		j = 0;//j�� ����ؼ� �ʱ�ȭ 
		for(i = 0; i < len; i++){
			if(a_name[i] == m_name[i+count]){
				j++;
			}//�迭 1��1�� üũ�ؼ� ������ ������ j++ 
		}
		if(j == len){
			return 1;
		}//j�� �Է¹����Ŷ� ���̰� ������ 1��ȯ 
		count++;
	}
	return 0;//�ƴϸ� 0��ȯ 
}//�˻��Լ����� ���(1���ڷ� �˻��ϱ�) 

void input(){
	char s_name[SIZE];
	char s_year[SIZE];
	char s_month[SIZE];
	char s_day[SIZE];
	char s_level[SIZE];
	int i = 9;//��ǥ ������ �س��� 

	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	system("cls");

	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(10,2);
	printf("���ҰŸ� -1�Է��ϼ���\n");
	gotoxy(10,4);
	printf("Ȱ���� �Է� : ");
	scanf(" %[^\n]s", s_name);//���� �����ؼ� �ޱ� 
	EraseSpace(s_name);//�������� �Լ� 
	gotomain(s_name);//-1�Է½� main���� ������ 
	//���������ؼ� �޾Ƽ� ���������ؼ� ���� 
	
	gotoxy(10,5);
	printf("�⵵ �Է� : ");
	scanf(" %[^\n]s", s_year);
	EraseSpace(s_year);
	gotomain(s_year);
		
	gotoxy(10,6);
	printf("�� �Է� : ");
	scanf(" %[^\n]s", s_month);
	EraseSpace(s_month);
	gotomain(s_month);
	
	gotoxy(10,7);
	printf("�� �Է� : ");
	scanf(" %[^\n]s", s_day);
	EraseSpace(s_day);
	gotomain(s_day);
	
	gotoxy(10,8);
	printf("�߿䵵 �Է�(1~5) : ");
	scanf(" %[^\n]s", s_level);//����ü �迭�� �Է� 
	EraseSpace(s_level);
	gotomain(s_level);
	
	while(atoi(s_year) == 0){//�⵵�� �ѱ� �Է½� 
		gotoxy(10,i);
		printf("�� �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s",s_year);
		EraseSpace(s_year);
		gotomain(s_year);
		
		i = reset_menu(i);
		i++;
	}
	while(atoi(s_month) == 0){//���� �ѱ� �Է½� 
		gotoxy(10,i);
		printf("�� �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);//�Է¹޴� �κ��� ui�� �Ѿ�� �ʱ�ȭ���� ui �ٽ�ǥ�� 
		i++;
	}
	while(atoi(s_day) == 0){//�Ͽ� �ѱ� �Է½� 
		gotoxy(10,i);
		printf("�� �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s",s_day);
		EraseSpace(s_day);
		gotomain(s_day);
		
		i = reset_menu(i);
		i++;
	}
	while(atoi(s_level) == 0){//�߿䵵�� �ѱ� �Է½� 
		gotoxy(10,i);
		printf("�߿䵵 �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s", s_level);//����ü �迭�� �Է� 
		EraseSpace(s_level);
		gotomain(s_level);
		
		i = reset_menu(i);
		i++;
	}//����ڰ� ���ڸ� �Է��ؾ� �ϴµ� ���ڸ� �Է��� ��� 
	
	while(atoi(s_year) < t->tm_year+1900 || atoi(s_year) > 3000){//���� 1���̸� 12�� �ʰ��� �Է½� 
		gotoxy(10,i); 
		printf("�� �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);
		i++;
	}
	
	while(atoi(s_month) < 1 || atoi(s_month) > 12){//���� 1���̸� 12�� �ʰ��� �Է½� 
		gotoxy(10,i);
		printf("�� �ٽ��Է��ϼ��� : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);
		i++;
	}//���� 1���̸� 12�� �ʰ��� �Է��� ��� 
	
	if(atoi(s_month) < 8){
		if(atoi(s_month) %2 == 1){//Ȧ���� 31�� 
			while(atoi(s_day) < 0 || atoi(s_day) > 31){//0�� �̸� 31�� �ʰ��� 
				gotoxy(10,i);
				printf("�� �ٽ��Է��ϼ��� : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
		else{
			while(atoi(s_day) < 0 || atoi(s_day) > 30){//0�� �̸� 30�� �ʰ��� 
				gotoxy(10,i);
				printf("�� �ٽ��Է��ϼ��� : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
	}//7������ �ν� 
	else{
		if(atoi(s_month) %2 == 0){//¦���� 31�� 
			while(atoi(s_day) < 0 || atoi(s_day) > 31){//0�� �̸� 31�� �ʰ��� 
				gotoxy(10,i);
				printf("�� �ٽ��Է��ϼ��� : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
		else{
			while(atoi(s_day) < 0 || atoi(s_day) > 30){//0�� �̸� 30�� �ʰ��� 
				gotoxy(10,i);
				printf("�� �ٽ��Է��ϼ��� : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
	}//7�� �̻� �ν� 
	
	while(atoi(s_level) < 1 || atoi(s_level) > 5){//�߿䵵�� 1�̸� 5�ʰ� �Է½� 
		gotoxy(10,i);
		printf("�߿䵵 �ٽ� �Է��ϼ��� : ");
		scanf(" %[^\n]s", s_level);
		EraseSpace(s_level);
		gotomain(s_level);
		
		i = reset_menu(i);
		i++;
	}//�߿䵵�� 1�̸� 5�ʰ��̸� �ٽ��Է� 
	
	while((isyoon(atoi(s_year)) && atoi(s_month) == 2 && atoi(s_day) > 29)){//�����̰� 2���ε� 28���̻����� �Է��ҽ� 
		gotoxy(10,i);
		printf("�����Դϴ�.\n");
		printf("�� �ٽ��Է��ϼ���.");
		scanf(" %[^\n]s",s_day);
		EraseSpace(s_day);
		gotomain(s_day);
		
		i = reset_menu(i);
		i++;
	}//�����϶� 2�� 29���̸� �ٽ��Է� 
	
	fp = fopen("test.txt","a");//����ü �迭�� �Է¹����� ���Ͽ� �Է��ϱ� ���� append�� ���� 
	fprintf(fp, "%s %s %s %s %s\n", s_name, s_year, s_month, s_day, s_level);//���Ͽ� �Է� 
	fclose(fp);//�������� �ݱ�

	gotoxy(10,i+1);
	printf("�Է� �Ϸ�\n");
	getchar();
	getchar();
	main();//�������� �Ĺ� 
}//�Է� 

void modify(){	
	char f_name[20];
	int i,j;
	int sel = 0;
	int num;
	int check;
	char m_name[SIZE];
	char m_year[SIZE];
	char m_month[SIZE];
	char m_day[SIZE];
	char m_level[SIZE];
	
	system("cls");
	
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,2);
	printf("���ҰŸ� -1�Է��ϼ���\n");
	
	gotoxy(7,3);
	printf("������ Ȱ������ �Է��Ͻÿ� :");
	scanf(" %[^\n]s",f_name);
	EraseSpace(f_name);
	gotomain(f_name);
	
	for(i = 0; i < LSIZE; i++){
		check = check_str(f_name,a[i].name);
		if(check == 1){
			gotoxy(7,5);
			printf("1. %s\n", a[i].name);
			gotoxy(7,6);
			printf("2. %s��-%s��-%s��\n", a[i].year,a[i].month,a[i].day);
			num = atoi(a[i].level);
			gotoxy(7,7);
			if(num == 0){
				printf("clear\n");
			}
			else{
				printf("�߿䵵 : ");
				for(j = 0; j < num; j++){
					printf("��");
				}
				printf("\n");
			}
			break;
		}
	}//����ü�� ũ�⸸ŭ �ݺ��ؼ� üũ
	
	if(i != LSIZE){
		gotoxy(7,9);
		printf("������ ����� �Է��ϼ���.");
		gotoxy(7,10);
		printf("(1. Ȱ����, 2. ��, 3. ��, 4. ��, 5. �߿䵵)");
		scanf("%d", &sel);
		switch(sel){
			case 1:
				gotoxy(7,12);
				printf("�ٲ� Ȱ���� �Է� : ");
				scanf(" %[^\n]s", m_name);
				EraseSpace(m_name);	
				gotomain(m_name);
				strcpy(a[i].name, m_name);
				break;
			case 2:
				gotoxy(7,12);
				printf("�ٲ� �⵵ �Է� : ");
				scanf(" %[^\n]s", m_year);
				EraseSpace(m_year);
				gotomain(m_year);
				strcpy(a[i].year, m_year);
				break;
			case 3:
				gotoxy(7,12);
				printf("�ٲ� �� �Է� : ");
				scanf(" %[^\n]s", m_month);
				EraseSpace(m_month);
				gotomain(m_month);
				strcpy(a[i].month, m_month);
				break;
			case 4:
				gotoxy(7,12);
				printf("�ٲ� �� �Է� : ");
				scanf(" %[^\n]s", m_day);
				EraseSpace(m_day);
				gotomain(m_day);
				strcpy(a[i].day, m_day);
				break;
			case 5:
				gotoxy(7,12);
				printf("�ٲ� �߿䵵 �Է� : ");
				scanf(" %[^\n]s", m_level);
				EraseSpace(m_level);
				gotomain(m_level);
				strcpy(a[i].level, m_level);
				break;
			default:
				system("cls");
				main();
				break;				
		}
	}//������ �κ� ���� 1~3 4���� �׳� ���� 
	
	fp = fopen("test.txt","w");
	for(i = 0; i < LSIZE; i++){
		fprintf(fp, "%s %s %s %s %s\n", a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
	}//������ �κ��� ���ļ� ���Ͽ� �Է� 
	fclose(fp);
	
	gotoxy(7,13);
	printf("�����Ϸ�");
	getchar();
	getchar();
	main();
}//���� 

void find(){
	char m_name[SIZE];
	char m_year[SIZE];
	char m_month[SIZE];
	char m_day[SIZE];
	char m_level[SIZE];
	int i,j;
	int sel;
	int num;
	int check;
	
	system("cls");
	
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,2);
	printf("���ҰŸ� -1�Է��ϼ���\n");
	if(i != LSIZE){
		gotoxy(7,4);
		printf("�˻��� ����� �Է��ϼ���.");
		gotoxy(7,5);
		printf("(1. Ȱ����, 2. ��, 3. ��, 4. ��, 5. �߿䵵)");
		scanf("%d",&sel);
		switch(sel){
			case 1:
				gotoxy(7,7);
				printf("�˻��� Ȱ���� �Է� : ");
				scanf(" %[^\n]s", m_name);
				EraseSpace(m_name);
				gotomain(m_name);
				for(i = 0; i < LSIZE; i++){
					check = check_str(m_name,a[i].name);
					if(check == 1){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("Ȱ���� : %s\n",a[i].name);
						gotoxy(10,10);
						printf("���� : %s�� - %s�� - %s��\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("�߿䵵 : ");
							for(j = 0; j < num; j++){
								printf("��");
							}
							printf("\n");
						}
					}
				}
				break;
			case 2:
				gotoxy(7,7);
				printf("�˻��� �⵵ �Է� : ");
				scanf(" %[^\n]s", m_year);
				EraseSpace(m_year);
				gotomain(m_year);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_year, a[i].year) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("Ȱ���� : %s\n",a[i].name);
						gotoxy(10,10);
						printf("���� : %s�� - %s�� - %s��\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("�߿䵵 : ");
							for(j = 0; j < num; j++){
								printf("��");
							}
							printf("\n");
						}
					}
				}
				break;
			case 3:
				gotoxy(7,7);
				printf("�˻��� �� �Է� : ");
				scanf(" %[^\n]s", m_month);
				EraseSpace(m_month);	
				gotomain(m_month);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_month, a[i].month) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("Ȱ���� : %s\n",a[i].name);
						gotoxy(10,10);
						printf("���� : %s�� - %s�� - %s��\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("�߿䵵 : ");
							for(j = 0; j < num; j++){
								printf("��");
							}
							printf("\n");
						}
					}
				}
				break;
			case 4:
				gotoxy(7,7);
				printf("�˻��� �� �Է� : ");
				scanf(" %[^\n]s", m_day);
				EraseSpace(m_day);	
				gotomain(m_day);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_day, a[i].day) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("Ȱ���� : %s\n",a[i].name);
						gotoxy(10,10);
						printf("���� : %s�� - %s�� - %s��\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("�߿䵵 : ");
							for(j = 0; j < num; j++){
								printf("��");
							}
							printf("\n");
						}
					}
				}
				break;
			case 5 :
				gotoxy(7,7);
				printf("�˻��� �߿䵵 �Է� : ");
				scanf(" %[^\n]s",m_level);
				EraseSpace(m_level);	
				gotomain(m_level);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_level, a[i].level) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("Ȱ���� : %s\n",a[i].name);
						gotoxy(10,10);
						printf("���� : %s�� - %s�� - %s��\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("�߿䵵 : ");
							for(j = 0; j < num; j++){
								printf("��");
							}
							printf("\n");
						}
					}
				}
				break;
			default:
				system("cls");
				main();
				break;
		}	
	}
	fclose(fp);
	
	gotoxy(7,13);
	printf("�˻��Ϸ�");
	
	//����ü�� ũ�⸸ŭ �ݺ��ؼ� üũ
	getchar();
	getchar();
	main();
}//�˻� 

void delete1(){
	int i;
	char f_name[SIZE];

	system("cls");
		
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,2);
	printf("���ҰŸ� -1�Է��ϼ���\n");
	
	gotoxy(7,4);
	printf("������ Ȱ������ �Է��Ͻÿ� : ");
	gotoxy(7,5);
	scanf(" %[^\n]s",f_name);
	EraseSpace(f_name);	
	gotomain(f_name);
	
	for(i = 0; i < LSIZE; i++){
		if(strcmp(f_name, a[i].name) == 0){
			strcpy(a[i].name," ");
			gotoxy(7,7);
			printf("�����Ϸ�");
			break;
		}
	}	//����ü�� ũ�⸸ŭ �ݺ��ؼ� üũ
	
	if( i == LSIZE){
		gotoxy(7,6);
		printf("��ġ�ϴ� Ȱ���� �����ϴ�.");
	}//0���� 99���� �������� ��ġ�ϴ� ����� ������ ��� 
	
	fp = fopen("test.txt","w");//�����ϱ� ���� w�� �о���� 
	for(i = 0; i < LSIZE; i++){
		if(strcmp(a[i].name, " ") != 0){
			fprintf(fp, "%s %s %s %s %s\n", a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
			break; 
		}
	}
	fclose(fp);
	getchar(); 
	getchar();
	main();
}//���� 

void all_print(){
	int i,j,num;
	char sel[SIZE],sel1[SIZE];
	
	system("cls");
	
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,6);
	printf("����� ������ ����Ͻðڽ��ϱ�?");
	scanf(" %[^\n]s",sel);
	EraseSpace(sel);
	gotomain(sel);
	
	gotoxy(7,8);
	printf("����� ������ ����Ͻðڽ��ϱ�?");
	scanf(" %[^\n]s",sel1);
	EraseSpace(sel1);
	gotomain(sel1);
	
	system("cls");
	
	fp = fopen("test.txt","r");
	//fseek(fp,0,SEEK_SET);
	
	for(i = 0 ; i < LSIZE; i++){
		if(strcmp(a[i].year,sel) == 0 && strcmp(a[i].month,sel1) == 0){
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, a[i-1].name) == 0){
				i++;
			}
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, " ") != 0){
				printf("Ȱ���� : %s\n",a[i].name);
				printf("%s��-%s��-%s��\n",a[i].year,a[i].month,a[i].day);
				num = atoi(a[i].level);
				if(num == 0){
					printf("clear\n");
				}
				else{
					printf("�߿䵵 : ");
					for(j = 0; j < num; j++){
						printf("��");
					}
					printf("\n");
				}
				printf("\n");
			}
		}
	}
	if(i == LSIZE){
		printf("���̻� �����ϴ�.");
	}
	fclose(fp);
	
	getchar();
	getchar();
}

void check_OX(){
	int i,j;
	int num;
	char c_name[SIZE];
	
	system("CLS");
	
	all_print();
	
	printf("���ҰŸ� -1�Է��ϼ���\n");
	printf("check�� Ȱ������ �Է��Ͻÿ� : ");
	scanf(" %[^\n]s",&c_name);
	EraseSpace(c_name);
	gotomain(c_name);//-1�Է��ϸ� main������ Ż�� 
	
	for(i = 0; i < LSIZE; i++){
		if(strcmp(a[i].name,c_name) == 0 && strcmp(a[i].level, "0") == 0){
			printf("�̹� Ŭ�����߽��ϴ�.");
		}
		if(strcmp(c_name, a[i].name) == 0){
			strcpy(a[i].level,"0");	
		} 
	}
	
	fp = fopen("test.txt","w");//�����ϱ� ���� w�� �о���� 
	for(i = 0; i < LSIZE; i++){
		fprintf(fp, "%s %s %s %s %s\n", a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
	}
	fclose(fp);
	
	getchar();
	getchar();
	main();
}

void check_percent(){
	int i,j;
	int num;
	char sel[SIZE],sel1[SIZE];
	int per = 0,per1 = 0;
	int result = 0;
	float sum = 0;
	
	system("cls");
	
	load();
	
	newmenu();
	fillmenu();
	
	fp = fopen("test.txt","r");
	
	gotoxy(7,6);
	printf("����� ������ ����Ͻðڽ��ϱ�?");
	scanf(" %[^\n]s",sel);
	EraseSpace(sel);
	gotomain(sel);
	
	gotoxy(7,8);
	printf("����� ������ ����Ͻðڽ��ϱ�?");
	scanf(" %[^\n]s",sel1);
	EraseSpace(sel1);
	gotomain(sel1);
	
	for(i = 0; i < LSIZE; i++){
		fscanf(fp, "%s %s %s %s %s",a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
		}	//���� �о���� 
		for(i = 0; i < LSIZE; i++){
		if(strcmp(a[i].year,sel) == 0 && strcmp(a[i].month,sel1) == 0){
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, a[i-1].name) == 0){
				i++;
			}//���̰� 0�̰� �������� ������ i++ 
			
			system("cls");
			
			newmenu();
			fillmenu();
			
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, " ") != 0){
				if(strcmp(a[i].level,"0") == 0){
					per++;//Ŭ���� ������ per++ 
				}
				else{
					per1++;//Ŭ���� �������� per1++; 
				}
			}//�Էµ� �͵鸸 ��� 
		}
	}
	fclose(fp);
	
	if(per == 0 ){
		gotoxy(7,8);
		printf("Ŭ������ ������ �����ϴ�.");
	}
	else{
		sum = per + per1;
		result = (per/sum) * 100;//�ۼ�Ʈ ���� 
		
		gotoxy(7,5);
		printf("%d���� %d�� �Ϸ��߽��ϴ�.\n",(int)sum,per);
		gotoxy(7,7);
		printf("%s�� %s���� Ŭ������ �ۼ�Ʈ�� %d%%�Դϴ�.",sel,sel1,result);//%%�ҽ� %��� 
		//printf("clear percent : %d",result);	
	} 
	getchar();
	getchar();
	main();
}

void timeprint(){
	struct tm *t;
	time_t timer;
	char str[2][20] = {"����","����"};

	system("cls");
	
	timer = time(NULL);
	t = localtime(&timer);
	
	if(t->tm_hour > 12){//12�� �̻��̸� ���� 
		t->tm_hour = t->tm_hour-12; 
		printf("������ð��� %d�� %d�� %d�� %s %d�� %d�� �Դϴ�.��\n\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, str[1], t->tm_hour, t->tm_min);
	}
	else{//�ƴϸ� ���� 
		printf("������ð��� %d�� %d�� %d�� %s %d�� %d�� �Դϴ�.��\n\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, str[0], t->tm_hour, t->tm_min);
	}
}//����ð� ��� 

void print_menu(){
	int i, j = 0;
	char str[3][10] = {"�������","�ΰ����","����"};
	
	for(i = 1; i < 6; i+=2){
		gotoxy(18,6+i);
		if(i != 1 && i % 2 == 1){
			j++;
		}
		printf("%d. ", j+1);
		printf("%s",str[j]);
	}
}
void print_menu1(){
	int i, j = 0;
	char str[5][10] = {"���� �Է�","�Է� ����","���� �˻�","��������","����"};
	
	for(i = 1; i < 10; i+=2){
		gotoxy(18,4+i);
		if(i != 1 && i % 2 == 1){
			j++;
		}
		printf("%d. ",j+1);
		printf("%s",str[j]);
	}
}
void print_menu2(){
	int i, j = 0;
	char str[5][10] = {"��ü���", "����üũ", "�޼���", "�޷�", "����"};
	
	for(i = 1; i < 10; i+=2){
		gotoxy(18,4+i);
		if(i != 1 && i % 2 == 1){
			j++;
		}
		printf("%d. ",j+1);
		printf("%s",str[j]);
	}
}

int menu_print(){
	int select;
	
	SetConsoleTitle("�μ��� ��������"); //�ܼ�â �̸� ���� 
	system("mode con cols=90 lines=30");//�ܼ� ũ�� ���� 
	
	init_struct();//����ü �ʱ�ȭ 
	
	while(1){
		system("cls");
		
		timeprint();
		newmenu();
		print_menu();
		
		gotoxy(30,17);
		printf("\n�޴��� �����ϼ��� : ");
		scanf("%d",&select);
		switch(select){
			case 1: 
				menu_print1();
				break;//�������(�޴�1)
			case 2:
				menu_print2();
				break;//�ΰ����(�޴�2) 
			default:
				return 0;
		}
	}
}//ó�� �޴� 

int menu_print1(){
	int select;
	
	while(1){
		system("cls");
		
		timeprint();
		newmenu();
		print_menu1();
		
		gotoxy(30,17);
		printf("\n�޴��� �����ϼ��� : ");
		scanf("%d",&select);
		switch(select){
			case 1: 
				input();
				break;//�Է� 
			case 2:
				modify();//���� 
				break;
			case 3:
				find();//�˻�
				break;
			case 4:
				delete1();//���� 
				break;
			case 5:
				return 0;//���� 
			default:
				return 0;
		}
	}
}

int menu_print2(){
	int select;
	
	while(1){
		system("cls");
		
		timeprint();
		newmenu();
		print_menu2();
		
		gotoxy(30,17);
		printf("\n�޴��� �����ϼ��� : ");
		scanf("%d",&select);
		switch(select){
			case 1:
				all_print();
				break; 	//��ü��� 
			case 2:
				check_OX();
				break;
			case 3:
				check_percent();
				break;
			case 4: 
				calendar();
				return 0;//���� 
			case 5:
				return 0;
			default:
				return 0;
		}
	}
}

int main(){
	menu_print();
	
	return 0;
}
