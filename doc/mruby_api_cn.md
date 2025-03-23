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

### factory_reset! 方法

#### 参数

无

#### 返回值 (bool)

- true: 成功
- false: 失败

#### 代码示例

```ruby
Blink.factory_reset!
```
