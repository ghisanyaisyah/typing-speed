#include <ncurses.h>   
#include <unistd.h>    
#include <ctime>       
#include <cstdlib>     
#include <cstring>     
using namespace std;

const int BATAS_WAKTU = 25;   

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

    
    attron(COLOR_PAIR(3));
    mvprintw(2, 5, "=== GAME TYPING SPEED ===");
    attroff(COLOR_PAIR(3));
    mvprintw(4, 5, "Ketik huruf pada kata yang muncul secepat mungkin.");
    mvprintw(5, 5, "Waktu bermain: %d detik.", BATAS_WAKTU);
    mvprintw(7, 5, "Tekan tombol apa saja untuk mulai...");
    refresh();
    getch();   

    
    int  indeks      = rand() % jumlahKata;  
    int  posisi      = 0;                    
    int  benar       = 0;                    
    int  salah       = 0;                    
    int  kataSelesai = 0;                    
    int  sisa        = BATAS_WAKTU;          

    nodelay(stdscr, TRUE);        
    time_t mulai = time(0);       

    
    while (sisa > 0) {

        
        sisa = BATAS_WAKTU - (int)(time(0) - mulai);

        
        int ch = getch();
        if (ch != ERR) {
            if (ch == kata[indeks][posisi]) {
                
                benar++;
                posisi++;

                
                if (posisi == (int)strlen(kata[indeks])) {
                    kataSelesai++;
                    indeks = rand() % jumlahKata; 
                    posisi = 0;
                }
            } else if (ch >= 32 && ch <= 126) {
                
                salah++;
            }
        }

       
        erase();   

        attron(COLOR_PAIR(3));
        mvprintw(1, 5, "=== GAME TYPING SPEED ===");
        attroff(COLOR_PAIR(3));

        
        if (sisa < 0) sisa = 0;
        mvprintw(3, 5, "Waktu : %2d detik", sisa);
        mvprintw(4, 5, "[");
        for (int i = 0; i < BATAS_WAKTU; i++) {
            if (i < sisa) mvprintw(4, 6 + i, ">");
        }
        mvprintw(4, 6 + BATAS_WAKTU, "]");

        mvprintw(6, 5, "Skor kata : %d", kataSelesai);
        mvprintw(7, 5, "Salah     : %d", salah);

        
        mvprintw(10, 5, "Ketik: ");
        for (int i = 0; i < (int)strlen(kata[indeks]); i++) {
            if (i < posisi) {
                attron(COLOR_PAIR(1));
                mvprintw(10, 12 + i, "%c", kata[indeks][i]);
                attroff(COLOR_PAIR(1));
            } else {
                mvprintw(10, 12 + i, "%c", kata[indeks][i]);
            }
        }

        refresh();       
        usleep(10000);   
    }

    
    double menit    = BATAS_WAKTU / 60.0;
    double wpm      = (benar / 5.0) / menit;
    int    total    = benar + salah;
    double akurasi  = 0;
    if (total > 0) akurasi = (benar * 100.0) / total;

    
    nodelay(stdscr, FALSE);   
    flushinp();               
    clear();

    attron(COLOR_PAIR(2));
    mvprintw(2, 5, "=== WAKTU HABIS! ===");
    attroff(COLOR_PAIR(2));

    mvprintw(4, 5, "Kata selesai    : %d", kataSelesai);
    mvprintw(5, 5, "Ketikan benar   : %d", benar);
    mvprintw(6, 5, "Ketikan salah   : %d", salah);
    mvprintw(7, 5, "Kecepatan (WPM) : %.1f", wpm);
    mvprintw(8, 5, "Akurasi         : %.1f %%", akurasi);
    mvprintw(10, 5, "Tekan tombol apa saja untuk keluar...");
    refresh();
    getch();

    
    endwin();   
    return 0;
}