<div align=center>
    
# Laporan Resmi Praktikum Sistem Operasi Modul 3 Kelompok B27


|    NRP     |      Name      |
| :--------: | :------------: |
| 5025231226 | Arya Kusuma Dewa |
| 5025231114 | Muhammad Surya Yasar |
| 5025231254 | Ahmad Muqorrobin |

</div>

# Soal 1
Pada task ini, terdapat 3 file yang harus dibuat, yaitu `ayamgoreng.c` sebagai program utama, `Dockerfile` untuk docker, dan `docker-compose.yml`.

<br>

## Langkah Pengerjaan

<br>

Pertama, buat program utama `ayamgoreng.c` sesuai dengan ketentuan pada soal.

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
```

- Struct `Identity` digunakan untuk menyimpan nama, role, tipe, dan tahun rilis masing-masing hero yang diambil dari file `identitas.csv`

<br>

```c
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
```

- Struct `Attributes` digunakan untuk menyimpan stat masing-masing hero yang diambil dari file `atribut-hero.csv`

<br>

```c
typedef struct {
    char name[50];
    float skillpoints;
} HeroScore;
```

- Struct `HeroScore` digunakan untuk menyimpan skillpoint masing-masing hero

<br>

---

### b. Buat prototipe fungsi supaya kode terlihat lebih rapi


```c
void download_and_extract();
int isDirectoryExists(const char *path);
int read_identities(const char* filename, Identity identities[]);
int read_attributes(const char* filename, Attributes attributes[]);
HeroScore calculate_best_hero(const char* role, Identity identities[], int id_count, Attributes attributes[], int att_count);
```

<br>

---


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

### d. Deklarasi variabel, membaca data, lalu menentukan hero terbaik

<br>

Deklarasi variabel:
```c
Identity identities[MAX_HERO_COUNT];
Attributes attributes[MAX_HERO_COUNT];
HeroScore best_hero;
const char* roles[] = {"TANK", "ASSASSIN", "FIGHTER", "MM", "MAGE", "SUPPORT"};
int role_count = sizeof(roles) / sizeof(roles[0]);
```

- `identities[MAX_HERO_COUNT]` dan `attributes[MAX_HERO_COUNT]`: Array yang menyimpan data identitas dan atribut hero, dengan ukuran maksimum yang ditentukan oleh `MAX_HERO_COUNT`, yaitu 112.
- `best_hero`: Variabel untuk menyimpan hero terbaik yang akan ditentukan.
- `roles[]`: Array yang berisi daftar role hero yang akan dianalisis.
- `role_count`: Jumlah role yang ada dalam array `roles[]`.

<br>

Membaca data:
```c
int id_count = read_identities("Data Mobile Legend/identitas.csv", identities);
int att_count = read_attributes("Data Mobile Legend/Atribut/atribut-hero.csv", attributes);
```
- `id_count`: Jumlah identitas hero yang berhasil dibaca dari file CSV "Data Mobile Legend/identitas.csv".
- `att_count`: Jumlah atribut hero yang berhasil dibaca dari file CSV "Data Mobile Legend/Atribut/atribut-hero.csv".

<br>

```c
if (argc > 1) {
    best_hero = calculate_best_hero(argv[1], identities, id_count, attributes, att_count);
    printf("The best %s is %s with skillpoints %.2f\n", argv[1], best_hero.name, best_hero.skillpoints);
} else {
    for (int i = 0; i < role_count; i++) {
        best_hero = calculate_best_hero(roles[i], identities, id_count, attributes, att_count);
        printf("The best %s is %s with skillpoints %.2f\n", roles[i], best_hero.name, best_hero.skillpoints);
    }
}
```
- Jika terdapat argumen command-line (argv) lebih dari satu, maka program akan mencari hero terbaik untuk peran yang diberikan sebagai argumen.
- Jika tidak ada argumen, program akan mencari hero terbaik untuk setiap peran yang ada dalam array `roles[]`.
- Untuk setiap peran, fungsi `calculate_best_hero()` dipanggil dengan peran tersebut sebagai argumen. Hasilnya disimpan dalam `best_hero` dan dicetak di layar bersama dengan peran yang sedang dianalisis dan jumlah skill points yang dimiliki hero terbaik.

<br>

