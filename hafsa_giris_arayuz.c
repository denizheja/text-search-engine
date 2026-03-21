#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_SATIR_UZUNLUGU  1024
#define MAX_DOSYA_SAYISI    10
#define MAX_DOSYA_ADI       256
#define MAX_KELIME_UZUNLUGU 128

static int g_cikti_modu = 0;

void  kucuk_harfe_cevir(char *str);
int   kelime_bul(const char *satir, const char *kelime);
void  dosya_ara(const char *dosya_adi, const char *kelime, FILE *cikti);
void  baslik_yazdir(FILE *cikti);
void  ayirici_ciz(FILE *cikti);
void  yazdir(FILE *cikti, const char *fmt, ...);

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

    /* Deniz'in yazdir() ve cikti modu kodu buraya gelecek */

    return EXIT_SUCCESS;
}
