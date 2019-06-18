#include <stdio.h>
#include <stdlib.h>
char * s_gets(char * st, int n);
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100 /* ������������ ���������� ���� */
#include <locale.h>

struct book {   /* ��������� ������� book */;
    char * title;
    char * author;
    float value;
};

int getBookInfo (struct book * library, int count){
    printf("������� �������� �����.\n");
    printf ("������� [enter] � ������ ������, ����� ��������� ����.\n");
    while (count < MAXBKS && s_gets(library[count].title, MAXTITL)!= NULL && library[count].title[0]!= '\0')
        {
            printf("������ ������� ��� ������.\n");
            s_gets(library[count].author, MAXAUTL);
            printf ("������ ������� ����\n");
            scanf("%f", &library[count++].value);
            while (getchar()!= '\n')
                continue; /* �������� ������� ������ */
            if (count < MAXBKS)
                printf("������� �������� ��������� �����.\n");
        };
    return count;
}

void sortByOrder (struct book * library, int count, int index){
    if (count > 0)
    {
        printf("������� ����� ����:\n");
        for (index = 0; index < count; index++)
            printf("%s ��������� %s: $%.2f\n", library[index].title,
                library[index].author, library[index].value);
    }
    else
        printf("������ ��� ����? ����� �����.\n");
}

void sortByAlpha (struct book * library, int count, int index){

}

int main (void)
{
    setlocale (LC_ALL, "rus");
    struct book library[MAXBKS]; /* ������ �������� ���� book */
    int count=0;
    int index=0;
    int* ptrCount=&count;
    struct book * catalogOfBooks = calloc (MAXBKS, sizeof(struct book));
    for (int i=0; i<MAXBKS; i++){
        catalogOfBooks[i].title=calloc (MAXTITL, sizeof(char));
        catalogOfBooks[i].author=calloc (MAXAUTL, sizeof(char));
    }
    count=getBookInfo(catalogOfBooks, count);
    sortByOrder(catalogOfBooks, count, index);
    for (int i=0; i<MAXBKS; i++){
        free(catalogOfBooks[i].title);
        free(catalogOfBooks[i].author);
    };
    free (catalogOfBooks);
    return 0;
}


char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;
    ret_val = fgets (st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // ����� ����� ������
        if (find) // ���� ����� �� ����� NULL,
            *find = '\0'; // ��������� ���� ������� ������
        else
            while (getchar()!= '\n')
                continue; // ��������� ������� ������
    }
    return ret_val;
}
