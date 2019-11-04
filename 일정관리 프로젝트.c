/*일정관리 프로젝트 
학번 : 201611321
이름 : 임민수*/ 
#include<stdio.h>//기본 
#include<string.h>//strcmp 등등 
#include<stdlib.h>
#include<windows.h>//콘솔+system 
#include<time.h>//현재시간 
#include<conio.h>//gotoxy()

#define LSIZE 100//전체구조체 크기 
#define SIZE 20//구조체안 배열 크기 

void gotoxy(int x, int y);//ui용 좌표 
void init_struct();//구조체 초기화 
void newmenu();//ui
void fillmenu();//ui++ 

int isyoon(int a);//윤년 체크 
void calendar();//달력 
int check_freeday(int a,int b);//공휴일 체크 

void load();//로드 
void EraseSpace(char a_string[]);
void gotomain(char a[]);//-1입력시 main문으로 
int reset_menu(int i);//입력용 좌표 
void input();//입력 
void modify();//수정 
int check_str(char m_name[],char a_name[]);//검색용 check 

void find();//검색 
void delete1();//삭제 
void all_print();//일정 전체출력 
void check_OX();//ox 체크 
void check_percent();//체크한 목록 전체출력 
void timeprint();//현재시간 출력 
void print_menu();
void print_menu1();
void print_menu2();//메뉴들 출력 
int menu_print();
int menu_print1();
int menu_print2();//메뉴들 선택 

typedef struct schedule{
	char name[SIZE];
	char year[SIZE];
	char month[SIZE];
	char day[SIZE];	
	char level[SIZE];
}schedule;	//구조체 활동명, 년도, 월, 일, 중요도 

schedule a[LSIZE];

FILE *fp;//파일 1개 사용 

void gotoxy(int x, int y){
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}//좌표지정 함수 

void init_struct(){
	int i;
	
	for(i = 0; i < LSIZE; i++){
		a[i].name[0] = '\0';
		a[i].year[0] = '\0';
		a[i].month[0] = '\0';
		a[i].day[0] = '\0';
		a[i].level[0] = '\0';
	}
}//구조체 초기화 

void newmenu(){
	int i;
	
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	for(i = 3; i < 17; i++){
		gotoxy(0,i);
		printf("┃");
	}
	for(i = 3; i < 17; i++){
		gotoxy(52,i);
		printf("┃");
	}
	printf("\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}//메뉴그리기 

void fillmenu(){
	int i;
	
	for(i = 1; i < 3; i++){
		gotoxy(0,i);
		printf("┃");
	}
	for(i = 1; i < 3; i++){
		gotoxy(52,i);
		printf("┃");
	}
}//부족한 부분 채우기 

int isyoon(int a) {
    if ((a % 4 == 0) && (a % 100 != 0) || (a % 400 == 0)) {
        return 1;
    }
    else {
        return 0;
    }
}//윤년체크 

int check_freeday(int a,int b){
	if(a == b && (a == 1 || a == 5 || a == 6)){//1월 1일, 5월 5일, 6월 6일 
		return 1;
	}
	else if(b == 9 && (a == 3 || a == 10)){//3월 9일, 10월 9일 
		return 1;
	}
	else if(a-2 == b && (a == 8 || a == 3)){//8월 6일, 3월 1일 
		return 1;
	}
	else if(((a*2+1 == b || a*2-1 == b) && b % 5 == 0) && (a == 8 || a == 12)){//8월 15일, 12월 25일 
		return 1;
	}
	else if((a == 3 || a == 10) && (a/3 == b)){//3월 1일, 10월 3일 
		return 1;
	} 
	else{
		return 0;
	}
}//공휴일 체크 

void calendar(){
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	int year = t->tm_year, month = t->tm_mon, day = t->tm_mday;
	
	goto_loop_out:;
	 
	int i,j; // for문용 변수
    int k = 0; // 저장용 변수
    int sum = 0; // 현재의 모든 일 계산 변수
    int chk = 0; // 윤년 확인 변수
    int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // 기본 1~12월 일수
	int key;//키보드 방향키 아스키코드값 읽기 
	
	system("cls");
    
	if (isyoon(year + 1900)) {
        chk = 1;//윤년이면 chk = 1; 
        basicyear[1]++;//배열[2]인 28을 1추가 
    }
    else{
        chk = 0;
	}//윤년이면 2월 29일 아니면 28일 

    sum = 365;
    for (i = 1;i < year + 1900;i++) {
        if(isyoon(i)){
            sum += 366;//윤년이면 
        }
        else{
            sum += 365;//윤년이 아니면 	
        }
    }//0년부터 작년까지 며칠인지 셈
 
    for (i = 0;i < month;i++) {
        sum += basicyear[i];//입력한 달까지 며칠인지 
    }
 
    k = sum % 7;//1월1일 무슨 요일인지 계산(주단위로 나눔) 
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    
    printf("\t\t%d년 %d월\n",year + 1900, month + 1);
    printf("일\t월\t화\t수\t목\t금\t토\n");
    printf("===================================================\n");
 
    for (j = 0;j < k;j++) {
        printf("\t");//시작 요일에 맞춰 정렬
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
		}//공휴일 
        else if (k == 6){
        	printf("%d\t", i);
            k = -1;
            printf("\n");
        }//토요일 
        else if(k == 0){
        	printf("%d\t", i);
		}//일요일 
        else{
        	printf("%d\t", i);
		}//평일 
		k++;
    }
    printf("\n");//달력출력 
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf("탈출할려면 아무키나 눌러");
    
    while(1){//키입력 
    	if(kbhit()){
    		key = getch();
    		if(key == 224 || key == 0){//방향키 입력하면 224가 먼저 나와서 
    			key = getch();//키입력 받기 
    			switch(key){
    				case 72://↑클릭 
    					year+=1;
    					goto goto_loop_out;
    					break;
    				case 75://←클릭 
    					month-=1;
    					if(month < 0){
    						month = 11;
							year -= 1;
						}//1월 전이면 1년--, 12월로 
    					goto goto_loop_out;
    					break;
    				case 77://→클릭 
    					month+=1;
    					if(month > 11){
    						month = 0;
							year += 1;
						}//12월이 지나면 1년++, 1월로 
    					goto goto_loop_out;
    					break;
    				case 80://↓클릭 
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
	
	fp = fopen("test.txt","a+");//read 상태로 파일 열기 
	
	if(fp == NULL){//a+ 읽고 쓰기 가능 || a = 쓰기가능 
		printf("파일이 없습니다.\n");
		exit(1);
	}//파일이 없는지 확인 
	while(1){
		if(feof(fp)){
			break;
		}
		fscanf(fp, "%s %s %s %s %s\n",a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
		i++;
	}//파일을 끝까지 읽어온다.
	fclose(fp);
}

void EraseSpace(char a_string[]){//공백제거할 배열 받기 
	int i, index = 0;
	
	for(i = 0; a_string[i] != 0; i++){//배열이 끝날때까지 반복 
		if(a_string[i] != ' '){//i번째 배열이 공백이면 
			a_string[index] = a_string[i];//그랩 
			index++;
		}
	}
	a_string[index] = 0;
}//공백 제거 함수 

void gotomain(char a[]){
	if(atoi(a) == -1){
		main(); 
		exit(1);
	}
}//탈출함수

int reset_menu(int i){
	if(i >= 16){
		i = 2;
		system("cls");
		newmenu();
		fillmenu();
	}
	return i;
}//입력함수에서 사용(ui에 맞게 수정가능) 

int check_str(char m_name[], char a_name[]){
	int len,len1;
	int count = 0;
	int i, j;
	
	len = strlen(m_name);
	len1 = strlen(a_name);//배열 길이재기 
	
	while(len+count <= len1){
		j = 0;//j는 계속해서 초기화 
		for(i = 0; i < len; i++){
			if(a_name[i] == m_name[i+count]){
				j++;
			}//배열 1개1개 체크해서 같은거 있으면 j++ 
		}
		if(j == len){
			return 1;
		}//j가 입력받은거랑 길이가 같으면 1반환 
		count++;
	}
	return 0;//아니면 0반환 
}//검색함수에서 사용(1글자로 검색하기) 

void input(){
	char s_name[SIZE];
	char s_year[SIZE];
	char s_month[SIZE];
	char s_day[SIZE];
	char s_level[SIZE];
	int i = 9;//좌표 때문에 해놓음 

	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	system("cls");

	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(10,2);
	printf("안할거면 -1입력하세요\n");
	gotoxy(10,4);
	printf("활동명 입력 : ");
	scanf(" %[^\n]s", s_name);//공백 포함해서 받기 
	EraseSpace(s_name);//공백제거 함수 
	gotomain(s_name);//-1입력시 main으로 보내기 
	//공백포함해서 받아서 공백제거해서 저장 
	
	gotoxy(10,5);
	printf("년도 입력 : ");
	scanf(" %[^\n]s", s_year);
	EraseSpace(s_year);
	gotomain(s_year);
		
	gotoxy(10,6);
	printf("월 입력 : ");
	scanf(" %[^\n]s", s_month);
	EraseSpace(s_month);
	gotomain(s_month);
	
	gotoxy(10,7);
	printf("일 입력 : ");
	scanf(" %[^\n]s", s_day);
	EraseSpace(s_day);
	gotomain(s_day);
	
	gotoxy(10,8);
	printf("중요도 입력(1~5) : ");
	scanf(" %[^\n]s", s_level);//구조체 배열에 입력 
	EraseSpace(s_level);
	gotomain(s_level);
	
	while(atoi(s_year) == 0){//년도에 한글 입력시 
		gotoxy(10,i);
		printf("년 다시입력하세요 : ");
		scanf(" %[^\n]s",s_year);
		EraseSpace(s_year);
		gotomain(s_year);
		
		i = reset_menu(i);
		i++;
	}
	while(atoi(s_month) == 0){//월에 한글 입력시 
		gotoxy(10,i);
		printf("월 다시입력하세요 : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);//입력받는 부분이 ui를 넘어가면 초기화한후 ui 다시표현 
		i++;
	}
	while(atoi(s_day) == 0){//일에 한글 입력시 
		gotoxy(10,i);
		printf("일 다시입력하세요 : ");
		scanf(" %[^\n]s",s_day);
		EraseSpace(s_day);
		gotomain(s_day);
		
		i = reset_menu(i);
		i++;
	}
	while(atoi(s_level) == 0){//중요도에 한글 입력시 
		gotoxy(10,i);
		printf("중요도 다시입력하세요 : ");
		scanf(" %[^\n]s", s_level);//구조체 배열에 입력 
		EraseSpace(s_level);
		gotomain(s_level);
		
		i = reset_menu(i);
		i++;
	}//사용자가 숫자를 입력해야 하는데 문자를 입력할 경우 
	
	while(atoi(s_year) < t->tm_year+1900 || atoi(s_year) > 3000){//월에 1월미만 12월 초과로 입력시 
		gotoxy(10,i); 
		printf("년 다시입력하세요 : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);
		i++;
	}
	
	while(atoi(s_month) < 1 || atoi(s_month) > 12){//월에 1월미만 12월 초과로 입력시 
		gotoxy(10,i);
		printf("월 다시입력하세요 : ");
		scanf(" %[^\n]s",s_month);
		EraseSpace(s_month);
		gotomain(s_month);
		
		i = reset_menu(i);
		i++;
	}//월이 1월미만 12월 초과로 입력할 경우 
	
	if(atoi(s_month) < 8){
		if(atoi(s_month) %2 == 1){//홀수가 31일 
			while(atoi(s_day) < 0 || atoi(s_day) > 31){//0일 미만 31일 초과시 
				gotoxy(10,i);
				printf("일 다시입력하세요 : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
		else{
			while(atoi(s_day) < 0 || atoi(s_day) > 30){//0일 미만 30일 초과시 
				gotoxy(10,i);
				printf("일 다시입력하세요 : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
	}//7월이하 인식 
	else{
		if(atoi(s_month) %2 == 0){//짝수가 31일 
			while(atoi(s_day) < 0 || atoi(s_day) > 31){//0일 미만 31일 초과시 
				gotoxy(10,i);
				printf("일 다시입력하세요 : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
		else{
			while(atoi(s_day) < 0 || atoi(s_day) > 30){//0일 미만 30일 초과시 
				gotoxy(10,i);
				printf("일 다시입력하세요 : ");
				scanf(" %[^\n]s",s_day);
				EraseSpace(s_day);
				gotomain(s_day);
				
				i = reset_menu(i);
				i++;
			}
		}
	}//7월 이상 인식 
	
	while(atoi(s_level) < 1 || atoi(s_level) > 5){//중요도를 1미만 5초과 입력시 
		gotoxy(10,i);
		printf("중요도 다시 입력하세요 : ");
		scanf(" %[^\n]s", s_level);
		EraseSpace(s_level);
		gotomain(s_level);
		
		i = reset_menu(i);
		i++;
	}//중요도가 1미만 5초과이면 다시입력 
	
	while((isyoon(atoi(s_year)) && atoi(s_month) == 2 && atoi(s_day) > 29)){//윤년이고 2월인데 28일이상으로 입력할시 
		gotoxy(10,i);
		printf("윤년입니다.\n");
		printf("일 다시입력하세요.");
		scanf(" %[^\n]s",s_day);
		EraseSpace(s_day);
		gotomain(s_day);
		
		i = reset_menu(i);
		i++;
	}//윤년일때 2월 29일이면 다시입력 
	
	fp = fopen("test.txt","a");//구조체 배열에 입력받은걸 파일에 입력하기 위해 append로 오픈 
	fprintf(fp, "%s %s %s %s %s\n", s_name, s_year, s_month, s_day, s_level);//파일에 입력 
	fclose(fp);//열었으니 닫기

	gotoxy(10,i+1);
	printf("입력 완료\n");
	getchar();
	getchar();
	main();//메인으로 컴백 
}//입력 

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
	printf("안할거면 -1입력하세요\n");
	
	gotoxy(7,3);
	printf("수정할 활동명을 입력하시오 :");
	scanf(" %[^\n]s",f_name);
	EraseSpace(f_name);
	gotomain(f_name);
	
	for(i = 0; i < LSIZE; i++){
		check = check_str(f_name,a[i].name);
		if(check == 1){
			gotoxy(7,5);
			printf("1. %s\n", a[i].name);
			gotoxy(7,6);
			printf("2. %s년-%s월-%s일\n", a[i].year,a[i].month,a[i].day);
			num = atoi(a[i].level);
			gotoxy(7,7);
			if(num == 0){
				printf("clear\n");
			}
			else{
				printf("중요도 : ");
				for(j = 0; j < num; j++){
					printf("★");
				}
				printf("\n");
			}
			break;
		}
	}//구조체의 크기만큼 반복해서 체크
	
	if(i != LSIZE){
		gotoxy(7,9);
		printf("수정할 목록을 입력하세요.");
		gotoxy(7,10);
		printf("(1. 활동명, 2. 년, 3. 월, 4. 일, 5. 중요도)");
		scanf("%d", &sel);
		switch(sel){
			case 1:
				gotoxy(7,12);
				printf("바꿀 활동명 입력 : ");
				scanf(" %[^\n]s", m_name);
				EraseSpace(m_name);	
				gotomain(m_name);
				strcpy(a[i].name, m_name);
				break;
			case 2:
				gotoxy(7,12);
				printf("바꿀 년도 입력 : ");
				scanf(" %[^\n]s", m_year);
				EraseSpace(m_year);
				gotomain(m_year);
				strcpy(a[i].year, m_year);
				break;
			case 3:
				gotoxy(7,12);
				printf("바꿀 월 입력 : ");
				scanf(" %[^\n]s", m_month);
				EraseSpace(m_month);
				gotomain(m_month);
				strcpy(a[i].month, m_month);
				break;
			case 4:
				gotoxy(7,12);
				printf("바꿀 일 입력 : ");
				scanf(" %[^\n]s", m_day);
				EraseSpace(m_day);
				gotomain(m_day);
				strcpy(a[i].day, m_day);
				break;
			case 5:
				gotoxy(7,12);
				printf("바꿀 중요도 입력 : ");
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
	}//수정할 부분 선택 1~3 4번은 그냥 종료 
	
	fp = fopen("test.txt","w");
	for(i = 0; i < LSIZE; i++){
		fprintf(fp, "%s %s %s %s %s\n", a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
	}//수정한 부분을 고쳐서 파일에 입력 
	fclose(fp);
	
	gotoxy(7,13);
	printf("수정완료");
	getchar();
	getchar();
	main();
}//수정 

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
	printf("안할거면 -1입력하세요\n");
	if(i != LSIZE){
		gotoxy(7,4);
		printf("검색할 목록을 입력하세요.");
		gotoxy(7,5);
		printf("(1. 활동명, 2. 년, 3. 월, 4. 일, 5. 중요도)");
		scanf("%d",&sel);
		switch(sel){
			case 1:
				gotoxy(7,7);
				printf("검색할 활동명 입력 : ");
				scanf(" %[^\n]s", m_name);
				EraseSpace(m_name);
				gotomain(m_name);
				for(i = 0; i < LSIZE; i++){
					check = check_str(m_name,a[i].name);
					if(check == 1){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("활동명 : %s\n",a[i].name);
						gotoxy(10,10);
						printf("일자 : %s년 - %s월 - %s일\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("중요도 : ");
							for(j = 0; j < num; j++){
								printf("★");
							}
							printf("\n");
						}
					}
				}
				break;
			case 2:
				gotoxy(7,7);
				printf("검색할 년도 입력 : ");
				scanf(" %[^\n]s", m_year);
				EraseSpace(m_year);
				gotomain(m_year);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_year, a[i].year) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("활동명 : %s\n",a[i].name);
						gotoxy(10,10);
						printf("일자 : %s년 - %s월 - %s일\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("중요도 : ");
							for(j = 0; j < num; j++){
								printf("★");
							}
							printf("\n");
						}
					}
				}
				break;
			case 3:
				gotoxy(7,7);
				printf("검색할 월 입력 : ");
				scanf(" %[^\n]s", m_month);
				EraseSpace(m_month);	
				gotomain(m_month);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_month, a[i].month) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("활동명 : %s\n",a[i].name);
						gotoxy(10,10);
						printf("일자 : %s년 - %s월 - %s일\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("중요도 : ");
							for(j = 0; j < num; j++){
								printf("★");
							}
							printf("\n");
						}
					}
				}
				break;
			case 4:
				gotoxy(7,7);
				printf("검색할 일 입력 : ");
				scanf(" %[^\n]s", m_day);
				EraseSpace(m_day);	
				gotomain(m_day);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_day, a[i].day) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("활동명 : %s\n",a[i].name);
						gotoxy(10,10);
						printf("일자 : %s년 - %s월 - %s일\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("중요도 : ");
							for(j = 0; j < num; j++){
								printf("★");
							}
							printf("\n");
						}
					}
				}
				break;
			case 5 :
				gotoxy(7,7);
				printf("검색할 중요도 입력 : ");
				scanf(" %[^\n]s",m_level);
				EraseSpace(m_level);	
				gotomain(m_level);
				for(i = 0; i < LSIZE; i++){
					if(strcmp(m_level, a[i].level) == 0){
						gotoxy(7,9);
						printf("%d. ",i+1);
						printf("활동명 : %s\n",a[i].name);
						gotoxy(10,10);
						printf("일자 : %s년 - %s월 - %s일\n", a[i].year, a[i].month, a[i].day);
						num = atoi(a[i].level);
						gotoxy(10,11);
						if(num == 0){
							printf("clear\n");
						}
						else{
							printf("중요도 : ");
							for(j = 0; j < num; j++){
								printf("★");
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
	printf("검색완료");
	
	//구조체의 크기만큼 반복해서 체크
	getchar();
	getchar();
	main();
}//검색 

void delete1(){
	int i;
	char f_name[SIZE];

	system("cls");
		
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,2);
	printf("안할거면 -1입력하세요\n");
	
	gotoxy(7,4);
	printf("삭제할 활동명을 입력하시오 : ");
	gotoxy(7,5);
	scanf(" %[^\n]s",f_name);
	EraseSpace(f_name);	
	gotomain(f_name);
	
	for(i = 0; i < LSIZE; i++){
		if(strcmp(f_name, a[i].name) == 0){
			strcpy(a[i].name," ");
			gotoxy(7,7);
			printf("삭제완료");
			break;
		}
	}	//구조체의 크기만큼 반복해서 체크
	
	if( i == LSIZE){
		gotoxy(7,6);
		printf("일치하는 활동이 없습니다.");
	}//0부터 99까지 돌렸을시 일치하는 사람이 없으면 출력 
	
	fp = fopen("test.txt","w");//수정하기 위해 w로 읽어오기 
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
}//삭제 

void all_print(){
	int i,j,num;
	char sel[SIZE],sel1[SIZE];
	
	system("cls");
	
	load();
	
	newmenu();
	fillmenu();
	
	gotoxy(7,6);
	printf("몇년의 일정을 출력하시겠습니까?");
	scanf(" %[^\n]s",sel);
	EraseSpace(sel);
	gotomain(sel);
	
	gotoxy(7,8);
	printf("몇월의 일정을 출력하시겠습니까?");
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
				printf("활동명 : %s\n",a[i].name);
				printf("%s년-%s월-%s일\n",a[i].year,a[i].month,a[i].day);
				num = atoi(a[i].level);
				if(num == 0){
					printf("clear\n");
				}
				else{
					printf("중요도 : ");
					for(j = 0; j < num; j++){
						printf("★");
					}
					printf("\n");
				}
				printf("\n");
			}
		}
	}
	if(i == LSIZE){
		printf("더이상 없습니다.");
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
	
	printf("안할거면 -1입력하세요\n");
	printf("check할 활동명을 입력하시오 : ");
	scanf(" %[^\n]s",&c_name);
	EraseSpace(c_name);
	gotomain(c_name);//-1입력하면 main문으로 탈출 
	
	for(i = 0; i < LSIZE; i++){
		if(strcmp(a[i].name,c_name) == 0 && strcmp(a[i].level, "0") == 0){
			printf("이미 클리어했습니다.");
		}
		if(strcmp(c_name, a[i].name) == 0){
			strcpy(a[i].level,"0");	
		} 
	}
	
	fp = fopen("test.txt","w");//수정하기 위해 w로 읽어오기 
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
	printf("몇년의 일정을 출력하시겠습니까?");
	scanf(" %[^\n]s",sel);
	EraseSpace(sel);
	gotomain(sel);
	
	gotoxy(7,8);
	printf("몇월의 일정을 출력하시겠습니까?");
	scanf(" %[^\n]s",sel1);
	EraseSpace(sel1);
	gotomain(sel1);
	
	for(i = 0; i < LSIZE; i++){
		fscanf(fp, "%s %s %s %s %s",a[i].name, a[i].year, a[i].month, a[i].day, a[i].level);
		}	//파일 읽어오기 
		for(i = 0; i < LSIZE; i++){
		if(strcmp(a[i].year,sel) == 0 && strcmp(a[i].month,sel1) == 0){
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, a[i-1].name) == 0){
				i++;
			}//길이가 0이고 전에꺼랑 같으면 i++ 
			
			system("cls");
			
			newmenu();
			fillmenu();
			
			if(strlen(a[i].name) != 0 && strcmp(a[i].name, " ") != 0){
				if(strcmp(a[i].level,"0") == 0){
					per++;//클리어 했으면 per++ 
				}
				else{
					per1++;//클리어 안했으면 per1++; 
				}
			}//입력된 것들만 출력 
		}
	}
	fclose(fp);
	
	if(per == 0 ){
		gotoxy(7,8);
		printf("클리어한 일정이 없습니다.");
	}
	else{
		sum = per + per1;
		result = (per/sum) * 100;//퍼센트 계산식 
		
		gotoxy(7,5);
		printf("%d개중 %d개 완료했습니다.\n",(int)sum,per);
		gotoxy(7,7);
		printf("%s년 %s월에 클리어한 퍼센트는 %d%%입니다.",sel,sel1,result);//%%할시 %출력 
		//printf("clear percent : %d",result);	
	} 
	getchar();
	getchar();
	main();
}

void timeprint(){
	struct tm *t;
	time_t timer;
	char str[2][20] = {"오전","오후"};

	system("cls");
	
	timer = time(NULL);
	t = localtime(&timer);
	
	if(t->tm_hour > 12){//12시 이상이면 오후 
		t->tm_hour = t->tm_hour-12; 
		printf("★현재시간은 %d년 %d월 %d일 %s %d시 %d분 입니다.★\n\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, str[1], t->tm_hour, t->tm_min);
	}
	else{//아니면 오전 
		printf("★현재시간은 %d년 %d월 %d일 %s %d시 %d분 입니다.★\n\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, str[0], t->tm_hour, t->tm_min);
	}
}//현재시간 출력 

void print_menu(){
	int i, j = 0;
	char str[3][10] = {"일정기능","부가기능","종료"};
	
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
	char str[5][10] = {"일정 입력","입력 수정","일정 검색","일정삭제","이전"};
	
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
	char str[5][10] = {"전체출력", "일정체크", "달성률", "달력", "이전"};
	
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
	
	SetConsoleTitle("민수의 일정관리"); //콘솔창 이름 변경 
	system("mode con cols=90 lines=30");//콘솔 크기 설정 
	
	init_struct();//구조체 초기화 
	
	while(1){
		system("cls");
		
		timeprint();
		newmenu();
		print_menu();
		
		gotoxy(30,17);
		printf("\n메뉴를 선택하세요 : ");
		scanf("%d",&select);
		switch(select){
			case 1: 
				menu_print1();
				break;//일정기능(메뉴1)
			case 2:
				menu_print2();
				break;//부가기능(메뉴2) 
			default:
				return 0;
		}
	}
}//처음 메뉴 

int menu_print1(){
	int select;
	
	while(1){
		system("cls");
		
		timeprint();
		newmenu();
		print_menu1();
		
		gotoxy(30,17);
		printf("\n메뉴를 선택하세요 : ");
		scanf("%d",&select);
		switch(select){
			case 1: 
				input();
				break;//입력 
			case 2:
				modify();//수정 
				break;
			case 3:
				find();//검색
				break;
			case 4:
				delete1();//삭제 
				break;
			case 5:
				return 0;//종료 
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
		printf("\n메뉴를 선택하세요 : ");
		scanf("%d",&select);
		switch(select){
			case 1:
				all_print();
				break; 	//전체출력 
			case 2:
				check_OX();
				break;
			case 3:
				check_percent();
				break;
			case 4: 
				calendar();
				return 0;//종료 
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
