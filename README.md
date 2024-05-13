<div align=center>
    
# Laporan Resmi Praktikum Sistem Operasi Modul 3 Kelompok B27

## Anggota Kelompok:

|    NRP     |      Name      |
| :--------: | :------------: |
| 5025231226 | Arya Kusuma Dewa |
| 5025231114 | Muhammad Surya Yasar |
| 5025231254 | Ahmad Muqorrobin |

</div>

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

- Struct `Identity` digunakan untuk menyimpan nama, role, tipe, dan tahun rilis masing-masing hero yang diambil dari file `identitas.csv`
<br>
- Struct `Attributes` digunakan untuk menyimpan stat masing-masing hero yang diambil dari file `atribut-hero.csv`
<br>
- Struct `HeroScore` digunakan untuk menyimpan skillpoint masing-masing hero
<br>

---
<br>

### b. Buat prototipe fungsi supaya kode terlihat lebih rapi

<br>

```c
void download_and_extract();
int isDirectoryExists(const char *path);
int read_identities(const char* filename, Identity identities[]);
int read_attributes(const char* filename, Attributes attributes[]);
HeroScore calculate_best_hero(const char* role, Identity identities[], int id_count, Attributes attributes[], int att_count);
```

<br>

---

<br>

### c. Panggil fungsi `download_and_extract()` apabila directory "Data Mobile Legend" belum ada, jikas sudah ada lanjutkan program

<br>

```c
    if(isDirectoryExists("Data Mobile Legend")){
    	printf("Directory already exists, continue executing the program\n");
    }
    else{
    	download_and_extract();
    }
```
<br>

- Untuk mengecek apakah folder "Data Mobile Legend" sudah ada di directory saat ini, gunakan fungsi `isDirectoryExists` yang berisi:

```c
int isDirectoryExists(const char *path) {
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}
```
<br>

- Jika sudah ada, maka panggil fungsi `download_and_extract` yang berisi:

```c
void download_and_extract() {
    system("kaggle datasets download -d irwansyah10010/mobilelegend -p .");
    system("unzip -o mobilelegend.zip");
}
```
<br>

### d. 
