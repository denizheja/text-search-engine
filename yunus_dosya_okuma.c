void dosya_ara(const char *dosya_adi, const char *kelime, FILE *cikti)
{
    FILE *dosya;
    char  satir[MAX_SATIR_UZUNLUGU];
    int   satir_no = 0;
    int   toplam   = 0;
    int   eslesme;

    dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        yazdir(cikti, "\n[!] Dosya acilamadi: %s\n", dosya_adi);
        yazdir(cikti, "    --> Yanlis dosya adi veya yol girmis olabilirsiniz.\n");
        if (g_cikti_modu != 0) {
            printf("[!] Dosya acilamadi: %s\n", dosya_adi);
            printf("    --> Yanlis dosya adi veya yol girmis olabilirsiniz.\n");
        }
        return;
    }

    yazdir(cikti, "\nDosya: %s\n", dosya_adi);
    yazdir(cikti, "  Kelime gecen satirlar:\n");

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir_no++;
        eslesme = kelime_bul(satir, kelime);

        if (eslesme > 0) {
            toplam += eslesme;
            satir[strcspn(satir, "\n")] = '\0';
            yazdir(cikti, "    Satir %4d  (%dx)  --> %s\n", satir_no, eslesme, satir);
        }
    }

    fclose(dosya);

    if (toplam == 0)
        yazdir(cikti, "    (Bu dosyada kelime bulunamadi.)\n");

    yazdir(cikti, "  Toplam eslesme: %d\n", toplam);
}
