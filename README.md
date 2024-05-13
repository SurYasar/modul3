# Laporan Resmi Praktikum Sistem Operasi Modul 3 Kelompok B27
## Anggota Kelompok:
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025231226 | Arya Kusuma Dewa |
| 5025231114 | Muhammad Surya Yasar |
| 5025231254 | Ahmad Muqorrobin |

<br>

# Soal 1
## Langkah Pengerjaan

<br>

### a. Membuat struktur data yang diperlukan yaitu Identity, Attributes, dan HeroScore

<br>

```c
typedef struct {
    char name[50];
    char role[50];
    char tipe[50];
    int tahun_rilis;
} Identity;

typedef struct {
    char name[50];
    int hp;
    float hp_regen;
    int physical_attack;
    int physical_defense;
    float attack_speed;
    int attack_speed_pc;
    int mana;
    int mana_regen;
    int magic_power;

} Attributes;

typedef struct {
    char name[50];
    float skillpoints;
} HeroScore;
```
<br>

- struct `Identity` digunakan untuk menyimpan nama, role, tipe, dan tahun rilis masing-masing hero yang diambil dari file `identitas.csv`
- 
