#include <stdio.h>
#include "../include/conio2.h"
#include "../include/rlyres.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define ALL_TRAINS_FILEPATH "alltrains.dat"
#define ALL_BOOKINGS_FILEPATH "allbookings.dat"
#define TEMP_FILEPATH "temp.dat"


int enterchoice()
{
    int choice, i;
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (i = 1; i <= 120; i++)
    {
        printf("-");
    }
    printf("\n\n Select an Option\n 1- View Trains\n 2- Book Ticket\n 3- View Ticket\n 4- Search Ticket No\n 5- View all Bookings\n 6- View Train Bookings\n 7- Cancel Ticket\n 8- Quit");
    printf("\n\n Enter Choice : ");
    scanf("%d", &choice);
    return choice;
}
void add_trains()
{
    FILE *fp;
    fp = fopen(ALL_TRAINS_FILEPATH, "rb");

    if (fp == NULL)
    {
        struct Train alltrains[4] =
        {
            {"123", "BPL", "GWA", 2100, 1500},
            {"546", "BPL", "DEL", 3500, 2240},
            {"345", "HBJ", "AGR", 1560, 1135},
            {"896", "HBJ", "MUM", 4500, 3360},
        };
        fp = fopen(ALL_TRAINS_FILEPATH, "wb");
        fwrite(alltrains, 4 * sizeof(Train), 1, fp);
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}

void view_trains()
{
    clrscr();
    int i;
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (i = 1; i <= 120; i++)
    {
        printf("-");
    }
    printf(" TRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOND AC FAIR\n");
    for (i = 1; i <= 120; i++)
    {
        printf("-");
    }
    printf("\n");
    FILE *fp;
    fp = fopen(ALL_TRAINS_FILEPATH, "rb");
    struct Train q[4];

    fread(&q, 4 * sizeof(Train), 1, fp);
    for (i = 0; i < 4; i++)
        printf(" %s\t\t%s\t%s\t%d\t\t%d\n", q[i].train_no, q[i].from, q[i].to, q[i].fac_fare, q[i].sac_fare);

    textcolor(WHITE);
    printf("\n\n\n\n Press any key to go back to the Main Screen!!");

    fclose(fp);
    getch();
    clrscr();
}

int check_train_no(char *trainno)
{
    FILE *fp = fopen(ALL_TRAINS_FILEPATH, "rb");
    Train tr;
    while (fread(&tr, sizeof(tr), 1, fp) == 1)
    {
        if (strcmp(trainno, tr.train_no) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void cancel_reservation()
{
    textcolor(LIGHTRED);
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t");
    gotoxy(1, 25);
    printf("RESERVATION CANCELLED!!");
    textcolor(YELLOW);
}

Passenger *get_passenger_details()
{
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (int i = 1; i <= 120; i++)
    {
        printf("-");
    }

    gotoxy(90, 3);
    textcolor(RED);
    printf("Press 0 to Cancle Reservation");

    gotoxy(1, 3);
    textcolor(WHITE);

    //passenger name

    static Passenger psn;
    printf("Enter Passenger Name : ");
    fflush(stdin);
    fgets(psn.p_name, 20, stdin);
    char *pos = strchr(psn.p_name, '\n');
    if (pos != NULL)
        *pos = '\0';

    // name is empty
    while (strlen(psn.p_name) == 0)
    {
        gotoxy(1, 25);
        textcolor(RED);
        printf("Name cannot be empty!!!!");

        gotoxy(24, 3);
        printf(" \b");
        textcolor(WHITE);

        fflush(stdin);
        fgets(psn.p_name, 20, stdin);
        char *pos = strchr(psn.p_name, '\n');
        if (pos != NULL)
            *pos = '\0';
    }




    //cancel reservation

    if (strcmp(psn.p_name, "0") == 0)
    {
        cancel_reservation();
        return NULL;
    }
    //enter gender

    printf("Enter Gender\(M/F) : ");
    scanf("%c", &psn.gender);
    while (psn.gender != 'M' && psn.gender != 'F')
    {
        if (psn.gender == 48)
        {
            cancel_reservation();
            return NULL;
        }
        gotoxy(1, 25);
        textcolor(RED);
        printf("Wrong Details Entered!!!!");

        gotoxy(21, 4);
        textcolor(WHITE);
        printf(" \b");
        scanf("%c", &psn.gender);
    }

    gotoxy(1, 25);
    printf("                         ");
    gotoxy(1, 5);

    //train number

    printf("Enter Train Number : ");
    int x;
    scanf("%s", psn.train_no);
    x = check_train_no(psn.train_no);
    while (x == 0)
    {
        if (psn.train_no[0] == 48)
        {
            cancel_reservation();
            return NULL;
        }
        gotoxy(1, 25);
        textcolor(RED);
        printf("Enter valid Train Number!!");
        gotoxy(22, 5);
        textcolor(WHITE);
        printf("                         ");
        gotoxy(22, 5);
        scanf("%s", psn.train_no);
        x = check_train_no(psn.train_no);
    }

    gotoxy(1, 25);
    printf("                                      ");
    gotoxy(1, 6);

    //travelling class

    printf("Enter Travelling Class(First AC-F,Second AC-S) : ");
    fflush(stdin);
    scanf("%c", &psn.p_class);
    while (psn.p_class != 'S' && psn.p_class != 'F')
    {
        if (psn.p_class == 48)
        {
            cancel_reservation();
            return NULL;
        }
        gotoxy(1, 25);
        textcolor(RED);
        printf("Wrong Details Entered!!!!");
        gotoxy(50, 6);
        textcolor(WHITE);
        printf(" \b");
        scanf("%c", &psn.p_class);
    }
    gotoxy(1, 25);
    printf("                         ");
    gotoxy(1, 7);

    //address

    printf("Enter Address : ");
    fflush(stdin);
    fgets(psn.addr, 30, stdin);
    pos = strchr(psn.addr, '\n');
    if (pos != NULL)
        *pos = '\0';

    if (strcmp(psn.addr, "0") == 0)
    {
        cancel_reservation();
        return NULL;
    }

    //age

    printf("Enter Age : ");
    scanf("%d", &psn.age);
    while (psn.age <= 0)
    {
        if (psn.age == 0)
        {
            cancel_reservation();
            return NULL;
        }
        else
        {
            gotoxy(1, 25);
            textcolor(RED);
            printf("Enter Positive Age");
            gotoxy(13, 8);
            textcolor(WHITE);
            printf("     ");
            gotoxy(13, 8);
            scanf("%d", &psn.age);
        }
    }
    gotoxy(1, 25);
    printf("                           ");
    gotoxy(1, 9);

    //mobile number

    printf("Enter Mobile Number : ");
    int valid;
    do
    {
        fflush(stdin);
        fgets(psn.mob_no, 11, stdin);
        pos = strchr(psn.mob_no, '\n');
        if (pos != NULL)
            *pos = '\0';
        if (strcmp(psn.mob_no, "0") == 0)
        {
            cancel_reservation();
            return NULL;
        }
        valid = check_mob_no(psn.mob_no);
        if (valid == 0)
        {
            gotoxy(1, 25);
            textcolor(RED);
            printf("Invalid Mobile Number");
            gotoxy(23, 9);
            printf("                                       ");
            gotoxy(23, 9);
            textcolor(WHITE);
        }
    }
    while (valid == 0);
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t\t\t");
    gotoxy(33, 9);
    getch();
    return &psn;
}

int check_mob_no(char *p_mob)
{

    if (strlen(p_mob) != 10)
        return 0;
    while (*p_mob != '\0')
    {
        if (isdigit(*p_mob) == 0)
            return 0;
        p_mob++;
    }
    return 1;
}
int get_book_ticket_count(char *train_no, char tc)
{
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    if (fp == NULL)
    {
        return 0;
    }
    Passenger pr;
    int count = 0;
    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (strcmp(pr.train_no, &train_no) == 0 && pr.p_class == tc)
            ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    if (fp == NULL)
        return 0;
    Passenger pr;
    fseek(fp, -1 * sizeof(pr), SEEK_END);
    fread(&pr, sizeof(pr), 1, fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger p)
{
    int x = get_book_ticket_count(p.train_no, p.p_class);
    if (x == 30)
    {
        return -1;
    }
    p.ticketno = last_ticket_no() + 1;
    clrscr();
    textcolor(GREEN);
    printf("Ticket successfully booked!!");
    textcolor(WHITE);
    printf("\nYour Ticket Number is : %d", p.ticketno);
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "ab");
    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    return p.ticketno;
}

int accept_ticket_no()
{

    int p;
    clrscr();
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (int i = 1; i <= 120; i++)
    {
        printf("-");
    }

    gotoxy(90, 3);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    textcolor(YELLOW);
    printf("\n");
    printf("Enter Your Ticket Number : ");
    scanf("%d", &p);
    if (p == 0)
        return 0;
    return p;
}

int check_ticket_no(int p)
{
    int found;
    Passenger pr;
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");

    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (pr.ticketno == p)
        {
            found = 1;
            break;
        }
    }
    if (found != 1 && p >= 0)
    {
        fclose(fp);
        return 0;
    }
    if (found != 1 && p < 0)
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 1;
}

void view_ticket(int p)
{

    Passenger pr;
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    if (fp == NULL)
    {
        textcolor(RED);
        printf("\n\nNo Bookings Done!!");
        return;
    }

    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (pr.ticketno == p)
        {
            printf("\n\nNAME : %s\nGENDER : %c\nTRAIN NO : %s\nCLASS : %c\nADDRESS : %s\nAGE : %d\nMOBILE NO : %s\nTICKET NO : %d", pr.p_name, pr.gender, pr.train_no, pr.p_class, pr.addr, pr.age, pr.mob_no, pr.ticketno);
            break;
        }
    }

    textcolor(WHITE);
    printf("\n\n\n\n\n\n\nPress any key to return to the main menu");
    fclose(fp);
}

int *get_ticket_no(char *p)
{
    Passenger pr;
    int count = 0;
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (strcmp(pr.mob_no, p) == 0)
        {
            count++;
        }
    }

    int *store = (int *)malloc(sizeof(int) * count);
    rewind(fp);
    count = 0;
    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (strcmp(pr.mob_no, p) == 0)
        {
            *(store + count) = pr.ticketno;
            count++;
        }
    }
    *(store + count) = -1;
    if (count != 0)
    {
        fclose(fp);
        return store;
    }
    fclose(fp);
    textcolor(RED);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNo Registerations from this Number!!");
    return NULL;
}

void view_all_bookings()
{

    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    int i;
    for (i = 1; i <= 120; i++)
    {
        printf("-");
    }
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    Passenger pr;

    i = 5;
    printf(" NAME");
    gotoxy(20, 3);
    printf("GENDER");
    gotoxy(30, 3);
    printf("TRAIN");
    gotoxy(45, 3);
    printf("CLASS");
    gotoxy(55, 3);
    printf("ADDRESS");
    gotoxy(75, 3);
    printf("AGE");
    gotoxy(90, 3);
    printf("MOBILE");
    gotoxy(105, 3);
    printf("TICKET\n");
    for (int j = 0; j <= 118; j++)
    {
        printf("-");
    }

    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        printf("\n");
        printf(" %s", pr.p_name);
        gotoxy(20, i);
        printf("%c", pr.gender);
        gotoxy(30, i);
        printf("%s", pr.train_no);
        gotoxy(45, i);
        printf("%c", pr.p_class);
        gotoxy(55, i);
        printf("%s", pr.addr);
        gotoxy(75, i);
        printf("%d", pr.age);
        gotoxy(90, i);
        printf("%s", pr.mob_no);
        gotoxy(105, i);
        printf("%d", pr.ticketno);
        i++;
    }
    fclose(fp);
}
char *accept_train_no()
{
    clrscr();
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (int i = 1; i <= 120; i++)
    {
        printf("-");
    }
    char *h;
    printf("Enter Train Number : ");
    scanf("%s", &h);
    return h;
}
void view_bookings(char *p)
{

    gotoxy(90, 3);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit\n");
    textcolor(YELLOW);
    Passenger pr;

    gotoxy(1, 1);
    textcolor(YELLOW);
    printf("                             ");
    gotoxy(1, 1);
    int x = check_train_no(p);
    if (strcmp(p, "0") == 0)
    {
        clrscr();
        return NULL;
    }
    if (x == 0)
    {
        textcolor(RED);
        gotoxy(1, 25);
        printf("Wrong Details Entered");
        getch();
        clrscr();
        return NULL;
    }
    clrscr();
    int i = 0;
    FILE *fp = fopen(ALL_BOOKINGS_FILEPATH, "rb");
    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if (strcmp(p, pr.train_no) == 0)
        {
            i++;
        }
    }
    if (i == 0)
    {
        printf("No Tickets Found!!!");
        return NULL;
    }
    rewind(fp);
    i = 2;
    printf(" NAME");
    gotoxy(20, 1);
    printf("GENDER");
    gotoxy(30, 1);
    printf("TRAIN");
    gotoxy(45, 1);
    printf("CLASS");
    gotoxy(55, 1);
    printf("ADDRESS");
    gotoxy(75, 1);
    printf("AGE");
    gotoxy(90, 1);
    printf("MOBILE");
    gotoxy(105, 1);
    printf("TICKET\n");
    for (int j = 0; j <= 118; j++)
    {
        printf("-");
    }

    while (fread(&pr, sizeof(pr), 1, fp) == 1)
    {

        if (strcmp(p, pr.train_no) == 0)
        {
            i++;
            printf("\n");
            printf(" %s", pr.p_name);
            gotoxy(20, i);
            printf("%c", pr.gender);
            gotoxy(30, i);
            printf("%s", pr.train_no);
            gotoxy(45, i);
            printf("%c", pr.p_class);
            gotoxy(55, i);
            printf("%s", pr.addr);
            gotoxy(75, i);
            printf("%d", pr.age);
            gotoxy(90, i);
            printf("%s", pr.mob_no);
            gotoxy(105, i);
            printf("%d", pr.ticketno);
        }
    }
    fclose(fp);
    getch();
    clrscr();
}

int cancel_ticket(int p)
{
    FILE *fp1 = fopen(ALL_BOOKINGS_FILEPATH, "rb+");

    if (fp1 == NULL)
    {
        return -1;
    }
    FILE *fp2 = fopen(TEMP_FILEPATH, "wb+");
    Passenger pr;
    int found = 0;
    while (fread(&pr, sizeof(pr), 1, fp1) == 1)
    {
        if (pr.ticketno != p)
        {
            fwrite(&pr, sizeof(pr), 1, fp2);
        }
        else
            found = 1;
    }
    fclose(fp1);
    fclose(fp2);
    if (found == 0)
        remove(TEMP_FILEPATH);
    else
    {
        remove(ALL_BOOKINGS_FILEPATH);
        rename(TEMP_FILEPATH, ALL_BOOKINGS_FILEPATH);
    }
    return found;
}


char *accept_mob_no()
{
    clrscr();
    textcolor(YELLOW);
    gotoxy(48, 1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for (int i = 1; i <= 120; i++)
    {
        printf("-");
    }

    gotoxy(90, 3);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit\n");
    textcolor(YELLOW);
    printf("Enter mobile number : ");
    static char mob_no[11];
    char *pos;
    int valid;
    do
    {
        fflush(stdin);
        fgets(mob_no, 11, stdin);
        pos = strchr(mob_no, '\n');
        if (pos != NULL)
            *pos = '\0';
        if (strcmp(mob_no, "0") == 0)
        {
            textcolor(LIGHTRED);
            gotoxy(1, 25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1, 25);
            printf("Cancelling Input. . .!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid = check_mob_no(mob_no);
        if (valid == 0)
        {
            textcolor(LIGHTRED);
            gotoxy(1, 25);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21, 1);
            printf("\t\t\t\t\t\t");
            gotoxy(21, 1);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
    }
    while (valid == 0);
    clrscr();
    return mob_no;
}
