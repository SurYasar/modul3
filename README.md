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


### c. Panggil fungsi `download_and_extract()` apabila directory "Data Mobile Legend" belum ada, jika sudah ada lanjutkan program

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

Menentukan hero terbaik:
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

### e. Buat fungsi secara lengkap di bawah main

<br>

1. `void download_and_extract()`
Fungsi download_and_extract() adalah sebuah fungsi yang bertugas untuk mengunduh dan mengekstrak dataset dari platform Kaggle.

```c
void download_and_extract() {
    system("kaggle datasets download -d irwansyah10010/mobilelegend -p .");
    system("unzip -o mobilelegend.zip");
}
```

- Fungsi `system()` digunakan untuk mengeksekusi perintah sistem operasi dari dalam program C.
- Perintah yang dieksekusi di sini adalah `kaggle datasets download -d irwansyah10010/mobilelegend -p .`, yang mengunduh dataset dengan nama `mobilelegend` dari akun Kaggle `irwansyah10010` ke direktori saat ini (`.`).
- Setelah dataset berhasil diunduh, perintah ini mengekstrak isi dari file `mobilelegend.zip`.
- Opsi `-o` digunakan untuk menimpa file yang sudah ada tanpa konfirmasi tambahan.

<br>

2. `int read_identities()`
Fungsi read_identities bertugas untuk membaca data hero identities dari sebuah file CSV.

```c
int read_identities(const char* filename, Identity identities[]) {
    FILE* file = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) && count < MAX_HERO_COUNT) {
        sscanf(buffer, "%[^;];%[^;];%[^;];%d", identities[count].name, identities[count].role, identities[count].tipe, &identities[count].tahun_rilis);
        count++;
    }

    fclose(file);
    return count;
}
```

- `filename` merupakan nama file yang akan dibuka, yaitu "Data Mobile Legend/identitas.csv".
- Jika file gagal dibuka, maka fungsi akan mencetak pesan kesalahan yang berisi nama file yang gagal dibuka, dan kemudian mengembalikan nilai 0 sebagai tanda bahwa operasi membaca file gagal.
- Fungsi `fgets` digunakan untuk membaca satu baris teks dari file dan menyimpannya ke dalam buffer `buffer`.
- `sscanf` digunakan untuk mem-parsing (menguraikan) teks dalam `buffer` sesuai dengan format yang ditentukan.
- Pada fungsi ini, teks dalam `buffer` diparsing untuk mengisi struktur `Identity` pada indeks `count` dari array `identities`.
- Proses membaca akan terus dilakukan selama masih ada baris yang dapat dibaca dari file dan `count` masih kurang dari `MAX_HERO_COUNT`.
- Setiap baris yang berhasil dibaca akan meningkatkan nilai `count` untuk mengisi data hero identities selanjutnya.
- Setelah selesai membaca, file ditutup menggunakan fungsi `fclose`. Fungsi kemudian mengembalikan jumlah data hero identities yang berhasil dibaca.

<br>

3. `int read_attributes()`
Fungsi read_attributes bertugas untuk membaca data atribut hero dari sebuah file CSV.

```c
int read_attributes(const char* filename, Attributes attributes[]) {
    FILE* file = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) && count < MAX_HERO_COUNT) {
        sscanf(buffer, "%[^;];%d;%f;%d;%d;%f;%d;%d;%d;%d", attributes[count].name, &attributes[count].hp, &attributes[count].hp_regen, &attributes[count].physical_attack, &attributes[count].physical_defense, 
               &attributes[count].attack_speed, &attributes[count].attack_speed_pc, &attributes[count].mana, &attributes[count].mana_regen, &attributes[count].magic_power);
        count++;
    }
 
    fclose(file);
    return count;
}
```

- `filename` merupakan nama file yang akan dibuka, yaitu "Data Mobile Legend/Atribut/atribut-hero.csv".
- Jika file gagal dibuka, maka fungsi akan mencetak pesan kesalahan yang berisi nama file yang gagal dibuka, dan kemudian mengembalikan nilai `0` sebagai tanda bahwa operasi membaca file gagal.
- Pada fungsi ini, teks dalam `buffer` diparsing untuk mengisi struktur `Attributes` pada indeks `count` dari array `attributes`.
- Proses membaca akan terus dilakukan selama masih ada baris yang dapat dibaca dari file dan `count` masih kurang dari `MAX_HERO_COUNT`.
- Setiap baris yang berhasil dibaca akan meningkatkan nilai `count` untuk mengisi data hero identities selanjutnya.
- Setelah selesai membaca, file ditutup menggunakan fungsi `fclose`. Fungsi kemudian mengembalikan jumlah data hero identities yang berhasil dibaca.

<br>

4. `HeroScore calculate_best_hero()`
Fungsi calculate_best_hero digunakan untuk mencari hero terbaik berdasarkan peran (role) yang ditentukan.

#### 1. Inisialisasi variabel
```c
HeroScore best_hero = {"", 0.0};
float max_score = -1.0;
float score;
```
- `best_hero` adalah variabel untuk menyimpan data hero terbaik yang ditemukan.
- `max_score` digunakan untuk menyimpan nilai tertinggi dari skor hero yang ditemukan.
- `score` digunakan untuk menyimpan nilai skor sementara saat mengevaluasi setiap hero.

<br>

#### 2. Perulangan untuk Mengevaluasi Setiap Hero
```c
for (int i = 0; i < att_count; i++) {
```
- Fungsi ini akan mengevaluasi setiap hero yang ada dalam daftar atribut hero.

<br>

#### 3. Pemilihan Hero Berdasarkan Role
```c
if (strcmp(identities[i].role, role) == 0) {
```
- Setiap hero akan dicek apakah rolenya sesuai dengan role yang ditentukan.

<br>

#### 4. Perhitungan Skor Hero
```c
            if (strcmp(role, "TANK") == 0) {
                score = attributes[i].hp;
            } else if (strcmp(role, "ASSASSIN") == 0) {
                score = attributes[i].physical_attack;
            } else if (strcmp(role, "FIGHTER") == 0) {
                score = attributes[i].hp + attributes[i].physical_attack;
            } else if (strcmp(role, "MM") == 0) {
                score = attributes[i].physical_attack * attributes[i].attack_speed;
            } else if (strcmp(role, "MAGE") == 0) {
                score = attributes[i].mana / attributes[i].mana_regen;
            } else if (strcmp(role, "SUPPORT") == 0) {
                score = attributes[i].mana_regen + attributes[i].hp;
            } else {
                score = 0;
            }
```
- Skor hero dihitung berdasarkan formula yang ditentukan:
- Untuk `TANK`, skor dihitung dari atribut `hp`.
- Untuk `ASSASSIN`, skor dihitung dari atribut `physical_attack`.
- Untuk `FIGHTER`, skor dihitung dari jumlah atribut `hp` dan `physical_attack`.
- Untuk `MM`, skor dihitung dari hasil perkalian atribut `physical_attack` dan `attack_speed`.
- Untuk `MAGE`, skor dihitung dari pembagian atribut `mana` dengan `mana_regen`.
- Untuk `SUPPORT`, skor dihitung dari jumlah atribut `mana_regen` dan `hp`.
- Jika role tidak sesuai, maka skor diatur menjadi `0`.

<br>

#### 5. Penyimpanan Hero Terbaik
```c
if (score > max_score) {
    max_score = score;
    if(strcmp(best_hero.name, "MM") == 0) strcpy(best_hero.name, "MARKSMAN");
    else strcpy(best_hero.name, identities[i].name);
    best_hero.skillpoints = score;
}
```
- Jika skor hero saat ini lebih tinggi dari `max_score`, maka skor tersebut akan dijadikan sebagai `max_score` baru.
- Data hero terbaik (`best_hero`) akan diperbarui dengan nama dan skor hero yang memiliki skor tertinggi.

<br>

#### 6. Pengembalian Hero Terbaik
```c
    return best_hero;
```
- Setelah selesai mengevaluasi semua hero, fungsi akan mengembalikan data hero terbaik yang ditemukan.

<br>

5. `int isDirectoryExists()`

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
