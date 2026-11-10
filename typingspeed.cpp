#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

const int LEBAR = 50;
const int TINGGI = 15;
const char* FILE_HIGHSCORE = "highscore.txt";

struct Kata {
    std::string teks;
    int x, y;
};

std::vector<std::string> bank = {
    "LOOP", "ARRAY", "FUNGSI", "CLASS", "MUTEX", "COUT", "CIN",
    "STRING", "VECTOR", "POINTER", "STRUCT", "TEMPLATE", "THREAD", "COMPILE"
};

std::vector<Kata> kata;
std::string input;
int skor = 0, nyawa = 3, level = 1, highScore = 0, tick = 0;
bool selesai = false;

int BacaHighScore() {
    std::ifstream f(FILE_HIGHSCORE);
    int h = 0;
    if (f >> h) return h;
    return 0;
}

void SimpanHighScore(int h) {
    std::ofstream f(FILE_HIGHSCORE);
    f << h;
}

void Spawn() {
    Kata k;
    k.teks = bank[rand() % bank.size()];
    k.x = rand() % (LEBAR - (int)k.teks.length() + 1);
    k.y = 0;
    kata.push_back(k);
}

void Setup() {
    srand(time(NULL));
    highScore = BacaHighScore();

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    set_escdelay(25); // supaya ESC langsung terbaca
    curs_set(0);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // huruf yang cocok
    init_pair(2, COLOR_RED, COLOR_BLACK);    // nyawa
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // info

    Spawn();
}

void Draw() {
    erase();

    std::string garis(LEBAR, '-');
    mvprintw(0, 0, "+%s+", garis.c_str());
    for (int y = 0; y < TINGGI; y++) {
        mvaddch(y + 1, 0, '|');
        mvaddch(y + 1, LEBAR + 1, '|');
    }
    mvprintw(TINGGI + 1, 0, "+%s+", garis.c_str());

    // Gambar semua kata, huruf yang sudah cocok diberi warna
    for (const Kata& k : kata) {
        bool cocok = !input.empty() && k.teks.compare(0, input.size(), input) == 0;
        for (size_t i = 0; i < k.teks.size(); i++) {
            if (cocok && i < input.size()) attron(COLOR_PAIR(1) | A_BOLD);
            mvaddch(k.y + 1, k.x + 1 + i, k.teks[i]);
            attroff(COLOR_PAIR(1) | A_BOLD);
        }
    }

    int baris = TINGGI + 3;
    attron(COLOR_PAIR(3));
    mvprintw(baris, 0, "SKOR: %d   LEVEL: %d   HIGH SCORE: %d", skor, level, highScore);
    attroff(COLOR_PAIR(3));

    mvprintw(baris + 1, 0, "NYAWA: ");
    attron(COLOR_PAIR(2));
    for (int i = 0; i < nyawa; i++) printw("<3 ");
    attroff(COLOR_PAIR(2));

    mvprintw(baris + 2, 0, "Ketik: [ %s ]", input.c_str());
    mvprintw(baris + 3, 0, "ENTER = kirim, ESC = keluar");

    refresh();
}

void Input() {
    int ch;
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case 27:
                selesai = true;
                break;
            case 10:
            case KEY_ENTER: {
                auto it = std::find_if(kata.begin(), kata.end(),
                    [](const Kata& k) { return k.teks == input; });
                if (it != kata.end()) {
                    skor += 10;
                    kata.erase(it);
                }
                input.clear();
                break;
            }
            case 127:
            case 8:
            case KEY_BACKSPACE:
                if (!input.empty()) input.pop_back();
                break;
            default:
                if (isalpha(ch) && input.size() < 15)
                    input += toupper(ch);
        }
    }
}

void Logic() {
    tick++;
    level = skor / 50 + 1;

    int kecepatan = std::max(3, 12 - level);     // makin kecil makin cepat
    int jedaSpawn = std::max(30, 90 - level * 8); // jeda antar kata baru

    if (tick % kecepatan == 0) {
        for (Kata& k : kata) k.y++;
    }

    if (tick % jedaSpawn == 0 && kata.size() < 5) Spawn();
    if (kata.empty()) Spawn();

    // Kata yang menyentuh dasar mengurangi nyawa
    for (size_t i = 0; i < kata.size();) {
        if (kata[i].y >= TINGGI) {
            kata.erase(kata.begin() + i);
            nyawa--;
        } else {
            i++;
        }
    }

    if (nyawa <= 0) selesai = true;
}

int main() {
    Setup();

    while (!selesai) {
        Draw();
        Input();
        Logic();
        usleep(50000);
    }

    if (skor > highScore) {
        highScore = skor;
        SimpanHighScore(highScore);
    }

    flushinp();
    erase();
    mvprintw(TINGGI / 2, (LEBAR / 2) - 5, "GAME OVER!");
    mvprintw(TINGGI / 2 + 1, (LEBAR / 2) - 6, "Total Skor: %d", skor);
    mvprintw(TINGGI / 2 + 2, (LEBAR / 2) - 8, "High Score: %d", highScore);
    mvprintw(TINGGI / 2 + 4, (LEBAR / 2) - 12, "Tekan tombol apa saja...");
    nodelay(stdscr, FALSE);
    getch();

    endwin();
    return 0;
}