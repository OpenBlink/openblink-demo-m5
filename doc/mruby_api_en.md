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

### factory_reset! Method

#### Arguments

None

#### Return Value (bool)

- true: Success
- false: Fail

#### Code Example

```ruby
Blink.factory_reset!
```
