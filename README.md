# 📄 Text Search Engine — Metin Arama Sistemi

> BIL1203 Mühendislikte Proje Yönetimi | Proje #2  
> İzmir Bakırçay Üniversitesi — Bilgisayar Mühendisliği Bölümü

---

## 📌 Proje Açıklaması

Bu proje, kullanıcıdan alınan bir kelimeyi bir veya birden fazla metin dosyasında arayan ve kelimenin kaç kez geçtiğini hesaplayan bir yazılım uygulamasıdır. Program **C dili** kullanılarak geliştirilmiştir.

Uygulama:
- Kullanıcıdan aramak istediği kelimeyi alır
- Seçilen dosya/dosyalar içinde bu kelimenin frekansını hesaplar
- Kelimenin geçtiği satırları ve toplam tekrar sayısını raporlar

---

## 👥 Grup Üyeleri

| İsim | Sorumluluk |
|---|---|
| Hafsa | Giriş & Kullanıcı Arayüzü |
| Deniz | Çıktı Sistemi |
| Yunus | Dosya Okuma & Raporlama |
| Selim | Arama Algoritması |

---

## ✨ Özellikler

- 🔍 Büyük/küçük harf duyarsız arama
- 📂 Birden fazla dosyada aynı anda arama (max 10 dosya)
- 📍 Kelimenin geçtiği satır numaralarını listeleme
- 🔢 Aynı satırda birden fazla geçişi sayma
- ⚠️ Yanlış dosya adı için açıklayıcı hata mesajı
- 💾 Sonuçları 3 farklı şekilde kaydetme:
  - `0` — Sadece terminale yaz
  - `1` — Masaüstünde `sonuc.txt` dosyasına kaydet
  - `2` — Her dosyanın yanına ayrı `_sonuc.txt` oluştur
- 🇹🇷 Windows'ta Türkçe karakter desteği

---

## 🗂️ İş Paketi Dağılımı

| İş Paketi | Açıklama | Sorumlu |
|---|---|---|
| 1 | Kullanıcıdan aranacak kelimeyi alma | Hafsa |
| 2 | Belirtilen metin dosyasını açma | Hafsa |
| 3 | Dosyayı satır satır okuma | Yunus |
| 4 | Aranan kelimenin toplam tekrar sayısını hesaplama | Yunus |
| 5 | Kelimenin geçtiği satır numaralarını listeleme | Selim |
| 6 | Sonuçları kullanıcıya raporlama | Selim |
| 7 | Çıktı modu seçimi ve dosyaya yazma | Deniz |
| 8 | Windows/Linux uyumluluğu ve karakter desteği | Deniz |

---

## ⚙️ Kurulum ve Çalıştırma

### Gereksinimler
- GCC derleyici
- Windows / Linux / Mac

### Derleme

```bash
gcc -Wall -std=c11 -o text_search_engine text_search_engine.c
```

### Çalıştırma

```bash
./text_search_engine        # Linux / Mac
text_search_engine.exe      # Windows
```

---

## 💻 Kullanım Örneği

```
============================================================
  Text Search Engine - Metin Arama Sistemi
============================================================

Aramak istediginiz kelimeyi girin: merhaba

Kac dosya aramak istiyorsunuz? (1-10): 1
Dosya 1 adini girin: deneme.txt

Sonuclari nereye yazdirmak istersiniz?
  1 - Yeni dosya (masaustu -> sonuc.txt)
  2 - Mevcut dosyalarin yanina (her dosya icin ayri _sonuc.txt)
  0 - Sadece terminale yaz
Secim: 0

============================================================
  ARAMA SONUCLARI  |  Kelime: "merhaba"
============================================================

Dosya: deneme.txt
  Kelime gecen satirlar:
    Satir    1  (1x)  --> merhaba dunya
    Satir    3  (2x)  --> merhaba merhaba tekrar
  Toplam eslesme: 3
============================================================
Program basariyla tamamlandi.
```

---

## 📁 Dosya Yapısı

```
text-search-engine/
│
├── text_search_engine.c      ← Ana kaynak kod
├── hafsa_giris_arayuz.c      ← Hafsa'nın kısmı
├── deniz_cikti_sistemi.c     ← Deniz'in kısmı
├── yunus_dosya_okuma.c       ← Yunus'un kısmı
├── selim_arama_algoritmasi.c ← Selim'in kısmı
└── README.md                 ← Bu dosya
```

---
