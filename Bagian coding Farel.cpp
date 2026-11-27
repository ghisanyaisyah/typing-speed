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
