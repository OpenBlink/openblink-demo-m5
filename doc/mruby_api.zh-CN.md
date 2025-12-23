# mruby API 规范

---

## Input 类

### pressed? 方法

#### 参数

无

#### 返回值 (bool)

- true: 按钮被按下
- false: 条件不满足

#### 代码示例

```ruby
Input.pressed?()
```

### released? 方法

#### 参数

无

#### 返回值 (bool)

- true: 按钮被释放
- false: 条件不满足

#### 代码示例

```ruby
Input.released?()
```

---

## LED 类

### set 方法

#### 参数

- `LED.set([r, g, b])` - 设置 RGB LED 颜色。每个值应在 0-255 之间。

#### 返回值 (bool)

- true: 成功
- false: 失败

#### 代码示例

```ruby
LED.set([255, 0, 0]) # 红色
LED.set([0, 255, 0]) # 绿色
LED.set([0, 0, 255]) # 蓝色
```

---

## Blink 类

### req_reload? 方法

#### 参数

无

#### 返回值 (bool)

- true: 存在重载请求
- false: 无重载请求

#### 代码示例

```ruby
while true
  return if Blink.req_reload?
  # 主要处理
end
```

### lock 方法

#### 参数

无

#### 返回值 (bool)

- true: 成功
- false: 失败

#### 代码示例

```ruby
Blink.lock
  # Critical process
Blink.unlock
```

### unlock 方法

#### 参数

无

#### 返回值 (bool)

- true: 成功
- false: 失败

#### 代码示例

```ruby
Blink.lock
  # Critical process
Blink.unlock
```

### factory_reset! 方法

- 处理成功后，系统将执行重启（软重置）。

#### 参数

无

#### 返回值 (bool)

- false: 失败

#### 代码示例

```ruby
Blink.factory_reset!
```

#### 常量

- `BLINK_MAX_BYTECODE_SIZE`: 可传输字节码的最大大小限制（15KB）。

---

## Display 类

Display 类提供用于控制设备显示屏的方法。

#### 方法

- `Display.available?()`: 检查显示屏是否可用。
- `Display.print(text)`: 在当前光标位置打印文本。
- `Display.println(text)` 或 `Display.puts(text)`: 打印文本并换行。
- `Display.set_text_size(size)`: 设置文本大小。
- `Display.set_text_color(color)` 或 `Display.set_text_color(foreground, background)`: 设置文本颜色。
- `Display.clear()`: 清除显示屏。
- `Display.set_cursor(x, y)`: 设置光标位置。
- `Display.get_cursor()`: 获取当前光标位置，返回 [x, y]。
- `Display.color565(r, g, b)`: 将 RGB 值转换为 16 位颜色值。
- `Display.dimension()`: 返回显示屏尺寸，格式为 [宽度, 高度]。

#### 绘图方法

- `Display.start_write()`: 开始批量绘图操作以提高性能。
- `Display.end_write()`: 结束批量绘图操作。
- `Display.fill_rect(x, y, width, height, color)`: 用指定颜色填充矩形。
- `Display.draw_rect(x, y, width, height, color)`: 用指定颜色绘制矩形轮廓。
- `Display.fill_circle(x, y, radius, color)`: 用指定颜色填充圆形。
- `Display.draw_circle(x, y, radius, color)`: 用指定颜色绘制圆形轮廓。
- `Display.draw_line(x0, y0, x1, y1, color)`: 在两点之间绘制线条。

#### 图像方法

- `Display.draw_bmpfile(path, x, y)`: 在指定位置绘制 BMP 图像文件。
- `Display.draw_jpgfile(path, x, y)`: 在指定位置绘制 JPEG 图像文件。
- `Display.draw_pngfile(path, x, y)`: 在指定位置绘制 PNG 图像文件。
- `Display.draw_bmpstr(data, x, y)`: 在指定位置从二进制数据绘制 BMP 图像。
- `Display.draw_jpgstr(data, x, y)`: 在指定位置从二进制数据绘制 JPEG 图像。
- `Display.draw_pngstr(data, x, y)`: 在指定位置从二进制数据绘制 PNG 图像。

#### 其他方法

- `Display.scroll(dx, dy)`: 按指定量滚动显示屏。
- `Display.set_rotation(rotation)`: 设置显示屏旋转（0-3，表示 0°、90°、180°、270°）。
- `Display.wait_display()`: 等待显示操作完成。

---

## Canvas 类

Canvas 类提供用于绘图操作的离屏缓冲区，随后可以将其推送到显示屏。

#### 方法

- `Canvas.new(width, height, [depth])`: 创建具有指定尺寸和可选颜色深度的新画布。
- `Canvas.create_sprite(width, height)`: 创建具有指定尺寸的精灵缓冲区。
- `Canvas.push_sprite(x, y)` 或 `Canvas.push_sprite(target, x, y)`: 将画布内容推送到指定位置的显示屏或另一个画布。
- `Canvas.delete_sprite()`: 删除精灵缓冲区。
- `Canvas.destroy()`: 销毁画布并释放资源。

#### 文本方法

- `Canvas.print(text)`: 在当前光标位置打印文本。
- `Canvas.puts(text)`: 打印文本并换行。
- `Canvas.set_text_size(size)`: 设置文本大小。
- `Canvas.set_text_color(color)` 或 `Canvas.set_text_color(foreground, background)`: 设置文本颜色。
- `Canvas.set_cursor(x, y)`: 设置光标位置。
- `Canvas.get_cursor()`: 获取当前光标位置，返回 [x, y]。
- `Canvas.clear()`: 清除画布。

#### 绘图方法

- `Canvas.fill_rect(x, y, width, height, color)`: 用指定颜色填充矩形。
- `Canvas.draw_rect(x, y, width, height, color)`: 用指定颜色绘制矩形轮廓。
- `Canvas.fill_circle(x, y, radius, color)`: 用指定颜色填充圆形。
- `Canvas.draw_circle(x, y, radius, color)`: 用指定颜色绘制圆形轮廓。
- `Canvas.draw_line(x0, y0, x1, y1, color)`: 在两点之间绘制线条。

#### 图像方法

- `Canvas.draw_bmpfile(path, x, y)`: 在指定位置绘制 BMP 图像文件。
- `Canvas.draw_jpgfile(path, x, y)`: 在指定位置绘制 JPEG 图像文件。
- `Canvas.draw_pngfile(path, x, y)`: 在指定位置绘制 PNG 图像文件。
- `Canvas.draw_bmpstr(data, x, y)`: 在指定位置从二进制数据绘制 BMP 图像。
- `Canvas.draw_jpgstr(data, x, y)`: 在指定位置从二进制数据绘制 JPEG 图像。
- `Canvas.draw_pngstr(data, x, y)`: 在指定位置从二进制数据绘制 PNG 图像。

#### 其他方法

- `Canvas.scroll(dx, dy)`: 按指定量滚动画布。
- `Canvas.set_rotation(rotation)`: 设置画布旋转（0-3，表示 0°、90°、180°、270°）。
- `Canvas.dimension()`: 返回画布尺寸，格式为 [宽度, 高度]。

---

## 按钮常量

OpenBlink 提供用于访问设备上物理按钮的常量。

#### 常量

- `BtnA`: 按钮 A 的引用。
- `BtnB`: 按钮 B 的引用。
- `BtnC`: 按钮 C 的引用。

#### 方法

按钮常量具有以下方法：

- `is_pressed?()`: 检查按钮当前是否被按下。
- `was_pressed?()`: 检查自上次检查以来按钮是否被按下。
- `number()`: 返回按钮的数字标识符。

#### 示例

```ruby
if BtnA.is_pressed?
  puts "按钮A被按下！"
end

if BtnC.was_pressed?
  puts "按钮C被按下过！"
end
```
