void yazdir(FILE *cikti, const char *fmt, ...)
{
    va_list args;

    if (g_cikti_modu == 0) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    } else {
        if (cikti != NULL) {
            va_start(args, fmt);
            vfprintf(cikti, fmt, args);
            va_end(args);
        }
    }
}

/* main() icinde cikti modu secimi ve dosya acma kismi */

    printf("\nSonuclari nereye yazdirmak istersiniz?\n");
    printf("  1 - Yeni dosya (masaustu -> sonuc.txt)\n");
    printf("  2 - Mevcut dosyalarin yanina (her dosya icin ayri _sonuc.txt)\n");
    printf("  0 - Sadece terminale yaz\n");
    printf("Secim: ");
    if (scanf("%d", &cikti_modu) != 1) {
        fprintf(stderr, "Gecersiz secim.\n");
        return EXIT_FAILURE;
    }
    getchar();

    g_cikti_modu = cikti_modu;

    if (cikti_modu == 1) {
#ifdef _WIN32
        char yol[MAX_DOSYA_ADI];
        const char *masaustu = getenv("USERPROFILE");
        if (masaustu)
            snprintf(yol, sizeof(yol), "%s\\Desktop\\sonuc.txt", masaustu);
        else
            snprintf(yol, sizeof(yol), "sonuc.txt");
#else
        char yol[MAX_DOSYA_ADI];
        const char *ev = getenv("HOME");
        if (ev)
            snprintf(yol, sizeof(yol), "%s/Desktop/sonuc.txt", ev);
        else
            snprintf(yol, sizeof(yol), "sonuc.txt");
#endif
        cikti_dosya = fopen(yol, "w");
        if (!cikti_dosya) {
            printf("[!] Cikti dosyasi acilamadi, terminale yazilacak.\n");
            g_cikti_modu = 0;
        } else {
            printf("Sonuclar %s dosyasina kaydedilecek.\n", yol);
        }
    }

    baslik_yazdir(cikti_dosya);
    ayirici_ciz(cikti_dosya);
    yazdir(cikti_dosya, "  ARAMA SONUCLARI  |  Kelime: \"%s\"\n", kelime);
    ayirici_ciz(cikti_dosya);

    for (int i = 0; i < dosya_sayisi; i++) {
        FILE *yan_dosya = NULL;

        if (cikti_modu == 2) {
            char yan_yol[MAX_DOSYA_ADI];
            snprintf(yan_yol, sizeof(yan_yol), "%s_sonuc.txt", dosyalar[i]);
            yan_dosya = fopen(yan_yol, "w");
            if (!yan_dosya)
                printf("[!] %s icin cikti dosyasi acilamadi.\n", dosyalar[i]);
            else {
                baslik_yazdir(yan_dosya);
                ayirici_ciz(yan_dosya);
                yazdir(yan_dosya, "  ARAMA SONUCLARI  |  Kelime: \"%s\"\n", kelime);
                ayirici_ciz(yan_dosya);
            }
        }

        dosya_ara(dosyalar[i], kelime,
                  (cikti_modu == 1) ? cikti_dosya :
                  (cikti_modu == 2) ? yan_dosya   : NULL);

        if (yan_dosya) {
            ayirici_ciz(yan_dosya);
            fprintf(yan_dosya, "Program basariyla tamamlandi.\n");
            fclose(yan_dosya);
        }
    }

    ayirici_ciz(cikti_dosya);
    yazdir(cikti_dosya, "Program basariyla tamamlandi.\n");

    if (cikti_dosya) fclose(cikti_dosya);

    if (cikti_modu != 0)
        printf("Arama tamamlandi.\n");
