#include "invetaris.h"

struct DataBarang gudang[MAX_ITEMS];
uint8_t head_indeks= NULL_INDEKS;
uint8_t free_head = 0; 
// test git
void CekSound() {
    Serial.begin(9600);
    Serial.println(F("BOOTING OVERRIDE..."));
    for (int i = 0; i < MAX_ITEMS - 1; i++)
    {
        gudang[i].next_indeks = i + 1;
    }
    gudang[MAX_ITEMS - 1].next_indeks = NULL_INDEKS;
    Serial.println(F("GALACTIC ARMORY TERMINAL ONLINE!"));
}

// void tambahData(char* input_id, char* input_nama, char* input_lokasi, char* input_pic_owner, uint8_t input_stok, uint8_t input_status) {
//     if (free_head == NULL_INDEKS)
//     {
//         Serial.println(F("GAGAL: Memori Penuh!")); 
//         return;
//     }

//     uint8_t indeks_baru = free_head;
//     free_head = gudang[indeks_baru].next_indeks;
//     strncpy(gudang[indeks_baru].id, input_id, sizeof(gudang[indeks_baru].id));
//     strncpy(gudang[indeks_baru].nama, input_nama, sizeof(gudang[indeks_baru].nama));
//     strncpy(gudang[indeks_baru].lokasi, input_lokasi, sizeof(gudang[indeks_baru].lokasi));

//     gudang[indeks_baru].stok = input_stok;
//     gudang[indeks_baru].status = input_status;
//     gudang[indeks_baru].pic = input_pic;

//     gudang[indeks_baru].next_indeks = head_indeks; 
//     head_indeks = indeks_baru;

//     Serial.print(F("SUKSES: Data berhasil ditambah ke Laci "));
//     Serial.println(indeks_baru);
// }

void tambahData(char* input_id, char* input_nama, char* input_lokasi, char* input_pic_owner, uint8_t input_stok, uint8_t input_status) {
    if (input_status == 0) {
        uint8_t indeks_cek = head_indeks;
        while (indeks_cek != NULL_INDEKS) {
            // cek kalau idnya sama
            if (strcmp(gudang[indeks_cek].id, input_id) == 0 && gudang[indeks_cek].status == 0) {
                Serial.println(F("\n[ERROR] GAGAL: ID Senjata sudah terdaftar di Arsenal!"));
                Serial.println(F("Gunakan fitur Update Stok jika ingin menambah kuantitas."));
                return; //keluar function
            }
            indeks_cek = gudang[indeks_cek].next_indeks;
        }
    }
    
    if (free_head == NULL_INDEKS)
    {
        Serial.println(F("GAGAL: Memori Penuh!"));
        return;
    }

    uint8_t indeks_baru = free_head;
    free_head = gudang[indeks_baru].next_indeks;
    strncpy(gudang[indeks_baru].id, input_id, sizeof(gudang[indeks_baru].id));
    strncpy(gudang[indeks_baru].nama, input_nama, sizeof(gudang[indeks_baru].nama));
    strncpy(gudang[indeks_baru].lokasi, input_lokasi, sizeof(gudang[indeks_baru].lokasi));
    strncpy(gudang[indeks_baru].pic_owner, input_pic_owner, sizeof(gudang[indeks_baru].pic_owner)); //tambahin picnya

    gudang[indeks_baru].stok = input_stok;
    gudang[indeks_baru].status = input_status;
    gudang[indeks_baru].next_indeks = head_indeks;
    head_indeks = indeks_baru;

    Serial.print(F("SUKSES: Data berhasil ditambah ke Laci "));
    Serial.println(indeks_baru);
}

/** updateStatus(char* input_id, uint8_t status_baru){

    uint8_t indeks_sekarang = head_index

    while (gudang[indeks_sekarang].id = NULL_INDEX)
    {
        if (strcmp(gudang[indeks_sekarang].id,input_id) == 0)
        {
            serial.print("STATUS BARANG : &d", gudang[indeks_baru].status);
            serial.print("MAU DIAPAKAN BARANGNYA?"'\n'); // 1. pinjam 2. buang
            if (status_baru == 1)
            {
                gudang[indeks_sekarang].status = 
            }
            

        }
        
        //masukin input, while loop till input == gudang[indeks_baru].id??
        //serial.print("STATUS BARANG :%d", input_status);
        kurang efisien dah?? 
        
        //masukin input status baru
    }
    
}*/

void hapusdata(uint8_t indeks_target) {
    if (head_indeks == NULL_INDEKS) return;

    if (head_indeks == indeks_target) 
    {
        head_indeks = gudang[indeks_target].next_indeks;
        gudang[indeks_target].next_indeks = free_head;
        free_head = indeks_target;
        return;
    }
    
    uint8_t indeks_sebelumnya = head_indeks;
    uint8_t indeks_sekarang = gudang[head_indeks].next_indeks;

    while (indeks_sekarang != NULL_INDEKS) 
    {
        if (indeks_sekarang == indeks_target)
        {
            gudang[indeks_sebelumnya].next_indeks = gudang[indeks_sekarang].next_indeks;
            gudang[indeks_target].next_indeks = free_head;
            free_head = indeks_target;
            return;
        }
        indeks_sebelumnya = indeks_sekarang;
        indeks_sekarang = gudang[indeks_sekarang].next_indeks;
    }
}

void pinjambarang(char* input_id, uint8_t jumlah_pinjam, char* pic_peminjam) { 
    uint8_t indeks = head_indeks;
    while (indeks != NULL_INDEKS) {
        
        if (strcmp(gudang[indeks].id, input_id) == 0 && gudang[indeks].status == 0) {
            
            if (gudang[indeks].stok >= jumlah_pinjam) {

                gudang[indeks].stok = gudang[indeks].stok - jumlah_pinjam;
                
                tambahData(input_id, gudang[indeks].nama, gudang[indeks].lokasi, pic_peminjam, jumlah_pinjam, 1);                
                if (gudang[indeks].stok == 0)
                {
                    hapusdata(indeks);
                }

                Serial.println(F("SUKSES: Peminjaman item berhasil dicatat!"));
                return;
                
            } else {
                Serial.println(F("ERROR: Transaksi Gagal, sisa stok tidak mencukupi!"));
                return; 
            }
        }
        indeks = gudang[indeks].next_indeks;
    }
    Serial.println(F("ERROR: Item tidak ditemukan atau stok sedang kosong."));
}

void kembalikanBarang(char* input_id, uint8_t jumlah_kembali) { 
    uint8_t indeks = head_indeks;
    uint8_t indeks_pinjam = NULL_INDEKS;
    uint8_t indeks_tersedia = NULL_INDEKS;
    while (indeks != NULL_INDEKS)
    {
        if (strcmp(gudang[indeks].id, input_id) == 0 && gudang[indeks].status == 1)
        {
            indeks_pinjam = indeks;
        }
        else if (strcmp(gudang[indeks].id, input_id) == 0 && gudang[indeks].status == 0)
        {
            indeks_tersedia = indeks;
        }
        indeks = gudang[indeks].next_indeks;
    }

    if (indeks_pinjam == NULL_INDEKS) {
        Serial.println(F("ERROR: Data peminjaman item tidak ditemukan!"));
        return;
    }
    if (gudang[indeks_pinjam].stok < jumlah_kembali) {
        Serial.println(F("ERROR: Jumlah yang dikembalikan melebihi data pinjaman!"));
        return;
    }

    gudang[indeks_pinjam].stok = gudang[indeks_pinjam].stok - jumlah_kembali;

    if (indeks_tersedia != NULL_INDEKS){
        gudang[indeks_tersedia].stok = gudang[indeks_tersedia].stok + jumlah_kembali;
    }
    else
    {
        tambahData(input_id, gudang[indeks_pinjam].nama, gudang[indeks_pinjam].lokasi, "-", jumlah_kembali, 0);
    }
    
    if (gudang[indeks_pinjam].stok == 0) {
        hapusdata(indeks_pinjam);
    }    
    Serial.println(F("SUKSES: Item berhasil dikembalikan ke markas!"));
}

void printall() { //ini buat kek overall gimana aja gak yang dilist atu2
    uint8_t indeks = head_indeks;

    uint8_t total_jenis_item = 0;
    uint32_t total_kuantitas_stok = 0;
    uint8_t item_tersedia = 0;
    uint8_t item_dipinjam = 0;
    uint8_t item_rusak = 0;

    while (indeks != NULL_INDEKS) {
        total_jenis_item++;
        total_kuantitas_stok += gudang[indeks].stok;
        
        if (gudang[indeks].status == 0) {
            item_tersedia++;
        } 
        else if (gudang[indeks].status == 1) {
            item_dipinjam++;
        } 
        else if (gudang[indeks].status == 2) {
            item_rusak++;
        }
        
        indeks = gudang[indeks].next_indeks;
    }

    Serial.println(F("     :: HOLONET SUMMARY REPORT ::   "));
    Serial.println(F("------------------------------------------------"));
    Serial.print(F(" Total Variasi Jenis Item :")); Serial.print(total_jenis_item); Serial.println(F(" Jenis"));
    Serial.print(F(" Total Kuantitas Senjata  :")); Serial.print(total_kuantitas_stok); Serial.println(F(" Unit"));
    Serial.println(F("------------------------------------------"));
    Serial.print(F("Kategori Tersedia: ")); Serial.println(item_tersedia); 
    Serial.print(F("Kategori Dipinjam: ")); Serial.println(item_dipinjam); 
    Serial.print(F("Kategori Rusak: ")); Serial.println(item_rusak);
    Serial.println(F("------------------------------------------------"));
}

/**READ() { // ganti sistem pemilihan
    if (Serial.available() > 0) {
        String input_teks = Serial.readStringUntil('\n');
        input_teks.trim(); 
        
        if (input_teks.length() == 0) return;

        char buffer[64];
        input_teks.toCharArray(buffer, sizeof(buffer));

        char* perintah = strtok(buffer, " ");

        if (perintah == NULL) return;

        if (strcmp(perintah, "TAMPIL") == 0) {
            printoutput();
        } 
        else if (strcmp(perintah, "CARI") == 0) {
            char* id_barang = strtok(NULL, " ");
            if (id_barang != NULL) {
                cariData(id_barang);
            }
        } 
        else if (strcmp(perintah, "PINJAM") == 0) {
            char* id_barang = strtok(NULL, " ");
            char* jumlah_str = strtok(NULL, " ");
            if (id_barang != NULL && jumlah_str != NULL) {
                pinjambarang(id_barang, atoi(jumlah_str));
            }
        } 
        else if (strcmp(perintah, "KEMBALI") == 0) {
            char* id_barang = strtok(NULL, " ");
            char* jumlah_str = strtok(NULL, " ");
            if (id_barang != NULL && jumlah_str != NULL) {
                kembalikanBarang(id_barang, atoi(jumlah_str));
            }
        } 
        else {
            Serial.println("ERROR: Perintah tidak dikenal!");
        }
    }
}**/

void printoutput() {
    uint8_t indeks = head_indeks;

    Serial.println(F("=== DAFTAR STOK ARSENAL ==="));

    if (indeks == NULL_INDEKS) {
        Serial.println(F("Sistem kosong. Belum ada data item yang terdaftar."));
        Serial.println(F("=========================="));
        return;
    }

    while (indeks != NULL_INDEKS) {
        Serial.print("[");
        Serial.print(gudang[indeks].id);
        Serial.print("] ");
        Serial.print(gudang[indeks].nama);
        Serial.print(F(" - Stok: "));
        Serial.print(gudang[indeks].stok);
        Serial.print(F(" - Status: "));

        if (gudang[indeks].stok == 0) {
            Serial.println(F("Stok Habis"));
        } 
        else if (gudang[indeks].status == 0) {
            Serial.println(F("Tersedia"));
        } 
        else if (gudang[indeks].status == 1) {
            Serial.print(F("Dipinjam OWNER: "));
            Serial.print(gudang[indeks].pic_owner);
            Serial.println(")");
        } 
        else {
            Serial.println(F("Rusak (Disisihkan)"));
        }
        indeks = gudang[indeks].next_indeks;
    }
    
    Serial.println(F("=========================="));
}  

void balik() {
    Serial.println(F("\n[TRANSMISI JEDA... Tekan tombol apa saja lalu ENTER untuk kembali]"));
    while (Serial.available() > 0) { Serial.read(); } 
    while (Serial.available() == 0) { } 
    while (Serial.available() > 0) { Serial.read(); } 
    Serial.println(F("\n[////////////////////////////////////////]"));
}

void cariData(char* input_id) {
    uint8_t indeks = head_indeks;
    bool ketemu = false;

    Serial.print(F("=== HASIL PENCARIAN: "));
    Serial.print(input_id);
    Serial.println(F(" ==="));

    while (indeks != NULL_INDEKS) {
        if (strcmp(gudang[indeks].id, input_id) == 0) {
            Serial.print(F("Nama Item   : ")); 
            Serial.println(gudang[indeks].nama);
            Serial.print(F("Kode Sektor : ")); 
            Serial.println(gudang[indeks].lokasi);
            Serial.print(F("Sisa Stok   : ")); 
            Serial.print(gudang[indeks].stok);
            
            Serial.print(F(" (Status: "));
            if (gudang[indeks].stok == 0) {
                Serial.print(F("Stok Habis"));
            } 
            else if (gudang[indeks].status == 0) {
                Serial.print(F("Tersedia"));
            } 
            else if (gudang[indeks].status == 1) {
                Serial.print(F("Dipinjam oleh Trooper/Jedi "));
                Serial.print(gudang[indeks].pic);
            } 
            else {
                Serial.print(F("Rusak"));
            }
            Serial.println(")");
            
            Serial.println(F("-------------------------"));
            ketemu = true;
        }
        indeks = gudang[indeks].next_indeks;
    }

    if (!ketemu) {
        Serial.println(F("Item tidak ditemukan di dalam sistem."));
    }
    Serial.println(F("========================="));
}

void laporRusak(char* input_id, uint8_t jumlah_rusak) {
    uint8_t indeks = head_indeks;
    while (indeks != NULL_INDEKS) {
        if (strcmp(gudang[indeks].id, input_id) == 0 && gudang[indeks].status == 0) {
            if (gudang[indeks].stok >= jumlah_rusak) {
                gudang[indeks].stok = gudang[indeks].stok - jumlah_rusak;
                tambahData(input_id, gudang[indeks].nama, gudang[indeks].lokasi, "-", jumlah_rusak, 2);
                if (gudang[indeks].stok == 0) {
                    hapusdata(indeks);
                    Serial.println(F("[SUKSES] Data item rusak berhasil dipisahkan dari stok utama."));
                    return;
                }
            } else {
                Serial.println(F("[ERROR] Jumlah laporan rusak melebihi sisa stok yang ada!"));
                return; 
            }
        }
        indeks = gudang[indeks].next_indeks;
    }
    Serial.println(F("[ERROR] Item tidak ditemukan atau stok sedang kosong."));
}

void mainmenu() {
    while (Serial.available() > 0) { Serial.read(); }

    Serial.println(F("\n[////////////////////////////////////////]"));
    Serial.println(F(" > SYSCOM HOLONET LINK...... ESTABLISHED"));
    Serial.println(F(" > DECRYPTING DATAPAD....... SUCCESS"));
    Serial.println(F("[////////////////////////////////////////]"));
    Serial.println(F("      :: GALACTIC ARMORY TERMINAL ::      "));
    Serial.println(F("------------------------------------------"));
    Serial.println(F(" [1] RUN DIAGNOSTICS  (Cek Semua Arsenal)"));
    Serial.println(F(" [2] EXEC PROTOCOL    (Transaksi Item)"));
    Serial.println(F(" [3] UPLOAD SCHEMATIC (Tambah Data Baru)"));
    Serial.println(F("------------------------------------------"));
    Serial.print(F("AWAITING COMMAND (1/2/3): "));

    while (Serial.available() == 0) { }
    String input_menu = Serial.readStringUntil('\n');
    input_menu.trim();
    if (input_menu.length() == 0) return;
    char menu_utama = input_menu.charAt(0);
    Serial.println(menu_utama);

    if (menu_utama == '1') {
        while (Serial.available() > 0) { Serial.read(); }
        
        Serial.println(F("\n---PILIH MODE-----"));
        Serial.println(F("1. Tampilkan Seluruh Detail Data"));
        Serial.println(F("2. Tampilkan Summary Inventaris"));
        Serial.print(F("Pilih opsi (1/2): "));

        while (Serial.available() == 0) { }
        String opsi_diag = Serial.readStringUntil('\n');
        opsi_diag.trim();
        char opsi = opsi_diag.charAt(0);
        Serial.println(opsi);

        if (opsi == '2') {
            printall(); 
        } else {
            printoutput();   
        }
        balik();
    }
    else if (menu_utama == '2') {
        while (Serial.available() > 0) { Serial.read(); }
        Serial.print(F("Ketik ID Item yang dicari (Example: R2D2 / SITH): "));
        while (Serial.available() == 0) { }
        String input_id = Serial.readStringUntil('\n');
        input_id.trim();
        if (input_id.length() == 0) return;
        Serial.println(input_id);

        char id_barang[5];
        input_id.toCharArray(id_barang, sizeof(id_barang));

        cariData(id_barang);

        Serial.println(F("\nPilih Aksi Transaksi:"));
        Serial.println(F("1. Pinjam Item"));
        Serial.println(F("2. Kembalikan Item"));
        Serial.println(F("3. Lapor Item Rusak"));
        Serial.println(F("4. Batal"));
        Serial.print(F("Pilih angka (1/2/3/4): "));

        while (Serial.available() == 0) { }
        String aksi_str = Serial.readStringUntil('\n');
        aksi_str.trim();
        if (aksi_str.length() == 0) return;
        char aksi = aksi_str.charAt(0);
        Serial.println(aksi);

        if (aksi == '1' || aksi == '2' || aksi == '3') {
            while (Serial.available() > 0) { Serial.read(); }
            Serial.print(F("Masukkan jumlah item: "));
            while (Serial.available() == 0) { }
            String jumlah_str = Serial.readStringUntil('\n');
            jumlah_str.trim();
            if (jumlah_str.length() == 0) return;
            int jumlah = jumlah_str.toInt();
            Serial.println(jumlah);

            if (aksi == '1') {
                while (Serial.available() > 0) { Serial.read(); }
                Serial.print(F("Ketik nama Trooper / Jedi peminjam (Maks 5 karakter, Ex: RUDI): ")); //jadiin character
                while (Serial.available() == 0) { }
                String pic_str = Serial.readStringUntil('\n');
                pic_str.trim();
                if (pic_str.length() == 0) return;
                Serial.println(pic_str);

                char buf_peminjam[6];
                pic_str.toCharArray(buf_peminjam, sizeof(buf_peminjam));
                
                pinjambarang(id_barang, jumlah, buf_peminjam);
            }
            else if (aksi == '2') {
                kembalikanBarang(id_barang, jumlah);
            }
            else if (aksi == '3') {
                laporRusak(id_barang, jumlah);
            }
        } else {
            Serial.println(F("Transaksi dibatalkan. Kembali ke markas utama."));
        }
        balik();
    }
    else if (menu_utama == '3') {
        while (Serial.available() > 0) { Serial.read(); }
        Serial.println(F("\n--- TAMBAH DATA ARSENAL BARU ---"));
        
        Serial.print(F("Ketik ID Baru (Maks 4 karakter, Example: R2D2 / BB8): "));
        while (Serial.available() == 0) { }
        String id_baru = Serial.readStringUntil('\n'); 
        id_baru.trim(); 
        if (id_baru.length() == 0) return;
        Serial.println(id_baru);
        
        Serial.print(F("Ketik Nama Item (Example: Lightsaber / Thermal Detonator): "));
        while (Serial.available() == 0) { }
        String nama_baru = Serial.readStringUntil('\n'); 
        nama_baru.trim(); 
        if (nama_baru.length() == 0) return;
        Serial.println(nama_baru);

        Serial.print(F("Ketik Kode Sektor (Maks 3 karakter, Example: DS1 [Death Star] / TAT [Tatooine]): "));
        while (Serial.available() == 0) { }
        String lokasi_baru = Serial.readStringUntil('\n'); 
        lokasi_baru.trim(); 
        if (lokasi_baru.length() == 0) return;
        Serial.println(lokasi_baru);

        Serial.print(F("Ketik Jumlah Stok Awal: "));
        while (Serial.available() == 0) { }
        String stok_str = Serial.readStringUntil('\n'); 
        stok_str.trim(); 
        if (stok_str.length() == 0) return;
        int stok_baru = stok_str.toInt();
        Serial.println(stok_baru);

        char buf_id[5], buf_nama[16], buf_lokasi[4];
        id_baru.toCharArray(buf_id, sizeof(buf_id));
        nama_baru.toCharArray(buf_nama, sizeof(buf_nama));
        lokasi_baru.toCharArray(buf_lokasi, sizeof(buf_lokasi));

        tambahData(buf_id, buf_nama, buf_lokasi, "-", stok_baru, 0);
        balik();
    }
    else {
        Serial.println(F("Pilihan tidak valid. Silakan coba lagi."));
        balik();
    }
}