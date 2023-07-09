#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc,char *argv[]){
    //First, check if program exists.
    if(argc!=4){
        puts("Error: you can't change number of arguments.");
        return 1;
    }else if(strcmp(argv[2],"-o")!=0){
        puts("Error: you can't change positions of arguments.");
        return 1;
    }
    int l1=strlen(argv[1]),l3=strlen(argv[3]);
    if(argv[1][l1-1]!='f'||argv[1][l1-2]!='b'||argv[1][l1-3]!='.'){
        puts("Error: you can't change positions of arguments.");
        return 1;
    }
    if(argv[3][l3-1]!='c'||argv[3][l3-2]!='.'){
        puts("Error: you can't change positions of arguments.");
        return 1;
    }
    if(access(argv[1],F_OK)){
        printf("Error: %s does not exist.",argv[1]);
        return 1;
    }else if(access(argv[1],R_OK)){
        printf("Error: can't read %s.",argv[1]);
        return 1;
    }
    //next, write preparation for c.
    FILE *bfck=fopen(argv[1],"r"),*c=fopen(argv[3],"w"),*bf=bfck;
    char ch,prog[1000010]={};
    int top=0,len=0;
    do{
        ch=fgetc(bfck);
        if(feof(bfck)) break;
        if(ch=='['||ch==']'){
            if(ch=='[') top++;
            else if(ch==']'){
                if(top==0){
                    puts("Error: program lose a \'[\'.");
                    return 1;
                }else top--;
            }
        }
        if(ch=='['||ch==']'||ch=='<'||ch=='>'||ch=='+'||ch=='-'||ch==','||ch=='.') prog[++len]=ch;
    }while(1);
    if(top!=0){
        puts("Error: program lose \']\'s.");
        return 1;
    }
    fprintf(c,"#include <stdio.h>\n#include <stdlib.h>\nchar getch(){char c;system(\"stty -icanon\");c=getchar();system(\"stty icanon\");return c;}int main(){unsigned char mem[30010]={};int pt=0;");
    for(int i=1;i<=len;i++){
        ch=prog[i];
        if(ch=='<') fprintf(c,"pt=(pt-1+30000)%30000;");
        if(ch=='>') fprintf(c,"pt=(pt+1)%30000;");
        if(ch=='+') fprintf(c,"mem[pt]++;");
        if(ch=='-') fprintf(c,"mem[pt]--;");
        if(ch=='.') fprintf(c,"putchar(mem[pt]);fflush(stdout);");
        if(ch==',') fprintf(c,"mem[pt]=getch();");
        if(ch=='[') fprintf(c,"while(mem[pt]!=0){");
        if(ch==']') fprintf(c,"}");
    }
    fprintf(c,"return 0;}");
    return 0;
}