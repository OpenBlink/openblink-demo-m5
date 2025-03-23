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

### factory_reset! メソッド

#### 引数

なし

#### 戻り値 (bool)

- true: 成功
- false: 失敗

#### コード例

```ruby
Blink.factory_reset!
```
