//Bagian awal 
#include <ncurses.h>   
#include <unistd.h>    
#include <ctime>       
#include <cstdlib>     
#include <cstring>  
#include <windows.h>   
using namespace std;


const int WAKTU_EASY   = 40;
const int WAKTU_MEDIUM = 30;
const int WAKTU_HARD   = 15;


const double TARGET_WPM = 30.0;

int main() {
    
    const char* kata[] = {
        "hidup", "ganyang", "fufufafa", "teddy", "buna",
        "wowo", "wong ditawari kok", "lo siento", "wilson", "febriono",
        "ajeng", "rawon", "seto", "josjis", "jokowi"
    };
    int jumlahKata = 15;

    srand(time(0));   

    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    
    start_color();
    init_pair(1, COLOR_GREEN,  COLOR_BLACK);  
    init_pair(2, COLOR_RED,    COLOR_BLACK);  
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);  

    
    int         batasWaktu = 0;     
    const char* namaLevel  = "";
    int         pilihan;

    while (batasWaktu == 0) {
        clear();
        attron(COLOR_PAIR(3));
        mvprintw(2, 5, "=== GAME TYPING SPEED ===");
        attroff(COLOR_PAIR(3));

        mvprintw(4, 5, "Ketik huruf pada kata yang muncul secepat mungkin.");
        mvprintw(6, 5, "Pilih level:");
        mvprintw(7, 5, "  [1] Easy   (%d detik)", WAKTU_EASY);
        mvprintw(8, 5, "  [2] Medium (%d detik)", WAKTU_MEDIUM);
        mvprintw(9, 5, "  [3] Hard   (%d detik)", WAKTU_HARD);
        mvprintw(11, 5, "Tekan 1, 2, atau 3: ");
        refresh();

        pilihan = getch();

        switch (pilihan) {
            case '1':
                batasWaktu = WAKTU_EASY;
                namaLevel  = "EASY";
                break;
            case '2':
                batasWaktu = WAKTU_MEDIUM;
                namaLevel  = "MEDIUM";
                break;
            case '3':
                batasWaktu = WAKTU_HARD;
                namaLevel  = "HARD";
                break;
            default:
                attron(COLOR_PAIR(2));
                mvprintw(13, 5, "Pilihan tidak valid! Coba lagi.");
                attroff(COLOR_PAIR(2));
                refresh();
                Sleep(800);   
                break;
        }
    }

    
    clear();
    attron(COLOR_PAIR(3));
    mvprintw(2, 5, "=== LEVEL %s ===", namaLevel);
    attroff(COLOR_PAIR(3));
    mvprintw(4, 5, "Waktu bermain: %d detik.", batasWaktu);
    mvprintw(6, 5, "Tekan tombol apa saja untuk mulai...");
    refresh();
    getch();

//Bagian Akhir
    mvprintw(13, 5, "Tekan ENTER untuk keluar...");
    refresh();

    Sleep(1000);   

    int tombol = getch();
    while (tombol != '\n' && tombol != KEY_ENTER && tombol != '\r') {
        tombol = getch();
    }

    endwin();
    return 0;
}