
//{						Header Files Used In Program
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>			//}
//{						Functions Used In Program
void intro();			 // 1.  Introductory Screen Module
void authentication();	 // 2.  Authentication & Access Control Function

void create_ac();		 // 3.  Account Creating Module
void display_all();		 // 4.  Account List Display Module
void dw(char t[30]);	 // 6.  Amount Deposit And Withdraw Control Module
void delete_account();	 // 7.  Account Delete Control Module
void modify_account();	 // 8.  Account Type Modification Control Module
void changeId();		 // 9.  Access Control Setting Module

void accountMenu(int i); // 10. To Display Account Information List
int	checkAmount();		 // 11. Balance & Amount Checking Module
void modifyThis(char option[5]);			// 12. Account Modification Module
void searchControl(char *ch, char t[30]);	//  5. Search Control and Display Module
void makeBox(int x, int y, int w, int h);	// 13. Box Design Module
void getinput(char o[10], char *data);		// 14. Input Control Mechanism Module
void cs_id(char o[10],char *u,char *p);		// 15. Access Setting Storage & Scan Module
int search(char *acnos, char *names);		// 16. Account Searching Module
//}
char spc[5]=" ";	//	Cleaner String
typedef struct		//	Data Structure Used in Program
{
	char acno[12];
	char name[20];
	char snm [20];
	char type[10];
	char balance[12];

} account;
 account ac, s[10];		//	Selected account and Searched Account Storage Varible
//~~~~~~~~~~~~~~~~	0. Main Module of this Program	~~~~~~~~~~~~~~~~
int main()
{
	char ch='1';
	textbackground(LIGHTGRAY);
	clrscr();	intro();	authentication();
	do					//	Main Menu of Program
	{	textcolor(BLACK); clrscr();
		printf("\n\n\n\t\t01. NEW ACCOUNT");
		printf("\n\n\t\t02. DEPOSIT AMOUNT");
		printf("\n\n\t\t03. WITHDRAW AMOUNT");
		printf("\n\n\t\t04. BALANCE ENQUIRY");
		printf("\n\n\t\t05. ALL ACCOUNT HOLDER LIST");
		printf("\n\n\t\t06. CLOSE AN ACCOUNT");
		printf("\n\n\t\t07. MODIFY AN ACCOUNT");
		printf("\n\n\t\t08. SECURITY SETTINGS");
		printf("\n\n\t\t09. EXIT");

		makeBox(7,2,50,20); textcolor(BLUE);
		gotoxy(10,2);	cprintf(" BANKING ACCOUNT SYSTEM ");
		gotoxy(14,24);	cprintf("Select Your Option (1-9) ");

		if(ch<49||ch>57)
		{	gotoxy(40,24);	cprintf("%c",ch);
			textcolor(RED); gotoxy(11,25);
			cprintf("Invalid Choice. Choose Valid Option");
		}
		gotoxy(40,24); ch=getch();
		switch(ch)
		{
		case '1':	create_ac(); 			break;
		case '2':	dw("Deposit Amount");	break;
		case '3':	dw("Withdraw Amount");	break;
		case '4':	searchControl(" ","Search Account");
											break;
		case '5':	display_all();			break;
		case '6':	delete_account();		break;
		case '7':	modify_account();		break;
		case '8':	changeId();				break;
		case '9':
			clrscr();
			printf("\n\n\n\n\t\t  Are you sure to exit the Program Y/N");
			ch=getch();
			if(ch=='Y'||ch=='y')
			{	printf("\n\n\n\t\tThanks for using bank management system");
				getch();	ch='9';
			}
			break;
		default :	printf("\a");
		}
    }while(ch!='9');
return 0;
}
//~~~~~~~~~~~~~~~~	16. Account Modification Control Module 	~~~~~~~~~~~~~~~~~~
void modify_account()
{
	char check[10], ch;
	int x;
	searchControl(check, "Modify Account");
	while(strcmp(check,"selected")==0)
	{	if(ac.type[0]=='S')
		{	strcpy(ac.type,"Current");	gotoxy(16,23);
			cprintf("Modify Saving A/C TO Current Account");
		}
		else
		{	strcpy(ac.type,"Saving");	gotoxy(16,23);
			cprintf("Modify Current A/C TO Saving Account");
		}
		x=checkAmount();
		if(x==0)
		{	textcolor(RED);
			gotoxy(12,25); cprintf("Enter : Modify the Account%10s",spc);
			ch=getch();
			if(ch==27) break;
			else if(ch==13)
			{	modifyThis("modify");
				gotoxy(12,25); cprintf("Account is Modified %12s",spc);
				getch();
			}
			else
			{	gotoxy(12,25);
				cprintf("Account Not Modified%12s",spc);
				getch();
			}
		}
		else
		{	gotoxy(14,23);
			cprintf("You don''t have sufficient Balance to Modify this A/C");
			getch();
		} 	break;
	}
}
//~~~~~~~~~~~~~~~~	15. Account Modifier Module 	~~~~~~~~~~~~~~~~~~
void modifyThis(char option[5])
{
	char ch;
	FILE *fp,*fpx;
	fp=fopen("bmsdata.bms","r");
	fpx=fopen("C:/Users/Public/temp.bms","w");
	do
	{	ch=fscanf(fp,"%s %s %s %s %s",s[0].acno,s[0].name, s[0].snm ,s[0].type,s[0].balance);
		if(ch==EOF) break;
		if(strcmp(ac.acno,s[0].acno)==0)
		{	if(strcmp(option,"del")!=0)
			fprintf(fpx, "%s %s %s %s %s ",ac.acno, ac.name, ac.snm, ac.type, ac.balance);
		}
		else
		fprintf(fpx, "%s %s %s %s %s ",s[0].acno, s[0].name, s[0].snm, s[0].type, s[0].balance);
	}while(1);
	fcloseall();
	remove("bmsdata.bms");
	rename("C:/Users/Public/temp.bms","bmsdata.bms");
}
//~~~~~~~~~~~~~~~~	14. Deposit And Withdraw Control Module 	~~~~~~~~~~~~~~~~~~
void dw(char title[30])
{
	long int temp;
	char check[10],ch;
	char amount[12];
	searchControl(check, title);
	while(strcmp(check,"selected")==0)
	{	gotoxy(25, 16);	cprintf("%30s",spc);
		gotoxy(25,20); cprintf("Enter Amount : %12s",spc);
		textcolor(RED);
		gotoxy(12,25); cprintf("Enter : %s  %15s",title,spc);
		gotoxy(40, 20); getinput("number",amount);

		if(amount[0]=='\0') break;
		if(strcmp(title,"Deposit Amount")==0)
				temp = atol(ac.balance)+atol(amount);
		else 	temp= atol(ac.balance)-atol(amount);

		ltoa(temp,ac.balance,10);

		if(checkAmount()==1)
		{ 	textcolor(RED); gotoxy(25,20);
			cprintf("Not Sufficient Balance");
			getch(); break;
		}

		gotoxy(43,13);	cprintf("%-30s",ac.balance);
		gotoxy(25,20);cprintf("Enter : Confirm        Any Key : Abort");
		ch=getch();

		if(ch==27) break;
		textcolor(RED);
		if(ch==13)
		{	modifyThis("deposit");
			gotoxy(12,25);
			cprintf("Balance Successfully Updated %12s",spc); getch();
		}
		else
		{	gotoxy(12,25);
			cprintf("Balance Not Updated%12s",spc); getch();
		}	break;
	}
}
//~~~~~~~~~~~~~~~~	13. Account Deleting Control Module 	~~~~~~~~~~~~~~~~~~
void delete_account()
{
	char check[10],ch;
	searchControl(check, "Delete Account"); textcolor(RED);
	while(strcmp(check,"selected")==0)
	{	gotoxy(12,25); cprintf("Enter : Delete the Account%10s",spc);
		ch=getch();
		if(ch==27) break;
		else if(ch==13)
		{	modifyThis("del");
			gotoxy(12,25);
			cprintf("Account is Deleted %12s",spc);
		} else
		{	gotoxy(12,25);
			cprintf("Account Not Deleted%12s",spc);
		}	getch(); break;
	}
}
//~~~~~~~~~~~~~~~~	12. Account Searching Module 	~~~~~~~~~~~~~~~~~~
int search(char *acnos, char *names)
{
	FILE *fp;
	char ch;
	int a=0,len;
	len = strlen(names);
	fp=fopen("bmsdata.bms","r");
	do
	{	ch=fscanf(fp,"%s %s %s %s %s",s[a].acno,s[a].name,s[a].snm,s[a].type,s[a].balance);
		if(ch==EOF) break;
		if(acnos[0]!=1)
		{	if(atol(acnos)==atol(s[a].acno))//strcmp(acnos,s[a].acno)==0)
			{	a=a+1;		break;		}
		}
		else if(strncmpi(names,s[a].name,len)==0)
		a=a+1;
	}while(ch!=EOF);
	fclose(fp); return a;
}
//~~~~~~~~~~~~~~~~	11. Search Control and Display Module 	~~~~~~~~~~~~~~~~~~
void searchControl(char *check, char title[30])
{
	int a=0, i, m, c;
	char acnos[12], names[30]="iii",ch;
	m=strcmp(title,"Search Account");
	do
	{	do
		{	accountMenu(2);	textcolor(BLUE);
			gotoxy(12,4);	cprintf(" %s ",title);
			gotoxy(25,16);	cprintf("Search by A/C by Number");
			gotoxy(43,9); textcolor(DARKGRAY);
			cprintf("Press TAB to search A/C Name  ");
			gotoxy(43,7);	getinput("acnos", acnos);		// A/C No Search Input
			if(acnos[0]=='\0'||acnos[0]!=1) break;

			gotoxy(43,7); textcolor(DARKGRAY);
			cprintf("Press TAB to search A/C Number");
			gotoxy(43,9);	textcolor(BLUE);	cprintf("                            ");
			gotoxy(25,16);	cprintf("Search by A/C by Name  ");
			gotoxy(43,9);	getinput("names", names);		// A/C Name Search Input
			if(names[0]=='\0'||names[0]!=1) break;
		}while(1==1);
		if(acnos[0]=='\0'||names[0]=='\0') break;

		a=search(acnos,names);
		if(a>0)
		{	for(i=0;i<a;i++)
			{	c=i;
				gotoxy(43,7);	cprintf("%-30s",s[c].acno);
				gotoxy(43,9);	cprintf("%s %-20s",s[c].name,s[c].snm);
				gotoxy(43,11);	cprintf("%-30s",s[c].type);
				gotoxy(43,13);	cprintf("%-30s",s[c].balance);
				gotoxy(25,16);	cprintf("%d Account Found %-10s",a,spc);
				gotoxy(16,23);	cprintf("Press Any Key to see Next Result");
				if(m!=0)
				{	gotoxy(12,25);
					textcolor(RED);
					cprintf("Enter: Select to %s",title);
					textcolor(BLUE);
				}
				if(a!=1&&i<a-1)	ch=getch(); if(ch==27)	break;
				if(m!=0&&ch==13) break;
				gotoxy(25,16);if(a!=1&&i==a-1)	cprintf("No More Results %20s",spc);
			}
			gotoxy(16,23);	cprintf("Do you want to search another account Y/N");
			if(a==1||i==a) ch=getch();
			if(m!=0&&ch==13)
			{	strcpy(ac.acno,s[c].acno);
				strcpy(ac.name,s[c].name);
				strcpy(ac.snm,s[c].snm);
				strcpy(ac.type,s[c].type);
				strcpy(ac.balance,s[c].balance);
				strcpy(check,"selected");
				gotoxy(16,23); cprintf("This Account is Selected %20s",spc);
			}
		}
		else
		{	gotoxy(25,16); cprintf("No Account Found       ");
			gotoxy(16,23);	cprintf("Do u want to search another account Y/N");
			ch=getch();
		}
	}while(ch=='Y'||ch=='y');
}
//~~~~~~~~~~~~~~~~	10. Account List Display Module 	~~~~~~~~~~~~~~~~~~
void display_all()
{
	int a=1, sno=0, page=1, i;
	char ch;
	FILE *fp;
	clrscr();	makeBox(5,2,72,23); textcolor(BLUE);
	gotoxy(15,2); cprintf(" List of All Bank Accounts ");

	textcolor(BLACK);
	gotoxy(6,5);
	for(i=0;i<35;i++) cprintf("__");
	gotoxy(7,4);	cprintf("Sn");
	gotoxy(11,4);	cprintf("A/C no");		gotoxy(23,4);	cprintf("A/C Holder's Name");
	gotoxy(49,4);	cprintf("A/C Type");	gotoxy(60,4);	cprintf("Total Balance");

	textcolor(BLUE);
	fp=fopen("bmsdata.bms","r");
	do
	{	a=(sno%18)+6;
		sno=sno+1;
		ch=fscanf(fp,"%s %s %s %s %s",ac.acno, ac.name, ac.snm, ac.type, ac.balance);
		if(ch==EOF) break;
		if(a%2==1) textcolor(BLUE); else textcolor(LIGHTBLUE);
		gotoxy(7,a);	cprintf("%2d",sno);
		gotoxy(11,a);	cprintf("%s",ac.acno);
		gotoxy(23,a);	cprintf("%s %-15s",ac.name,ac.snm);
		gotoxy(49,a);	cprintf("%s",ac.type);
		gotoxy(60,a);	cprintf("Rs %s",ac.balance);
		gotoxy(68,24); cprintf(" Page %d",page);
		if(sno%18==0)
		{	i=0;	page++;
			gotoxy(10,25); textcolor(RED);
			cprintf(" Enter : Next Page ");
			gotoxy(58,25);	cprintf(" ESC : Main Menu ");
			ch=getch(); textcolor(BLUE);
			if(ch==27) break;
			do
			{	a=i+6;	i=i+1;	gotoxy(7,a);
				cprintf("%70s",spc);//Eraser if do repeats
			}while(i!=18);
		}
	}while(1==1);
	fclose(fp);
	if(ch!=27) getch();
}
//~~~~~~~~~~~~~~~~	9. Balance & Amount Checking Module 	~~~~~~~~~~~~~~~~~~
int checkAmount()
{
	int a=0;
	if(strcmp(ac.type,"Saving")==0)
	{	if(atol(ac.balance)<500)
		{	gotoxy(12,25); a=1; textcolor(RED);
			cprintf("Min Balance : 500%20s",spc);
			printf("\a");
		}
	}
	else
	{	if(atol(ac.balance)<1000)
		{	gotoxy(12,25); a=1; textcolor(RED);
			cprintf("Min Balance: 1000%20s",spc);
			printf("\a");
		}
	}
	textcolor(BLUE);
	return a;
}
//~~~~~~~~~~~~~~~~	8. Account Creating Module 	~~~~~~~~~~~~~~~~~~
void create_ac()
{
	int amount, a=0;
	char ch;
	FILE *fp;
	do
	{	accountMenu(1);	textcolor(BLUE);
		gotoxy(12,4);	cprintf(" New Account ");
		do											// Account Number Input
		{	gotoxy(16,17);	cprintf("        Accepts Number Only       ");
			gotoxy(43,7);	cprintf("%-30s",spc);	//Eraser if do repeats

			gotoxy(43,7);	getinput("acno", ac.acno);
			if(ac.acno[0]=='\0') break;				//	ESC Key
			a=search(ac.acno,ac.name);				//Check if Account Exists
			if(a>0)
			{	gotoxy(16,24);
				cprintf("Account Number Already Exists");
				printf("\a");
			}
		} while(a!=0);
		if(ac.acno[0]=='\0') break;					//ESC Key
		gotoxy(16,24);	cprintf("%-30s",spc);		//erasers
		gotoxy(16,17);	cprintf("%-30s",spc);		//erasers

		gotoxy(43,9);	getinput("name",ac.name);
		if(ac.name[0]=='\0') break;					//ESC Key

		gotoxy(43,11);	getinput("name",ac.snm);
		if(ac.snm[0]=='\0') break;					//ESC Key
		gotoxy(16,17);	cprintf("C=Current A/C   S:Saving A/C");

		gotoxy(43,13);	getinput("type", ac.type); strupr(ac.type);
		if(ac.type[0]=='S') strcpy(ac.type,"Saving");
		else strcpy(ac.type,"Current");
		if(ac.type[0]=='\0') break;				//ESC Key
		do
		{	gotoxy(16,17);	cprintf("%13sAccepts Number Only    ",spc);
			gotoxy(43,15);	cprintf("%-30s",spc);	//Eraser if do repeats
			gotoxy(43,15);	getinput("number", ac.balance);
			if(ac.balance[0]=='\0') break;		//ESC Key
			a=checkAmount();
		} while(a==1);
		if(ac.balance[0]=='\0') break;				//ESC Key

		gotoxy(16,17);
		cprintf("Are you sure to create this Account Y/N");
		ch=getch();
		gotoxy(16,17);
		if(ac.balance[0]=='\0') break;
		else if (ch=='y'||ch=='Y')
		{	cprintf("%13sAccount Created%13s",spc,spc);
			fp = fopen("bmsdata.bms","a");
			fprintf(fp, "%s %s %s %s %s ", ac.acno, ac.name, ac.snm, ac.type, ac.balance);
			fclose(fp);
		}
		else cprintf("         Account Not Not Created       ");
		gotoxy(16,23);	cprintf("Do you want to create another account Y/N");
		ch=getch();
	}while(ch=='Y'||ch=='y');
}
//~~~~~~~~~~~~~~~~	7. Account Detail Information List 	~~~~~~~~~~~~~~~~~~
void accountMenu( int i)
{
	int a=1;
	textcolor(BLACK); clrscr(); gotoxy(10,5);
	printf("\n\n\t   %d.	Account Number		:",a++);
	printf("\n\n\t   %d.	A/C Holder's Name 	:",a++);
	if(i==1)
	printf("\n\n\t   %d.	A/C Holder's Surname	:",a++);
	printf("\n\n\t   %d.	Account Type 		:",a++);
	printf("\n\n\t   %d.	Balance Amount	 	:",a++);
	makeBox(8,4,65,14); textcolor(RED);
	gotoxy(55,25);	cprintf("ESC : Main Menu");
}
//~~~~~~~~~~~~~~~~	6. Access Control Setting Module	~~~~~~~~~~~~~~
void changeId()
{
char ch='1';
char username[30]="user", inuser[30],temp[30];
char password[30]="pass", inpass[30];
do
	{
	textcolor(BLACK); clrscr(); gotoxy(10,5);
	printf("\n\n\t\t1.	Change Username");
	printf("\n\n\t\t2.	Change Password");
	printf("\n\n\t\t3.	Lock Screen");
	printf("\n\n\t\t4.	Back");
		if(ch<49||ch>52)
		{	gotoxy(41,22);	cprintf("%c",ch);
			textcolor(RED); gotoxy(11,25);
			cprintf("Invalid Choice. Choose Valid Option");
		}
		makeBox(8,4,50,15);
		textcolor(BLUE);
		gotoxy(10,4);	cprintf(" SECURITY SETTINGS ");
		gotoxy(14,22);	cprintf("Select Your Option (1-4) : ");
		ch=getch();
		switch(ch)
		{
			case '1':
				do
				{	textcolor(BLACK); clrscr(); gotoxy(10,7);
					printf("\t\t Enter a new Username");
					makeBox(16,10,34,3); makeBox(8,4,52,15);
					textcolor(BLUE);
					gotoxy(10,4);	cprintf(" CHANGE USERNAME ");
					gotoxy(20,12);	getinput("user",inuser);
					gotoxy(16,17);	cprintf("Enter Password to change your Username");
					gotoxy(20,15);	getinput("password",inpass);
					gotoxy(16,17);
					cs_id("scan",username,password);
					if(strcmp(password,inpass)==0)
					{	cs_id("change",inuser,password);
						cprintf("            Username Changed            ");
					}
					else
					{	cprintf("          Username Not Changed          ");
						textcolor(RED); gotoxy(25,25);
						printf("\a"); cprintf("Wrong Password : Try Again Y/N");
					}
					ch=getch();
				}while(ch=='y'||ch=='Y');
			break;
			case '2':
				do
				{	cs_id("scan",username,password);
					textcolor(BLACK); clrscr(); gotoxy(5,5);
					printf("\n\n\t   Enter Old Password :");
					printf("\n\n\t   Enter New Password :");
					makeBox(8,4,62,15);
					textcolor(BLUE);
					gotoxy(10,4);	cprintf(" CHANGE PASSWORD ");
					gotoxy(35,7);	getinput("password",temp);

					if(strcmp(password,temp)!=0)
					{	textcolor(RED); gotoxy(11,25);
						cprintf("Wrong Password :");
					}
					else
					{	gotoxy(35,9);	getinput("password",inpass);
						gotoxy(12,11);	printf("New Password Again :");
						gotoxy(35,11);	getinput("password",temp);

						gotoxy(16,16);
						if(strcmp(inpass,temp)!=0)
						cprintf("New Passwords do not Match :");
						else
						{	cprintf("Are you sure to change your Password Y/N");
							ch=getch();	gotoxy(16,16);
							if(ch=='y'||ch=='Y')
							{	cs_id("change",username,inpass);
								cprintf("%13sPassword Changed%13s",spc,spc);
								getch();
								break;
							}
							else cprintf("%12sPassword Not Changed%12s",spc,spc);
						}
					}
					textcolor(RED); gotoxy(30,25);
					cprintf("Try Again Y/N");
					printf("\a");
					ch=getch();
				}while(ch=='y'||ch=='Y');
			break;
			case '3':
				authentication();
				ch='4';
			break;
			case '4':
			break;
			default :
				 printf("\a");
		 }
	}while(ch!='4');
}
//~~~~~~~~~~~~~~~~	5. Access Setting Storage and Scan Module	~~~~~~~~~~
void cs_id(char option[10], char *username, char *password)
{
	FILE *fp;
	fp = fopen("bms.bms","r");

	if((strcmp(option,"change")!=0)&&(fp!=NULL))
	{	fscanf(fp,"%s %s",username,password);
		fclose(fp);
	}
	else
	{	if(fp==NULL)
		{	gotoxy(18,12);textcolor(LIGHTRED);
			cprintf("First Run: Defaults User: %s    Password: %s",username,password);
		}
	fp = fopen("bms.bms","w");
	fprintf(fp,"%s %s",username,password);
	fclose(fp);
	}
/*
	if(strcmp(option,"change")==0)
		{
			fp = fopen("bms.bms","w");
			fprintf(fp,"%s %s",username,password);
			fclose(fp);
		}
	else
		{
			fp = fopen("bms.bms","r");
			if(fp==NULL)
				{
					gotoxy(18,10);textcolor(GREEN);
					cprintf("First Run:  Default User : %s Password : %s",username,password);
					fp = fopen("bms.bms","w");
					fprintf(fp,"%s %s",username,password);
					fclose(fp);
				}
			else
				{
					fscanf(fp,"%s %s",username,password);
					fclose(fp);
				}
		} */
}
//~~~~~~~~~~~~~~~~	4. Input Control Mechanism Module	~~~~~~~~~~~~~~
void getinput(char option[10], char *data)
{
	int i, a, s=0;
	char temp;
	char string1[31]="\0";

	if(strcmp(option,"number")==0) a=9;
	else if (strcmp(option,"type")==0) a=1;
	else if (strcmp(option,"acno")==0) a=10;
	else if (strcmp(option,"acnos")==0) {a=10; s=1;}
	else if (strcmp(option,"names")==0) {a=15; s=1;}
	else if (strcmp(option,"name")==0) a=15;
	else a=30;

	textcolor(LIGHTBLUE);
	while(string1[0]=='\0')
	{	for(i=0;i<a+1;)
		{	temp=getch();
			  if(temp==8)				// Action of Backspace Key
				 {	if(i<1) break;		// Prevents Unwanted Backspace
					printf("%c%c%c",8,32,8);
					i-=2;
				 }		//	TAB and Esc does nothing If Password and Username
			  else if(((strcmp(option,"password")==0)||(strcmp(option,"user")==0))&&(temp==9||temp==27))
			  i--;
			  else if(temp==27) break;
			  else if(temp==9||temp==13) break;	// Action of TaB and Enter
			  else if(temp==32) i--;			// Action of Esc Key and Space
			  else if(i==a) i--;				// Prevents array Overflow Typings
			  else if ((a==1)&&((temp==99||temp==115||temp==67||temp==83))==0)
			  i--;								// Input only S, C, OR s, c
			  else if(((a==9)||(a==10))&&(temp<48||temp>57))
			  i--;								// Filters Number
			  else
				{	string1[i]=temp;
					if(strcmp(option,"password")==0)
					cprintf("*");
					else
					cprintf("%c",string1[i]);
				}
			i++;
			string1[i]='\0'; // put null at the end of the array
		}
		if(temp==27) { string1[0]='\0'; break;}
		if(s==1&&temp==9) { string1[0]=1; break;}
	}
	textcolor(BLUE);
	strcpy(data,string1);
}
//~~~~~~~~~~~~~~~~	3. Autentication & Access Control Fucntion	~~~~~~~~~~~~~~~~~~~~~~
void authentication()
{
	char username[30]="user";		// Actual & Default Username at first run
	char password[30]="pass";		// Actual & Default Password at first run
	char inuser[30], inpass[30];	// Username & Password received from input
	int attempts;

	clrscr();
	cs_id("scan",username,password);	//	Scan Username and Password from file

	textcolor(BLUE);			// Text Colour
	gotoxy(33,7);	cprintf("BANK MANAGEMENT");
	gotoxy(37,9);	cprintf("SYSTEM");
	makeBox(16,14,50,6);
	textcolor(BLACK);
	gotoxy(22,16);	cprintf("Username: ");
	gotoxy(22,18);	cprintf("Password: ");

	for(attempts=5;attempts>0;attempts--)
	{	// To erase the previous inputs
		gotoxy(32,16); cprintf("%-30s",spc);
		gotoxy(32,18); cprintf("%-30s",spc);

		// getinput is userdefined input module
		gotoxy(32,16); getinput("user",inuser);
		gotoxy(32,18); getinput("password",inpass);

		textcolor(BLACK); gotoxy(15,22);
		if(strcmp(username,inuser)==0 && strcmp(password,inpass)==0)
		{	cprintf("Username and password authenticated. Access Granted");
			gotoxy(25,24); cprintf("Press any key to continue");
			getch();
			break;
		}
		else if(attempts==1)
		{	clrscr();
			gotoxy(10,10); cprintf("Your are not Authenticated. Access Denied.");
			getch();
			exit(0);
		}
		else
		{	textcolor(RED);
			cprintf("Access Denied. Re-enter Username and Password.");
			gotoxy(25,24);
			cprintf("    Attempts Left: %i"    ,attempts-1);
		}
	}
}
//~~~~~~~~~~~~~~~~	2. Introductory Screen Module	~~~~~~~~~~~~~~~~
void intro()
{
	clrscr();
	makeBox(11,3,60,12);	// For outer Double Title border
	makeBox(16,5,50,8);		// For Inner Double Title border

	textcolor(BLUE);			// Text Colour
	gotoxy(35,7);	cprintf("WEL-COME TO");
	gotoxy(33,9);	cprintf("BANK MANAGEMENT");
	gotoxy(37,11);	cprintf("SYSTEM");
	gotoxy(20,20);	cprintf("Project By by: Tapendra Pandey");
	gotoxy(15,24);	cprintf("Pulchowk Engineering College" );
	getch();
}
//~~~~~~~~~~~~~~~~	1. Box Design Module	~~~~~~~~~~~~~~~~
void makeBox(int x, int y, int w, int h)
{
	int n;	//x & y are coordintes w and h are width and height
	textcolor(MAGENTA);		// Border will be Magenta in whole program

	gotoxy(x, y);		cprintf("%c",201);		//	Top Left Corner
	gotoxy(x+w, y);		cprintf("%c",187);		//	Top Right Corner
	gotoxy(x, y+h);		cprintf("%c",200);		//	Bottom Left Corner
	gotoxy(x+w, y+h); 	cprintf("%c",188);		//	Bottom Right Corner

	for(n=x+1; n<x+w; n++)		// Horizontal lines
	{	gotoxy(n, y);	cprintf("%c",205);		// Top horizontal line
		gotoxy(n, y+h);	cprintf("%c",205);		// Bottom horizontal line
	}

	for(n=y+1; n<y+h; n++)		// Vertical lines
	{	gotoxy(x,n);	cprintf("%c",186);		// Left Vertical line
		gotoxy(x+w,n);	cprintf("%c",186);		// Right Vertical line
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    			END OF PROJECT
//***************************************************************
