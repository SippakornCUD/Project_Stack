#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
char* admincode[]={"ADmin1","ADmin2","ADmin3"};
char name[21],tel[13];
void adminconsole();
void steak();
void steakadd();
void steakedit();
void steakdelete();
void edit();
void fdelete();
void adminentercode();
void drink();
void drinkadd();
void drinkedit();
void drinkdelete();
void other();
void otheradd();
void otheredit();
void otherdelete();
void membername();
void memberconsole();
void membersteak();
void memberdrink();
void memberother();
void memberdeliver();
void recipe();
void writebill(float x);
float caltotal(int qua[],float price[],int loop);
void titleadmin(){
    printf("  ==============================");
    printf("\n             ADMIN            \n");
    printf("  ==============================\n");
}void titlemember(){
    printf("  ==============================");
    printf("\n             MEMBER           \n");
    printf("  ==============================\n");
}

FILE *fptr,*tptr,*bptr,*bptrm;
struct steakmenu{
    char name[101];
    float price;
}steakmn;
struct billmenu{
    char name[101];
    float price;
    int quantity;
}bmenu;
void main(){
    system("cls");
    int i=0,j,select1;
    printf("  ==============================");
    printf("\n       WELCOME TO PROGRAM     \n");
    printf("  ==============================\n");
    printf("\n          Select\n\n");
    printf("\t1) ADMIN\n");
    printf("\t2) MEMBER\n");
    printf("\t2) EXIT\n\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select1);
    switch(select1){
        case 1: adminentercode();break;
        case 2: membername();break;
        case 3: printf("\n\n\t\t\tTHANK YOU;)");getch();exit(0);break;
    }
    return 0;
}
void adminconsole(){
    system("cls");
    titleadmin();
    int select;
    fclose(fptr);
    printf("\n        Select Menu to check\n\n");
    printf("\t1) Steak\n");
    printf("\t2) Drink\n");
    printf("\t3) Other\n");
    printf("\t4) Back\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select);
    switch(select){
        case 1: steak();break;
        case 2: drink();break;
        case 3: other();break;
        case 4: main();break;
        default : adminconsole();break;
    }
}
void steak(){
    system("cls");
    titleadmin();
    int select,i=1;
    fptr=fopen("steakmenu.txt","a+");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    printf("\n             Steak\n\n");
    printf("\t1) ADD\n");
    printf("\t2) EDIT\n");
    printf("\t3) DELETE\n");
    printf("\t4) Back\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select);
    switch(select){
        case 1: steakadd();break;
        case 2: steakedit();break;
        case 3: steakdelete();break;
        case 4: fclose(fptr);adminconsole();break;
        default : steak();break;
    }
}
void steakadd(){
    system("cls");
    titleadmin();
    char steakname[21];
    int i=1;
    rewind(fptr);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    i=1;
    printf("\n             ADD\n\n");
    fflush(stdin);
    printf("  Enter Steak MENU ('CANCLE' to back) :");
    gets(steakname);
    if(strcmp(steakname,"CANCLE")==0){
        steak();
    }
    if(steakname[0]=='\0'){
        printf("\n Please Check Your Menu again");
        getch();
        steakadd();
    }
    rewind(fptr);
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        if(strcasecmp(steakname,steakmn.name)==0){
            printf("\n This Menu already exists");
            printf("\n Please Check Your Menu again");
            getch();
            steakadd();
        }
    }
    rewind(fptr);
    printf("  Price :");
    scanf("%f",&steakmn.price);
    strcpy(steakmn.name,steakname);
    fwrite(&steakmn,sizeof(steakmn),1,fptr);
    printf("\n%s has been added to the program.",steakname);
    getch();
    fclose(fptr);
    steak();
}
void edit(){
    int nocount=0,j=0,no;
    char select;
    tptr=fopen("tempmenu.txt","wb");
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",nocount+1,steakmn.name,steakmn.price);
        nocount++;
    }
    rewind(fptr);
    printf("\n              EDIT\n\n");
    do{
    fflush(stdin);
    printf("  Enter number to EDIT : ");
    scanf("%s",&select);
    if(isdigit(select)==0){
        printf("\n          !!!ERROR!!!");
        printf("\n       PLEASE TRY AGAIN\n\n");
        getch();
    }else{
        no=select-'0';
        if(no>nocount||no<0){
            printf("\n  !!!Enter number between 1-%d !!!\n\n",nocount);
            getch();
        }
    }
    }while(isdigit(select)==0||(no>nocount||no<0));
    fflush(stdin);
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        if(no-1==j){
            printf("  Name : ");
            gets(steakmn.name);
            printf("  Price :");
            scanf("%f",&steakmn.price);
            fseek(tptr,j*sizeof(steakmn),SEEK_SET);
            fwrite(&steakmn,sizeof(steakmn),1,tptr);
        }else{
            fwrite(&steakmn,sizeof(steakmn),1,tptr);
        }
        j++;
    }
}
void steakedit(){
    system("cls");
    titleadmin();
    rewind(fptr);
    edit();
    fclose(tptr);
    fclose(fptr);
    remove("steakmenu.txt");
    rename("tempmenu.txt","steakmenu.txt");
    steak();
}
void fdelete(){
    int nocount=0,i=0,no;
    char select;
    tptr=fopen("tempmenu.txt","wb");
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",nocount+1,steakmn.name,steakmn.price);
        nocount++;
    }
    rewind(fptr);
    printf("\n              Delete\n\n");
    do{
    fflush(stdin);
    printf("  Enter number to EDIT : ");
    scanf("%s",&select);
    if(isdigit(select)==0){
        printf("\n          !!!ERROR!!!");
        printf("\n       PLEASE TRY AGAIN\n\n");
        getch();
    }else{
        no=select-'0';
        if(no>nocount||no<0){
            printf("\n  !!!Enter number between 1-%d !!!\n\n",nocount);
            getch();
        }
    }
    }while(isdigit(select)==0||(no>nocount||no<0));
    fflush(stdin);
    if(no<nocount){
        for(i=1;i<no;i++){
            fread(&steakmn,sizeof(steakmn),1,fptr);
            fwrite(&steakmn,sizeof(steakmn),1,tptr);
        }
        fread(&steakmn,sizeof(steakmn),1,fptr);
        for(i=no;i<nocount;i++){
            fread(&steakmn,sizeof(steakmn),1,fptr);
            fwrite(&steakmn,sizeof(steakmn),1,tptr);
        }
    }else{
        if(no==nocount){
            for(i=1;i<no;i++){
                fread(&steakmn,sizeof(steakmn),1,fptr);
                fwrite(&steakmn,sizeof(steakmn),1,tptr);
            }
        }
    }
}
void steakdelete(){
    system("cls");
    titleadmin();
    rewind(fptr);
    fdelete();
    fclose(tptr);
    fclose(fptr);
    remove("steakmenu.txt");
    rename("tempmenu.txt","steakmenu.txt");
    steak();
}
void drink(){
    system("cls");
    titleadmin();
    int select,i=1;
    fptr=fopen("drinkmenu.txt","a+");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    printf("\n             Drink\n\n");
    printf("\t1) ADD\n");
    printf("\t2) EDIT\n");
    printf("\t3) DELETE\n");
    printf("\t4) Back\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select);
    switch(select){
        case 1: drinkadd();break;
        case 2: drinkedit();break;
        case 3: drinkdelete();break;
        case 4: fclose(fptr);adminconsole();break;
        default : drink();break;
    }
}
void drinkadd(){
    system("cls");
    titleadmin();
    char drinkname[21];
    int i=1;
    rewind(fptr);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    printf("\n             ADD\n\n");
    fflush(stdin);
    printf("  Enter Steak MENU ('CANCLE' to back) :");
    gets(drinkname);
    if(strcmp(drinkname,"CANCLE")==0){
        drink();
    }
    if(drinkname[0]=='\0'){
        printf("\n Please Check Your Menu again");
        getch();
        drinkadd();
    }
    rewind(fptr);
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        if(strcmpi(drinkname,steakmn.name)==0){
            printf("\n This Menu already exists");
            printf("\n Please Check Your Menu again");
            getch();
            drinkadd();
        }
    }
    printf("  Price :");
    scanf("%f",&steakmn.price);
    strcpy(steakmn.name,drinkname);
    fwrite(&steakmn,sizeof(steakmn),1,fptr);
    printf("\n%s has been added to the program.",drinkname);
    getch();
    fclose(fptr);
    drink();
}
void drinkedit(){
    system("cls");
    titleadmin();
    rewind(fptr);
    edit();
    fclose(tptr);
    fclose(fptr);
    remove("drinkmenu.txt");
    rename("tempmenu.txt","drinkmenu.txt");
    drink();
}
void drinkdelete(){
    system("cls");
    titleadmin();
    rewind(fptr);
    fdelete();
    fclose(tptr);
    fclose(fptr);
    remove("drinkmenu.txt");
    rename("tempmenu.txt","drinkmenu.txt");
    drink();
}
void other(){
    system("cls");
    titleadmin();
    int select,i=1;
    fptr=fopen("othermenu.txt","a+");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    printf("\n             Other\n\n");
    printf("\t1) ADD\n");
    printf("\t2) EDIT\n");
    printf("\t3) DELETE\n");
    printf("\t4) Back\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select);
    switch(select){
        case 1: otheradd();break;
        case 2: otheredit();break;
        case 3: otherdelete();break;
        case 4: fclose(fptr);adminconsole();break;
        default : other();break;
    }
}
void otheradd(){
    system("cls");
    titleadmin();
    char othername[21];
    int i=1;
    rewind(fptr);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    printf("\n             ADD\n\n");
    fflush(stdin);
    printf("  Enter Steak MENU ('CANCLE' to back) :");
    gets(othername);
    if(strcmp(othername,"CANCLE")==0){
        other();
    }
    if(othername[0]=='\0'){
        printf("\n Please Check Your Menu again");
        getch();
        otheradd();
    }
    rewind(fptr);
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        if(strcmpi(othername,steakmn.name)==0){
            printf("\n This Menu already exists");
            printf("\n Please Check Your Menu again");
            getch();
            otheradd();
        }
    }
    printf("  Price :");
    scanf("%f",&steakmn.price);
    strcpy(steakmn.name,othername);
    fwrite(&steakmn,sizeof(steakmn),1,fptr);
    printf("\n%s has been added to the program.",othername);
    getch();
    fclose(fptr);
    other();
}
void otheredit(){
    system("cls");
    titleadmin();
    rewind(fptr);
    edit();
    fclose(tptr);
    fclose(fptr);
    remove("othermenu.txt");
    rename("tempmenu.txt","othermenu.txt");
    other();
}
void otherdelete(){
    system("cls");
    titleadmin();
    rewind(fptr);
    fdelete();
    fclose(tptr);
    fclose(fptr);
    remove("othermenu.txt");
    rename("tempmenu.txt","othermenu.txt");
    other();
}
void adminentercode(){
    system("cls");
    char check[11],checkcheck[11];
    int i,j,loop=0,checkim=0;
    titleadmin();
    printf("\n     Enter your ADMIN CODE\n");
    printf("     Press 'bk' to back\n\n");
    printf("\tCode :");
    scanf("%s",check);
    if(strcmp(check,"bk")==0){
        main();
    }else{
    for(i=0;i<3;i++){
        for(j=0;admincode[i][j]!='\0';j++){
            checkcheck[j]=admincode[i][j];
        }
        for(j=0;admincode[i][j]!='\0';j++){
            if(check[j]!=checkcheck[j]){
                checkim++;
            }
        }
        if(checkim==0){
            loop=1;
        }
        checkim=0;
    }
    if(loop==0){
        printf("\nWrong ADMIN CODE : Please try Again\n");
        getch();
        adminentercode();
    }else{
        printf("\n    ::Collect ADMIN CODE::\n  Welcome %s to ADMIN CONSOLE",check);
        getch();
        adminconsole();
    }
    }
}
void membername(){
    system("cls");
    titlemember();
    bptr=fopen("billforcal.txt","w+");
    fflush(stdin);
    printf("Enter Name :");
    gets(name);
    printf("Enter Tel (0XX-XXXX-XXX) :");
    gets(tel);
    printf("  ==============================");
    getch();
    memberconsole();
}
void memberconsole(){
    system("cls");
    titlemember();
    int select;
    fclose(fptr);
    printf("  Hello %s \n  Welcome to steak menu (%s) ",name,tel);
    printf("\n        Select Menu\n\n");
    printf("\t1) Steak\n");
    printf("\t2) Drink\n");
    printf("\t3) Other\n");
    printf("\t4) FINISH\n");
    printf("\t5) Back\n\n");
    printf("  ==============================\n");
    printf("\tSelect :");
    scanf("%d",&select);
    switch(select){
        case 1: membersteak();break;
        case 2: memberdrink();break;
        case 3: memberother();break;
        case 4: memberdeliver();break;
        case 5: fclose(bptr);main();break;
        default : memberconsole();break;
    }
}
void membersteak(){
    system("cls");
    titlemember();
    int i=1,select,slsteak,quantity;
    char lsteak[51],YN[2];
    fptr=fopen("steakmenu.txt","r");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    rewind(fptr);
    while(1){
        printf("\n\tSelect Number : ");
        scanf("%d",&select);
        if(select>0&&select<i){
            break;
        }
    }
    for(i=0;i<select;i++){
        fread(&steakmn,sizeof(steakmn),1,fptr);
    }
    printf("\n             Level\n\n");
    printf("\t1) Rare\n");
    printf("\t2) Medium-Rare\n");
    printf("\t3) Medium\n");
    printf("\t4) Medium-Well\n");
    printf("\t5) Well\n\n");
    do{
    printf("\n\tSelect Number : ");
    scanf("%d",&slsteak);
    if(slsteak==1){
        strcpy(lsteak,"(Rare)");
        break;
    }else{
        if(slsteak==2){
            strcpy(lsteak,"(Medium-Rare)");
            break;
        }else{
            if(slsteak==3){
                strcpy(lsteak,"(Medium)");
                break;
            }else{
                if(slsteak==4){
                    strcpy(lsteak,"(Medium-Well)");
                    break;
                }else{
                    if(slsteak==5){
                        strcpy(lsteak,"(Well)");
                        break;
                    }else{
                        printf("Error\n");
                        getch();
                    }
                }
            }
        }
    }
    }while(1);
    printf("\n\tQuantity : ");
    scanf("%d",&quantity);
    strncat(steakmn.name,lsteak,sizeof(lsteak));
    strcpy(bmenu.name,steakmn.name);
    bmenu.price=steakmn.price;
    bmenu.quantity=quantity;
    fwrite(&bmenu,sizeof(bmenu),1,bptr);
    fclose(fptr);
    fflush(stdin);
    printf("If you want more press \"y\": ");
    gets(YN);
    if(YN[0]=='Y'||YN[0]=='y'){
        memberconsole();
    }else{
        memberdeliver();
    }
}
void memberdrink(){
    system("cls");
    titlemember();
    int i=1,select,quantity;
    char lsteak[51],YN[2];
    fptr=fopen("drinkmenu.txt","r");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    rewind(fptr);
    while(1){
        printf("\n\tSelect Number : ");
        scanf("%d",&select);
        if(select>0&&select<i){
            break;
        }
    }
    for(i=0;i<select;i++){
        fread(&steakmn,sizeof(steakmn),1,fptr);
    }
    printf("\n\tQuantity : ");
    scanf("%d",&quantity);
    strcpy(bmenu.name,steakmn.name);
    bmenu.price=steakmn.price;
    bmenu.quantity=quantity;
    fwrite(&bmenu,sizeof(bmenu),1,bptr);
    fclose(fptr);
    fflush(stdin);
    printf("If you want more press \"y\": ");
    gets(YN);
    if(YN[0]=='Y'||YN[0]=='y'){
        memberconsole();
    }else{
        memberdeliver();
    }
}
void memberother(){
    system("cls");
    titlemember();
    int i=1,select,quantity;
    char lsteak[51],YN[2];
    fptr=fopen("othermenu.txt","r");
    fseek(fptr,0,0);
    printf("     MENU                 Price\n");
    while(fread(&steakmn,sizeof(steakmn),1,fptr)==1){
        printf("   %d %-20s %.2f\n",i,steakmn.name,steakmn.price);
        i++;
    }
    rewind(fptr);
    while(1){
        printf("\n\tSelect Number : ");
        scanf("%d",&select);
        if(select>0&&select<i){
            break;
        }
    }
    for(i=0;i<select;i++){
        fread(&steakmn,sizeof(steakmn),1,fptr);
    }
    printf("\n\tQuantity : ");
    scanf("%d",&quantity);
    strcpy(bmenu.name,steakmn.name);
    bmenu.price=steakmn.price;
    bmenu.quantity=quantity;
    fwrite(&bmenu,sizeof(bmenu),1,bptr);
    fclose(fptr);
    fflush(stdin);
    printf("If you want more press \"y\" : ");
    gets(YN);
    if(YN[0]=='Y'||YN[0]=='y'){
        memberconsole();
    }else{
        memberdeliver();
    }
}
void memberdeliver(){
    system("cls");
    titlemember();
    int sldeliver;
    printf("\n             Delivery\n\n");
    printf("\t1) Take Home\n");
    printf("\t2) Take Here\n");
    do{
    printf("\n\tSelect Number : ");
    scanf("%d",&sldeliver);
    if(sldeliver==1){
        strcpy(bmenu.name,"Take_Home(Delivery)");
        bmenu.price=40.00;
        bmenu.quantity=1;
        fwrite(&bmenu,sizeof(bmenu),1,bptr);
        break;
    }else{
        if(sldeliver==2){
            strcpy(bmenu.name,"Take_Here(Delivery)");
            bmenu.price=0.00;
            bmenu.quantity=1;
            fwrite(&bmenu,sizeof(bmenu),1,bptr);
            break;
        }else{
            printf("Error\n");
            getch();
        }
    }
    }while(1);
    fclose(bptr);
    recipe();
}
char *now(char *ttime){
    time_t current = time(NULL);
    struct tm *tinfo = localtime(&current);
    strftime(ttime,45,"%d/%m/%Y  :  %H.%M.%S",tinfo);
    return ttime;
}
void recipe(){
    system("cls");
    int coun=0,i=0;
    char ttime[45];
    printf("  ==============================");
    printf("\n             Recipe           \n");
    printf("  ==============================\n");
    fflush(stdin);
    printf("\n  Your Name : %s\n",name);
    printf("  Your Tel : %s\n\n",tel);
    printf("     MENU                     Price\n");
    bptr=fopen("billforcal.txt","r");
    if((bptrm=fopen("bill_month.txt","r"))==NULL){
        bptrm=fopen("bill_month.txt","w");
    }else{
        bptrm=fopen("bill_month.txt","a");
    }
    fprintf(bptrm,"%s\nName : %s\nTel : %s\n",now(ttime),name,tel);
    float simpl;
    while(fread(&bmenu,sizeof(bmenu),1,bptr)==1){
        simpl=bmenu.price*bmenu.quantity;
        printf("   %d %-20s %-3d %.2f\n",coun+1,bmenu.name,bmenu.quantity,simpl);
        fprintf(bptrm,"%-20s %-3d %.2f\n",bmenu.name,bmenu.quantity,simpl);
        coun++;
        simpl=0;
    }
    rewind(bptr);
    int qual[coun];
    float arprice[coun];
    while(fread(&bmenu,sizeof(bmenu),1,bptr)==1){
        qual[i]=bmenu.quantity;
        arprice[i]=bmenu.price;;
        i++;
    }
    float alltotal=caltotal(qual,arprice,i);
    printf("Total                         %.2f",alltotal);
    float net_total=0,billinput;
    fprintf(bptrm,"The_Total:%25.2f\n\n",alltotal);
    fclose(bptr);
    fclose(bptrm);
    getch();
    writebill(alltotal);
}
float caltotal(int qua[],float price[],int calloop){
    int i;
    float sum=0;
    for(i=0;i<calloop;i++){
        sum+=qua[i]*price[i];
    }
    return sum;
}
void writebill(float x){
    tptr=fopen("billforcal.txt","r");
    bptr=fopen("bill.txt","w+");
    while(fread(&bmenu,sizeof(bmenu),1,tptr)==1){
        fprintf(bptr,"%-20s %10d %.2f\n",bmenu.name,bmenu.quantity,bmenu.price);
    }
    fprintf(bptr,"\nTotal  %32.2f",x);
    fclose(tptr);
    fclose(bptr);
    remove("billforcal.txt");
}

