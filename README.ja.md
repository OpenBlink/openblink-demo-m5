# OpenBlink Demo M5 (日本語)

[![English](https://img.shields.io/badge/language-English-blue.svg)](README.md)
[![中文](https://img.shields.io/badge/language-中文-red.svg)](README.zh-CN.md)
[![日本語](https://img.shields.io/badge/language-日本語-green.svg)](README.ja.md)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/OpenBlink/openblink-demo-m5)

## OpenBlink とは

**_OpenBlink_** は **_ViXion Blink_** からフォークされたオープンソースプロジェクトです。

- 高い生産性を持つ軽量言語 Ruby を使用して組み込みデバイスを開発できます。
- プログラムの書き換えとデバッグコンソールは完全にワイヤレスです。（BluetoothLE）
- 書き換え時間は 0.1 秒未満で、マイクロプロセッサの再起動を必要としません。（これを「Blink」と呼んでいます）

## OpenBlink の入手方法

リポジトリをクローンしてサブモジュールを初期化するには、次のコマンドを実行します：

```console
$ git clone https://github.com/OpenBlink/openblink-demo-m5.git
$ pio run
$ pio run -e m5stack-stamps3 -t erase -t upload
```

> **注意:** platformio.ini には`m5stack-stamps3`と`m5stack-atom`の両方の環境が設定されており、デバイス操作に使用できます。上記の例では`m5stack-stamps3`を使用していますが、コマンド内の「`m5stack-stamps3`」を「`m5stack-atom`」に置き換えることで`m5stack-atom`を使用できます。

## 検証済みハードウェア

以下のハードウェアプラットフォームは OpenBlink でテスト済みです：

- M5 StampS3 (Espressif ESP32-S3FN8)
- M5 ATOM (Espressif ESP32)

## ドキュメント

より詳細なドキュメントについては、[doc ディレクトリ](./doc)をご確認ください。
コードベースの理解を助ける AI 駆動の包括的なドキュメントは、[DeepWiki](https://deepwiki.com/OpenBlink/openblink-demo-m5)をご覧ください。

## mruby/c LED 制御 API

OpenBlink は mruby/c を通じて基板上の RGB LED を制御するためのシンプルな API を提供しています。

### 利用可能なクラスとメソッド

#### LED クラス

- `LED.set([r, g, b])` - RGB LED の色を設定します。各値は 0〜255 の間である必要があります。

### 例：LED 点滅コード

異なる色で LED を点滅させる簡単な例です：

```ruby
# RGB LED 点滅例
while true do
  # 赤
  LED.set([255, 0, 0])
  sleep 1

  # 緑
  LED.set([0, 255, 0])
  sleep 1

  # 青
  LED.set([0, 0, 255])
  sleep 1

end
```

この例は以下を示しています：

- `LED.set`メソッドを使用した RGB LED 色の設定
- RGB 値を指定するための配列の使用
