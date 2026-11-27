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
