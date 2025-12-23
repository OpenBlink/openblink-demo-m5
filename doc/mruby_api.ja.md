# mruby API 仕様

---

## Input クラス

### pressed? メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: ボタンが押されている
- false: 条件を満たしていない

#### コード例

```ruby
Input.pressed?()
```

### released? メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: ボタンが離されている
- false: 条件を満たしていない

#### コード例

```ruby
Input.released?()
```

---

## LED クラス

### set メソッド

#### 引数

- `LED.set([r, g, b])` - RGB LED の色を設定します。各値は 0〜255 の間である必要があります。

#### 戻り値 (bool)

- true: 成功
- false: 失敗

#### コード例

```ruby
LED.set([255, 0, 0]) # 赤
LED.set([0, 255, 0]) # 緑
LED.set([0, 0, 255]) # 青
```

---

## Blink クラス

### req_reload? メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: リロード要求が存在する
- false: リロード要求なし

#### コード例

```ruby
while true
  return if Blink.req_reload?
  # メイン処理
end
```

### lock メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: 成功
- false: 失敗

#### コード例

```ruby
Blink.lock
  # クリティカル処理
Blink.unlock
```

### unlock メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: 成功
- false: 失敗

#### コード例

```ruby
Blink.lock
  # クリティカル処理
Blink.unlock
```

### factory_reset! メソッド

- 処理が成功すると、再起動（ソフトリセット）を実行します。

#### 引数

なし

#### 戻り値 (bool)

- false: 失敗

#### コード例

```ruby
Blink.factory_reset!
```

#### 定数

- `BLINK_MAX_BYTECODE_SIZE`: 転送可能なバイトコードの最大サイズ制限（15KB）。

---

## Display クラス

Display クラスは、デバイスのディスプレイを制御するためのメソッドを提供します。

#### メソッド

- `Display.available?()`: ディスプレイが利用可能かどうかをチェックします。
- `Display.print(text)`: 現在のカーソル位置にテキストを表示します。
- `Display.println(text)` または `Display.puts(text)`: テキストを改行付きで表示します。
- `Display.set_text_size(size)`: テキストサイズを設定します。
- `Display.set_text_color(color)` または `Display.set_text_color(foreground, background)`: テキスト色を設定します。
- `Display.clear()`: ディスプレイをクリアします。
- `Display.set_cursor(x, y)`: カーソル位置を設定します。
- `Display.get_cursor()`: 現在のカーソル位置を [x, y] として取得します。
- `Display.color565(r, g, b)`: RGB 値を 16 ビットの色値に変換します。
- `Display.dimension()`: ディスプレイの寸法を [幅, 高さ] として返します。

#### 描画メソッド

- `Display.start_write()`: 描画操作のバッチ処理を開始し、パフォーマンスを向上させます。
- `Display.end_write()`: 描画操作のバッチ処理を終了します。
- `Display.fill_rect(x, y, width, height, color)`: 指定した色で長方形を塗りつぶします。
- `Display.draw_rect(x, y, width, height, color)`: 指定した色で長方形の輪郭を描画します。
- `Display.fill_circle(x, y, radius, color)`: 指定した色で円を塗りつぶします。
- `Display.draw_circle(x, y, radius, color)`: 指定した色で円の輪郭を描画します。
- `Display.draw_line(x0, y0, x1, y1, color)`: 2 点間に線を描画します。

#### 画像メソッド

- `Display.draw_bmpfile(path, x, y)`: 指定した位置に BMP 画像ファイルを描画します。
- `Display.draw_jpgfile(path, x, y)`: 指定した位置に JPEG 画像ファイルを描画します。
- `Display.draw_pngfile(path, x, y)`: 指定した位置に PNG 画像ファイルを描画します。
- `Display.draw_bmpstr(data, x, y)`: 指定した位置にバイナリデータから BMP 画像を描画します。
- `Display.draw_jpgstr(data, x, y)`: 指定した位置にバイナリデータから JPEG 画像を描画します。
- `Display.draw_pngstr(data, x, y)`: 指定した位置にバイナリデータから PNG 画像を描画します。

#### その他のメソッド

- `Display.scroll(dx, dy)`: 指定した量だけディスプレイをスクロールします。
- `Display.set_rotation(rotation)`: ディスプレイの回転を設定します（0-3、0°、90°、180°、270° を表します）。
- `Display.wait_display()`: ディスプレイ操作が完了するまで待機します。

---

## Canvas クラス

Canvas クラスは、描画操作のためのオフスクリーンバッファーを提供し、後でディスプレイに転送できます。

#### メソッド

- `Canvas.new(width, height, [depth])`: 指定した寸法とオプションの色深度で新しいキャンバスを作成します。
- `Canvas.create_sprite(width, height)`: 指定した寸法でスプライトバッファーを作成します。
- `Canvas.push_sprite(x, y)` または `Canvas.push_sprite(target, x, y)`: キャンバスの内容を指定した位置でディスプレイまたは別のキャンバスに転送します。
- `Canvas.delete_sprite()`: スプライトバッファーを削除します。
- `Canvas.destroy()`: キャンバスを破棄してリソースを解放します。

#### テキストメソッド

- `Canvas.print(text)`: 現在のカーソル位置にテキストを表示します。
- `Canvas.puts(text)`: テキストを改行付きで表示します。
- `Canvas.set_text_size(size)`: テキストサイズを設定します。
- `Canvas.set_text_color(color)` または `Canvas.set_text_color(foreground, background)`: テキスト色を設定します。
- `Canvas.set_cursor(x, y)`: カーソル位置を設定します。
- `Canvas.get_cursor()`: 現在のカーソル位置を [x, y] として取得します。
- `Canvas.clear()`: キャンバスをクリアします。

#### 描画メソッド

- `Canvas.fill_rect(x, y, width, height, color)`: 指定した色で長方形を塗りつぶします。
- `Canvas.draw_rect(x, y, width, height, color)`: 指定した色で長方形の輪郭を描画します。
- `Canvas.fill_circle(x, y, radius, color)`: 指定した色で円を塗りつぶします。
- `Canvas.draw_circle(x, y, radius, color)`: 指定した色で円の輪郭を描画します。
- `Canvas.draw_line(x0, y0, x1, y1, color)`: 2 点間に線を描画します。

#### 画像メソッド

- `Canvas.draw_bmpfile(path, x, y)`: 指定した位置に BMP 画像ファイルを描画します。
- `Canvas.draw_jpgfile(path, x, y)`: 指定した位置に JPEG 画像ファイルを描画します。
- `Canvas.draw_pngfile(path, x, y)`: 指定した位置に PNG 画像ファイルを描画します。
- `Canvas.draw_bmpstr(data, x, y)`: 指定した位置にバイナリデータから BMP 画像を描画します。
- `Canvas.draw_jpgstr(data, x, y)`: 指定した位置にバイナリデータから JPEG 画像を描画します。
- `Canvas.draw_pngstr(data, x, y)`: 指定した位置にバイナリデータから PNG 画像を描画します。

#### その他のメソッド

- `Canvas.scroll(dx, dy)`: 指定した量だけキャンバスをスクロールします。
- `Canvas.set_rotation(rotation)`: キャンバスの回転を設定します（0-3、0°、90°、180°、270° を表します）。
- `Canvas.dimension()`: キャンバスの寸法を [幅, 高さ] として返します。

---

## ボタン定数

OpenBlink は、デバイス上の物理ボタンにアクセスするための定数を提供します。

#### 定数

- `BtnA`: ボタン A への参照。
- `BtnB`: ボタン B への参照。
- `BtnC`: ボタン C への参照。

#### メソッド

ボタン定数には以下のメソッドがあります：

- `is_pressed?()`: ボタンが現在押されているかどうかをチェックします。
- `was_pressed?()`: 前回のチェック以降にボタンが押されたかどうかをチェックします。
- `number()`: ボタンの数値識別子を返します。

#### 例

```ruby
if BtnA.is_pressed?
  puts "ボタンAが押されています！"
end

if BtnC.was_pressed?
  puts "ボタンCが押されました！"
end
```
