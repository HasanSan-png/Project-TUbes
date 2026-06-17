#ifndef INVETARIS_H
#define INVETARIS_H

#include <stdint.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>

#define MAX_ITEMS 45
#define NULL_INDEKS 255    

struct DataBarang {
  char id[5];         // Gabungan Kategori + ID (misal: "M001")
  char nama[16];      // Nama maksimal 15 huruf
  char lokasi[4];     // Kode lokasi (misal: "R1A")
  char pic_owner[6]; //owner sama pic digabung biar memorinya ga abis
  uint8_t stok;       // Jumlah barang (0-255)
  uint8_t status;     // 0:Tersedia, 1:Dipinjam, 2:Rusak, 
  uint8_t pic;        // 0:Admin, 1:Asisten A, dll
  uint8_t next_indeks; 
};

extern struct DataBarang gudang[MAX_ITEMS];
extern uint8_t head_indeks;
extern uint8_t free_head;

//void updateStok(char* input_id, uint8_t stok_baru);
//void updateStatus(char* input_id, uint8_t status_baru);
void CekSound();
void pinjambarang(char* input_id, uint8_t jumlah_pinjam, char* pic_peminjam);
void kembalikanbarang(char* input_id, uint8_t jumlah_kembali);
void hapusdata(uint8_t indeks_target);
void tambahData(char* input_id, char* input_nama, char* input_lokasi, char* input_pic_owner, uint8_t input_stok, uint8_t input_status);
void printoutput();
void printall(); //ini gue tambahin buat kek print semua tp ga satu2 gitu misal pengen tau brp stok dll
//void READ();
void balik();
void mainmenu();
void Rusak(char* input_id, uint8_t jumlah_rusak);
#endif