/*
bfi.c - the main program of bfi.
Copyright (C) 2023-2024 Alexandre Lea.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char version[10]="0.4";
//Copyright Information
void cpr(){
    printf("bfi (BrainFuck Interpreter) v%s Copyright (C) 2023 Alexandre Lea\n",version);
    puts("This program comes with ABSOLUTELY NO WARRANTY; for details please read warranty.");
    puts("This is free software, and you are welcome to redistribute it");
    puts("under certain conditions; please read copying for details.");
}
int max(int a,int b){
    return a>=b?a:b;
}
int min(int a,int b){
    return a<=b?a:b;
}
//Home page of all the program.
int homp(){
    int choice;
    puts("What do you want to do:");
    puts("1 - Edit program");
    puts("2 - Analyze program");
    puts("3 - Run program");
    puts("4 - Debug program");
    puts("5 - Read informations about this program.");
    puts("0 - Exit");
    printf("Please select(0~5):");
    scanf("%d",&choice);
    return choice;
}
char prog[100010]={};
int len=0;
int khop[100010]={},top,stck[100010]={},pt=0,prpt=0,analed=0;
char mem[30010]={};
void edit(){
    char ch,msg[100110]="Your program:";
    puts("You can copy and edit your program. The end sign is '!'.");
    if(strlen(prog)!=0) puts(strcat(msg,prog));
    analed=len=0;
    memset(prog,0,sizeof prog);
    while(scanf("%c",&ch)!=0&&ch!='!')
        if(ch=='['||ch==']'||ch=='<'||ch=='>'||ch=='+'||ch=='-'||ch=='.'||ch==',') prog[len++]=ch;
    return;
}
char getch(){
    char c;
    system("stty -echo;stty -icanon");
    c=getchar();
    system("stty echo;stty icanon");
    return c; 
}
void anal(){
    puts("Analyzing your program...");
    len=strlen(prog);
    if(len==0){
        puts("Your program is empty!");
        return;
    }
    for(int i=0;i<len;i++){
        if(prog[i]=='[') stck[++top]=i;
        if(prog[i]==']'){
            if(top==0){
                for(int j=max(0,i-10);j<=min(len,i+10);j++) printf("%c",prog[j]);
                printf("\n");
                for(int j=max(0,i-10);j<i;j++) printf(" ");
                printf("X\n");
                printf("Extra parenthesis at %d.\n",i);
                puts("");
            }else khop[stck[top]]=i,khop[i]=stck[top],top--;
        }
    }
    if(top!=0){
        printf("Missing parentheses at %d.\n",len);
        return;
    }
    puts("Analysis successful.");
    analed=1;
}
void run(){
    memset(mem,0,sizeof mem);
    getchar();
    if(analed==0){
        puts("Hasn't analyzed yet!");
        return;
    }
    for(prpt=0;prpt!=len+1;prpt++){
        switch(prog[prpt]){
        case '<':
            pt=(pt-1+30000)%30000;
            break;
        case '>':
            pt=(pt+1)%30000;
            break;
        case '+':
            mem[pt]++;
            break;
        case '-':
            mem[pt]--;
            break;
        case '.':
            printf("%c",mem[pt]);
            fflush(stdout);
            break;
        case ',':
            mem[pt]=getch();
            break;
        case '[':
            if(mem[pt]=='\0') prpt=khop[prpt];
            break;
        case ']':
            if(mem[pt]!='\0') prpt=khop[prpt];
            break;
        }
    }
    puts("");
    return;
}
void debug(){
    memset(mem,0,sizeof mem);
    if(analed==0){
        puts("Hasn't analyzed yet!");
        return;
    }
    char ch;
    int mod=1;
    puts("Auto,Fastest or Manual?(A/F/M)");
    ch=getch();
    while(ch!='A'&&ch!='M'&&ch!='a'&&ch!='m'&&ch!='F'&&ch!='f') puts("Please enter A or M."),ch=getch();
    if(ch=='A'||ch=='a') mod=0;
    if(ch=='F'||ch=='f') mod=-1;
    pt=0;
    int outfl=0;
    char outed[100010]={};
    for(prpt=0;prpt!=len+1;prpt++){
        puts("Code area:");
        for(int j=max(0,prpt-10);j<=min(len,prpt+10);j++) printf("%c",prog[j]);
        printf("\n");
        for(int j=max(0,prpt-10);j<prpt;j++) printf(" ");
        printf("N\n");
        puts("Memory area:");
        for(int i=max(0,pt-10);i<=min(pt+10,30000);i++){
            printf("%4d",mem[i]);
            switch(mem[i]){
            case '\0':
                printf("\\0");
                break;
            case '\a':
                printf("\\a");
                break;
            case '\b':
                printf("\\b");
                break;
            case '\t':
                printf("\\t");
                break;
            case '\n':
                printf("\\n");
                break;
            case '\v':
                printf("\\v");
                break;
            case '\f':
                printf("\\f");
                break;
            case '\r':
                printf("\\r");
                break;
            case '\\':
                printf("\\\\");
                break;
            case '\'':
                printf("\\\'");
                break;
            case '\"':
                printf("\\\"");
                break;
            case '\?':
                printf("\\\?");
                break;
            default:
                if(mem[i]>=32) printf(" %c",mem[i]);
                else printf("UO");
            }
        }
        printf("\n");
        for(int i=max(0,pt-10);i<pt;i++) printf("      ");
        printf("NNNNNN\n");
        puts("Out message:");
        printf("%s\n",outed);
        switch(prog[prpt]){
        case '<':
            pt=(pt-1+30000)%30000;
            break;
        case '>':
            pt=(pt+1)%30000;
            break;
        case '+':
            mem[pt]++;
            break;
        case '-':
            mem[pt]--;
            break;
        case '.':
            outed[outfl++]=mem[pt];
            fflush(stdout);
            break;
        case ',':
            printf("Please enter a character:");
            ch=getch();printf("%c\n",ch);
            break;
        case '[':
            if(mem[pt]=='\0') prpt=khop[prpt];
            break;
        case ']':
            if(mem[pt]!='\0') prpt=khop[prpt];
            break;
        }
        if(mod==-1) system("sleep 0.001");
        else if(mod==1) getchar();
        else system("sleep 0.1");
    }
    puts("");
    return;
}
void inform(){
    printf("bfi - BrainFuck Interpreter by Water Horizontal Branch version %s\n",version);
    puts("Cell size:30000");
    puts("Cell code:ASCII(unsigned char in C)");
    puts("");
    puts("Brainfuck is a minimal computer language created by Urban Muller in 1993");
    puts("> pointer plus one");
    puts("< pointer minus one");
    puts("+ pointer to byte plus one");
    puts("- pointer to byte minus one");
    puts(". Output pointer pointing unit content (ASCII code)");
    puts(", input content to pointer pointing unit (ASCII code)");
    puts("[ jumps back to the next instruction of the corresponding ] instruction if the cell value the pointer points to is zero");
    puts("] jumps forward to the corresponding [ next instruction of instruction if the cell value that the pointer points to is not zero.");
}
int main(){
    cpr();
    while(1){
        puts("");
        switch(homp()){
        case 1:
            edit();
            break;
        case 2:
            anal();
            break;
        case 3:
            run();
            break;
        case 4:
            debug();
            break;
        case 5:
            inform();
            break;
        case 0:
            return 0;
        default:
            puts("This choice is incorrect.");
        }
    }
    return 0;
}
