#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#define SEATS_COUNT 12
#define FLIGHT_1 1
#define FLIGHT_2 2
#define FLIGHT_3 3
#define FLIGHT_4 4

struct Name
{
    char * firstName;
    char * lastName;
};

struct TicketDescription
{
    int ticketID;
    bool isReserved;
    struct Name * name;
};

struct Airplane {
    int flightNumber;
    struct TicketDescription * tickets;
};

void showEditFlightMenu (struct Airplane * airplane)
{
    char choiceOption='\0';
    showMenuOptions(ptrTicket);
    while (scanf("%c", &choiceOption)==1)
    {
        fflush(stdin);
        switch (choiceOption)
        {
        case 'a':
            showNumberOfFreeSeats (airplane[seat], SEATS_COUNT);
            break;
        case 'b':
            showListOfFreeSeats (ptrTicket, SEATS_COUNT);
            break;
        case 'c':
            showListOfReservedSeats (ptrTicket, SEATS_COUNT);
            break;
        case 'd':
            setReservedSeat (ptrTicket);
            break;
        case 'e':
            getReservedAway(ptrTicket);
            break;
        case 'f':
            showMenuFlight (ptrTicket, userFlightInput, SEATS_COUNT);
        default:
            puts("Некорректный ввод");
        }
        showMenuOptions();
    }
}

void showNumberOfFreeSeats (struct ticketDescription * ptrTicket, int count_of_seats){
    int count=0;
    for (int i=0; i<count_of_seats;i++){
        if (ptrTicket[i].reserved==false)
            count+=1;
    }
    printf("Количество свободных мест=%d\n", count);
}

void showListOfFreeSeats (struct ticketDescription * ptrTicket, int count_of_seats){
    for (int i=0; i<count_of_seats;i++){
        if (ptrTicket[i].reserved==false)
        printf("Место №%d свободно\n", i);
    }
}

void showListOfReservedSeats (struct ticketDescription * ptrTicket, int count_of_seats){
    for (int i=0; i<count_of_seats;i++){
        if (ptrTicket[i].reserved==true) {
        printf("Место №%d забронировано\n", i);
        printf("Фамилия - %s\n", ptrTicket[i].name->lastName);
        printf("Имя - %s\n", ptrTicket[i].name->firstName);
        }
    }
}

void showMenuOptions(struct ticketDescription * ptrTicket)
{
    printf("Текущий номер рейса - %d\n", ptrTicket[0].flight);
    puts ("Для выбора функции введите ее буквенную метку:");
    puts ("a) Показать количество свободных мест");
    puts ("b) Показать список свободных мест");
    puts ("c) Показать список забронированных мест в алфавитном порядке");
    puts ("d) Забронировать место для пассажира");
    puts ("e) Снять броню с места");
    puts ("f) Выйти из меню");
}

int selectAirplane (){
    puts ("Выберите номер рейса и введите пункт");
    puts ("a) 1");
    puts ("b) 2");
    puts ("c) 3");
    puts ("d) 4");
    puts ("e) Выход");
    scanf("%c", &userFlightInput);
    fflush(stdin);
    switch (userFlightInput){
    case 'a':return FLIGHT_1;
    case 'b':return FLIGHT_2;
    case 'c':return FLIGHT_3;
    case 'd':return FLIGHT_4;
    case 'e':exit (0);
    };
}

void getReservedAway (struct ticketDescription * ptrTicket)
{
    int seat=0;
    puts("С какого места снять бронь? Введите число");
    scanf("%d", &seat);
    ptrTicket[seat].reserved=false;
}

void setReservedSeat (struct ticketDescription * ptrTicket, char userFlightInput) {
    puts("Введите место от 1 до 12 или q для завершения");
    int seat=0;
    scanf("%d", &seat);
    ptrTicket[seat].ticketID=seat;
    fflush(stdin);
    ptrTicket[seat].reserved=true;
    puts("Введите фамилию");
    gets(ptrTicket[seat].name->lastName);
    fflush(stdin);
    puts("Введите имя");
    gets(ptrTicket[seat].name->firstName);
    puts("Подтверждаете бронь?");
    puts("1 для подтверждения или 0 для отмены");
    scanf("%d", &ptrTicket[seat].confirmed);
    if (ptrTicket[seat].confirmed==0)
      showEditFlightMenu(ptrTicket, userFlightInput);
}

int main()
{
    setlocale (LC_ALL, "rus");
    struct Airplane * airplanes = calloc (4, sizeof(struct Airplane));
    for (int i=0; i<4; i++){
        airplanes[i].flightNumber=i+1;
        airplanes[i].tickets = calloc (SEATS_COUNT, sizeof(struct TicketDescription));
            for (int j=0; j<SEATS_COUNT;j++){
            airplanes[i].tickets[j].name=calloc (1, sizeof(struct Name));
            airplanes[i].tickets[j].name->firstName=calloc (20, sizeof(char));
            airplanes[i].tickets[j].name->lastName=calloc (20, sizeof(char));
        };
    };
    int selectedAirplane = selectAirplane();
    showEditFlightMenu(&(airplanes[selectedAirplane-1]));
    for (int i=0; i<4; i++){
            for (int j=0; j<SEATS_COUNT;j++){
            free(airplanes[i].tickets[j].name->firstName);
            free(airplanes[i].tickets[j].name->lastName);
            free(airplanes[i].tickets[j].name);
        };
        free(airplanes[i].tickets);
    };
    free(airplanes);
    return 0;
}
