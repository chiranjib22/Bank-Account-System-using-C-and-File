#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// declaring all sub modules

void account(void);
void accountCreated(void);
void login(void);
void loginSuccess(char[]);
void display(char[]);
void transferMoney(char[]);
void checkBalance(char[]);
void updateBalance(char[], double, char[]);
void withdrawMoney(char[]);
void depositMoney(char[]);
void transactionHistory(char[]);
void logout(void);

//creating a structure to store input data of the user from console

struct user {
  char username[50];
  int date, month, year;
  char pNumber[15];
  char fname[20];
  char lname[20];
  char fatherName[20];
  char motherName[20];
  char address[50];
  char typeAccount[20];
  char NID[20];
  char password[20];
  double balance;
};

// structure to keep track of amount transfer
struct transaction {
  char usernameFrom[50];
  char usernameTo[50];
  char type[10];
  double money1;
};

int main() {
  system("clear");
  int i, a, b, choice;

  //creating a main menu for the user
  printf("================================\n");
  printf("WELCOME TO BANK ACCOUNT SYSTEM\n");
  printf("================================\n");

  printf("\tDEV-Chiranjib-HSTU\n\n");
  printf("1. CREATE A BANK ACCOUNT\n");
  printf("2. ALREADY A USER? SIGN IN\n");
  printf("3. Exit\n\n");
  printf("Enter Your Choice : ");
  scanf("%d", & choice);
  getchar();

  switch (choice) {
  case 1:
    account();
    break;
  case 2:
    login();
    break;
  case 3:
    exit(0);
    break;
  }
  return 0;
}

//Create accounts of users
void account(void) {
  char password[20];
  int i, j,found = 0;
  char ch;

  FILE * fp, *fq;

  struct user u1,u2;

  //opening file to write data of a user
  fp = fopen("userData.txt", "ab");
  fq = fopen("userData.txt", "rb");
  if (!fp || !fq) {
    printf("ERROR IN FILE OPENING.\n");
    main();
  }
  //inputs
  system("clear");
  printf("============================\n");
  printf("\tCREATE ACCOUNT\n");
  printf("============================\n\n");


  printf("\nFIRST NAME: ");
  scanf("%s", u1.fname);
  printf("\nLAST NAME: ");
  scanf("%s", u1.lname);
  getchar();
  printf("\nFATHER'S NAME: ");
  scanf("%[^\n]%*c", u1.fatherName);
  printf("\nMOTHER'S NAME: ");
  scanf("%[^\n]%*c", u1.motherName);
  printf("\nADDRESS: ");
  scanf("%[^\n]%*c", u1.address);
  printf("\nACCOUNT TYPE: ");
  scanf("%s", u1.typeAccount);
  printf("\nDATE OF BIRTH(DD/MM/YYYY): ");
  scanf("%d/%d/%d", & u1.date, & u1.month, & u1.year);
  printf("\nNID NO : ");
  scanf("%s", u1.NID);
  printf("\nPHONE NUMBER(01*********): ");
  scanf("%s", u1.pNumber);
  D:printf("\nUSERNAME : ");
  scanf("%s", u1.username);
  getchar();

  //check weather the username is unique or not
  while(fread(&u2,sizeof(u2),1,fq))
  {
    if(strcmp(u2.username,u1.username) == 0)
    {
      found = 1;
      break;
    }
  }
  if(found)
  {
    printf("\nALREADY REGISTERED USERNAME!!\nPlease input another username..!\n");
    found = 0;
    goto D;
  }
  A: printf("\nSET A PASSWORD: ");

  //taking password in the form of stars;
  i = 0;
  while (scanf("%c", & ch) && ch != '\n') {
    u1.password[i++] = ch;
  }
  u1.password[i] = '\0';
  if (i == 0) goto A; // if password didn't given

  u1.balance = 0.0; // new user balance

  //writing to the file  
  j = fwrite( & u1, sizeof(u1), 1, fp);
  fclose(fp);

  // calling the accountCreated()
  if (j == 1)
    accountCreated();
  else {
    printf("FAILED TO STORE!\n");
    printf("Press Enter to registration again : ");
    getchar();
    account();
  }
}

//successful account creation
void accountCreated(void) {
  int i,j;
  char ch;
  printf("PLEASE WAIT!! YOUR DATA IS PROCESSING.....\n");
  for(i = 0; i<20; i++)
  {
    for(j = 0; j<20000000; j++)
    {
      i++;
      i--;
    }
    printf(".");
  }
  system("clear");
  printf("\nACCOUNT CREATED SUCCESSFULLY...\n");
  printf("Press Enter to Login: ");
  getchar();
  login();
}

//login function to check the username and password of the user
void login(void) {
  system("clear");

  char username[50];
  char password[50];

  struct user u1;
  int i, j, k;
  char ch;
  FILE * fp;

  //opening file of user data
  fp = fopen("userData.txt", "rb");

  if (fp == NULL) {
    printf("ERROR IN FILE OPENING.\n");
    printf("Please Enter to HOME...\n");
    getchar();
    main();
  }
  printf("===============\n");
  printf("ACCOUNT LOGIN\n");
  printf("===============\n\n");
  printf("USERNAME: ");
  scanf("%s", username);
  getchar();
  printf("\nPASSWORD: ");
  scanf("%s%*c", password);

  //user authentication
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if ((strcmp(username, u1.username) == 0) && (strcmp(password, u1.password) == 0)) {
      loginSuccess(username);
      system("clear");
      main();
    }
  }
  // if the user isn't found
  if (feof(fp)) {
    printf("\nWRONG USERNAME OR PASSWORD!!\nPlease Enter to HOME");
    getchar();
    system("clear");
    main();
  }

  //closing the file
  fclose(fp);
}

void loginSuccess(char userName[]) {
  int i,j;
  printf("\nFetching account details..\n");
  for(i = 0; i<20; i++)
  {
    for(j = 0; j<20000000; j++)
    {
      i++;
      i--;
    }
    printf(".");
  }
  printf("\nSUCCESSFULLY LOGGED IN AS '%s'...\n", userName);
  printf("Press enter to continue\n");
  getchar();
  display(userName);
}

// display function for logged user
void display(char userName[]) {
  system("clear");
  FILE * fp;
  int choice, i,j;
  struct user u1;

  fp = fopen("userData.txt", "rb");

  if (fp == NULL) {
    printf("ERROR IN OPENING FILE!");
    exit(1);
  }
  // search in the userData file to display his/her information
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if (strcmp(userName, u1.username) == 0) {
      printf("============================\n\n");
      printf("WELCOME %s %s\n", u1.fname, u1.lname);
      printf("YOUR ACCOUNT INFORMATION\n\n");
      printf("============================\n\n");

      printf("NAME          : %s %s\n", u1.fname, u1.lname);
      printf("FATHER'S NAME : %s\n", u1.fatherName);
      printf("MOTHER'S NAME : %s\n", u1.motherName);
      printf("NID NO        : %s\n", u1.NID);
      printf("MOBILE NO     : %s\n", u1.pNumber);
      printf("DATE OF BIRTH : %d-%d-%d\n", u1.date, u1.month, u1.year);
      printf("ADDRESS       : %s\n", u1.address);
      printf("ACCOUNT TYPE  : %s\n", u1.typeAccount);
    }
  }
  printf("\n========USER MENU========\n\n");
  printf("1. CHECK BALANCE\n");
  printf("2. DEPOSIT MONEY\n");
  printf("3. TRANSFER MONEY\n");
  printf("4. WITHDRAW MONEY\n");
  printf("5. TRANSACTION HISTORY\n");
  printf("6. LOG OUT\n");
  printf("7. EXIT\n");
  printf("\nEnter your choice : ");
  scanf("%d", & choice);
  getchar();
  // create menu for logged user
  switch (choice) {
  case 1:
    checkBalance(userName);
    break;
  case 2:
    depositMoney(userName);
    break;
  case 3:
    transferMoney(userName);
    display(userName);
    break;
  case 4:
    withdrawMoney(userName);
    break;
  case 5:
    transactionHistory(userName);
    break;
  case 6:
    logout();
    login();
    break;
  case 7:
    system("clear");
    exit(0);
  }
}

//function to transfer money from one user to another
void transferMoney(char userName[]) {
  int i, j, found = 0;
  double money = 0;
  FILE * fp, *fq, * fm;
  struct user u1,u2;
  struct transaction m1;

  char usernameTo[20];
  char currentPassword[20];
  system("clear");

  // opening file in read mode to read user's username;
  fp = fopen("userData.txt", "rb");
  fq = fopen("userData.txt", "rb");
  //creating an another file to write amount along with username to which amount is going to be transferred
  fm = fopen("moneyInfo.txt", "ab");
  if (!fp || !fm) {
    printf("ERROR IN OPENING FILE.\n");
    exit(1);
  }

  printf("===============\n");
  printf("TRANSFER MONEY\n");
  printf("===============\n\n");
  printf("FROM(YOUR USERNAME) : %s\n", userName);
  B: printf("\nTO (username of person you want to transfer): ");
  scanf("%s", usernameTo);
  getchar();

  rewind(fp);
  rewind(fm);

  //checking the sender username
  while(fread(&u2, sizeof(u2),1,fq)){
    if(strcmp(userName,u2.username) == 0){
      break;
    }
  } 
  //checking for username in which the transaction is transferred
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if (strcmp(usernameTo, u1.username) == 0) {
      found = 1;
      break;
    }
  }
  // if the user isn't found
  if (feof(fp)) {
    printf("\nUSER NOT FOUND!!ENTER CORRECT USERNAME TO TRANSFER\n");
    goto B;
  }

  //Taking amount input
  printf("\nENTER THE AMOUNT TO BE TRANSFERRED : ");
  scanf("%lf", & money);
  getchar();
  if (u2.balance - money > 0) {
    //Take user password to confirm transaction
    C: printf("\nENTER YOUR PASSWORD TO CONFIRM TRANSACTION : ");
    scanf("%s", currentPassword);
    getchar();
    // to check if the user password is correct or not. If correct save the transaction to the moneyInfo file
    if (strcmp(u2.password, currentPassword) == 0 && found) {
      strcpy(m1.usernameTo, usernameTo);
      strcpy(m1.usernameFrom, userName);
      strcpy(m1.type, "transfer");
      m1.money1 = abs(money);
      j = fwrite( & m1, sizeof(m1), 1, fm);
      // check the storing process in the moneyInfo.txt file is successfully executed or not?
      if (j == 1) {
        printf("\nTRANSFERRING AMOUNT, PLEASE WAIT..\n");
        for(i = 0; i<20; i++)
        {
          for(j = 0; j<20000000; j++)
          {
            i++;
            i--;
          }
          printf(".");
        }
        //update the balance in that both userInfo
        updateBalance(userName,m1.money1,"withdraw");
        updateBalance(usernameTo,m1.money1,"deposit");

        printf("\nAMOUNT SUCCESSFULLY TRANSFERRED TO %s\n", usernameTo);
        printf("\nPress Enter to goto USER MENU again..");
        getchar();
        fclose(fp);
        fclose(fm);
        display(userName);
      } else {
        printf("\nFAILED TO TRANSFER!\n");
        printf("Press Enter to goto USER MENU again..");
        getchar();
        fclose(fp);
        fclose(fm);
        display(userName);
      }
    } else {
      printf("\nWRONG PASSWORD!");
      goto C;
    }
  }
  else {
    printf("INSUFFICIENT BALANCE!\n");
    printf("Press Enter to goto USER MENU again..");
    getchar();
    display(userName);
  }
}

// to check user balance
void checkBalance(char userName[]) {
  system("clear");
  printf("============================\n");
  printf("\tWELCOME %s\n", userName);
  printf("============================\n\n");
  
  FILE *fq = fopen("userData.txt","rb");
  struct user u2;

  while(fread(&u2, sizeof(u2),1,fq)){
    if(strcmp(userName,u2.username) == 0){
      break;
    }
  }
  if (feof(fq)) {
    printf("\nUSER NOT FOUND!!\n");
    printf("\nPlease Enter to USER MENU\n");
    getchar();
    display(userName);
  }
  printf("YOUR CURRENT BALANCE IS : %lf TK.\n", u2.balance);
  printf("\nPlease Enter to back to USER MENU.");
  getchar();
  display(userName);
}

// to withdraw money
void withdrawMoney(char userName[]) {
  int i, j, found = 0;
  double money = 0;
  FILE * fp, * fm;
  struct user u1;
  struct transaction m1;
  char currentPassword[20];
  system("clear");

  // opening file in read mode to read user's username;
  fp = fopen("userData.txt", "rb");
  //creating an another file to write amount along with username to which amount is going to be transferred
  fm = fopen("moneyInfo.txt", "ab");
  if (!fp || !fm) {
    printf("ERROR IN OPENING FILE.\n");
    exit(1);
  }

  printf("===============\n");
  printf("WITHDRAW MONEY\n");
  printf("===============\n\n");
  printf("YOUR USERNAME : %s\n", userName);
  rewind(fp);
  rewind(fm);

  //checking for username in which the transaction is transferred
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if (strcmp(userName, u1.username) == 0) {
      found = 1;
      break;
    }
  }
  // if the user isn't found
  if (feof(fp)) {
    printf("\nUSER NOT FOUND!!ENTER CORRECT USERNAME TO TRANSFER\n");
    display(userName);
  }

  //Taking amount input
  printf("\nENTER THE AMOUNT TO BE WITHDRAWN : ");
  scanf("%lf", & money);
  getchar();
  if (u1.balance - money > 0) {
    //Take user password to confirm transaction
    C: printf("\nENTER YOUR PASSWORD TO CONFIRM TRANSACTION : ");
    scanf("%s", currentPassword);
    getchar();
    // to check if the user password is correct or not. If correct save the transaction to the moneyInfo file
    if (strcmp(u1.password, currentPassword) == 0 && found) {
      strcpy(m1.usernameTo, userName);
      strcpy(m1.usernameFrom, "BANK");
      strcpy(m1.type, "withdraw");
      m1.money1 = abs(money);
      j = fwrite( & m1, sizeof(m1), 1, fm);
      // check the storing process in the moneyInfo.txt file is successfully executed or not?
      if (j == 1) {
        printf("\nWITHDRAWING AMOUNT, PLEASE WAIT..\n");

        for(i = 0; i<20; i++)
        {
          for(j = 0; j<20000000; j++)
          {
            i++;
            i--;
          }
          printf(".");
        }
        //update the balance of the user
        updateBalance(userName,m1.money1,m1.type);
        printf("\nAMOUNT WITHDRAW IS SUCCESSFUL.\n");
        printf("\nPress Enter to goto USER MENU again..");
        getchar();
        fclose(fp);
        fclose(fm);
        display(userName);
      } else {
        printf("\nFAILED TO WITHDRAW!\n");
        printf("Press Enter to goto USER MENU again..");
        getchar();
        fclose(fp);
        fclose(fm);
        display(userName);
      }
    } else {
      printf("\nWRONG PASSWORD!");
      goto C;
    }
  }
  else {
    printf("INSUFFICIENT BALANCE!\n");
    printf("Press Enter to goto USER MENU again..");
    getchar();
    display(userName);
  }
}

// deposit money to the account
void depositMoney(char userName[]) {

  int i, j, found = 0;
  double money = 0;
  FILE * fp, * fm;
  struct user u1;
  struct transaction m1;
  char currentPassword[20];
  system("clear");

  // opening file in read mode to read user's username;
  fp = fopen("userData.txt", "rb");
  //creating an another file to write amount along with username to which amount is going to be transferred
  fm = fopen("moneyInfo.txt", "ab");
  if (!fp || !fm) {
    printf("ERROR IN OPENING FILE.\n");
    exit(1);
  }

  printf("===============\n");
  printf("DEPOSIT MONEY\n");
  printf("===============\n\n");
  printf("YOUR USERNAME : %s\n", userName);
  rewind(fp);
  rewind(fm);

  //checking for username in which the deposit occurs.
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if (strcmp(userName, u1.username) == 0) {
      found = 1;
      break;
    }
  }
  // if the user isn't found
  if (feof(fp)) {
    printf("\nUSER NOT FOUND!!ENTER CORRECT USERNAME TO TRANSFER\n");
    display(userName);
  }

  //Taking amount input
  printf("\nENTER THE AMOUNT TO BE DEPOSIT : ");
  scanf("%lf", &money);
  getchar();
  //Take user password to confirm transaction
  C: printf("\nENTER YOUR PASSWORD TO CONFIRM DEPOSIT : ");
  scanf("%s", currentPassword);
  getchar();
  // to check if the user password is correct or not. If correct save the transaction to the moneyInfo file
  if (strcmp(u1.password, currentPassword) == 0 && found) {
    strcpy(m1.usernameTo, "BANK");
    strcpy(m1.usernameFrom, userName);
    strcpy(m1.type, "deposit");
    m1.money1 = abs(money);
    j = fwrite( & m1, sizeof(m1), 1, fm);
    // check the storing process in the moneyInfo.txt file is successfully executed or not?
    if (j == 1) {
      printf("\nDEPOSITING AMOUNT, PLEASE WAIT..\n");
        for(i = 0; i<20; i++)
        {
          for(j = 0; j<20000000; j++)
          {
            i++;
            i--;
          }
          printf(".");
        }

      //update the balance of the user
      updateBalance(userName,m1.money1,m1.type);
      printf("\nAMOUNT DEPOSIT IS SUCCESSFUL.\n");
      printf("\nPress Enter to goto USER MENU again..");
      getchar();
      fclose(fp);
      fclose(fm);
      display(userName);
    } else {
      printf("\nFAILED TO DEPOSIT!\n");
      printf("Press Enter to goto USER MENU again..");
      getchar();
      fclose(fp);
      fclose(fm);
      display(userName);
    }
  } else {
    printf("\nWRONG PASSWORD!");
    goto C;
  }
}

void updateBalance(char userName[],double money, char type[]) {
  // opening the binary file in read-write mode
  FILE * fp = fopen("userData.txt", "r+b");

  if (fp == NULL) {
    printf("ERROR IN FILE OPENING.\n");
    exit(1);
  }

  struct user u1;
  int found = 0;

  //read each record from the userInfo file
  while (fread( & u1, sizeof(u1), 1, fp)) {
    if (strcmp(u1.username, userName) == 0) {
      found = 1;
      
      if(strcmp(type,"withdraw") == 0)
      {
        u1.balance -= money;
      }
      else
      {
        u1.balance += money;
      }

      //move the file pointer back to the start of the current record
      fseek(fp, -sizeof(struct user), SEEK_CUR);

      //update the record with new balance
      fwrite(&u1, sizeof(u1),1,fp);
      fclose(fp);
      break;
    }
  }

  if(!found)
  {
    printf("USER NOT FOUND!\n");
    fclose(fp);
    return;
  }
  return ;
}

void logout(void)
{
  system("clear");
  printf("\n\nPLEASE WAIT, LOGGING OUT!!!\n");

  int i, j;
  for(i = 0; i<20; i++)
  {
    for(j = 0; j<20000000; j++)
    {
      i++;
      i--;
    }
    printf(".");
  }

  printf("\nSIGN OUT SUCCESSFULLY....\n");
  printf("Press any key to continue..");
  getchar();
  main();
}

void transactionHistory(char userName[])
{
  system("clear");
  struct transaction m1;
  FILE *fp = fopen("moneyInfo.txt","rb");

  if(fp == NULL)
  {
    printf("ERROR IN OPENING FILE\nPlease Enter to USER MENU..\n");
    getchar();
    display(userName);
  }

  printf("==================================\n");
  printf("TRANSACTION HISTORY OF %s\n",userName);
  printf("=================================\n\n");

  printf("FROM\tTO\tTYPE\t\tAMOUNT\n\n");
  while(fread(&m1, sizeof(m1),1,fp))
  {
    if((strcmp(userName,m1.usernameFrom) == 0) || (strcmp(userName,m1.usernameTo) == 0))
    {

      printf("%.10s\t%.10s\t%.10s\t%0.3lf TK.\n",m1.usernameFrom,m1.usernameTo,m1.type,m1.money1);
    }
  }
  fclose(fp);
  getchar();
  display(userName);
}