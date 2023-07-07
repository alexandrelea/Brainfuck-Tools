/*
main.c - the main program of bfi.
Copyright (C) 2023 Water Horizontal Branch

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
void cpr(){
    puts("bfi (BrainFuck Interpreter) v0.3 Copyright (C) 2023 Water Horizontal Branch");
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
int homp(){
    int choice;
    puts("What do you want to do:");
    puts("1 - Edit program");
    puts("2 - Run program");
    puts("3 - Debug program");
    puts("4 - Read informations about this program.");
    puts("0 - Exit");
    printf("Please select(0-3):");
    scanf("%d",&choice);
    return choice;
}
char prog[100010]={};
int len=0;
void edit(){
    char ch,msg[100110]="Your program:";
    puts("You can copy and edit your program. The end sign is '!'.");
    if(strlen(prog)!=0) puts(strcat(msg,prog));
    len=0;
    memset(prog,0,sizeof prog);
    while(scanf("%c",&ch)!=0&&ch!='!')
        if(ch=='['||ch==']'||ch=='<'||ch=='>'||ch=='+'||ch=='-'||ch=='.'||ch==',') prog[len++]=ch;
    return;
}
char getche(){
    char c;
    system("stty -echo;stty -icanon");
    c=getchar();
    system("stty echo;stty icanon");
    return c; 
}
void run(){
    puts("Analyzing your program...");
    len=strlen(prog);
    int khop[100010]={},top,stck[100010]={},pt=0,prpt=0;
    char mem[30010]={};
    for(int i=0;i<len;i++){
        if(prog[i]=='[') stck[++top]=i;
        if(prog[i]==']'){
            if(top==0){
                for(int j=max(0,i-10);j<=min(len,i+10);j++) printf("%c",prog[j]);
                printf("\n");
                for(int j=max(0,i-10);j<i;j++) printf(" ");
                printf("X\n");
                printf("Extra parenthesis at %d.\n",i);
                return;
            }else khop[stck[top]]=i,khop[i]=stck[top],top--;
        }
    }
    if(top!=0){
        printf("Missing some parentheses at %d.\n",len);
        return;
    }
    getchar();
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
            mem[pt]=getche();
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
    puts("This can't be used in this program(version 0.3).");
    return;
}
void inform(){
    puts("bfi - BrainFuck Interpreter by Water Horizontal Branch version 0.3");
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
    puts("");
}
int main(){
    cpr();
    while(1){
        switch(homp()){
        case 1:
            edit();
            break;
        case 2:
            run();
            break;
        case 3:
            debug();
            break;
        case 4:
            inform();
            break;
        case 0:
            return 0;
        default:
            puts("Sorry, this choice is incorrect.");
        }
    }
    return 0;
}
