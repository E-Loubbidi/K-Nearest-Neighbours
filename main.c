#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>


typedef struct point
{
    double x;
    double y;
    double m;

}Point;

typedef struct
{
    Point p;
    double dist;

}Distance;

void initialiserPoint(Point *tab[],int N)
{
    int i;
    for(i=0;i<N;i++)
        tab[i]=NULL;
}

void SaisirPoint(Point *tab[],int N,Point *p)
{
    int i;
    for(i=0;i<N;i++)
    {
        if(tab[i]==NULL)
        {
            tab[i]=(Point*)malloc(sizeof(Point));
            tab[i]->x = p->x;
            tab[i]->y = p->y;
            tab[i]->m = p->m;
            break;
        }
    }
}

void initDataPoints(char *filename, Point *tab[], int N)
{
    FILE *file;
    file=fopen(filename,"r");
    int i=1;
    int x;
    int y;
    int m;

    if (file == NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    fseek(file, 5, SEEK_SET);

    while(i<=N)
    {
        Point* p = (Point*)malloc(sizeof(Point));
        fscanf(file,"%lf",&p->x);
        fscanf(file,"%lf",&p->y);
        fscanf(file,"%lf",&p->m);
        SaisirPoint(tab, N, p);
        i++;
    }

    fclose(file);
}

void afficherPoint(Point *tab[],int N)
{
    int i;
    for(i=0;i<N;i++)
        if(tab[i]!=NULL)    printf("\n(%lf - %lf - %lf)\n",tab[i]->x,tab[i]->y,tab[i]->m);
}

void calculerDistance(Point *P,Point *tab[],Distance *Dist[],int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        Dist[i]=(Distance*)malloc(sizeof(Distance));
        Dist[i]->p=*tab[i];
        Dist[i]->dist=sqrt(pow(P->x-tab[i]->x,2)+pow(P->y-tab[i]->y,2));
    }
}

void trierDistance(Distance *Dist[],int N)
{
    int i,j,k;
    Distance *aux;
    for(i=0;i<N-1;i++)
    {
        k=i;
        for(j=i+1;j<N;j++)
            if(Dist[j]->dist < Dist[k]->dist)   k=j;
        aux=Dist[i];
        Dist[i]=Dist[k];
        Dist[k]=aux;
    }
}

int decider(Distance *Dist[],int k)
{
    int i,NG1,NG2;
    for(i=0;i<k;i++)
    {
        if(Dist[i]->p.m==1) NG1++;
        else NG2++;
    }
    if(NG1 > NG2) return 1;
    return 2;
}

void prevoirMaladie(Point *P,Point *tab[],Distance *Dist[],int k,int N)
{
    calculerDistance(P,tab,Dist,N);
    trierDistance(Dist,N);
    P->m=decider(Dist,k);
}

int main()
{
    const int k = 3, N = 17;
    int rep;
    Point P,*tab[N];
    Distance *Dist[N];

    initialiserPoint(tab,N);

    initDataPoints("file.txt", tab, N);

    afficherPoint(tab,N);

    printf("\n----------Prevision de la maladie----------\n");

    do
    {
        printf("x = ");
        scanf("%lf",&P.x);
        printf("y = ");
        scanf("%lf",&P.y);

        prevoirMaladie(&P,tab,Dist,k,N);

        printf("(%lf,%lf,%lf)\n",P.x,P.y,P.m);

        printf("Entrer un nombre # 0 pour une autre prevision, ou entrer 0 pour quitter... ");
        scanf("%d",&rep);

    }while(rep);

    printf("\nAppuyer sur une touche pour continuer... ");
    getch();
    return 0;
}