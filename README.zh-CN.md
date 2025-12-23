# OpenBlink Demo M5 (中文)

[![English](https://img.shields.io/badge/language-English-blue.svg)](README.md)
[![中文](https://img.shields.io/badge/language-中文-red.svg)](README.zh-CN.md)
[![日本語](https://img.shields.io/badge/language-日本語-green.svg)](README.ja.md)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/OpenBlink/openblink-demo-m5)

## 什么是 OpenBlink

**_OpenBlink_** 是一个从 **_ViXion Blink_** 分支出来的开源项目。

- 可以使用 Ruby 这种高效轻量级语言来开发嵌入式设备。
- 程序重写和调试控制台完全无线。（蓝牙低功耗）
- 重写时间少于 0.1 秒，且不涉及微处理器重启。（我们称之为"Blink"）

## 如何获取 OpenBlink

要克隆仓库并初始化子模块，请运行以下命令：

```console
$ git clone https://github.com/OpenBlink/openblink-demo-m5.git
$ pio run
$ pio run -e m5stack-stamps3 -t erase -t upload
```

> **注意:** platformio.ini 中配置了`m5stack-stamps3`和`m5stack-atom`两种环境，可用于设备操作。上面的示例使用`m5stack-stamps3`，但您可以通过将命令中的`m5stack-stamps3`替换为`m5stack-atom`来使用`m5stack-atom`。

## 已验证的硬件

以下硬件平台已经过 OpenBlink 测试：

- M5 StampS3 (Espressif ESP32-S3FN8)
- M5 ATOM (Espressif ESP32)

## 文档

有关更详细的文档，请查看[文档目录](./doc)
如需查阅 AI 驱动的全面文档以帮助您理解代码库，请访问[DeepWiki](https://deepwiki.com/OpenBlink/openblink-demo-m5)

## mruby/c LED 控制 API

OpenBlink 提供了一个简单的 API，通过 mruby/c 控制板载 RGB LED。

### 可用的类和方法

#### LED 类

- `LED.set([r, g, b])` - 设置 RGB LED 颜色。每个值应在 0-255 之间。

### 示例：LED 闪烁代码

这是一个使 LED 以不同颜色闪烁的简单示例：

```ruby
# RGB LED 闪烁示例
while true do
  # 红色
  LED.set([255, 0, 0])
  sleep 1

  # 绿色
  LED.set([0, 255, 0])
  sleep 1

  # 蓝色
  LED.set([0, 0, 255])
  sleep 1

end
```

此示例演示了：

- 使用`LED.set`方法设置 RGB LED 颜色
- 使用数组指定 RGB 值
