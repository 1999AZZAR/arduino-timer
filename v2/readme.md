# Timer Tamiya

Ini adalah program untuk mengukur waktu tempuh dan jumlah lap Tamiya melalui jalur yang dilengkapi dengan sensor cahaya. Program ini menggunakan Arduino dan LCD I2C untuk menampilkan informasi waktu dan jumlah lap.

## Kebutuhan Perangkat Keras

- Arduino Uno atau kompatibel
- LCD I2C 16x2
- Sensor cahaya
- Tombol lap terakhir
- Tombol reset

## Koneksi Perangkat Keras

### Sensor Cahaya

- Pin Sensor 1: Terhubung ke pin A0 pada Arduino
- Pin Sensor 2: Terhubung ke pin A1 pada Arduino
- Pin Sensor 3: Terhubung ke pin A2 pada Arduino

### LCD I2C

- SDA: Terhubung ke pin analog A4 pada Arduino Uno
- SCL: Terhubung ke pin analog A5 pada Arduino Uno

### Tombol Lap Terakhir

- Pin Lap Button: Terhubung ke pin digital 2 pada Arduino

### Tombol Reset

- Pin Reset Button: Terhubung ke pin digital 3 pada Arduino

## Instalasi Perangkat Lunak

1. Pasang Arduino IDE dan perluas library Wire dan LiquidCrystal_I2C.
2. Salin kode program Timer Tamiya ke dalam Arduino IDE.
3. Sambungkan Arduino dengan komputer menggunakan kabel USB.
4. Pilih papan Arduino yang sesuai dan port serial yang terhubung.
5. Unggah kode program ke Arduino.

## Cara Penggunaan

1. Sambungkan sensor cahaya, LCD I2C, tombol lap terakhir, dan tombol reset ke Arduino sesuai dengan koneksi perangkat keras yang disebutkan di atas.
2. Hubungkan Arduino ke daya atau komputer menggunakan kabel USB.
3. Setelah Arduino menyala, LCD akan menampilkan pesan "Timer Tamiya Siap!".
4. Letakkan Tamiya di jalur yang dilengkapi dengan sensor cahaya.
5. Tamiya akan mendeteksi jalur melalui sensor cahaya dan waktu tempuh serta jumlah lap akan ditampilkan di LCD.
6. Tekan tombol lap terakhir untuk menghentikan penghitungan waktu dan menampilkan waktu total dan jumlah lap terakhir.
7. Tekan tombol reset untuk mengatur ulang penghitungan waktu dan menghapus data lap.

## Kontribusi

Kontribusi terbuka untuk perbaikan atau peningkatan program ini sangat diterima. Silakan buka masalah (issue) atau kirimkan permintaan tarik (pull request) ke repositori ini.
