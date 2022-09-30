In a real project, I'd compress, encrypt, and pack all these data into a single packed file (e.g .pak).

Reasons:
1. Compression - Smaller size.
2. Encryption - Less malicious manipulation of code (like manipulation of textures which allows "easy" wallhacks).
3. Single packed file - Much faster reading of data into memory on most filesystem types like NTFS/exFAT/Ext* due to latency against reading hundreds (or thousands) of files.
--------------------------------------------------------------------------------------------------------
В реальном проекте я бы сжал, зашифровал и упаковал все эти данные в один упакованный файл (например, pak).

Причины:
1. Сжатие - Меньший размер.
2. Шифрование - менее злонамеренные манипуляции с кодом (например, манипуляции с текстурами, которые позволяют "легко" взламывать стены).
3. Единый упакованный файл - Гораздо более быстрое считывание данных в память в большинстве типов файловых систем, таких как NTFS/exFAT/Ext*, из-за задержки при чтении сотен (или тысяч) файлов.