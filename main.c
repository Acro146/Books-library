#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int id, quantity;
    char name [30];
} bookinfo;

void mian_menu();

void add_book(void)
{
    bookinfo book;
    FILE* BP=fopen("library.txt","a");
    if(BP==NULL)
        printf("File could not be opened\n");
    else
    {

        printf( "Enter Book ID:" );
        scanf( "%d",&book.id);

        printf( "Enter Book Quantity:" );
        scanf( "%d",&book.quantity);

        printf( "Enter Book Name:" );
        getchar();
        gets(book.name);


        fprintf(BP,"%d\n",book.id);
        fprintf(BP,"%d\n",book.quantity);
        fprintf(BP,"%s\n",book.name);


        fclose(BP);

    }

}

void view_books_unsorted(void)
{
    FILE* BP=fopen("library.txt","r");
    int i;
    bookinfo book[1000]= {0};
    for(i=0;; i++)
    {

        fscanf(BP,"%d\n",&book[i].id);
        if(feof(BP))
            break;
        fscanf(BP,"%d\n",&book[i].quantity);
        fscanf(BP,"%[^\n]",book[i].name);

    }
    fclose(BP);

    for(int j=0; j<i; j++)
    {
        printf("\nBook No.%d\n",j+1);
        printf("ID : %d\n",book[j].id);
        printf("Quantity : %d\n",book[j].quantity);
        printf("Name : %s\n",book[j].name);
    }



}

void view_books_sorted(void)
{
    FILE* BP=fopen("library.txt","r");
    int i;
    bookinfo book[1000]= {0};
    for(i=0;; i++)
    {

        fscanf(BP,"%d\n",&book[i].id);
        if(feof(BP))
            break;
        fscanf(BP,"%d\n",&book[i].quantity);
        fscanf(BP,"%[^\n]",book[i].name);

    }

    bookinfo temp;
    for(int s=0; s<i-1; s++)
    {
        for(int j=s+1; j<i; j++)
        {
            if(strcmp(book[s].name,book[j].name)>0)
            {
                temp = book[s];
                book[s] = book[j];
                book[j] = temp;

            }
        }
    }
    for(int j=0; j<i; j++)
    {
        printf("\n\t Book No.%d\n",j+1);
        printf("ID : %d\n",book[j].id);
        printf("Quantity : %d\n",book[j].quantity);
        printf("Name : %s\n",book[j].name);
    }

    fclose(BP);


}

int lsr(bookinfo book[], int r, int key)
{

    int l=0;
    if (r < l)
        return -1;
    if (book[l].id == key)
        return l;
    if (book[r].id == key)
        return r;
    l++;
    return lsr(book,r - 1, key);

}


void search_book_id(int s)
{
    int f=1;
    FILE* BP=fopen("library.txt","r");
    int i;
    bookinfo book[1000]= {0};
    for(i=0;; i++)
    {
        fscanf(BP,"%d\n",&book[i].id);
        if(feof(BP))
            break;
        fscanf(BP,"%d\n",&book[i].quantity);
        fscanf(BP,"%[^\n]",book[i].name);
    }
    fclose(BP);


    if(lsr(book,i,s)==-1)printf("NOT FOUND\n");
    else
    {
        int z=lsr(book,i,s);
        printf("ID : %d\n",book[z].id);
        printf("Quantity : %d\n",book[z].quantity);
        printf("Name : %s\n",book[z].name);


    }
}


int binarySearch(bookinfo book[],char searchKey[], int low, int high )
{
    int middle;
    while ( low <= high )
    {
        middle = ( low + high ) / 2;
        if ( strcmp(searchKey,book[ middle ].name )==0)
            return middle;
        else if ( strcmp(searchKey, book[ middle ].name)<0  )
            high = middle - 1;
        else
            low = middle + 1;
    }
    return -1;
}

void search_book_name(char s[])
{
    FILE* BP=fopen("library.txt","r");
    int i;
    bookinfo book[1000]= {0};
    for(i=0;; i++)
    {

        fscanf(BP,"%d\n",&book[i].id);
        if(feof(BP))
            break;
        fscanf(BP,"%d\n",&book[i].quantity);
        fscanf(BP,"%[^\n]",book[i].name);

    }
    fclose(BP);

    bookinfo temp;
    for(int s=0; s<i-1; s++)
    {
        for(int j=s+1; j<i; j++)
        {
            if(strcmp(book[s].name,book[j].name)>0)
            {
                temp = book[s];
                book[s] = book[j];
                book[j] = temp;

            }
        }
    }

    int result;
    int f=1;
    result= binarySearch(book,s,0,i-1);
    if(result>=0)
    {

        printf("\n");
        printf("ID : %d\n",book[result].id);
        printf("Quantity : %d\n",book[result].quantity);
        printf("Name : %s\n",book[result].name);

        f=0;


    }

    else printf("NOT FOUND\n");
}


void delete_book_id(int del)
{

    int f=-1;
    FILE* BP=fopen("library.txt","r");
    int i;
    bookinfo book[1000]= {0};
    for(i=0;; i++)
    {

        fscanf(BP,"%d\n",&book[i].id);
        if(feof(BP))
            break;
        fscanf(BP,"%d\n",&book[i].quantity);
        fscanf(BP,"%[^\n]",book[i].name);
        if(book[i].id==del)
            f=i;

    }
    fclose(BP);
    if(f==-1)printf("\nBook Not Found\n");
    else
    {


        FILE* B=fopen("library.txt","w");
        for(i=0;; i++)
        {
            if(i==f)
                continue;
            if(book[i].id==0||book[i].quantity==0||book[i].name==NULL)
                break;
            fprintf(B,"%d\n",book[i].id);
            fprintf(B,"%d\n",book[i].quantity);
            fprintf(B,"%s\n",book[i].name);

        }
        printf("\nThe book has been successfully deleted\n");
        fclose(B);
    }

}


int main()
{

    char ch[3];

    do
    {
        system("cls");
        printf("\n\n\n\t\tEnter \"1\" To Add New Books.\n");
        printf("\t\tEnter \"2\" To Display Books Unsorted.\n");
        printf("\t\tEnter \"3\" To Display Books sorted by name.\n");
        printf("\t\tEnter \"4\" To Search Book by ID.\n");
        printf("\t\tEnter \"5\" To Search Book by Name.\n");
        printf("\t\tEnter \"6\" To Delete Book by ID.\n");
        printf("\t\tEnter \"7\" Exit.\n");

        printf("\n\n\t\t\tEnter your choice : ");

        int choice ;
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:add_book();break;
        case 2:view_books_unsorted();break;
        case 3:view_books_sorted();break;
        case 4:
            {
                int ids;
                printf("Enter ID : ");
                scanf("%d",&ids);
                search_book_id(ids);
                break;
            }


        case 5:
            {
                char str[30];
                printf("Enter Name : ");
                getchar();
                gets(str);
                search_book_name(str);
                break;
            }

        case 6:
        {
            int del;
            printf("Enter ID : ");
            scanf("%d",&del);
            delete_book_id(del);
            break;
        }
        case 7:exit(1);break;
        default:printf("\nPlease Enter Valid value");
        }

        printf ("\nTo do another operation Enter YES or yes , To Exit Enter NO or no: ");
        scanf (" %s", &ch);
    }
    while ((ch[0] == 'y'&&ch[1] == 'e'&&ch[2] == 's')  || (ch[0] == 'Y'&&ch[1] == 'E'&&ch[2] == 'S'));
}

