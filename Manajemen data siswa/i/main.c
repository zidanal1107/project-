#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *data;
const char *namaFile_data = "data.csv";

#define JUMLAH_ARRAY 50

// ===== fungsi tambah data ===== 
void tambah_siswa() {
    char system_operasi[10] = "nt";  // contoh nilai
    if (strcmp(system_operasi, "nt") == 0) {
        system("cls");   // perintah clear di Windows
    } else {
        system("clear"); // perintah clear di Linux/Unix
    }

    // deklarasi veriabel
    // Fixed: Changed jenis_klamin from [1][JUMLAH_ARRAY] to [JUMLAH_ARRAY] to make it a char array for single char storage
    // Added tugas to store average grades
    // Added uts and uas arrays for UTS and UAS scores
    int no_awal = 1;
    char baris[256];
    int jml = 0;
    char nama[JUMLAH_ARRAY][JUMLAH_ARRAY],kelas[JUMLAH_ARRAY][JUMLAH_ARRAY],jenis_klamin[JUMLAH_ARRAY];
    int nisn[JUMLAH_ARRAY],total_tugas[JUMLAH_ARRAY],total_uts[JUMLAH_ARRAY],total_uas[JUMLAH_ARRAY];
    float tugas[JUMLAH_ARRAY], uts[JUMLAH_ARRAY], uas[JUMLAH_ARRAY];
    data = fopen(namaFile_data, "a");
    // Bug fix: Added check if file opens successfully to prevent crashes
    if (data == NULL) {
        printf("Error: Tidak dapat membuka file data.csv!\n");
        return;
    }
    rewind(data);
    while (fgets(baris, sizeof(baris), data)) {
        int temp;
        if (sscanf(baris, "%d;", &temp) == 1) {
            no_awal = temp + 1;
        }
    }

    // Bug fix: Added logic to write CSV header if file is empty for proper CSV format
    // Updated header to include UTS and UAS scores
    fseek(data, 0, SEEK_END);
    long size = ftell(data);
    if (size == 0) {
        fprintf(data, "Nama;Jenis Kelamin;NISN;Kelas;Tugas;UTS;UAS\n");
    }

    printf("=== Tambah Data Siswa/i ===\n");
    while (1)
    {
        // input nama
        printf("Masukkan Nama           : ");
        fgets(nama[jml], JUMLAH_ARRAY, stdin);
        nama[jml][strcspn(nama[jml], "\n")] = 0;
        
        // input jenis kelamin
        while (1)
        {
            printf("Masukkan jenis klamin   : ");
            if (scanf(" %c", &jenis_klamin[jml]) != 1) {
                while (getchar() != '\n');
                printf("Input tidak valid!\n");
                continue;
            } else if (jenis_klamin[jml] != 'L' && jenis_klamin[jml] != 'P') {
                printf("Input harus L atau P!\n");
                continue;
            } else {
                break;
            }
        }
        
        // input nisn
        while (1)
        {
            printf("Masukkan NISN           : ");
            if (scanf("%d", &nisn[jml]) != 1) {
                while (getchar() != '\n');
                printf("Input tidak valid!\n");
                continue;
            } else {
                while (getchar() != '\n');
                break;
            }
        }
        
        // input kelas
        printf("Masukkan Kelas          : ");
        fgets(kelas[jml], JUMLAH_ARRAY, stdin);
        kelas[jml][strcspn(kelas[jml], "\n")] = 0;

        // input nilai
        printf("\nNilai:\n");
        while (1)
        {
            // Fixed: Changed from nama (undefined) to nama[jml] to display the student's name
            printf("Masukkan total tugas yang sudah dikerjakan %s : ", nama[jml]);
            if (scanf("%d", &total_tugas[jml]) != 1) {
                while (getchar() != '\n');
                printf("Input tidak valid!\n");
                continue;
            } else {
                while (getchar() != '\n');
                break;
            }
        }

        int i;
        int *nilai_tugas = malloc(sizeof(int) * (total_tugas[jml] > 0 ? total_tugas[jml] : 1));
        if (nilai_tugas == NULL) {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }
        for (i = 0; i < total_tugas[jml]; i++) {
            while (1)
            {
                printf("Masukkan nilai tugas ke-%d: ", i+1);
                if (scanf("%d", &nilai_tugas[i]) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
        }
        // Fixed: Calculate average grade to save in CSV
        int sum = 0;
        for (i = 0; i < total_tugas[jml]; i++) {
            sum += nilai_tugas[i];
        }
        // Bug fix: Handle division by zero if total_tugas is 0, set tugas to 0
        if (total_tugas[jml] > 0) {
            tugas[jml] = (float)sum / total_tugas[jml];
        } else {
            tugas[jml] = 0.0;
        }
        free(nilai_tugas);

        // input nilai UTS
        while (1)
        {
            printf("Masukkan berapa kali %s ikut UTS: ", nama[jml]);
            if (scanf("%d", &total_uts[jml]) != 1) {
                while (getchar() != '\n');
                printf("Input tidak valid!\n");
                continue;
            } else {
                while (getchar() != '\n');
                break;
            }
        }

        int *nilai_uts = malloc(sizeof(int) * (total_uts[jml] > 0 ? total_uts[jml] : 1));
        if (nilai_uts == NULL) {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }
        for (i = 0; i < total_uts[jml]; i++) {
            while (1)
            {
                printf("Masukkan nilai UTS ke-%d: ", i+1);
                if (scanf("%d", &nilai_uts[i]) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
        }

        int sumUts = 0;
        for (i = 0; i < total_uts[jml]; i++) {
            sumUts += nilai_uts[i];
        }

        if (total_uts[jml] > 0) {
            uts[jml] = (float)sumUts / total_uts[jml];
        } else {
            uts[jml] = 0.0;
        }
        free(nilai_uts);

        // input nilai UAS
        while (1)
        {
            printf("Masukkan berapa kali %s ikut UAS : ", nama[jml]);
            if (scanf("%d", &total_uas[jml]) != 1) {
                while (getchar() != '\n');
                printf("Input tidak valid!\n");
                continue;
            } else {
                while (getchar() != '\n');
                break;
            }
        }

        int *nilai_uas = malloc(sizeof(int) * (total_uas[jml] > 0 ? total_uas[jml] : 1));
        if (nilai_uas == NULL) {
            printf("Memory allocation failed!\n");
            fclose(data);
            return;
        }
        for (i = 0; i < total_uas[jml]; i++) {
            while (1)
            {
                printf("Masukkan nilai UAS ke-%d: ", i+1);
                if (scanf("%d", &nilai_uas[i]) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
        }

        int sumUas = 0;
        for (i = 0; i < total_uas[jml]; i++) {
            sumUas += nilai_uas[i];
        }

        if (total_uas[jml] > 0) {
            uas[jml] = (float)sumUas / total_uas[jml];
        } else {
            uas[jml] = 0.0;
        }

        free(nilai_uas);

        jml+=1;
        // Fixed: Removed break to allow adding multiple students, added prompt to continue or stop
        char lagi;
        printf("Tambah siswa lagi? (y/n): ");
        scanf(" %c", &lagi);
        while (getchar() != '\n'); // clear buffer
        if (lagi != 'y' && lagi != 'Y') {
            break;
        }
    }
    int i;
    for (i = 0; i < jml; i++)
    {
    // Bug fix: Changed format string to include the student number (i+1) at the beginning to match CSV header "No;Nama;..."
    // Updated to include UTS and UAS
    fprintf(data, "\n%s;%c;%d;%s;%.2f;%.2f;%.2f",
                    nama[i], jenis_klamin[i], nisn[i], kelas[i], tugas[i], uts[i], uas[i]);
    }
    fclose(data);
}

void lihat_data() {
    char system_operasi[10] = "nt";  // contoh nilai
        if (strcmp(system_operasi, "nt") == 0) {
            system("cls");   // perintah clear di Windows
        } else {
            system("clear"); // perintah clear di Linux/Unix
        }
    // Implementation: Read and display data from CSV file
    FILE *file = fopen(namaFile_data, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file data.csv!\n");
        getchar();
        return;
    }
    printf("=== Data Siswa ===\n");
    printf("%-20s %-15s %-10s %-10s %-10s %-10s %-10s\n", "Nama", "Jenis Kelamin", "NISN", "Kelas", "Tugas", "UTS", "UAS");
    printf("-----------------------------------------------------------------------------------\n");
    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line_count++;
        if (line_count == 1) {
            // Skip header
            continue;
        }
        // Parse and display data
        // Updated to exclude total_tugas
        int nisn;
        char nama[50], jenis_kelamin, kelas[50];
        float tugas, uts, uas;
        if (sscanf(line, "%[^;];%c;%d;%[^;];%f;%f;%f", nama, &jenis_kelamin, &nisn, kelas, &tugas, &uts, &uas) == 7) {
            printf("%-20s %-15c %-10d %-10s %-10.2f %-10.2f %-10.2f\n", nama, jenis_kelamin, nisn, kelas, tugas, uts, uas);
        }
    }
    fclose(file);
    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
}

void edit_data() {
    char system_operasi[10] = "nt";  // contoh nilai
        if (strcmp(system_operasi, "nt") == 0) {
            system("cls");   // perintah clear di Windows
        } else {
            system("clear"); // perintah clear di Linux/Unix
        }
    // Implementation: Edit student data by NISN
    typedef struct {
        char nama[50];
        char jenis_kelamin;
        int nisn;
        char kelas[50];
        float tugas, uts, uas;
    } Student;

    FILE *file = fopen(namaFile_data, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file data.csv!\n");
        getchar();
        return;
    }

    Student students[100]; // Assume max 100 students
    int count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Skip header
    while (fgets(line, sizeof(line), file)) {
        // Updated to exclude total_tugas
        if (sscanf(line, "%[^;];%c;%d;%[^;];%f;%f;%f", students[count].nama, &students[count].jenis_kelamin, &students[count].nisn, students[count].kelas, &students[count].tugas, &students[count].uts, &students[count].uas) == 7) {
            count++;
        }
    }
    fclose(file);

    int edit_nisn;
    while (1)
    {
        printf("Masukkan NISN siswa yang ingin diedit: ");
        if (scanf("%d", &edit_nisn) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid!\n");
            getchar();
            continue;
        } else {
            while (getchar() != '\n');
            break;
        }
    }

    int found = -1;
    int i; // Declare loop variable outside for C89 compatibility
    for (i = 0; i < count; i++) {
        if (students[i].nisn == edit_nisn) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Siswa dengan NISN %d tidak ditemukan.\n", edit_nisn);
        getchar();
        return;
    }

    printf("Data saat ini:\n");
    printf("Nama            : %s\n", students[found].nama);
    printf("Jenis Kelamin   : %c\n", students[found].jenis_kelamin);
    printf("NISN            : %d\n", students[found].nisn);
    printf("Kelas           : %s\n", students[found].kelas);
    printf("Tugas           : %.2f\n", students[found].tugas);
    printf("UTS             : %.2f\n", students[found].uts);
    printf("UAS             : %.2f\n", students[found].uas);

    int choice;
    while (1)
    {
        printf("\nPilih field yang ingin diedit:\n");
        printf("1. Nama\n2. Jenis Kelamin\n3. Kelas\n4. Nilai Tugas\n5. UTS\n6. UAS");
        printf("\nPilih: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid!\n");
            getchar();
            continue;
        } else if (choice < 1 || choice > 6) {
            printf("Input tidak valid!\n");
            getchar();
            continue;
        } else {
            while (getchar() != '\n');
            break;
        }
    }

    switch (choice) {
        case 1: {
            printf("Masukkan nama baru: ");
            fgets(students[found].nama, 50, stdin);
            students[found].nama[strcspn(students[found].nama, "\n")] = 0;
            if (strlen(students[found].nama) == 49) {
                while (getchar() != '\n');
            }
            break;
        }
        case 2: {
            while (1) {
                printf("Masukkan jenis kelamin baru (L/P): ");
                if (scanf(" %c", &students[found].jenis_kelamin) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                }
                while (getchar() != '\n');
                if (students[found].jenis_kelamin == 'L' || students[found].jenis_kelamin == 'P') break;
                printf("Input harus L atau P!\n");
            }
            break;
        }
        case 3: {
            printf("Masukkan kelas baru: ");
            fgets(students[found].kelas, 50, stdin);
            students[found].kelas[strcspn(students[found].kelas, "\n")] = 0;
            if (strlen(students[found].kelas) == 49) {
                while (getchar() != '\n');
            }
            break;
        }
        case 4: {
            int total_tugas;
            while (1) {
                printf("Masukkan berapa kali %s mengerjakan tugas: ", students[found].nama);
                if (scanf("%d", &total_tugas) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
            int *nilai_tugas = malloc(sizeof(int) * (total_tugas > 0 ? total_tugas : 1));
            if (nilai_tugas == NULL) {
                printf("Memory allocation failed!\n");
                return;
            }
            int i;
            for (i = 0; i < total_tugas; i++) {
                while (1) {
                    printf("Masukkan nilai tugas ke-%d: ", i+1);
                    if (scanf("%d", &nilai_tugas[i]) != 1) {
                        while (getchar() != '\n');
                        printf("Input tidak valid!\n");
                        continue;
                    } else {
                        while (getchar() != '\n');
                        break;
                    }
                }
            }
            int sum = 0;
            for (i = 0; i < total_tugas; i++) {
                sum += nilai_tugas[i];
            }
            if (total_tugas > 0) {
                students[found].tugas = (float)sum / total_tugas;
            } else {
                students[found].tugas = 0.0;
            }
            free(nilai_tugas);
            break;
        }
        case 5: {
            int total_uts;
            while (1) {
                printf("Masukkan berapa kali %s mengikuti UTS: ", students[found].nama);
                if (scanf("%d", &total_uts) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
            int *nilai_uts = malloc(sizeof(int) * (total_uts > 0 ? total_uts : 1));
            if (nilai_uts == NULL) {
                printf("Memory allocation failed!\n");
                return;
            }
            int i;
            for (i = 0; i < total_uts; i++) {
                while (1) {
                    printf("Masukkan nilai UTS ke-%d: ", i+1);
                    if (scanf("%d", &nilai_uts[i]) != 1) {
                        while (getchar() != '\n');
                        printf("Input tidak valid!\n");
                        continue;
                    } else {
                        while (getchar() != '\n');
                        break;
                    }
                }
            }
            int sum = 0;
            for (i = 0; i < total_uts; i++) {
                sum += nilai_uts[i];
            }
            if (total_uts > 0) {
                students[found].uts = (float)sum / total_uts;
            } else {
                students[found].uts = 0.0;
            }
            free(nilai_uts);
            break;
        }
        case 6: {
            int total_uas;
            while (1) {
                printf("Masukkan berapa kali %s mengikuti UAS: ", students[found].nama);
                if (scanf("%d", &total_uas) != 1) {
                    while (getchar() != '\n');
                    printf("Input tidak valid!\n");
                    continue;
                } else {
                    while (getchar() != '\n');
                    break;
                }
            }
            int *nilai_uas = malloc(sizeof(int) * (total_uas > 0 ? total_uas : 1));
            if (nilai_uas == NULL) {
                printf("Memory allocation failed!\n");
                return;
            }
            int i;
            for (i = 0; i < total_uas; i++) {
                while (1) {
                    printf("Masukkan nilai UAS ke-%d: ", i+1);
                    if (scanf("%d", &nilai_uas[i]) != 1) {
                        while (getchar() != '\n');
                        printf("Input tidak valid!\n");
                        continue;
                    } else {
                        while (getchar() != '\n');
                        break;
                    }
                }
            }
            int sum = 0;
            for (i = 0; i < total_uas; i++) {
                sum += nilai_uas[i];
            }
            if (total_uas > 0) {
                students[found].uas = (float)sum / total_uas;
            } else {
                students[found].uas = 0.0;
            }
            free(nilai_uas);
            break;
        }
    }

    // Write back to file
    file = fopen(namaFile_data, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk menulis!\n");
        getchar();
        return;
    }
    fprintf(file, "Nama;Jenis Kelamin;NISN;Kelas;Tugas;UTS;UAS\n");
    for (i = 0; i < count; i++) { // Use existing i variable for C89 compatibility
    fprintf(file, "%s;%c;%d;%s;%.2f;%.2f;%.2f\n", students[i].nama, students[i].jenis_kelamin, students[i].nisn, students[i].kelas, students[i].tugas, students[i].uts, students[i].uas);
    }
    fclose(file);

    printf("Data berhasil diedit!\n");
    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
}

void hapus_data() {
    char system_operasi[10] = "nt";  // contoh nilai
    if (strcmp(system_operasi, "nt") == 0) {
        system("cls");   // perintah clear di Windows
    } else {
        system("clear"); // perintah clear di Linux/Unix
    }

    typedef struct {
        char nama[50];
        char jenis_kelamin;
        int nisn;
        char kelas[50];
        float tugas, uts, uas;
    } Student;

    FILE *file = fopen(namaFile_data, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file data.csv!\n");
        getchar();
        return;
    }

    Student students[100];
    int count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Skip header
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^;];%c;%d;%[^;];%f;%f;%f", students[count].nama, &students[count].jenis_kelamin, &students[count].nisn, students[count].kelas, &students[count].tugas, &students[count].uts, &students[count].uas) == 7) {
            count++;
        }
    }
    fclose(file);

    int delete_nisn;
    while (1) {
        printf("Masukkan NISN siswa yang ingin dihapus: ");
        if (scanf("%d", &delete_nisn) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid!\n");
            getchar();
            continue;
        } else {
            while (getchar() != '\n');
            break;
        }
    }

    int found = -1;
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].nisn == delete_nisn) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Siswa dengan NISN %d tidak ditemukan.\n", delete_nisn);
        getchar();
        return;
    }

    // Shift array to remove the student
    for (i = found; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;

    // Write back to file
    file = fopen(namaFile_data, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk menulis!\n");
        getchar();
        return;
    }
    fprintf(file, "Nama;Jenis Kelamin;NISN;Kelas;Tugas;UTS;UAS\n");
    for (i = 0; i < count; i++) {
        fprintf(file, "%s;%c;%d;%s;%.2f;%.2f;%.2f\n", students[i].nama, students[i].jenis_kelamin, students[i].nisn, students[i].kelas, students[i].tugas, students[i].uts, students[i].uas);
    }
    fclose(file);

    printf("Data siswa berhasil dihapus!\n");
    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
}

void lihat_nilai() {
    char system_operasi[10] = "nt";  // contoh nilai
    if (strcmp(system_operasi, "nt") == 0) {
        system("cls");   // perintah clear di Windows
    } else {
        system("clear"); // perintah clear di Linux/Unix
    }

    FILE *file = fopen(namaFile_data, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file data.csv!\n");
        getchar();
        return;
    }

    printf("=== Lihat Nilai & Rapor Siswa ===\n");
    printf("%-20s %-10s %-10s %-10s %-10s %-10s\n", "Nama", "Kelas", "Tugas", "UTS", "UAS", "Final");
    printf("---------------------------------------------------------------------------------\n");

    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line_count++;
        if (line_count == 1) {
            // Skip header
            continue;
        }
        char nama[50], jenis_kelamin, kelas[50];
        int nisn;
        float tugas, uts, uas;
        if (sscanf(line, "%[^;];%c;%d;%[^;];%f;%f;%f", nama, &jenis_kelamin, &nisn, kelas, &tugas, &uts, &uas) == 7) {
            // Calculate final grade (example: 20% tugas, 30% UTS, 50% UAS)
            float final = (tugas * 0.2) + (uts * 0.3) + (uas * 0.5);
            printf("%-20s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", nama, kelas, tugas, uts, uas, final);
        }
    }
    fclose(file);

    printf("\nTekan Enter untuk kembali ke menu...\n");
    getchar();
}

int main() {
    int pilih;
    while (1)
    {
        char system_operasi[10] = "nt";  // contoh nilai
            if (strcmp(system_operasi, "nt") == 0) {
                system("cls");   // perintah clear di Windows
            } else {
                system("clear"); // perintah clear di Linux/Unix
            }
    
        printf("=== SISTEM PERPUSTAKAAN ===\n");
        printf("1. Tambah Data Siswa\n2. Lihat Data Siswa\n3. Edit Data Siswa\n4. Hapus Data Siswa\n5. Lihat Nilai & Rapor\n0. Keluar");
        
        printf("\nPilih: ");
        if (scanf("%d", &pilih) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid!\n");
            getchar();
            continue;
        }
        while (getchar() != '\n');

        if (pilih < 0 || pilih > 5) {
            printf("Input tidak valid!\n");
            getchar();
            continue;
        }

        if (pilih == 0) {
            break;
        }

        switch (pilih)
        {
            case 1: tambah_siswa(); break;
            case 2: lihat_data(); break;
            case 3: edit_data(); break;
            case 4: hapus_data(); break;
            case 5: lihat_nilai(); break;
        }
    }
    printf("\nProgram selesai!\n");
    return 0;
}