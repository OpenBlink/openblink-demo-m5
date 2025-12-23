led = true
sw_last = Input.pressed?()

puts "Hello World!"

RED = [255, 0, 0]
GREEN = [0, 255, 0]
BLUE = [0, 0, 255]

while true

  led = !led
  led = true if Input.pressed?()
  led = false if Input.pressed?()
  LED.set(GREEN) if led
  LED.set(BLUE) if !led

  sw = Input.pressed?()
  if sw_last != sw
    sw_last = sw
    puts (sw ? "SW pressed" : "SW released")
  end

  sleep_ms 500

end
