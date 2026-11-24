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

   
    int indeks      = rand() % jumlahKata;  
    int posisi      = 0;                   
    int benar       = 0;                    
    int salah       = 0;                   
    int kataSelesai = 0;                    
    int sisa        = batasWaktu;           

    nodelay(stdscr, TRUE);       
    time_t mulai = time(0);     

   
    while (sisa > 0) {

       
        sisa = batasWaktu - (int)(time(0) - mulai);

       
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
        mvprintw(1, 5, "=== LEVEL %s ===", namaLevel);
        attroff(COLOR_PAIR(3));

        if (sisa < 0) sisa = 0;
        mvprintw(3, 5, "Waktu : %2d detik", sisa);
        mvprintw(4, 5, "[");
        for (int i = 0; i < batasWaktu; i++) {
            if (i < sisa) mvprintw(4, 6 + i, ">");
        }
        mvprintw(4, 6 + batasWaktu, "]");

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
        Sleep(10);  
    }

    
    double menit   = batasWaktu / 60.0;
    double wpm     = (benar / 5.0) / menit;     
    int    total   = benar + salah;
    double akurasi = 0;
    if (total > 0) akurasi = (benar * 100.0) / total;

    
    double nilai = (wpm / TARGET_WPM) * akurasi;
    if (nilai > 100) nilai = 100;

   
    const char* predikat;
    int         warna;

    if (nilai >= 90) {
        predikat = "A - JosJis";
        warna = 1;
    } else if (nilai >= 75) {
        predikat = "B - Uhuy";
        warna = 3;
    } else if (nilai >= 60) {
        predikat = "C - ok";
        warna = 3;
    } else {
        predikat = "D - hell nah";
        warna = 2;
    }

   
    nodelay(stdscr, FALSE);  
    flushinp();               
    clear();

    attron(COLOR_PAIR(2));
    mvprintw(2, 5, "=== WAKTU HABIS! (Level %s) ===", namaLevel);
    attroff(COLOR_PAIR(2));

    mvprintw(4, 5, "Kata selesai    : %d", kataSelesai);
    mvprintw(5, 5, "Ketikan benar   : %d", benar);
    mvprintw(6, 5, "Ketikan salah   : %d", salah);
    mvprintw(7, 5, "Kecepatan (WPM) : %.1f", wpm);
    mvprintw(8, 5, "Akurasi         : %.1f %%", akurasi);
    mvprintw(10, 5, "Nilai           : %.1f", nilai);

    mvprintw(11, 5, "Predikat        : ");
    attron(COLOR_PAIR(warna));
    mvprintw(11, 23, "%s", predikat);
    attroff(COLOR_PAIR(warna));

    mvprintw(13, 5, "Tekan tombol apa saja untuk keluar...");
    refresh();
    getch();

    endwin();
    return 0;
}