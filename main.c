/*
 * Text Search Engine - Metin Arama Sistemi
 * =========================================
 * Birlestirilmis kaynak dosya:
 *   - hafsa_giris_arayuz.c  (Giris arayuzu ve main)
 *   - deniz_cikti_sistemi.c (Cikti yonetimi)
 *   - yunus_dosya_okuma.c   (Dosya okuma)
 *   - selim_arama_algoritmasi.c (Arama algoritmasi)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* -------------------------------------------------------
 * Sabitler
 * ------------------------------------------------------- */
#define MAX_SATIR_UZUNLUGU  1024
#define MAX_DOSYA_SAYISI    10
#define MAX_DOSYA_ADI       256
#define MAX_KELIME_UZUNLUGU 128

/* -------------------------------------------------------
 * Global degisken
 * ------------------------------------------------------- */
static int g_cikti_modu = 0;

/* -------------------------------------------------------
 * Fonksiyon bildirimleri
 * ------------------------------------------------------- */
void  kucuk_harfe_cevir(char *str);
int   kelime_bul(const char *satir, const char *kelime);
void  dosya_ara(const char *dosya_adi, const char *kelime, FILE *cikti);
void  baslik_yazdir(FILE *cikti);
void  ayirici_ciz(FILE *cikti);
void  yazdir(FILE *cikti, const char *fmt, ...);

/* -------------------------------------------------------
 * selim_arama_algoritmasi.c - Arama Algoritmasi
 * ------------------------------------------------------- */
void kucuk_harfe_cevir(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = (char)tolower((unsigned char)str[i]);
}

int kelime_bul(const char *satir, const char *kelime)
{
    char satir_kucuk[MAX_SATIR_UZUNLUGU];
    char kelime_kucuk[MAX_KELIME_UZUNLUGU];

    strncpy(satir_kucuk,  satir,  MAX_SATIR_UZUNLUGU  - 1);
    strncpy(kelime_kucuk, kelime, MAX_KELIME_UZUNLUGU - 1);
    satir_kucuk [MAX_SATIR_UZUNLUGU  - 1] = '\0';
    kelime_kucuk[MAX_KELIME_UZUNLUGU - 1] = '\0';

    kucuk_harfe_cevir(satir_kucuk);
    kucuk_harfe_cevir(kelime_kucuk);

    int   sayi        = 0;
    int   kelime_uzun = (int)strlen(kelime_kucuk);
    char *p           = satir_kucuk;

    while ((p = strstr(p, kelime_kucuk)) != NULL) {
        int onceki_ok  = (p == satir_kucuk) || !isalnum((unsigned char)*(p - 1));
        int sonraki_ok = !isalnum((unsigned char)*(p + kelime_uzun));
        if (onceki_ok && sonraki_ok) sayi++;
        p++;
    }

    return sayi;
}

/* -------------------------------------------------------
 * yunus_dosya_okuma.c - Dosya Okuma
 * ------------------------------------------------------- */
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

/* -------------------------------------------------------
 * deniz_cikti_sistemi.c - Cikti Sistemi
 * ------------------------------------------------------- */
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

/* -------------------------------------------------------
 * hafsa_giris_arayuz.c - Giris Arayuzu & Yardimci
 * ------------------------------------------------------- */
void baslik_yazdir(FILE *cikti)
{
    ayirici_ciz(cikti);
    yazdir(cikti, "  Text Search Engine - Metin Arama Sistemi\n");
    ayirici_ciz(cikti);
    yazdir(cikti, "\n");
}

void ayirici_ciz(FILE *cikti)
{
    yazdir(cikti, "============================================================\n");
}

/* -------------------------------------------------------
 * main
 * ------------------------------------------------------- */
int main(void)
{
    char  kelime[MAX_KELIME_UZUNLUGU];
    int   dosya_sayisi = 0;
    char  dosyalar[MAX_DOSYA_SAYISI][MAX_DOSYA_ADI];
    int   cikti_modu = 0;
    FILE *cikti_dosya = NULL;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    printf("============================================================\n");
    printf("  Text Search Engine - Metin Arama Sistemi\n");
    printf("============================================================\n\n");

    printf("Aramak istediginiz kelimeyi girin: ");
    if (fgets(kelime, sizeof(kelime), stdin) == NULL) {
        fprintf(stderr, "Kelime okunamadi!\n");
        return EXIT_FAILURE;
    }
    kelime[strcspn(kelime, "\n")] = '\0';

    if (strlen(kelime) == 0) {
        fprintf(stderr, "Hata: Bos kelime girilemez.\n");
        return EXIT_FAILURE;
    }

    printf("\nKac dosya aramak istiyorsunuz? (1-%d): ", MAX_DOSYA_SAYISI);
    if (scanf("%d", &dosya_sayisi) != 1 ||
        dosya_sayisi < 1 || dosya_sayisi > MAX_DOSYA_SAYISI) {
        fprintf(stderr, "Gecersiz dosya sayisi.\n");
        return EXIT_FAILURE;
    }
    getchar();

    for (int i = 0; i < dosya_sayisi; i++) {
        printf("Dosya %d adini girin: ", i + 1);
        if (fgets(dosyalar[i], MAX_DOSYA_ADI, stdin) == NULL) {
            fprintf(stderr, "Dosya adi okunamadi!\n");
            return EXIT_FAILURE;
        }
        dosyalar[i][strcspn(dosyalar[i], "\r\n")] = '\0';
    }

    /* Cikti modu secimi (deniz_cikti_sistemi.c) */
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
        char yol[MAX_DOSYA_ADI];
#ifdef _WIN32
        const char *masaustu = getenv("USERPROFILE");
        if (masaustu)
            snprintf(yol, sizeof(yol), "%s\\Desktop\\sonuc.txt", masaustu);
        else
            snprintf(yol, sizeof(yol), "sonuc.txt");
#else
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

    return EXIT_SUCCESS;
}
