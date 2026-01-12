# so_long - 2D Oyun Motoru

## 📚 Proje Açıklaması

**so_long**, MiniLibX grafik kütüphanesi kullanarak basit bir 2D oyun yapılan bir proje. Oyuncu bir harita üzerinde hareket eder, koleksiyonları toplar ve çıkışa ulaşmayı amaçlar. Bu proje, grafik programlaması, event handling ve oyun loop'ları gibi konseptleri öğretir.

## 🎯 Oyun Mekanikası

### Oyun Amacı
- Haritada dağılmış olan koleksiyonları (collectibles) topla
- Tüm koleksiyonları topladıktan sonra çıkışa ulaş (exit)

### Kontroller
```
W veya ↑ - Yukarı hareket
S veya ↓ - Aşağı hareket
A veya ← - SolA hareket
D veya → - Sağ hareket
ESC      - Oyundan çık
```

### Harita Elemanları
```
1 - Duvar (geçilemez)
0 - Boş alan
P - Oyuncu başlangıç pozisyonu
C - Koleksiyon (toplanacak)
E - Çıkış (hedef)
```

### Harita Örneği
```
1 1 1 1 1 1 1 1 1 1
1 P 0 0 1 C 0 0 0 1
1 0 1 0 0 0 0 1 0 1
1 0 0 0 C 0 1 0 C 1
1 C 0 1 0 0 0 0 E 1
1 1 1 1 1 1 1 1 1 1
```

## 🛠️ Özellikler

### Grafik Sistemi
- **MiniLibX**: Grafik rendering
- **Texture'lar**: Oyuncu, duvarlar, koleksiyonlar, çıkış
- **Screen Update**: 60 FPS rendering

### Game Loop
```c
while (!game->window_closed) {
    handle_input();
    update_game_state();
    render_frame();
    usleep(16667);  // ~60 FPS
}
```

### Harita Yükleme
- `.ber` formatında harita dosyası
- Harita validasyonu (P, C, E sayısı kontrol)
- Flood fill ile oynanabilir alan kontrolü

## 🛠️ Derleme ve Çalıştırma

```bash
cd so_long
make                    # Oyunu derle

./so_long maps/map.ber  # Oyunu başlat
```

## 📖 Temel Yapı

### Oyun Durumu Yapısı
```c
typedef struct s_game {
    void        *mlx;           // MiniLibX pointer
    void        *window;        // Pencere
    char        **map;          // Harita verisi
    int         player_x;       // Oyuncu X
    int         player_y;       // Oyuncu Y
    int         collectibles;   // Toplanacak sayı
    int         moves;          // Hareket sayısı
    int         width;
    int         height;
} t_game;
```

### Görüntü Yapısı
```c
typedef struct s_image {
    void        *img;           // MiniLibX image
    int         width;
    int         height;
} t_image;
```

## 💡 Algoritma ve Teknikler

### 1. Harita Yükleme

```c
// 1. Dosyayı oku
// 2. Her satırı parse et
// 3. Boyutları belirle
// 4. Validasyon yap (P, C, E var mı?)
// 5. Flood fill ile oynanabilir kontrol
```

### 2. Oyuncu Hareketi

```c
// Yön tuşlarına basıldığında:
// 1. Hedef pozisyonu hesapla
// 2. Hedef duvar mı kontrol et
// 3. Duvar değilse hareket et
// 4. Koleksiyon varsa topla
// 5. Çıkışa ulaştı mı kontrol et
```

### 3. Flood Fill (Harita Validasyonu)

```c
// Amaç: Oyuncu başlangıcından her alana ulaşılabilir mi?
void flood_fill(char **map, int x, int y, t_point size)
{
    if (x < 0 || y < 0 || x >= size.x || y >= size.y)
        return;
    if (map[y][x] == '1' || map[y][x] == 'X')
        return;
    
    map[y][x] = 'X';  // Ziyaret ettik işaretle
    
    // 4 yöne recursive flood fill
    flood_fill(map, x + 1, y, size);
    flood_fill(map, x - 1, y, size);
    flood_fill(map, x, y + 1, size);
    flood_fill(map, x, y - 1, size);
}
```

## 📚 Öğrenme Çıktıları

✅ MiniLibX grafik kütüphanesi öğrenildi  
✅ Event handling ve input processing yapıldı  
✅ Oyun loop mekanizması anlaşıldı  
✅ Grafik rendering implementasyonu öğrenildi  
✅ Dosya I/O (harita yükleme) yapıldı  
✅ Flood fill algoritması uygulandı  
✅ Texture ve image işlemlerinde yeterlilik elde edildi  

## 🔧 Dosya Yapısı

```
so_long/
├── source/
│   ├── main.c               # Entry point
│   ├── game_init.c          # Oyun başlatma
│   ├── game_loop.c          # Ana loop
│   ├── map_parsing.c        # Harita yükleme
│   ├── validation.c         # Harita kontrolü
│   ├── rendering.c          # Grafik çizme
│   ├── input_handler.c      # Input işleme
│   ├── movement.c           # Oyuncu hareketi
│   ├── utils.c              # Yardımcı fonksiyonlar
│   └── cleanup.c            # Kaynakları serbest bırakma
├── includes/
│   └── so_long.h            # Header dosyası
├── maps/
│   ├── map.ber
│   ├── map_bonus.ber
│   └── ...
├── textures/
│   ├── player.xpm
│   ├── wall.xpm
│   ├── collectible.xpm
│   ├── exit.xpm
│   └── ...
├── minilibx-linux/
├── Makefile
└── Makefile.rules
```

## 📝 MiniLibX Fonksiyonları

### Pencere Yönetimi
```c
void *mlx_init();
void *mlx_new_window(void *mlx, int w, int h, char *title);
int mlx_destroy_window(void *mlx, void *window);
```

### Görüntü İşlemleri
```c
void *mlx_xpm_file_to_image(void *mlx, char *filename, int *w, int *h);
int mlx_put_image_to_window(void *mlx, void *window, void *image, int x, int y);
```

### Event Handling
```c
int mlx_hook(void *window, int event, int mask, int (*func)(), void *param);
int mlx_key_hook(void *window, int (*func)(), void *param);
```

### Game Loop
```c
int mlx_loop(void *mlx);
int mlx_loop_hook(void *mlx, int (*func)(), void *param);
```

## 🎯 Teknik Zorluklar

### 1. Harita Validasyonu
```
Gerekli kontroller:
- En az 1 P (oyuncu)
- En az 1 C (koleksiyon)
- En az 1 E (çıkış)
- Duvar ile çevrili (map_is_rectangular)
- Oyuncudan tüm alanara ulaşılabilir (flood_fill)
```

### 2. Graphics Rendering
```
- XPM formatı texture yükleme
- Tile-based rendering
- Smooth movement illüzyonu
```

### 3. Event Processing
```
- Key down/release events
- Window close event (ESC)
- Smooth movement (key state tracking)
```

## 🚀 Bonus Özellikler (İsteğe Bağlı)

- **Enemy System**: Hareketli düşmanlar
- **Animation**: Oyuncu ve collectible animasyonları
- **Visual Effects**: Efektler, parçacıklar
- **Sound**: Ses efektleri ve müzik
- **Better Maps**: Daha zorlayıcı haritalar

## 💡 Key Learning Points

1. **Graphics Programming**: MiniLibX library kullanımı
2. **Event-Driven Programming**: Input handling
3. **Game Loop**: Update ve render döngüsü
4. **Flood Fill Algorithm**: Pathfinding ve connectivity
5. **Resource Management**: Texture ve memory yönetimi
6. **Coordinate Systems**: 2D rendering

## 📚 Norm Standartları

- 80 karaktere kadar satır uzunluğu
- Fonksiyon başına maksimum 25 satır
- Memory leaks yoktur
- Norm compliance sağlanmıştır

Bu proje, grafik programlaması ve oyun geliştirmeye giriş sağlar.
