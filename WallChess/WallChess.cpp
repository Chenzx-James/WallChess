//
//  main.cpp
//  WallChess
//
//  Created by Chen Zixuan on 1/16/23.
//

/*
https://github.com/codewasp942/WallChess
Visual Studio 2019 on windows
*/


#include <iostream>
#include <cstdio>
#include <cmath>
//#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <CoreFoundation/CFUserNotification.h>
#include "position.h"
#include "ioex.h"
#include "dfs.h"
#include "qipan.h"
#define elif(tiaojian) else if(tiaojian)
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

using namespace std;

bool mp[3][maxxw][maxyw];            //某位置是否有墙
bool cmove[maxxw][maxyw];            //是否可达
char outm[2*maxxw][2 * maxyw];        //地图输出
const int xw = 7, yw = 7;            //棋盘宽度、高度
int piy = 2;                        //棋盘前空开列数
pos p1, p2;                            //棋子位置
//HANDLE hout;                        //标准输出句柄
FILE* fp;                            //C风格的文件输入输出
int s1, s2;                            //记录领地面积
int wins = 0;                        //记录赢家，3表示平局

inline void outto(pos ps, char(*outm)[218], char ch);
void drawqi(int x,int y);
void draw();
void printhelp();
bool judge();
int set_disp_mode(int fd,int option);

int main(){
    // 关闭缓存
    system("stty -icanon");
    // 关闭回显
    set_disp_mode(STDIN_FILENO,0);
//    system("stty -echo");
    if ((fp = fopen("~/Desktop/WallChess/WallChess/help.txt", "r")) == NULL) {
        CFUserNotificationDisplayNotice(0, kCFUserNotificationNoDefaultButtonFlag, NULL, NULL, NULL, CFSTR("Error in line 55"), CFSTR("无法打开帮助文件，请确认help.txt在程序目录下"), NULL);
        
//        MessageBox(HWND_DESKTOP, TEXT("无法打开帮助文件，请确认help.txt在程序目录下"),TEXT("运行错误"), MB_OK | MB_ICONERROR);
//        不退出
//        return 5201314;
    }
/* if (!hinit(hout)) {
        messagebox("无法获取标准输出句柄");
//        MessageBox(HWND_DESKTOP, TEXT("无法获取标准输出句柄"),TEXT("运行错误"),MB_OK | MB_ICONERROR);
        return 5201314;
    }
 */

    while (1) {
        memset(mp, 0, sizeof(mp));
        for (int j = 1;j <= yw;j++) {
            mp[0][1][j] = mp[0][xw + 1][j] = 1;
        }
        for (int i = 1;i <= xw;i++) {
            mp[1][i][1] = mp[1][i][yw + 1] = 1;
        }
        p1.x = p1.y = 1;
        p2.x = xw;p2.y = yw;
        int akey;
        while (1) {
            scan(0, cmove, mp, xw, yw, p1, p2, 3);
            draw();
            akey = getk();
            while (akey != 32) {
                if (0 <= akey && akey <= 3) {
                    outto(p1, outm, ' ');
                    pos tmp = p1[akey];
                    if (!(tmp.x<1 || tmp.x>xw || tmp.y<1 || tmp.y>yw || tmp == p2 || !cmove[tmp.x][tmp.y] || mp[akey % 2][max(tmp.x, p1.x)][max(tmp.y, p1.y)])) {
                        p1 = tmp;
                    }
                    draw();
//                    Sleep(100);
                    usleep(100000);
                }elif(akey == 'i') {
                    printhelp();
                }
                akey = getk();
            }
            panduan_p1:
            do { akey = getk(); } while (0 > akey || akey > 3);
            if (akey == 0) {
                if (mp[0][p1.x][p1.y])goto panduan_p1;
                mp[0][p1.x][p1.y] = 1;
            }elif(akey == 1) {
                if (mp[1][p1.x][p1.y])goto panduan_p1;
                mp[1][p1.x][p1.y] = 1;
            }elif(akey == 2) {
                if (mp[0][p1.x + 1][p1.y])goto panduan_p1;
                mp[0][p1.x + 1][p1.y] = 1;
            }elif(akey == 3) {
                if (mp[1][p1.x][p1.y + 1])goto panduan_p1;
                mp[1][p1.x][p1.y + 1] = 1;
            }
            scan(0, cmove, mp, xw, yw, p2, p1, 3);
            draw();

            if (!judge()) {
                break;
            }

            scan(0, cmove, mp, xw, yw, p2, p1, 3);
            draw();
            akey = getk();
            while (akey != 32) {
                if (0 <= akey && akey <= 3) {
                    outto(p1, outm, ' ');
                    pos tmp = p2[akey];
                    if (!(tmp.x<1 || tmp.x>xw || tmp.y<1 || tmp.y>yw || tmp == p1 || !cmove[tmp.x][tmp.y] || mp[akey % 2][max(tmp.x, p2.x)][max(tmp.y, p2.y)])) {
                        p2 = tmp;
                    }
                    draw();
//                    Sleep(100);
                    usleep(100000);
                }elif(akey == 'i') {
                    printhelp();
                }
                akey = getk();
            }
            panduan_p2:
            do { akey = getk(); } while (0 > akey || akey > 3);
            if (akey == 0) {
                if (mp[0][p2.x][p2.y])goto panduan_p2;
                mp[0][p2.x][p2.y] = 1;
            }elif(akey == 1) {
                if (mp[1][p2.x][p2.y])goto panduan_p2;
                mp[1][p2.x][p2.y] = 1;
            }elif(akey == 2) {
                if (mp[0][p2.x + 1][p2.y])goto panduan_p2;
                mp[0][p2.x + 1][p2.y] = 1;
            }elif(akey == 3) {
                if (mp[1][p2.x][p2.y + 1])goto panduan_p2;
                mp[1][p2.x][p2.y + 1] = 1;
            }
            scan(0, cmove, mp, xw, yw, p2, p1, 3);
            draw();

            if (!judge()) {
                break;
            }
        }
//        system("cls");
        system("clear");
        if (s1 > s2) {
            puts(">>> >>>  Red wins !!! <<< <<<");
        }elif(s1 < s2) {
            puts(">>> >>> Blue wins !!! <<< <<<");
        }elif(s1 == s2) {
            puts(">>> >>> -+-+ Tie +-+- <<< <<<");
        }
        printf("\n\n");
        printf("          %2d ",s1);
        outch(':', COL_RED, COL_BLACK);
        printf(" %2d\n\n\n\n",s2);
        system("pause");
    }
    // 开启缓存
    system("stty icanon");
    // 开启回显
    set_disp_mode(STDIN_FILENO,1);
//    system("stty echo");
//    CloseHandle(hout);
    return 0;
}

inline void outto(pos ps, char(*outm)[218], char ch) {
    outm[calx(ps.x) + 1][caly(ps.y) + 1] = ch;
    outm[calx(ps.x) + 1][caly(ps.y) + 2] = ch;
}

void drawqi() {
    for (int i = 1;i <= xw + 1;i++) {
        for (int j = 1;j <= yw + 1;j++) {
            outm[calx(i)][caly(j)] = '#';
        }
    }
    for (int i = 1;i <= xw; i++){
        for (int j = 1;j <= yw; j++) {
            if (cmove[i][j]) {
                outto(pos(i, j), outm, '-');
            }
        }
    }
    for (int i = 1;i <= xw + 1; i++) {
        for (int j = 1;j <= yw + 1; j++) {
            if (mp[0][i][j]) {
                outm[calx(i)][caly(j) + 1] = '=';
                outm[calx(i)][caly(j) + 2] = '=';
            }
            if (mp[1][i][j]) {
                outm[calx(i) + 1][caly(j)] = '=';
            }
        }
    }
    outto(p1, outm, '1');
    outto(p2, outm, '2');
}

void draw() {
//    system("cls");
    system("clear");
    puts(">->-> The WallChess <-<-<");
    puts("$ press i to find help...");
    for (int i = 1;i <= calx(xw + 1);i++) {
        for (int j = 1;j <= caly(yw + 1);j++) {
            outm[i][j] = ' ';
        }
    }
    drawqi();
    for (int i = 1;i <= calx(xw+1);i++){
        for (int j = 1;j <= piy;j++) {
            printf(" ");
        }
        for (int j = 1;j <= caly(yw+1);j++) {
            if (outm[i][j] == ' ')    putchar(' ');
            elif(outm[i][j] == '1')    outch(' ', COL_RED, COL_RED);
            elif(outm[i][j] == '2')    outch(' ', COL_BLUE, COL_BLUE);
            elif(outm[i][j] == '#')    outch('#', COL_WHITE, COL_PURPLE);
            elif(outm[i][j] == '-')    outch('.', COL_CYAN, COL_BLACK);
            elif(outm[i][j] == '=')    outch('+', COL_PURPLE, COL_PURPLE);
            else                    putchar(' ');
        }
        printf("\n");
    }
}

void printhelp() {
//    system("cls");
    if ((fp = fopen("~/Desktop/WallChess/WallChess/help.txt", "r")) == NULL) {
        CFUserNotificationDisplayNotice(0, kCFUserNotificationNoDefaultButtonFlag, NULL, NULL, NULL, CFSTR("Error in line 248"), CFSTR("无法打开帮助文件，请确认help.txt在程序目录下"), NULL);
//        exit(5201314);
        return;
    }
    system("clear");
    char buffer[509];
    while (fgets(buffer,509,fp) != NULL) {
        puts(buffer);
    }
    while (getchar() != 'i') {};
    draw();
}

bool judge() {
    s1 = scan(1, cmove, mp, xw, yw, p1, p2, 0);
    s2 = scan(1, cmove, mp, xw, yw, p2, p1, 0);
    return cmove[p1.x][p1.y];
}

int set_disp_mode(int fd, int option)
{
   int err;
   struct termios term;
   if(tcgetattr(fd, &term) == -1){
       perror("Cannot get the attribution of the terminal.");
       return 1;
   }
   if(option)
       term.c_lflag |= ECHOFLAGS;
   else
       term.c_lflag &= ~ECHOFLAGS;
   err = tcsetattr(fd, TCSAFLUSH, &term);
   if(err == -1 && err == EINTR){
        perror("Cannot set the attribution of the terminal.");
        return 1;
   }
   return 0;
}
