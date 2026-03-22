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

void kucuk_harfe_cevir(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = (char)tolower((unsigned char)str[i]);
}
