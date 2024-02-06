#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include<stdio.h>
#include<cstring>
#include <windows.h>
#include <mmsystem.h>
#define width 800
#define height 800
#include<cmath>
#include <graphics.h>
#define MAX 20
#define FUNDAL RED
#define MAX_INPUT_LEN 256
#define euler 2.7182818
#include <fstream>
using namespace std;

ifstream fin("arbore.in");
ofstream fout("rez.in");

char s[256],simbol[]="+-*/^<>=#()",func[]="acslre", rez[50], rez_c, cif_car, sir_num[256], rez_c_sir[50];
int  fr[200], ok_var=1, verif_expresie=1, verif_rad=1,verif_ln=1,verif_div=1, verif_put=1, poz_er, k, val_top_int;
float op, val_var,val_top;
float put(float x, float y)
{
    return pow(x,y);
}
struct nod
{
    float val;
    nod *urm;
};
struct nod_char
{
    char val;
    nod_char *urm;
};
nod* newNode(float val)
{
    nod* nodNou = new nod();
    nodNou -> val = val;
    nodNou -> urm = NULL;
    return nodNou;
}
nod_char *newNode_char(char val)
{
    nod_char* nodNou = new nod_char();
    nodNou -> val = val;
    nodNou -> urm = NULL;
    return nodNou;
}
void push(nod *&p, float val)
{
    nod* nodNou = newNode(val);
    nodNou->urm=p;
    p=nodNou;
}
void push_char(nod_char *&p, char val)
{
    nod_char *nodNou = newNode_char(val);
    nodNou->urm=p;
    p=nodNou;
}
float pop(nod *&p)
{
    if(p==NULL)
        return 0;
    nod* tmp = p;
    p=p->urm;
    float rezultat=tmp->val;
    delete tmp;
    return rezultat;
}
char pop_char(nod_char *&p)
{
    if(p==NULL)
        return 0;
    nod_char* tmp = p;
    p=p->urm;
    char rezultat=tmp->val;
    delete tmp;
    return rezultat;
}
float top(nod *p)
{
    if(p==NULL)
        return 0;
    return p->val;
}
char top_char(nod_char *p)
{
    if(p==NULL)
        return 0;
    return p->val;
}
float conv(nod *&operand, nod_char *&operatr)
{
    float x,y,op;
    y=pop(operand);
    x=pop(operand);
    switch(top_char(operatr))
    {
    case '+':
        op=x+y;
        break;
    case '-':
        op=x-y;
        break;
    case '*':
        op=x*y;
        break;
    case '/':
        if(y==0)
        {
            verif_expresie=0;
            verif_div=0;
        }
        else
            op=x/y;
        break;
    case '^':
        if(x==0 && y==0)
        {
            verif_expresie=0;
            verif_put=0;
        }
        else
            op=put(x,y);
        break;
    case '<':
        op=x<y;
        break;
    case '>':
        op=x>y;
        break;
    case '=':
        op=(x==y);
        break;
    case '#':
        op=(x!=y);
        break;
    case 'a':
        op=abs(y);
        break;
    case 'c':
        op=cos(y);

        break;
    case 's':
        op=sin(y);
        break;
    case 'l':
        if(y<=0)
        {
            verif_expresie=0;
            verif_ln=0;
        }
        else
            op=log(y);
        break;
    case 'r':
        if(y<0)
        {
            verif_expresie=0;
            verif_rad=0;
        }
        else
            op=sqrt(y);
        break;
    case 'e':
        op=exp(y);
        break;
    }
    return op;
}


void citit(int a,int b);
char inputbuf[256];
int input_pos = 0;
int var_intr = 0;




float expresie(char s[], char rez[])
{
    fr['(']=0, fr[')']=0;
    fr['+']=1, fr['-']=1;
    fr['*']=2, fr['/']=2;
    fr['^']=3;
    fr['<']=4, fr['>']=4, fr['=']=4, fr['#']=4;
    fr['a']=5, fr['c']=5, fr['s']=5, fr['l']=5, fr['r']=5, fr['e']=5;
    float num=0,p=10,fract;
    int i, nr_par_desc=0, nr_par_inc=0;
    nod_char *operatr;
    nod *operand;
    for(i=0; i<strlen(s); i++)
        if(s[i]=='(')
            nr_par_desc++;
        else if(s[i]==')')
            nr_par_inc++;
    if(nr_par_desc!=nr_par_inc || s[0]==')')
    {
        strcpy(rez,"Eroare: Parantezarea este gresita!");
        verif_expresie=0;
        return 0;
    }
    for(i=0; i<strlen(s); i++)
    {
        if(strchr(simbol,s[0]) && s[0]!='-' && s[0]!='(' && s[0]!='+')
        {
            strcpy(rez,"Eroare: Primul caracter nu poate fi operator!                                    ");
            verif_expresie=0;
            return 0;
        }
        else if(strchr(simbol,s[i]) && strchr(simbol,s[i+1]) && s[i]!='(' && s[i]!=')'&& s[i+1]!='(')
        {
            rez_c=i+1;
            if(rez_c<10)
            {
                rez_c=i+1+'0';
                strcpy(rez,"Eroare (pozitia ");
                rez[16]=rez_c;
                strcat(rez,"): Nu putem avea 2 operatori consecutivi!");
                verif_expresie=0;
                return 0;
            }
            else
            {
                sprintf(rez_c_sir, "%i", rez_c);
                strcpy(rez,"Eroare (pozitia ");
                strcat(rez,rez_c_sir);
                strcat(rez,"): Nu putem avea 2 operatori consecutivi!");
                verif_expresie=0;
                return 0;
            }
        }
        else if(strchr(simbol,s[i]) && s[i+1]=='(')
        {
            i=i+1;
            while(s[i]=='(')
                i++;
            if(strchr(simbol,s[i]) && s[i]!='-')
            {
                rez_c=i+1;
                if(rez_c<10)
                {
                    rez_c=i+1+'0';
                    strcpy(rez,"Eroare (pozitia ");
                    rez[16]=rez_c;
                    strcat(rez,"): Nu putem avea 2 operatori consecutivi!");
                    verif_expresie=0;
                    return 0;
                }
                else
                {
                    sprintf(rez_c_sir, "%i", rez_c);
                    strcpy(rez,"Eroare (pozitia ");
                    strcat(rez,rez_c_sir);
                    strcat(rez,"): Nu putem avea 2 operatori consecutivi!");
                    verif_expresie=0;
                    return 0;
                }
            }
        }
    }
    for(i=0; i<strlen(s); i++)
    {
        if(verif_rad==0 || verif_ln==0 || verif_div==0 || verif_put==0)
        {
            poz_er=i-2;
            break;
        }
        else if(s[i]=='(')
            push_char(operatr, s[i]);
        else if(s[i]==')')
        {
            while(top_char(operatr)!='(')
            {
                op=conv(operand, operatr);
                push(operand, op);
                pop_char(operatr);
            }
            pop_char(operatr);
        }
        else if(s[i]=='-' && (i==0 || s[i-1]=='(') && isdigit(s[i+1]))
        {
            i=i+1;
            num=0;
            p=10;
            while(isdigit(s[i]))
            {
                num=num*10+(s[i]-'0');
                i++;
            }
            if(s[i]=='.')
            {
                i++;
                while(isdigit(s[i]))
                {
                    fract=((s[i]-'0')/p);
                    num=num+fract;
                    p*=10;
                    i++;
                }
            }
            i--;
            num=num*(-1);
            push(operand,num);
        }
        else if(s[i]=='a' && s[i+1]=='b' && s[i+2]=='s' && s[i+3]=='(')
        {
            push(operand,0);
            push_char(operatr,'a');
            i=i+2;
        }
        else if(s[i]=='c' && s[i+1]=='o' && s[i+2]=='s' && s[i+3]=='(')
        {
            push(operand,0);
            push_char(operatr,'c');
            i=i+2;
        }
        else if(s[i]=='s' && s[i+1]=='i' && s[i+2]=='n' && s[i+3]=='(')
        {
            push(operand, 0);
            push_char(operatr,'s');
            i=i+2;
        }
        else if (s[i]=='l' && s[i+1]=='n' && s[i+2]=='(')
        {
            push(operand, 0);
            push_char(operatr,'l');
            i=i+1;
            poz_er=i+2;
        }
        else if(s[i]=='r' && s[i+1]=='a' && s[i+2]=='d' && s[i+3]=='(')
        {
            push(operand, 0);
            push_char(operatr,'r');
            i=i+2;
            poz_er=i+2;
        }
        else if(s[i]=='e' && s[i+1]=='x' && s[i+2]=='p' && s[i+3]=='(')
        {
            push(operand, 0);
            push_char(operatr,'e');
            i=i+2;
        }
        else if(s[i]=='e' && strchr(simbol,s[i+1]))
            push(operand, euler);
        else if(isdigit(s[i]))
        {
            num=0;
            p=10;
            while(isdigit(s[i]))
            {
                num=num*10+(s[i]-'0');
                i++;
            }
            if(s[i]=='.')
            {
                i++;
                while(isdigit(s[i]))
                {
                    fract=((s[i]-'0')/p);
                    num=num+fract;
                    p*=10;
                    i++;
                }
            }
            i--;
            push(operand,num);
        }
        else if(isalpha(s[i]))
        {
            while(strchr(simbol,s[i+1])==0)
                i=i+1;
            if(ok_var==1)
            {
                cout<<"Introduceti valorile variabilelor(constante): ";
                ok_var=0;
            }
            cin>>val_var;
            push(operand, val_var);
        }
        else if(strchr(simbol,s[i]) && (strchr(simbol,top_char(operatr))==0) && (strchr(func,top_char(operatr))==0))
            push_char(operatr,s[i]);
        else if(strchr(simbol,s[i]) && fr[s[i]]<=fr[top_char(operatr)])
        {
            while(fr[s[i]]<=fr[top_char(operatr)] && (strchr(simbol,top_char(operatr)) || strchr(func,top_char(operatr))))
            {
                op=conv(operand, operatr);
                pop_char(operatr);
                push(operand,op);
            }
            push_char(operatr,s[i]);
        }
        else if(strchr(simbol,s[i]) && fr[s[i]]>fr[top_char(operatr)])
            push_char(operatr,s[i]);

    }
    while(verif_expresie==1 && (strchr(simbol,top_char(operatr)) || strchr(func,top_char(operatr))))
    {
        op=conv(operand, operatr);
        pop_char(operatr);
        push(operand,op);

    }
    if(verif_expresie==1)
    {
        strcpy(rez,"Rezultatul este: ");
        val_top=top(operand);
        k=-1;
        if(val_top<0)
        {
            if(val_top==int(val_top))
            {
                val_top_int=int(val_top);
                strcat(rez,"-");
                val_top_int=abs(val_top_int);
                do
                {
                    k++;
                    cif_car=(val_top_int%10)+'0';
                    sir_num[k]=cif_car;
                    val_top_int/=10;
                }
                while(val_top_int);
                strrev(sir_num);
                strcat(rez,sir_num);
            }
            else
            {
                strcat(rez,"-");
                val_top=abs(val_top);
                sprintf(sir_num, "%f", val_top);
                strcat(rez,sir_num);
            }
        }
        else if(val_top==int(val_top))
        {
            val_top_int=int(val_top);
            do
            {
                k++;
                cif_car=(val_top_int%10)+'0';
                sir_num[k]=cif_car;
                val_top_int/=10;
            }
            while(val_top_int);
            strrev(sir_num);
            strcat(rez,sir_num);
        }
        else
        {
            sprintf(sir_num, "%f", val_top);
            strcat(rez,sir_num);
        }
    }
    else if(verif_rad==0)
    {
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): Radicalul nu poate fi negativ!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): Radicalul nu poate fi negativ!");
            verif_expresie=0;
        }
    }
    else if(verif_ln==0)
    {
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): Logaritmul trebuie sa fie mai mare ca 0!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): Logaritmul trebuie sa fie mai mare ca 0!");
            verif_expresie=0;
        }
    }
    else if(verif_div==0 && poz_er==0)
    {
        for(i=strlen(s)-1; i>=0; i--)
            if(s[i]=='/')
            {
                poz_er=i+1;
                break;
            }
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): Impartirea la 0 este nedefinita!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): Impartirea la 0 este nedefinita!");
            verif_expresie=0;
        }
    }
    else if(verif_div==0)
    {
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): Impartirea la 0 este nedefinita!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): Impartirea la 0 este nedefinita!");
            verif_expresie=0;
        }
    }
    else if(verif_put==0 && poz_er==0)
    {
        for(i=strlen(s)-1; i>=0; i--)
            if(s[i]=='^')
            {
                poz_er=i+1;
                break;
            }
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): 0 la puterea 0 este nedefinit!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): 0 la puterea 0 este nedefinit!");
            verif_expresie=0;
        }
    }
    else if(verif_put==0)
    {
        if(poz_er<10)
        {
            rez_c=poz_er+'0';
            strcpy(rez,"Eroare (pozitia ");
            rez[16]=rez_c;
            strcat(rez,"): 0 la puterea 0 este nedefinit!");
            verif_expresie=0;
        }
        else
        {
            sprintf(rez_c_sir, "%i", poz_er);
            strcpy(rez,"Eroare (pozitia ");
            strcat(rez,rez_c_sir);
            strcat(rez,"): 0 la puterea 0 este nedefinit!");
            verif_expresie=0;
        }
    }
}

void loading()
{
    for(int i=0; i<360*360; i++)
    {
        cleardevice();
        arc(900,400,-i,80-i,100);
        swapbuffers();
    }
}

void eval()
{
    for(int i=0; i<=8; i++)
    {
        settextstyle(10,0,5);
        outtextxy(835,15,"E");
        setcolor(i);
        outtextxy(875,15,"V");
        setcolor(i+1);
        outtextxy(915,15,"A");
        setcolor(i+2);
        outtextxy(955,15,"L");
        setcolor(i+3);
        delay(200);

    }
    setcolor(WHITE);
    outtextxy(835,15,"E");
    outtextxy(875,15,"V");
    outtextxy(915,15,"A");
    outtextxy(955,15,"L");
}

typedef unsigned char byte;

char* fctcitit(int x1,int y1, byte colorback = 0, byte colorfont = 15, byte limit = 0)
{
    byte x=0;
    int i=0;
    char in[2];
    in[0]=' ';
    in[1]='\0';
    char *texto;

    int originalcolor = getcolor();

    while(*in!=(char)13)
    {
        in[0]=getch();
        if(in[0]==(char)13)
            break;
        else if(in[0]==(char)8)
        {

            x--;
            i-=7;
            setcolor(colorback);
            in[0]= texto[x];
            outtextxy(x1+i,y1,in);
            i+=7;
            texto[x]=in[0];
            x++;
        }
    }
    setcolor(originalcolor);
    texto[x]='\0';
    return (texto);
}

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

bool apartine(punct P, dreptunghi D)
{
    return D.SS.x<=P.x && P.x<=D.DJ.x && D.SS.y<=P.y && P.y<=D.DJ.y;

}

struct buton
{
    dreptunghi D;
    int culoare;
    char text[256];
};

struct casuta
{
    dreptunghi D;
    char text[256];
    int valoare;

};
buton B[3];
int nrButoane = 3 ;
int nrCasute = 3;
casuta C[3];

void deseneazaMeniul();

void citit(int a,int b)
{
    char c;
    int the_end = 0;
    do
    {
        outtextxy (a,b, inputbuf);
        c = getch();
        switch (c)
        {
        case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                inputbuf[input_pos]=' ';
                inputbuf[input_pos+1]=' ';
            }
            break;
        case 13: /* return */
            the_end = 1;
            break;
        case 27: /* Escape = Abort */
            inputbuf[0] = 0;
            the_end = 1;
            break;
        default:
            if (input_pos < MAX_INPUT_LEN-1 && c >= ' ' && c <= '~')
            {
                inputbuf[input_pos] = c;
                input_pos++;
                inputbuf[input_pos] = 0;
            }
        }
    }
    while (!the_end);
}


///void readimagefile(const char* filename=NULL, int left=0,int top=0,int right=INT_MAX,int bottom=INT_MAX);

void deseneazaMeniulPrinc()
{
    readimagefile("BOSULICA.jpg",0,0,1800,1600);
    settextstyle(10,0,5);
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(600,0,1200,1600);
    bar(599,0,1201,1600);
    eval();
    for (int i=1; i<=nrButoane; i++)
    {
        B[i].D.SS.y=200*i;
        B[i].D.DJ.y=200*(i+1)-10;
        B[i].D.SS.x=730;
        B[i].D.DJ.x=1080;


        switch(i)
        {
        case 1:
            strcpy(B[i].text,"   Start");
            break;
        case 2:
            strcpy(B[i].text,"   Reguli");
            break;
        case 3:
            strcpy(B[i].text," Informatii");
            break;
        }
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        setcolor(BLACK);
        bar(B[i].D.SS.x, B[i].D.SS.y, B[i].D.DJ.x, B[i].D.SS.y);
        setbkcolor(BLACK);
        setcolor(WHITE);
        outtextxy(B[i].D.SS.x+30,B[i].D.SS.y+80,B[i].text);
    }

}
void eval2()
{
    for(int i=0; i<=8; i++)
    {
        settextstyle(10,0,5);

        outtextxy(840,270,"E");
        setcolor(i);
        outtextxy(880,270,"V");
        setcolor(i+1);
        outtextxy(920,270,"A");
        setcolor(i+2);
        outtextxy(960,270,"L");
        setcolor(i+3);

    }
}
void deseneazaReguli()
{
    readimagefile("BOSULICA.jpg",0,0,1800,1600);
    rectangle(200,100,1600,1400);
    bar(199,101,1599,1301);
    eval2();
    rectangle(730,200,1080,390);

}

void deseneazaInformatii()
{
    readimagefile("BOSULICA.jpg",0,0,1800,1600);
    rectangle(199,101,1599,899);
    bar(199,101,1599,899);
    eval2();
    rectangle(730,200,1080,390);

}

void deseneazaMeniul3();


void deseneazaMeniul2()
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(100,300,1700,200);
    strcpy(C[2].text,"Rezultatul este:");
    outtextxy(150,240,C[2].text);

    for (int i=2; i<=3; i++)
    {
        B[i].D.SS.x=400*i;
        B[i].D.DJ.x=400*(i+1)-10;
        B[i].D.SS.y=600;
        B[i].D.DJ.y=680;


        switch(i)
        {
        case 2:
            strcpy(B[i].text,"Afisare arbore");
            break;
        case 3:
            strcpy(B[i].text,"Iesire");
            break;
        }
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        bar(B[i].D.SS.x, B[i].D.SS.y+30, B[i].D.DJ.x, B[i].D.SS.y);
        setbkcolor(BLACK);
        setcolor(WHITE);
        outtextxy(B[i].D.SS.x+15,B[i].D.SS.y+10,B[i].text);
    }
}

void deseneazaMeniul()
{

    setcolor(WHITE);
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(100,100,1700,200);
    strcpy(C[1].text,"Introduceti expresia:");
    outtextxy(150,140,C[1].text);
    rectangle(100,300,1700,200);
    strcpy(C[2].text,"Rezultatul este:");
    outtextxy(150,240,C[2].text);
    for (int i=1; i<=nrButoane; i++)
    {
        B[i].D.SS.x=360*i;
        B[i].D.DJ.x=360*(i+1)-10;
        B[i].D.SS.y=600;
        B[i].D.DJ.y=680;


        switch(i)
        {
        case 1:
            strcpy(B[i].text,"    Reset");
            break;
        case 2:
            strcpy(B[i].text,"   Arbore");
            break;
        case 3:
            strcpy(B[i].text,"   Iesire");
            break;
        }
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        bar(B[i].D.SS.x, B[i].D.SS.y+30, B[i].D.DJ.x, B[i].D.SS.y);
        setbkcolor(BLACK);
        setcolor(WHITE);
        outtextxy(B[i].D.SS.x+15,B[i].D.SS.y+10,B[i].text);
    }
}

int butonAles()
{
    int i;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x=mousex();
        p.y=mousey();
        for (i=1; i<=nrButoane; i++)
            if (apartine(p,B[i].D))
            {
                PlaySound("Sunet3.wav",NULL, SND_SYNC);
                return i;
            }
    }
    return 0;
}

struct nod_arb
{
    int nivel, coloana;
    char info[5];
    nod_arb *st, *dr;
};
nod_arb *arb;

int n;
char v[1000][5];
int latime, inaltime;

struct tabel
{
    int x1_arb, x2_arb, y1_arb, y2_arb;
} mat[1000][1000];
int numar(nod_arb *p)
{
    if(p==NULL) return 0;
    else return (1+numar(p->st)+numar(p->dr));
}
void creeare(nod_arb *&p, int i)
{
    p=new nod_arb;
    strcpy(p->info,v[i]);
    if(strcmp(v[2*i+1],"#")==0 || 2*i+1>=n) p->st=NULL;
    else creeare(p->st,2*i+1);
    if(strcmp(v[2*i+2],"#")==0 || 2*i+2>=n) p->dr=NULL;
    else creeare(p->dr,2*i+2);
}
void creearepozitii(nod_arb *&p, int i, int col, int st)
{
    p->nivel=log2(i+1)+1;
    if(p==arb) p->coloana=col;
    else
    {
        if(st) p->coloana=col-1-numar(p->dr);
        else p->coloana=col+1+numar(p->st);
    }
    if(strcmp(v[2*i+1],"#")==0 || 2*i+1>=n) p->st=NULL;
    else creearepozitii(p->st,2*i+1,p->coloana,1);
    if(strcmp(v[2*i+2],"#")==0 || 2*i+2>=n) p->dr=NULL;
    else creearepozitii(p->dr,2*i+2,p->coloana,0);
}
void desentabel()
{
    setcolor(BLACK);
    for(int i=1; i<=inaltime; i++)
        line(0,mat[i][1].y1_arb,width,mat[i][1].y1_arb);
    for(int j=1; j<=latime; j++)
        line(mat[1][j].x1_arb,0,mat[1][j].x1_arb,height);
}
void desen(nod_arb *p, nod_arb *tata, int st)
{
    settextstyle(10,HORIZ_DIR,2);
    setcolor(WHITE);
    if(p!=NULL)
    {
        int x=(mat[p->nivel][p->coloana].x2_arb-mat[p->nivel][p->coloana].x1_arb)/2+mat[p->nivel][p->coloana].x1_arb;
        int y=(mat[p->nivel][p->coloana].y2_arb-mat[p->nivel][p->coloana].y1_arb)/2+mat[p->nivel][p->coloana].y1_arb;
        int r=min((mat[p->nivel][p->coloana].x2_arb-mat[p->nivel][p->coloana].x1_arb)/2,(mat[p->nivel][p->coloana].y2_arb-mat[p->nivel][p->coloana].y1_arb)/2);
        circle(x,y,r);
        outtextxy(x,y,p->info);
        if(p!=arb)
        {
            if(st)line(x,y-r,mat[tata->nivel][tata->coloana].x1_arb,(mat[tata->nivel][tata->coloana].y2_arb-mat[tata->nivel][tata->coloana].y1_arb)/2+mat[tata->nivel][tata->coloana].y1_arb);
            else line(x,y-r,mat[tata->nivel][tata->coloana].x2_arb,(mat[tata->nivel][tata->coloana].y2_arb-mat[tata->nivel][tata->coloana].y1_arb)/2+mat[tata->nivel][tata->coloana].y1_arb);
        }
        desen(p->st,p,1);
        desen(p->dr,p,0);
    }
}

char rez_arb[256][10], s_arb[256], simbol_curent, vect_stg[256], vect_drp[256];
int i, poz_rez_arb[256],ok=1, verif_prim=1, stg, drp, verif, poz_simbol_curent, nr_par_inc, nr_par_desc, cap_1, cap_2, cap_1_vect_stg, cap_2_vect_stg, cap_1_vect_drp, cap_2_vect_drp;
int z, poz_ult_car;

bool verif_put_2(int n)
{
    while(n%2==0)
        n/=2;
    if(n==1)
        return 1;
    else
        return 0;
}

void caut_stanga(int i)
{
    verif=1;
    if(verif==1)
        for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
            if(s_arb[stg]=='+' || s_arb[stg]=='-')
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=s_arb[stg];
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=stg;
                s_arb[stg]='$';
                verif=0;
                break;
            }
    if(verif==1)
        for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
            if(s_arb[stg]=='*' || s_arb[stg]=='/')
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=s_arb[stg];
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=stg;
                s_arb[stg]='$';
                verif=0;
                break;
            }

    if(verif==1)
        for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
            if(s_arb[stg]=='^')
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=s_arb[stg];
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=stg;
                s_arb[stg]='$';
                verif=0;
                break;
            }

    if(verif==1)
        for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
            if(s_arb[stg]=='=' || s_arb[stg]=='<' || s_arb[stg]=='>')
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=s_arb[stg];
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=stg;
                s_arb[stg]='$';
                verif=0;
                break;
            }

    if(verif==1)
        for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
            if(isdigit(s_arb[stg]) || isalpha(s_arb[stg]) || s_arb[stg]=='.')
            {
                char l[10];
                int k=0;
                poz_rez_arb[2*i+1]=stg;
                fill_n(l,10,0);
                while(isdigit(s_arb[stg]) || isalpha(s_arb[stg]) || s_arb[stg]=='.')
                {
                    l[k]=s_arb[stg];
                    k++;
                    s_arb[stg]='$';
                    stg--;
                }
                stg++;
                strrev(l);
                strcpy(rez_arb[2*i+1],l);
                verif=0;
                break;
            }
}

void caut_dreapta(int i)
{
    verif=1;
    if(verif==1)
    {
        for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
            if(s_arb[drp]=='+' || s_arb[drp]=='-')
            {
                simbol_curent=s_arb[drp];
                poz_simbol_curent=drp;
                verif=0;
            }
        if(verif==0)
        {
            char l[10];
            fill_n(l,10,0);
            l[0]=simbol_curent;
            strcpy(rez_arb[2*i+2],l);
            poz_rez_arb[2*i+2]=poz_simbol_curent;
            s_arb[poz_simbol_curent]='$';
        }
    }
    if(verif==1)
    {
        for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
            if(s_arb[drp]=='*' || s_arb[drp]=='/')
            {
                simbol_curent=s_arb[drp];
                poz_simbol_curent=drp;
                verif=0;
            }
        if(verif==0)
        {
            char l[10];
            fill_n(l,10,0);
            l[0]=simbol_curent;
            strcpy(rez_arb[2*i+2],l);
            poz_rez_arb[2*i+2]=poz_simbol_curent;
            s_arb[poz_simbol_curent]='$';
        }
    }

    if(verif==1)
    {
        for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
            if(s_arb[drp]=='^')
            {
                simbol_curent=s_arb[drp];
                poz_simbol_curent=drp;
                verif=0;
            }
        if(verif==0)
        {
            char l[10];
            fill_n(l,10,0);
            l[0]=simbol_curent;
            strcpy(rez_arb[2*i+2],l);
            poz_rez_arb[2*i+2]=poz_simbol_curent;
            s_arb[poz_simbol_curent]='$';
        }
    }

    if(verif==1)
    {
        for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
            if(s_arb[drp]=='=' || s_arb[drp]=='<' || s_arb[stg]=='>')
            {
                simbol_curent=s_arb[drp];
                poz_simbol_curent=drp;
                verif=0;
            }
        if(verif==0)
        {
            char l[10];
            fill_n(l,10,0);
            l[0]=simbol_curent;
            strcpy(rez_arb[2*i+2],l);
            poz_rez_arb[2*i+2]=poz_simbol_curent;
            s_arb[poz_simbol_curent]='$';
        }
    }

    if(verif==1)
    {
        for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
            if(isdigit(s_arb[drp]) || isalpha(s_arb[drp]) || s_arb[drp]=='.')
            {
                simbol_curent=s_arb[drp];
                poz_simbol_curent=drp;
                verif=0;
            }
        if(verif==0)
        {
            char l[10];
            int k=0;
            drp--;
            fill_n(l,10,0);
            while(isdigit(s_arb[drp]) || isalpha(s_arb[drp]) || s_arb[drp]=='.')
            {
                l[k]=s_arb[drp];
                k++;
                s_arb[drp]='$';
                drp--;
            }
            drp++;
            strrev(l);
            strcpy(rez_arb[2*i+2],l);
            poz_rez_arb[2*i+2]=drp;
        }
    }
}

void creare_vect_stg(int i)
{
    fill_n(vect_stg, 256, 0);
    int k=0;
    cap_2_vect_stg=poz_rez_arb[i]-1;
    for(stg=poz_rez_arb[i]-1; stg>=0 && s_arb[stg]!='$'; stg--)
    {
        vect_stg[k]=s_arb[stg];
        k++;
    }
    cap_1_vect_stg=stg+1;
    strrev(vect_stg);
}

void creare_vect_drp(int i)
{
    fill_n(vect_drp, 256, 0);
    int k=0;
    cap_1_vect_drp=poz_rez_arb[i]+1;
    for(drp=poz_rez_arb[i]+1; drp<strlen(s_arb) && s_arb[drp]!='$'; drp++)
    {
        vect_drp[k]=s_arb[drp];
        k++;
    }
    cap_2_vect_drp=drp-1;
}

void caut_stanga_simbol(int i, char s1, char s2, char s3)
{
    if(verif==1)
        while(simbol_curent=='@')
        {
            nr_par_desc=0;
            nr_par_inc=0;

            for(stg=0; stg<strlen(vect_stg); stg++)
            {
                if(vect_stg[stg]=='(')
                    nr_par_desc++;
                if(vect_stg[stg]==')')
                    nr_par_inc++;
                if((vect_stg[stg]==s1 || vect_stg[stg]==s2 || vect_stg[stg]==s3) && nr_par_desc==nr_par_inc)
                {
                    simbol_curent=vect_stg[stg];
                    poz_simbol_curent=stg;
                    verif=0;
                }
            }
            if(verif==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=poz_simbol_curent+cap_1_vect_stg;
                vect_stg[poz_simbol_curent]='$';
            }

            if(simbol_curent=='@' && vect_stg[cap_1]=='(' && vect_stg[cap_2]==')')
            {
                vect_stg[cap_1]='$';
                vect_stg[cap_2]='$';
                cap_1++;
                cap_2--;
            }
            else break;
        }
}

void caut_dreapta_simbol(int i, char s1, char s2, char s3)
{
    if(verif==1)
        while(simbol_curent=='@')
        {
            nr_par_desc=0;
            nr_par_inc=0;

            for(drp=0; drp<strlen(vect_drp); drp++)
            {
                if(vect_drp[drp]=='(')
                    nr_par_desc++;
                if(vect_drp[drp]==')')
                    nr_par_inc++;
                if((vect_drp[drp]==s1 || vect_drp[drp]==s2 || vect_drp[drp]==s3) && nr_par_desc==nr_par_inc)
                {
                    simbol_curent=vect_drp[drp];
                    poz_simbol_curent=drp;
                    verif=0;
                }
            }
            if(verif==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[2*i+2],l);
                poz_rez_arb[2*i+2]=poz_simbol_curent+cap_1_vect_drp;
                vect_drp[poz_simbol_curent]='$';
            }

            if(simbol_curent=='@' && vect_drp[cap_1]=='(' && vect_drp[cap_2]==')')
            {
                vect_drp[cap_1]='$';
                vect_drp[cap_2]='$';
                cap_1++;
                cap_2--;
            }
            else break;
        }
}

void caut_stanga_paranteze(int i)
{
    simbol_curent='@';
    cap_1=0;
    cap_2=strlen(vect_stg)-1;
    verif=1;
    caut_stanga_simbol(i, '+', '-', '`');

    caut_stanga_simbol(i, '*', '/', '`');

    caut_stanga_simbol(i, '^', '`', '`');

    caut_stanga_simbol(i, '=', '<', '>');

    if(verif==1)
        while(simbol_curent=='@')
        {
            nr_par_desc=0;
            nr_par_inc=0;

            for(stg=0; stg<strlen(vect_stg); stg++)
            {
                if(vect_stg[stg]=='(')
                    nr_par_desc++;
                if(vect_stg[stg]==')')
                    nr_par_inc++;
                if((isdigit(vect_stg[stg]) || isalpha(vect_stg[stg]) || vect_stg[stg]=='.') && nr_par_desc==nr_par_inc)
                {
                    simbol_curent=vect_stg[stg];
                    poz_simbol_curent=stg;
                    verif=0;
                }
            }
            if(verif==0)
            {
                char l[10];
                int k=0;
                fill_n(l,10,0);
                while(isdigit(vect_stg[poz_simbol_curent]) || isalpha(vect_stg[poz_simbol_curent]) || vect_stg[poz_simbol_curent]=='.')
                {
                    l[k]=vect_stg[poz_simbol_curent];
                    k++;
                    vect_stg[poz_simbol_curent]='$';
                    poz_simbol_curent--;
                }
                poz_simbol_curent++;
                strrev(l);
                strcpy(rez_arb[2*i+1],l);
                poz_rez_arb[2*i+1]=poz_simbol_curent+cap_1_vect_stg;

            }

            if(simbol_curent=='@' && vect_stg[cap_1]=='(' && vect_stg[cap_2]==')')
            {
                vect_stg[cap_1]='$';
                vect_stg[cap_2]='$';
                cap_1++;
                cap_2--;
            }
            else break;
        }
}



void caut_dreapta_paranteze(int i)
{
    simbol_curent='@';
    cap_1=0;
    cap_2=strlen(vect_drp)-1;
    verif=1;
    caut_dreapta_simbol(i, '+', '-', '`');

    caut_dreapta_simbol(i, '*', '/', '`');

    caut_dreapta_simbol(i, '^', '`', '`');

    caut_dreapta_simbol(i, '=', '<', '>');

    if(verif==1)
        while(simbol_curent=='@')
        {
            nr_par_desc=0;
            nr_par_inc=0;

            for(drp=0; drp<strlen(vect_drp); drp++)
            {
                if(vect_drp[drp]=='(')
                    nr_par_desc++;
                if(vect_drp[drp]==')')
                    nr_par_inc++;
                if((isdigit(vect_drp[drp]) || isalpha(vect_drp[drp]) || vect_drp[drp]=='.') && nr_par_desc==nr_par_inc)
                {
                    simbol_curent=vect_drp[drp];
                    poz_simbol_curent=drp;
                    verif=0;
                }
            }
            if(verif==0)
            {
                char l[10];
                int k=0;
                fill_n(l,10,0);
                while(isdigit(vect_drp[poz_simbol_curent]) || isalpha(vect_drp[poz_simbol_curent]) || vect_drp[poz_simbol_curent]=='.')
                {
                    l[k]=vect_drp[poz_simbol_curent];
                    k++;
                    vect_drp[poz_simbol_curent]='$';
                    poz_simbol_curent--;
                }
                poz_simbol_curent++;
                strrev(l);
                strcpy(rez_arb[2*i+2],l);
                poz_rez_arb[2*i+2]=poz_simbol_curent+cap_1_vect_drp;

            }

            if(simbol_curent=='@' && vect_drp[cap_1]=='(' && vect_drp[cap_2]==')')
            {
                vect_drp[cap_1]='$';
                vect_drp[cap_2]='$';
                cap_1++;
                cap_2--;
            }
            else break;
        }
}


void vect_tati(char c[], char rez_arb[256][10])
{
    for(i=0; i<strlen(c); i++)
        s_arb[i]=c[i];
    s_arb[i]='\0';

    for(i=0; i<=200; i++)
        strcpy(rez_arb[i],"#");

    for(i=0; i<strlen(s_arb); i++)
        if(s_arb[i]=='(')
            nr_par_desc++;
    if(nr_par_desc==0)
    {
        if(verif_prim==1)
        {
            for(i=0; i<strlen(s_arb); i++)
                if(s_arb[i]=='+' || s_arb[i]=='-')
                {
                    simbol_curent=s_arb[i];
                    poz_simbol_curent=i;
                    verif_prim=0;
                }
            if(verif_prim==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[0],l);
                poz_rez_arb[0]=poz_simbol_curent;
                s_arb[poz_simbol_curent]='$';
            }
        }

        if(verif_prim==1)
        {
            for(i=0; i<strlen(s_arb); i++)
                if(s_arb[i]=='*' || s_arb[i]=='/')
                {
                    simbol_curent=s_arb[i];
                    poz_simbol_curent=i;
                    verif_prim=0;
                }
            if(verif_prim==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[0],l);
                poz_rez_arb[0]=poz_simbol_curent;
                s_arb[poz_simbol_curent]='$';
            }
        }

        if(verif_prim==1)
        {
            for(i=0; i<strlen(s_arb); i++)
                if(s_arb[i]=='^')
                {
                    simbol_curent=s_arb[i];
                    poz_simbol_curent=i;
                    verif_prim=0;
                }
            if(verif_prim==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[0],l);
                poz_rez_arb[0]=poz_simbol_curent;
                s_arb[poz_simbol_curent]='$';
            }
        }

        if(verif_prim==1)
        {
            for(i=0; i<strlen(s_arb); i++)
                if(s_arb[i]=='=' || s_arb[i]=='<' || s_arb[i]=='>')
                {
                    simbol_curent=s_arb[i];
                    poz_simbol_curent=i;
                    verif_prim=0;
                }
            if(verif_prim==0)
            {
                char l[10];
                fill_n(l,10,0);
                l[0]=simbol_curent;
                strcpy(rez_arb[0],l);
                poz_rez_arb[0]=poz_simbol_curent;
                s_arb[poz_simbol_curent]='$';
            }
        }

        if(verif_prim==1)
        {
            for(i=0; i<strlen(s_arb); i++)
                if(isdigit(s_arb[i]) || isalpha(s_arb[i]) || s_arb[i]=='.')
                {
                    simbol_curent=s_arb[i];
                    poz_simbol_curent=i;
                    verif_prim=0;
                }
            if(verif_prim==0)
            {
                char l[10];
                int k=0;
                fill_n(l,10,0);
                while(isdigit(s_arb[poz_simbol_curent]) || isalpha(s_arb[poz_simbol_curent]) || s_arb[poz_simbol_curent]=='.')
                {
                    l[k]=s_arb[poz_simbol_curent];
                    k++;
                    s_arb[poz_simbol_curent]='$';
                    poz_simbol_curent--;
                }
                poz_simbol_curent++;
                strrev(l);
                strcpy(rez_arb[0],l);
                poz_rez_arb[0]=poz_simbol_curent;
            }
        }

        for(i=0; i<50; i++)
        {
            if(strcmp(rez_arb[i],"#")==0 );
            else
            {
                caut_stanga(i);
                caut_dreapta(i);
            }
        }
    }
    else
    {
        simbol_curent='@';
        cap_1=0;
        cap_2=strlen(s_arb)-1;
        verif_prim=1;
        nr_par_desc=0;
        nr_par_inc=0;
        if(verif_prim==1)
            while(simbol_curent=='@')
            {
                nr_par_desc=0;
                nr_par_inc=0;

                for(i=0; i<strlen(s_arb); i++)
                {
                    if(s_arb[i]=='(')
                        nr_par_desc++;
                    if(s_arb[i]==')')
                        nr_par_inc++;
                    if((s_arb[i]=='+' || s_arb[i]=='-') && nr_par_desc==nr_par_inc)
                    {
                        simbol_curent=s_arb[i];
                        poz_simbol_curent=i;
                        verif_prim=0;
                    }
                }
                if(verif_prim==0)
                {
                    char l[10];
                    fill_n(l,10,0);
                    l[0]=simbol_curent;
                    strcpy(rez_arb[0],l);
                    poz_rez_arb[0]=poz_simbol_curent;
                    s_arb[poz_simbol_curent]='$';
                }

                if(simbol_curent=='@' && s_arb[cap_1]=='(' && s_arb[cap_2]==')')
                {
                    s_arb[cap_1]='$';
                    s_arb[cap_2]='$';
                    cap_1++;
                    cap_2--;
                }
                else break;
            }

        nr_par_desc=0;
        nr_par_inc=0;
        if(verif_prim==1)
            while(simbol_curent=='@')
            {
                nr_par_desc=0;
                nr_par_inc=0;

                for(i=0; i<strlen(s_arb); i++)
                {
                    if(s_arb[i]=='(')
                        nr_par_desc++;
                    if(s_arb[i]==')')
                        nr_par_inc++;
                    if((s_arb[i]=='*' || s_arb[i]=='/') && nr_par_desc==nr_par_inc)
                    {
                        simbol_curent=s_arb[i];
                        poz_simbol_curent=i;
                        verif_prim=0;
                    }
                }
                if(verif_prim==0)
                {
                    char l[10];
                    fill_n(l,10,0);
                    l[0]=simbol_curent;
                    strcpy(rez_arb[0],l);
                    poz_rez_arb[0]=poz_simbol_curent;
                    s_arb[poz_simbol_curent]='$';
                }

                if(simbol_curent=='@' && s_arb[cap_1]=='(' && s_arb[cap_2]==')')
                {
                    s_arb[cap_1]='$';
                    s_arb[cap_2]='$';
                    cap_1++;
                    cap_2--;
                }
                else break;
            }


        nr_par_desc=0;
        nr_par_inc=0;
        if(verif_prim==1)
            while(simbol_curent=='@')
            {
                nr_par_desc=0;
                nr_par_inc=0;

                for(i=0; i<strlen(s_arb); i++)
                {
                    if(s_arb[i]=='(')
                        nr_par_desc++;
                    if(s_arb[i]==')')
                        nr_par_inc++;
                    if((s_arb[i]=='^') && nr_par_desc==nr_par_inc)
                    {
                        simbol_curent=s_arb[i];
                        poz_simbol_curent=i;
                        verif_prim=0;
                    }
                }
                if(verif_prim==0)
                {
                    char l[10];
                    fill_n(l,10,0);
                    l[0]=simbol_curent;
                    strcpy(rez_arb[0],l);
                    poz_rez_arb[0]=poz_simbol_curent;
                    s_arb[poz_simbol_curent]='$';
                }

                if(simbol_curent=='@' && s_arb[cap_1]=='(' && s_arb[cap_2]==')')
                {
                    s_arb[cap_1]='$';
                    s_arb[cap_2]='$';
                    cap_1++;
                    cap_2--;
                }
                else break;
            }

        nr_par_desc=0;
        nr_par_inc=0;
        if(verif_prim==1)
            while(simbol_curent=='@')
            {
                nr_par_desc=0;
                nr_par_inc=0;

                for(i=0; i<strlen(s_arb); i++)
                {
                    if(s_arb[i]=='(')
                        nr_par_desc++;
                    if(s_arb[i]==')')
                        nr_par_inc++;
                    if((s_arb[i]=='=' || s_arb[i]=='<' || s_arb[i]=='>') && nr_par_desc==nr_par_inc)
                    {
                        simbol_curent=s_arb[i];
                        poz_simbol_curent=i;
                        verif_prim=0;
                    }
                }
                if(verif_prim==0)
                {
                    char l[10];
                    fill_n(l,10,0);
                    l[0]=simbol_curent;
                    strcpy(rez_arb[0],l);
                    poz_rez_arb[0]=poz_simbol_curent;
                    s_arb[poz_simbol_curent]='$';
                }

                if(simbol_curent=='@' && s_arb[cap_1]=='(' && s_arb[cap_2]==')')
                {
                    s_arb[cap_1]='$';
                    s_arb[cap_2]='$';
                    cap_1++;
                    cap_2--;
                }
                else break;
            }

        nr_par_desc=0;
        nr_par_inc=0;
        if(verif_prim==1)
            while(simbol_curent=='@')
            {
                nr_par_desc=0;
                nr_par_inc=0;

                for(i=0; i<strlen(s_arb); i++)
                {
                    if(s_arb[i]=='(')
                        nr_par_desc++;
                    if(s_arb[i]==')')
                        nr_par_inc++;
                    if((isdigit(s_arb[i]) || isalpha(s_arb[i]) || s_arb[i]=='.') && nr_par_desc==nr_par_inc)
                    {
                        simbol_curent=s_arb[i];
                        poz_simbol_curent=i;
                        verif_prim=0;
                    }
                }
                if(verif_prim==0)
                {
                    char l[10];
                    int k=0;
                    fill_n(l,10,0);
                    while(isdigit(s_arb[poz_simbol_curent]) || isalpha(s_arb[poz_simbol_curent]) || s_arb[poz_simbol_curent]=='.')
                    {
                        l[k]=s_arb[poz_simbol_curent];
                        k++;
                        s_arb[poz_simbol_curent]='$';
                        poz_simbol_curent--;
                    }
                    poz_simbol_curent++;
                    strrev(l);
                    strcpy(rez_arb[0],l);
                    poz_rez_arb[0]=poz_simbol_curent;
                }

                if(simbol_curent=='@' && s_arb[cap_1]=='(' && s_arb[cap_2]==')')
                {
                    s_arb[cap_1]='$';
                    s_arb[cap_2]='$';
                    cap_1++;
                    cap_2--;
                }
                else break;
            }

        for(i=0; i<50; i++)
        {
            if(strcmp(rez_arb[i],"#")==0);

            else if(strcmp(rez_arb[i],"cos")==0 || strcmp(rez_arb[i],"sin")==0 || strcmp(rez_arb[i],"exp")==0 || strcmp(rez_arb[i],"abs")==0|| strcmp(rez_arb[i],"rad")==0)
            {
                int k=0,j,nr_par_desc_func=0, nr_par_inc_funct=0;
                fill_n(vect_stg,256,0);
                cap_1_vect_stg=poz_rez_arb[i]+3;
                for(j=poz_rez_arb[i]+3;; j++)
                {
                    if(s_arb[j]=='(')
                        nr_par_desc_func++;
                    if(s_arb[j]==')')
                        nr_par_inc_funct++;
                    vect_stg[k]=s_arb[j];
                    k++;
                    if(nr_par_desc_func==nr_par_inc_funct)
                        break;
                }
                cap_2_vect_stg=j;
                caut_stanga_paranteze(i);

                z=0;
                for(
                    j=cap_1_vect_stg; j<=cap_2_vect_stg; j++)
                {
                    if(vect_stg[z]=='$') s_arb[j]='$';
                    z++;
                }
            }

            else if(strcmp(rez_arb[i],"ln")==0)
            {
                int k=0,j,nr_par_desc_func=0, nr_par_inc_funct=0;
                fill_n(vect_stg,256,0);
                cap_1_vect_stg=poz_rez_arb[i]+2;
                for(j=poz_rez_arb[i]+2;; j++)
                {
                    if(s_arb[j]=='(')
                        nr_par_desc_func++;
                    if(s_arb[j]==')')
                        nr_par_inc_funct++;
                    vect_stg[k]=s_arb[j];
                    k++;
                    if(nr_par_desc_func==nr_par_inc_funct)
                        break;
                }
                cap_2_vect_stg=j;
                caut_stanga_paranteze(i);

                z=0;
                for(
                    j=cap_1_vect_stg; j<=cap_2_vect_stg; j++)
                {
                    if(vect_stg[z]=='$') s_arb[j]='$';
                    z++;
                }
            }

            else
            {
                creare_vect_stg(i);
                caut_stanga_paranteze(i);
                z=0;
                for(int j=cap_1_vect_stg; j<=cap_2_vect_stg; j++)
                {
                    if(vect_stg[z]=='$') s_arb[j]='$';
                    z++;
                }
                creare_vect_drp(i);
                caut_dreapta_paranteze(i);

                z=0;
                for(int j=cap_1_vect_drp; j<=cap_2_vect_drp; j++)
                {
                    if(vect_drp[z]=='$') s_arb[j]='$';
                    z++;
                }
            }
        }
    }
    for(i=0; i<200; i++)
        if(strcmp(rez_arb[i],"#"))
            poz_ult_car=i;
    for(i=poz_ult_car;; i++)
        if(verif_put_2(i+2)==1)
        {
            for(int j=i+1; j<=256; j++)
            {
                char l[10];
                fill_n(l,10,0);
                strcpy(rez_arb[j],l);
            }
            break;
        }
    poz_ult_car=i+1;
}

int main()
{
    int comanda,butonul_apasat,comanda2,butonul_apasat2;
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,(char*)"");
    initwindow(1800,1000);
    deseneazaMeniulPrinc();

    do
    {

        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
        {
            comanda=butonul_apasat;
            switch(comanda)
            {
            case 1:

                cleardevice();
                eval();
                deseneazaMeniul();

                citit(680,140);
                expresie(inputbuf,rez);
                outtextxy(150,240,rez);

                do
                {
                    butonul_apasat2=butonAles();
                    if (butonul_apasat2!=0)
                    {
                        comanda2=butonul_apasat2;
                        switch(comanda2)
                        {
                        case 1:

                            cleardevice();
                            eval();

                            fill_n(inputbuf,256,0);
                            input_pos=0;
                            fill_n(rez,50,0);
                            fill_n(sir_num,256,0);
                            fill_n(rez_c_sir,50,0);
                            ok_var=1, verif_expresie=1, verif_rad=1,verif_ln=1,verif_div=1, verif_put=1, poz_er=0, k=0, val_top_int=0;
                            op=0, val_var=0,val_top=0;
                            deseneazaMeniul();
                            citit(680,140);
                            expresie(inputbuf,rez);
                            outtextxy(150,240,rez);
                            strcpy(B[comanda2].text,"Calculeaza");
                            cout<<"comanda apasata "<<comanda2<<endl;

                            break;
                        case 2:
                        {
                            i, poz_rez_arb[256],ok=1, verif_prim=1, stg, drp, verif=0, poz_simbol_curent=0, nr_par_inc=0, nr_par_desc=0, cap_1=0, cap_2=0, cap_1_vect_stg=0, cap_2_vect_stg=0, cap_1_vect_drp=0, cap_2_vect_drp=0;
                            z=0, poz_ult_car=0;
                            vect_tati(inputbuf,rez_arb);
                            if(verif_expresie==1)
                            {
                                cleardevice();

                                int  latime=0, inaltime=0, w, h, y1_arb, y2_arb, nr;
                                n=poz_ult_car;
                                for(int i=0; i<n; i++)
                                {
                                    strcpy(v[i],rez_arb[i]);
                                    if(strcmp(v[i],"#")) latime++;
                                }
                                inaltime=log2(n+1);
                                w=width/latime;
                                h=height/inaltime;
                                y1_arb=0;
                                y2_arb=h;
                                for(int i=1; i<=inaltime; i++)
                                {
                                    for(int j=1; j<=latime; j++)
                                    {
                                        if(j==1)
                                        {
                                            mat[i][j].x1_arb=0;
                                            mat[i][j].x2_arb=w;
                                        }
                                        else
                                        {
                                            mat[i][j].x1_arb=mat[i][j-1].x2_arb;
                                            mat[i][j].x2_arb=mat[i][j-1].x2_arb+w;
                                        }
                                        mat[i][j].y1_arb=y1_arb;
                                        mat[i][j].y2_arb=y2_arb;
                                    }
                                    y1_arb=y2_arb;
                                    y2_arb+=h;
                                }
                                creeare(arb,0);
                                nr=numar(arb->st);
                                creearepozitii(arb,0,nr+1,0);
                                cleardevice();
                                eval();
                                desen(arb,arb,0);

                                rectangle(1200,400,1600,600);
                                settextstyle(10,0,6);
                                outtextxy(1280,470,"<-INAPOI");
                                while(true)
                                {
                                    if(ismouseclick(WM_LBUTTONDOWN))
                                    {
                                        int x, y;
                                        getmouseclick(WM_LBUTTONDOWN,x,y);
                                        if(x>=1200 && x<=1600 && y>=400 && y<=600)
                                        {
                                            cleardevice();
                                            PlaySound("Sunet3.wav",NULL, SND_SYNC);
                                            eval();

                                            fill_n(inputbuf,256,0);
                                            input_pos=0;
                                            fill_n(rez,50,0);
                                            fill_n(sir_num,256,0);
                                            fill_n(rez_c_sir,50,0);
                                            ok_var=1, verif_expresie=1, verif_rad=1,verif_ln=1,verif_div=1, verif_put=1,poz_er=0, k=0, val_top_int=0;
                                            op=0, val_var=0,val_top=0;
                                            deseneazaMeniul();
                                            citit(680,140);
                                            expresie(inputbuf,rez);
                                            outtextxy(150,240,rez);
                                            strcpy(B[comanda2].text,"Calculeaza");
                                            cout<<"comanda apasata "<<comanda2<<endl;
                                            break;
                                        }
                                    }
                                }



                            }

                            else if(verif_expresie==0)
                            {
                                cleardevice();
                                eval();
                                settextstyle(10,0,2);
                                for(int j=0; j<3000; j++)
                                {
                                    outtextxy(rand()%1800,60+rand()%1000," : ");
                                }
                                settextstyle(10,0,7);
                                outtextxy(55,450,"Nu putem desena arborele");
                                outtextxy(40,500, "pentru o expresie gresita :(");
                                rectangle(1200,400,1600,600);
                                bar(1201,401,1600,600);
                                settextstyle(10,0,6);
                                outtextxy(1280,470,"<-INAPOI");

                                while(true)
                                {
                                    if(ismouseclick(WM_LBUTTONDOWN))
                                    {
                                        int x, y;
                                        getmouseclick(WM_LBUTTONDOWN,x,y);
                                        if(x>=1200 && x<=1600 && y>=400 && y<=600)
                                        {
                                            cleardevice();
                                            PlaySound("Sunet3.wav",NULL, SND_SYNC);
                                            eval();

                                            fill_n(inputbuf,256,0);
                                            input_pos=0;
                                            fill_n(rez,50,0);
                                            fill_n(sir_num,256,0);
                                            fill_n(rez_c_sir,50,0);
                                            ok_var=1, verif_expresie=1, verif_rad=1,verif_ln=1,verif_div=1, verif_put=1,poz_er=0, k=0, val_top_int=0;
                                            op=0, val_var=0,val_top=0;
                                            deseneazaMeniul();
                                            citit(680,140);
                                            expresie(inputbuf,rez);
                                            outtextxy(150,240,rez);
                                            strcpy(B[comanda2].text,"Calculeaza");
                                            cout<<"comanda apasata "<<comanda2<<endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        }


                        break;
                        case 3:
                            strcpy(B[comanda2].text,"    Iesire");
                            cout<<"comanda "<<comanda2<<endl;
                            closegraph();
                            break;
                        }
                    }
                }

                while (comanda2!=3);
                break;

            case 2:

                strcpy(B[comanda].text,"   Reguli");
                cout<<"comanda "<<comanda<<endl;
                cleardevice();
                deseneazaReguli();
                settextstyle(10,0,3);
                outtextxy(250,450,"Input: un sir de caractere, care ar putea reprezenta o expresie in limbajul Basic, folosind:");
                outtextxy(250,480,"-parantezele ( si );");
                outtextxy(250,510,"-operatorii: +, -, /, *, ^, <>, =;");
                outtextxy(250,540,"-functiile matematice sin, cos, rad, log;");
                outtextxy(250,570,"-identificatori de variabile definite prin siruri de litere si cifre, in care prima este litera;");
                outtextxy(250,600,"-valori pentru fiecare dintre variabilele date prin identificatori.");

                outtextxy(250,750,"Output:");
                outtextxy(250,780,"-daca expresia este corecta din punct de vedere sintactic, este afisata valoarea expresiei;");
                outtextxy(250,810,"-daca expresia este gresita, programul va afisa tipul erorii si pozitia acesteia.");

                rectangle(250,900,400,940);
                settextstyle(10,0,2);
                outtextxy(268,910,"Informatii");

                while(true)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN,x,y);
                        if(x>=250 && x<=400 && y>=900 && y<=940)
                        {
                            cleardevice();
                            PlaySound("Sunet3.wav",NULL, SND_SYNC);
                            strcpy(B[comanda].text,"Informatii");
                            cout<<"comanda "<<comanda<<endl;
                            deseneazaInformatii();
                            settextstyle(10,0,3);
                            outtextxy(250,450,"Numarul proiectului: 15");
                            outtextxy(250,480,"Titlul proiectului:  Eval - Evaluator matematic si reprezentarea grafica a arborelui asociat");
                            outtextxy(250,510,"                     expresiei");
                            outtextxy(250,540,"Profesor Coordonator: Stelian Hadimbu");
                            outtextxy(250,570,"Membrii echipei: Bejenaru Matei si Vadana Andrei");
                            break;
                        }
                        break;
                    }
                }

                break;

            case 3:




                strcpy(B[comanda].text,"Informatii");
                cout<<"comanda "<<comanda<<endl;
                deseneazaInformatii();
                settextstyle(10,0,3);
                outtextxy(250,450,"Numarul proiectului: 15");
                outtextxy(250,480,"Titlul proiectului:  Eval - Evaluator matematic si reprezentarea grafica a arborelui asociat");
                outtextxy(250,510,"                     expresiei");
                outtextxy(250,540,"Profesor Coordonator: Stelian Hadimbu");
                outtextxy(250,570,"Membrii echipei: Bejenaru Matei si Vadana Andrei");

                rectangle(250,800,400,840);
                settextstyle(10,0,2);
                outtextxy(290,810,"Reguli");

                while(true)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN,x,y);
                        if(x>=250 && x<=400 && y>=800 && y<=840)
                        {
                            cleardevice();
                            PlaySound("Sunet3.wav",NULL, SND_SYNC);
                            deseneazaReguli();
                            settextstyle(10,0,3);
                            outtextxy(250,450,"Input: un sir de caractere, care ar putea reprezenta o expresie in limbajul Basic, folosind:");
                            outtextxy(250,480,"-parantezele ( si );");
                            outtextxy(250,510,"-operatorii: +, -, /, *, ^, <>, =;");
                            outtextxy(250,540,"-functiile matematice sin, cos, rad, log;");
                            outtextxy(250,570,"-identificatori de variabile definite prin siruri de litere si cifre, in care prima este litera;");
                            outtextxy(250,600,"-valori pentru fiecare dintre variabilele date prin identificatori.");

                            outtextxy(250,750,"Output:");
                            outtextxy(250,780,"-daca expresia este corecta din punct de vedere sintactic, este afisata valoarea expresiei;");
                            outtextxy(250,810,"-daca expresia este gresita, programul va afisa tipul erorii si pozitia acesteia.");
                            break;
                        }
                        break;
                    }
                }


                break;
            }
        }
    }
    while (comanda2!=3);

    return 0;
}
