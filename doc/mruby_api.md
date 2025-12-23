# mruby API Specification

---

## Input Class

### pressed? Method

#### Arguments

None

#### Return Value (bool)

- true: Button is pressed
- false: Condition not met

#### Code Example

```ruby
Input.pressed?()
```

### released? Method

#### Arguments

None

#### Return Value (bool)

- true: Button is released
- false: Condition not met

#### Code Example

```ruby
Input.released?()
```

---

## LED Class

### set Method

#### Arguments

- `LED.set([r, g, b])` - Sets the RGB LED color. Each value should be between 0-255.

#### Return Value (bool)

- true: Success
- false: Failure

#### Code Example

```ruby
LED.set([255, 0, 0]) # Red
LED.set([0, 255, 0]) # Green
LED.set([0, 0, 255]) # Blue
```

---

## Blink Class

### req_reload? Method

#### Arguments

None

#### Return Value (bool)

- true: Reload request exists
- false: No reload request

#### Code Example

```ruby
while true
  return if Blink.req_reload?
  # Main processing
end
```

### lock Method

#### Arguments

None

#### Return Value (bool)

- true: Success
- false: Failure

#### Code Example

```ruby
while true
  return if Blink.req_reload?
  # Main processing

  Blink.lock
  # Critical process
  Blink.unlock
end
```

### unlock Method

#### Arguments

None

#### Return Value (bool)

- true: Success
- false: Failure

#### Code Example

```ruby
while true
  return if Blink.req_reload?
  # Main processing

  Blink.lock
  # Critical process
  Blink.unlock
end
```

### factory_reset! Method

- Upon successful processing, a restart (soft reset) will be executed.

#### Arguments

None

#### Return Value (bool)

- false: Fail

#### Code Example

```ruby
Blink.factory_reset!
```

#### Constants

- `BLINK_MAX_BYTECODE_SIZE`: Maximum size limit (15KB) for transferable bytecode.

---

## Display Class

The Display class provides methods for controlling the device's display.

#### Methods

- `Display.available?()`: Checks if a display is available.
- `Display.print(text)`: Prints text at the current cursor position.
- `Display.println(text)` or `Display.puts(text)`: Prints text with a newline.
- `Display.set_text_size(size)`: Sets the text size.
- `Display.set_text_color(color)` or `Display.set_text_color(foreground, background)`: Sets the text color.
- `Display.clear()`: Clears the display.
- `Display.set_cursor(x, y)`: Sets the cursor position.
- `Display.get_cursor()`: Gets the current cursor position, returns [x, y].
- `Display.color565(r, g, b)`: Converts RGB values to a 16-bit color value.
- `Display.dimension()`: Returns the display dimensions as [width, height].

#### Drawing Methods

- `Display.start_write()`: Begins a batch of drawing operations for improved performance.
- `Display.end_write()`: Ends a batch of drawing operations.
- `Display.fill_rect(x, y, width, height, color)`: Fills a rectangle with the specified color.
- `Display.draw_rect(x, y, width, height, color)`: Draws a rectangle outline with the specified color.
- `Display.fill_circle(x, y, radius, color)`: Fills a circle with the specified color.
- `Display.draw_circle(x, y, radius, color)`: Draws a circle outline with the specified color.
- `Display.draw_line(x0, y0, x1, y1, color)`: Draws a line between two points.

#### Image Methods

- `Display.draw_bmpfile(path, x, y)`: Draws a BMP image from a file at the specified position.
- `Display.draw_jpgfile(path, x, y)`: Draws a JPEG image from a file at the specified position.
- `Display.draw_pngfile(path, x, y)`: Draws a PNG image from a file at the specified position.
- `Display.draw_bmpstr(data, x, y)`: Draws a BMP image from binary data at the specified position.
- `Display.draw_jpgstr(data, x, y)`: Draws a JPEG image from binary data at the specified position.
- `Display.draw_pngstr(data, x, y)`: Draws a PNG image from binary data at the specified position.

#### Other Methods

- `Display.scroll(dx, dy)`: Scrolls the display by the specified amount.
- `Display.set_rotation(rotation)`: Sets the display rotation (0-3, representing 0°, 90°, 180°, 270°).
- `Display.wait_display()`: Waits for display operations to complete.

---

## Canvas Class

The Canvas class provides an off-screen buffer for drawing operations, which can then be pushed to the display.

#### Methods

- `Canvas.new(width, height, [depth])`: Creates a new canvas with the specified dimensions and optional color depth.
- `Canvas.create_sprite(width, height)`: Creates a sprite buffer with the specified dimensions.
- `Canvas.push_sprite(x, y)` or `Canvas.push_sprite(target, x, y)`: Pushes the canvas content to the display or another canvas at the specified position.
- `Canvas.delete_sprite()`: Deletes the sprite buffer.
- `Canvas.destroy()`: Destroys the canvas and frees resources.

#### Text Methods

- `Canvas.print(text)`: Prints text at the current cursor position.
- `Canvas.puts(text)`: Prints text with a newline.
- `Canvas.set_text_size(size)`: Sets the text size.
- `Canvas.set_text_color(color)` or `Canvas.set_text_color(foreground, background)`: Sets the text color.
- `Canvas.set_cursor(x, y)`: Sets the cursor position.
- `Canvas.get_cursor()`: Gets the current cursor position, returns [x, y].
- `Canvas.clear()`: Clears the canvas.

#### Drawing Methods

- `Canvas.fill_rect(x, y, width, height, color)`: Fills a rectangle with the specified color.
- `Canvas.draw_rect(x, y, width, height, color)`: Draws a rectangle outline with the specified color.
- `Canvas.fill_circle(x, y, radius, color)`: Fills a circle with the specified color.
- `Canvas.draw_circle(x, y, radius, color)`: Draws a circle outline with the specified color.
- `Canvas.draw_line(x0, y0, x1, y1, color)`: Draws a line between two points.

#### Image Methods

- `Canvas.draw_bmpfile(path, x, y)`: Draws a BMP image from a file at the specified position.
- `Canvas.draw_jpgfile(path, x, y)`: Draws a JPEG image from a file at the specified position.
- `Canvas.draw_pngfile(path, x, y)`: Draws a PNG image from a file at the specified position.
- `Canvas.draw_bmpstr(data, x, y)`: Draws a BMP image from binary data at the specified position.
- `Canvas.draw_jpgstr(data, x, y)`: Draws a JPEG image from binary data at the specified position.
- `Canvas.draw_pngstr(data, x, y)`: Draws a PNG image from binary data at the specified position.

#### Other Methods

- `Canvas.scroll(dx, dy)`: Scrolls the canvas by the specified amount.
- `Canvas.set_rotation(rotation)`: Sets the canvas rotation (0-3, representing 0°, 90°, 180°, 270°).
- `Canvas.dimension()`: Returns the canvas dimensions as [width, height].

---

## Button Constants

OpenBlink provides constants for accessing the physical buttons on the device.

#### Constants

- `BtnA`: Reference to button A.
- `BtnB`: Reference to button B.
- `BtnC`: Reference to button C.

#### Methods

Button constants have the following methods:

- `is_pressed?()`: Checks if the button is currently pressed.
- `was_pressed?()`: Checks if the button was pressed since the last check.
- `number()`: Returns the button's numeric identifier.

#### Example

```ruby
if BtnA.is_pressed?
  puts "Button A is pressed!"
end

if BtnC.was_pressed?
  puts "Button C was pressed!"
end
```
